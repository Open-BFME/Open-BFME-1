#!/usr/bin/env bash
# Inner half of lan4-netns.sh: runs as root inside a fresh user+net+mount
# namespace. Builds a bridge with one veth per client, then drives the test.
set -euo pipefail
cd "$REPO"

mount -t tmpfs tmpfs /run            # so `ip netns` has somewhere to put handles
mkdir -p /run/netns /run/xdg
export XDG_RUNTIME_DIR=/run/xdg      # the real one is under the tmpfs now

# The game picks the address it binds its game transport to by calling
# gethostname() and then gethostbyname() on the result (IPEnumeration.cpp). In a
# namespace that resolves to ::1, which is not an address the namespace has, so
# the bind fails and the match never forms -- while the lobby, which broadcasts,
# carries on working and hides it. Give each namespace a hostname that resolves
# to its own address. nsswitch has to be overridden too: the stock order puts
# `resolve [!UNAVAIL=return]` ahead of `files`, so systemd-resolved answers first
# and /etc/hosts is never consulted.
{ echo "127.0.0.1 localhost"
  for i in $(seq 1 $N); do echo "10.99.0.$i bfme$i"; done
} > /run/hosts
echo "hosts: files" > /run/nsswitch.conf
mount --bind /run/hosts /etc/hosts
mount --bind /run/nsswitch.conf /etc/nsswitch.conf

ip link add br0 type bridge
ip link set br0 up
ip addr add 10.99.0.254/24 dev br0

for i in $(seq 1 $N); do
    ip netns add "g$i"
    ip link add "v${i}a" type veth peer name "v${i}b"
    ip link set "v${i}a" master br0
    ip link set "v${i}a" up
    ip link set "v${i}b" netns "g$i"
    ip -n "g$i" addr add "10.99.0.$i/24" dev "v${i}b"
    ip -n "g$i" link set "v${i}b" up
    ip -n "g$i" link set lo up
    # A default route is not for reaching anything outside -- there is nothing
    # outside. The game works out which address to advertise to its peers with a
    # route lookup, and with no default route that lookup fails: the lobby still
    # works, because discovery is broadcast and replies go back to the sender,
    # but the in-game mesh never forms and every joiner falls back to the lobby
    # saying the host left.
    ip -n "g$i" route add default via 10.99.0.254
done
echo "  $N stacks up: 10.99.0.1-$N"

R='C:\users\wacket\AppData\Roaming\My Battle for Middle-earth Files\GameResult.jsonl'
GAMEDIR="$HOME/.wine/drive_c/BFME1"
CPUS=(0-3 4-7 8-11 12-15)
DISPS=($DISPLAYS)
for i in $(seq 1 $N); do
    pfx="$HOME/bfme-test/wine$i"
    rm -f "$pfx/drive_c/users/wacket/AppData/Roaming/My Battle for Middle-earth Files/GameResult.jsonl"
    cat > "/run/launch$i.sh" <<LAUNCH
hostname bfme$i
exec taskset -c ${CPUS[$((i-1))]} \
    env DISPLAY=${DISPS[$((i-1))]} WINEPREFIX="$pfx" WINEDEBUG=-all \
        XDG_RUNTIME_DIR=/run/xdg BFME_RESULT_PATH="$R" \
        WINEDLLOVERRIDES="winealsa.drv=d" \
    wine explorer /desktop=bfme,640x480 \
        "$GAMEDIR/lotrbfme.t4.exe" -win -noshellmap -noaudio -xres 640 -yres 480
LAUNCH
    chmod +x "/run/launch$i.sh"
    ip netns exec "g$i" unshare -u bash "/run/launch$i.sh" \
        > "$REPO/build/gametest/logs/ns$i.log" 2>&1 &
    sleep 6
done
echo "  $N clients launched"

if [ -n "${BFME_SNIFF:-}" ]; then
    for i in $(seq 1 $N); do
        ip netns exec "g$i" python3 "$REPO/tools/gametest/sniff.py" "v${i}b" \
            "$REPO/build/gametest/logs/sniff$i.log" &
    done
    echo "  sniffing"
fi
sleep 40
python3 -u tools/gametest/run_lan4.py $DISPLAYS "$SHOTDIR"
rc=$?

# Hold the namespace open. br0 lives in THIS namespace, and the clients' veth
# peers are plugged into it -- so when this script exits the bridge is destroyed
# and every client loses its network mid-match. That looked exactly like the
# game failing to form its in-game connections: the host carries on alone, each
# joiner reports that the host left, and the truth was that the test harness
# pulled the wire out eight seconds after clicking PLAY GAME.
echo "  holding the network up for ${BFME_HOLD:-900}s (rc=$rc)"
sleep "${BFME_HOLD:-900}"
exit $rc
