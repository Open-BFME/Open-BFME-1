#!/usr/bin/env python3
"""Find a source file in the flat Common/ directory without knowing its name.

WHY THIS EXISTS. 6,546 .cpp files sit directly in game/GameEngine/Source/Common/
and 80% are named after a hex address or an invented token, so the directory
cannot be browsed and a filename cannot be guessed. Four mechanical fixes were
measured and all fail:

  * group into subdirectories by owning class -- 2,623 classes for 2,817 files,
    i.e. one file each; it trades a flat directory for thousands of empty ones.
  * rename files after their ledger row -- rename_addressed_sources.py approves
    19 and refuses 4,585, of which 4,087 are "row still placeholder": a file
    cannot be named after a function nobody has identified.
  * place files by their neighbours in the retail binary -- validated against
    already-placed bodies as a holdout, it is 70% correct and 29% WRONG. Moving
    a file breaks its includers, and a previous placement lane shipped 529 wrong
    moves out of 1,368. Not usable for moving.
  * rename files after their owning class -- 3,039 classes for 3,306 files, and
    it collapses three distinct BitFlags constructors onto one filename.

The information needed to ORGANISE the tree does not exist yet; it arrives only
as functions are identified. But a 70% signal that is unusable for a `git mv` is
perfectly good for a search hint, because a wrong hint costs a second and a wrong
move breaks the build. So this indexes rather than reorganises.

    python3 tools/whereis.py Weather          # substring of a class or symbol
    python3 tools/whereis.py 0x0039B450       # a retail address
    python3 tools/whereis.py --near 0x0039B450  # what else lives around it
"""
import argparse
import bisect
import csv
import os
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGER = ROOT / "targets/game/reverse/functions.csv"
DUMPS = ("game/GameEngine/Source/Common", "game/gen_small", "game/gen_asm",
         "game/GameEngine/Source/Common/Bfme",
         "game/GameEngine/Source/Common/SmallGaps")
NEAR = 0x4000


def load():
    rows = []
    with open(LEDGER, newline="") as fh:
        for r in csv.DictReader(fh):
            src = r.get("source") or ""
            try:
                rva = int(r["target_rva"], 16)
            except (KeyError, TypeError, ValueError):
                continue
            if src:
                rows.append((rva, r["name"], src, r.get("target_size") or "?"))
    rows.sort()
    return rows


def neighbour_hint(rows, rvas, rva, own_source):
    """Best guess at the owning module, from the placed bodies either side.

    Measured 70% correct / 29% wrong on a holdout of already-placed bodies, so it
    is reported as a guess and never acted on. Same-file siblings are skipped --
    using them to predict their own file is circular.
    """
    i = bisect.bisect_left(rvas, rva)
    left = right = None
    for j in range(i - 1, -1, -1):
        d = os.path.dirname(rows[j][2])
        if d in DUMPS or rows[j][2] == own_source:
            continue
        if rva - rows[j][0] <= NEAR:
            left = d
        break
    for j in range(i + 1, len(rows)):
        d = os.path.dirname(rows[j][2])
        if d in DUMPS or rows[j][2] == own_source:
            continue
        if rows[j][0] - rva <= NEAR:
            right = d
        break
    return left if left and left == right else None


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("query", help="substring of a class/symbol, or an 0x address")
    ap.add_argument("--near", action="store_true",
                    help="with an address: show the bodies laid out around it")
    ap.add_argument("--limit", type=int, default=25)
    args = ap.parse_args()

    rows = load()
    rvas = [r[0] for r in rows]

    if args.query.lower().startswith("0x"):
        want = int(args.query, 16)
        if args.near:
            i = bisect.bisect_left(rvas, want)
            for rva, name, src, size in rows[max(0, i - 6):i + 7]:
                mark = ">>" if rva == want else "  "
                print(f"{mark} {rva:#010x} {size:>6}B  {name[:58]}\n      {src}")
            return 0
        hits = [r for r in rows if r[0] == want]
    else:
        q = args.query.lower()
        hits = [r for r in rows if q in r[1].lower() or q in os.path.basename(r[2]).lower()]

    if not hits:
        print(f"nothing in the ledger matches {args.query!r}. "
              f"Try a shorter substring, or --near an address.")
        return 1

    by_src = defaultdict(list)
    for rva, name, src, size in hits:
        by_src[src].append((rva, name, size))

    print(f"{len(hits)} row(s) in {len(by_src)} file(s)\n")
    for src, items in sorted(by_src.items())[:args.limit]:
        flat = os.path.dirname(src) in DUMPS
        print(src + ("   [flat -- unplaced]" if flat else ""))
        if flat:
            hint = neighbour_hint(rows, rvas, items[0][0], src)
            if hint:
                # A hint, never an instruction: this signal is 29% wrong.
                print(f"      probably belongs under {hint}  (neighbour guess, ~70% reliable)")
        for rva, name, size in sorted(items)[:6]:
            print(f"      {rva:#010x} {size:>6}B  {name[:70]}")
        if len(items) > 6:
            print(f"      ... and {len(items) - 6} more")
        print()
    if len(by_src) > args.limit:
        print(f"({len(by_src) - args.limit} more files; raise --limit)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
