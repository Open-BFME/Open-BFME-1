#!/usr/bin/env python3
"""Retail's own base relocations: which dwords of lotrbfme.exe hold an absolute address.

The unpacked baseline has IMAGE_FILE_RELOCS_STRIPPED set and a zero
BASERELOC directory, but its last section (blank name, RVA 0xF62000) still
holds the .reloc blocks link.exe wrote: 3,174 page blocks, 284,870
IMAGE_REL_BASED_HIGHLOW entries (+1,586 ABSOLUTE padding entries) for pages
0x5B000..0xF5E000. The ILT (0x1000..0x5B000) is all rel32 jumps and has none.
That is the linker's list, not an inference: a dword at a listed site is an
absolute address, a dword at any other site is not (a number, a rel32, bytes).

  python3 tools/retail_relocs.py                 # summary
  python3 tools/retail_relocs.py --csv OUT.csv   # one row per site: site_va, target_va, section
"""
import argparse
import bisect
import csv
import struct
import sys
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

HIGHLOW, ABSOLUTE = 3, 0


def parse_blocks(blob):
    """(HIGHLOW site RVAs, ABSOLUTE padding count, bytes consumed) of a run of base relocation blocks.

    Stops at the first header that is not a block (zero size, unaligned page,
    odd size or past the end): the section's raw tail is zero padding.
    """
    sites, padding, p = [], 0, 0
    while p + 8 <= len(blob):
        page, size = struct.unpack_from("<II", blob, p)
        if size < 8 or size % 2 or page % 0x1000 or p + size > len(blob):
            break
        for (entry,) in struct.iter_unpack("<H", blob[p + 8:p + size]):
            kind, offset = entry >> 12, entry & 0xFFF
            if kind == HIGHLOW:
                sites.append(page + offset)
            elif kind == ABSOLUTE:
                padding += 1
            else:
                raise ValueError(f"base relocation type {kind} at page {page:#x}")
        p += size
    return sites, padding, p


def last_section(data):
    """(rva, raw bytes) of the PE's last section."""
    pe = build.u32(data, 0x3C)
    count, optional = build.u16(data, pe + 6), build.u16(data, pe + 20)
    o = pe + 24 + optional + 40 * (count - 1)
    vsize, rva, raw_size, raw_ptr = struct.unpack_from("<IIII", data, o + 8)
    return rva, data[raw_ptr:raw_ptr + min(raw_size, vsize or raw_size)]


@lru_cache(maxsize=1)
def site_rvas():
    """Sorted tuple of every HIGHLOW site RVA in retail."""
    data, _ = build.exe_image()
    _, blob = last_section(data)
    sites, _, _ = parse_blocks(blob)
    if len(sites) < 100_000:
        raise SystemExit(f"retail_relocs: only {len(sites)} HIGHLOW sites in the last section; not a .reloc copy")
    return tuple(sorted(sites))


def sites_in(start_rva, end_rva):
    """Sorted site RVAs in [start_rva, end_rva)."""
    sites = site_rvas()
    return sites[bisect.bisect_left(sites, start_rva):bisect.bisect_left(sites, end_rva)]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--csv", type=Path, help="write site_va,target_va,section per HIGHLOW site")
    args = ap.parse_args(argv)
    data, _ = build.exe_image()
    rva, blob = last_section(data)
    sites, padding, used = parse_blocks(blob)
    base = build.u32(data, build.u32(data, 0x3C) + 24 + 28)
    sections = build.pe_sections(data)

    def section_of(s):
        return next((x for x in sections if x["rva"] <= s < x["rva"] + x["size"]), None)

    by_section = {}
    for s in sites:
        name = (section_of(s) or {"name": "?"})["name"] or "(blank)"
        by_section[name] = by_section.get(name, 0) + 1
    print(f"last section RVA {rva:#x}: {used} bytes of blocks, {len(sites)} HIGHLOW sites, {padding} ABSOLUTE pads")
    print(f"pages {min(sites) & ~0xFFF:#x}..{max(sites) & ~0xFFF:#x}; sites by section: {by_section}")
    if args.csv:
        with args.csv.open("w", newline="", encoding="utf-8") as handle:
            w = csv.writer(handle)
            w.writerow(["site_va", "target_va", "section"])
            for s in sorted(sites):
                sec = section_of(s)
                raw = sec["raw_pointer"] + s - sec["rva"]
                w.writerow([f"0x{base + s:08X}", f"0x{build.u32(data, raw):08X}", sec["name"]])
    return 0


if __name__ == "__main__":
    sys.exit(main())
