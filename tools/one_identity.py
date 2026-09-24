#!/usr/bin/env python3
"""Retail was linked without identical-COMDAT folding, so each body has one identity.
Prints the evidence for that and counts the real names beyond one per body.
Usage: python3 tools/one_identity.py [--list]   (read by tools/identity_guard.py)"""
import argparse
import collections
import csv
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402
from multi_name import is_placeholder  # noqa: E402

TABLE_START = 0x1005  # first incremental-link table entry, after five bytes of 0xCC
SCALAR_DELETING = bytes.fromhex("568bf1")  # push esi; mov esi,ecx
VECTOR_DELETING = bytes.fromhex("f644240401")  # test byte ptr [esp+4],1


def matched_rows(path=None):
    path = path or B.ROOT / "reverse" / "functions.csv"
    with open(path, encoding="utf-8", errors="replace", newline="") as handle:
        return [r for r in csv.DictReader(handle)
                if r["status"] == "matched" and r["target_rva"].startswith("0x")]


def real_names_by_address(rows):
    """RVA -> set of non-placeholder names claiming a body that starts there."""
    names = collections.defaultdict(set)
    for row in rows:
        if not is_placeholder(row["name"]):
            names[int(row["target_rva"], 16)].add(row["name"])
    return names


def link_table(text, text_rva):
    """(end RVA, body -> entry RVAs) of the contiguous 5-byte `jmp` table at TABLE_START."""
    entries, off = collections.defaultdict(list), TABLE_START - text_rva
    while off + 5 <= len(text) and text[off] == 0xE9:
        body = text_rva + off + 5 + struct.unpack_from("<i", text, off + 1)[0]
        entries[body].append(text_rva + off)
        off += 5
    return text_rva + off, entries


def folding_evidence(rows, text, text_rva, table_end):
    """Byte patterns of 4..16 bytes, free of E8/E9, that retail keeps as separate bodies."""
    sizes, names = {}, collections.defaultdict(set)
    for row in rows:
        rva, size = int(row["target_rva"], 16), int(row["target_size"])
        if table_end <= rva < text_rva + len(text) and 4 <= size <= 16:
            sizes[rva] = size
            names[rva].add(row["name"])
    groups = collections.defaultdict(list)
    for rva, size in sizes.items():
        body = text[rva - text_rva:rva - text_rva + size]
        if 0xE8 not in body and 0xE9 not in body:
            groups[body].append(rva)
    shared = {b: v for b, v in groups.items() if len(v) > 1}
    template = sum(1 for v in shared.values() for rva in v
                   if names[rva] and all("?$" in n for n in names[rva]))
    widest = max(shared.items(), key=lambda kv: len(kv[1]), default=(b"", []))
    return len(shared), sum(len(v) for v in shared.values()), template, widest


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--list", action="store_true", help="print every address with 2+ real names")
    args = ap.parse_args(argv)
    rows = matched_rows()
    image = B.EXE.read_bytes()
    text = next(s for s in B.pe_sections(image) if s["name"] == ".text")
    blob = image[text["raw_pointer"]:text["raw_pointer"] + text["size"]]
    table_end, entries = link_table(blob, text["rva"])
    doubled = [b for b, e in entries.items() if len(e) > 1]
    deleting = sum(1 for b in doubled
                   if blob.startswith((SCALAR_DELETING, VECTOR_DELETING), b - text["rva"]))
    print(f"incremental-link table: {sum(map(len, entries.values()))} entries, "
          f"0x{TABLE_START:08X}..0x{table_end:08X} (the MSVC linker drops incremental "
          f"linking under /OPT:ICF, LNK4075); {len(doubled)} bodies have two entries, "
          f"{deleting} of them deleting-destructor shaped (the ??_E/??_G alias pair)")
    patterns, bodies, template, (widest, widest_rvas) = folding_evidence(
        rows, blob, text["rva"], table_end)
    print(f"folding evidence: {patterns} byte patterns (4..16 B, no E8/E9) sit on {bodies} "
          f"separate bodies; {template} of those bodies are named only as template "
          f"instantiations; {widest.hex()} alone on {len(widest_rvas)}")
    multi = {rva: n for rva, n in real_names_by_address(rows).items() if len(n) > 1}
    if args.list:
        for rva in sorted(multi):
            print(f"0x{rva:08X}\t{len(multi[rva])}\t" + "\t".join(sorted(multi[rva])))
    print(f"surplus names beyond one per body: {sum(len(n) - 1 for n in multi.values())}")
    print(f"addresses with 2+ real names: {len(multi)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
