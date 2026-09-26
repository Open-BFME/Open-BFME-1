#!/usr/bin/env python3
"""Direct near calls and named IAT calls in a retail body.

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

Exit status 3 and a WARNING line mean decoding did not reach the requested size,
so the listing is incomplete.

Read it BEFORE writing the body, but verify the callee contract independently.
Generated dumps and thunks can have placeholder void signatures unrelated to
the actual ABI. A ledger name is neither signature proof nor a symbols.csv pin.
"""
if __name__ == "__main__":
    from target_guard import require_game_cli
    require_game_cli("callees.py")

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
    # Several retail addresses have multiple ledger identities sharing one
    # compiled COMDAT. The ledger is sorted by name, so last-row-wins can
    # present an unrelated alias as the callee's identity.
    at_rva = collections.defaultdict(set)
    with open(build.ROOT / "targets/game/reverse/functions.csv", newline="") as fh:
        for row in csv.DictReader(fh):
            try:
                rva = int(row["target_rva"], 16)
                name = row["name"]
            except (KeyError, TypeError, ValueError):
                continue
            if name:
                object_symbol = build.ledger_object_symbol(
                    {"name": name, "notes": row.get("notes") or ""})
                at_rva[rva].add((name, object_symbol))

    out = {}
    for rva, entries in at_rva.items():
        names = {name for name, _ in entries}
        objects = {object_symbol for _, object_symbol in entries}
        if len(entries) == 1:
            name, object_symbol = next(iter(entries))
            out[rva] = (name if name == object_symbol else
                        f"{name} [object symbol: {object_symbol}]")
        elif len(objects) == 1:
            out[rva] = (f"{next(iter(objects))} [object symbol; "
                        f"{len(names)} ledger names share RVA]")
        else:
            out[rva] = (f"*** AMBIGUOUS LEDGER: {len(names)} ledger names, "
                        f"{len(objects)} object symbols share RVA ***")
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
    try:
        from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    except ImportError:
        raise SystemExit("callees.py requires capstone; install it in the active Python environment")
    body = build.read_target_bytes(rva, size)
    targets = []
    for instruction in Cs(CS_ARCH_X86, CS_MODE_32).disasm(body, rva):
        # E8 inside an immediate or displacement is not a call. Keep this
        # direct-near-call inventory separate from indirect calls and data.
        if instruction.size == 5 and instruction.bytes[0] == 0xE8:
            target = instruction.address + 5 + struct.unpack_from("<i", instruction.bytes, 1)[0]
            if 0x1000 <= target < IMAGE_MAX and read(target, 1) is not None:
                targets.append(target)
    return collections.Counter(targets)


def decoded_extent(rva, size):
    """Bytes of the body that linear decoding covers before it stops.

    capstone ends the stream at the first byte it cannot decode and says
    nothing, so an inline jump table or padding inside the extent used to cut
    the inventory short while the listing still read as complete.
    """
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    body = build.read_target_bytes(rva, size)
    end = 0
    for instruction in Cs(CS_ARCH_X86, CS_MODE_32).disasm(body, rva):
        end = instruction.address + instruction.size - rva
    return end


def import_calls(rva, size):
    """Resolve call [absolute IAT slot] from the PE import directory.

    Keep these separate from ledger identities and register/vtable calls.
    Decoding instructions prevents an FF 15 byte pair inside data or another
    instruction's operand from being mistaken for a call.
    """
    from capstone import Cs, CS_ARCH_X86, CS_MODE_32
    from pin_consistency import import_table

    imports = import_table()
    counts = collections.Counter()
    body = build.read_target_bytes(rva, size)
    for instruction in Cs(CS_ARCH_X86, CS_MODE_32).disasm(body, rva):
        if instruction.size == 6 and instruction.bytes[:2] == b"\xff\x15":
            slot = struct.unpack_from("<I", instruction.bytes, 2)[0]
            if slot in imports:
                counts[(slot, *imports[slot])] += 1
    return counts


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
        print(f"  {target:#x}{via}  x{hits}  {name or '*** UNNAMED IN FUNCTION LEDGER ***'}")

    print(f"\n{len(counts)} distinct call target(s), {len(unpinned)} unnamed in function ledger")
    if unpinned:
        print("  unnamed: " + ", ".join(hex(u) for u in unpinned))
    else:
        print("  Every direct call target above has a ledger name, not necessarily a proven signature.")
    print("  Ledger names, especially generated/thunk placeholders, are not ABI proof. "
          "Verify full callee bodies and typed declarations before adding or reusing pins.")
    covered = decoded_extent(rva, args.size)
    if covered != args.size:
        print(f"\n  WARNING: INCOMPLETE INVENTORY. Decoding stopped at +0x{covered:X} of 0x{args.size:X} "
              f"bytes (inline data, padding or a wrong size); calls after that point are NOT listed.")
    imports = import_calls(rva, args.size)
    if imports and not args.unpinned_only:
        print("\n  Direct IAT calls (slot VA; names read from the PE import directory):")
        for (slot, dll, name), hits in sorted(imports.items()):
            print(f"  [{slot:#x}]  x{hits}  {dll}!{name}")
        print("  Verify imported argument types separately; register and vtable calls are not listed.")
    return 0 if covered == args.size else 3


if __name__ == "__main__":
    sys.exit(main())
