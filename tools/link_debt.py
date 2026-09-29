#!/usr/bin/env python3
"""Refuse NEW hard-coded image addresses in game source.

A per-function byte match cannot see `*(int *)0x012ED5C8`: the byte gate masks
relocations, so a literal address compiles to the same bytes as a named global.
A linked build can: the moment data moves, that literal reads the wrong memory.
On 2026-09-28, 875 game sources held 2,497 such casts, all integration debt
for the linked build (tools/link_census.py). Declare the global as a named
extern instead -- targets/game/reverse/dir32_addresses.csv names 16,000 of
them, and an address-derived name (g_XXXXXXXX) is fine for one it does not;
docs/shape_levers.md shows that an extern array also matches where a literal
was tried first. The count may only fall: moving or splitting a file keeps its
count, adding a literal fails the commit.

  python3 tools/link_debt.py --staged     # commit hook: staged total vs HEAD
  python3 tools/link_debt.py --report     # per-file counts in the tree
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SKIP = ("game/gen_small/", "game/gen_asm/")
SUFFIXES = (".cpp", ".c", ".h", ".hpp", ".inl")
COMMENTS = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"', re.S)
CAST = re.compile(r'\(\s*(?:(?:const|volatile)\s+)*[\w:<>\s]+\*+\s*(?:const\s*)?\)\s*\(?\s*(0x[0-9A-Fa-f]{7,8})\b'
                  r'|reinterpret_cast\s*<[^>]*\*\s*>\s*\(\s*(0x[0-9A-Fa-f]{7,8})\b')
LOW, HIGH = 0x00400000, 0x02000000  # the image: masks and flag words fall outside


def literals(text):
    found = []
    for match in CAST.finditer(COMMENTS.sub(" ", text or "")):
        value = int(match.group(1) or match.group(2), 16)
        if LOW <= value < HIGH:
            found.append(match.group(0).strip())
    return found


# Every hex literal inside the retail image, in any form: casts, BFME_AT-style
# macros, vftable pointers stored as integers, returned code addresses. The
# commit hook keeps to `literals` (casts); link_census.write_status and the
# README count use this, and err towards calling a constant an address.
IMAGE_HEX = re.compile(r"\b0x([0-9A-Fa-f]{6,8})[uUlL]{0,3}\b")
IMAGE_LOW, IMAGE_HIGH = 0x00401000, 0x01416000  # lotrbfme.exe: ImageBase 0x400000 + SizeOfImage 0x1016000


def addresses(text):
    found = []
    for match in IMAGE_HEX.finditer(COMMENTS.sub(" ", text or "")):
        value = int(match.group(1), 16)
        # Not addresses: low 12 bits clear (sizes, flag words), two or fewer bits
        # set (flags), one repeated hex digit (masks and fill patterns: 0xffffff).
        digits = match.group(1).lstrip("0").lower()
        if (IMAGE_LOW <= value < IMAGE_HIGH and value & 0xFFF and bin(value).count("1") > 2
                and len(set(digits)) > 1):
            found.append(match.group(0))
    return found


def watched(path):
    return path.startswith("game/") and not path.startswith(SKIP) and path.endswith(SUFFIXES)


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True,
                          encoding="utf-8", errors="replace")


def blob(ref, path):
    result = git("show", f"{ref}:{path}")
    return result.stdout if result.returncode == 0 else None


def staged():
    changes = git("diff", "--cached", "--name-status", "-z", "--no-renames").stdout.split("\0")
    before = after = 0
    grew = []
    for status, path in zip(changes[0::2], changes[1::2]):
        if not path or not watched(path):
            continue
        old = len(literals(blob("HEAD", path)))
        new = [] if status.startswith("D") else literals(blob("", path))
        before += old
        after += len(new)
        if len(new) > old:
            grew.append((path, old, new))
    if after <= before:
        return 0
    print(f"link_debt: this commit adds {after - before} hard-coded image address(es) "
          f"({before} -> {after} across the staged sources):")
    for path, old, new in grew:
        print(f"  {path}: {old} -> {len(new)}   e.g. {new[-1][:80]}")
    print("  Declare the global as a named extern instead (dir32_addresses.csv names most; "
          "g_XXXXXXXX otherwise). A literal breaks the linked build the moment data moves.")
    return 1


def per_file(detect=None):
    """[(count, path)] for every tracked game source holding a literal."""
    detect = detect or literals
    rows = []
    for path in git("ls-files", "game").stdout.splitlines():
        if not watched(path):
            continue
        try:
            count = len(detect((ROOT / path).read_text(encoding="utf-8", errors="replace")))
        except OSError:
            continue
        if count:
            rows.append((count, path))
    return rows


def report():
    rows = per_file()
    total, files = sum(count for count, _ in rows), len(rows)
    for count, path in sorted(rows, reverse=True)[:25]:
        print(f"  {count:5}  {path}")
    print(f"link_debt: {total:,} hard-coded image addresses in {files:,} game sources")
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--report", action="store_true")
    args = ap.parse_args(argv)
    return staged() if args.staged else report()


if __name__ == "__main__":
    sys.exit(main())
