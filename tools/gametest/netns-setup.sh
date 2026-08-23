#!/usr/bin/env bash
# netns-setup.sh [N] — give N game clients one network stack each (default 4).
#
# Why this exists: separate WINEPREFIXes are enough to run two clients and play
# a full LAN match, but a THIRD client is always refused with "Game has already
# started". Ports are not the cause (each client takes its own from 8086-8089),
# and every other suspect has been eliminated — see docs/overlay.md. What is
# left is that every client binds the same interface, because wine takes the
# first one it finds. This gives each its own stack and its own address.
#
# Generalised from ~/bfme-test/netns-setup.sh, which hardcoded two namespaces.
# Idempotent, and entirely gone on reboot — it touches nothing persistent.
#
#   sudo tools/gametest/netns-setup.sh 4
#   ip netns exec game1 sudo -u "$SUDO_USER" env DISPLAY=:79 ... wine ...
set -euo pipefail

N="${1:-4}"
BRIDGE=br-lan
SUBNET=10.99.0

if [ "$(id -u)" -ne 0 ]; then
    echo "must run as root: sudo $0 ${N}" >&2
    exit 1
fi

if ! ip link show "$BRIDGE" >/dev/null 2>&1; then
    ip link add "$BRIDGE" type bridge
    ip link set "$BRIDGE" up
    ip addr add "$SUBNET.254/24" dev "$BRIDGE"
    echo "created bridge $BRIDGE at $SUBNET.254"
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

# Prove it before claiming success: every namespace must reach every other, or
# a LAN broadcast between them will not work either.
fail=0
for a in $(seq 1 "$N"); do
    for b in $(seq 1 "$N"); do
        [ "$a" = "$b" ] && continue
        if ! ip netns exec "game$a" ping -c1 -W2 "$SUBNET.$b" >/dev/null 2>&1; then
            echo "UNREACHABLE: game$a -> $SUBNET.$b" >&2
            fail=1
        fi
    done
done
[ "$fail" -eq 0 ] || { echo "NETNS FAILED" >&2; exit 1; }
echo "NETNS_READY: game1..game$N all mutually reachable on $SUBNET.0/24"
