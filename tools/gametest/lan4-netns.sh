#!/usr/bin/env bash
# lan4-netns.sh <disp1> <disp2> <disp3> <disp4> <shotdir>
# Run a four-client LAN test with one network stack per client -- no root.
#
# Clients that share an address cannot share a game. Ports are not the problem
# (each client takes its own from 8086-8089); the LAN peer table is keyed on the
# address, so the second and third joiners behind one IP are admitted to the
# roster and then dropped as "not responding" while the first keeps its seat.
#
# The older netns-setup.sh needed sudo for a host bridge. This does the same
# thing inside an unprivileged user namespace: root there is only root there, so
# it touches nothing on a shared machine and evaporates when the run ends.
# X11 is reached over /tmp/.X11-unix, which no network namespace affects.
set -euo pipefail
[ $# -ge 3 ] || { echo "usage: $0 :2 [:3 ...] <shotdir>" >&2; exit 1; }
export SHOTDIR="${@: -1}"
export DISPLAYS="${@:1:$#-1}"
export N=$(( $# - 1 ))
export REPO="$(cd "$(dirname "$0")/../.." && pwd)"
exec unshare -Urnm --propagation private "$REPO/tools/gametest/lan4-netns-inner.sh"
