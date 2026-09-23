#!/usr/bin/env python3
"""Unclaimed-gap conversion with the analyst model (gpt-6-astra) and Ghidra.

About 1.0 MB of retail .text has no ledger row at all (tools/gaps.py): 425 KB
in 343 gaps of 600-2,500 real bytes, 410 KB in 81 gaps above that (giant
functions and code Ghidra never found), the rest small remnants.
carve_unclaimed.py only emits candidates with positive boundary evidence, so
most of these bytes never reach a seat. This runs an analyst on one gap:
enumerate the functions in it, prove their boundaries, land what is exact,
bank the rest, and leave a FUNCTIONS.csv the follow-up phase serves.

  python tools/fleet/gap_cluster.py --rank                 # gaps by real bytes, with Ghidra entries
  python tools/fleet/gap_cluster.py 0xSTART 0xEND analyse  # phase 1: one analyst session on the gap
  python tools/fleet/gap_cluster.py 0xSTART 0xEND functions  # phase 2: sessions on FUNCTIONS.csv entries 200-1500 B
"""
import argparse
import bisect
import csv
import os
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/fleet"))
MODEL = os.environ.get("HUB_MODEL", "gpt-6-sol")
EFFORT = os.environ.get("HUB_EFFORT", "medium")
EXE = ROOT / "baselines/bfme1/workshop-vanilla-1.03/files/lotrbfme.exe"
TEXT_START, TEXT_END = 0x1000, 0x1000 + 13049856

GAP_BRIEF = """ROLE. You are the analyst for one UNCLAIMED region of retail .text: no ledger row covers it, so no seat has ever
been served any of it. One bounded session (hard cap {cap} hours). Read AGENTS.md first; it binds you.

GAP. RVA 0x{start:08X} .. 0x{end:08X} ({span} bytes, {real} non-0xCC bytes). Ghidra lists {n_gh} function entries inside:
{gh_list}
Ghidra sizes stop short of the epilogue and it misses functions with aligned-stack prologues (push ebx / mov ebx,esp /
and esp,-16); treat its entries as advisory starts only. Neighbouring landed rows: {neighbours}.

TOOLS. python tools/ghidra_decompile.py --out build/gap_{start:08x}/ghdec 0xRVA 0xRVA ... (about 10 s per call; batch).
Decompiled C is a DRAFT: control flow, call order, argument passing, loops, EH states. Names and types are invented and
never proof. python tools/fleet/context_pack.py 0xRVA prints callers, strings, vtable slots and layout witnesses for any
address. python tools/callees.py 0xRVA SIZE lists callees. python tools/bfme_layout.py CLASS for witnessed BFME layouts.
Read raw bytes with capstone from {exe} (file offset == RVA in .text). A function START is proved by a REL32 call/jmp
target, a vtable slot, or a decoded prologue right after an int3/ret run; an END by ret or tail jmp followed by int3
padding or the next proved start.

DELIVERABLES, in this order, under build/gap_{start:08x}/:
1. FUNCTIONS.csv with header rva,size,start_evidence,end_evidence,callers,vtable,class_hint: EVERY function in the gap
   with a proved start and end, in address order. class_hint only when a vtable install or a landed caller proves it;
   else empty. Gaps you cannot decode (jump tables, data, unreachable bytes) go in GAP.md with the reason.
2. LAND what you can, largest first, natural C++ only: for each function write a source under an official Code/ path
   (AGENTS.md 'File placement'), measure with python tools/probe.py SRC "MANGLED" 0xRVA, and when EXACT run
   python tools/add_match.py "MANGLED" 0xRVA SIZE SRC --notes "<evidence>" (a new row: nothing to replace). Opaque
   address-derived names where identity is not proved (Rva0XXXXXXXX tokens); no plausible guessed names.
3. BANK the rest: python tools/re_log.py record "?d_XXXXXXXX@@YAXXZ" 0xRVA SIZE partial "<evidence> t=<min>min
   model={model}-{effort}" --stash build/gap_{start:08x}/body_XXXXXXXX.cpp --score <measured>, measured =
   max(0, 1 - (differing bytes + 2 x |ours - retail|) / SIZE). Log every probe in PROGRESS.md.
4. GAP.md: layouts and callee contracts you proved (offset, width, witnessing instructions, "proved"/"assumed"), what
   the region is (which class, which subsystem, from strings and vtables), the biggest obstacle, minutes per function.

RULES. Never run git. No full gate, no whole-tree build, never launch the game. Do not edit tools/, docs/ or any
reverse/*.csv by hand (add_match and re_log are the only ledger paths). Never add rows for bytes you did not decode.
Stop at {cap} hours; FUNCTIONS.csv, an honest GAP.md and banked bodies are the result.
"""

FUNC_NOTE = ("GAP ANALYST PACK. An analyst session mapped the unclaimed region 0x{start:08X}..0x{end:08X} and wrote "
             "build/gap_{start:08x}/GAP.md and FUNCTIONS.csv: proved function boundaries, callers, vtable slots, layouts and "
             "callee contracts with instruction-level witnesses. READ GAP.md FIRST. These bodies have NO ledger row: when a "
             "body is EXACT, land it with python tools/add_match.py \"MANGLED\" 0xRVA SIZE SRC --notes \"...\" (a new row, "
             "nothing to replace); otherwise bank with python tools/re_log.py record \"?d_XXXXXXXX@@YAXXZ\" 0xRVA SIZE partial "
             "\"...\" --stash FILE --score MEASURED. The Ghidra decompiler is installed: python tools/ghidra_decompile.py 0xRVA "
             "prints a control-flow DRAFT (names and types invented, never proof). python tools/fleet/context_pack.py 0xRVA "
             "prints callers, strings, vtable slots. Opaque address-derived names where identity is not proved.")


def gaps():
    data = EXE.read_bytes()
    iv = []
    with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace") as fh:
        for r in csv.DictReader(fh):
            if r["status"] != "matched" or not r["target_rva"].lower().startswith("0x"):
                continue
            s = int(r["target_rva"], 16)
            iv.append((s, s + int(r["target_size"] or 0), r["name"]))
    iv.sort()
    merged, out = [], []
    for s, e, _ in iv:
        if merged and s <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], e)
        else:
            merged.append([s, e])
    prev = TEXT_START
    for s, e in merged:
        if s > prev:
            out.append((prev, s))
        prev = max(prev, e)
    if prev < TEXT_END:
        out.append((prev, TEXT_END))
    scored = []
    for s, e in out:
        chunk = data[s:e]
        real = len(chunk) - chunk.count(0xCC)
        if real > 0:
            scored.append((real, s, e))
    return scored, iv


def ghidra_inside(s, e):
    rows = []
    with open(ROOT / "reverse/ghidra_functions.csv", newline="") as fh:
        for r in csv.DictReader(fh):
            a = int(r["rva"], 16)
            if s <= a < e:
                rows.append((a, int(r["size"] or 0), r["name"]))
    return rows


def codex_command(cap_seconds):
    return ["timeout", "-k", "60", str(cap_seconds), "codex", "exec", "-m", MODEL, "-c",
            'model_reasoning_effort="%s"' % EFFORT, "--sandbox", "danger-full-access", "--cd", str(ROOT), "-"]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("start", nargs="?")
    ap.add_argument("end", nargs="?")
    ap.add_argument("phase", nargs="?", choices=["analyse", "functions"])
    ap.add_argument("--rank", action="store_true")
    ap.add_argument("--cap-hours", type=float, default=3.0)
    ap.add_argument("--per-session", type=int, default=3)
    ap.add_argument("--dry", action="store_true")
    a = ap.parse_args()
    scored, iv = gaps()
    if a.rank:
        print("  real   span   ghidra(mid 200-1500B / all)   gap")
        for real, s, e in sorted(scored, reverse=True)[:40]:
            gh = ghidra_inside(s, e)
            mid = [g for g in gh if 200 <= g[1] <= 1500]
            print(f"{real:7,} {e - s:7,}   {len(mid):3} / {len(gh):3}   0x{s:08X}..0x{e:08X}")
        return
    if not (a.start and a.end and a.phase):
        ap.error("start end phase required")
    s, e = int(a.start, 16), int(a.end, 16)
    work = ROOT / "build" / f"gap_{s:08x}"
    if a.phase == "analyse":
        data = EXE.read_bytes()
        chunk = data[s:e]
        gh = ghidra_inside(s, e)
        starts = [x[0] for x in iv]
        i = bisect.bisect_left(starts, s)
        nb = [f"0x{r[0]:08X} {r[2]}" for r in iv[max(0, i - 2):i]] + [f"0x{r[0]:08X} {r[2]}" for r in iv[i:i + 2]]
        text = GAP_BRIEF.format(cap=a.cap_hours, start=s, end=e, span=e - s, real=len(chunk) - chunk.count(0xCC),
                                n_gh=len(gh), gh_list="\n".join(f"  0x{x[0]:08X} {x[1]} B {x[2]}" for x in gh) or "  (none)",
                                neighbours="; ".join(nb), exe=EXE.relative_to(ROOT).as_posix(), model=MODEL, effort=EFFORT)
        # fleet_run leases what the brief lists; lease the region as one pseudo-target
        text += f"\nTARGETS\n- 0x{s:08X} {e - s}B unclaimed region 0x{s:08X}..0x{e:08X}\n"
        if a.dry:
            print(text)
            return
        work.mkdir(parents=True, exist_ok=True)
        import fleet_run
        brief = ROOT / "build" / f"brief_gap_{s:08x}.txt"
        brief.write_text(text, encoding="utf-8")
        log = ROOT / "build" / "fleet_logs" / f"seat_astragapG_{s:08x}.log"
        code = fleet_run.execute(ROOT, brief, log, "astragap", "G", codex_command(int(a.cap_hours * 3600)))
        if (work / "GAP.md").exists():
            doc = ROOT / "docs" / "analysis" / f"gap_0x{s:08x}.md"
            doc.parent.mkdir(exist_ok=True)
            parts = [f"# Gap analyst: 0x{s:08X}..0x{e:08X} ({MODEL} with Ghidra, {time.strftime('%Y-%m-%d')})\n"]
            for f in ("GAP.md", "FUNCTIONS.csv"):
                if (work / f).exists():
                    body = (work / f).read_text(encoding="utf-8", errors="replace")
                    parts.append(body if f.endswith(".md") else "## FUNCTIONS.csv\n\n```\n" + body + "\n```\n")
            doc.write_text("\n\n---\n\n".join(parts), encoding="utf-8")
            print("wrote", doc.relative_to(ROOT).as_posix())
        sys.exit(code)
    # functions: bodies the analyst proved, still without a ledger row, 200-1500 B, largest first
    funcs = []
    with open(work / "FUNCTIONS.csv", newline="", encoding="utf-8", errors="replace") as fh:
        for r in csv.DictReader(fh):
            try:
                rva, size = int(r["rva"], 16), int(r["size"])
            except (KeyError, ValueError):
                continue
            if 200 <= size <= 1500:
                funcs.append((rva, size, r))
    claimed = {x[0] for x in iv}
    funcs = [f for f in funcs if f[0] not in claimed]
    funcs.sort(key=lambda f: -f[1])
    groups = [funcs[i:i + a.per_session] for i in range(0, len(funcs), a.per_session)]
    if a.dry:
        for g in groups:
            print([f"0x{f[0]:08X} {f[1]}B" for f in g])
        return
    procs = []
    for i, g in enumerate(groups):
        seat = chr(ord("A") + i)
        brief = ROOT / "build" / f"brief_gap_{s:08x}_{seat}.txt"
        lines = [FUNC_NOTE.format(start=s, end=e), "", "RULES. Never run git. No full gate, never launch the game. Natural C++ only. "
                 f"Hard cap {a.cap_hours} hours; bank before you stop.", "", "TARGETS"]
        for rva, size, r in g:
            lines.append(f"- 0x{rva:08X} {size}B ?d_{rva:08x}@@YAXXZ (unclaimed; {r.get('start_evidence', '')}; {r.get('end_evidence', '')}; "
                         f"callers {r.get('callers', '')}; vtable {r.get('vtable', '')}; class {r.get('class_hint', '')})")
        brief.write_text("\n".join(lines) + "\n", encoding="utf-8")
        log = ROOT / "build" / "fleet_logs" / f"seat_astragf{seat}_{s:08x}.log"
        cmd = [sys.executable, str(ROOT / "tools/fleet_run.py"), "--brief", str(brief), "--log", str(log),
               "--engine", "astragf", "--seat", seat, "--", *codex_command(int(a.cap_hours * 3600))]
        procs.append(subprocess.Popen(cmd, cwd=ROOT, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL))
        print(f"seat {seat}: {' '.join(f'0x{f[0]:08X}' for f in g)}")
        time.sleep(3)
    for p in procs:
        p.wait()


if __name__ == "__main__":
    main()
