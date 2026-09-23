#!/usr/bin/env python3
"""Serve the unclaimed-.text census to analyst seats (gpt-6-astra + Ghidra).

build/gap_census.py proves 4,166 function starts inside the gaps that hold no
ledger row (834 KB of the 994 KB unclaimed on 2026-09-23); 374 of them are
600-2,500 B (446 KB) and about 150 KB sit in vtables whose class the ledger
already names. No picker served any of these: eligibility only sees ledger rows
and carved.csv. This one briefs census bodies three per seat, warmest evidence
first (vtable slot of a known class > direct call target > Ghidra entry), with
the gap-analyst instructions: prove the boundary yourself, identify through the
vtable slot order of the ZH twin header or a caller, land with add_match (a NEW
row), bank the rest.

  python build/gap_census.py                       # refresh the census first
  python tools/fleet/gap_seats.py N [min_b] [max_b] [--cap-hours H] [--dry]
"""
import argparse
import csv
import json
import os
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/fleet"))
MODEL = os.environ.get("HUB_MODEL", "gpt-6-astra")
EFFORT = os.environ.get("HUB_EFFORT", "xhigh")

NOTE = """UNCLAIMED BODIES. None of these addresses has a ledger row: no seat was ever served them, there is no dump to
replace and no prior bank unless re_attempts.log says so. Each line gives the start evidence (a REL32 call/jmp target,
a vtable slot, a data pointer, a Ghidra entry, or a prologue right after int3 padding) and an ESTIMATED extent to the
next proved start; the real end is the ret/tail-jmp followed by int3 padding, which you must find yourself
(capstone over baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe; file offset == RVA in .text). Never claim
bytes you did not decode. IDENTITY: where the line names a vtable and class, the slot index maps to the virtual in
declaration order of the class's Zero Hour header (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include);
python tools/vtable_lookup.py 0xVT prints the landed siblings; python tools/fleet/context_pack.py 0xRVA prints callers,
strings, layout witnesses; python tools/ghidra_decompile.py 0xRVA prints a control-flow DRAFT (names/types invented). A
sibling's landed source is the best start. When identity is proved, use the real mangled name; otherwise opaque
address-derived names (Rva0XXXXXXXX tokens), never plausible guesses. LAND when EXACT with python tools/add_match.py
"MANGLED" 0xRVA SIZE Code/.../File.cpp --notes "<evidence>" (new row; AGENTS.md 'File placement'; a sibling's file is a
fine home if every row it holds still verifies with bash build.sh FILE). Otherwise BANK: python tools/re_log.py record
"MANGLED" 0xRVA SIZE partial "<evidence> t=<min>min model={model}-{effort}" --stash FILE --score MEASURED, MEASURED =
max(0, 1 - (differing bytes + 2 x |ours - retail|) / SIZE). Measure with python tools/probe.py SRC "MANGLED" 0xRVA;
structure first (prologue/frame, EH, call sequence), then registers. Natural C++ only: no naked, no __emit, no
volatile shaping. Never run git. No full gate, never launch the game. Do not edit tools/ or docs/ or reverse/*.csv by
hand. Hard cap {cap} hours; bank every body before you stop."""


def codex_command(cap_seconds):
    return ["timeout", "-k", "60", str(cap_seconds), "codex", "exec", "-m", MODEL, "-c",
            'model_reasoning_effort="%s"' % EFFORT, "--sandbox", "danger-full-access", "--cd", str(ROOT), "-"]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("seats", type=int)
    ap.add_argument("min_b", type=int, nargs="?", default=600)
    ap.add_argument("max_b", type=int, nargs="?", default=2500)
    ap.add_argument("--per-session", type=int, default=3)
    ap.add_argument("--cap-hours", type=float, default=3.0)
    ap.add_argument("--dry", action="store_true")
    a = ap.parse_args()
    import eligibility
    census = ROOT / "build/gap_census.csv"
    if not census.exists():
        sys.exit("run python build/gap_census.py first")
    slots = {}
    vj = ROOT / "build/gap_vtable_slots.json"
    if vj.exists():
        for e in json.loads(vj.read_text()):
            rva = int(e["rva"], 16)
            if rva not in slots or not e["cls"].startswith(("Rva", "Gen_", "Bfme", "PAV", "PBU", "T2", "K")):
                slots[rva] = e
    rows = {eligibility.rva_of(r) for r in eligibility.load_rows() if eligibility.rva_of(r) is not None}
    busy = eligibility.busy_rvas(ROOT) | eligibility.recent_run_rvas(48, ROOT)
    attempts = eligibility.attempt_counts()
    cands = []
    with census.open(newline="") as fh:
        for r in csv.DictReader(fh):
            rva, size, ev = int(r["rva"], 16), int(r["size"]), r["evidence"].split("|")
            if not (a.min_b <= size <= a.max_b) or rva in rows or f"0x{rva:08x}" in busy:
                continue
            if attempts.get(rva, 0) >= eligibility.ATTEMPT_CAP:
                continue
            s = slots.get(rva)
            known = s is not None and not s["cls"].startswith(("Rva", "Gen_", "Bfme", "PAV", "PBU", "T2", "K", "_STL"))
            warmth = (4 if known else 2 if s else 0) + (2 if "call" in ev else 0) + (1 if "ghidra" in ev else 0) \
                + (1 if "prologue_after_int3" in ev else 0) - attempts.get(rva, 0)
            cands.append((warmth, size, rva, ev, s))
    # warm first, then bytes; neighbours in one seat share context, so group by address after ranking the seeds
    cands.sort(key=lambda c: (-c[0], -c[1]))
    picked = cands[: a.seats * a.per_session]
    picked.sort(key=lambda c: c[2])
    groups = [picked[i:i + a.per_session] for i in range(0, len(picked), a.per_session)]
    if a.dry:
        for g in groups:
            for w, size, rva, ev, s in g:
                print(f"0x{rva:08X} {size:5} B warmth={w} {'|'.join(ev)} {s['cls'] + ' slot ' + str(s['slot']) + ' vt ' + s['vt'] if s else ''}")
            print("--")
        return
    import fleet_run
    procs = []
    stamp = time.strftime("%H%M")
    for i, g in enumerate(groups):
        seat = chr(ord("A") + i)
        lines = [NOTE.format(model=MODEL, effort=EFFORT, cap=a.cap_hours), "", "TARGETS"]
        for w, size, rva, ev, s in g:
            hint = f"vtable {s['vt']} slot {s['slot']} class {s['cls']}" if s else "no vtable slot found"
            lines.append(f"- 0x{rva:08X} {size}B ?d_{rva:08x}@@YAXXZ (unclaimed; start evidence {'|'.join(ev)}; extent estimated; {hint})")
        brief = ROOT / "build" / f"brief_gapseat_{stamp}_{seat}.txt"
        brief.write_text("\n".join(lines) + "\n", encoding="utf-8")
        log = ROOT / "build" / "fleet_logs" / f"seat_astragap{seat}_{stamp}.log"
        cmd = [sys.executable, str(ROOT / "tools/fleet_run.py"), "--brief", str(brief), "--log", str(log),
               "--engine", "astrags", "--seat", seat, "--", *codex_command(int(a.cap_hours * 3600))]
        procs.append(subprocess.Popen(cmd, cwd=ROOT, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL))
        print(f"seat {seat}: " + " ".join(f"0x{c[2]:08X}({c[1]}B)" for c in g), flush=True)
        time.sleep(3)
    for p in procs:
        p.wait()
    print("all seats ended", flush=True)


if __name__ == "__main__":
    main()
