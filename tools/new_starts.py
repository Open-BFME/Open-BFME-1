#!/usr/bin/env python3
"""Add function starts that only the call graph knows about to the inventory.

Every byte-verified body is retail code, so a `call` inside one points at a real
function whether or not Ghidra found it. Collecting those targets turns up
addresses the inventory has no row for at all -- some genuinely missed, and some
that are mid-function jump targets or the debris of a bad linear decode.

The discriminator is the byte in front of the target: real code between
functions is int3 padding, and a body that ends properly ends in `ret` or a nop
slide. A target that begins immediately after ordinary code is not a boundary,
so it is dropped rather than guessed at. Nothing here reads a proposal file --
the retail image and the two committed inventories are the only inputs.

  python3 tools/new_starts.py            # report only
  python3 tools/new_starts.py --apply    # merge into targets/game/reverse/ghidra_functions.csv
"""
import argparse
import bisect
import csv
import struct
import sys
from pathlib import Path

import build

ROOT = Path(__file__).resolve().parents[1]
GHIDRA = ROOT / "targets/game/reverse" / "ghidra_functions.csv"
IMAGE_BASE = 0x400000
# A body may carry a lone int3 as a trap after a call that never returns, so a
# single 0xCC does not end a function. Inter-function padding is a run.
PADDING_RUN = 2
BOUNDARY_BYTES = (0xCC, 0xC3, 0x90)      # int3 padding, ret, nop slide


def load_inventory():
    with GHIDRA.open("r", encoding="utf-8", newline="") as handle:
        return {int(row["rva"], 16): (int(row["size"]), row["name"])
                for row in csv.DictReader(handle)}


def interval_lookup(intervals):
    """Return a predicate answering whether an address falls inside a span."""
    merged = []
    for low, high in sorted(intervals):
        if merged and low <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], high)
        else:
            merged.append([low, high])
    lows = [span[0] for span in merged]

    def covers(address):
        index = bisect.bisect_right(lows, address) - 1
        return index >= 0 and address < merged[index][1]
    return covers


def call_targets(rows, data, sections, text_low, text_high):
    """Return every .text address called from a byte-verified body.

    Decoded straight from the retail bytes, and stepped a whole instruction at a
    time past each call: restarting one byte in would decode displacement bytes
    as opcodes and invent targets. An incremental-link thunk is followed to the
    body it stands for, so one function is not discovered twice -- but only when
    its displacement stays in .text, since a target this decode invented can
    begin with 0xE9 without being a thunk at all.
    """
    thunks = {}

    def follow(rva):
        if rva not in thunks:
            thunks[rva] = build.follow_thunk(
                data, sections, rva, text_low, text_high)
        return thunks[rva]

    targets = {}
    for row in rows:
        rva = int(row["target_rva"], 16)
        size = int(row["target_size"])
        body = build.read_target_bytes(rva, size)
        index = 0
        while index < len(body) - 4:
            if body[index] not in (0xE8, 0xE9):
                index += 1
                continue
            destination = rva + index + 5 + struct.unpack_from("<i", body, index + 1)[0]
            if body[index] == 0xE8 and text_low <= destination < text_high:
                target = follow(destination)
                targets[target] = targets.get(target, 0) + 1
            index += 5
    return targets


def is_boundary(data, sections, rva):
    """True when rva looks like the first byte of a real function.

    The byte in front must be int3 padding, a ret, or a nop slide. The byte at
    the address must not itself be int3: a call whose displacement lands in the
    middle of a padding run passes the look-behind test while pointing at no
    function at all, which is how 0x98E0B -- five bytes of int3 before the body
    at 0x98E10 -- got proposed as a function start.
    """
    offset = build.rva_to_file_offset(sections, rva)
    return data[offset - 1] in BOUNDARY_BYTES and data[offset] != 0xCC


def derive_size(data, sections, rva, boundaries, text_high):
    """Size from the next known start or the padding run, whichever comes first.

    Trailing int3 is alignment padding and belongs to neither function.
    """
    index = bisect.bisect_right(boundaries, rva)
    limit = boundaries[index] if index < len(boundaries) else text_high
    offset = build.rva_to_file_offset(sections, rva)
    span = data[offset:offset + (limit - rva)]
    run = span.find(b"\xcc" * PADDING_RUN)
    if run >= 0:
        span = span[:run]
    return len(span.rstrip(b"\xcc"))


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--apply", action="store_true",
                        help="merge the verified starts into the inventory")
    args = parser.parse_args()

    data, sections = build.exe_image()
    text = next(section for section in sections if section["name"] == ".text")
    text_low, text_high = text["rva"], text["rva"] + text["size"]

    inventory = load_inventory()
    # The over-claim answer, deliberately, and the one place in the tree that is
    # true: this tool only ever asks "does anything already record a boundary
    # here?", both to skip known starts and to bound derive_size below. A
    # gen-dump row records exactly that and nothing else, so it counts. Asking
    # the work-finder question instead proposes 522 inventory rows (31,769 B)
    # that the dumps already pin, which test_inventory.py rejects outright.
    rows = build.load_claim_rows(counting_dumps=True, matched_only=True)
    claimed = {int(row["target_rva"], 16) for row in rows}
    in_claimed_body = interval_lookup(
        (int(row["target_rva"], 16),
         int(row["target_rva"], 16) + int(row["target_size"])) for row in rows)

    targets = call_targets(rows, data, sections, text_low, text_high)
    unknown = sorted(address for address in targets
                     if address not in inventory and address not in claimed
                     and not in_claimed_body(address))
    verified = [address for address in unknown if is_boundary(data, sections, address)]
    print(f"call targets from {len(rows):,} byte-verified bodies: {len(targets):,}")
    print(f"  starts unknown to the inventory and unclaimed: {len(unknown)}")
    print(f"  preceded by int3/ret/nop (a real boundary)   : {len(verified)}")
    print(f"  rejected as mid-function or bad decode       : {len(unknown) - len(verified)}")

    boundaries = sorted(set(inventory) | claimed | set(verified))
    landed = []
    for address in verified:
        size = derive_size(data, sections, address, boundaries, text_high)
        if size < 1:
            raise SystemExit(f"0x{address:X}: derived a {size}-byte function, "
                             f"which means the boundary scan is wrong")
        landed.append({"rva": f"0x{address:X}", "size": str(size),
                       "name": f"FUN_{address + IMAGE_BASE:08x}"})
    inside_ghidra = interval_lookup(
        (rva, rva + size) for rva, (size, _) in inventory.items())
    overlapping = sum(1 for row in landed if inside_ghidra(int(row["rva"], 16)))
    print(f"  landing {len(landed)} row(s), {sum(int(r['size']) for r in landed):,} bytes"
          f"; {overlapping} fall inside an existing inventory body")

    if not args.apply:
        print("\nreport only; pass --apply to merge into the inventory")
        return 0

    with GHIDRA.open("r", encoding="utf-8", newline="") as handle:
        existing = list(csv.DictReader(handle))
    merged = sorted(existing + landed, key=lambda row: int(row["rva"], 16))
    with GHIDRA.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, ["rva", "size", "name"], lineterminator="\n")
        writer.writeheader()
        writer.writerows(merged)
    print(f"merged into {GHIDRA.relative_to(ROOT)}: "
          f"{len(existing):,} -> {len(merged):,} rows")
    return 0


if __name__ == "__main__":
    sys.exit(main())
