#!/usr/bin/env bash
# kill-mine.sh <display> [<display>...] — stop ONLY the clients on these displays.
#
# Never match on the exe name alone. This machine can be shared, and a pattern
# like "lotrbfme" or "desktop=bfme" will happily kill someone else's session
# running the same game. Every process is checked against its own DISPLAY in
# /proc/<pid>/environ before it is signalled, and anything unreadable is left
# alone rather than guessed at.
set -uo pipefail

# An argument starting with / is a WINEPREFIX rather than a display. Matching on
# display alone is not enough: wineserver is per-prefix and outlives the client,
# so a run whose display is already gone leaves a server behind, and the next
# launch attaches to THAT server -- in the old, dead network namespace -- and
# dies with BadWindow on X_CreateWindow.
[ $# -ge 1 ] || { echo "usage: $0 :79 [:80 ...] [/path/to/wineprefix ...]" >&2; exit 1; }

killed=0
for pid in $(ps -eo pid,args | awk '/lotrbfme|desktop=bfme|wineserver/ && !/awk/ {print $1}'); do
    env_file="/proc/$pid/environ"
    [ -r "$env_file" ] || continue          # not ours to touch
    disp=$(tr '\0' '\n' < "$env_file" 2>/dev/null | sed -n 's/^DISPLAY=//p' | head -1)
    pfx=$(tr '\0' '\n' < "$env_file" 2>/dev/null | sed -n 's/^WINEPREFIX=//p' | head -1)
    [ -n "$disp" ] || [ -n "$pfx" ] || continue
    for want in "$@"; do
        if [ "$disp" = "$want" ] || { [ -n "$pfx" ] && [ "$pfx" = "$want" ]; }; then
            kill -9 "$pid" 2>/dev/null && { echo "  killed $pid on $disp"; killed=$((killed+1)); }
            break
        fi
    done
done
echo "stopped $killed process(es) on: $*"
