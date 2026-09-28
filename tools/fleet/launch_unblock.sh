#!/usr/bin/env bash
# One-off lead-directed session (gpt-6-astra by default; UNBLOCK_MODEL/UNBLOCK_EFFORT override): $1 = tag, $2 = brief file. No loop; logs like a seat.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1  # works from tools/fleet/ or a build/ copy
TAG="$1"; BRIEF="$2"; LOG="build/fleet_logs/seat_unblock_${TAG}.log"
echo "$(date '+%H:%M') seat unblock assigned $TAG" >> build/fleet_logs/seats.log
python tools/fleet_run.py --brief "$BRIEF" --log "$LOG" --engine lunablock --seat "unblock_${TAG}" -- \
  timeout -k 60 "${SESSION_CAP:-9000}" codex exec -m "${UNBLOCK_MODEL:-gpt-6-astra}" -c "model_reasoning_effort=\"${UNBLOCK_EFFORT:-high}\"" \
  --sandbox danger-full-access --cd "$(pwd)" - < /dev/null
RC=$?
echo "$(date '+%H:%M') seat unblock finished $TAG exit=$RC" >> build/fleet_logs/seats.log
exit "$RC"
