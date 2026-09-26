#!/usr/bin/env python3
"""Refuse to resurrect a file the project deleted on purpose.

`tools/gen_uw.py`, `gen_small.py`, `gen_dump.py`, the wave tooling and their
tests were retired in 2d4dab0ad5 ("retire the C++ generators") and came back
three days later as a side effect of a fleet harvest, f43040e9c5. A harvest
commits whatever the index holds, and an index seeded from a stale branch held
them. targets/game/reverse/retired_paths.txt lists every path that must stay gone; this
guard fails when a staged change ADDS one of them (--staged, the commit hook)
or when a commit range does (--range A..B, the push hook / harvest).

Restoring one is a decision, not an accident: remove its line from
targets/game/reverse/retired_paths.txt in the same commit and say why.

  python3 tools/retired_guard.py --staged
  python3 tools/retired_guard.py --range origin/master..HEAD
  python3 tools/retired_guard.py --paths a.py b.py      (library / harvest use)
"""
import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RETIRED = ROOT / "targets/game/reverse" / "retired_paths.txt"


def retired_paths(path=RETIRED):
    if not path.exists():
        return set()
    return {line.strip() for line in path.read_text(encoding="utf-8").splitlines()
            if line.strip() and not line.startswith("#")}


def offenders(paths, retired=None):
    retired = retired_paths() if retired is None else retired
    return sorted(p for p in paths if p.replace("\\", "/") in retired)


def added_in(args):
    out = subprocess.run(["git", "diff", "--name-only", "--diff-filter=AC", *args],
                         cwd=ROOT, capture_output=True, text=True, check=True).stdout
    return [line.strip() for line in out.splitlines() if line.strip()]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument("--staged", action="store_true")
    g.add_argument("--range", metavar="A..B")
    g.add_argument("--paths", nargs="+")
    a = ap.parse_args()
    if a.staged:
        paths = added_in(["--cached"])
    elif a.range:
        paths = added_in([a.range])
    else:
        paths = a.paths
    bad = offenders(paths)
    if bad:
        print("retired_guard: these paths were deleted on purpose and may not come back "
              "(targets/game/reverse/retired_paths.txt; remove the line there, in the same commit, if you mean it):")
        for p in bad:
            print("  " + p)
        sys.exit(1)
    sys.exit(0)


if __name__ == "__main__":
    main()
