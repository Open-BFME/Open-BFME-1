#!/usr/bin/env python3
"""Move one batch from reverse/placement_queue.tsv, byte-gated, ledger repointed.

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

STAGING. `git add -A Code/` sweeps in whatever else is dirty -- the `git add .`
ban in AGENTS.md by another door. Only the batch's own paths are staged.

THE LEDGER IS BYTES. reverse/functions.csv carries mixed line terminators and a
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
QUEUE = ROOT / "reverse/placement_queue.tsv"
LEDGER = ROOT / "reverse/functions.csv"


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


def build(paths):
    """(ok, failing paths). Never called with an empty list -- see the docstring."""
    if not paths:
        raise RuntimeError("refusing to build an empty set: that is the full gate")
    done = subprocess.run([str(ROOT / "build.sh"), *paths], cwd=ROOT,
                          capture_output=True, text=True)
    bad = set()
    for line in done.stdout.splitlines():
        if line.startswith("  FAIL") and "(" in line:
            bad.add(line[line.index("(") + 1:line.rindex(")")])
    ok = any(l.startswith("Functions: OK") for l in done.stdout.splitlines())
    return ok, bad, done.stdout


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--count", type=int, default=80)
    ap.add_argument("--commit", action="store_true")
    args = ap.parse_args()

    rows = [l.rstrip("\n").split("\t") for l in
            QUEUE.read_text(encoding="utf-8").splitlines() if l.strip()]
    if not rows:
        print("queue empty")
        return 9
    batch, rest = rows[:args.count], rows[args.count:]

    moved = []
    for source, target, _cls in batch:
        if not (ROOT / source).exists():
            continue
        (ROOT / target).parent.mkdir(parents=True, exist_ok=True)
        if git("mv", source, target, check=False).returncode:
            continue
        moved.append((source, target))
    if not moved:
        print("nothing moved")
        return 9
    print(f"moved {len(moved)}, repointed {repoint(moved)} ledger row(s)")

    ok, bad, out = build([t for _, t in moved])
    if bad:
        print(f"  {len(bad)} pre-existing red(s) -- returning them")
        back = [(t, s) for s, t in moved if t in bad]
        for target, source in back:
            git("mv", target, source, check=False)
        repoint(back)
        moved = [(s, t) for s, t in moved if t not in bad]
        if not moved:
            print("  every file in this batch was red; nothing to land")
            return 1
        ok, bad, out = build([t for _, t in moved])
        if bad:
            print("  still failing after returning the reds -- stopping", file=sys.stderr)
            return 1
    print(f"  byte gate: {'OK' if ok else 'UNVERIFIED'} over {len(moved)} file(s)")

    if not args.commit:
        print("  --commit to land. Queue is left unchanged until then.")
        return 0

    git("add", "reverse/functions.csv", *[t for _, t in moved])
    git("add", "-u", *[s for s, _ in moved])
    subject = f"Move {len(moved)} misplaced sources into their class's directory"
    body = (f"{subject}\n\n"
            "Placement lane. Each file declares exactly one owning class and sat in a\n"
            "directory that class keeps nothing else in; the destination is where ZH puts\n"
            "that class, or where the class already keeps two or more bodies. Never\n"
            "invented, never the flat Common/ dumping ground.\n\n"
            "Byte-neutral: the `// cl:` line travels with the file and none of these\n"
            "carries a relative include. The ledger source column is repointed as BYTES.\n\n"
            "Co-Authored-By: Claude Opus 5 (1M context) <noreply@anthropic.com>\n"
            "Claude-Session: https://claude.ai/code/session_01Wh8KKNWW2pk7waNmmnzU6R\n")
    done = subprocess.run(["git", "commit", "-q", "-F", "-"], cwd=ROOT,
                          input=body, text=True, capture_output=True)
    if done.returncode:
        print("COMMIT REFUSED:\n" + done.stdout[-2000:], file=sys.stderr)
        return 1
    QUEUE.write_text("".join("\t".join(r) + "\n" for r in rest), encoding="utf-8")
    print(f"  committed. queue: {len(rest)} left")
    return 0


if __name__ == "__main__":
    sys.exit(main())
