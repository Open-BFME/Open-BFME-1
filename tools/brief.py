#!/usr/bin/env python3
"""Write a worker brief from the LIVE ledger, so no worker is ever sent stale work.

Every brief hand-written on 2026-09-02 that listed RVAs from an older report sent
workers to bodies other lanes had already landed. This regenerates the target
list at the moment of writing and drops anything that no longer points at a
dump row, then attaches what the ledger knows per body: size, pins, the latest
attempt's evidence and stash, and the ZH twin when the sweep found one.

  python3 tools/brief.py --dump Code/gen_asm/d_0023c310.asm            > brief.txt
  python3 tools/brief.py --rvas 0x002FDDB0 0x002FC4C0 --note "..."      > brief.txt
  python3 tools/brief.py --csv reverse/zh_sweep/big_identified_worklist.csv --limit 12 > brief.txt

Then launch it with the engine of your choice, e.g.
  grok -p "$(cat brief.txt)" --always-approve --output-format plain
  codex exec -m gpt-5.6-sol --sandbox danger-full-access "$(cat brief.txt)"

Read-only. Writes nothing but stdout.
"""
import argparse
import csv
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

METHOD = """
METHOD. Read AGENTS.md, docs/matching.md and docs/shape_levers.md first. For each
target: confirm the row still points at a .asm dump (`grep ,0xRVA, reverse/functions.csv`);
grep reverse/symbols.csv and reverse/re_attempts.log for the RVA; use
`python3 tools/vtable_lookup.py <vtable VA>` for owning-class questions; port from the
Zero Hour twin under reference/CnC_Generals_Zero_Hour when one is named. Iterate with
`python3 tools/probe.py SOURCE.cpp "MANGLED" 0xRVA` -- it compiles, diffs against retail
with relocations masked, and prints a CANDIDATE cause with evidence; treat the label as
a hint and check the evidence lines. Land with
`python3 tools/add_match.py NAME 0xRVA SIZE SOURCE --replace-rva 0xRVA --notes "no commas"`
(byte-verifies, auto-reverts, may wait on the ledger lock -- that is normal). If a body
resists after ~40 minutes bank it:
`python3 tools/re_log.py record SYM 0xRVA SIZE partial "evidence t=Xmin model=MODEL" --stash FILE.cpp --score 0.NN`
and move on.
HARD RULES: never run git commands (the orchestrator owns VCS); never run a full ./build.sh;
never edit files under Code/gen_asm/; only touch your assigned bodies; new sources go in
the class's home directory under Code/ with descriptive names.
REPORT at the end: bodies landed (name rva size), partials banked, total bytes.
"""


def load():
    rows = {}
    for r in csv.DictReader(open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace")):
        try:
            rows[int(r["target_rva"], 16)] = r
        except ValueError:
            pass
    pins = {}
    for r in csv.reader(open(ROOT / "reverse/symbols.csv", newline="", encoding="utf-8", errors="replace")):
        if len(r) > 1 and r[1].startswith("0x"):
            try:
                pins.setdefault(int(r[1], 16), []).append((r[0], r[2] if len(r) > 2 else ""))
            except ValueError:
                pass
    latest = {}
    for l in open(ROOT / "reverse/re_attempts.log", encoding="utf-8", errors="replace"):
        p = l.rstrip("\n").split("\t")
        if len(p) >= 5:
            try:
                latest[int(p[1], 16)] = p
            except ValueError:
                pass
    near = {}
    mj = ROOT / "build/zh_sweep/match.json"
    if mj.exists():
        try:
            for e in json.load(open(mj)):
                if e.get("bucket") == "near":
                    near.setdefault(e["rva"], e["sym"] + " from " + e["source"])
        except Exception:
            pass
    return rows, pins, latest, near


def describe(rva, rows, pins, latest, near):
    r = rows[rva]
    parts = [f"- 0x{rva:08X} {r['target_size']}B {r['name']} (dump {Path(r['source']).name})"]
    real = [n for n, _ in pins.get(rva, []) if not re.match(r"^\?(d_|b_|j_|dup_)", n)]
    if real:
        parts.append(f"    pins: {'; '.join(real[:3])}")
    p = latest.get(rva)
    if p and p[3] in ("partial", "blocked"):
        ev = p[4]
        st = re.search(r"stash=(\S+)", ev)
        sc = re.search(r"score=([0-9.]+)", ev)
        parts.append(f"    last attempt ({p[3]}{', score ' + sc.group(1) if sc else ''}): {ev[:220]}")
        if st and (ROOT / st.group(1)).exists():
            parts.append(f"    START FROM STASH: {st.group(1)}")
    if rva in near:
        parts.append(f"    ZH twin: {near[rva]}")
    # mechanical evidence (callees, callers, vtable slot, strings, fields,
    # landed neighbours) so the session does not spend its first half hour
    # re-deriving it from the bytes; never let it break a brief
    try:
        sys.path.insert(0, str(ROOT / "tools/fleet"))
        import context_pack
        parts += ["    " + l for l in context_pack.pack(rva)[1:]]
    except Exception as e:  # noqa: BLE001
        parts.append(f"    (context pack unavailable: {e})")
    return "\n".join(parts)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dump", help="assign every remaining dump row in this gen_asm file")
    ap.add_argument("--rvas", nargs="*", help="explicit RVAs")
    ap.add_argument("--csv", help="worklist CSV with an 'rva' column")
    ap.add_argument("--limit", type=int, default=30)
    ap.add_argument("--note", default="", help="extra context placed at the top")
    ap.add_argument("--model", default="MODEL", help="model tag for re_log evidence")
    a = ap.parse_args()

    rows, pins, latest, near = load()
    targets = []
    if a.dump:
        want = a.dump.replace("\\", "/")
        targets = [rva for rva, r in rows.items() if r["source"].replace("\\", "/") == want]
        targets.sort(key=lambda v: int(rows[v]["target_size"]))
    if a.rvas:
        targets += [int(x, 16) for x in a.rvas]
    if a.csv:
        for r in csv.DictReader(open(a.csv, newline="")):
            targets.append(int(r["rva"], 16))

    live, dropped = [], []
    for rva in targets:
        r = rows.get(rva)
        if r and r["source"].endswith((".asm", ".s")):
            p = latest.get(rva)
            # SecuROM post-link bodies (55 89 E5 frames, opaque predicates) can never
            # byte-match clean C++; 32 sessions re-proved that at ~35 min each.
            if a.dump and p and p[3] in ("blocked", "no-match") and "SecuROM" in p[4]:
                continue
            if rva not in live:
                live.append(rva)
        else:
            dropped.append(rva)
    live = live[:a.limit]
    if not live:
        sys.exit("brief: no live dump targets (all landed or unknown)")

    out = ["You are a conversion worker in the Open-BFME reverse-engineering repo (run everything from the repo root). "
           "Convert the bodies below into byte-matching C++ (MSVC 7.1), smallest first unless told otherwise."]
    if a.note:
        out.append("CONTEXT: " + a.note)
    if dropped:
        out.append(f"(Already landed by other lanes and removed from this brief: {len(dropped)} body/bodies.)")
    out.append("TARGETS:")
    for rva in live:
        out.append(describe(rva, rows, pins, latest, near))
    out.append(METHOD.replace("model=MODEL", f"model={a.model}"))
    print("\n".join(out))
    print(f"[brief: {len(live)} live target(s), {sum(int(rows[v]['target_size']) for v in live)} bytes; {len(dropped)} dropped as stale]", file=sys.stderr)


if __name__ == "__main__":
    main()
