#!/usr/bin/env python3
"""Git merge driver for the line ledgers .gitattributes marks merge=union.

git's built-in union merge keeps BOTH sides of every conflicting hunk, and it
cannot tell a row one side deleted or edited from a row that side kept: when an
upstream edit or retraction lands next to your own change, the old row comes
back beside the new one. 39 of the 1,028 commits on 2026-09-27 repaired exactly
that by hand.

This takes union's layout and removes what union put back wrongly, decided from
the merge base: a row either side deleted stays deleted, and a row both sides
added is kept once. A row both sides EDITED differently keeps both versions, as
union does: that is a real conflict, and check_csv names it.

It is registered under the name `union` itself, so a clone that has not
registered it keeps git's plain union instead of stopping on conflicts:
  git config merge.union.driver "python3 tools/merge_rows.py %O %A %B %P"
(tools/setup_hooks.sh, tools/setup_local_fleet.py, and .githooks/pre-commit for
clones set up before this existed.)
"""
import collections
import subprocess
import sys


def lines(data):
    """Split on \\n only, keeping each terminator: some ledger rows end in \\r\\r\\n."""
    parts = data.split(b"\n")
    return [part + b"\n" for part in parts[:-1]] + ([parts[-1]] if parts[-1] else [])


def row(line):
    return line.rstrip(b"\r\n")


def merge(union, base, ours, theirs):
    """Return (merged bytes, lines dropped from union's output)."""
    o, a, b = (collections.Counter(map(row, lines(side))) for side in (base, ours, theirs))
    kept, out = collections.Counter(), []
    for line in lines(union):
        key = row(line)
        if a[key] >= o[key] and b[key] >= o[key]:
            want = max(a[key], b[key])
        else:
            want = a[key] + b[key] - o[key]
        if kept[key] < want:
            kept[key] += 1
            out.append(line)
    return b"".join(out), len(lines(union)) - len(out)


def main(argv):
    if len(argv) != 4:
        print("usage: merge_rows.py BASE OURS THEIRS PATH", file=sys.stderr)
        return 2
    base, ours, theirs, path = argv
    union = subprocess.run(["git", "merge-file", "-p", "--union", ours, base, theirs],
                           capture_output=True)
    if union.returncode:
        print(f"merge_rows: git merge-file failed on {path}; leaving a conflict\n"
              + union.stderr.decode(errors="replace"), file=sys.stderr)
        return 1
    sides = [open(p, "rb").read() for p in (base, ours, theirs)]
    merged, dropped = merge(union.stdout, *sides)
    with open(ours, "wb") as handle:
        handle.write(merged)
    if dropped:
        print(f"merge_rows: {path}: dropped {dropped} line(s) plain union would have "
              "resurrected or duplicated", file=sys.stderr)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
