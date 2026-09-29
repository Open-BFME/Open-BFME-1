#!/usr/bin/env python3
"""Which ledger-backed sources can a header change reach?

Both hooks ran the 40-60 minute full gate for ANY header or shim change, even a
header nothing includes, which made the shared-header work that a linked build
needs (one real header per class instead of private copies) the most expensive
edit in the repository. This bounds the change instead: it walks the #include
graph upward from each changed header and prints the sources that can reach it,
so the hook byte-verifies those and nothing else.

The graph is read from the snapshot being verified -- the index for --staged,
the NEW commit for --range -- never from the working tree, so an unstaged or
uncommitted edit cannot change what is selected.

Under-counting would let a broken TU through, so every doubt widens the set:
  - includes match on file NAME (case-insensitive), never on resolved path, so
    same-named variants in other folders all count;
  - any file a scanned file #includes by name is scanned too, whatever its
    suffix (a .def or .tbl that includes a header carries that edge);
  - a file with a macro include (`#include MACRO`) is treated as including
    every file, changed non-headers included; a `// cl: /FI<name>` forced
    include counts as an include;
  - a directive the line scan cannot read with certainty (a line splice, a
    comment around it, a trigraph, a BOM, a binary-looking file) is re-read
    whole with splices joined and comments blanked; one that still cannot be
    parsed (a malformed operand, UTF-16 text, #pragma include_alias) exits 2;
  - the graph is read from #include text, so a deleted or renamed header's
    includers are still found;
  - a changed .cpp, .c or table that a scanned file #includes by name compiles
    inside that file, so it reaches its includers like a header does;
  - toolchain, vendored-library and STLport changes, or a set larger than
    --limit sources, exit 2: the caller runs the full gate.

  python3 tools/header_dependents.py --staged           # pre-commit
  python3 tools/header_dependents.py --range OLD NEW    # pre-push
exit 0 = the sources to verify, one per line (possibly none); exit 2 = run the
full gate (reason on stderr).
"""
import argparse
import csv
import io
import os
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
HEADER_SUFFIXES = (".h", ".hpp", ".hh", ".hxx", ".inl", ".inc")
SOURCE_SUFFIXES = (".cpp", ".c", ".cc", ".cxx", ".cp", ".c++")
SCANNED_ROOTS = ("game/", "inputs/reference/")
FULL_GATE_ROOTS = ("inputs/toolchains/", "inputs/vendor/")
IGNORED_ROOTS = ("mods/", "worldbuilder/", "targets/worldbuilder/")
LEDGER = "targets/game/reverse/functions.csv"
DIRECTIVE = re.compile(r"^[ \t]*#[ \t]*(?:include|import)\b[ \t]*(.*)$", re.M)
MACRO = re.compile(r"[A-Za-z_]\w*")
FORCED = re.compile(r"[-/]FI[ \t]*\"?([^\s\"]+)")
CL_LINE = re.compile(r"//[ \t]*cl:(.*)$", re.M)
# A line the per-line scan cannot trust: a spliced directive head or include, a
# comment before or inside a directive, a trigraph, an include alias.
DOUBT = re.compile(r"^[ \t]*#[ \t]*\w*[ \t]*\\\s*$|^[ \t]*#[ \t]*(?:include|import)\b.*\\\s*$"
                   r"|\*/[ \t]*#|#[ \t]*/\*|\?\?[=/]|include_alias")
# Lines git grep hands to DIRECTIVE, CL_LINE and DOUBT: one PCRE alternation (0.3 s over
# the tree); git without PCRE takes the ERE pair, whose spliced-head pattern is slow
# alongside the others and so runs apart as a file listing.
GREP_PCRE = r"#\s*(?:include|import)|//\s*cl:|\?\?[=/]|\*/\s*#|#\s*/\*|include_alias|^\s*#\s*\w*\s*\\\s*$"
GREP_ERE = ("#[[:space:]]*(include|import)", "//[[:space:]]*cl:", "\\?\\?[=/]",
            "\\*/[[:space:]]*#", "#[[:space:]]*/\\*", "include_alias")
GREP_ERE_SPLICED_HEAD = "^[[:space:]]*#[[:space:]]*[A-Za-z0-9_]*[[:space:]]*\\\\[[:space:]]*$"
TRIGRAPHS = {"=": "#", "/": "\\", "'": "^", "(": "[", ")": "]", "!": "|", "<": "{", ">": "}", "-": "~"}
# Literals end at a newline, as the compiler's do, so a stray quote cannot hide a comment.
COMMENT_OR_LITERAL = re.compile(r'"(?:\\.|[^"\\\n])*"?|\'(?:\\.|[^\'\\\n])*\'?|/\*[\s\S]*?(?:\*/|\Z)|//[^\n]*')
PRAGMA_ALIAS = re.compile(r"^[ \t]*#[ \t]*pragma\b.*\binclude_alias\b", re.M)


class Widen(Exception):
    """The include graph cannot be bounded with certainty: run the full gate."""


def git(*args):
    result = subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True,
                            encoding="utf-8", errors="replace")
    if result.returncode:
        raise SystemExit(f"header_dependents: git {' '.join(args[:2])} failed: {result.stderr.strip()}")
    return result.stdout


def changed(args):
    if args.staged:
        return git("diff", "--cached", "--name-only", "--no-renames", "--diff-filter=ACMRTD").splitlines()
    return git("diff", "--name-only", "--no-renames", args.range[0], args.range[1]).splitlines()


def snapshot(args):
    """None for the index, else the NEW commit's full SHA."""
    if args.staged:
        return None
    return git("rev-parse", "--verify", "--quiet", f"{args.range[1]}^{{commit}}").strip()


def is_wide(path):
    return path.lower().endswith(HEADER_SUFFIXES) or path.startswith(("inputs/reference/shims/", "inputs/toolchains/"))


def name(path):
    return path.replace("\\", "/").rsplit("/", 1)[-1].lower()


def grep(snap, *args, check=True):
    """git grep over the snapshot's scanned roots: [(path, text after the NUL)], or None
    when it fails and `check` is off."""
    cmd = ["git", "-c", "grep.lineNumber=false", "-c", "grep.column=false", "-c", "color.grep=never",
           "-c", "submodule.recurse=false", "grep", "-z", *args,
           *(["--cached"] if snap is None else [snap]), "--", *SCANNED_ROOTS]
    result = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, encoding="utf-8", errors="replace",
                            env={**os.environ, "LC_ALL": "C"})
    if result.returncode not in (0, 1):
        if not check:
            return None
        raise SystemExit(f"header_dependents: git grep failed: {result.stderr.strip()}")
    prefix = "" if snap is None else f"{snap}:"
    records = []
    for record in result.stdout.split("\n") if "-l" not in args else result.stdout.split("\0"):
        if not record:
            continue
        path, _, text = record.partition("\0")
        records.append((path[len(prefix):] if path.startswith(prefix) else path, text))
    return records


def blobs(snap, paths):
    """{path: bytes} for the snapshot's copy of each path."""
    spec = ":" if snap is None else f"{snap}:"
    result = subprocess.run(["git", "cat-file", "--batch"], cwd=ROOT, capture_output=True,
                            input="".join(f"{spec}{p}\n" for p in paths).encode("utf-8"))
    if result.returncode:
        raise SystemExit(f"header_dependents: git cat-file failed: {result.stderr.decode(errors='replace').strip()}")
    out, pos, found = result.stdout, 0, {}
    for path in paths:
        end = out.index(b"\n", pos)
        header = out[pos:end].split()
        pos = end + 1
        if len(header) != 3:
            raise Widen(f"{path} is unreadable in the snapshot")
        size = int(header[2])
        found[path] = out[pos:pos + size]
        pos += size + 1
    return found


def operand_target(operand, path):
    """('name', literal) or ('macro', None) for one #include operand, else Widen."""
    operand = operand.strip()
    for open_, close in (('"', '"'), ("<", ">")):
        if operand.startswith(open_):
            end = operand.find(close, 1)
            if end > 1:
                return "name", operand[1:end]
            raise Widen(f"{path}: unparseable #include {operand!r}")
    if MACRO.match(operand):
        return "macro", None
    raise Widen(f"{path}: unparseable #include {operand!r}")


def forced_names(text):
    return {name(forced) for line in CL_LINE.findall(text) for forced in FORCED.findall(line)}


def read_whole(path, data):
    """(included names, has a macro include) from a whole file, splices joined and comments blanked."""
    if data[:2] in (b"\xff\xfe", b"\xfe\xff") or data.count(b"\0") * 4 > len(data):
        raise Widen(f"{path} looks like UTF-16/32 text")
    text = data.decode("latin-1")
    text = text[3:] if text.startswith("\xef\xbb\xbf") else text
    names, macro = forced_names(text), False
    text = re.sub(r"\?\?([=/'()!<>-])", lambda m: TRIGRAPHS[m.group(1)], text)
    # MSVC splices only backslash-newline; also read backslash-blanks-newline as a
    # splice, and keep the union: a spurious edge only widens the set.
    for spliced in {re.sub(r"\\\r?\n", "", text), re.sub(r"\\[ \t\f\v]*\r?\n", "", text)}:
        body = COMMENT_OR_LITERAL.sub(
            lambda m: re.sub(r"[^\n]", " ", m.group()) if m.group().startswith("/") else m.group(), spliced)
        if PRAGMA_ALIAS.search(body):
            raise Widen(f"{path} has #pragma include_alias")
        for operand in DIRECTIVE.findall(body):
            kind, literal = operand_target(operand, path)
            if kind == "macro":
                macro = True
            else:
                names.add(name(literal))
    return names, macro


def scan(snap):
    """({scanned path: {included name}}, {scanned paths with a macro include}) at the snapshot.

    One git grep reads every include-like line; only the few files it cannot
    read with certainty are fetched whole."""
    edges, macro, doubt = defaultdict(set), set(), set()
    lines = grep(snap, "-I", "-P", "-e", GREP_PCRE, check=False)
    if lines is None:
        lines = grep(snap, "-I", "-E", *(arg for p in GREP_ERE for arg in ("-e", p)))
        doubt |= {p for p, _ in grep(snap, "-l", "-I", "-E", "-e", GREP_ERE_SPLICED_HEAD)}
    for path, line in lines:
        if DOUBT.search(line):
            doubt.add(path)
        directive = DIRECTIVE.match(line.lstrip("\ufeff"))
        if directive:
            try:
                kind, literal = operand_target(directive.group(1), path)
            except Widen:
                doubt.add(path)
            else:
                if kind == "macro":
                    macro.add(path)
                else:
                    edges[path].add(name(literal))
        edges[path] |= forced_names(line)
    # git grep -I skips files it takes for binary: read those whole as well
    everything = {p for p, _ in grep(snap, "-l", "-e", "")}
    doubt |= everything - {p for p, _ in grep(snap, "-l", "-I", "-e", "")}
    names = set().union(*edges.values())

    def scanned(path):
        return path.lower().endswith(HEADER_SUFFIXES + SOURCE_SUFFIXES) or name(path) in names

    pending = sorted(p for p in doubt if scanned(p))
    while pending:
        for path, data in blobs(snap, pending).items():
            found, has_macro = read_whole(path, data)
            edges[path] |= found
            names |= found
            if has_macro:
                macro.add(path)
        doubt -= set(pending)
        pending = sorted(p for p in doubt if scanned(p))
    edges = {p: e for p, e in edges.items() if scanned(p)}
    return edges, {p for p in macro if scanned(p)}


def ledger_sources(snap):
    spec = ":" if snap is None else f"{snap}:"
    return {row[4] for row in csv.reader(io.StringIO(git("show", f"{spec}{LEDGER}"), newline=""))
            if len(row) > 4}


def graph(edges):
    """{included name: {including path}}."""
    includers = defaultdict(set)
    for path, included in edges.items():
        for literal in included:
            includers[literal].add(path)
    return includers


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
            # a macro include could name any file, so it may reach this one
            users |= macro
            macro_spread = True
        for path in users:
            if path in reached:
                continue
            reached.add(path)
            frontier.add(name(path))  # a source can be #included as well
    return reached


def select(args):
    paths = [p for p in changed(args) if not p.startswith(IGNORED_ROOTS)]
    wide = [p for p in paths if is_wide(p)]
    others = [p for p in paths if not is_wide(p) and p.startswith(("game/", "inputs/"))]
    if not wide and not others:
        return 0, [], 0
    snap = snapshot(args)
    edges, macro = scan(snap)
    names = set().union(*edges.values())
    # a macro include may name any changed file, whatever its suffix
    included = [p for p in others if macro or name(p) in names]
    roots = wide + included
    if not roots:
        return 0, [], 0
    blocked = [p for p in roots if p.startswith(FULL_GATE_ROOTS) or "stlport" in p.lower()]
    if blocked:
        raise Widen(f"{blocked[0]} is toolchain/vendored/STLport")
    rows = ledger_sources(snap)
    reached = dependents(roots, graph(edges), macro)
    # a changed file that is itself a ledger source (a shim .cpp) is verified too
    sources = sorted({p for p in reached if p in rows} | {p for p in wide if p in rows})
    return len(wide), sources, len(included)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    ap.add_argument("--limit", type=int, default=2000,
                    help="more dependent sources than this runs the full gate instead (default 2000)")
    args = ap.parse_args(argv)
    sys.stdout.reconfigure(newline="\n")  # the hooks read this with mapfile
    try:
        wide, sources, included = select(args)
    except Widen as why:
        print(f"header_dependents: {why}: full gate", file=sys.stderr)
        return 2
    if not wide and not included:
        return 0
    if len(sources) > args.limit:
        print(f"header_dependents: {len(sources):,} dependent sources exceed --limit {args.limit:,}: full gate",
              file=sys.stderr)
        return 2
    print(f"header_dependents: {wide} changed header(s) and {included} included file(s) "
          f"reach {len(sources):,} ledger source(s)",
          file=sys.stderr)
    for path in sources:
        print(path)
    return 0


if __name__ == "__main__":
    sys.exit(main())
