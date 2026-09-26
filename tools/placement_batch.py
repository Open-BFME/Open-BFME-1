#!/usr/bin/env python3
"""Move one batch from targets/game/reverse/placement_queue.tsv, byte-gated, ledger repointed.

    python3 tools/placement_batch.py --count 80        # move, verify, report
    python3 tools/placement_batch.py --count 80 --commit

Every guard below is something this lane has already paid for once.

EMPTY LIST. `./build.sh $MOVED` with an empty MOVED expands to `./build.sh` with
no arguments, which is the FULL gate: it takes a host-wide lock and verifies the
whole tree. A batch whose files all got returned did exactly that and held the
lock for twenty-one minutes, blocking every other agent, while verifying a
half-moved tree whose answer meant nothing. Nothing here ever builds an empty set.

PRE-EXISTING REDS. A file already red at its original path is red after the move
too, and the failure names the MOVED path, so it reads like the move's fault. They
are returned, not diagnosed.

STAGING. `git add -A game/` sweeps in whatever else is dirty -- the `git add .`
ban in AGENTS.md by another door. Only the batch's own paths are staged.

THE LEDGER IS BYTES. targets/game/reverse/functions.csv carries mixed line terminators and a
csv round-trip flattens them; check_csv rejects that. The source column is
repointed by byte replacement, anchored on the surrounding commas so a path that
is a prefix of another cannot be hit.
"""
import argparse
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
QUEUE = ROOT / "targets/game/reverse/placement_queue.tsv"
LEDGER = ROOT / "targets/game/reverse/functions.csv"
BLOCKED = ROOT / "targets/game/reverse/placement_blocked.tsv"


def git(*args, check=True):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True,
                          text=True, check=check)


def repoint(pairs):
    """Rewrite the ledger's source column for each (old, new), as bytes."""
    data = LEDGER.read_bytes()
    moved = 0
    for old, new in pairs:
        key = ("," + old + ",").encode()
        moved += data.count(key)
        data = data.replace(key, ("," + new + ",").encode())
    LEDGER.write_bytes(data)
    return moved


def blocked_paths():
    if not BLOCKED.exists():
        return set()
    return {l.split("\t")[0] for l in
            BLOCKED.read_text(encoding="utf-8").splitlines() if l.strip()}


def build(paths):
    """(failing paths, output). Raises on a failure it cannot attribute to a file.

    build.sh reports compile errors on STDERR and aborts the whole scoped build on
    the first one, so reading stdout alone sees a batch with no `Functions: OK`
    line and no FAIL line either. That used to print `byte gate: UNVERIFIED` and
    commit anyway -- a green-looking path through a build that never ran.
    """
    if not paths:
        raise RuntimeError("refusing to build an empty set: that is the full gate")
    done = subprocess.run([str(ROOT / "build.sh"), *paths], cwd=ROOT,
                          capture_output=True, text=True)
    out = done.stdout + done.stderr
    bad = {l[l.index("(") + 1:l.rindex(")")] for l in out.splitlines()
           if l.startswith("  FAIL") and "(" in l}
    bad |= {l.split(":", 1)[1].strip() for l in out.splitlines()
            if l.lower().startswith("compile failed:")}
    if done.returncode and not bad:
        raise RuntimeError(f"build.sh exited {done.returncode} naming no file:\n"
                           + out[-3000:])
    if not bad and "Functions: OK" not in out:
        raise RuntimeError("build.sh exited 0 with no verdict:\n" + out[-3000:])
    return bad, out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--count", type=int, default=80)
    ap.add_argument("--commit", action="store_true")
    args = ap.parse_args()

    rows = [l.rstrip("\n").split("\t") for l in
            QUEUE.read_text(encoding="utf-8").splitlines() if l.strip()]
    # A file the hook refuses at any path stays queued otherwise, so every later
    # batch moves it again, pays a build for it, and is refused again.
    refused = blocked_paths()
    rows = [r for r in rows if r[0] not in refused]
    if not rows:
        print("queue empty")
        return 9
    batch = rows[:args.count]

    moved = []
    for source, target, _cls in batch:
        if not (ROOT / source).exists():
            continue
        # A queue row names ONE SOURCE FILE. It has to be checked, because the
        # move below is `git mv`, and `git mv Code mods/Code` relocates the
        # entire 16,281-file source tree in one call -- which is exactly what a
        # malformed row did on 2026-09-14, leaving the repo with no game/ at all.
        # Nothing was committed, so it restored from HEAD, but the tool handed
        # the whole tree to one unchecked row and reported "moved 2".
        if not (ROOT / source).is_file() or not source.endswith((".cpp", ".h")):
            raise SystemExit(f"placement row 1 is not a source FILE: {source!r}. "
                             "A directory here moves the whole tree; refusing.")
        if not target.startswith("game/") or not target.endswith((".cpp", ".h")):
            raise SystemExit(f"placement row 2 leaves game/: {target!r}. "
                             "Sources only ever move within game/; refusing.")
        (ROOT / target).parent.mkdir(parents=True, exist_ok=True)
        if git("mv", source, target, check=False).returncode:
            continue
        moved.append((source, target))
    if not moved:
        print("nothing moved")
        return 9
    print(f"moved {len(moved)}, repointed {repoint(moved)} ledger row(s)")

    # One round of returning reds is not enough: build.sh raises SystemExit at the
    # FIRST compile failure, so a batch holding several names only one per round.
    # Stopping after one round left 84 verified files moved and uncommitted, and
    # every later batch then span on a queue that still listed them.
    returned = 0
    while True:
        bad, out = build([t for _, t in moved])
        if not bad:
            break
        returned += len(bad)
        back = [(t, s) for s, t in moved if t in bad]
        for target, source in back:
            git("mv", target, source, check=False)
        repoint(back)
        moved = [(s, t) for s, t in moved if t not in bad]
        if not moved:
            print("  every file in this batch was red; nothing to land")
            return 1
    if returned:
        print(f"  {returned} pre-existing red(s) returned")
    print(f"  byte gate: OK over {len(moved)} file(s)")

    if not args.commit:
        print("  --commit to land. Queue is left unchanged until then.")
        return 0

    return land(moved, rows)


def land(moved, rows):
    """Commit, returning whatever the hook names. Bounded rounds, not hope.

    A source that fails the gate at every path needs its underlying source-claim,
    compile, or byte defect repaired before it can move. Return that source and
    record the blocker so the rest of the batch can still land.
    """
    for _ in range(4):
        git("add", "targets/game/reverse/functions.csv", *[t for _, t in moved])
        if BLOCKED.exists():
            git("add", str(BLOCKED.relative_to(ROOT)))
        subject = f"Move {len(moved)} misplaced sources into their class's directory"
        body = (f"{subject}\n\n"
                "Placement lane. Each file declares exactly one owning class and sat in a\n"
                "directory that class keeps nothing else in; the destination is where ZH\n"
                "puts that class -- by a file of its own name, or by the header that\n"
                "declares it where ZH's Include/Source mirror is real. Never invented,\n"
                "never the flat Common/ dumping ground, and never a parent of where the\n"
                "file already sits.\n\n"
                "Byte-neutral: the `// cl:` line travels with the file and none of these\n"
                "carries a relative include. The ledger source column is repointed as BYTES.\n\n"
                "Co-Authored-By: Claude Opus 5 (1M context) <noreply@anthropic.com>\n"
                "Claude-Session: https://claude.ai/code/session_01Wh8KKNWW2pk7waNmmnzU6R\n")
        done = subprocess.run(["git", "commit", "-q", "-F", "-"], cwd=ROOT,
                              input=body, text=True, capture_output=True)
        if not done.returncode:
            break
        out = done.stdout + done.stderr
        named = {}
        for src, dst in moved:
            for line in out.splitlines():
                if line.startswith(dst + ":"):
                    named[(src, dst)] = "defines a function no ledger row declares"
                elif line.lower().startswith("compile failed:") and line.endswith(dst):
                    named[(src, dst)] = "does not compile at the new path"
                elif line.startswith("  FAIL") and line.endswith("(" + dst + ")"):
                    named[(src, dst)] = "byte-red at the new path"
        if not named:
            print("COMMIT REFUSED:\n" + out[-2500:], file=sys.stderr)
            return 1
        print(f"  hook refuses {len(named)} -- returning them")
        for src, dst in named:
            git("mv", dst, src, check=False)
        repoint([(dst, src) for src, dst in named])
        with BLOCKED.open("a", encoding="utf-8") as fh:
            for (src, _), why in named.items():
                fh.write(f"{src}\t{why}\n")
        moved = [m for m in moved if m not in named]
        if not moved:
            print("  nothing left to land")
            return 1
    else:
        print("COMMIT REFUSED: still refused after four rounds", file=sys.stderr)
        return 1

    # Drop by what actually moved, not by position: a batch that returned reds
    # leaves them queued, and slicing the first N would forget them.
    done_paths = {src for src, _ in moved}
    rest = [r for r in rows if r[0] not in done_paths]
    QUEUE.write_text("".join("\t".join(r) + "\n" for r in rest), encoding="utf-8")
    print(f"  committed {len(moved)}. queue: {len(rest)} left")
    return 0


if __name__ == "__main__":
    sys.exit(main())
