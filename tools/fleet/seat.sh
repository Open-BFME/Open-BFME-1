#!/usr/bin/env bash
# A fleet seat: keeps one engine busy. $1 = engine, $2 = seat id.
#   engines: grok | sol | luna        -> claim a whole dump file (>= 12 bodies), smallest first
#            lunaclass               -> the open dump slots of one warm vtable, worked as a unit (pick_class.py)
#            lunablock               -> up to 12 open bodies that share one blocker family (pick_blocker.py)
#            lunaanon                -> 2 anonymous dump bodies, warmest evidence pack first (pick_anon.py)
#            lunareview              -> review 2 banked bodies 0.5..0.95 for identity/layout/convention (pick_review.py)
#            grokbig | solbig | lunabig -> claim ONE large body (1KB..2.5KB) and stay on it
#            for up to 3 sessions while it is still a dump and the last banked partial
#            scored >= 0.5 (each session restarts from the stash)
#   luna = codex gpt-5.6-luna at reasoning effort max; sol = codex gpt-5.6-sol medium
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1  # works from tools/fleet/ or a build/ copy
ENGINE="$1"; SEAT="$2"
case "$ENGINE" in
  lunahigh*) CMODEL=luna-high; CM="gpt-5.6-luna"; CE="high";;
  lunaxhigh*) CMODEL=luna-xhigh; CM="gpt-5.6-luna"; CE="xhigh";;
  luna*) CMODEL=luna-max; CM="gpt-5.6-luna"; CE="max";;
  solhigh*) CMODEL=sol-high; CM="gpt-5.6-sol"; CE="high";;
  sol*)  CMODEL=sol;      CM="gpt-5.6-sol";  CE="medium";;
  *)     CMODEL=grok;;
esac
BIGNOTE="LARGE body. You have this whole session for it; previous sessions may have banked a stash (START FROM STASH line) -- continue from it, do not restart from scratch. Identify class and callees first (vtable_lookup.py, symbols.csv pins, ZH twin), get the control-flow skeleton compiling, then iterate with probe.py on the FIRST divergence only, one lever at a time (docs/shape_levers.md). Before you stop, ALWAYS bank your best attempt with re_log.py --stash and an honest --score; the next session resumes from it."

engine_once() {  # $1 brief, $2 log
  if [ "${ENGINE#grok}" != "$ENGINE" ]; then
    python tools/fleet_run.py --brief "$1" --log "$2" --engine "$ENGINE" --seat "$SEAT" -- timeout -k 60 "${SESSION_CAP:-9000}" "$HOME/.grok/bin/grok.exe" -p "$(cat "$1")" --always-approve --output-format plain < /dev/null
  else
    # codex echoes a full turn diff of the whole tree every turn (1.5GB logs seen):
    # keep only non-diff lines, capped in length
    # wall-clock cap: max-effort sessions were observed running 5h on one file
    # with nothing landed; a fresh session re-briefs from the live ledger + stashes
    python tools/fleet_run.py --brief "$1" --log "$2" --engine "$ENGINE" --seat "$SEAT" -- timeout -k 60 "${SESSION_CAP:-9000}" codex exec -m "$CM" -c "model_reasoning_effort=\"$CE\"" --sandbox danger-full-access --cd "$(pwd)" - < /dev/null  # fleet_run feeds the brief on stdin: a 30 KB brief as an argument is "Argument list too long"
  fi
}

# A session that dies at once (quota, network, a bad command line) must not spin:
# on 2026-09-18 a usage limit produced 2,680 instant failures in one day, each
# one picking fresh targets. Back off 60 s doubling to 30 min; a usage-limit
# message goes straight to 30 min. fleet_run marks such a run "aborted", so its
# targets do not cool down.
FAST_FAILS=0
run_engine() {  # $1 brief, $2 log
  local began=$SECONDS rc out wait
  engine_once "$1" "$2"; rc=$?
  if [ "$rc" -eq 75 ]; then
    # An advisory pick lost its atomic run claim or became stale before launch.
    # No worker ran, so quota/network backoff would punish an ordinary race.
    FAST_FAILS=0
  elif [ "$rc" -ne 0 ] && [ $((SECONDS - began)) -lt "${FLEET_ABORT_SECONDS:-300}" ]; then
    FAST_FAILS=$((FAST_FAILS + 1))
    wait=$((60 << (FAST_FAILS > 5 ? 5 : FAST_FAILS - 1))); [ "$wait" -gt 1800 ] && wait=1800
    out=$(sed -n 2p "$2" 2>/dev/null | tr -d '\r')   # fleet_run leaves a pointer to the transcript
    grep -q -i -E 'usage limit|rate limit|quota' "$out" "$2" 2>/dev/null && wait=1800
    echo "$(date '+%H:%M') seat $ENGINE$SEAT fast failure $FAST_FAILS (exit $rc); backing off ${wait}s" >> build/fleet_logs/seats.log
    sleep "${FLEET_BACKOFF_OVERRIDE:-$wait}"
  else
    FAST_FAILS=0
  fi
  return "$rc"
}

while true; do
  if [ "${ENGINE%big}" != "$ENGINE" ]; then
    RVA=$(python tools/fleet/pick_big.py 1 | tr -d '\r' | head -1)
    [ -z "$RVA" ] && { echo "seat $SEAT: no big body picked; retry in 60s"; sleep 60; continue; }
    for PASS in 1 2 3; do
      BEFORE=$(python tools/fleet_run.py --fingerprint "$RVA" | tr -d '\r')
      BRIEF="build/brief_seat_${ENGINE}${SEAT}_${RVA}_p${PASS}.txt"
      python tools/brief.py --rvas "$RVA" --model "$CMODEL" --limit 1 --note "$BIGNOTE (session $PASS of 3)" > "$BRIEF" 2>/dev/null || break
      LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${RVA}_p${PASS}.log"
      echo "$(date '+%H:%M') seat $ENGINE$SEAT assigned $RVA p$PASS" >> build/fleet_logs/seats.log
      run_engine "$BRIEF" "$LOG"
      echo "$(date '+%H:%M') seat $ENGINE$SEAT finished $RVA p$PASS" >> build/fleet_logs/seats.log
      # Repeating a score/date is not progress; require a changed preferred body.
      python tools/fleet_run.py --can-retry "$RVA" --before "$BEFORE" || break
      sleep 5
    done
  elif [ "${ENGINE%class}" != "$ENGINE" ]; then
    # class lane: the dump slots of one warm vtable (most slots already landed C++)
    python tools/fleet/pick_class.py > build/.pick_class_$SEAT.txt 2>/dev/null
    RVAS=$(head -1 build/.pick_class_$SEAT.txt | sed 's/^RVAS: //' | tr -d '\r')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: no warm class picked; retry in 120s"; sleep 120; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 8 --note-file "build/.pick_class_$SEAT.txt" --note "Work the class as a unit: reuse landed slot sources and align the proposed ZH order against proven slots. Verify each name against the body's own bytes before pinning it (tools/pin_consistency.py --symbol NAME first, --check after). Probe EXACT is masked shape only; add_match.py must verify relocations before landing. Bank close bodies with re_log.py partial --stash --score." > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT assigned $RVAS" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT finished $RVAS" >> build/fleet_logs/seats.log
  elif [ "${ENGINE%block}" != "$ENGINE" ]; then
    # blocker lane: the largest cluster of open bodies whose latest verdict names the same
    # blocker family (tools/blockers.py). One session looks for the shared lever, then
    # lists the bodies it reopens in reverse/unlocked.txt for the ordinary lanes.
    python tools/fleet/pick_blocker.py 12 > build/.pick_blocker_$SEAT.txt 2>/dev/null
    RVAS=$(head -1 build/.pick_blocker_$SEAT.txt | sed 's/^RVAS: //' | tr -d '\r')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: no shared blocker of 5+ bodies; retry in 600s"; sleep 600; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 12 --note-file "build/.pick_blocker_$SEAT.txt" > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT assigned $RVAS" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT finished $RVAS" >> build/fleet_logs/seats.log
  elif [ "${ENGINE%mid}" != "$ENGINE" ]; then
    # mid lane: 3 bodies of 300..1000 B from one dump file whose neighbours are already C++
    case "$ENGINE" in *big*) MIDARGS="2 1000 2500";; *) MIDARGS="3 300 2500";; esac   # lunabigmid = upper window
    # shellcheck disable=SC2086
    RVAS=$(python tools/fleet/pick_mid.py $MIDARGS | tr -d '\r' | tr '\n' ' ')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: no mid bodies picked; retry in 60s"; sleep 60; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 3 --note "MID-SIZE bodies (${MIDARGS#* } B window) from one dump file whose address neighbours are ALREADY landed as real C++. Before writing anything: rg the neighbouring landed rows in reverse/functions.csv (addresses just below and above each target), open those .cpp files and reuse their class layouts, pins, callee declarations and cl: flags -- they were proven against retail. Then identity from symbols.csv pins and the ZH twin, skeleton compiling, probe.py on the FIRST divergence only, one lever at a time (docs/shape_levers.md). Land each body with add_match.py as soon as it is EXACT; after ~35 min on one body bank it (re_log.py partial --stash --score) and move to the next. Never leave without banking your best attempt for every body you touched." > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT assigned $RVAS" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT finished $RVAS" >> build/fleet_logs/seats.log
  elif [ "${ENGINE%anon}" != "$ENGINE" ]; then
    # anonymous lane: 2 anonymous dump bodies with the warmest evidence pack
    RVAS=$(python tools/fleet/pick_anon.py 2 300 2500 | tr -d '\r' | tr '\n' ' ')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: no anonymous bodies picked; retry in 120s"; sleep 120; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 2 --note "ANONYMOUS bodies. The EVIDENCE block under each target is the lead: callers (including via ILT thunk), string literals, vtable install/slot, witnessed layout, landed neighbours. Step 1 is the boundary: confirm start, size and a contiguous end (ret/jmp then padding) from tools/dis_retail.py before anything else. Step 2 is the callee contract: python3 tools/callees.py RVA SIZE, and name ONLY what it prints. Step 3: identity you can PROVE from that evidence (a matched caller naming the symbol, a vtable slot, a unique literal in the ZH tree) gets the real name with the evidence cited. Identity you cannot prove gets an OPAQUE name that keeps the address token (RvaXXXXXXXX::method or ?dup_XXXXXXXX) -- this is permitted and expected; a plausible GUESSED class or method name is prohibited, no gate can see it. Then skeleton compiling, probe.py on the FIRST divergence, one lever at a time. Land with add_match.py when EXACT; otherwise ALWAYS bank your best body with re_log.py partial --stash --score and say in the evidence what you proved, what you assumed, and what would justify reopening." > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT assigned $RVAS" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT finished $RVAS" >> build/fleet_logs/seats.log
  elif [ "${ENGINE%review}" != "$ENGINE" ]; then
    # review lane: banked bodies 0.5..0.95; check what the byte gate cannot see
    RVAS=$(python tools/fleet/pick_review.py 2 0.5 0.95 | tr -d '\r' | tr '\n' ' ')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: nothing to review; retry in 300s"; sleep 300; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 2 --note "REVIEWER. A worker banked each body below (START FROM STASH line) and wrote its assumptions into the re_attempts.log evidence. Your job is what the byte gate cannot see: is the identity right (caller naming the symbol? vtable slot? literal?), is the class layout witnessed (tools/name_oracle.py, tools/bfme_layout.py), is the calling convention and every callee name what tools/callees.py prints, is any pin naming the WRONG function (tools/pin_consistency.py --symbol)? Correct what is wrong in the stash, run probe.py, and either land it with add_match.py or re-bank it with a corrected evidence line that states what you verified, what you changed, and the one thing still missing. Do not rewrite from scratch. Do not add a pin on the worker's say-so." > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT assigned $RVAS" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT finished $RVAS" >> build/fleet_logs/seats.log
  elif [ "${ENGINE%fin}" != "$ENGINE" ]; then
    # finish lane: 2 bodies whose banked partial scored >= 0.9, start from the stash
    # luna: fewer than 5 verdicts and not re-banked in 2 days. lunaxhigh: the
    # hard set too (no cap, no cooldown) -- a sixth max pass on the same levers
    # was the fleet's main occupation on 2026-09-16 (550 of 800 verdict rows).
    if [ "${ENGINE#lunaxhigh}" != "$ENGINE" ]; then FINARGS="4 0.9 0 0"; else FINARGS="4 0.9 5 2"; fi
    RVAS=$(python tools/fleet/pick_finish.py $FINARGS | tr -d '\r' | tr '\n' ' ')
    [ -z "${RVAS// /}" ] && { echo "seat $SEAT: no finish bodies picked; retry in 60s"; sleep 60; continue; }
    STEM=$(echo "$RVAS" | awk '{print $1}')
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    # shellcheck disable=SC2086
    python tools/brief.py --rvas $RVAS --model "$CMODEL" --limit 4 --note "NEAR-LANDED bodies: each has a banked stash scoring 0.9+ (START FROM STASH line). Do not rewrite from scratch. Compile the stash, run probe.py, and work ONLY the first divergence with one lever at a time from docs/shape_levers.md (register mirror = local definition order / loads above guard / IAT CSE; sib-order; eh-transposition; fall-through flag tail). READ the previous evidence lines for each body in reverse/re_attempts.log first and do not repeat a lever they already report; if every lever is exhausted, bank the FIRST divergence offset and the exhausted list in one evidence line and move to the next body within 15 minutes. Land with add_match.py; if still short, re-bank with an honest score and what you tried." > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $RVAS"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT assigned $RVAS" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT finished $RVAS" >> build/fleet_logs/seats.log
  else
    FILE=$(python tools/fleet/pick_file.py 12 | tr -d '\r')
    [ -z "$FILE" ] && { echo "seat $SEAT: no file picked; retry in 60s"; sleep 60; continue; }
    STEM=$(basename "$FILE" .asm)
    BRIEF="build/brief_seat_${ENGINE}${SEAT}_${STEM}.txt"
    python tools/brief.py --dump "$FILE" --model "$CMODEL" --limit 40 --max-size 2500 > "$BRIEF" 2>/dev/null || { echo "seat $SEAT: brief failed for $FILE"; continue; }
    LOG="build/fleet_logs/seat_${ENGINE}${SEAT}_${STEM}.log"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT assigned $STEM" >> build/fleet_logs/seats.log
    run_engine "$BRIEF" "$LOG"
    echo "$(date '+%H:%M') seat $ENGINE$SEAT finished $STEM" >> build/fleet_logs/seats.log
  fi
  sleep 5
done
