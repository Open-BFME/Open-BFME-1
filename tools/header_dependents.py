#!/usr/bin/env python3
"""Which ledger-backed sources can a header change reach?

Both hooks ran the 40-60 minute full gate for ANY header or shim change, even a
header nothing includes, which made the shared-header work that a linked build
needs (one real header per class instead of private copies) the most expensive
edit in the repository. This bounds the change instead: it walks the #include
graph upward from each changed header and prints the sources that can reach it,
so the hook byte-verifies those and nothing else.

Under-counting would let a broken TU through, so every doubt widens the set:
  - includes match on file NAME (case-insensitive), never on resolved path, so
    same-named variants in other folders all count;
  - a file with a macro include (`#include MACRO`) is treated as including
    every header; a `// cl: /FI<name>` forced include counts as an include;
  - the graph is read from #include text, so a deleted or renamed header's
    includers are still found;
  - toolchain, vendored-library and STLport changes, or a set larger than
    --limit sources, exit 2: the caller runs the full gate.

  python3 tools/header_dependents.py --staged           # pre-commit
  python3 tools/header_dependents.py --range OLD NEW    # pre-push
exit 0 = the sources to verify, one per line (possibly none); exit 2 = run the
full gate (reason on stderr).
"""
import argparse
import csv
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
HEADER_SUFFIXES = (".h", ".hpp", ".hh", ".hxx", ".inl", ".inc")
SOURCE_SUFFIXES = (".cpp", ".c")
SCANNED_ROOTS = ("game/", "inputs/reference/")
FULL_GATE_ROOTS = ("inputs/toolchains/", "inputs/vendor/")
IGNORED_ROOTS = ("mods/", "worldbuilder/", "targets/worldbuilder/")
INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]*(?:[<"]([^">]+)[">]|([A-Za-z_]\w*))', re.M)
FORCED = re.compile(r"[-/]FI\"?([^\s\"]+)")
CL_LINE = re.compile(r"^//\s*cl:(.*)$", re.M)


def git(*args):
    result = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True,
                            encoding="utf-8", errors="replace")
    if result.returncode:
        raise SystemExit(f"header_dependents: git {' '.join(args[:2])} failed: {result.stderr.strip()}")
    return result.stdout


def changed(args):
    if args.staged:
        return git("diff", "--cached", "--name-only", "--diff-filter=ACMRTD").splitlines()
    return git("diff", "--name-only", args.range[0], args.range[1]).splitlines()


def is_wide(path):
    return path.lower().endswith(HEADER_SUFFIXES) or path.startswith(("inputs/reference/shims/", "inputs/toolchains/"))


def name(path):
    return path.replace("\\", "/").rsplit("/", 1)[-1].lower()


def ledger_sources():
    with (ROOT / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        return {row[4] for row in csv.reader(handle) if len(row) > 4}


def graph():
    """({included name: {including path}}, {paths with a macro include})."""
    includers = defaultdict(set)
    macro = set()
    for path in git("ls-files", *SCANNED_ROOTS).splitlines():
        if not path.lower().endswith(HEADER_SUFFIXES + SOURCE_SUFFIXES):
            continue
        try:
            text = (ROOT / path).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for literal, symbolic in INCLUDE.findall(text):
            if symbolic:
                macro.add(path)
            else:
                includers[name(literal)].add(path)
        for line in CL_LINE.findall(text):
            for forced in FORCED.findall(line):
                includers[name(forced)].add(path)
    return includers, macro


def dependents(headers, includers, macro):
    """Every scanned file that can reach one of `headers` (names), transitively."""
    frontier = {name(h) for h in headers}
    seen_names, reached = set(), set()
    macro_spread = False
    while frontier:
        current = frontier.pop()
        if current in seen_names:
            continue
        seen_names.add(current)
        users = set(includers.get(current, ()))
        if not macro_spread:
            # a macro include could name any header, so it may reach this one
            users |= macro
            macro_spread = True
        for path in users:
            if path in reached:
                continue
            reached.add(path)
            if path.lower().endswith(HEADER_SUFFIXES):
                frontier.add(name(path))
    return reached


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    ap.add_argument("--limit", type=int, default=2000,
                    help="more dependent sources than this runs the full gate instead (default 2000)")
    args = ap.parse_args(argv)
    sys.stdout.reconfigure(newline="\n")  # the hooks read this with mapfile
    wide = [p for p in changed(args) if is_wide(p) and not p.startswith(IGNORED_ROOTS)]
    if not wide:
        return 0
    blocked = [p for p in wide if p.startswith(FULL_GATE_ROOTS) or "stlport" in p.lower()]
    if blocked:
        print(f"header_dependents: {blocked[0]} is toolchain/vendored/STLport: full gate", file=sys.stderr)
        return 2
    includers, macro = graph()
    rows = ledger_sources()
    reached = dependents(wide, includers, macro)
    sources = sorted(p for p in reached if p in rows and p.lower().endswith(SOURCE_SUFFIXES))
    # a changed file that is itself a ledger source (a shim .cpp) is verified too
    sources = sorted(set(sources) | {p for p in wide if p in rows})
    if len(sources) > args.limit:
        print(f"header_dependents: {len(sources):,} dependent sources exceed --limit {args.limit:,}: full gate",
              file=sys.stderr)
        return 2
    print(f"header_dependents: {len(wide)} changed header(s) reach {len(sources):,} ledger source(s)",
          file=sys.stderr)
    for path in sources:
        print(path)
    return 0


if __name__ == "__main__":
    sys.exit(main())
