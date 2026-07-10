#!/usr/bin/env python3
"""Record a structural/manual-RE attempt so no agent re-walks a dead end.

    python3 tools/log_attempt.py '<decorated-symbol>' <outcome> 'what you tried / learned'

Outcomes:
  landed    matched and committed (next_work drops the row via the ledger anyway)
  no-match  tried and failed; note MUST say which shapes were tried
  dead      provably unmatchable as-is (inlined/folded/SEH/absent) — note the proof
  blocked   needs something first (callee pins, shim, header layout) — note what

Appends one TAB-separated line to reverse/re_attempts.log (union-merged like the
ledgers). next_work.py hides structural rows with outcome=dead or >= 3 attempts.
"""
import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LOG = ROOT / "reverse" / "re_attempts.log"
OUTCOMES = ("landed", "no-match", "dead", "blocked")


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("function", help="exact decorated symbol")
    parser.add_argument("outcome", choices=OUTCOMES)
    parser.add_argument("note", help="what you tried / proved — the next agent reads this")
    args = parser.parse_args()

    if not args.note.strip():
        raise SystemExit("an empty note helps nobody — say what you tried")
    if "\t" in args.function or "\t" in args.note or "\n" in args.note:
        raise SystemExit("no tabs/newlines in fields (TSV file)")

    with LOG.open("a", encoding="utf-8") as fh:
        fh.write(f"{args.function}\t{args.outcome}\t{args.note}\n")
    print(f"logged: {args.function} -> {args.outcome}")


if __name__ == "__main__":
    main()
