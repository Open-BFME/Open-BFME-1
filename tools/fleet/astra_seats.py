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
  python3 tools/fleet/astra_seats.py harvest              # commit + push every finished seat

State lives in <main checkout>/build/astra_seats/ so every worktree sees the
same claims; a seat's bodies are not served again while it is listed there.
`harvest` stages everything a finished seat changed outside build/, commits it
through the normal hooks, and pushes with a rebase loop that drops tombstoned
records a union merge duplicates or resurrects (dedup_csv --merge-repair). A commit the hooks
refuse -- a name regression needing evidence, a gate failure -- is printed as
NEEDS REVIEW and left staged for the operator.
"""
import argparse
import collections
import datetime
import json
import os
import shutil
import subprocess
import sys
import time
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


def update_seats(change):
    """Load, change and save seats.json under one lock. A harvest takes an hour;
    one that loaded the list at its start and saved it at its end erased every
    seat launched meanwhile (2026-09-27: round 3 vanished and round 4 re-served
    its bodies), so every write re-reads the file it modifies."""
    sys.path.insert(0, str(ROOT / "tools"))
    from portable_lock import lock

    path = state_dir() / "seats.json"
    with (state_dir() / "seats.lock").open("a+b") as handle:
        lock(handle, exclusive=True)
        items = json.loads(path.read_text(encoding="utf-8")) if path.exists() else []
        change(items)
        tmp = path.with_suffix(".tmp")
        tmp.write_text(json.dumps(items, indent=1), encoding="utf-8")
        os.replace(tmp, path)


def mark_harvested(seat_id):
    released = []

    def change(items):
        for seat in items:
            if seat["id"] == seat_id:
                seat["harvested"] = True
                released.extend(seat["rvas"])
    update_seats(change)
    if released:
        import claims
        claims.release(released)             # landed or recorded: free them for everyone


def finished(seat):
    log = Path(seat["log"])
    return log.exists() and b"\ntokens used" in log.read_bytes()[-20000:]


def claimed():
    return {int(r, 16) for s in seats() if not s.get("harvested") for r in s["rvas"]}


def pick(count, lifts=False, lo=200, hi=1200, budget=5000, max_bodies=8, retry=False):
    """[(label, [rva, ...])] -- one file per seat, most fresh bytes first.

    retry=True serves bodies attempted once or twice instead of never: on
    2026-09-27 the never-tried pool was down to 107 mid and 6 big bodies while
    1,566 tried-but-open bodies (1.4 MB) remained. Files whose bodies carry the
    best banked scores come first, and a stash re-banked today is skipped (some
    lane is on it)."""
    import eligibility

    rows = eligibility.load_rows()
    latest = eligibility.latest_verdicts()
    attempts = eligibility.attempt_counts()
    # our own seats (seats.json) plus every live claim on origin (tools/claims.py)
    busy = claimed() | {int(r, 16) for r in eligibility.busy_rvas()}
    import datetime as _dt
    today = _dt.date.today()
    score = {}

    def wanted(r):
        rva = eligibility.rva_of(r)
        if rva in busy:
            return False
        tried = attempts.get(rva, 0)
        if not retry:
            return not tried
        if not 1 <= tried <= 2:
            return False
        found = eligibility.stash(rva)
        if found and eligibility.stash_date(found[0]) == today:
            return False
        score[rva] = found[1] if found else 0.0
        return True

    fresh = [r for r in eligibility.open_dumps(rows, latest, min_size=lo, max_size=hi) if wanted(r)]
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
    def weight(kv):
        # retry: bytes weighted by banked score, so near-finished files lead
        return -sum(s * (0.5 + score.get(r, 0.0)) if retry else s for r, s in kv[1])
    for source, bodies in sorted(by_file.items(), key=weight):
        if len(out) >= count + bool(lifts):
            break
        bodies.sort(key=lambda b: (-score.get(b[0], 0.0), b[0]) if retry else b)
        chosen, total = [], 0
        for rva, size in bodies:
            if len(chosen) < max_bodies and total + size <= budget + hi:
                chosen.append(rva)
                total += size
        out.append((source, chosen))
    return out


BIG_NOTE = """BIG-BODY SEAT ({model}, {effort}, hard cap {hours} hours). Each body below is 1.2-8 KB and has never been
attempted. Large bodies are where half the remaining bytes are, and where sessions fail by chasing bytes before
the structure is right. Method, in order: (1) python3 tools/callees.py and context_pack.py, then decompile with
GhidraSQL and write the WHOLE body first -- every call in retail order, every branch, the right prologue, frame size
and EH states; (2) only then work the first divergence with probe.py --shape; (3) a body that is not exact within
the cap is BANKED with re_log.py partial --stash --score (a complete 0.9 body is worth far more to the next seat than
nothing). Siblings in the same file share layouts: land or bank the most tractable one first.
""" + NOTE.split("\n", 3)[3]


RETRY_NOTE = """RETRY SEAT ({model}, {effort}, hard cap {hours} hours). Each body below was attempted once or twice
before and is still open. Its brief shows the PREFERRED STASH (the best banked attempt, with its score) and the
earlier verdicts. START FROM THE STASH, read every earlier verdict first, and try a lever nobody has tried --
repeating a recorded dead end is the one wasted move. Probe the stash before editing it; if the earlier verdict
blames a callee, run callees.py first (inferred ABI lines); if it is allocation-only, docs/shape_levers.md and
rotation_sweep.py. Siblings in the same file share layouts: land the closest one first.
""" + NOTE.split("\n", 3)[3]


def fresh_checkout():
    """pick() reads this checkout's ledger; a stale one re-serves landed bodies
    (2026-09-27: a seat was served four lifts landed hours earlier)."""
    subprocess.run(["git", "fetch", "-q", "origin", "master"], cwd=ROOT, check=True)
    head = subprocess.run(["git", "rev-parse", "HEAD"], cwd=ROOT, capture_output=True, text=True).stdout.strip()
    tip = subprocess.run(["git", "rev-parse", "origin/master"], cwd=ROOT, capture_output=True, text=True).stdout.strip()
    if head != tip:
        raise SystemExit(f"astra_seats: this checkout is at {head[:10]} but origin/master is {tip[:10]}; "
                         f"run `git pull --rebase origin master` here first (pick() reads the local ledger)")


GAP_NOTE = """GAP SEAT ({model}, {effort}, hard cap {hours} hours). The ranges below are retail .text that NO ledger row
claims: no boundary has been proven there yet. Your job is to turn each gap into claimed, byte-exact code.
For each gap, first decide what it is, with evidence:
  (a) the TAIL of the row that ends where the gap starts (a start mid-instruction or right after a non-terminal
      instruction means that row's extent stops short: extend it with add_match --replace-existing at the proven
      size and re-verify; Ghidra sizes are known to stop before the real ret);
  (b) one or more separate functions: prove each start (a REL32 call/jmp target, an ILT thunk target, a vtable
      slot, or int3 padding before it) and end (ret/tail jmp followed by int3 padding or the next proven start),
      then write the C++ and land it with tools/add_match.py as a new row (opaque address-derived name unless a
      caller/vtable/string proves the identity);
  (c) data inside .text (jump/index tables, constants): record it with re_log.py blocked "data: ..." and move on.
TOOLS: the GhidraSQL server (POST SQL to http://127.0.0.1:8081/query; VA = RVA + 0x400000): funcs (Ghidra's own
starts, advisory), xrefs WHERE to_addr=<VA> (who calls a start), pseudocode WHERE func_addr=<VA>, instructions.
python3 tools/callees.py, tools/fleet/context_pack.py and tools/probe.py work on any RVA/size you establish.
Rules as AGENTS.md: never run git, no full gate, never launch the game, never edit tools/ docs/ game/gen_asm/
game/gen_small/. Record a verdict for every function you establish (re_log.py; bank near misses with --stash
--score). Stop at {hours} hours and write build/astra_seat/REPORT.md: per gap, what it is and what landed.
"""


def find_gaps(min_bytes=64):
    """[(start, end, code_bytes)] of unclaimed .text between matched rows, padding
    stripped, largest first; SafeDisc no-ground-truth ranges excluded."""
    import build
    import eligibility

    rows = eligibility.load_rows()
    spans = sorted({(int(r["target_rva"], 16), int(r["target_size"] or 0)) for r in rows
                    if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x")})
    data = open(build.EXE, "rb").read()
    text = build.pe_sections(data)[0]
    lo, hi = text["rva"], text["rva"] + text["size"]
    raw = data[text["raw_pointer"]:text["raw_pointer"] + text["size"]]
    gaps, cur = [], lo
    for start, size in spans:
        if start > cur:
            gaps.append((cur, start))
        cur = max(cur, start + size)
    if cur < hi:
        gaps.append((cur, hi))
    out = []
    for a, b in gaps:
        core = raw[a - lo:b - lo].strip(b"\xcc")
        if len(core) >= min_bytes and not eligibility.no_ground_truth(a):
            out.append((a, b, len(core)))
    return sorted(out, key=lambda g: -g[2])


def gap_groups(count, budget=10000):
    """[(label, [gap start, ...])]: largest unclaimed gaps first, ~budget bytes a seat."""
    import eligibility

    busy = claimed() | {int(r, 16) for r in eligibility.busy_rvas()}
    gaps = [g for g in find_gaps() if g[0] not in busy]
    groups, current, total = [], [], 0
    for start, _, size in gaps:
        current.append(start)
        total += size
        if total >= budget:
            groups.append((f"gaps ({total:,} B)", current))
            current, total = [], 0
            if len(groups) >= count:
                break
    if current and len(groups) < count:
        groups.append((f"gaps ({total:,} B)", current))
    return groups


def gap_brief(starts):
    """TARGETS-style evidence for each gap: neighbours, Ghidra starts, callers."""
    import eligibility
    import json
    import urllib.request

    rows = [r for r in eligibility.load_rows()
            if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x")]
    rows.sort(key=lambda r: int(r["target_rva"], 16))
    ends = {int(r["target_rva"], 16) + int(r["target_size"] or 0): r for r in rows}
    begins = {int(r["target_rva"], 16): r for r in rows}
    gaps = {g[0]: g for g in find_gaps()}

    def ghidra(sql):
        try:
            req = urllib.request.Request("http://127.0.0.1:8081/query", data=sql.encode(), method="POST")
            with urllib.request.urlopen(req, timeout=60) as resp:
                res = json.loads(resp.read().decode())["results"][-1]
            return [dict(zip(res["columns"], row)) for row in res["rows"]] if res.get("success") else []
        except OSError:
            return []

    lines = ["TARGETS (unclaimed gaps; claimed on origin for this seat):"]
    for start in starts:
        a, b, size = gaps.get(start, (start, start, 0))
        lines.append(f"- GAP 0x{a:08X}..0x{b:08X} ({b - a} B span, {size} B not int3 padding)")
        before, after = ends.get(a), begins.get(b)
        if before:
            lines.append(f"    ends here: {before['name']} @ {before['target_rva']} ({before['target_size']} B) "
                         f"in {before['source']}")
        if after:
            lines.append(f"    starts after: {after['name']} @ {after['target_rva']} ({after['target_size']} B)")
        funcs = ghidra(f"SELECT addr, size, name FROM funcs WHERE addr >= {a + 0x400000} "
                       f"AND addr < {b + 0x400000} ORDER BY addr")
        for f in funcs[:12]:
            rva = int(f["addr"]) - 0x400000
            callers = ghidra(f"SELECT COUNT(*) AS n FROM xrefs WHERE to_addr = {f['addr']}")
            n = callers[0]["n"] if callers else "?"
            lines.append(f"    Ghidra start 0x{rva:08X} size {f['size']} ({f['name']}), {n} xref(s)")
        if not funcs:
            lines.append("    Ghidra knows no function start inside this gap (tail of the row before, or data?)")
    return "\n".join(lines) + "\n"


def launch(groups, hours, note_template=None, brief_fn=None):
    bash = shutil.which("bash")
    if not bash or not shutil.which("codex"):
        raise SystemExit("astra_seats: needs Git Bash (for `timeout`) and the codex CLI on PATH")
    base = main_root()
    subprocess.run(["git", "fetch", "-q", "origin", "master"], cwd=base, check=True)
    stamp = datetime.datetime.now().strftime("%Y%m%dT%H%M%S")
    import claims
    for i, (label, rvas) in enumerate(groups):
        seat_id = f"{stamp}_{i}"
        # Claim on origin before any work: a body another host claimed since
        # pick() ran is dropped, never converted twice.
        got, refused = claims.claim(rvas, note=f"astra seat {seat_id}")
        if refused:
            print(f"seat {seat_id}: {len(refused)} body(ies) claimed elsewhere, dropped: "
                  + " ".join(f"0x{r:08X}" for r in refused))
            rvas = [r for r in rvas if r not in set(refused)]
            if not rvas:
                continue
        worktree = base / "build" / f"wt_seat_{seat_id}"
        subprocess.run(["git", "worktree", "add", "-q", "--detach", str(worktree), "origin/master"],
                       cwd=base, check=True)
        work = state_dir() / seat_id
        work.mkdir()
        (worktree / "build" / "astra_seat").mkdir(parents=True, exist_ok=True)
        note = (note_template or NOTE).format(model=MODEL, effort=EFFORT, hours=hours)
        brief = work / "brief.txt"
        if brief_fn is not None:
            # gap seats have no ledger rows for brief.py to describe
            brief.write_text(note + "\n" + brief_fn(rvas), encoding="utf-8")
        else:
            with brief.open("w", encoding="utf-8") as handle:
                subprocess.run([sys.executable, str(worktree / "tools/brief.py"), "--rvas",
                                *[f"0x{r:08X}" for r in rvas],
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
        record = {"id": seat_id, "label": label, "rvas": [f"0x{r:08X}" for r in rvas],
                  "worktree": str(worktree), "log": str(log), "model": MODEL, "effort": EFFORT,
                  "started": stamp, "hours": hours}
        update_seats(lambda items: items.append(record))
        print(f"seat {seat_id}: {label}: {' '.join(f'0x{r:08X}' for r in rvas)}")


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


def git(tree, *args, check=False):
    return subprocess.run(["git", *args], cwd=tree, capture_output=True, text=True, check=check)


def landed_rows(tree):
    """New functions.csv rows in the seat's working tree, as `name @ rva (size B)`."""
    diff = git(tree, "diff", "HEAD", "--", "targets/game/reverse/functions.csv").stdout
    out = []
    for line in diff.splitlines():
        if line.startswith("+") and not line.startswith("+++"):
            fields = line[1:].split(",")
            if len(fields) > 4 and fields[2].startswith("0x"):
                out.append((fields[0], fields[2], int(fields[3] or 0)))
    return out


def push(tree, tries=20):
    """pull --rebase and push HEAD:master until the remote has it. After every
    rebase, union merge may have resurrected tombstoned rows (two deletions in
    one hunk keep both sides); drop them in place and commit before pushing."""
    for _ in range(tries):
        if git(tree, "pull", "-q", "--rebase", "origin", "master").returncode:
            state = git(tree, "status").stdout
            if "rebase in progress" in state:
                git(tree, "rebase", "--abort")
                return f"rebase conflict (aborted): {git(tree, 'diff', '--name-only', '--diff-filter=U').stdout.strip()}"
        dropped = subprocess.run([sys.executable, "tools/dedup_csv.py", "--merge-repair"], cwd=tree,
                                 capture_output=True, text=True).stdout
        ledgers = ["targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv"]
        if git(tree, "status", "--short", *ledgers).stdout.strip():
            git(tree, "add", *ledgers)
            commit = git(tree, "commit", "-q", "-m", "ledger: drop records a union merge duplicated or resurrected",
                         "-m", "\n".join(l for l in dropped.splitlines() if "dropped" in l)[:3000])
            if commit.returncode:
                return "merge-repair commit refused:\n" + (commit.stdout + commit.stderr)[-1500:]
        pushed = git(tree, "push", "-q", "origin", "HEAD:master")
        if pushed.returncode == 0:
            git(tree, "fetch", "-q", "origin", "master")
            if git(tree, "merge-base", "--is-ancestor", "HEAD", "origin/master").returncode == 0:
                return None
            continue
        # The pre-push checks take minutes and master moves meanwhile: a
        # non-fast-forward or ref-lock race is retried, anything else is real.
        text = pushed.stdout + pushed.stderr
        if not any(k in text for k in ("PUSH RACE", "fetch first", "non-fast-forward", "cannot lock ref", "stale info")):
            return "push refused:\n" + text[-2500:]
        if _ + 1 < tries:
            time.sleep(min(2 ** _, 8))
    return f"not pushed after {tries} attempts (lost every race with other pushers)"


def original_commit(tree):
    """The seat's own "reverse:" commit as first made, before any rebase.

    Rebasing it through union merge is what corrupted round 3's ledgers, and
    each later rebase or repair commit carries other contributors' rows; the
    first commit against its own parent is the seat's clean delta."""
    # The newest commit/amend the seat itself made; rebases log as
    # "rebase (pick)"/"pull --rebase" and never match, so an operator amend
    # (evidence for a name correction) is picked up and a rebase never is.
    for line in git(tree, "reflog", "--format=%H %gs").stdout.splitlines():
        sha, _, subject = line.partition(" ")
        if subject.startswith(("commit: reverse:", "commit (amend): reverse:")):
            return sha
    return None


def harvest(seat, correct=None):
    """Commit a finished seat and replay its delta onto master. Problem or None."""
    import seat_replay

    tree = Path(seat["worktree"])
    commit = original_commit(tree)
    if commit is None:
        rows = landed_rows(tree)
        changed = git(tree, "status", "--short", "--untracked-files=all").stdout.splitlines()
        paths = [line[3:].split(" -> ")[-1] for line in changed if not line[3:].startswith("build/")]
        if not paths:
            return "nothing to harvest"
        for path in paths:
            git(tree, "add", "-A", "--", path)
        total = sum(size for _, _, size in rows)
        subject = f"reverse: {len(rows)} bodies from {Path(seat['label']).name} ({total:,} B), {seat['model']} seat"
        body = "\n".join(f"  {rva} {size:5} B {name}" for name, rva, size in sorted(rows, key=lambda r: r[1]))
        made = git(tree, "commit", "-q", "-m", subject, "-m",
                   f"{seat['model']} ({seat['effort']}) fresh-file seat {seat['id']}, landed byte-exact:\n{body}",
                   "-m", "Co-Authored-By: Claude Opus 5.5 (1M context) <noreply@anthropic.com>")
        if made.returncode:
            return "commit refused by the hooks:\n" + (made.stdout + made.stderr)[-2500:]
        commit = git(tree, "rev-parse", "HEAD").stdout.strip()
    replay = seat_replay.replay_tree()
    problem = seat_replay.replay(tree, commit, replay, correct=correct)
    if problem is None:
        print(f"{seat['id']}: pushed {git(replay, 'log', '--oneline', '-1').stdout.strip()}")
    return problem


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["pick", "launch", "status", "harvest", "harvested"])
    ap.add_argument("count", nargs="?", type=int, default=4)
    ap.add_argument("--lifts", action="store_true", help="add one seat on servable named lifts")
    ap.add_argument("--gaps", action="store_true",
                    help="serve unclaimed .text gaps (no boundary proven yet) with GhidraSQL evidence, ~10 KB a seat")
    ap.add_argument("--retry", action="store_true",
                    help="serve bodies attempted once or twice (start from the stash) instead of never-tried ones")
    ap.add_argument("--big", action="store_true",
                    help="serve never-attempted bodies of 1.2-8 KB, 1-3 per seat, 3 h cap (half the remaining bytes)")
    ap.add_argument("--seat", help="harvested: mark this seat id as reviewed, releasing its bodies")
    ap.add_argument("--correct", nargs=2, metavar=("EVIDENCE", "REASON"),
                    help="harvest --seat ID: document the renames name_regression reports, citing EVIDENCE "
                         "(a tracked file in the seat commit) -- only after reviewing them")
    args = ap.parse_args(argv)
    if args.action == "status":
        return status()
    if args.action == "harvest":
        # corrections and replays use THIS checkout's name_regression/hooks
        # logic; a stale one computes corrections the current hooks reject
        fresh_checkout()
        for seat in seats():
            if seat.get("harvested") or not finished(seat) or (args.seat and seat["id"] != args.seat):
                continue
            problem = harvest(seat, tuple(args.correct) if args.correct else None)
            if problem and problem != "nothing to harvest":
                print(f"{seat['id']}: NEEDS REVIEW -- {problem}")
                continue
            mark_harvested(seat["id"])
        return 0
    if args.action == "harvested":
        mark_harvested(args.seat)
        return 0
    fresh_checkout()
    if args.gaps:
        groups = gap_groups(args.count)
        if args.action == "pick":
            for label, starts in groups:
                print(f"{label}: {' '.join(f'0x{r:08X}' for r in starts)}")
            return 0
        launch(groups, 3.0, GAP_NOTE, gap_brief)
        return 0
    if args.big:
        groups = pick(args.count, args.lifts, lo=1200, hi=8000, budget=8000, max_bodies=3, retry=args.retry)
    else:
        groups = pick(args.count, args.lifts, retry=args.retry)
    if args.action == "pick":
        for label, rvas in groups:
            print(f"{label}: {' '.join(f'0x{r:08X}' for r in rvas)}")
        return 0
    if args.retry:
        launch(groups, 3.0 if args.big else 2.0, RETRY_NOTE)
    elif args.big:
        launch(groups, 3.0, BIG_NOTE)
    else:
        launch(groups, 2.0)
    return 0


if __name__ == "__main__":
    sys.exit(main())
