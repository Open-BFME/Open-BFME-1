#!/usr/bin/env python3
"""What did a seat's last session produce? Landings and banks, by run id.

Measured 2026-09-25 (efdc0c4dd7..9c9c8b35d0): 3,807 verdict rows against 637
landed rows, and one host made 727 commits that added 28 ledger lines -- seats
kept drawing bodies they could not land and wrote `blocked` rows all day.
fleet_run tags every add_match note and re_log row with run=<id> (run_tag), so
a session's yield is countable without trusting its transcript. seat.sh pauses
a seat after FLEET_DRY_LIMIT sessions in a row with no landing and no bank.

  python3 tools/fleet/session_yield.py --engine luna --seat 3
prints `<run id> landed=<n> banked=<n> verdicts=<n>` for that seat's latest
finished run; exit 0 when it produced a landing or a bank, 1 when dry, 2 when
there is no finished run to judge (aborted runs never count as dry: they are
the fast-fail backoff's business).
"""
import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def latest_run(engine, seat, runs=None):
    runs = Path(runs or ROOT / "build" / "fleet_runs")
    best = None
    for record in runs.glob("*/record.json"):
        try:
            data = json.loads(record.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            continue
        if data.get("engine") != engine or str(data.get("seat")) != str(seat):
            continue
        if data.get("status") != "finished":
            continue
        if best is None or data.get("start", 0) > best.get("start", 0):
            best = data
    return best


def run_yield(run_id, functions=None, attempts=None):
    """(landed rows, banked partials, verdict rows) carrying run=<run_id>."""
    token = f"run={run_id}"
    functions = Path(functions or ROOT / "reverse" / "functions.csv")
    attempts = Path(attempts or ROOT / "reverse" / "re_attempts.log")
    landed = sum(1 for line in functions.read_text(encoding="utf-8", errors="replace").splitlines()
                 if token in line and ",matched," in line)
    banked = verdicts = 0
    for line in attempts.read_text(encoding="utf-8", errors="replace").splitlines():
        if token not in line:
            continue
        fields = line.split("\t")
        verdicts += 1
        if len(fields) > 3 and fields[3] == "partial":
            banked += 1
    return landed, banked, verdicts


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--engine", required=True)
    ap.add_argument("--seat", required=True)
    args = ap.parse_args(argv)
    run = latest_run(args.engine, args.seat)
    if not run:
        print("no finished run")
        return 2
    landed, banked, verdicts = run_yield(run["id"])
    print(f"{run['id']} landed={landed} banked={banked} verdicts={verdicts}")
    return 0 if landed or banked else 1


if __name__ == "__main__":
    sys.exit(main())
