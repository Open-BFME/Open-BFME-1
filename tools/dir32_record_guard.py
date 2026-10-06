#!/usr/bin/env python3
"""dir32_addresses.csv is evidence the gate reads, so a commit may not write it freely.

verify_dir32_addresses trusts a recorded (name, va) pair: every reference must
give the name that address. A hand-added line was therefore a free pass for a
new decorated name at any address (the red team's "wrong global" exploit), and
a hand-edited address moved every reference's expectation at once.

  * An address already recorded for a name may not change. A wrong record is
    corrected by deleting the line (the next full gate re-proposes it), never
    by rewriting it in a commit that also moves the references.
  * A deleted line is allowed: the record only shrinks by hand.
  * An added line must be one the tool would accept for an unrecorded name:
    build.unrecorded_dir32_problem against the record as of the base
    revision, so the added lines cannot vouch for each other.

Usage: python3 tools/dir32_record_guard.py --staged [BASE]     (BASE defaults to HEAD)
"""
import csv
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

REL = build.DIR32_ADDRESSES.relative_to(build.ROOT).as_posix()


def read_at(spec):
    shown = subprocess.run(["git", "show", spec], cwd=build.ROOT, capture_output=True)
    if shown.returncode != 0:
        return None
    rows = csv.DictReader(shown.stdout.decode("utf-8").splitlines())
    return {row["name"]: int(row["va"], 16) for row in rows}


def problems(old, new, symbol_map=None):
    out = []
    for name in sorted(old.keys() & new.keys()):
        if old[name] != new[name]:
            out.append(f"{name}: recorded 0x{old[name]:08X} rewritten to 0x{new[name]:08X}; "
                       "delete the line instead and let the full gate re-propose it")
    added = sorted(new.keys() - old.keys())
    if added:
        identities = build.dir32_identities(old)
        if symbol_map is None:
            symbol_map = build.load_symbol_map()
        for name in added:
            problem = build.unrecorded_dir32_problem(name, new[name], identities, symbol_map)
            if problem:
                out.append(f"{name},0x{new[name]:08X} added: {problem}")
    return out


def main(argv):
    if not argv or argv[0] != "--staged":
        sys.exit(__doc__)
    base = argv[1] if len(argv) > 1 else "HEAD"
    old, new = read_at(f"{base}:{REL}"), read_at(f":{REL}")
    if new is None:
        sys.exit(f"dir32_record_guard: {REL} is not in the index")
    found = problems(old or {}, new)
    if found:
        print(f"dir32_record_guard: FAIL {len(found)} change(s) to {REL} the gate did not make")
        for line in found[:20]:
            print("    " + line)
        return 1
    print(f"dir32_record_guard: OK ({len(old or {})} -> {len(new)} recorded names)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
