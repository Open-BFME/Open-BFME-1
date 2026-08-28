#!/usr/bin/env python3
"""Link the two halves of a split function.

A function often exists twice in the tree: a readable ported body carrying a
`present-unmatched` marker, and a byte-exact reconstruction that holds the
ledger row. Neither file mentions the other, so a reader of either half cannot
find the one that answers their question.

This writes that pointer into both halves as a comment. Comments emit no bytes,
so `./build.sh` is unaffected; re-running rewrites the same lines, so the links
cannot go stale while this is run.

    tools/crosslink.py            # write the links
    tools/crosslink.py --check    # exit 1 if any link is missing or stale
"""

import bisect
import csv
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGER = ROOT / "reverse" / "functions.csv"
SOURCE_SUFFIXES = (".cpp", ".h")
SKIP_DIRS = ("gen_asm", "gen_small", "masm_dumps")

MARKER_RE = re.compile(r"^(\s*)//\s*(\?\S+)\s+present-unmatched\s*$")
# A TU-local facade restates a class layout privately, so the reader gets offsets
# and no names. Point at the upstream declaration that has the names.
CLASS_RE = re.compile(r"^([ \t]*)(?:class|struct)\s+(\w+)\s*(.*)$")
CLASS_RE_MULTI = re.compile(r"\b(?:class|struct)\s+(?:[A-Z_]+\s+)?(\w+)\s*(?::[^;{]{0,200})?\{", re.S)
# A definition's `{` usually sits on the line after the head, sometimes after a
# base-class clause. Scan a short way ahead, and stop at `;` -- that is a forward
# declaration, which has no layout to point at.
DEFINITION_LOOKAHEAD = 4
UPSTREAM = ROOT / "reference" / "CnC_Generals_Zero_Hour" / "GeneralsMD" / "Code"
FORWARD = "// byte-exact reconstruction: "
REVERSE = "// readable body of "
LAYOUT = "// upstream layout: "
OWNED = (FORWARD, REVERSE, LAYOUT)
# `// cl:` and `// stlport` are read from the first 2048 bytes of a source, so a
# line inserted above either one can push it out of that window and silently
# change how the file compiles. Never insert before a marker inside the window.
HEAD_WINDOW = 2048
HEAD_MARKERS = ("// cl:", "// stlport")


def writable(relative):
    """A C++ source this tool may add a comment to. Excludes the pristine
    vendored tree, the generated directories, and MASM dumps -- a ledger row can
    name a .asm file, where `//` is not a comment and an insert breaks the
    assemble."""
    path = Path(relative)
    return (
        path.parts[:1] == ("Code",)
        and path.suffix in SOURCE_SUFFIXES
        and not any(d in path.parts for d in SKIP_DIRS)
    )


def sources():
    for path in sorted((ROOT / "Code").rglob("*")):
        if writable(path.relative_to(ROOT).as_posix()):
            yield path


def read(path):
    """Read without newline translation: 265 sources under Code/ are CRLF or
    mixed, and normalising them rewrites the whole file instead of one line."""
    with path.open("r", encoding="utf-8", errors="surrogateescape", newline="") as handle:
        return handle.read()


def write(path, text):
    with path.open("w", encoding="utf-8", errors="surrogateescape", newline="") as handle:
        handle.write(text)


def ledger_index():
    """mangled name -> set of source paths of its matched rows."""
    index = {}
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row["status"] == "matched" and row["source"]:
                index.setdefault(row["name"], set()).add(row["source"])
    return index


def resolve(key, index, names):
    """Sources matching a marker key. A key ending in `@@` lost its signature
    when it was written, so it is a prefix over the ledger's sorted names."""
    if not key.endswith("@@"):
        return set(index.get(key, ()))
    found = set()
    position = bisect.bisect_left(names, key)
    while position < len(names) and names[position].startswith(key):
        found |= index[names[position]]
        position += 1
    return found


def upstream_headers():
    """Upstream class name -> its declaring header, for names declared in
    exactly one. An ambiguous name would point the reader at a coin flip."""
    seen = {}
    for path in UPSTREAM.rglob("*.h"):
        relative = path.relative_to(ROOT).as_posix()
        for match in CLASS_RE_MULTI.finditer(read(path)):
            seen.setdefault(match.group(1), set()).add(relative)
    return {name: paths.pop() for name, paths in seen.items() if len(paths) == 1}


def class_definition(lines, number):
    """(indent, name) when this line opens a class/struct definition body."""
    match = CLASS_RE.match(lines[number])
    if not match:
        return None
    tail = match.group(3)
    for offset in range(DEFINITION_LOOKAHEAD):
        if ";" in tail:
            return None
        if "{" in tail:
            return match.group(1), match.group(2)
        if number + offset + 1 >= len(lines):
            return None
        tail = lines[number + offset + 1]
    return None


def head_floor(lines):
    """First line index that may be written above without displacing a marker."""
    floor, offset = 0, 0
    for number, line in enumerate(lines):
        if offset >= HEAD_WINDOW:
            break
        if line.startswith(HEAD_MARKERS):
            floor = number + 1
        # Some sources carry Latin-1 bytes (a © in an EA banner) that survive the
        # read as surrogates; plain utf-8 encoding of those raises.
        offset += len(line.encode("utf-8", "surrogateescape")) + 1
    return floor


def rewrite(path, forward, reverse, headers):
    """Drop every link this tool owns, re-insert the ones that belong. Returns
    the new text, or None when the file is already correct."""
    original = read(path)
    # Lines keep their own trailing \r, so joining reproduces the file byte for
    # byte; only an inserted line needs the file's dominant terminator.
    lines = original.split("\n")
    eol = "\r" if original.count("\r\n") * 2 > original.count("\n") else ""
    kept = [line for line in lines if not line.lstrip().startswith(OWNED)]

    floor = head_floor(kept)
    out = []
    for number, line in enumerate(kept):
        klass = class_definition(kept, number)
        # 40 class declarations sit inside a line-continued macro; a comment
        # inserted above one ends the continuation and breaks the macro.
        continued = number and kept[number - 1].rstrip().endswith("\\")
        if klass and number >= floor and not continued and klass[1] in headers:
            out.append(klass[0] + LAYOUT + headers[klass[1]] + eol)
        # ABOVE the marker, never below it: find_declared_unmatched.py pairs a
        # `present-unmatched` marker with the definition on the next line, and
        # clears the pending marker on any other comment. A link written between
        # the two unexcuses the definition and fails the commit gate.
        marker = MARKER_RE.match(line)
        if marker and marker.group(2) in forward:
            out.append(marker.group(1) + FORWARD + forward[marker.group(2)] + eol)
        out.append(line)

    if reverse:
        at = head_floor(out)
        out[at:at] = [f"{REVERSE}{name}: {source}{eol}" for name, source in sorted(reverse.items())]

    text = "\n".join(out)
    return None if text == original else text


def main():
    check = "--check" in sys.argv[1:]
    index = ledger_index()
    names = sorted(index)
    headers = upstream_headers()

    # Pass 1: every marker that resolves to exactly one other file.
    links = []
    skipped = {"unmatched": 0, "ambiguous": 0, "same-file": 0}
    for path in sources():
        relative = path.relative_to(ROOT).as_posix()
        for line in read(path).split("\n"):
            marker = MARKER_RE.match(line)
            if not marker:
                continue
            matched = resolve(marker.group(2), index, names)
            targets = matched - {relative}
            if not targets:
                skipped["same-file" if matched else "unmatched"] += 1
            elif len(targets) > 1:
                skipped["ambiguous"] += 1
            else:
                links.append((relative, marker.group(2), targets.pop()))

    # Pass 2: group both directions per file, then write each file once.
    forward, reverse = {}, {}
    for holder, name, target in links:
        forward.setdefault(holder, {})[name] = target
        if writable(target):
            reverse.setdefault(target, {})[name] = holder

    # Every source is visited: a layout link can belong to a file holding no
    # split-body link at all.
    changed, layouts = [], 0
    for path in sources():
        relative = path.relative_to(ROOT).as_posix()
        text = rewrite(path, forward.get(relative, {}), reverse.get(relative, {}), headers)
        settled = read(path) if text is None else text
        layouts += sum(1 for line in settled.split("\n") if line.lstrip().startswith(LAYOUT))
        if text is None:
            continue
        changed.append(relative)
        if not check:
            write(path, text)

    print(f"split-body links {len(links)} | upstream-layout links {layouts}")
    print(f"skipped: {skipped['unmatched']} no matched row, "
          f"{skipped['ambiguous']} ambiguous, {skipped['same-file']} row in same file")
    print(f"{'stale' if check else 'written'}: {len(changed)} files")
    if check and changed:
        for relative in changed[:10]:
            print(f"  {relative}")
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
