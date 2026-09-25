#!/usr/bin/env python3
"""Refuse a staged edit that is mostly a line-ending rewrite.

Many sources carry mixed terminators (InGameUI.cpp had 3,332 CRLF lines among
LF ones). With core.autocrlf=true, a text-mode rewrite or a plain `git add`
strips every CR, and a three-body change became a 7,000-line diff that every
concurrent lane then had to merge (the InGameUI finisher, 2026-09-25). The
byte gate cannot see it: the compiler ignores terminators.

  python3 tools/eol_guard.py --staged
Fix: restore the file's own terminators, or stage it with
`git -c core.autocrlf=false add <file>`. A deliberate normalisation is its own
commit: BFME_EOL_REWRITE=1 for that one commit.
"""
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
# Line changes that only a CR at end of line explains, above which the edit is
# a rewrite rather than an edit.
THRESHOLD = 50


def numstat(*extra):
    out = subprocess.run(["git", "diff", "--cached", "--numstat", "--diff-filter=M", *extra],
                         cwd=ROOT, capture_output=True, text=True, check=True).stdout
    stats = {}
    for line in out.splitlines():
        added, deleted, path = line.split("\t", 2)
        if added != "-":
            stats[path] = int(added) + int(deleted)
    return stats


def rewrites():
    plain, ignoring = numstat(), numstat("--ignore-cr-at-eol")
    return sorted((path, n, ignoring.get(path, 0)) for path, n in plain.items()
                  if n - ignoring.get(path, 0) >= THRESHOLD)


def main(argv=None):
    found = rewrites()
    if not found:
        return 0
    if os.environ.get("BFME_EOL_REWRITE") == "1":
        print(f"eol_guard: {len(found)} deliberate line-ending rewrite(s) allowed by BFME_EOL_REWRITE=1")
        return 0
    for path, total, real in found:
        print(f"  {path}: {total} changed lines, only {real} once CR-at-EOL is ignored")
    print("eol_guard: the staged change rewrites line endings. Restore the file's own terminators, or "
          "stage it with `git -c core.autocrlf=false add <file>`; a deliberate normalisation goes in "
          "its own commit with BFME_EOL_REWRITE=1.")
    return 1


if __name__ == "__main__":
    sys.exit(main())
