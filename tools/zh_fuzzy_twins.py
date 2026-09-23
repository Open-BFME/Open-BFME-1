#!/usr/bin/env python3
"""Fuzzy Zero Hour twins for anonymous retail bodies.

tools/zh_sweep.py places a compiled Zero Hour function in retail only when its
bytes match exactly. BFME changed most of that code, so 11,278 compiled ZH
functions were never placed, and the open dump bodies they correspond to stayed
anonymous: no class, no layout lines in the brief, no source to start from.

This tool compares SHAPE instead of bytes. Each body becomes its mnemonic
stream (relocation slots zeroed first); a 4-gram index proposes candidates and
difflib.SequenceMatcher scores the best few. It writes
reverse/zh_fuzzy_twins.tsv, which tools/fleet/context_pack.py shows in a brief.

Calibrated 2026-09-21 on 1,638 retail bodies already landed under the name of
an unplaced ZH function (so the truth is known): the true twin scores a median
0.81, and the table printed by --calibrate gives the share of top-1 answers
that are right at each similarity and margin. A row is a HYPOTHESIS: it gives a
session a class to test and a source to start from. It is never identity
evidence by itself -- AGENTS.md still requires a caller, vtable slot or literal
before a real name is pinned.

  python tools/zh_fuzzy_twins.py               # rewrite reverse/zh_fuzzy_twins.tsv
  python tools/zh_fuzzy_twins.py --calibrate   # precision table only

Inputs are host-local build artefacts (build/zh_sweep/match.json and the ZH
objects in build/spike_zh, both made by tools/zh_sweep.py); the output is
tracked so every host's briefs carry it.
"""
import argparse
import collections
import difflib
import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
OUT = ROOT / "reverse" / "zh_fuzzy_twins.tsv"
MIN_BYTES = 150
MIN_INSTRUCTIONS = 25
FLOOR = 0.60          # below this the top-1 answer is wrong more often than right
HEADER = "rva\tsize\tsimilarity\tmargin\tzh_symbol\tzh_source\n"


def grams(seq, n=4):
    return {tuple(seq[i:i + n]) for i in range(len(seq) - n + 1)}


def rank(seq, size, library, index, shortlist=12):
    """[(similarity, symbol)] best first among ZH functions of comparable size."""
    votes = collections.Counter()
    for gram in grams(seq):
        for symbol in index.get(gram, ()):
            votes[symbol] += 1
    scored = []
    for symbol, _ in votes.most_common(shortlist):
        other, other_size = library[symbol]
        if 0.5 <= other_size / max(size, 1) <= 2.0:
            scored.append((difflib.SequenceMatcher(None, seq, other, autojunk=False).ratio(), symbol))
    return sorted(scored, reverse=True)


def best(seq, size, library, index):
    """(similarity, margin over the runner-up, symbol) or None."""
    scored = rank(seq, size, library, index)
    if not scored:
        return None
    runner = scored[1][0] if len(scored) > 1 else 0.0
    return scored[0][0], scored[0][0] - runner, scored[0][1]


def build_index(library):
    index = collections.defaultdict(set)
    for symbol, (seq, _) in library.items():
        for gram in grams(seq):
            index[gram].add(symbol)
    return index


def load_library():
    """{zh symbol: (mnemonics, size)} and {symbol: source} for ZH functions the
    exact sweep did not place uniquely."""
    import build
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    match = json.loads((ROOT / "build/zh_sweep/match.json").read_text(encoding="utf-8"))
    by_obj = collections.defaultdict(list)
    for entry in match:
        if entry["size"] >= MIN_BYTES and entry["bucket"] in ("no-placement", "near"):
            by_obj[entry["obj"]].append(entry)
    library, sources = {}, {}
    for obj, entries in by_obj.items():
        path = ROOT / "build/spike_zh" / obj
        if not path.exists():
            continue
        for entry in entries:
            if entry["sym"] in library:
                continue
            try:
                data, relocs = build.read_object_symbol_bytes(path, entry["sym"])
            except Exception:  # noqa: BLE001  (a COMDAT the reader cannot isolate)
                continue
            data = bytearray(data)
            for offset, kind, _ in relocs:
                width = build.RELOC_WIDTH.get(kind, 4)
                data[offset:offset + width] = bytes(width)
            seq = [i.mnemonic for i in md.disasm(bytes(data), 0)]
            if len(seq) >= MIN_INSTRUCTIONS:
                library[entry["sym"]] = (seq, len(data))
                sources[entry["sym"]] = entry["source"]
    return library, sources, md


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--calibrate", action="store_true")
    ap.add_argument("--census", action="store_true",
                    help="also scan build/gap_census.csv bodies >= 600 B (unclaimed .text, extents estimated)")
    a = ap.parse_args()
    import build
    import eligibility
    library, sources, md = load_library()
    if not library:
        sys.exit("no compiled ZH objects under build/spike_zh: run tools/zh_sweep.py on this host first")
    index = build_index(library)
    exe = Path(build.EXE).read_bytes()
    sections = build.pe_sections(exe)

    def retail(rva, size):
        offset = build.rva_to_file_offset(sections, rva)
        return [i.mnemonic for i in md.disasm(exe[offset:offset + size], 0)]

    rows = eligibility.load_rows()
    print(f"{len(library)} unplaced ZH functions of {MIN_BYTES}+ bytes", flush=True)
    truth = []
    for row in rows:
        size = int(row.get("target_size") or 0)
        if row["name"] in library and not eligibility.is_dump_row(row) and size >= MIN_BYTES:
            got = best(retail(eligibility.rva_of(row), size), size, library, index)
            if got:
                truth.append((got[0], got[1], got[2] == row["name"]))
    print(f"calibration on {len(truth)} landed bodies whose ZH twin is known:")
    for low, high in ((0.9, 1.01), (0.8, 0.9), (0.7, 0.8), (0.6, 0.7), (0.0, 0.6)):
        for label, keep in (("any margin", lambda m: True), ("margin >= 0.05", lambda m: m >= 0.05)):
            band = [t for t in truth if low <= t[0] < high and keep(t[1])]
            if band:
                print(f"  similarity {low:.1f}-{min(high, 1.0):.1f}, {label:14}: top-1 correct "
                      f"{100 * sum(t[2] for t in band) / len(band):3.0f}%  (n={len(band)})")
    if a.calibrate:
        return
    found = []
    for row in eligibility.open_dumps(rows):
        size = int(row.get("target_size") or 0)
        if size < MIN_BYTES:
            continue
        rva = eligibility.rva_of(row)
        got = best(retail(rva, size), size, library, index)
        if got and got[0] >= FLOOR:
            found.append((rva, size, got[0], got[1], got[2], sources[got[2]]))
    if a.census:
        # unclaimed .text has no ledger row, so open_dumps never sees it; the census
        # (tools/gap_census.py) proves starts and estimates extents to the next start,
        # good enough for a shape match (2026-09-23: 390 bodies >= 600 B, 677 KB)
        import csv
        held = {eligibility.rva_of(r) for r in rows if eligibility.rva_of(r) is not None}
        seen = {f[0] for f in found}
        n_census = 0
        with (ROOT / "build/gap_census.csv").open(newline="") as fh:
            for r in csv.DictReader(fh):
                rva, size = int(r["rva"], 16), int(r["size"])
                if size < 600 or rva in held or rva in seen:
                    continue
                got = best(retail(rva, size), size, library, index)
                if got and got[0] >= FLOOR:
                    found.append((rva, size, got[0], got[1], got[2], sources[got[2]])); n_census += 1
        print(f"census: {n_census} unclaimed bodies with a twin >= {FLOOR}", flush=True)
    found.sort()
    with OUT.open("w", encoding="utf-8", newline="\n") as handle:
        handle.write(HEADER)
        for rva, size, similarity, margin, symbol, source in found:
            handle.write(f"0x{rva:08X}\t{size}\t{similarity:.2f}\t{margin:.2f}\t{symbol}\t{source}\n")
    strong = [f for f in found if f[2] >= 0.8]
    print(f"wrote {OUT.relative_to(ROOT).as_posix()}: {len(found)} open bodies ({sum(f[1] for f in found) // 1024} KB), "
          f"{len(strong)} at 0.80+ ({sum(f[1] for f in strong) // 1024} KB)")


def load_twins(path=None):
    """{rva:int -> dict(similarity, margin, symbol, source)} for brief generation."""
    path = path or OUT
    twins = {}
    if not path.exists():
        return twins
    for line in path.read_text(encoding="utf-8").splitlines()[1:]:
        fields = line.split("\t")
        if len(fields) >= 6:
            try:
                twins[int(fields[0], 16)] = dict(similarity=float(fields[2]), margin=float(fields[3]),
                                                 symbol=fields[4], source=fields[5])
            except ValueError:
                continue
    return twins


if __name__ == "__main__":
    main()
