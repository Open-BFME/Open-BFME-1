#!/usr/bin/env bash
# launch-mod.sh <display> <prefix> <exe-name> <result-path> [args...]
# Launch a modded BFME build with BFME_RESULT_PATH set for this instance.
# result-path is a Windows path (e.g. C:\result1.json) — the CRT fopen in the
# cave payload resolves it through wine, not the Unix filesystem.
DISP="$1"; PFX="$2"; EXE="$3"; RESULT="$4"; shift 4
GAMEDIR="$HOME/.wine/drive_c/BFME1"
cd "$GAMEDIR"
setsid env DISPLAY="$DISP" WINEPREFIX="$PFX" WINEDEBUG=-all \
  BFME_RESULT_PATH="$RESULT" \
  wine explorer /desktop=bfme,1280x1024 \
  "$GAMEDIR/$EXE" -win -noshellmap -xres 1024 -yres 768 "$@" \
  > "/tmp/bfme-${EXE%.exe}-${DISP#:}.log" 2>&1 < /dev/null &
echo "launched $EXE on $DISP -> $RESULT"
