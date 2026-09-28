#!/usr/bin/env python3
"""Map every unclaimed .text gap: what is there, and on what evidence.

`progress.py` reports ~140 KB of real code (padding stripped) that no ledger
row claims. carve_unclaimed.py emits only the bodies whose BOTH boundaries are
proven; the rest stays an anonymous "gap". This classifies each gap so a seat
(or a person) knows what kind of work it is before opening it:

  tail       the row ending at the gap's start stops on a non-terminal
             instruction (no ret/jmp/int3): its extent is short, the gap is
             the rest of that function -- fix the row's size, do not carve
  functions  positive starts inside the gap: direct REL32 call targets (folding
             ILT thunks), Ghidra function entries, or code right after an int3
             run; each listed with its caller count
  data       the gap does not decode as code at its start, or a table/indexed
             jump elsewhere points into it
  unknown    none of the above (read it by hand)

The `verdicts` column lists re_attempts.log bodies overlapping the gap (latest
status per address): a gap with a `partial`/`blocked` body there is already
mapped -- its boundary is proven and the work is a conversion, served by the
finish/retry lanes -- not unexplored code.

Evidence comes from the retail bytes (capstone), the repo's call index, and --
when the GhidraSQL server is up -- Ghidra's function table (advisory starts).

  python3 tools/map_gaps.py                 # rewrite targets/game/reverse/unclaimed_map.csv
  python3 tools/map_gaps.py --top 20        # print the largest gaps with their evidence
"""
import argparse
import bisect
import csv
import json
import struct
import sys
import urllib.request
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "fleet"))

OUT = ROOT / "targets/game/reverse/unclaimed_map.csv"
FIELDS = ["gap_start", "gap_end", "code_bytes", "kind", "prev_row", "prev_ends_terminal",
          "starts", "ghidra_starts", "evidence", "verdicts"]
BASE = 0x400000
TERMINAL = ("ret", "retf", "jmp", "int3")


def ghidra_starts(lo, hi, url):
    """Ghidra function entries in [lo, hi) as RVAs; [] when the server is down."""
    sql = f"SELECT addr FROM funcs WHERE addr >= {lo + BASE} AND addr < {hi + BASE} ORDER BY addr"
    try:
        req = urllib.request.Request(url, data=sql.encode(), method="POST")
        with urllib.request.urlopen(req, timeout=60) as resp:
            res = json.loads(resp.read().decode())["results"][-1]
        return [int(r[0]) - BASE for r in res["rows"]] if res.get("success") else []
    except OSError:
        return []


def last_instruction(md, raw, lo, start, size):
    """Mnemonic of the last decoded instruction of [start, start+size)."""
    last = None
    for ins in md.disasm(raw[start - lo:start - lo + size], start):
        last = ins
    return last.mnemonic if last else None


def overlapping_verdicts(a, b, records):
    """[(rva, size, status)] of latest verdict bodies overlapping [a, b)."""
    found = []
    for rva, fields in records.items():
        try:
            size = int(fields[2])
        except (ValueError, IndexError):
            continue
        if rva < b and rva + max(size, 1) > a:
            found.append((rva, size, fields[3]))
    return sorted(found)


def classify(gap, raw, lo, md, rows_by_end, callers, url, records=None):
    a, b, code = gap
    prev = rows_by_end.get(a)
    prev_terminal = None
    if prev is not None:
        mnemonic = last_instruction(md, raw, lo, int(prev["target_rva"], 16), int(prev["target_size"]))
        prev_terminal = mnemonic in TERMINAL if mnemonic else None
    # positive starts: call targets and code after an int3 run
    starts = sorted(t for t in callers if a <= t < b)
    # A lone 0xCC is often an operand byte. MSVC pads between functions with an
    # int3 RUN to the next 16-byte boundary, so require two or more int3 bytes
    # ending on an aligned start, or four or more anywhere.
    pad_starts = []
    for i in range(a + 1, b):
        if raw[i - lo] == 0xCC or raw[i - 1 - lo] != 0xCC:
            continue
        run = 0
        while i - 1 - run >= a and raw[i - 1 - run - lo] == 0xCC:
            run += 1
        if (run >= 2 and i % 16 == 0) or run >= 4:
            pad_starts.append(i)
    ghidra = ghidra_starts(a, b, url) if url else []
    first = raw[a - lo:a - lo + 16].lstrip(b"\xcc")
    decodes = next(md.disasm(first, a), None) is not None if first else False
    evidence = []
    if prev is not None and prev_terminal is False and not (starts and starts[0] == a):
        kind = "tail"
        evidence.append(f"{prev['name'][:60]} ends at the gap on a non-terminal instruction")
    elif starts or ghidra or pad_starts:
        kind = "functions"
        if starts:
            evidence.append(f"{len(starts)} call target(s)")
        if ghidra:
            evidence.append(f"{len(ghidra)} Ghidra start(s)")
        if pad_starts:
            evidence.append(f"{len(pad_starts)} start(s) after int3 padding")
    elif not decodes:
        kind = "data"
        evidence.append("does not decode at its start")
    else:
        kind = "unknown"
    all_starts = sorted(set(starts) | set(pad_starts))
    return {
        "gap_start": f"0x{a:08X}", "gap_end": f"0x{b:08X}", "code_bytes": code, "kind": kind,
        "prev_row": prev["name"] if prev is not None else "",
        "prev_ends_terminal": "" if prev_terminal is None else int(prev_terminal),
        "starts": " ".join(f"0x{s:08X}:{len(callers.get(s, ()))}" for s in all_starts[:12]),
        "ghidra_starts": " ".join(f"0x{s:08X}" for s in ghidra[:12]),
        "evidence": "; ".join(evidence),
        "verdicts": " ".join(f"0x{v:08X}:{size}:{status}"
                             for v, size, status in overlapping_verdicts(a, b, records or {})[:6]),
    }


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--top", type=int, default=0, help="print the N largest gaps instead of writing the CSV")
    ap.add_argument("--url", default="http://127.0.0.1:8081/query")
    ap.add_argument("--no-ghidra", action="store_true")
    args = ap.parse_args(argv)

    import capstone
    import astra_seats
    import build
    import callee_protos
    import eligibility
    import re_log

    data = open(build.EXE, "rb").read()
    text = build.pe_sections(data)[0]
    lo = text["rva"]
    raw = data[text["raw_pointer"]:text["raw_pointer"] + text["size"]]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    rows = [r for r in eligibility.load_rows()
            if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x")]
    rows_by_end = {int(r["target_rva"], 16) + int(r["target_size"] or 0): r for r in rows}
    callers = callee_protos.call_sites()
    url = None if args.no_ghidra else args.url
    gaps = astra_seats.find_gaps()
    records = re_log.latest_records()
    mapped = [classify(g, raw, lo, md, rows_by_end, callers, url, records) for g in gaps]
    if args.top:
        for m in mapped[:args.top]:
            print(f"{m['gap_start']}..{m['gap_end']} {m['code_bytes']:6} B  {m['kind']:9} {m['evidence']}")
            if m["starts"]:
                print(f"    starts: {m['starts']}")
            if m["ghidra_starts"]:
                print(f"    ghidra: {m['ghidra_starts']}")
            if m["verdicts"]:
                print(f"    verdicts: {m['verdicts']}")
        return 0
    with OUT.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(mapped)
    from collections import Counter
    kinds = Counter()
    for m in mapped:
        kinds[m["kind"]] += int(m["code_bytes"])
    print(f"map_gaps: {len(mapped)} gaps, {sum(kinds.values()):,} B -> {OUT.relative_to(ROOT).as_posix()}")
    for kind, size in kinds.most_common():
        print(f"  {kind:10} {size:8,} B  {sum(1 for m in mapped if m['kind'] == kind):4} gaps")
    # By the largest overlapping verdict body: partial/blocked gaps are proven
    # bodies (or proven data) awaiting conversion, the rest is still unexplored.
    state = Counter()
    count = Counter()
    for m in mapped:
        found = [v.split(":") for v in m["verdicts"].split()]
        key = f"verdict {max(found, key=lambda v: int(v[1]))[2]}" if found else f"open {m['kind']}"
        state[key] += int(m["code_bytes"])
        count[key] += 1
    print("  by state:")
    for key, size in state.most_common():
        print(f"    {key:22} {size:8,} B  {count[key]:4} gaps")
    return 0


if __name__ == "__main__":
    sys.exit(main())
