#!/usr/bin/env bash
# One-off lead-directed luna session: $1 = tag, $2 = brief file. No loop; logs like a seat.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1  # works from tools/fleet/ or a build/ copy
TAG="$1"; BRIEF="$2"; LOG="build/fleet_logs/seat_unblock_${TAG}.log"
echo "$(date '+%H:%M') seat unblock assigned $TAG" >> build/fleet_logs/seats.log
python tools/fleet_run.py --brief "$BRIEF" --log "$LOG" --engine lunablock --seat "unblock_${TAG}" -- \
  timeout -k 60 "${SESSION_CAP:-9000}" codex exec -m gpt-5.6-luna -c 'model_reasoning_effort="max"' \
  --sandbox danger-full-access --cd "$(pwd)" - < /dev/null
RC=$?
echo "$(date '+%H:%M') seat unblock finished $TAG exit=$RC" >> build/fleet_logs/seats.log
exit "$RC"
