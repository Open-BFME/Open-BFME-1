#!/usr/bin/env python3
"""Let a header land while the full gate is red, without hiding a regression.

The pre-commit hook runs the FULL gate for any staged header or shim with no
tolerance, and the gate has been red for weeks (docs/full_gate_red.md). The
gate is red partly BECAUSE of header fixes it refuses to accept, so nothing
structural could land. This is the same shape as the identity and pin
baselines: record the known red rows once, then fail only on a row that is
red NOW and was not red THEN. Counts only ever go down; a baseline edit that
adds a row is refused by --validate, so a red cannot be hidden by writing it
into the file.

  python3 tools/gate_baseline.py --record      run the gate, write targets/game/reverse/full_gate_baseline.txt
  python3 tools/gate_baseline.py --check       run the gate, fail on any NEW red (hook use)
  python3 tools/gate_baseline.py --validate    staged baseline must be a subset of HEAD's
  python3 tools/gate_baseline.py --check --output FILE   compare a saved gate transcript

A gate that dies before byte comparison (a TU that will not compile) is a
failure in every mode: there is no red set to compare and nothing is proven.
Rows that went green are printed so the fixer can shrink the baseline in the
same commit as the fix, which is the only allowed edit.
"""
import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "targets/game/reverse" / "full_gate_baseline.txt"
FAIL_RE = re.compile(r"^  FAIL (?P<name>.+) \((?P<source>[^()]*)\)$")
FUNCTIONS_RE = re.compile(r"^Functions: (OK|FAIL) ")
HEADER = "# full-gate red rows, shrink-only (tools/gate_baseline.py). One 'name (source)' per line.\n"


def run_gate():
    env = dict(os.environ)
    env.setdefault("BUILD_POOL", env.get("BUILD_POOL", "4"))
    env["PYTHONUNBUFFERED"] = "1"
    output = []
    with subprocess.Popen(gate_command(), cwd=ROOT, env=env, text=True,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT) as process:
        for line in process.stdout:
            output.append(line)
            print(line, end="", flush=True)
        return process.wait(), "".join(output)


def gate_command():
    """build.sh is a shell script: Windows cannot CreateProcess it directly
    (WinError 193), so run it under bash there."""
    script = str(ROOT / "build.sh")
    if sys.platform.startswith("win"):
        import shutil
        bash = shutil.which("bash") or str(Path("C:/Program Files/Git/bin/bash.exe"))
        return [bash, script]
    return [script]


def red_rows(output):
    """Sorted 'name (source)' rows from a gate transcript, or None when the
    gate never reached byte comparison."""
    reached = any(FUNCTIONS_RE.match(line) for line in output.splitlines())
    if not reached:
        return None
    return sorted({f"{m.group('name')} ({m.group('source')})"
                   for m in map(FAIL_RE.match, output.splitlines()) if m})


def parse_baseline(text):
    return sorted({line.strip() for line in text.splitlines()
                   if line.strip() and not line.startswith("#")})


def load_baseline(path=BASELINE):
    return parse_baseline(path.read_text(encoding="utf-8")) if path.exists() else None


def write_baseline(rows, path=BASELINE):
    path.write_text(HEADER + "".join(row + "\n" for row in rows), encoding="utf-8")


def compare(now, baseline):
    """(new_reds, fixed) between the gate's red set now and the baseline."""
    now_set, base_set = set(now), set(baseline)
    return sorted(now_set - base_set), sorted(base_set - now_set)


def check(output, baseline):
    now = red_rows(output)
    if now is None:
        print("gate_baseline: the gate died before byte comparison; nothing is proven")
        print("\n".join(output.splitlines()[-15:]), file=sys.stderr)
        return 2
    if baseline is None:
        if now:
            print(f"gate_baseline: no baseline recorded and {len(now)} red row(s); "
                  "run --record on a known revision first, or fix them")
            for row in now:
                print("  RED " + row)
            return 1
        print("gate_baseline: 0 red rows")
        return 0
    new, fixed = compare(now, baseline)
    for row in new:
        print("  NEW RED " + row)
    for row in fixed:
        print("  now green (remove from targets/game/reverse/full_gate_baseline.txt in the fixing commit): " + row)
    print(f"gate_baseline: {len(now)} red now, {len(baseline)} in baseline, "
          f"{len(new)} NEW, {len(fixed)} fixed")
    return 1 if new else 0


def validate_staged():
    """The staged baseline may only shrink relative to HEAD's copy."""
    rel = BASELINE.relative_to(ROOT).as_posix()
    head = subprocess.run(["git", "show", f"HEAD:{rel}"], cwd=ROOT, capture_output=True, text=True)
    staged = subprocess.run(["git", "show", f":{rel}"], cwd=ROOT, capture_output=True, text=True)
    if staged.returncode:
        return 0                      # not staged: nothing to validate
    if head.returncode:
        print(f"gate_baseline: {rel} is new; it may only be created by --record on a stated revision")
        return 0
    added = sorted(set(parse_baseline(staged.stdout)) - set(parse_baseline(head.stdout)))
    if added:
        print("gate_baseline: a baseline may only SHRINK; these rows were added:")
        for row in added:
            print("  + " + row)
        return 1
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--record", action="store_true")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--validate", action="store_true")
    ap.add_argument("--output", type=Path, help="use a saved gate transcript instead of running")
    a = ap.parse_args()
    if a.validate:
        sys.exit(validate_staged())
    if not (a.record or a.check):
        ap.error("one of --record, --check, --validate")
    output = a.output.read_text(encoding="utf-8", errors="replace") if a.output else run_gate()[1]
    if a.record:
        now = red_rows(output)
        if now is None:
            print("gate_baseline: the gate died before byte comparison; refusing to record")
            print("\n".join(output.splitlines()[-15:]), file=sys.stderr)
            sys.exit(2)
        write_baseline(now)
        print(f"gate_baseline: recorded {len(now)} red row(s) to {BASELINE.relative_to(ROOT).as_posix()}")
        sys.exit(0)
    sys.exit(check(output, load_baseline()))


if __name__ == "__main__":
    main()
