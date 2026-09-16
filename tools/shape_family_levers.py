#!/usr/bin/env python3
"""Generate bounded C++ choices for recurring non-EH codegen residues.

This module is deliberately a choice generator, not a compiler or an
acceptance check.  ``choices_for(text)`` returns the JSON shape consumed by
``shape_search.py``.  The transformations are intentionally narrow:

* ``sib`` reverses one independent integer addition at a time;
* ``register`` swaps adjacent, independent local definitions;
* ``bool`` materialises a call result before negating it;
* ``test`` reverses the operands of a simple bit-test condition;
* ``copy`` keeps a pointer alias live through its next guard or member load;
* ``store`` swaps adjacent independent simple field stores;
* ``loop`` toggles an empty-init/increment loop header between ``while`` and
  ``for``;
* ``branch`` folds a simple two-return boolean branch;
* ``constant`` materialises a literal false/true return;
* ``frame`` promotes a simple scalar local to an indexed two-element array.

The first two are useful probes for the hard-lane SIB and register-order
families.  A generated alternative is only a hypothesis: ``probe.py`` and the
ordinary byte gate remain the judge.  In particular, the current SIB family
has repeatedly shown a compiler-internal base/index choice even after these
source alternatives, so this tool must not be used to justify a guessed name
or an assembly fallback.

Usage::

    python3 tools/shape_family_levers.py SOURCE.cpp \
        --families sib,register,bool,test,copy,store,loop,branch,constant,frame > choices.json
    python3 tools/shape_search.py SOURCE.cpp "MANGLED" 0xRVA --size N \
        --choices choices.json
"""
import argparse
import json
import re
import sys
from pathlib import Path


# Keep this conservative.  A declaration with a call, arithmetic, or a
# comma-expression may have an observable order and is not a register-order
# probe.  Member reads and address-of reads are enough for the known family.
_ATOM = r"(?:[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*)*|\(?\s*&\s*[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*)*\s*\)?|\(\s*[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*)*\s*[*/+-]\s*[-+]?\d+\s*\)|[-+]?\d+)"
_DECL = re.compile(
    r"^(?P<indent>[ \t]+)"
    r"(?P<type>(?:(?:const|volatile|unsigned|signed|short|long|class|struct)\s+)*"
    r"[A-Za-z_]\w*(?:\s*<[^;=]+>)?(?:\s*[&*])*)\s+"
    r"(?P<name>[A-Za-z_]\w*)\s*=\s*(?P<expr>[^;]+);[ \t]*$"
)
_ADD = re.compile(
    r"^(?P<indent>[ \t]+)"
    r"(?P<prefix>(?:(?:const|volatile|unsigned|signed|short|long|class|struct)\s+)*"
    r"[A-Za-z_]\w*(?:\s*<[^;=]+>)?\s+)?"
    r"(?P<lhs>[A-Za-z_]\w*(?:\s*(?:->|\.)\s*[A-Za-z_]\w*)*)"
    r"\s*=\s*(?P<left>[^;+=]+?)\s*\+\s*(?P<right>[^;]+?);[ \t]*$", re.M
)
_NEGATED_CALL = re.compile(
    r"^(?P<indent>[ \t]*)return\s*!\s*(?P<call>[A-Za-z_]\w*(?:\s*::\s*[A-Za-z_]\w*)*"
    r"\s*\([^;{}]*\))\s*;[ \t]*$", re.M
)
_IF_LINE = re.compile(
    r"^(?P<indent>[ \t]*)if\s*\((?P<condition>.*)\)"
    r"(?P<tail>[ \t]*(?:\{[^\r\n]*)?)$",
    re.M,
)


def _unwrap_outer_parens(value):
    """Remove balanced outer parentheses from a small expression."""
    value = value.strip()
    changed = True
    while changed and value.startswith("(") and value.endswith(")"):
        changed = False
        depth = 0
        closes_at = None
        for index, char in enumerate(value):
            if char == "(":
                depth += 1
            elif char == ")":
                depth -= 1
                if depth == 0:
                    closes_at = index
                    break
        if closes_at == len(value) - 1:
            value = value[1:-1].strip()
            changed = True
    return value


def _top_level_ampersand(value):
    """Return the position of the only top-level bitwise ampersand."""
    parens = brackets = 0
    found = None
    for index, char in enumerate(value):
        if char == "(":
            parens += 1
        elif char == ")":
            parens -= 1
        elif char == "[":
            brackets += 1
        elif char == "]":
            brackets -= 1
        elif char == "&" and parens == 0 and brackets == 0:
            if found is not None:
                return None
            found = index
    return found


_BIT_ATOM = re.compile(
    r"[A-Za-z_]\w*(?:(?:\s*(?:->|\.)\s*[A-Za-z_]\w*)|"
    r"(?:\s*\[[^\]\r\n]+\]))*"
)
_POINTER_DECL = re.compile(
    r"^(?P<indent>[ \t]+)(?P<type>(?:(?:const|volatile)\s+)*[A-Za-z_]\w*"
    r"(?:\s*(?:::|->)\s*[A-Za-z_]\w*)*"
    r"\s*\*)\s*(?P<name>[A-Za-z_]\w*)\s*(?:=\s*[^;]+)?;[ \t]*$"
)
_ASSIGNMENT = re.compile(
    r"^(?P<indent>[ \t]+)(?P<name>[A-Za-z_]\w*)\s*=\s*(?P<rhs>[^;]+);[ \t]*$"
)
_GUARD = re.compile(
    r"^(?P<indent>[ \t]*)if\s*\(\s*(?P<name>[A-Za-z_]\w*)"
    r"\s*(?P<comparison>!=\s*0)?\s*\)[ \t]*(?:\{)?[ \t]*$"
)
_STORE = re.compile(
    r"^(?P<indent>[ \t]+)(?P<lhs>[A-Za-z_]\w*(?:(?:\s*(?:->|\.)\s*"
    r"[A-Za-z_]\w*)|(?:\s*\[[^\]\r\n]+\]))*)\s*=\s*"
    r"(?P<rhs>[^;]+);[ \t]*$"
)
_STORE_RHS = re.compile(r"^[A-Za-z0-9_ \t+*/%<>.&|^~\[\]()-?:!]+$")
_WHILE = re.compile(
    r"^(?P<indent>[ \t]*)while\s*\((?P<condition>[^{}\r\n]+)\)"
    r"(?P<tail>[ \t]*(?:\{[ \t]*)?)$"
)
_FOR_EMPTY = re.compile(
    r"^(?P<indent>[ \t]*)for\s*\(\s*;\s*(?P<condition>[^;{}\r\n]+)"
    r"\s*;\s*\)(?P<tail>[ \t]*(?:\{[ \t]*)?)$"
)
_BRANCH = re.compile(
    r"^(?P<indent>[ \t]*)if\s*\((?P<condition>[^{}\r\n]+)\)\s*"
    r"return\s+(?P<value>true|false)\s*;[ \t]*$"
)
_RETURN_BOOL = re.compile(
    r"^(?P<indent>[ \t]+)return\s+(?P<value>true|false)\s*;[ \t]*$"
)
_FRAME_DECL = re.compile(
    r"^(?P<indent>[ \t]+)(?P<type>unsigned int|int)\s+"
    r"(?P<name>[A-Za-z_]\w*)\s*=\s*(?P<expr>[^;]+);[ \t]*$"
)


def _in_function(lines, index):
    """Return whether a line is inside a function body using brace depth.

    This is not a C++ parser.  It only rejects the common class/namespace
    member-field case so a header declaration is never offered as a local
    register lever.  Strings and comments are harmless for the depth check in
    the source forms this tool accepts.
    """
    depth = 0
    seen_function = False
    for line in lines[:index + 1]:
        if ")" in line:
            seen_function = True
        depth += line.count("{") - line.count("}")
    return seen_function and depth > 0


def register_choices(text, limit=12):
    """Return safe adjacent independent-local-definition swaps.

    The swap is offered only when both initializers are atom-like and neither
    refers to the other's variable.  It is therefore a codegen experiment,
    not a semantic rewrite of a general statement sequence.
    """
    lines = text.splitlines(keepends=True)
    out = []
    occupied = []
    for i in range(len(lines) - 1):
        a, b = _DECL.match(lines[i]), _DECL.match(lines[i + 1])
        if not a or not b or a.group("indent") != b.group("indent"):
            continue
        if not _in_function(lines, i):
            continue
        an, bn = a.group("name"), b.group("name")
        ae, be = a.group("expr").strip(), b.group("expr").strip()
        if not re.fullmatch(_ATOM, ae) or not re.fullmatch(_ATOM, be):
            continue
        if re.search(r"\b%s\b" % re.escape(an), be) or re.search(r"\b%s\b" % re.escape(bn), ae):
            continue
        before = lines[i] + lines[i + 1]
        if text.count(before) != 1:
            continue
        start = text.index(before)
        end = start + len(before)
        if any(start < old_end and end > old_start
               for old_start, old_end in occupied):
            continue
        after = lines[i + 1] + lines[i]
        out.append({"before": before, "after": [after], "lever": "register-order"})
        occupied.append((start, end))
        if len(out) >= limit:
            break
    return out


def sib_choices(text, limit=12):
    """Return source-order alternatives for simple integer additions.

    The compiler may canonicalise both spellings to the same SIB byte; that
    negative result is useful evidence and is why this function never claims
    that a reversed expression is a match.
    """
    out = []
    for match in _ADD.finditer(text):
        line = match.group(0)
        if "+=" in line or text.count(line) != 1:
            continue
        left, right = match.group("left").strip(), match.group("right").strip()
        if not re.fullmatch(_ATOM, left) or not re.fullmatch(_ATOM, right):
            continue
        replacement = (f"{match.group('indent')}{match.group('prefix') or ''}"
                       f"{match.group('lhs').strip()} = "
                       f"{right} + {left};")
        if replacement == line:
            continue
        out.append({"before": line, "after": [replacement], "lever": "sib-order"})
        if len(out) >= limit:
            break
    return out


def bool_choices(text, limit=8):
    """Return the documented call-result-before-negation alternative."""
    out = []
    for match in _NEGATED_CALL.finditer(text):
        line = match.group(0)
        if text.count(line) != 1:
            continue
        indent, call = match.group("indent"), match.group("call")
        replacement = (f"{indent}unsigned char shape_result = (unsigned char)({call});\n"
                       f"{indent}return !shape_result;")
        out.append({"before": line, "after": [replacement], "lever": "bool-local"})
        if len(out) >= limit:
            break
    return out


def test_choices(text, limit=8):
    """Return alternatives that reverse a simple bit-test's operands.

    The parser accepts member/array expressions such as
    ``owner->m_words[index >> 5]`` and an optional ``!= 0`` comparison.  It
    deliberately rejects calls and compound expressions: this lever is only a
    codegen probe for commutative TEST residues, never a semantic rewrite.
    """
    out = []
    for match in _IF_LINE.finditer(text):
        line = match.group(0)
        if text.count(line) != 1:
            continue
        condition = match.group("condition").strip()
        comparison = re.fullmatch(
            r"(?P<expr>.+?)\s*(?P<op>!=|==)\s*0", condition
        )
        if comparison:
            condition = comparison.group("expr").strip()
            operator = comparison.group("op")
        else:
            operator = None
        condition = _unwrap_outer_parens(condition)
        split = _top_level_ampersand(condition)
        if split is None:
            continue
        left = condition[:split].strip()
        right = condition[split + 1:].strip()
        if not left or not right:
            continue
        if not _BIT_ATOM.fullmatch(left) or not _BIT_ATOM.fullmatch(right):
            continue
        if operator:
            new_condition = f"( {right} & {left} ) {operator} 0"
        else:
            new_condition = f"{right} & {left}"
        replacement = (f"{match.group('indent')}if ( {new_condition} )"
                       f"{match.group('tail')}")
        if replacement == line:
            continue
        out.append({"before": line, "after": [replacement],
                    "lever": "test-operand-order"})
        if len(out) >= limit:
            break
    return out


def _pointer_types(text):
    """Map simple pointer locals to their declared pointer type."""
    declarations = {}
    for line in text.splitlines():
        match = _POINTER_DECL.match(line)
        if match:
            declarations.setdefault(match.group("name"), []).append(
                match.group("type").strip()
            )
    # A text-only scan cannot model C++ scopes.  Refuse shadowed names rather
    # than borrowing a declaration from another block and emitting an alias
    # with an incompatible const-qualified type.
    return {name: values[0] for name, values in declarations.items()
            if len(values) == 1}


def copy_choices(text, limit=8):
    """Keep a pointer copy distinct from its source for one following use.

    This is intentionally limited to a declared pointer local and either an
    immediate null guard or a single member load.  The alias can change
    register allocation, but it is not a semantic escape hatch and never
    introduces a volatile access or an invented helper.
    """
    lines = text.splitlines(keepends=True)
    types = _pointer_types(text)
    out = []
    occupied = []
    for i, line in enumerate(lines):
        assignment = _ASSIGNMENT.match(line)
        if not assignment or assignment.group("name") not in types:
            continue
        name = assignment.group("name")
        alias = "shape_copy_" + name
        alias = "shape_copy_%s_%d" % (name, i)
        if alias in text:
            continue
        indent = assignment.group("indent")
        alias_line = (f"{indent}{types[name]}{alias} = {name};\n")

        # A pointer copy followed by its own null guard.
        if i + 1 < len(lines):
            guard = _GUARD.match(lines[i + 1])
            if guard and guard.group("name") == name:
                before = line + lines[i + 1]
                after_guard = lines[i + 1].replace(name, alias, 1)
                after = line + alias_line + after_guard
                if text.count(before) == 1:
                    start = text.index(before)
                    end = start + len(before)
                    if any(start < old_end and end > old_start
                           for old_start, old_end in occupied):
                        continue
                    out.append({"before": before, "after": [after],
                                "lever": "copy-lifetime"})
                    occupied.append((start, end))
                    if len(out) >= limit:
                        break
                    continue

        # A pointer copy followed immediately by a member load through it.
        if i + 1 < len(lines):
            next_line = lines[i + 1]
            if re.search(r"\b" + re.escape(name) + r"\s*->", next_line):
                before = line + next_line
                after_line = re.sub(r"\b" + re.escape(name) + r"\s*->",
                                    alias + "->", next_line, count=1)
                after = line + alias_line + after_line
                if text.count(before) == 1:
                    start = text.index(before)
                    end = start + len(before)
                    if any(start < old_end and end > old_start
                           for old_start, old_end in occupied):
                        continue
                    out.append({"before": before, "after": [after],
                                "lever": "copy-lifetime"})
                    occupied.append((start, end))
                    if len(out) >= limit:
                        break
    return out


def store_choices(text, limit=8):
    """Return bounded swaps of adjacent independent scalar field stores."""
    lines = text.splitlines(keepends=True)
    out = []
    occupied = []
    for i in range(len(lines) - 1):
        first, second = _STORE.match(lines[i]), _STORE.match(lines[i + 1])
        if not first or not second or first.group("indent") != second.group("indent"):
            continue
        lhs1, lhs2 = first.group("lhs").strip(), second.group("lhs").strip()
        rhs1, rhs2 = first.group("rhs").strip(), second.group("rhs").strip()
        if lhs1 == lhs2 or not _STORE_RHS.fullmatch(rhs1) or not _STORE_RHS.fullmatch(rhs2):
            continue
        leaf1 = re.split(r"->|\.", lhs1)[-1]
        leaf2 = re.split(r"->|\.", lhs2)[-1]
        if re.search(r"\b" + re.escape(leaf1) + r"\b", rhs2):
            continue
        if re.search(r"\b" + re.escape(leaf2) + r"\b", rhs1):
            continue
        before = lines[i] + lines[i + 1]
        if text.count(before) != 1:
            continue
        start = text.index(before)
        end = start + len(before)
        if any(start < old_end and end > old_start
               for old_start, old_end in occupied):
            continue
        out.append({"before": before, "after": [lines[i + 1] + lines[i]],
                    "lever": "store-order"})
        occupied.append((start, end))
        if len(out) >= limit:
            break
    return out


def loop_choices(text, limit=8):
    """Toggle a semantically equivalent empty-init/increment loop header."""
    out = []
    for line in text.splitlines(keepends=True):
        while_match = _WHILE.match(line)
        if while_match:
            replacement = (f"{while_match.group('indent')}for (; "
                           f"{while_match.group('condition').strip()}; )"
                           f"{while_match.group('tail')}\n")
        else:
            for_match = _FOR_EMPTY.match(line)
            if not for_match:
                continue
            replacement = (f"{for_match.group('indent')}while ("
                           f"{for_match.group('condition').strip()})"
                           f"{for_match.group('tail')}\n")
        if replacement == line or text.count(line) != 1:
            continue
        out.append({"before": line, "after": [replacement], "lever": "loop-header"})
        if len(out) >= limit:
            break
    return out


def branch_choices(text, limit=8):
    """Fold a simple boolean if/return followed by the opposite return."""
    lines = text.splitlines(keepends=True)
    out = []
    for i in range(len(lines) - 1):
        first = _BRANCH.match(lines[i])
        second = _RETURN_BOOL.match(lines[i + 1])
        if not first or not second or first.group("indent") != second.group("indent"):
            continue
        condition = first.group("condition").strip()
        if not condition or text.count(lines[i] + lines[i + 1]) != 1:
            continue
        if first.group("value") == second.group("value"):
            continue
        expression = condition if first.group("value") == "true" else "!(%s)" % condition
        replacement = f"{first.group('indent')}return {expression};\n"
        before = lines[i] + lines[i + 1]
        out.append({"before": before, "after": [replacement], "lever": "branch-return"})
        if len(out) >= limit:
            break
    return out


def constant_choices(text, limit=8):
    """Probe literal boolean-return materialisation without changing a value."""
    lines = text.splitlines(keepends=True)
    out = []
    for i, line in enumerate(lines):
        end = _function_end(lines, i)
        if end is None:
            continue
        balance = 0
        start = None
        for j in range(end, -1, -1):
            balance += lines[j].count("}") - lines[j].count("{")
            if balance == 0:
                start = j
                break
        if start is None or any(re.match(r"^[ \t]*(?:case\b|default\s*:)", item)
                                for item in lines[start:i + 1]):
            continue
        if _unbraced_control(lines, i):
            continue
        result = _RETURN_BOOL.match(line)
        if result and text.count(line) == 1:
            name = "shape_constant_%s_%d" % (result.group("value"), i)
            if name not in text:
                value = "1" if result.group("value") == "true" else "0"
                replacement = (f"{result.group('indent')}unsigned char {name} = {value};\n"
                               f"{result.group('indent')}return {name};\n")
                out.append({"before": line, "after": [replacement],
                            "lever": "constant-materialization"})
                if len(out) >= limit:
                    break
                continue
    return out


def _function_end(lines, start):
    depth = sum(line.count("{") - line.count("}") for line in lines[:start])
    if depth <= 0:
        return None
    for index in range(start, len(lines)):
        depth += lines[index].count("{") - lines[index].count("}")
        if depth == 0:
            return index
    return None


def _unbraced_control(lines, index):
    """Reject two-statement edits under an unbraced control header."""
    previous = index - 1
    while previous >= 0 and not lines[previous].strip():
        previous -= 1
    if previous < 0:
        return False
    if lines[previous].rstrip().endswith((";", "{", "}")):
        return False
    # A multiline condition ends on a line that is not itself an `if` token;
    # its lack of a statement terminator still means the next statement is
    # the unbraced controlled body.
    return True


def frame_choices(text, limit=8):
    """Promote a simple scalar local to a live indexed two-element array."""
    lines = text.splitlines(keepends=True)
    out = []
    for i, line in enumerate(lines):
        declaration = _FRAME_DECL.match(line)
        if not declaration or text.count(line) != 1:
            continue
        if _unbraced_control(lines, i):
            continue
        end = _function_end(lines, i)
        if end is None or end <= i:
            continue
        balance = 0
        start = None
        for j in range(end, -1, -1):
            balance += lines[j].count("}") - lines[j].count("{")
            if balance == 0:
                start = j
                break
        if start is None or any(re.match(r"^[ \t]*(?:case\b|default\s*:)", item)
                                for item in lines[start:end + 1]):
            continue
        name = declaration.group("name")
        if not re.fullmatch(_STORE_RHS, declaration.group("expr").strip()):
            continue
        body = lines[i + 1:end]
        if not any(re.search(r"\b" + re.escape(name) + r"\b", item) for item in body):
            continue
        if any(re.search(r"(?:\.|->)\s*" + re.escape(name) + r"\b", item)
               or re.search(r"\b" + re.escape(name) + r"\s*\[", item)
               or re.search(r"\b(?:int|unsigned int)\s+(?:[*&]\s*)?"
                            + re.escape(name) + r"\b", item)
               or re.search(r"[*&]\s*" + re.escape(name) + r"\b", item)
               or ("//" in item and re.search(r"\b" + re.escape(name) + r"\b", item))
               for item in body):
            continue
        array_name = "shape_frame_" + name + "_%d" % i
        if array_name in text:
            continue
        replacement_lines = [
            f"{declaration.group('indent')}{declaration.group('type')} {array_name}[2];\n",
            f"{declaration.group('indent')}{array_name}[1] = {declaration.group('expr').strip()};\n",
        ]
        before = line + "".join(body)
        after_body = re.sub(r"\b" + re.escape(name) + r"\b",
                            array_name + "[1]", "".join(body))
        after = "".join(replacement_lines) + after_body
        out.append({"before": before, "after": [after], "lever": "frame-array"})
        if len(out) >= limit:
            break
    return out


def _disjoint_choices(text, choices):
    """Keep one stable hypothesis per source range for shape_search."""
    out = []
    occupied = []
    for choice in choices:
        before = choice.get("before", "")
        if not before or text.count(before) != 1:
            continue
        start = text.index(before)
        end = start + len(before)
        if any(start < old_end and end > old_start
               for old_start, old_end in occupied):
            continue
        out.append(choice)
        occupied.append((start, end))
    return out


def choices_for(text, families=("sib", "register", "bool", "test", "copy", "store",
                                "loop", "branch", "constant", "frame"), max_choices=12):
    """Return choices in stable family order for ``shape_search.variants``."""
    out = []
    if "sib" in families:
        out.extend(sib_choices(text, max_choices))
    if "register" in families:
        out.extend(register_choices(text, max_choices))
    if "bool" in families:
        out.extend(bool_choices(text, max_choices))
    if "test" in families:
        out.extend(test_choices(text, max_choices))
    if "copy" in families:
        out.extend(copy_choices(text, max_choices))
    if "store" in families:
        out.extend(store_choices(text, max_choices))
    if "loop" in families:
        out.extend(loop_choices(text, max_choices))
    if "branch" in families:
        out.extend(branch_choices(text, max_choices))
    if "constant" in families:
        out.extend(constant_choices(text, max_choices))
    if "frame" in families:
        out.extend(frame_choices(text, max_choices))
    return _disjoint_choices(text, out)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("source", type=Path)
    ap.add_argument("--families", default="sib,register,bool,test,copy,store,loop,branch,constant,frame")
    ap.add_argument("--max-choices", type=int, default=12)
    args = ap.parse_args()
    if args.max_choices <= 0:
        raise SystemExit("shape_family_levers: --max-choices must be positive")
    text = args.source.read_text(encoding="utf-8-sig")
    choices = choices_for(text, tuple(x.strip() for x in args.families.split(",") if x.strip()),
                         args.max_choices)
    if not choices:
        raise SystemExit("shape_family_levers: no applicable source-level family lever")
    for choice in choices:
        choice.pop("lever", None)
    json.dump(choices, sys.stdout, indent=2)
    print()
    trials = 1
    for choice in choices:
        trials *= 1 + len(choice["after"])
    print(f"[shape_family_levers: {len(choices)} choice(s), {trials} combinations; "
          "shape_search caps at --max-trials]", file=sys.stderr)


if __name__ == "__main__":
    main()
