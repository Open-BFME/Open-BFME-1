#!/usr/bin/env python3
"""Get into a skirmish with the PROBE build and dump one record immediately.

The probe drops the end-of-game gate, so it writes on the first update after a
local slot exists. That turns a layout question into a three-minute experiment
instead of a full match.
"""
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
SHOTS = HERE.parents[1] / "build" / "gametest"
sys.path.insert(0, str(HERE))
from driver import Driver  # noqa: E402

REF = HERE / "ref"
DISP, PREFIX = ":79", Path.home() / "bfme-test/wine1"
EXE, WIN = "lotrbfme.probe.exe", "C:/bfme-probe.jsonl"
UNIX = PREFIX / "drive_c/bfme-probe.jsonl"

UNIX.unlink(missing_ok=True)
subprocess.run([HERE / "launch-mod.sh", DISP, str(PREFIX), EXE, WIN], check=True)
d = Driver(SHOTS / "probe", "p", display=DISP)
d.wait_for_screen(REF / "main-menu.png", tol=8, timeout=300)
d.focus(); d.shot("menu")
d.click(358, 944, settle=2); d.wait_for_screen(REF / "solo-play.png", tol=8, timeout=60)
d.click(656, 944, settle=3)
d.dismiss_profile_prompt(REF / "skirmish-setup.png")
d.shot("setup")
d.click(670, 943, settle=3); d.shot("starting")
print("waiting for a record with a live slot table", flush=True)

deadline = time.time() + 420
while time.time() < deadline:
    if UNIX.exists():
        txt = UNIX.read_text()
        if '"slots"' in txt:
            print(txt.splitlines()[-1], flush=True)
            break
    time.sleep(3)
else:
    print("TIMEOUT", flush=True)
d.shot("final")
