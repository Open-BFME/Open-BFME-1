#!/usr/bin/env python3
"""Kill a client mid-match and verify the file distinguishes that from "never played".

The whole reason records are appended rather than written once at game end is
that a machine which dies mid-match otherwise leaves nothing behind, which
downstream is indistinguishable from a game that never happened. This asserts
the three states are actually distinguishable:
    no file          -> never loaded a game
    start only       -> died mid-match          <- what this proves
    start + end      -> finished cleanly
"""
import os
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
SHOTS = HERE.parents[1] / "build" / "gametest"
sys.path.insert(0, str(HERE))
from driver import Driver  # noqa: E402

REF = HERE / "ref"
DISP = ":79"
# A separate prefix: the single-instance mutex is per wineserver, so
# sharing ~/.wine with another running match makes this client exit at once.
PREFIX = Path.home() / "bfme-test/wine1"
EXE = "lotrbfme.mod2.exe"
WIN = "C:/bfme-crash.jsonl"
UNIX = Path.home() / "bfme-test/wine1/drive_c/bfme-crash.jsonl"

UNIX.unlink(missing_ok=True)
assert not UNIX.exists()
print(f"state 1 — before any game: file exists = {UNIX.exists()}", flush=True)

subprocess.run([HERE / "launch-mod.sh", DISP, str(PREFIX), EXE, WIN], check=True)
d = Driver(SHOTS / "crash", "c", display=DISP)
d.wait_for_screen(REF / "main-menu.png", tol=8, timeout=300)
d.focus(); d.shot("menu")
d.click(358, 944, settle=2); d.wait_for_screen(REF / "solo-play.png", tol=8, timeout=60)
d.click(656, 944, settle=2); d.wait_for_screen(REF / "skirmish-setup.png", tol=8, timeout=90)
d.shot("setup")
d.click(670, 943, settle=3); d.shot("starting")
print("game starting; waiting for the start record", flush=True)

deadline = time.time() + 300
while time.time() < deadline and not UNIX.exists():
    time.sleep(2)
if not UNIX.exists():
    sys.exit("no start record appeared")
print(f"state 2 — in game: {UNIX.read_text().strip()}", flush=True)
d.shot("in-game")

# SIGKILL: no unwinding, no atexit, no flush — the harshest realistic crash.
# Only this display's client — other matches may be running in parallel.
def on_this_display(pid):
    try:
        env = Path(f"/proc/{pid}/environ").read_bytes().split(b"\0")
    except OSError:
        return False
    return f"DISPLAY={DISP}".encode() in env

pids = [l.split()[0] for l in subprocess.run(["ps", "-eo", "pid,args"],
        capture_output=True, text=True).stdout.splitlines()
        if EXE in l and "-win" in l and on_this_display(l.split()[0])]
if not pids:
    sys.exit("no client found to kill on " + DISP)
print(f"killing {pids} with SIGKILL", flush=True)
for p in pids:
    os.kill(int(p), 9)
time.sleep(5)

txt = UNIX.read_text()
lines = [l for l in txt.splitlines() if l.strip()]
print("\n=== after the kill ===", flush=True)
print(txt, flush=True)
print(f"records      : {len(lines)}", flush=True)
print(f"has start    : {'\"ev\":\"start\"' in txt}", flush=True)
print(f"has end      : {'\"ev\":\"end\"' in txt}", flush=True)
ok = len(lines) == 1 and '"ev":"start"' in txt and '"ev":"end"' not in txt
print(f"\nCRASH STATE DISTINGUISHABLE: {ok}", flush=True)
