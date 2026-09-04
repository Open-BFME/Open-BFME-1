#!/usr/bin/env bash
# Launch the luna fleet: $1 file-lane seats, $2 big seats, $3 finish seats, $4 mid seats (300-1000 B, landed-neighbour files).
# Retire seats with build/retire_seat.ps1 (pass -Seats/-Stems as @() arrays via -Command, not -File).
# Weighted by measured bytes/session from build/fleet_logs (luna 1271, lunabig 672, lunafin 636).
cd "$(dirname "$0")/.." || exit 1
mkdir -p build/fleet_logs
python tools/source_donors.py --refresh || exit 1
N=${1:-25}; B=${2:-0}; F=${3:-5}; M=${4:-10}
launch() { nohup bash build/seat.sh "$1" "$2" > "build/fleet_logs/seat_$1$2.supervisor.log" 2>&1 < /dev/null & disown; sleep 2; }
for i in $(seq 1 "$N"); do launch luna "$i"; done
for i in $(seq 1 "$B"); do launch lunabig "$i"; done
for i in $(seq 1 "$F"); do launch lunafin "$i"; done
for i in $(seq 1 "$M"); do launch lunamid "$i"; done
nohup python build/ledger_watchdog.py --interval 300 > build/fleet_logs/watchdog.supervisor.log 2>&1 < /dev/null & disown
nohup bash build/harvest_loop.sh > /dev/null 2>&1 < /dev/null & disown
echo "launched $N luna + $B lunabig + $F lunafin + $M lunamid, watchdog, harvest loop"
