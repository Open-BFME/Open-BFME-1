#!/usr/bin/env python3
"""Update the tracked reloc-names table from the last full gate, explicitly.

The full gate (tools/build.py write_reloc_names) regenerates the table into
build/reloc_names.generated.csv. It used to overwrite the tracked
targets/game/reverse/reloc_names.csv, so every full gate left the tree
dirty and the push hook's post-gate snapshot check refused the push
(2026-09-30 landing window). The tracked copy -- the one next_work.py,
red_rows.py and the tests read -- now changes only here, in its own commit.

  python3 tools/reloc_names.py status    # rows added/removed vs the tracked copy
  python3 tools/reloc_names.py promote   # copy the generated table over it
"""
import argparse
import csv
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TRACKED = ROOT / "targets/game/reverse" / "reloc_names.csv"
GENERATED = ROOT / "build" / "reloc_names.generated.csv"


def rows(path):
    with path.open(newline="", encoding="utf-8") as handle:
        return {tuple(r.values()) for r in csv.DictReader(handle)}


def diff(tracked=None, generated=None):
    """(added, removed) row counts, or None when no generated table exists."""
    tracked, generated = tracked or TRACKED, generated or GENERATED
    if not generated.exists():
        return None
    old = rows(tracked) if tracked.exists() else set()
    new = rows(generated)
    return len(new - old), len(old - new)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["status", "promote"])
    args = ap.parse_args(argv)
    change = diff()
    if change is None:
        print(f"reloc_names: no {GENERATED.relative_to(ROOT)}; run the full gate first", file=sys.stderr)
        return 1
    added, removed = change
    print(f"reloc_names: generated vs tracked: +{added} -{removed} row(s)")
    if args.action == "promote" and (added or removed):
        shutil.copyfile(GENERATED, TRACKED)
        print(f"reloc_names: {TRACKED.relative_to(ROOT)} updated; review and commit it on its own")
    return 0


if __name__ == "__main__":
    sys.exit(main())
