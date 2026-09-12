#!/usr/bin/env python3
"""Run the whole byte gate and report every matched row that no longer verifies.

The commit hooks byte-verify only the sources a commit touches, so a row can rot
-- a shared header edit, a toolchain bump, a neighbouring body moving a label --
while progress.py keeps counting it as matched. Nothing else in this repo runs
the full gate on purpose, which is why every red row found so far was found by
accident.

  python3 tools/red_rows.py

Prints the failing rows and one total line; the gate's byte dumps stay in the
gate. Exit 0 means the gate ran to completion with every row green. A gate that
dies before it reaches byte comparison -- a TU that will not compile exits 2 --
gets its own verdict and never reads as zero red rows: that wall once hid twelve
hours of commits.
"""
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RELOC_NAMES = ROOT / "reverse" / "reloc_names.csv"
FAIL_RE = re.compile(r"^  FAIL (?P<name>.+) \((?P<source>[^()]*)\)$")


def run_gate():
    """Run ./build.sh over every row; return (exit code, output)."""
    env = dict(os.environ)
    # build.py reserves BUILD_POOL=8 for the full-suite audit that runs alone
    # under the host-wide build lock. This is that audit.
    env.setdefault("BUILD_POOL", "8")
    result = subprocess.run([str(ROOT / "build.sh")], cwd=ROOT, env=env, text=True,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    return result.returncode, result.stdout


def report(code, output, reloc_rewritten):
    failures = [match.group("name", "source")
                for match in map(FAIL_RE.match, output.splitlines()) if match]
    for name, source in failures:
        print(f"RED {name} ({source})")
    print("reverse/reloc_names.csv: "
          + ("REWRITTEN by this run - commit or discard it" if reloc_rewritten
             else "unchanged"))
    if failures:
        print(f"{len(failures)} red row(s) (gate exit {code})")
    elif code:
        print(f"gate exit {code} with no failing row: it failed before it "
              "reached byte comparison")
        # Whatever killed it is the only actionable thing in the whole run, and
        # it is nowhere else: this is the gate's only console.
        print("\n".join(output.splitlines()[-20:]), file=sys.stderr)
    else:
        print("0 red rows")
    return 1 if failures or code else 0


def main():
    print("running the full byte gate (~10-20 min; a host-wide lock serializes "
          "it against sibling clones)...", file=sys.stderr)
    before = RELOC_NAMES.read_bytes()
    code, output = run_gate()
    return report(code, output, RELOC_NAMES.read_bytes() != before)


if __name__ == "__main__":
    sys.exit(main())
