#!/usr/bin/env python3
"""Generate bounded C++ choices for recurring non-EH codegen residues.

This module is deliberately a choice generator, not a compiler or an
acceptance check.  ``choices_for(text)`` returns the JSON shape consumed by
``shape_search.py``.  The transformations are intentionally narrow:

* ``sib`` reverses one independent integer addition at a time;
* ``register`` swaps adjacent, independent local definitions;
* ``bool`` materialises a call result before negating it;
* ``test`` reverses the operands of a simple bit-test condition;
* ``copy`` keeps a pointer alias live through its next guard or member load.

The first two are useful probes for the hard-lane SIB and register-order
families.  A generated alternative is only a hypothesis: ``probe.py`` and the
ordinary byte gate remain the judge.  In particular, the current SIB family
has repeatedly shown a compiler-internal base/index choice even after these
source alternatives, so this tool must not be used to justify a guessed name
or an assembly fallback.

Usage::

    python3 tools/shape_family_levers.py SOURCE.cpp \
        --families sib,register,bool,test,copy > choices.json
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
    r"^(?P<indent>[ \t]+)(?P<type>[A-Za-z_]\w*(?:\s*(?:::|->)\s*[A-Za-z_]\w*)*"
    r"\s*\*)\s*(?P<name>[A-Za-z_]\w*)\s*(?:=\s*[^;]+)?;[ \t]*$"
)
_ASSIGNMENT = re.compile(
    r"^(?P<indent>[ \t]+)(?P<name>[A-Za-z_]\w*)\s*=\s*(?P<rhs>[^;]+);[ \t]*$"
)
_GUARD = re.compile(
    r"^(?P<indent>[ \t]*)if\s*\(\s*(?P<name>[A-Za-z_]\w*)"
    r"\s*(?P<comparison>!=\s*0)?\s*\)[ \t]*(?:\{)?[ \t]*$"
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
    types = {}
    for line in text.splitlines():
        match = _POINTER_DECL.match(line)
        if match:
            types[match.group("name")] = match.group("type").strip()
    return types


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


def choices_for(text, families=("sib", "register", "bool", "test", "copy"), max_choices=12):
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
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("source", type=Path)
    ap.add_argument("--families", default="sib,register,bool,test,copy")
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
