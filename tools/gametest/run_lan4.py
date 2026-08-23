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

Every client walks the menus at the same time, because a seated player that
waits is a seated player that gets dropped: "P3_T2 dropped; player was not
responding" is what a client earns for sitting in the lobby for the two minutes
it takes to click the next one through Multiplayer -> Network -> nickname. Only
the joins themselves are sequential, and they are the fast part.
"""
import sys
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
from driver import Driver  # noqa: E402

REF = HERE / "ref640"
TOL = 8.0
ATTEMPTS = 5


def to_lobby(d, name):
    d.wait_for_screen(REF / "main-menu.png", tol=TOL, timeout=500)
    d.place()
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
    """True while the client is still on the browser, seated or not.

    Matched on the "CUSTOM GAME LOBBY" sub-header rather than the button strip
    at the bottom. A JOIN FAILED dialog dims that strip, which scores as a
    changed screen -- so the obvious check reports a refused join as a seated
    one, and every 'seated on attempt 1' it printed was unverified. The
    sub-header sits above anything a modal covers."""
    x, y, w, h = d.client_rect()
    box = (int(x + 0.20 * w), int(y + 0.13 * h),
           int(x + 0.80 * w), int(y + 0.23 * h))
    return d.screen_score(REF / "lobby-subheader.png", box) <= TOL


def join(d, name, shots, stagger=0.0):
    """Return the attempt number that seated this client, or None."""
    time.sleep(stagger)
    for attempt in range(1, ATTEMPTS + 1):
        time.sleep(6)                   # let a fresh game broadcast land
        d.park()
        d.tap("GAME_ROW1", settle=3)    # re-select every attempt: the row goes stale
        d.tap("JOIN_GAME", settle=8)
        time.sleep(8)
        d.shot(f"{name}-try{attempt}")
        if not in_lobby(d):
            print(f"  {name}: seated on attempt {attempt}", flush=True)
            return attempt
        print(f"  {name}: attempt {attempt} refused, dismissing", flush=True)
        d.tap("DIALOG_OK", settle=3)
        time.sleep(2)
        d.park()
    return None


# Host roster geometry, absolute screen pixels at a 640x480 client placed at the
# desktop origin. The team dropdown opens *below* the row it belongs to, so an
# item's y is derived from its own row rather than from a fixed list position.
ROW_Y = {1: 168, 2: 184, 3: 199, 4: 214}
TEAM_ARROW_X = 270
TEAM_ITEM_X = 240
TEAM_ITEM_DY = 15      # first item ("None") below the row
TEAM_ITEM_STEP = 13


def set_team(d, row, team):
    """Set the team on row `row` from the client that owns that row.

    Each player owns exactly one row. The host's dropdowns for everyone else are
    inert -- clicking them from the host silently does nothing, which reads as a
    working script producing a free-for-all."""
    d.click(TEAM_ARROW_X, ROW_Y[row], settle=1.2)
    d.click(TEAM_ITEM_X, ROW_Y[row] + TEAM_ITEM_DY + TEAM_ITEM_STEP * team, settle=1.2)


def main(displays, shotdir):
    displays = [d for d in displays if d]
    names = ["P1_T1", "P2_T1", "P3_T2", "P4_T2"][:len(displays)]
    teams = {2: (1, 2), 3: (1, 2, 2), 4: (1, 1, 2, 2)}[len(displays)]
    shotdir = Path(shotdir)
    drivers = {n: Driver(shotdir / n, n[:2], display=p)
               for n, p in zip(names, displays)}

    with ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(lambda n: to_lobby(drivers[n], n), names))
    print("  all four at the lobby", flush=True)

    h = drivers[names[0]]
    h.tap("CREATE_GAME", settle=6)
    time.sleep(10)
    h.shot("hosting")
    print(f"  {names[0]}: hosting", flush=True)

    # All three join at once. Seating them one at a time leaves the earliest
    # joiner sitting in the lobby for the length of the other two joins, and on
    # a machine this busy that is long enough to be dropped for not responding.
    # Real players click at the same time too.
    seated = {names[0]: 0}
    with ThreadPoolExecutor(max_workers=3) as pool:
        futs = {n: pool.submit(join, drivers[n], n, shotdir, 2.0 * i)
                for i, n in enumerate(names[1:])}
        for n, f in futs.items():
            seated[n] = f.result()

    h.shot("final-roster")
    ok = [n for n, a in seated.items() if a is not None]
    print(f"SEATED {len(ok)}/{len(names)}: {seated}", flush=True)
    if len(ok) != len(names):
        return 1

    for i, n in enumerate(names, start=1):
        drivers[n].shot("seated")

    # 2v2: rows 1+2 on team 1, rows 3+4 on team 2, each set by its own owner.
    for i, (n, team) in enumerate(zip(names, teams), start=1):
        set_team(drivers[n], i, team)
    for n in names:
        drivers[n].shot("team-set")

    # Let the team changes propagate before starting. Starting on top of them
    # leaves the host in the match and every joiner in the lobby reporting
    # "host has left" -- the clients disagreed about the game they were joining.
    time.sleep(12)
    h.shot("teams-set")
    h.tap("PLAY_GAME", settle=8)
    h.shot("play-clicked")
    print("PLAY GAME clicked", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:-1], sys.argv[-1]))
