#!/usr/bin/env python3
"""Hub-and-neighbours conversion with the analyst model (gpt-6-astra) and Ghidra.

Measured 2026-09-21 on 0x003E8E10: one analyst session on a 1.8 KB hub did not
land it (codegen wall) but its layouts and callee contracts let three
follow-up sessions land 4 of the hub's 7 open callers/callees byte-exact in
15-45 minutes each. Large bodies are analysis hubs; their neighbours are the
landing targets.

  python tools/fleet/hub_cluster.py 0xHUB analyse     # phase 1: analyst session -> docs/analysis/<hub>.md
  python tools/fleet/hub_cluster.py 0xHUB neighbours  # phase 2: 2-3 open neighbours per session, analyst pack attached
  python tools/fleet/hub_cluster.py --rank            # hubs by open bytes among direct callers/callees

Every session goes through tools/fleet_run.py (leases, run records, touched
targets). Nothing here runs git; harvest.py publishes what lands.
"""
import argparse
import os
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "fleet"))
MODEL = os.environ.get("HUB_MODEL", "gpt-6-astra")
EFFORT = os.environ.get("HUB_EFFORT", "xhigh")

HUB_BRIEF = """ROLE. You are the analyst. One hub body, one bounded session (hard cap {cap} hours). The hub itself is NOT expected to
land: its value is the analysis that lets its open callers and callees land afterwards. Read AGENTS.md first; it binds you.

HUB. RVA 0x{rva:08X}, {size} bytes, ledger name {name}. {history}
Open neighbours this analysis must serve (they get sessions next): {neighbours}.

TOOLS. python tools/ghidra_decompile.py --out build/hub_{rva:08x}/ghdec 0xRVA 0xRVA ... (about 10 s per call; batch).
Decompiled C is a DRAFT: control flow, call order, argument passing, loops, EH states. Names and types are invented and
never proof. python tools/callees.py 0x{rva:08X} {size} lists every callee; python tools/fleet/context_pack.py 0xRVA prints
callers, strings, vtable, layout witnesses. python tools/bfme_layout.py CLASS for witnessed BFME layouts.

DELIVERABLES, in this order, under build/hub_{rva:08x}/:
1. ANALYSIS.md (a) CONTROL FLOW as numbered blocks with retail offsets, every call with its arguments, loops, exits, EH
   states; (b) LAYOUTS: one table per object touched (this, arguments, callee results): offset, width, r/w, witnessing
   instruction offsets, meaning ONLY where a landed source, a pin, bfme_layout.py or a string proves it, else "unknown";
   (c) CALLEE CONTRACTS for every distinct callee: address, thunk target, convention, stack args, cleanup, ECX, return as
   used, evidence, "proved"/"assumed"; (d) IDENTITY: what callers prove; no guessed names; (e) NEIGHBOUR NOTES: for each
   open neighbour listed above, which layouts/contracts apply and what the hub proves about its signature.
2. body.cpp: a COMPLETE reconstruction (every call, every branch, the real prologue and frame). Opaque address-derived
   names where identity is not proved. Measure: python tools/probe.py body.cpp "MANGLED" 0x{rva:08X}. Iterate on the
   FIRST divergence with structure first (prologue/frame, call sequence, size). Log every probe in PROGRESS.md.
3. Bank the best body before you stop: python tools/re_log.py record "{name}" 0x{rva:08X} {size} partial "<evidence>
   t=<min>min model={model}-{effort}" --stash build/hub_{rva:08x}/body.cpp --score <measured> where measured =
   max(0, 1 - (differing bytes + 2 x |ours - retail|) / {size}). If EXACT, land it with tools/add_match.py (source under an
   official Code/ path, AGENTS.md 'File placement').
4. REPORT.md: what was proved, what the decompiler got wrong, the biggest remaining obstacle, minutes per deliverable.

RULES. Never run git. No full gate, no whole-tree build, never launch the game. Do not edit tools/ or docs/. Stop at
{cap} hours; an honest report and a banked body are the result.
"""

PACK_NOTE = ("ANALYST PACK. An analyst session reverse-engineered the neighbouring hub body 0x{rva:08X} and wrote "
             "docs/analysis/0x{rva:08x}.md. READ ITS 'LAYOUTS', 'CALLEE CONTRACTS' and 'NEIGHBOUR NOTES' FIRST: they give, "
             "with instruction-level witnesses, the object layouts and the proved calling convention, argument count, stack "
             "cleanup and return width of the hub's callees, and what the hub proves about each of these bodies. Use them "
             "instead of rediscovering them; the names in them are opaque on purpose. The Ghidra decompiler is installed: "
             "python tools/ghidra_decompile.py 0xRVA [0xRVA ...] prints a control-flow DRAFT (about 10 s per call; names and "
             "types are invented, never proof). Get the WHOLE body first (every call in retail order, the right prologue and "
             "frame size), then work the first divergence with probe.py. Opaque address-derived names are required where "
             "identity is not proved. Land with add_match.py when EXACT; otherwise ALWAYS bank your best body with re_log.py "
             "partial --stash --score using the MEASURED score 1 - (differing bytes + 2 x |ours - retail|) / retail size.")


def neighbours_of(rva, size, opens, lo=200, hi=1200):
    """Open dump bodies of lo..hi bytes that the hub calls or that call it (through ILT thunks too)."""
    import capstone
    import build
    import context_pack
    context_pack._load()
    rows = context_pack._rows
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    text = context_pack._secs[0]
    tlo, thi = text['rva'], text['rva'] + text['size']
    body = context_pack._exe[build.rva_to_file_offset(context_pack._secs, rva):][:size]
    out = set()
    for ins in md.disasm(body, rva):
        if ins.mnemonic in ('call', 'jmp') and ins.op_str.startswith('0x'):
            tgt = int(ins.op_str, 16)
            if tlo <= tgt < thi and not (rva <= tgt < rva + size):
                thunk = context_pack.thunk_target(tgt) if tgt in rows and int(rows[tgt]['target_size'] or 0) == 5 else None
                out.add(thunk if thunk is not None else tgt)
    sites = set(context_pack._calls.get(rva, []))
    for th in context_pack._thunks_of.get(rva, []):
        sites |= set(context_pack._calls.get(th, []))
    for site in sites:
        owner = context_pack.owner(site)
        if owner:
            out.add(int(owner['target_rva'], 16))
    return sorted(n for n in out - {rva} if n in opens and lo <= opens[n] <= hi)


def codex_command(cap_seconds):
    return ["timeout", "-k", "60", str(cap_seconds), "codex", "exec", "-m", MODEL, "-c",
            'model_reasoning_effort="%s"' % EFFORT, "--sandbox", "danger-full-access", "--cd", str(ROOT), "-"]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("hub", nargs="?")
    ap.add_argument("phase", nargs="?", choices=["analyse", "neighbours"])
    ap.add_argument("--rank", action="store_true")
    ap.add_argument("--cap-hours", type=float, default=3.0)
    ap.add_argument("--per-session", type=int, default=3)
    ap.add_argument("--dry", action="store_true")
    a = ap.parse_args()
    import eligibility
    import re_log
    latest = eligibility.latest_verdicts()
    att = eligibility.attempt_counts()
    opens = {eligibility.rva_of(r): int(r["target_size"] or 0) for r in eligibility.open_dumps(latest=latest)}
    rows = {eligibility.rva_of(r): r for r in eligibility.load_rows() if eligibility.rva_of(r) is not None}
    if a.rank:
        hubs = []
        for rva, size in opens.items():
            if size >= 1200:
                nb = neighbours_of(rva, size, opens)
                if len(nb) >= 3:
                    hubs.append((sum(opens[n] for n in nb), len(nb), rva, size, att.get(rva, 0)))
        for total, n, rva, size, tried in sorted(hubs, reverse=True)[:15]:
            print(f"{total / 1024:6.1f} KB in {n:2} open neighbours  hub 0x{rva:08X} {size:5} B  attempts {tried}")
        return
    if not a.hub or not a.phase:
        ap.error("hub and phase required")
    rva = int(a.hub, 16)
    size = opens.get(rva) or int(rows[rva]["target_size"])
    name = rows[rva]["name"]
    nb = neighbours_of(rva, size, opens)
    work = ROOT / "build" / f"hub_{rva:08x}"
    if a.phase == "analyse":
        rec = re_log.latest_records().get(rva)
        hist = f"{att.get(rva, 0)} prior verdict(s); latest: {rec[3]}: {rec[4][:300]}" if rec else "No prior verdicts."
        stash = eligibility.stash(rva)
        if stash:
            hist += f" Banked stash: {stash[0].relative_to(ROOT).as_posix()} (author score {stash[1]}; measure it first)."
        text = HUB_BRIEF.format(cap=a.cap_hours, rva=rva, size=size, name=name, history=hist, model=MODEL, effort=EFFORT,
                                neighbours=", ".join(f"0x{n:08X} ({opens[n]} B)" for n in nb))
        text += f"\nTARGETS\n- 0x{rva:08X} {size}B {name}\n"    # fleet_run leases what the brief lists
        if a.dry:
            print(text)
            return
        work.mkdir(parents=True, exist_ok=True)
        import fleet_run
        brief = ROOT / "build" / f"brief_hub_{rva:08x}.txt"
        brief.write_text(text, encoding="utf-8")
        log = ROOT / "build" / "fleet_logs" / f"seat_astrahubH_{rva:08x}.log"
        code = fleet_run.execute(ROOT, brief, log, "astrahub", "H", codex_command(int(a.cap_hours * 3600)))
        if (work / "ANALYSIS.md").exists():
            doc = ROOT / "docs" / "analysis" / f"0x{rva:08x}.md"
            doc.parent.mkdir(exist_ok=True)
            parts = [f"# Analyst hub: 0x{rva:08X} ({MODEL} with Ghidra, {time.strftime('%Y-%m-%d')})\n"]
            for f in ("REPORT.md", "ANALYSIS.md"):
                if (work / f).exists():
                    parts.append((work / f).read_text(encoding="utf-8", errors="replace"))
            doc.write_text("\n\n---\n\n".join(parts), encoding="utf-8")
            print("wrote", doc.relative_to(ROOT).as_posix())
        sys.exit(code)
    # neighbours: largest first, a few per session, each session its own process so they run in parallel
    nb.sort(key=lambda n: -opens[n])
    groups = [nb[i:i + a.per_session] for i in range(0, len(nb), a.per_session)]
    if a.dry:
        for g in groups:
            print([f"0x{n:08X}" for n in g])
        return
    procs = []
    for i, g in enumerate(groups):
        seat = chr(ord("A") + i)
        brief = ROOT / "build" / f"brief_hub_{rva:08x}_{seat}.txt"
        with brief.open("w", encoding="utf-8") as out:
            subprocess.run([sys.executable, str(ROOT / "tools/brief.py"), "--rvas", *[f"0x{n:08X}" for n in g],
                            "--model", f"{MODEL}-{EFFORT}", "--limit", str(a.per_session), "--note", PACK_NOTE.format(rva=rva)],
                           cwd=ROOT, stdout=out, check=True)
        log = ROOT / "build" / "fleet_logs" / f"seat_astranb{seat}_{rva:08x}.log"
        cmd = [sys.executable, str(ROOT / "tools/fleet_run.py"), "--brief", str(brief), "--log", str(log),
               "--engine", "astranb", "--seat", seat, "--", *codex_command(int(a.cap_hours * 3600))]
        procs.append(subprocess.Popen(cmd, cwd=ROOT, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL))
        print(f"seat {seat}: {' '.join(f'0x{n:08X}' for n in g)}")
        time.sleep(3)
    for p in procs:
        p.wait()


if __name__ == "__main__":
    main()
