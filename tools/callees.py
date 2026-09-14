#!/usr/bin/env python3
"""Every function a retail body calls, resolved against the ledger.

WHY THIS EXISTS. Two seats on consecutive tier-1 candidates reported being
blocked on "unresolved" or "unpinned" callees, and both were wrong in the same
way: they INVENTED a name and then reported it missing. The body at 0x004DBE80
was declared to call `lookupRankImageForPopup`, which does not exist -- the real
function is `lookupRankImage` at 0x004DA760 with an identical signature, pinned
all along. The body at 0x00757E70 was declared to call
`SegmentedLineClass::Set_Texture`, which it never calls; every SegmentedLineClass
method it DOES call was already pinned. In both bodies the true count of
unpinned targets was zero.

Acting on either report would have added bogus pins -- a claim about the retail
binary, invented to make our own source compile.

`decode_calls.py` answers this, but only for a symbol that already has a ledger
row or a known source, and a tier-1 candidate has neither by definition. That is
precisely when a seat is guessing, so the tool it needs refuses to run. This one
takes a bare address and never needs a row.

    python3 tools/callees.py 0x004DBE80 4126
    python3 tools/callees.py 0x00757E70 982 --unpinned-only

Read it BEFORE writing the body: the resolved names are the callee contract, and
every one of them is a function whose signature the ledger already knows.
"""
import argparse
import collections
import csv
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import build

IMAGE_MAX = 0x1400000


def ledger_names():
    out = {}
    with open(build.ROOT / "reverse/functions.csv", newline="") as fh:
        for row in csv.DictReader(fh):
            try:
                out[int(row["target_rva"], 16)] = row["name"]
            except (KeyError, TypeError, ValueError):
                continue
    return out


def read(rva, size):
    """Bytes at rva, or None when the address is not in a section.

    A bare 0xE8 scan is not a disassembler: the byte occurs inside operands and
    data, so some computed targets land outside the image. Those are not calls,
    and letting read_target_bytes raise on them would abort the whole listing.
    """
    try:
        return build.read_target_bytes(rva, size)
    except ValueError:
        return None


def call_targets(rva, size):
    body = build.read_target_bytes(rva, size)
    targets, i = [], 0
    while i < len(body) - 4:
        if body[i] == 0xE8:
            target = rva + i + 5 + struct.unpack_from("<i", body, i + 1)[0]
            if 0x1000 <= target < IMAGE_MAX and read(target, 1) is not None:
                targets.append(target)
                i += 5
                continue
        i += 1
    return collections.Counter(targets)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("rva", help="body start, e.g. 0x004DBE80")
    ap.add_argument("size", type=int, help="body length in bytes")
    ap.add_argument("--unpinned-only", action="store_true",
                    help="print only targets the ledger cannot name")
    args = ap.parse_args()

    rva = int(args.rva, 16)
    names = ledger_names()
    counts = call_targets(rva, args.size)

    unpinned = []
    for target, hits in sorted(counts.items()):
        resolved, name = target, names.get(target)
        thunk = read(target, 5)
        if thunk and thunk[0] == 0xE9:          # incremental-link thunk
            resolved = target + 5 + struct.unpack_from("<i", thunk, 1)[0]
            name = name or names.get(resolved)
        if name is None:
            unpinned.append(resolved)
        elif args.unpinned_only:
            continue
        via = f" -> {resolved:#x}" if resolved != target else ""
        print(f"  {target:#x}{via}  x{hits}  {name or '*** UNPINNED ***'}")

    print(f"\n{len(counts)} distinct call target(s), {len(unpinned)} unpinned")
    if unpinned:
        # Only these are candidates for a new pin, and even here the body may be
        # reached through a thunk this scan did not follow. Prove it before pinning.
        print("  unpinned: " + ", ".join(hex(u) for u in unpinned))
    else:
        print("  Every callee is already in the ledger. If your source will not "
              "link, you named one of them WRONG -- match your declaration to the "
              "name above rather than adding a pin.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
