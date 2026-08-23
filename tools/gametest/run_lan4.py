#!/usr/bin/env python3
"""Seat four human clients in one LAN game, retrying joins that are refused.

The refusal that blocked this for a long time is LAN:ErrorGameGone -- "Game has
already started" -- which is NOT LAN:ErrorGameStarted ("Sorry, this game has
already started."). Game *gone* means the browser row the client clicked no
longer describes a live game: the host's entry changed when an earlier player
took a slot, and the row went stale. So the row must be re-selected from a fresh
broadcast on every attempt, not selected once and clicked repeatedly.

Success is verified by looking at the joiner's screen, never assumed: still on
the LAN lobby means the join failed, whatever the click sequence returned.
"""
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
from driver import Driver  # noqa: E402

REF = HERE / "ref640"
TOL = 8.0
ATTEMPTS = 5


def to_lobby(d, name):
    d.wait_for_screen(REF / "main-menu.png", tol=TOL, timeout=500)
    d.focus()
    d.tap("MULTIPLAYER", settle=4); time.sleep(3)
    d.tap("FIREWALL_OK", settle=4); time.sleep(3)
    d.tap("NETWORK", settle=5)
    d.wait_for_screen(REF / "lan-lobby.png", tol=TOL, timeout=250)
    x, y = d.at("NICKNAME")
    d.click(x, y, settle=1)
    d._run("xdotool", "key", "End")
    for _ in range(24):
        d._run("xdotool", "key", "BackSpace")
    time.sleep(0.4)
    d.type(name)
    d._run("xdotool", "key", "Return")
    time.sleep(1.5)
    d.park()


def in_lobby(d):
    return d.screen_score(REF / "lan-lobby.png") <= TOL


def join(d, name, shots):
    """Return the attempt number that seated this client, or None."""
    for attempt in range(1, ATTEMPTS + 1):
        time.sleep(10)                  # let a fresh game broadcast land
        d.park()
        d.tap("GAME_ROW1", settle=3)    # re-select every attempt: the row goes stale
        d.tap("JOIN_GAME", settle=8)
        time.sleep(10)
        d.shot(f"{name}-try{attempt}")
        if not in_lobby(d):
            print(f"  {name}: seated on attempt {attempt}", flush=True)
            return attempt
        print(f"  {name}: attempt {attempt} refused, dismissing", flush=True)
        d.tap("DIALOG_OK", settle=3)
        time.sleep(2)
        d.park()
    return None


def main(displays, shotdir):
    names = ["P1_T1", "P2_T1", "P3_T2", "P4_T2"]
    shotdir = Path(shotdir)
    h = Driver(shotdir / names[0], "H", display=displays[0])
    to_lobby(h, names[0])
    h.tap("CREATE_GAME", settle=6)
    time.sleep(10)
    h.shot("hosting")
    print(f"  {names[0]}: hosting", flush=True)

    seated = {names[0]: 0}
    for disp, name in zip(displays[1:], names[1:]):
        d = Driver(shotdir / name, name[:2], display=disp)
        to_lobby(d, name)
        seated[name] = join(d, name, shotdir)
        h.shot(f"roster-after-{name}")

    h.shot("final-roster")
    ok = [n for n, a in seated.items() if a is not None]
    print(f"SEATED {len(ok)}/4: {seated}", flush=True)
    return 0 if len(ok) == 4 else 1


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:5], sys.argv[5]))
