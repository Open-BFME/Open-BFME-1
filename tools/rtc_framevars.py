#!/usr/bin/env python3
"""Recover retail's own local-variable names from /GZ frame descriptors.

MSVC 7.1's /GZ (run-time error checks) emits, for every function with a local
ARRAY, a call to _RTC_CheckStackVars(frame, desc) where `desc` is a static
structure describing each such local:

    struct _RTC_framedesc { int varCount; _RTC_vardesc *variables; };
    struct _RTC_vardesc  { int addr;      int size;  char *name; };

and `name` is a plain C string carrying THE NAME THE ORIGINAL SOURCE USED. The
descriptor is emitted into .text immediately after the body it belongs to, and
the call site loads it with `lea edx,<imm32>` -- NOT `push imm32`, which is what
an earlier attempt at this scanned for and why it found nothing.

So for any /Od /GZ translation unit this reads out real identifiers and exact
array sizes for free: no shape analysis, no guessing. Measured across the
unclaimed pool it names 151 variables in 101 bodies, including `ncb[0x40]` (a
NetBIOS control block) and `Adapter[0xF0]`, which identify their subsystem
outright.

WHAT IT DOES NOT DO. It sees only locals that are ARRAYS -- /GZ does not
describe scalars -- so an empty result means "no local arrays", never "not /GZ".
And a name is evidence about the SOURCE, not about the function's identity: it
constrains a body's meaning, it does not name the body.

Usage:
  python3 tools/rtc_framevars.py                 # every unclaimed gen_asm body
  python3 tools/rtc_framevars.py --lo 0x7FD000 --hi 0x7FF000
  python3 tools/rtc_framevars.py --rva 0x007FD080
"""
import argparse
import csv
import io
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import build

IMAGE_LO, IMAGE_HI = 0x00400000, 0x01400000
IMAGE_BASE = 0x00400000


def _read(rva, n):
    try:
        return build.read_target_bytes(rva, n)
    except Exception:
        return None


def _cstring(rva, limit=64):
    raw = _read(rva, limit)
    if not raw:
        return None
    end = raw.find(b"\0")
    if end < 1:
        return None
    text = raw[:end]
    return text.decode("ascii") if all(32 <= c < 127 for c in text) else None


def frame_vars(rva, size):
    """[(ebp_offset, size, name)] for the body at rva, or [] if it has none."""
    body = _read(rva, size)
    if not body:
        return []
    for i in range(len(body) - 6):
        # lea edx, <imm32>  -- how the descriptor address reaches the call
        if body[i] != 0x8D or body[i + 1] != 0x15:
            continue
        desc_va = struct.unpack_from("<I", body, i + 2)[0]
        if not (IMAGE_LO <= desc_va < IMAGE_HI):
            continue
        header = _read(desc_va - IMAGE_BASE, 8)
        if not header:
            continue
        count, table_va = struct.unpack("<II", header)
        if not (1 <= count <= 16 and IMAGE_LO <= table_va < IMAGE_HI):
            continue
        out = []
        for k in range(count):
            entry = _read(table_va - IMAGE_BASE + 12 * k, 12)
            if not entry:
                break
            offset, width, name_va = struct.unpack("<iII", entry)
            if not (IMAGE_LO <= name_va < IMAGE_HI):
                break
            name = _cstring(name_va - IMAGE_BASE)
            if not name:
                break
            out.append((offset, width, name))
        if len(out) == count:
            return out
    return []


def main():
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lo", type=lambda s: int(s, 0), default=0)
    ap.add_argument("--hi", type=lambda s: int(s, 0), default=0xFFFFFFFF)
    ap.add_argument("--rva", type=lambda s: int(s, 0),
                    help="one address, claimed or not")
    ap.add_argument("--min-size", type=int, default=24)
    args = ap.parse_args()

    root = Path(__file__).resolve().parent.parent
    rows = []
    with io.open(root / "reverse" / "functions.csv", encoding="utf-8") as fh:
        for i, row in enumerate(csv.reader(fh)):
            if i == 0 or len(row) != 7:
                continue
            rva = int(row[2], 16)
            if args.rva is not None:
                if rva == args.rva:
                    rows.append((rva, int(row[3]), row[4]))
                continue
            # notes, not the source path: dump rows are not confined to
            # Code/gen_asm/ and a path test silently skips the ones that moved.
            if not build.is_scaffold_row({"notes": row[6]}) or "Unwind@" in row[6]:
                continue
            if args.lo <= rva <= args.hi and args.min_size <= int(row[3]) <= 4096:
                rows.append((rva, int(row[3]), row[4]))
    rows.sort()

    bodies = variables = 0
    for rva, size, _ in rows:
        found = frame_vars(rva, size)
        if not found:
            continue
        bodies += 1
        variables += len(found)
        print("0x%08X %5dB  %s" % (rva, size, ", ".join(
            "%s[0x%X] @ebp%+d" % (n, w, o) for o, w, n in found)))
    print("\n%d body(s) carry a frame descriptor; %d variable(s) named"
          % (bodies, variables))


if __name__ == "__main__":
    main()
