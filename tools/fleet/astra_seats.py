#!/usr/bin/env python3
"""Launch gpt-6-astra seats on fresh mid-size bodies, one source file per seat.

WHY. Measured 2026-09-21..26 on this project: Astra landed 11 of 16 and 19 of 21
untried neighbours of an analysed hub, 4 of 7 siblings, but only 5 of 19 near
misses already walled by earlier seats. Fresh bodies grouped by file land 3-4x
better because the first body's layouts and callee contracts carry to the rest
(AGENTS.md "Work the file"). This serves exactly that: never-attempted open
dumps of 200-1,200 B, the file with the most such bytes first, plus optionally
one seat on the servable named lifts (Zero Hour twins first).

WHY NOT fleet_run. fleet_run requires a delegated Linux cgroup-v2 unit and has
deliberately no fallback, so it cannot start a worker on a Windows host. These
seats are not fleet workers: each gets its own detached worktree off
origin/master, never runs git, and the operator reviews and commits what it
lands. BFME_MODEL is exported so re_log and add_match attribute every verdict.

  python3 tools/fleet/astra_seats.py pick 5 [--lifts]     # show what would be served
  python3 tools/fleet/astra_seats.py launch 5 [--lifts]   # worktrees + briefs + codex
  python3 tools/fleet/astra_seats.py status               # running/done, what each landed

State lives in <main checkout>/build/astra_seats/ so every worktree sees the
same claims; a seat's bodies are not served again while it is listed there.
"""
import argparse
import collections
import datetime
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

MODEL = os.environ.get("ASTRA_MODEL", "gpt-6-astra")
EFFORT = os.environ.get("ASTRA_EFFORT", "medium")

NOTE = """FRESH-FILE SEAT ({model}, {effort}, hard cap {hours} hours). The bodies below come from ONE source file and
none has been attempted before. Land the one with the best evidence first, then reuse its layouts, callee declarations
and shapes on its siblings (measured: 46.5% land rate with siblings vs 19.5% solo).

TOOLS (all read-only against the retail image):
- python3 tools/callees.py 0xRVA SIZE : every callee; under unsigned ones an "inferred ABI:" line (convention, stack
  slots, result used) read from the retail bytes. Declare callees that way.
- GhidraSQL server (already running; never restart or stop it): POST SQL text to http://127.0.0.1:8081/query, JSON
  back. Addresses are VAs = RVA + 0x400000. SELECT text FROM pseudocode WHERE func_addr=<VA>; xrefs, function_calls,
  string_refs, stack_vars, decomp_lvars, funcs. Decompiled C is a control-flow draft; names and types are invented.
- python3 tools/fleet/context_pack.py 0xRVA : callers (through ILT thunks), strings, vtable, layout witnesses.
- python3 tools/probe.py <src.cpp> "MANGLED" 0xRVA --shape : compile + retail diff + shape score; docs/shape_levers.md
  for near misses. Shape 1.000 with only EAX/ECX/EDX differing: python3 tools/rotation_sweep.py (scratch registers
  rotate; toggle the copy of a pushed argument above the first mismatch). Compiler switches are not a lever.
- python3 tools/name_oracle.py --class C --offset N before naming any member.

RESULTS: EXACT -> land with tools/add_match.py (real source at the proper game/ path per AGENTS.md; opaque
address-derived names where identity is unproved; --replace-rva for gen_asm rows; --model {model}), then
./build.sh <that source> (build.cmd in PowerShell) must print Functions OK. Close but not exact -> python3
tools/re_log.py record ... partial "<what is wrong> blocker=<family> t=<min>min model={model}-{effort}" --stash
<your.cpp> --score <measured>. Hand-written assembly (no compiler frame, MMX) or no progress -> record blocked with the
evidence and move to the next sibling. Write build/astra_seat/REPORT.md at the end: per body, result and what moved it.

RULES: never run git (the operator commits). No full gate, no whole-tree build, never launch the game. Do not edit
tools/, docs/, game/gen_asm/ or game/gen_small/. Never rename an established descriptive name without evidence. Stop
at {hours} hours."""


def main_root():
    common = subprocess.run(["git", "rev-parse", "--path-format=absolute", "--git-common-dir"],
                            cwd=ROOT, capture_output=True, text=True, check=True).stdout.strip()
    return Path(common).parent


def state_dir():
    path = main_root() / "build" / "astra_seats"
    path.mkdir(parents=True, exist_ok=True)
    return path


def seats():
    path = state_dir() / "seats.json"
    return json.loads(path.read_text(encoding="utf-8")) if path.exists() else []


def save_seats(items):
    (state_dir() / "seats.json").write_text(json.dumps(items, indent=1), encoding="utf-8")


def finished(seat):
    log = Path(seat["log"])
    return log.exists() and b"\ntokens used" in log.read_bytes()[-20000:]


def claimed():
    return {int(r, 16) for s in seats() if not s.get("harvested") for r in s["rvas"]}


def pick(count, lifts=False, lo=200, hi=1200, budget=5000, max_bodies=8):
    """[(label, [rva, ...])] -- one file per seat, most fresh bytes first."""
    import eligibility

    rows = eligibility.load_rows()
    latest = eligibility.latest_verdicts()
    attempts = eligibility.attempt_counts()
    busy = claimed()
    fresh = [r for r in eligibility.open_dumps(rows, latest, min_size=lo, max_size=hi)
             if not attempts.get(eligibility.rva_of(r)) and eligibility.rva_of(r) not in busy]
    by_file = collections.defaultdict(list)
    for r in fresh:
        by_file[r["source"]].append((eligibility.rva_of(r), int(r["target_size"])))
    out = []
    if lifts:
        import lift_lane
        live = [v for v in lift_lane.lift_verdicts(rows)
                if not eligibility.retired(eligibility.rva_of(v[0]), latest) and (not v[1] or v[2])
                and eligibility.rva_of(v[0]) not in busy and lo <= int(v[0]["target_size"]) <= 2 * hi]
        live.sort(key=lambda v: (not lift_lane.zh_twin(v[0]["name"]), attempts.get(eligibility.rva_of(v[0]), 0),
                                 -int(v[0]["target_size"])))
        chosen, total = [], 0
        for row, _, _ in live:
            if len(chosen) >= max_bodies or total >= budget:
                break
            chosen.append(eligibility.rva_of(row))
            total += int(row["target_size"])
        if chosen:
            out.append(("lifts (ZH twins first)", chosen))
    for source, bodies in sorted(by_file.items(), key=lambda kv: -sum(s for _, s in kv[1])):
        if len(out) >= count + bool(lifts):
            break
        bodies.sort()
        chosen, total = [], 0
        for rva, size in bodies:
            if len(chosen) < max_bodies and total + size <= budget + hi:
                chosen.append(rva)
                total += size
        out.append((source, chosen))
    return out


def launch(groups, hours):
    bash = shutil.which("bash")
    if not bash or not shutil.which("codex"):
        raise SystemExit("astra_seats: needs Git Bash (for `timeout`) and the codex CLI on PATH")
    base = main_root()
    subprocess.run(["git", "fetch", "-q", "origin", "master"], cwd=base, check=True)
    items = seats()
    stamp = datetime.datetime.now().strftime("%Y%m%dT%H%M%S")
    for i, (label, rvas) in enumerate(groups):
        seat_id = f"{stamp}_{i}"
        worktree = base / "build" / f"wt_seat_{seat_id}"
        subprocess.run(["git", "worktree", "add", "-q", "--detach", str(worktree), "origin/master"],
                       cwd=base, check=True)
        work = state_dir() / seat_id
        work.mkdir()
        (worktree / "build" / "astra_seat").mkdir(parents=True, exist_ok=True)
        note = NOTE.format(model=MODEL, effort=EFFORT, hours=hours)
        brief = work / "brief.txt"
        with brief.open("w", encoding="utf-8") as handle:
            subprocess.run([sys.executable, str(worktree / "tools/brief.py"), "--rvas", *[f"0x{r:08X}" for r in rvas],
                            "--model", MODEL, "--limit", str(len(rvas)), "--note", note],
                           cwd=worktree, stdout=handle, check=True)
        log = work / "session.log"
        script = (f"export BFME_MODEL={MODEL}; timeout -k 60 {int(hours * 3600)} codex exec -m {MODEL} "
                  f"-c 'model_reasoning_effort=\"{EFFORT}\"' --sandbox danger-full-access "
                  f"--cd \"{worktree.as_posix()}\" - < \"{brief.as_posix()}\" > \"{log.as_posix()}\" 2>&1")
        flags = 0
        if os.name == "nt":
            flags = subprocess.DETACHED_PROCESS | subprocess.CREATE_NEW_PROCESS_GROUP
        subprocess.Popen([bash, "-c", script], cwd=worktree, stdin=subprocess.DEVNULL,
                         stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, creationflags=flags,
                         start_new_session=os.name != "nt")
        items.append({"id": seat_id, "label": label, "rvas": [f"0x{r:08X}" for r in rvas],
                      "worktree": str(worktree), "log": str(log), "model": MODEL, "effort": EFFORT,
                      "started": stamp, "hours": hours})
        print(f"seat {seat_id}: {label}: {' '.join(f'0x{r:08X}' for r in rvas)}")
    save_seats(items)


def status():
    for seat in seats():
        if seat.get("harvested"):
            continue
        tree = Path(seat["worktree"])
        changes = subprocess.run(["git", "status", "--short"], cwd=tree, capture_output=True, text=True).stdout
        landed = [l[3:] for l in changes.splitlines() if l.startswith("?? game/")]
        state = "done" if finished(seat) else "running"
        print(f"{seat['id']} {state:7} {seat['label']}: {len(seat['rvas'])} bodies; new game/ sources: "
              f"{len(landed)}{' ' + ', '.join(landed) if landed else ''}")


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["pick", "launch", "status", "harvested"])
    ap.add_argument("count", nargs="?", type=int, default=4)
    ap.add_argument("--lifts", action="store_true", help="add one seat on servable named lifts")
    ap.add_argument("--hours", type=float, default=2.0)
    ap.add_argument("--seat", help="harvested: mark this seat id as reviewed, releasing its bodies")
    args = ap.parse_args(argv)
    if args.action == "status":
        return status()
    if args.action == "harvested":
        items = seats()
        for seat in items:
            if seat["id"] == args.seat:
                seat["harvested"] = True
        save_seats(items)
        return 0
    groups = pick(args.count, args.lifts)
    if args.action == "pick":
        for label, rvas in groups:
            print(f"{label}: {' '.join(f'0x{r:08X}' for r in rvas)}")
        return 0
    launch(groups, args.hours)
    return 0


if __name__ == "__main__":
    sys.exit(main())
