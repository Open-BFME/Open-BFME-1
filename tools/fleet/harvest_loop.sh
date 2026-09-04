#!/usr/bin/env bash
# Every 15 min: repair mechanical ledger states, then commit+push fleet landings.
cd "$(dirname "$0")/.." || exit 1
while true; do
  sleep 900
  {
    python build/ledger_prep.py
    python build/harvest.py "Open-BFME6: fleet harvest $(date '+%m-%d %H:%M')" || python tools/dedup_csv.py
  } >> build/fleet_logs/harvest.log 2>&1
done
