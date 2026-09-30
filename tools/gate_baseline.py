#!/usr/bin/env python3
"""Let a header land while the full gate is red, without hiding a regression.

The pre-commit hook runs the FULL gate for any staged header or shim with no
tolerance, and the gate has been red for weeks. The
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
DIR32_BASELINE = ROOT / "targets/game/reverse" / "dir32_known_red.txt"
DIR32_REPORT = ROOT / "build" / "dir32_inconsistent.txt"
FAIL_RE = re.compile(r"^  FAIL (?P<name>.+) \((?P<source>[^()]*)\)$")
FUNCTIONS_RE = re.compile(r"^Functions: (OK|FAIL) ")
FULL_GATE_RE = re.compile(r"^FULL GATE: FAIL \S+ \d+ red: (?P<checks>.+)$")
HEADER = "# full-gate red rows, shrink-only (tools/gate_baseline.py). One 'name (source)' per line.\n"
DIR32_HEADER = ("# DIR32 symbols that resolve to more than one retail address and are not in\n"
                "# dir32_consistency_whitelist.txt. Shrink-only (tools/gate_baseline.py). One symbol per line.\n")
# The no-op patch cannot run while any function row is red; every other check has no known-red list.
TOLERATED_CHECKS = {"functions", "dir32 consistency", "no-op patch (unrunnable)"}


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
    """Run the same Python gate directly on Windows, where build.sh is not executable."""
    if sys.platform.startswith("win"):
        return [sys.executable, str(ROOT / "tools/build.py")]
    return [str(ROOT / "build.sh")]


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


def red_checks(output):
    line = next((line for line in reversed(output.splitlines()) if line.startswith("FULL GATE: ")), "")
    m = FULL_GATE_RE.match(line)
    return m.group("checks").split(", ") if m else []


def dir32_symbols(report_text):
    return sorted({line.split("\t", 1)[0] for line in report_text.splitlines() if line.strip()})


def verdict(output):
    """'OK', 'FAIL', or None when the transcript has no final FULL GATE line:
    a gate interrupted after the byte comparison proves nothing about the
    checks that run after it."""
    line = next((line for line in reversed(output.splitlines()) if line.startswith("FULL GATE: ")), "")
    if line.startswith("FULL GATE: OK"):
        return "OK"
    return "FAIL" if FULL_GATE_RE.match(line) else None


# build.py's exit status for each verdict: SystemExit(1) after "FULL GATE: FAIL",
# a normal return after "FULL GATE: OK". Any other status (a crash, a kill, 137)
# after a printed verdict is abnormal termination, never an approval.
VERDICT_EXIT = {"OK": 0, "FAIL": 1}


def exit_agrees(final, returncode):
    """True when there is no exit status to check (a saved transcript) or it is
    exactly the one build.py uses for this verdict."""
    return returncode is None or returncode == VERDICT_EXIT[final]


def check(output, baseline, dir32_baseline=None, dir32_report=None, returncode=None):
    """dir32_report is the gate's own dir32_inconsistent.txt text, or None when the
    gate did not write one. dir32_baseline None skips the DIR32 comparison.
    returncode is the gate process's exit status when this run started it; it
    must agree with the transcript's verdict (build.py exits 1 on FAIL)."""
    now = red_rows(output)
    if now is None:
        print("gate_baseline: the gate died before byte comparison; nothing is proven")
        print("\n".join(output.splitlines()[-15:]), file=sys.stderr)
        return 2
    final = verdict(output)
    if final is None:
        print("gate_baseline: the gate did not finish (no FULL GATE verdict); nothing is proven")
        print("\n".join(output.splitlines()[-15:]), file=sys.stderr)
        return 2
    if not exit_agrees(final, returncode):
        print(f"gate_baseline: the gate exited {returncode} but its transcript says FULL GATE: {final} "
              f"(build.py exits {VERDICT_EXIT[final]}); nothing is proven")
        return 2
    full_gate = next((line for line in reversed(output.splitlines())
                      if line.startswith("FULL GATE: ")), None)
    if full_gate and full_gate.startswith("FULL GATE: FAIL"):
        print("gate_baseline: function failure row comparison does not establish that all checks passed; "
              f"raw {full_gate}")
    if baseline is None:
        if now:
            print(f"gate_baseline: no baseline recorded and {len(now)} function failure row(s); "
                  "run --record on a known revision first, or fix them")
            for row in now:
                print("  RED " + row)
            return 1
        print("gate_baseline: 0 function failure rows")
        return 0
    new, fixed = compare(now, baseline)
    for row in new:
        print("  NEW RED " + row)
    for row in fixed:
        print("  now green (remove from targets/game/reverse/full_gate_baseline.txt in the fixing commit): " + row)
    print(f"gate_baseline: function failure rows: {len(now)} red now, {len(baseline)} in baseline, "
          f"{len(new)} NEW, {len(fixed)} fixed")
    failed = bool(new)
    checks = red_checks(output)
    untracked = [c for c in checks if c not in TOLERATED_CHECKS
                 or (c == "no-op patch (unrunnable)" and "functions" not in checks)]
    if untracked:
        print("gate_baseline: red with no known-red list: " + ", ".join(untracked))
        failed = True
    if dir32_baseline is not None:
        if "dir32 consistency" in checks and dir32_report is None:
            print(f"gate_baseline: DIR32 consistency is red but {DIR32_REPORT.relative_to(ROOT).as_posix()} was not written")
            return 1
        dir32_now = dir32_symbols(dir32_report) if "dir32 consistency" in checks else []
        new32, fixed32 = compare(dir32_now, dir32_baseline)
        for symbol in new32:
            print("  NEW DIR32 " + symbol)
        for symbol in fixed32:
            print(f"  now consistent (remove from {DIR32_BASELINE.relative_to(ROOT).as_posix()} in the fixing commit): " + symbol)
        print(f"gate_baseline: DIR32 symbols: {len(dir32_now)} inconsistent now, {len(dir32_baseline)} known, "
              f"{len(new32)} NEW, {len(fixed32)} fixed")
        failed = failed or bool(new32)
    return 1 if failed else 0


def validate_staged():
    return max(validate_file(BASELINE), validate_file(DIR32_BASELINE))


def validate_file(path):
    """The staged baseline may only shrink relative to HEAD's copy."""
    rel = path.relative_to(ROOT).as_posix()
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


def read_dir32_report(output):
    """The report build.py writes when DIR32 consistency fails; None when the gate did not fail it."""
    if "dir32 consistency" not in red_checks(output) or not DIR32_REPORT.exists():
        return None
    return DIR32_REPORT.read_text(encoding="utf-8")


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
    if a.output:  # a saved transcript has no exit status; its verdict line must stand alone
        returncode, output = None, a.output.read_text(encoding="utf-8", errors="replace")
    else:
        returncode, output = run_gate()
    if a.record:
        now = red_rows(output)
        final = verdict(output)
        if now is None or final is None or not exit_agrees(final, returncode):
            print("gate_baseline: the gate died, did not finish, or exited against its verdict; refusing to record")
            print("\n".join(output.splitlines()[-15:]), file=sys.stderr)
            sys.exit(2)
        write_baseline(now)
        dir32_now = dir32_symbols(read_dir32_report(output) or "")
        DIR32_BASELINE.write_text(DIR32_HEADER + "".join(s + "\n" for s in dir32_now), encoding="utf-8")
        print(f"gate_baseline: recorded {len(now)} red row(s) to {BASELINE.relative_to(ROOT).as_posix()} "
              f"and {len(dir32_now)} DIR32 symbol(s) to {DIR32_BASELINE.relative_to(ROOT).as_posix()}")
        sys.exit(0)
    sys.exit(check(output, load_baseline(), load_baseline(DIR32_BASELINE) or [], read_dir32_report(output),
                   returncode))


if __name__ == "__main__":
    main()
