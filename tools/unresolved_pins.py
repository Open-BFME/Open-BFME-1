#!/usr/bin/env python3
"""Pin the callees a red row asks for, reading each address out of retail.

WHY. `symbols.csv` is an ADDITIVE candidate list, so a symbol with no pin is not
a wrong answer -- it is NO answer. build.py says so and emits a zero
displacement:

    unresolved call(s): ?bfmeStep3_250@@YAXPAX@Z (add to targets/game/reverse/symbols.csv)
    target:   ... 56 e8 b9 b5 00 00 ...
    compiled: ... 56 e8 00 00 00 00 ...

29 of the full gate's 147 failures are this, across 22 distinct symbols. None of
them has a matched ledger row, so the address cannot come from the ledger -- it
comes from the retail bytes of the very row that is red, which is the only place
it could honestly come from.

WHY THIS IS NOT THE BULK HARVEST THAT WAS RETRACTED. On 2026-09-06 an automated
pass added 372 callee pins and was retracted the same day for "192 inconsistent
multi-pin identities and even out-of-image targets such as luaM_growaux at
0x6A9E59DF". The difference is scope and proof. This only ever pins a symbol some
RED row is actually blocked on, takes the address from that row's own retail
bytes, and refuses anything it cannot stand behind:

  * the call site must decode as E8 rel32 with a ZERO displacement compiled --
    that is the signature of "no candidate", not of a wrong choice
  * the computed target must land inside the image
  * a symbol already pinned elsewhere is left alone; a second address on a name
    that has one is the multi-pin shape the retraction was about
  * two red rows disagreeing about where one symbol lives is a contradiction, and
    both are dropped rather than one being picked

Every surviving pin is then proved the only way that counts: rebuild the source
and let the byte gate resolve the displacement.

    python3 tools/unresolved_pins.py            # report, write nothing
    python3 tools/unresolved_pins.py --apply    # add the pins it can prove
"""
import argparse
import collections
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

SYMBOLS = build.ROOT / "targets/game/reverse/symbols.csv"
UNRESOLVED = re.compile(r"unresolved call\(s\): (.+?) \(add to")


def pinned():
    out = collections.defaultdict(set)
    for line in SYMBOLS.read_text(encoding="utf-8", errors="replace").splitlines():
        parts = line.split(",")
        if len(parts) >= 2 and parts[1].startswith("0x"):
            out[parts[0]].add(int(parts[1], 16))
    return out


def red_rows(log, rows):
    """Only the rows the gate reported FAILing with an unresolved call.

    Scoping this to the red rows is the whole difference between this tool and the
    372-pin harvest that was retracted. Handed every matched row instead, it
    proposed 7,100 pins -- including $SG419, a string-literal label -- because a
    zero compiled displacement is common and ordinary in rows that are perfectly
    green for other reasons. "A red row asked for it" is the evidence; without it
    there is none.
    """
    wanted, current = set(), None
    for line in Path(log).read_text(errors="replace").splitlines():
        if line.startswith("  FAIL") and "(" in line:
            current = line[len("  FAIL"):line.index("(")].strip()
        elif current and UNRESOLVED.search(line):
            wanted.add(current)
    by_name = {r["name"]: r for r in rows}
    return [by_name[n] for n in wanted if n in by_name], wanted


def proposals(rows):
    """{symbol: {address: [row names]}} read from each red row's retail bytes."""
    found = collections.defaultdict(lambda: collections.defaultdict(list))
    for row in rows:
        try:
            obj = build.require_row_object(row)
            size = int(row["target_size"])
            rva = int(row["target_rva"], 16)
            target = build.read_target_bytes(rva, size)
            body, relocs = build.read_object_symbol_bytes(
                obj, build.ledger_object_symbol(row), size)
        except BaseException:
            continue
        if len(body) < size:
            continue
        for off, rtype, sym in relocs:
            if off + 4 > size:
                continue
            # A zero compiled displacement on an E8 is the "no candidate at all"
            # signature. A non-zero one means a candidate was chosen and did not
            # reproduce, which is a different problem and not this tool's.
            if body[off - 1:off] != b"\xe8" or body[off:off + 4] != b"\0\0\0\0":
                continue
            disp = struct.unpack_from("<i", target, off)[0]
            addr = rva + off + 4 + disp
            found[sym][addr].append(row["name"])
    return found


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--apply", action="store_true")
    ap.add_argument("--gate-log", required=True,
                    help="output of a full ./build.sh; the red rows come from here")
    args = ap.parse_args()

    everything = [r for r in build.load_function_rows() if r.get("status") == "matched"]
    rows, asked = red_rows(args.gate_log, everything)
    print(f"red rows reporting an unresolved call: {len(asked)} "
          f"({len(rows)} still in the ledger)")
    found = proposals(rows)
    already = pinned()

    keep, refused = [], collections.Counter()
    for sym, by_addr in sorted(found.items()):
        if sym in already:
            refused["already pinned under this name"] += 1
            continue
        if len(by_addr) > 1:
            refused["red rows disagree about the address"] += 1
            continue
        addr = next(iter(by_addr))
        if not (0x1000 <= addr < 0x2000000):
            refused["computed target is outside the image"] += 1
            continue
        keep.append((sym, addr, by_addr[addr]))

    print(f"symbols a red row is blocked on: {len(found)}")
    print(f"  pinnable: {len(keep)}   refused: {sum(refused.values())}")
    for why, n in refused.most_common():
        print(f"    {n:>3}  {why}")
    for sym, addr, askers in keep:
        print(f"  {sym[:64]:<64} 0x{addr:08X}  ({len(askers)} row(s))")
    if not args.apply or not keep:
        if keep:
            print("\n  --apply to add them, then rebuild the sources and let the gate prove it")
        return 0

    # symbols.csv is CRLF and the union merge driver treats a bare LF as a
    # distinct line, which is how 4,172 pins once became 8,784. Append with the
    # terminator the file already uses.
    data = SYMBOLS.read_bytes()
    term = b"\r\n" if b"\r\n" in data[-4096:] else b"\n"
    if not data.endswith((b"\n",)):
        data += term
    for sym, addr, askers in keep:
        note = f"additive: retail call target of the red row {askers[0]}"
        data += f"{sym},0x{addr:08X},{note}".encode() + term
    SYMBOLS.write_bytes(data)
    print(f"\nadded {len(keep)} pin(s). Rebuild the affected sources now.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
