#!/usr/bin/env bash
# One-off lead-directed luna session: $1 = tag, $2 = brief file. No loop; logs like a seat.
cd "$(dirname "$0")/.." || exit 1
TAG="$1"; BRIEF="$2"; LOG="build/fleet_logs/seat_unblock_${TAG}.log"
echo "$(date '+%H:%M') seat unblock -> $TAG" >> build/fleet_logs/seats.log
timeout -k 60 "${SESSION_CAP:-9000}" codex exec -m gpt-5.6-luna -c 'model_reasoning_effort="max"' --sandbox danger-full-access --cd "$(pwd)" "$(cat "$BRIEF")" 2>&1 < /dev/null \
  | grep -a -v -E '^(diff --git |index [0-9a-f]+[.][.]|[+][+][+] |--- |@@ |[-+])' | cut -c1-400 > "$LOG"
echo "$(date '+%H:%M') seat unblock done $TAG" >> build/fleet_logs/seats.log
