#!/usr/bin/env bash
# gpu-displays.sh <count> [WxH] — start N headless GPU-backed X displays, print them.
#
# Four BFME clients on llvmpipe burn ~640% CPU and drop each other from the
# lobby for missing heartbeats. Headless sway renders on the real card instead,
# which costs about half that and stays invisible to the user's session.
#
# The display number is DETECTED by diffing the set of X servers that actually
# ANSWER before and after each compositor starts, never assumed and never taken
# from the socket files. X display numbers are global and this machine is shared,
# so assuming one would either collide with another session or silently drive
# someone else's screen -- and a dead server leaves its socket file behind, so a
# file-level diff misses a compositor that reclaims a stale number.
set -uo pipefail

N="${1:?usage: gpu-displays.sh <count> [WxH]}"
MODE="${2:-640x480}"
RUN="${XDG_RUNTIME_DIR:-/run/user/$(id -u)}"
CFGDIR="$(mktemp -d /tmp/bfme-gpu.XXXXXX)"
echo "logs: $CFGDIR" >&2

live() {
    for s in /tmp/.X11-unix/X*; do
        n=":${s##*/X}"
        DISPLAY="$n" timeout 2 xdpyinfo >/dev/null 2>&1 && echo "$n"
    done | sort
}

for i in $(seq 1 "$N"); do
    before=$(live)
    cfg="$CFGDIR/sway-$i.conf"
    cat > "$cfg" <<CONF
output HEADLESS-1 mode $MODE
default_border none
focus_follows_mouse no
CONF
    WAYLAND_DISPLAY="bfme-wl-$i" \
    WLR_BACKENDS=headless WLR_LIBINPUT_NO_DEVICES=1 \
    XDG_RUNTIME_DIR="$RUN" \
        setsid sway -c "$cfg" >"$CFGDIR/sway-$i.log" 2>&1 &

    disp=""
    for _ in $(seq 1 80); do
        sleep 0.5
        new=$(comm -13 <(echo "$before") <(live) | head -1)
        [ -n "$new" ] && { disp="$new"; break; }
    done
    [ -n "$disp" ] || { echo "FAILED on compositor $i; see $CFGDIR/sway-$i.log" >&2; exit 1; }
    echo "$disp"
done
