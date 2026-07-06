#!/usr/bin/env python3
"""Re-locate cascade: harvest functions that a growing match set has unlocked.

locate.py skips a function when one of its callees is not yet a known function
start (the callee-gate). Every time a batch of new functions is matched — by a
local harvest OR by an external contribution landing on master — some previously
callee-gated functions become placeable, because the newly-matched functions are
now known starts. Re-running `locate --emit` across every tracked .cpp harvests
them for free. This converges in a few passes (each pass's new matches can unlock
the next). Validated 2026-07-06: one pass after a merged FX-parser PR cascaded +93.

Run after any significant harvest and after pulling external commits:

    python3 tools/relocate_cascade.py          # one emit pass over all sources
    python3 tools/relocate_cascade.py --loop    # repeat until a pass emits 0

It only appends candidate rows (status=matched) and de-dups; it never edits source
or headers. ALWAYS follow with a full `./build.sh` — the byte comparison is the
judge, and a wrong-address candidate simply fails and must be dropped. Then strip
now-matched `// ?<name> present-unmatched` markers from the affected sources.
"""
import subprocess, sys, csv, re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "reverse" / "functions.csv"


def sources():
    seen = []
    for row in csv.DictReader(FUNCTIONS.open()):
        s = row["source"]
        if s.endswith(".cpp") and s not in seen and (ROOT / s).exists():
            seen.append(s)
    return sorted(seen)


def one_pass():
    total = 0
    for s in sources():
        try:
            out = subprocess.run(
                ["python3", str(ROOT / "tools" / "locate.py"), s, "--emit"],
                cwd=ROOT, capture_output=True, text=True, timeout=300,
            ).stdout
        except subprocess.TimeoutExpired:
            continue
        m = re.search(r"emitted (\d+) row", out)
        if m and int(m.group(1)) > 0:
            n = int(m.group(1))
            total += n
            print(f"  +{n:4d} {s}")
    if total:
        subprocess.run(["python3", str(ROOT / "tools" / "dedup_csv.py")], cwd=ROOT,
                       capture_output=True)
    return total


def main():
    loop = "--loop" in sys.argv
    grand = 0
    while True:
        print("--- cascade pass ---")
        n = one_pass()
        grand += n
        print(f"pass emitted {n}")
        if not loop or n == 0:
            break
    print(f"total emitted this run: {grand}")
    if grand:
        print("NOW: run ./build.sh to verify, drop any FAIL rows, strip now-matched markers, commit.")


if __name__ == "__main__":
    main()
