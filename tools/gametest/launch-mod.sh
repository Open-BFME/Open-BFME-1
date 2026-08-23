#!/usr/bin/env bash
# launch-mod.sh <display> <prefix> <exe-name> <result-path> [args...]
# Launch a modded BFME build with BFME_RESULT_PATH set for this instance.
# result-path is a Windows path (e.g. C:\result1.json) — the CRT fopen in the
# cave payload resolves it through wine, not the Unix filesystem.
DISP="$1"; PFX="$2"; EXE="$3"; RESULT="$4"; shift 4
# Four clients at 1024x768 cost roughly four times the fill rate of 640x480,
# which is what pushed earlier runs into dropped lobby heartbeats.
XRES="${BFME_XRES:-1024}"; YRES="${BFME_YRES:-768}"
# BFME_CPUS pins this client to its own cores. Four clients left to float across
# a machine that is also running a VM, a browser and a compiler get migrated
# constantly, and a joiner that misses the host's lobby pings is dropped as "not
# responding" -- the game is fine, the scheduler is not.
PIN=""; [ -n "${BFME_CPUS:-}" ] && PIN="taskset -c ${BFME_CPUS}"
GAMEDIR="$HOME/.wine/drive_c/BFME1"
cd "$GAMEDIR"
setsid $PIN env DISPLAY="$DISP" WINEPREFIX="$PFX" WINEDEBUG=-all \
  BFME_RESULT_PATH="$RESULT" \
  wine explorer /desktop=bfme,${XRES}x${YRES} \
  "$GAMEDIR/$EXE" -win -noshellmap -xres "$XRES" -yres "$YRES" "$@" \
  > "/tmp/bfme-${EXE%.exe}-${DISP#:}.log" 2>&1 < /dev/null &
echo "launched $EXE on $DISP -> $RESULT"
