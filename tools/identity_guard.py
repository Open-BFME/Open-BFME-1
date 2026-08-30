#!/usr/bin/env python3
"""Fail when a byte-verified row starts naming the wrong function.

The byte gate cannot see this class: a pin naming the wrong function still
byte-matches, so a green build proves nothing about identity. Three detectors
find it, and before this guard existed they ran only when somebody remembered
them -- which made them reports rather than checks.

Two are fast enough for the commit hook (~4s together) and run here.
null_reloc.py takes ~70s and runs in the full gate instead; see tools/build.py.

Counts only ever go DOWN. Raising a baseline to go green is the same prohibited
move as raising ORPHAN_BASELINE or appending to pin_consistency_baseline.csv:
it converts a found defect into a permanent one. Lower a number when you fix
something, and say what you fixed in the commit message.
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "reverse" / "identity_baseline.txt"

# An ANCHOR is a line the tool prints unconditionally, so its presence proves the
# output is still the format the count pattern was written against. multi_name
# tallies its verdicts and prints only the categories that occurred, so a
# category that falls to zero loses its line entirely: without an anchor there
# is no way to tell "clean" from "the format moved", and guessing either way is
# wrong. A check whose anchor is None must always print its own line.
# (label, tool, count regex, anchor regex or None)
CHECKS = [
    ("multi_name.family",
     "multi_name.py",
     re.compile(r"^\s+(\d+)\s+FOLDS HERE but the names are one family member apart", re.M),
     re.compile(r"^matched rows; addresses claimed by 2\+ names: \d+", re.M)),
    ("multi_name.different",
     "multi_name.py",
     re.compile(r"^\s+(\d+)\s+DIFFERENT BODIES - cannot share an address", re.M),
     re.compile(r"^matched rows; addresses claimed by 2\+ names: \d+", re.M)),
    ("size_outlier.indicted",
     "size_outlier.py",
     re.compile(r"none same-method or same-class=(\d+)"),
     None),
]


def read_baseline():
    if not BASELINE.exists():
        sys.exit(f"identity_guard: {BASELINE.relative_to(ROOT)} is missing. It is not "
                 f"self-seeding -- an auto-written baseline is an unreviewed free pass.")
    out = {}
    for line in BASELINE.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        key, _, value = line.partition("=")
        out[key.strip()] = int(value)
    return out


def measure():
    cache, found = {}, {}
    for label, tool, pattern, anchor in CHECKS:
        if tool not in cache:
            done = subprocess.run([sys.executable, str(ROOT / "tools" / tool)],
                                  capture_output=True, text=True, cwd=ROOT)
            if done.returncode != 0:
                sys.exit(f"identity_guard: {tool} failed:\n{done.stderr.strip()}")
            cache[tool] = done.stdout
        match = pattern.search(cache[tool])
        if match is None:
            # A silent zero here would read as "clean" -- the exact failure this
            # whole family of checks exists to catch. Read zero only when the
            # anchor proves the tool did print its tally and this category
            # simply did not occur in it.
            if anchor is None or not anchor.search(cache[tool]):
                sys.exit(f"identity_guard: could not find the {label} count in "
                         f"{tool}'s output, and its anchor line is missing too. "
                         f"The tool's format changed; fix the pattern rather "
                         f"than assuming zero.")
            found[label] = 0
            continue
        found[label] = int(match.group(1))
    return found


def main():
    baseline, found = read_baseline(), measure()
    worse = {k: (found[k], baseline[k]) for k in found
             if k in baseline and found[k] > baseline[k]}
    missing = [k for k in found if k not in baseline]
    if missing:
        sys.exit(f"identity_guard: no baseline for {', '.join(sorted(missing))}")
    if worse:
        print("identity_guard: FAIL — a row that byte-matches now names the wrong function",
              file=sys.stderr)
        for key, (now, was) in sorted(worse.items()):
            print(f"    {key}: {was} -> {now}", file=sys.stderr)
        print("    Run the detector named by the key to see which rows. The byte "
              "gate cannot catch this class; that is why this check exists.",
              file=sys.stderr)
        raise SystemExit(1)
    # A drop is good news that still fails, the way pin_consistency fails on a
    # baseline row that no longer describes a violation: a baseline left above
    # the truth is head-room the next defect slips into unnoticed.
    better = {k: (found[k], baseline[k]) for k in found if found[k] < baseline[k]}
    if better:
        print("identity_guard: FIXED — now lower the baseline in this same commit",
              file=sys.stderr)
        for key, (now, was) in sorted(better.items()):
            print(f"    {key} = {now}    (was {was})", file=sys.stderr)
        raise SystemExit(1)
    print(f"identity_guard: OK ({sum(found.values())} known identity suspects, none new)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
