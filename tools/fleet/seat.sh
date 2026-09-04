#!/usr/bin/env bash
# A fleet seat: keeps one engine busy. $1 = engine, $2 = seat id.
#   engines: grok | sol | luna        -> claim a whole dump file (>= 12 bodies), smallest first
#            grokbig | solbig | lunabig -> claim ONE large body (1KB..2.5KB) and stay on it
#            for up to 3 sessions while it is still a dump and the last banked partial
#            scored >= 0.5 (each session restarts from the stash)
#   luna = codex gpt-5.6-luna at reasoning effort max; sol = codex gpt-5.6-sol medium
cd "$(dirname "$0")/.." || exit 1
ENGINE="$1"; SEAT="$2"
case "$ENGINE" in
  lunahigh*) CMODEL=luna-high; CM="gpt-5.6-luna"; CE="high";;
  luna*) CMODEL=luna-max; CM="gpt-5.6-luna"; CE="max";;
  solhigh*) CMODEL=sol-high; CM="gpt-5.6-sol"; CE="high";;
  sol*)  CMODEL=sol;      CM="gpt-5.6-sol";  CE="medium";;
  *)     CMODEL=grok;;
esac
BIGNOTE="LARGE body. You have this whole session for it; previous sessions may have banked a stash (START FROM STASH line) -- continue from it, do not restart from scratch. Identify class and callees first (vtable_lookup.py, symbols.csv pins, ZH twin), get the control-flow skeleton compiling, then iterate with probe.py on the FIRST divergence only, one lever at a time (docs/shape_levers.md). Before you stop, ALWAYS bank your best attempt with re_log.py --stash and an honest --score; the next session resumes from it."

run_engine() {  # $1 brief, $2 log
  if [ "${ENGINE#grok}" != "$ENGINE" ]; then
    python tools/fleet_run.py --brief "$1" --log "$2" --engine "$ENGINE" --seat "$SEAT" -- timeout -k 60 "${SESSION_CAP:-9000}" "$HOME/.grok/bin/grok.exe" -p "$(cat "$1")" --always-approve --output-format plain < /dev/null
  else
    # codex echoes a full turn diff of the whole tree every turn (1.5GB logs seen):
    # keep only non-diff lines, capped in length
    # wall-clock cap: max-effort sessions were observed running 5h on one file
    # with nothing landed; a fresh session re-briefs from the live ledger + stashes
    python tools/fleet_run.py --brief "$1" --log "$2" --engine "$ENGINE" --seat "$SEAT" -- timeout -k 60 "${SESSION_CAP:-9000}" codex exec -m "$CM" -c "model_reasoning_effort=\"$CE\"" --sandbox danger-full-access --cd "$(pwd)" "$(cat "$1")" < /dev/null
  fi
}

while true; do
  if [ "${ENGINE%big}" != "$ENGINE" ]; then
    RVA=$(python build/pick_big.py 1 | tr -d '\r' | head -1)
    [ -z "$RVA" ] && { echo "seat $SEAT: no big body picked; retry in 60s"; sleep 60; continue; }
    for PASS in 1 2 3; do
      BEFORE=$(python tools/fleet_run.py --fingerprint "$RVA" | tr -d '\r')
      BRIEF="build/brief_seat_${ENGINE}${SEAT}_${RVA}_p${PASS}.txt"
      python tools/brief.py --rvas "$RVA" --model "$CMODEL" --limit 1 --note "$BIGNOTE (session $PASS of 3)" > "$BRIEF" 2>/dev/null || break
      LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${RVA}_p${PASS}.log"
      echo "$(date '+%H:%M') seat $ENGINE$SEAT -> $RVA p$PASS" >> build/fleet_logs/seats.log
      run_engine "$BRIEF" "$LOG"
      echo "$(date '+%H:%M') seat $ENGINE$SEAT done $RVA p$PASS" >> build/fleet_logs/seats.log
      # Repeating a score/date is not progress; require a changed preferred body.
      python tools/fleet_run.py --can-retry "$RVA" --before "$BEFORE" || break
      sleep 5
    done
  elif [ "${ENGINE%class}" != "$ENGINE" ]; then
    # class lane: the dump slots of one warm vtable (most slots already landed C++)
    python build/pick_class.py > build/.pick_class_$SEAT.txt 2>/dev/null
    RVAS=$(head -1 build/.pick_class_$SEAT.txt | sed 's/^RVAS: //' | tr -d '\r')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: no warm class picked; retry in 120s"; sleep 120; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 8 --note-file "build/.pick_class_$SEAT.txt" --note "Work the class as a unit: reuse landed slot sources and align the proposed ZH order against proven slots. Verify each name against the body's own bytes before pinning it (tools/pin_consistency.py --symbol NAME first, --check after). Probe EXACT is masked shape only; add_match.py must verify relocations before landing. Bank close bodies with re_log.py partial --stash --score." > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT -> $STEM" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT done $STEM" >> build/fleet_logs/seats.log
  elif [ "${ENGINE%mid}" != "$ENGINE" ]; then
    # mid lane: 3 bodies of 300..1000 B from one dump file whose neighbours are already C++
    case "$ENGINE" in *big*) MIDARGS="2 1000 1600";; *) MIDARGS="3 300 1000";; esac   # lunabigmid = upper window
    # shellcheck disable=SC2086
    RVAS=$(python build/pick_mid.py $MIDARGS | tr -d '\r' | tr '\n' ' ')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: no mid bodies picked; retry in 60s"; sleep 60; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 3 --note "MID-SIZE bodies (${MIDARGS#* } B window) from one dump file whose address neighbours are ALREADY landed as real C++. Before writing anything: rg the neighbouring landed rows in reverse/functions.csv (addresses just below and above each target), open those .cpp files and reuse their class layouts, pins, callee declarations and cl: flags -- they were proven against retail. Then identity from symbols.csv pins and the ZH twin, skeleton compiling, probe.py on the FIRST divergence only, one lever at a time (docs/shape_levers.md). Land each body with add_match.py as soon as it is EXACT; after ~35 min on one body bank it (re_log.py partial --stash --score) and move to the next. Never leave without banking your best attempt for every body you touched." > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT -> $STEM" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT done $STEM" >> build/fleet_logs/seats.log
  elif [ "${ENGINE%fin}" != "$ENGINE" ]; then
    # finish lane: 2 bodies whose banked partial scored >= 0.9, start from the stash
    RVAS=$(python build/pick_finish.py 4 0.9 | tr -d '\r' | tr '\n' ' ')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: no finish bodies picked; retry in 60s"; sleep 60; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 4 --note "NEAR-LANDED bodies: each has a banked stash scoring 0.9+ (START FROM STASH line). Do not rewrite from scratch. Compile the stash, run probe.py, and work ONLY the first divergence with one lever at a time from docs/shape_levers.md (register mirror = local definition order / loads above guard / IAT CSE; sib-order; eh-transposition; fall-through flag tail). Land with add_match.py; if still short, re-bank with an honest score and what you tried." > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT -> $STEM" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT done $STEM" >> build/fleet_logs/seats.log
  else
    FILE=$(python build/pick_file.py 12 | tr -d '\r')
    [ -z "$FILE" ] && { echo "seat $SEAT: no file picked; retry in 60s"; sleep 60; continue; }
    STEM=$(basename "$FILE" .asm)
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    python tools/brief.py --dump "$FILE" --model "$CMODEL" --limit 40 > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $FILE"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT -> $STEM" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT done $STEM" >> build/fleet_logs/seats.log
  fi
  sleep 5
done
