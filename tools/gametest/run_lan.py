#!/usr/bin/env python3
"""Two-client LAN match: host, join, play, one player quits, dump both files.

The quitter case is the interesting one. FINDINGS: nothing in the network layer
defeats a leaver — DESTROYPLAYER's MSG_SELF_DESTRUCT kills their objects and the
survivor's VictoryConditions::update notices the defeat some frames later. So
the survivor should reach m_endFrame and write an "end" record naming the
leaver's fate, while the leaver itself only ever wrote "start".
"""
import os
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
SHOTS = HERE.parents[1] / "build" / "gametest"
sys.path.insert(0, str(HERE))
REF = HERE / "ref"
TOL = 8.0
GAMEDIR = Path.home() / ".wine/drive_c/BFME1"
EXE = "lotrbfme.mod2.exe"

CLIENTS = [
    dict(disp=":79", prefix=Path.home() / "bfme-test/wine1",
         win="C:/bfme-A.jsonl", unix=Path.home() / "bfme-test/wine1/drive_c/bfme-A.jsonl",
         role="host"),
    dict(disp=":80", prefix=Path.home() / "bfme-test/wine2",
         win="C:/bfme-B.jsonl", unix=Path.home() / "bfme-test/wine2/drive_c/bfme-B.jsonl",
         role="join"),
]


def kill_all():
    """Kill only this run's own clients. Matching on the exe name alone also
    kills unrelated matches running on other displays — which is how a parallel
    skirmish got taken out mid-run."""
    mine = {c["disp"] for c in CLIENTS}
    out = subprocess.run(["ps", "-eo", "pid,args"], capture_output=True, text=True).stdout
    for line in out.splitlines():
        if EXE not in line and "/desktop=bfme" not in line:
            continue
        pid = line.split()[0]
        try:
            env = Path(f"/proc/{pid}/environ").read_bytes().split(b"\0")
        except OSError:
            continue
        if any(f"DISPLAY={d}".encode() in env for d in mine):
            try:
                os.kill(int(pid), 9)
            except Exception:
                pass
    time.sleep(3)


def launch(c):
    env = dict(os.environ, DISPLAY=c["disp"], WINEPREFIX=str(c["prefix"]),
               WINEDEBUG="-all", BFME_RESULT_PATH=c["win"])
    subprocess.Popen(
        ["setsid", "wine", "explorer", "/desktop=bfme,1280x1024",
         str(GAMEDIR / EXE), "-win", "-noshellmap", "-xres", "1024", "-yres", "768"],
        cwd=GAMEDIR, env=env,
        stdout=open(f"/tmp/bfme-lan{c['disp'][1:]}.log", "w"),
        stderr=subprocess.STDOUT, stdin=subprocess.DEVNULL, start_new_session=True)


kill_all()
for c in CLIENTS:
    c["unix"].unlink(missing_ok=True)
    launch(c)
    print(f"launched {c['role']} on {c['disp']}", flush=True)

from driver import Driver  # noqa: E402

drivers = {}
for c in CLIENTS:
    d = Driver(SHOTS / "lan" / c["role"], c["role"], display=c["disp"])
    d.wait_for_screen(REF / "main-menu.png", tol=TOL, timeout=300)
    d.focus()
    d.shot("menu")
    d.click(517, 944, settle=3); d.wait_stable(timeout=30)   # MULTIPLAYER
    d.click(667, 693, settle=3); d.wait_stable(timeout=30)   # firewall ACCEPT
    d.click(673, 944, settle=4)                              # NETWORK
    d.wait_for_screen(REF / "lan-lobby.png", tol=TOL, timeout=120)
    d.shot("lan-lobby")
    print(f"{c['role']}: LAN lobby", flush=True)
    drivers[c["role"]] = d

h, j = drivers["host"], drivers["join"]
h.click(668, 943, settle=5); h.wait_stable(timeout=60); h.shot("hosting")
print("host: game created", flush=True)

# The LAN game list polls; clicking a row that has not appeared yet selects
# nothing and leaves JOIN GAME disabled. Wait for the list to populate.
GAMES_LIST = (542, 444, 842, 580)
baseline = j._grab()
if j.wait_change(baseline, timeout=120, min_pixels=200) is None:
    raise SystemExit("join: hosted game never appeared in the lobby list")
j.shot("game-listed")
j.click(628, 454, settle=2); j.shot("game-selected")
j.click(839, 943, settle=5); j.wait_stable(timeout=60); j.shot("joined")
print("join: joined", flush=True)

# and confirm the host actually sees a second player before starting
h.shot("lobby-before-play")

h.click(668, 943, settle=5); h.shot("play-clicked")
print("host: PLAY GAME; waiting for both start records", flush=True)

deadline = time.time() + 300
while time.time() < deadline:
    if all(c["unix"].exists() for c in CLIENTS):
        break
    time.sleep(3)
for c in CLIENTS:
    print(f"  {c['role']} start: {c['unix'].read_text().strip() if c['unix'].exists() else '(no file)'}", flush=True)

time.sleep(45)
for d in (h, j):
    d.shot("in-game")

print("join: quitting", flush=True)
j.focus(); j.key("Escape"); time.sleep(2); j.shot("esc")
j.click(757, 652, settle=3); j.shot("exit-dialog")
j.click(665, 641, settle=3); j.shot("quit-confirmed")

print("waiting for the survivor's end record", flush=True)
deadline = time.time() + 420
host_file = CLIENTS[0]["unix"]
while time.time() < deadline:
    if host_file.exists() and '"ev":"end"' in host_file.read_text():
        break
    time.sleep(5)

time.sleep(5)
for d in (h, j):
    d.shot("final")
print("\n=== RESULTS ===", flush=True)
for c in CLIENTS:
    print(f"--- {c['role']} ({c['win']}) ---", flush=True)
    print(c["unix"].read_text() if c["unix"].exists() else "(missing)", flush=True)
