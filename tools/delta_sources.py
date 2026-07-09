#!/usr/bin/env python3
"""Print the source files whose functions.csv claims change between two states.

Row-set semantics: a row counts as delta only if its exact tuple is absent from
the old state — new claims and edited claims need byte-proof; deletions and
reorders (dedup_csv re-sorts the whole file) cannot break byte-truth and are
ignored. Used by the git hooks to byte-verify exactly what a commit or push
adds, instead of running the full multi-minute gate.

  --staged        HEAD vs the git index (pre-commit)
  --range A B     committed state A vs committed state B (pre-push)

Output: one repo-relative source path per line (empty output = no new claims).
"""
import argparse
import csv
import io
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LEDGER = "reverse/functions.csv"


def rows_at(spec):
    """Ledger rows at a git object spec (e.g. 'HEAD:reverse/...', ':reverse/...').
    Returns an empty set when the ledger does not exist there (new repo)."""
    out = subprocess.run(["git", "-C", str(ROOT), "show", spec], capture_output=True)
    if out.returncode != 0:
        return set()
    text = out.stdout.decode("utf-8", errors="replace")
    return {tuple(r) for r in csv.reader(io.StringIO(text)) if r and r[0] != "name"}


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true",
                      help="delta between HEAD and the staged ledger")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"),
                      help="delta between two committed refs/SHAs")
    args = parser.parse_args()

    if args.staged:
        old, new = rows_at(f"HEAD:{LEDGER}"), rows_at(f":{LEDGER}")
    else:
        old_ref, new_ref = args.range
        old, new = rows_at(f"{old_ref}:{LEDGER}"), rows_at(f"{new_ref}:{LEDGER}")

    sources = {r[4] for r in (new - old) if len(r) >= 5 and r[4]}
    for s in sorted(sources):
        print(s)


if __name__ == "__main__":
    main()
