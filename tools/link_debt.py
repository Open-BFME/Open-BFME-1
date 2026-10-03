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
was tried first. A source's address multiset may only shrink. A detected file
rename keeps it; adding or substituting an address fails the commit.

  python3 tools/link_debt.py --staged     # commit hook: staged total vs HEAD
  python3 tools/link_debt.py --report     # per-file counts in the tree
"""
import argparse
import collections
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SKIP = ("game/gen_small/", "game/gen_asm/")
SUFFIXES = (".cpp", ".c", ".h", ".hpp", ".inl")
COMMENTS = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"', re.S)
# Keep the suffix outside the captured address, but inside its token. Callback
# casts have a parenthesized pointer declarator followed by a parameter list.
# Both spellings used to evade the per-file address multiset ratchet.
INTEGER_SUFFIX = r'(?:[uU](?:ll|LL|[lL])?|(?:ll|LL|[lL])[uU]?)?'
POINTER_TYPE = r'[\w:<>\s]+(?:\*+\s*(?:(?:const|volatile)\s*)?|\(\s*\*\s*\)\s*\([^()]*\)\s*)'
CAST = re.compile(r'\(\s*' + POINTER_TYPE + r'\)\s*\(?\s*(0x[0-9A-Fa-f]{6,8})' + INTEGER_SUFFIX + r'\b'
                  r'|reinterpret_cast\s*<(?:[^>]*\*\s*|\s*' + POINTER_TYPE + r')>\s*\(\s*(0x[0-9A-Fa-f]{6,8})' + INTEGER_SUFFIX + r'\b')
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
    fields = git("diff", "--cached", "--name-status", "-z", "--find-renames").stdout.split("\0")
    changes, index = [], 0
    while index < len(fields) and fields[index]:
        status = fields[index]
        if status.startswith(("R", "C")):
            changes.append((status, fields[index + 1], fields[index + 2]))
            index += 3
        else:
            changes.append((status, fields[index + 1], fields[index + 1]))
            index += 2
    before = after = 0
    grew = []
    for status, old_path, path in changes:
        if not path or not watched(path):
            continue
        old_literals = ([] if status.startswith(("A", "C")) or not watched(old_path)
                        else literals(blob("HEAD", old_path)))
        new = [] if status.startswith("D") else literals(blob("", path))
        before += len(old_literals)
        after += len(new)
        old_addresses = collections.Counter(int(re.search(r"0x[0-9A-Fa-f]{6,8}", item).group(), 16)
                                             for item in old_literals)
        new_addresses = collections.Counter(int(re.search(r"0x[0-9A-Fa-f]{6,8}", item).group(), 16)
                                             for item in new)
        added = list((new_addresses - old_addresses).elements())
        if added:
            grew.append((path, len(old_literals), new, added))
    if after <= before and not grew:
        return 0
    added = sum(len(found) for _, _, _, found in grew)
    print(f"link_debt: this commit adds {added} hard-coded image address(es) to staged source(s) "
          f"({before} -> {after} in total across the staged sources):")
    for path, old, new, found in grew:
        print(f"  {path}: {old} -> {len(new)}   new address e.g. 0x{found[-1]:08X}")
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
