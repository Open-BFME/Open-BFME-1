#!/usr/bin/env bash
# Launch the luna fleet: $1 file-lane seats, $2 big seats, $3 finish seats, $4 mid seats (300-1000 B, landed-neighbour files),
# $5 anonymous-lane seats (pick_anon.py), $6 reviewer seats (pick_review.py).
# 2026-09-15 consensus defaults: finish first, anonymous lane as the main conversion lane, no new seats overall.
# 2026-09-16: finish pool under the attempt cap is ~30 bodies, so 2 finish seats; the freed seats go to mid
# (300-2500 B, largest first) and anon (ranked by expected bytes): same 37 seats, more bytes per session.
# Retire seats with tools/fleet/retire_seat.ps1 (pass -Seats/-Stems as @() arrays via -Command, not -File).
# Weighted by measured bytes/session from build/fleet_logs (luna 1271, lunabig 672, lunafin 636).
cd "$(dirname "$0")/.." || exit 1
mkdir -p build/fleet_logs
python tools/source_donors.py --refresh || exit 1
N=${1:-10}; B=${2:-0}; F=${3:-2}; M=${4:-8}; A=${5:-15}; R=${6:-2}
launch() { nohup bash tools/fleet/seat.sh "$1" "$2" > "build/fleet_logs/seat_$1$2.supervisor.log" 2>&1 < /dev/null & disown; sleep 2; }
for i in $(seq 1 "$N"); do launch luna "$i"; done
for i in $(seq 1 "$B"); do launch lunabig "$i"; done
for i in $(seq 1 "$F"); do launch lunafin "$i"; done
for i in $(seq 1 "$M"); do launch lunamid "$i"; done
for i in $(seq 1 "$A"); do launch lunaanon "$i"; done
for i in $(seq 1 "$R"); do launch lunareview "$i"; done
nohup python tools/fleet/ledger_watchdog.py --interval 300 > build/fleet_logs/watchdog.supervisor.log 2>&1 < /dev/null & disown
nohup bash tools/fleet/harvest_loop.sh > /dev/null 2>&1 < /dev/null & disown
echo "launched $N luna + $B lunabig + $F lunafin + $M lunamid + $A lunaanon + $R lunareview, watchdog, harvest loop"
