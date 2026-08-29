#!/usr/bin/env python3
"""List functions defined in source files that are not yet in functions.csv."""

import csv
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = ROOT / "src"
FUNCTIONS_CSV = ROOT / "reverse" / "functions.csv"
CLAIMS_WHITELIST = ROOT / "reverse" / "unclaimed_sources_whitelist.txt"

# `// <label> present-unmatched` / `// <label> absent-from-retail` definition markers
UNMATCHED_MARKER_RE = re.compile(
    r"^\s*//\s*(\S+)\s+(present-unmatched|absent-from-retail)\b", re.MULTILINE
)


def load_claims_whitelist():
    if not CLAIMS_WHITELIST.exists():
        return set()
    return {
        line.strip()
        for line in CLAIMS_WHITELIST.read_text(encoding="utf-8").splitlines()
        if line.strip() and not line.lstrip().startswith("#")
    }

# MSVC operator mangling codes for common operators.
OPERATOR_CODES = {
    "operator=": "??4",
    "operator==": "??8",
    "operator!=": "??9",
    "operator+": "??H",
    "operator-": "??G",
    "operator*": "??D",
    "operator/": "??K",
    "operator+=": "??Y",
    "operator-=": "??Z",
    "operator*=": "??X",
    "operator/=": "??_0",
    "operator<<": "??6",
    "operator>>": "??5",
    "operator[]": "??A",
    "operator()": "??R",
    "operator~": "??1",  # destructor is also ??1; handled separately
}


def git_show(path: Path):
    result = subprocess.run(
        ["git", "show", f":{path.as_posix()}"],
        cwd=ROOT,
        stdout=subprocess.PIPE,
        stderr=subprocess.DEVNULL,
        text=True,
    )
    if result.returncode != 0:
        return None
    return result.stdout


def read_function_names(path: Path, staged: bool):
    text = git_show(path.relative_to(ROOT)) if staged else None
    if text is None:
        text = path.read_text(encoding="utf-8")
    declared = set()
    matched = set()
    matched_by_source = {}
    matched_sources = {}
    for row in csv.DictReader(text.splitlines()):
        declared.add(row["name"])
        if row["status"] == "matched":
            matched.add(row["name"])
            matched_by_source[row["source"]] = matched_by_source.get(row["source"], 0) + 1
            matched_sources.setdefault(row["name"], set()).add(row["source"])
    return declared, matched, matched_by_source, matched_sources


def mangle_method(class_name: str, method_name: str) -> str:
    """Return a rough MSVC mangled-name substring to search for.

    Constructors use ??0, destructors use ??1, operator= uses ??4,
    and ordinary methods use ?name@Class@Namespace@@.
    class_name may be qualified (e.g. "FXParticleSystem::ButterflyDrawModuleInfo").
    """
    parts = class_name.split("::")
    if method_name == parts[-1]:
        prefix = "??0"
    elif method_name == f"~{parts[-1]}":
        prefix = "??1"
    elif method_name in OPERATOR_CODES:
        prefix = OPERATOR_CODES[method_name]
    else:
        prefix = f"?{method_name}"
    mangled_class = "@".join(reversed(parts))
    # Constructors, destructors and operators attach directly to the class name;
    # ordinary methods are separated from the class by an @.
    if prefix.startswith("?") and not prefix.startswith("??"):
        return f"{prefix}@{mangled_class}@@"
    return f"{prefix}{mangled_class}@@"


def find_defined_functions(text: str):
    # Match definitions like:
    #   ReturnType ClassName::methodName(
    #   Namespace::ClassName::methodName(
    #   ClassName::ClassName(
    #   ClassName::~ClassName(
    definition_pattern = re.compile(
        r"^[\w:&*~\s]*?((?:\w+::)*\w+)::(operator[\s=\+\-\*/\[\]\(\)<>!]+|\~?\w+)\s*\(",
        re.MULTILINE,
    )
    namespace_pattern = re.compile(r"\bnamespace\s+(\w+)\s*\{")

    results = set()
    symbol_comment = None
    # Stack of (namespace_name, brace_depth_at_open). Anonymous namespaces use "".
    namespace_stack = []
    brace_depth = 0

    in_macro = False
    # splitlines() breaks on a LONE carriage return as well as on CRLF, so a
    # file written with doubled carriage returns (CR CR LF -- what a text-mode
    # write over content that already ended in CRLF produces) yields a PHANTOM
    # EMPTY LINE after every real one. An empty line does not end in a
    # backslash, so it silently clears in_macro and the remainder of the macro
    # body is then read as ordinary code. Fourteen such files made this checker
    # report a class called NAME and fail a commit. Normalise first: the parse
    # below cares about lines, not about how they were terminated.
    for line in text.replace("\r\n", "\n").replace("\r", "\n").split("\n"):
        stripped = line.strip()
        # A function definition written inside a #define body is not a
        # definition -- it is macro text, and the identifiers in it are
        # parameters. FunctorBindConstructors.cpp generates 82 constructors from
        # one macro whose body reads `NAME::NAME( ... )`, and this checker read
        # that literally and failed the commit for a class called NAME. Track
        # backslash continuations and skip the whole macro body; the functions
        # the macro EXPANDS to are declared in the ledger under their real names.
        was_macro = in_macro
        if stripped.startswith("#define"):
            in_macro = line.rstrip().endswith("\\")
        elif in_macro:
            in_macro = line.rstrip().endswith("\\")
        if was_macro or stripped.startswith("#define"):
            continue
        # A MEMBER-INITIALISER LIST is not a definition. A constructor written
        #     Derived::Derived(const Derived &other)
        #         : std::exception(other)
        # puts `std::exception(other)` on its own line, which matches the same
        # Qualified::name( shape a definition has -- so the checker reported a
        # function called `std::exception` and failed the commit. Initialiser
        # entries always begin with the ':' that opens the list or the ',' that
        # continues it, and a real definition never starts a line with either.
        if stripped.startswith((":", ",")) and not stripped.startswith("::"):
            continue
        if stripped.startswith("// ?"):
            # Only a real ANNOTATION may bind to the next definition. Two forms
            # exist in this tree: a bare mangled name (3305 of them), and a name
            # followed by present-unmatched / absent-from-retail (11104). A third
            # thing also starts with "// ?" -- ordinary PROSE that happens to open
            # with a mangled name, 109 of those, e.g.
            #   // ??_GCrateTemplate 0x0037A2F0 -> 0x0002FC70 -> 0x00379EC0.
            # Binding prose to the following definition made this checker report
            # CrateTemplate::~CrateTemplate as undeclared when its row exists and
            # matches, failing a commit for a correctly declared destructor. Prose
            # is now ignored rather than captured, and the pending annotation is
            # cleared so a stale one cannot leak past it.
            candidate = stripped[3:].strip()
            parts = candidate.split()
            if len(parts) == 1 or (len(parts) >= 2 and parts[1] in
                                   ("present-unmatched", "absent-from-retail")):
                symbol_comment = candidate
            else:
                symbol_comment = None
            continue
        is_namespace_line = stripped.startswith("namespace ") or stripped.startswith("namespace\t") or stripped.startswith("namespace {")

        open_count = line.count("{")
        close_count = line.count("}")

        if is_namespace_line:
            match = namespace_pattern.search(line)
            ns_name = match.group(1) if match else ""
            # The namespace opens at the next unmatched brace depth.
            namespace_stack.append((ns_name, brace_depth + 1))

        brace_depth += open_count - close_count

        # Close any namespaces whose opening brace has now been matched.
        while namespace_stack and namespace_stack[-1][1] > brace_depth:
            namespace_stack.pop()

        # a definition's signature line never ends with ';' — that's a call
        # statement or prototype (e.g. `BASECLASS::Read(buffer, size);`)
        if stripped.endswith(";"):
            match = None
        else:
            match = definition_pattern.match(line)
        if match:
            class_name = match.group(1)
            method_name = match.group(2)
            if method_name.startswith("operator"):
                # normalize "operator ()" / "operator() " to "operator()"
                method_name = "operator" + re.sub(r"\s+", "", method_name[len("operator"):])
            if namespace_stack and "::" not in class_name:
                # Filter out anonymous namespace entries.
                ns_parts = [ns for ns, _ in namespace_stack if ns]
                class_name = "::".join(ns_parts + [class_name])
            results.add((class_name, method_name, symbol_comment))
            symbol_comment = None
    return results


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("paths", nargs="*", help="source files to inspect; defaults to every src/*.cpp")
    parser.add_argument("--fail", action="store_true", help="exit non-zero when unmatched functions are found")
    parser.add_argument("--staged", action="store_true", help="read paths from the git index")
    args = parser.parse_args()

    declared, matched, matched_by_source, matched_sources = read_function_names(FUNCTIONS_CSV, args.staged)
    whitelist = load_claims_whitelist()

    unmatched = []
    violations = []
    source_paths = [ROOT / path for path in args.paths] if args.paths else sorted(SRC_DIR.rglob("*.cpp"))
    for source_path in source_paths:
        if source_path.suffix != ".cpp":
            continue
        rel_path = source_path.relative_to(ROOT)
        if args.staged:
            text = git_show(rel_path)
            if text is None:
                continue
        else:
            text = source_path.read_text(encoding="utf-8")

        # Claims gate: a source file with ZERO byte-verified rows is not progress —
        # a wall of present-unmatched markers must not be committable as if it were.
        marker_labels = UNMATCHED_MARKER_RE.findall(text)
        file_matched = matched_by_source.get(rel_path.as_posix(), 0)
        if file_matched == 0 and rel_path.as_posix() not in whitelist:
            violations.append(
                f"{rel_path}: ZERO matched functions.csv rows — match at least one "
                f"function before committing this file, or whitelist it with a reason "
                f"(reverse/unclaimed_sources_whitelist.txt)"
            )
        own_names = {n for n, srcs in matched_sources.items()
                     if rel_path.as_posix() in srcs}
        label_counts = {}
        for label, _m in marker_labels:
            label_counts[label] = label_counts.get(label, 0) + 1
        for label, marker in marker_labels:
            # matched from ANOTHER file is correct bookkeeping (asm-whale scaffolds
            # claim symbols the verbatim ZH copy also defines); matched from THIS
            # file means the marker is stale
            if rel_path.as_posix() not in matched_sources.get(label, ()):
                # An abbreviated label -- `??0OutputStream@@` standing in for
                # `??0OutputStream@DebugIOFlat@@AAE@PBDI@Z` -- never equals a
                # ledger name, so the exact test above cannot fire. Every stale
                # marker in this tree is of that form, which is exactly why this
                # check had never reported one. Resolve by prefix instead, but
                # only when the answer is unambiguous: one marker carrying the
                # label, and one matched row it could mean. Overloads share an
                # abbreviated label -- ?isPlayer@GameSlot@@ appears three times
                # in GameInfo.cpp -- and claiming one says nothing about the
                # others, so a count mismatch is not evidence about any of them.
                key = label[:-2] if label.endswith("@@") else label
                cand = [n for n in own_names if n.startswith(key + "@")]
                if len(cand) != 1 or label_counts[label] != 1:
                    continue
                label = cand[0]
            if rel_path.as_posix() in matched_sources.get(label, ()):
                violations.append(
                    f"{rel_path}: {label} is matched in functions.csv from this file but "
                    f"still marked {marker} (stale annotation — remove the marker)"
                )
        if args.paths and marker_labels:
            print(
                f"note: {rel_path}: {file_matched} matched row(s), "
                f"{len(marker_labels)} unclaimed definition(s)"
            )

        for class_name, method_name, symbol_name in find_defined_functions(text):
            if symbol_name:
                # `// ?<mangled> absent-from-retail` marks a definition kept only to
                # force emission/instantiation of other matched functions; the retail
                # binary dead-stripped it, so there is no address for a CSV row.
                parts = symbol_name.split()
                if len(parts) >= 2 and parts[1] in ("absent-from-retail", "present-unmatched"):
                    # absent-from-retail: definition kept only to force emission of
                    # matched siblings; the retail binary dead-stripped it.
                    # present-unmatched: the function exists in retail but its bytes
                    # or address are not yet pinned; kept because trimming it would
                    # change inlining of matched functions in this TU.
                    continue
                if symbol_name in declared:
                    continue
                unmatched.append((rel_path, class_name, method_name))
                continue

            needle = mangle_method(class_name, method_name)
            # The namespace tracker below loses its stack in very large files, so
            # class_name can arrive unqualified for a symbol whose real decorated
            # name carries a namespace: ??4EmissionVolumeInfo@FXParticleSystem@@
            # against a needle of ??4EmissionVolumeInfo@@. Trimming one '@' off
            # the terminator lets the qualified form match, and cannot widen the
            # class itself -- the trailing '@' still has to follow it exactly.
            open_needle = needle[:-1]
            # Constructors/destructors match a prefix; ordinary methods match a substring.
            if needle.startswith("??0") or needle.startswith("??1"):
                if any(name.startswith(open_needle) for name in matched):
                    continue
            else:
                if any(open_needle in name for name in matched):
                    continue
            unmatched.append((rel_path, class_name, method_name))

    if violations:
        for violation in violations:
            print(violation)
    if not unmatched and not violations:
        print("All defined functions are already matched.")
        return

    for rel_path, class_name, method_name in unmatched:
        print(f"{rel_path}: {class_name}::{method_name}")
    if args.fail:
        sys.exit(1)


if __name__ == "__main__":
    main()
