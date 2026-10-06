#!/usr/bin/env python3
"""Refuse a byte gate that would read a ledger other than the one being committed.

WHY. The build reads reverse/functions.csv and reverse/symbols.csv from the
WORKING TREE. A row rename left unstaged (the header lane's U->V class-key
renames, 2026-10-06) let units commit green that only match under the
unstaged names: the commit's own ledger still had the old names, so HEAD was
inconsistent and nothing said so. The old guard only fired when a ledger was
both staged and edited again; an unstaged-only edit slipped through.

So before any source is verified:
  --staged      (pre-commit) every verification ledger must be identical in
                the working tree and the index;
  --commit SHA  (pre-push)  every verification ledger in the working tree must
                be the pushed commit's (nothing unstaged, nothing staged-only).

    python3 tools/ledger_guard.py --staged
    python3 tools/ledger_guard.py --commit <sha>
exit 0 = the gate will read the ledgers it is proving; 1 = refused (paths on stderr).
"""
import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
if (ROOT / "targets" / "game" / "reverse" / "functions.csv").exists():      # Open-BFME-1
    LEDGERS = ("targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv")
else:                                                                         # Open-BFME-2
    LEDGERS = ("reverse/functions.csv", "reverse/symbols.csv")


def differing(*spec):
    """Ledgers whose working-tree bytes differ from the index (no spec) or a commit."""
    done = subprocess.run(["git", "diff", "--name-only", *spec, "--", *LEDGERS], cwd=ROOT,
                          capture_output=True, text=True)
    if done.returncode:
        raise SystemExit(f"ledger_guard: git diff failed: {done.stderr.strip()}")
    return [p for p in done.stdout.split() if p]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--staged", action="store_true")
    group.add_argument("--commit", metavar="SHA")
    args = parser.parse_args(argv)
    bad = differing() if args.staged else differing(args.commit)
    if not bad:
        return 0
    against = "the index" if args.staged else f"the pushed commit {args.commit[:10]}"
    for path in bad:
        print(f"  {path}: the working tree differs from {against}", file=sys.stderr)
    print("ledger_guard: the byte gate reads the working-tree ledgers, so it would verify rows this "
          "commit does not contain. Stage (and commit) the ledger edit, or stash it.", file=sys.stderr)
    return 1


if __name__ == "__main__":
    sys.exit(main())
