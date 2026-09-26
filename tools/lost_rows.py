#!/usr/bin/env python3
"""Rows that were landed once and have since vanished from the ledger.

WHY. `targets/game/reverse/*.csv` are union-merged, and a rebase can drop an appended line
without a conflict. When that happens the SOURCE stays and its row disappears, so
the file reads exactly like an abandoned attempt -- "ZERO matched rows -- source
presence is not progress" -- and the obvious response is to delete it. That throws
away a byte-matched function.

This happened overnight to LifeEventModuleInfoVectorDeletingDestructor.cpp: the
row landed in ac85103f80 on 2026-09-12 together with its source, vanished later,
and the gate reported the file as zero-row. Restoring the row byte-verified
immediately, Functions: OK 1/1.

So the two cases look identical in the working tree and are opposite in what they
deserve. The difference is in git history: an abandoned attempt NEVER had a
matched row; a lost row did. This asks history.

    python3 tools/lost_rows.py                 # every source whose row vanished
    python3 tools/lost_rows.py --zero-only     # only files with NO rows left,
                                               # i.e. the ones the gate is red on

A row that was deliberately retired is not lost: `targets/game/reverse/deleted_rows.csv`
tombstones those, and anything tombstoned is excluded.
"""
import argparse
import csv
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGER = ROOT / "targets/game/reverse/functions.csv"
ADDED = re.compile(r"^\+(\?\??[^,]+|[A-Za-z_][^,]*),")


def current():
    names, by_source = set(), {}
    with open(LEDGER, newline="") as fh:
        for row in csv.DictReader(fh):
            names.add(row["name"])
            by_source.setdefault(row.get("source") or "", []).append(row)
    return names, by_source


def tombstoned():
    path = ROOT / "targets/game/reverse/deleted_rows.csv"
    if not path.exists():
        return set()
    with open(path, newline="") as fh:
        return {r["name"] for r in csv.DictReader(fh) if r.get("name")}


def landed(since):
    """{row name: (commit, source)} for every matched row ever added."""
    out = {}
    log = subprocess.run(
        ["git", "log", f"--since={since}", "--format=%H", "--", "targets/game/reverse/functions.csv"],
        cwd=ROOT, capture_output=True, text=True).stdout.split()
    for commit in log:
        diff = subprocess.run(["git", "show", commit, "--", "targets/game/reverse/functions.csv"],
                              cwd=ROOT, capture_output=True, text=True).stdout
        for line in diff.splitlines():
            if not line.startswith("+") or line.startswith("++"):
                continue
            parts = line[1:].split(",")
            if len(parts) < 6 or parts[5].strip() != "matched":
                continue
            out.setdefault(parts[0], (commit[:10], parts[4]))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--since", default="30.days")
    ap.add_argument("--zero-only", action="store_true",
                    help="only sources that have no rows left at all")
    args = ap.parse_args()

    names, by_source = current()
    dead = tombstoned()
    was = landed(args.since)
    lost = [(n, c, s) for n, (c, s) in sorted(was.items())
            if n not in names and n not in dead]
    if args.zero_only:
        # The actionable case is a source that STILL EXISTS and has no rows left:
        # that is the one the gate reports as "ZERO matched rows" and that someone
        # is about to delete. A row whose source went with it is a deletion that
        # merely skipped its tombstone -- untidy, not lost work.
        lost = [(n, c, s) for n, c, s in lost
                if not by_source.get(s) and (ROOT / s).exists()]
    print(f"rows landed in the last {args.since} that are gone and not tombstoned: "
          f"{len(lost)}")
    for name, commit, source in lost:
        alive = "source missing" if not (ROOT / source).exists() else \
                (f"{len(by_source.get(source, []))} row(s) left" )
        print(f"  {name[:58]:<58} {commit}  {alive}")
        print(f"      {source}")
    if lost:
        print("\n  Restore with the row text from its commit, then byte-verify the "
              "source.\n  A row that was proved once does not need re-deriving -- but it "
              "does need\n  re-verifying, because the tree has moved since.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
