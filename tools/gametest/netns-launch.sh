#!/usr/bin/env bash
# netns-launch.sh [N] — create N network namespaces and start N BFME clients,
# one per namespace, each on its own display and WINEPREFIX. Default N=4.
#
# Must run as root, because `ip netns exec` does; wine itself is dropped back to
# $SUDO_USER immediately. One sudo call sets the whole rig up, after which the
# clients can be driven over X with no further privilege.
#
# The point of the namespaces: separate WINEPREFIXes are enough for two clients
# to play a full LAN match, but a third is always refused with "Game has already
# started". Every other suspect has been eliminated (docs/overlay.md); what is
# left is that all clients bind the same interface, since wine takes the first
# one it finds. A namespace each gives them a stack and an address each.
#
#   sudo tools/gametest/netns-launch.sh 4
set -euo pipefail

N="${1:-4}"
BRIDGE=br-lan
SUBNET=10.99.0
GAMEDIR="/home/${SUDO_USER:-wacket}/.wine/drive_c/BFME1"
EXE="lotrbfme.mod2.exe"
USER_NAME="${SUDO_USER:-wacket}"
HOME_DIR="/home/$USER_NAME"

[ "$(id -u)" -eq 0 ] || { echo "must run as root: sudo $0 $N" >&2; exit 1; }
[ -x "$GAMEDIR/$EXE" ] || { echo "missing $GAMEDIR/$EXE" >&2; exit 1; }

# --- namespaces ------------------------------------------------------------
if ! ip link show "$BRIDGE" >/dev/null 2>&1; then
    ip link add "$BRIDGE" type bridge
    ip link set "$BRIDGE" up
    ip addr add "$SUBNET.254/24" dev "$BRIDGE"
    echo "created bridge $BRIDGE"
fi

for i in $(seq 1 "$N"); do
    ns="game$i"
    if ip netns list | grep -qw "$ns"; then
        echo "$ns already present"
        continue
    fi
    ip netns add "$ns"
    ip link add "veth$i" type veth peer name "veth${i}b"
    ip link set "veth$i" netns "$ns"
    ip link set "veth${i}b" master "$BRIDGE" up
    ip netns exec "$ns" ip addr add "$SUBNET.$i/24" dev "veth$i"
    ip netns exec "$ns" ip link set "veth$i" up
    ip netns exec "$ns" ip link set lo up
    echo "created $ns at $SUBNET.$i"
done

# Prove the mesh before launching anything: LAN discovery is broadcast, so a
# partially connected bridge would look like the very bug being investigated.
for a in $(seq 1 "$N"); do
    for b in $(seq 1 "$N"); do
        [ "$a" = "$b" ] && continue
        ip netns exec "game$a" ping -c1 -W2 "$SUBNET.$b" >/dev/null 2>&1 \
            || { echo "UNREACHABLE game$a -> $SUBNET.$b" >&2; exit 1; }
    done
done
echo "NETNS_READY: game1..game$N mutually reachable"

# --- clients ---------------------------------------------------------------
for i in $(seq 1 "$N"); do
    disp=":$((78 + i))"                 # game1 -> :79 ... game4 -> :82
    prefix="$HOME_DIR/bfme-test/wine$i"
    cpus="$(( (i-1)*4 ))-$(( (i-1)*4 + 3 ))"
    [ -d "$prefix" ] || { echo "missing WINEPREFIX $prefix" >&2; exit 1; }

    setsid ip netns exec "game$i" \
        sudo -u "$USER_NAME" taskset -c "$cpus" \
        env DISPLAY="$disp" WINEPREFIX="$prefix" WINEDEBUG=-all HOME="$HOME_DIR" \
        wine explorer /desktop=bfme,1280x1024 \
        "$GAMEDIR/$EXE" -win -noshellmap -xres 1024 -yres 768 \
        > "/tmp/bfme-ns$i.log" 2>&1 < /dev/null &
    echo "launched game$i on $disp (prefix wine$i, cores $cpus, $SUBNET.$i)"
done

echo
echo "all $N clients launching; give them ~90s, then drive them over X"
