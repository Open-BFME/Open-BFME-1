#!/usr/bin/env python3
"""Answer "whose function is this?" from a vtable address.

Workers keep banking bodies as "owning class unidentified" while the retail
vtable constant sits right there in the prologue (`mov [ecx], 0x011xxxxx`).
Given one or more vtable VAs this prints everything the ledger already knows:

  * the ledger row for every slot the retail vtable points at (slot index,
    byte offset, callee name, source) -- the class's known method set
  * every function whose retail bytes carry the vtable constant (ctors, dtors,
    and anything else that installs it), with their ledger names -- the class
    name usually falls straight out of these
  * every symbols.csv / functions.csv note that mentions the address

  python3 tools/vtable_lookup.py 0x01137180 [0x01136058 ...]
  python3 tools/vtable_lookup.py --slots 12 0x011135D0     # cap slot listing
"""
import argparse
import csv
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

ROOT = Path(__file__).resolve().parents[1]


def load_ledger():
    by_rva = {}
    for r in csv.DictReader(open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace")):
        try:
            rva = int(r["target_rva"], 16)
        except ValueError:
            continue
        by_rva[rva] = (r["name"], int(r["target_size"] or 0), r["source"], r["notes"])
    return by_rva


def containing_row(by_rva, sorted_rvas, rva):
    import bisect
    i = bisect.bisect_right(sorted_rvas, rva) - 1
    if i < 0:
        return None
    start = sorted_rvas[i]
    name, size, src, notes = by_rva[start]
    if start <= rva < start + max(size, 1):
        return start, name, size, src
    return None


def read_slots(data, secs, va, max_slots):
    rva = va - 0x400000
    off = build.rva_to_file_offset(secs, rva)
    text_lo, text_hi = None, None
    for s in secs:
        if s["name"].rstrip(b"\0") == b".text" if isinstance(s.get("name"), bytes) else False:
            pass
    slots = []
    for i in range(max_slots):
        entry = struct.unpack("<I", data[off + i * 4: off + i * 4 + 4])[0]
        erva = entry - 0x400000
        if not (0x1000 <= erva < 0x00C00000):
            break
        slots.append((i, entry))
    return slots


def scan_code_for_constant(data, secs, va):
    """File offsets inside .text only where the 4-byte constant appears."""
    needle = struct.pack("<I", va)
    lo, hi = text_bounds(secs)
    start = build.rva_to_file_offset(secs, lo)
    end = build.rva_to_file_offset(secs, hi - 1) + 1
    hits = []
    while True:
        i = data.find(needle, start, end)
        if i < 0:
            break
        hits.append(i)
        start = i + 1
    return hits


def file_offset_to_rva(secs, off):
    for s in secs:
        raw, size, virt = s["raw_pointer"], s["size"], s["rva"]
        if raw <= off < raw + size:
            return virt + (off - raw)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("vtables", nargs="+")
    ap.add_argument("--slots", type=int, default=64)
    a = ap.parse_args()

    data = open(build.EXE, "rb").read()
    secs = build.pe_sections(data)
    by_rva = load_ledger()
    sorted_rvas = sorted(by_rva)
    sym_lines = open(ROOT / "reverse/symbols.csv", encoding="utf-8", errors="replace").read().splitlines()
    fn_lines = open(ROOT / "reverse/functions.csv", encoding="utf-8", errors="replace").read().splitlines()

    pinned_vtables = set()
    for l in sym_lines:
        if l.startswith("??_7"):
            parts = l.split(",")
            if len(parts) > 1 and parts[1].startswith("0x"):
                try:
                    pinned_vtables.add(int(parts[1], 16))
                except ValueError:
                    pass

    for vs in a.vtables:
        va = int(vs, 16)
        if va < 0x400000:
            va += 0x400000
        print(f"=== vtable {va:#010x} (rva {va - 0x400000:#010x}) ===")
        pat = re.compile(r"0x0*%X\b" % va, re.I)
        pat_rva = re.compile(r"0x0*%X\b" % (va - 0x400000), re.I)
        named = [l for l in sym_lines if l.startswith("??_7") and pat.search(l)]
        for l in named:
            print("  PIN:", l[:140])
        print("  -- retail slots --")
        try:
            slots = read_slots(data, secs, va, a.slots, pinned_vtables)
        except Exception as e:
            slots = []
            print("  (cannot read slots:", e, ")")
        for i, entry in slots:
            row = containing_row(by_rva, sorted_rvas, entry - 0x400000)
            if row:
                start, name, size, src = row
                tag = "" if start == entry - 0x400000 else f" (+{entry - 0x400000 - start:#x} into)"
                print(f"  slot {i:3} +{i*4:#05x} -> {entry:#010x} {name[:70]}{tag}  [{Path(src).name}]")
            else:
                print(f"  slot {i:3} +{i*4:#05x} -> {entry:#010x} <unclaimed>")
        print("  -- .text functions carrying the constant (ctors/dtors install it; a cmp is a type check) --")
        hits = scan_code_for_constant(data, secs, va)
        seen = set()
        for off in hits:
            rva = file_offset_to_rva(secs, off)
            if rva is None:
                continue
            row = containing_row(by_rva, sorted_rvas, rva)
            if not row:
                print(f"  at rva {rva:#010x}: <no ledger row>")
                continue
            start, name, size, src = row
            if start in seen:
                continue
            seen.add(start)
            print(f"  {start:#010x} {size:5}B {name[:80]}  [{Path(src).name}]")
        print("  -- ledger notes mentioning it --")
        n = 0
        for l in sym_lines + fn_lines:
            if (pat.search(l) or pat_rva.search(l)) and not l.startswith("??_7"):
                print("  ", l[:150])
                n += 1
                if n >= 12:
                    print("   ...")
                    break
        print()


if __name__ == "__main__":
    main()
