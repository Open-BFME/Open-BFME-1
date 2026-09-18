#!/usr/bin/env bash
# Every 15 min: repair mechanical ledger states, then commit+push fleet landings.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1  # works from tools/fleet/ or a build/ copy
# started from PowerShell/Task Scheduler the Git usr/bin is not on PATH (date, sleep: command not found)
export PATH="/usr/bin:/mingw64/bin:$PATH"
while true; do
  sleep 900
  {
    python tools/fleet/ledger_prep.py
    python tools/fleet/harvest.py "Open-BFME6: fleet harvest $(date '+%m-%d %H:%M')" || python tools/dedup_csv.py
  } >> build/fleet_logs/harvest.log 2>&1
done
