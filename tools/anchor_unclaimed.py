#!/usr/bin/env python3
"""Identify unclaimed retail functions by the string literals only they reference.

next_work.py's Ghidra tier already does string anchoring, but it starts from a
drift row -- so it can only ever name a function that already has a Zero Hour
counterpart in drift_report.csv. That input is finite and now drained: at
db3e7b522 the structural tier holds 2 candidates and the Ghidra tier 0.

This runs the same evidence the other way round. Start from every unclaimed
function in the image, take the literals that no *other* unclaimed function
references, and look those up in the Zero Hour reference tree. Measured at
db3e7b522:

    19,464  unclaimed functions >=32B
     1,326  have at least one uniquely-referenced literal
       138  whose literals appear in exactly one ZH source file   <- emitted
        59  ambiguous across several ZH files                     <- emitted, medium
     1,129  literal absent from the ZH tree entirely (BFME-only code)

The 1,129 are not served here. They carry a real lead -- a distinctive string, a
boundary, resolved callees -- but naming them means synthesising an identity
rather than recovering one, which is a different job with a different review bar.

Scanning 5,512 reference files takes far longer than next_work.py's ten-second
budget, so the result is cached in targets/game/reverse/anchored_candidates.csv the way
drift_report.csv is. Regenerate after a batch of landings.

Usage:
  python3 tools/anchor_unclaimed.py [--min-size 32] [--out targets/game/reverse/anchored_candidates.csv]
"""
import argparse
import collections
import csv
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import numpy as np

import build
import progress as P

ROOT = Path(__file__).resolve().parents[1]
GHIDRA = ROOT / "targets/game/reverse" / "ghidra_functions.csv"
XREFS = ROOT / "targets/game/reverse" / "string_xrefs.tsv"
ZH = ROOT / "inputs/reference" / "CnC_Generals_Zero_Hour"
OUT = ROOT / "targets/game/reverse" / "anchored_candidates.csv"

# Short literals ("OK", "%d") are shared by hundreds of functions and identify
# nothing; the floor is what makes a match evidence rather than a coincidence.
MIN_LITERAL = 8
QUOTED = re.compile(r'"((?:[^"\\]|\\.){%d,120})"' % MIN_LITERAL)


def unclaimed_functions(min_size):
    """{rva: (size, ghidra name)} for every function no ledger row covers."""
    for path in (GHIDRA, XREFS):
        if not path.exists():
            raise SystemExit(
                f"{path.relative_to(ROOT)} is missing — it is required here and is "
                f"generated per tools/ghidra/README.md")
    text_start, text_size = P.retail_text()
    text_end = text_start + text_size
    claimed = np.zeros(text_size, dtype=bool)
    for (_name, rva), (size, _source) in P.matched_at(None).items():
        start = max(int(rva, 16), text_start) - text_start
        end = min(int(rva, 16) + size, text_end) - text_start
        if start < end:
            claimed[start:end] = True
    out = {}
    with GHIDRA.open(newline="") as handle:
        for row in csv.DictReader(handle):
            rva, size = int(row["rva"], 16), int(row["size"])
            start = max(rva, text_start) - text_start
            end = min(rva + size, text_end) - text_start
            if start >= end or size < min_size or claimed[start:end].mean() >= 0.5:
                continue
            out[rva] = (size, row["name"])
    return out


def unique_anchors(unclaimed):
    """{rva: [literals that no other unclaimed function references]}."""
    anchors = collections.defaultdict(list)
    with XREFS.open(encoding="utf-8", errors="replace") as handle:
        for line in handle:
            fields = line.rstrip("\n").split("\t")
            if len(fields) < 2 or len(fields[0]) < MIN_LITERAL:
                continue
            referencing = []
            for token in fields[1].replace(",", " ").split():
                try:
                    referencing.append(int(token, 16))
                except ValueError:
                    pass
            hits = [rva for rva in referencing if rva in unclaimed]
            if len(hits) == 1:
                anchors[hits[0]].append(fields[0])
    return anchors


def zh_literal_index():
    """{literal: {source basenames containing it}} over the reference tree."""
    if not ZH.is_dir():
        raise SystemExit(f"{ZH.relative_to(ROOT)} is missing — the reference tree is required")
    index = collections.defaultdict(set)
    for base, _dirs, files in os.walk(ZH):
        for name in files:
            if not name.endswith((".cpp", ".c", ".h")):
                continue
            try:
                text = Path(base, name).read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            for match in QUOTED.finditer(text):
                index[match.group(1)].add(name)
    return index


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--min-size", type=int, default=32,
                        help="ignore functions smaller than this (default 32)")
    parser.add_argument("--out", default=str(OUT.relative_to(ROOT)))
    args = parser.parse_args()

    unclaimed = unclaimed_functions(args.min_size)
    anchors = unique_anchors(unclaimed)
    print(f"unclaimed >={args.min_size}B: {len(unclaimed):,}; "
          f"uniquely anchored: {len(anchors):,}", file=sys.stderr)

    index = zh_literal_index()
    print(f"reference literals indexed: {len(index):,}", file=sys.stderr)

    rows, unresolved, ambiguous = [], 0, 0
    for rva, literals in anchors.items():
        sources = set()
        for literal in literals:
            sources |= index.get(literal, set())
        if not sources:
            unresolved += 1
            continue
        best = sorted(literals, key=len, reverse=True)[0]
        size, ghidra_name = unclaimed[rva]
        if len(sources) == 1:
            confidence = "high"
        else:
            confidence = "medium"
            ambiguous += 1
        rows.append({
            "target_rva": f"0x{rva:08X}", "target_size": size,
            "zh_source": sorted(sources)[0], "alternates": len(sources) - 1,
            "confidence": confidence, "ghidra_name": ghidra_name,
            "anchor": best,
        })
    rows.sort(key=lambda r: (r["confidence"] != "high", -r["target_size"]))

    path = ROOT / args.out
    with path.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(rows[0].keys()) if rows else
                                ["target_rva", "target_size", "zh_source", "alternates",
                                 "confidence", "ghidra_name", "anchor"])
        writer.writeheader()
        writer.writerows(rows)

    high = sum(1 for r in rows if r["confidence"] == "high")
    total = sum(r["target_size"] for r in rows)
    print(f"wrote {path.relative_to(ROOT)}: {len(rows):,} candidates "
          f"({high:,} high, {ambiguous:,} medium), {total:,} bytes", file=sys.stderr)
    print(f"not in the reference tree (BFME-only, not served): {unresolved:,}",
          file=sys.stderr)


if __name__ == "__main__":
    main()
