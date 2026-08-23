#!/usr/bin/env python3
"""Drive one skirmish from launch to game end and report the result file.

usage: run_skirmish.py <display> <prefix> <exe> <win-result-path> <unix-result-path> <outdir>

Every step asserts which screen it is on before clicking. Pixel stability is
not a usable readiness signal here — the loading splash is a static image, so
"nothing is moving" is true long before the menu exists.
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

disp, prefix, exe, winpath, unixpath, outdir = sys.argv[1:7]
os.environ["BFME_DISPLAY"] = disp
from driver import Driver  # noqa: E402

target = Path(unixpath)
if target.exists():
    target.unlink()

subprocess.run([HERE / "launch-mod.sh", disp, prefix, exe, winpath], check=True)

d = Driver(SHOTS / outdir, "run")
print("waiting for the main menu to actually be drawn...", flush=True)
score = d.wait_for_screen(REF / "main-menu.png", tol=TOL, timeout=300)
print(f"  main menu confirmed (score {score:.1f})", flush=True)
d.focus()
d.shot("menu")

d.click(358, 944, settle=2)                                    # SOLO PLAY
d.wait_for_screen(REF / "solo-play.png", tol=TOL, timeout=60)
d.shot("solo-play")

d.click(656, 944, settle=2)                                    # SKIRMISH
d.dismiss_profile_prompt(REF / "skirmish-setup.png", tol=TOL)
d.shot("skirmish-setup")

d.click(670, 943, settle=3)                                    # START GAME
d.shot("starting")
print("game starting; polling for result file", flush=True)

t0 = time.time()
last_shot = 0.0
# The file now appears at game START, so existence is not the finish signal —
# wait for the end record specifically.
while time.time() - t0 < 5400:
    if target.exists() and '"ev":"end"' in target.read_text():
        print(f"RESULT after {int(time.time()-t0)}s:\n{target.read_text()}", flush=True)
        d.shot("game-over")
        break
    if time.time() - last_shot > 600:
        d.shot(f"progress-{int(time.time()-t0)}s")
        last_shot = time.time()
    time.sleep(5)
else:
    print("TIMEOUT: no result file", flush=True)
    d.shot("timeout")
