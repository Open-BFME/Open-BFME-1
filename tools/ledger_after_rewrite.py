#!/usr/bin/env python3
"""The ledger checks for commits that never saw pre-commit.

`git rebase` and `git cherry-pick` create commits without running pre-commit,
and the union merge driver can put a tombstoned functions.csv row back while
they do (reverse/deleted_rows.csv records deletions exactly because the union
driver cannot express one). Until now that was first caught at pre-push. The
post-rewrite and post-commit hooks run this: check_csv (duplicates, tombstoned
rows, overlaps) and b_pin_check (every b_<rva>() call keeps its pin), and on a
failure a banner with the repair.

  python3 tools/ledger_after_rewrite.py LABEL
Exit 1 when a check fails; the hooks only warn, git gives them no veto.
"""
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

BANNER = """
=============== {label}: THE LEDGER NEEDS A FIX ===============
A rebase or cherry-pick skipped pre-commit, and the ledger no longer passes.
  1. python3 tools/dedup_csv.py --drop-tombstoned   # duplicates + resurrected
                                                     # tombstoned rows
  2. python3 tools/check_csv.py                      # must pass
  3. python3 tools/b_pin_check.py                    # must pass: restore any
                                                     # ?b_<rva>@@YAXXZ pin BESIDE
                                                     # the real name
  4. git add reverse/functions.csv reverse/symbols.csv && git commit
Do this before pushing; pre-push will refuse it otherwise.
================================================================
"""


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    label = argv[0] if argv else "after rewrite"
    failed = False
    for tool in ("tools/check_csv.py", "tools/b_pin_check.py"):
        if subprocess.run([sys.executable, tool], cwd=ROOT).returncode != 0:
            failed = True
    if failed:
        print(BANNER.format(label=label.upper()), file=sys.stderr)
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
