#!/usr/bin/env python3
"""Screenshot-and-click driver for BFME running under Xvfb + wine virtual desktop.

Two things here are load-bearing and were each learned the hard way:

1. The wine virtual desktop. With no window manager on the display, DirectInput
   never acquires the mouse and every synthetic click is silently dropped —
   the pointer moves, the window reports focus, and nothing happens.

2. Positive screen identification. Pixel stability is NOT a readiness signal:
   the loading splash is a static image, so "nothing is moving" is true long
   before the menu exists. Assert which screen you are on before clicking.

The display is per-instance, never module-global — two clients on two displays
are the normal case, and a shared global silently sends one client's clicks to
the other's screen.
"""
import os
import subprocess
import time
from pathlib import Path

from PIL import Image, ImageChops

BUTTON_STRIP = (243, 915, 1270, 975)


class Driver:
    def __init__(self, outdir, prefix="s", display=None):
        self.display = display or os.environ.get("BFME_DISPLAY", ":77")
        self.out = Path(outdir)
        self.out.mkdir(parents=True, exist_ok=True)
        self.prefix = prefix
        self.n = 0

    def _run(self, *args):
        return subprocess.run(args, env=dict(os.environ, DISPLAY=self.display),
                              capture_output=True, text=True)

    # --- capture -------------------------------------------------------
    def shot(self, label=""):
        self.n += 1
        p = self.out / f"{self.n:02d}-{label or 'shot'}.png"
        r = self._run("import", "-window", "root", str(p))
        if r.returncode != 0:
            raise RuntimeError(f"import failed on {self.display}: {r.stderr}")
        return p

    def _grab(self):
        p = self.out / ".tmp.png"
        self._run("import", "-window", "root", str(p))
        return Image.open(p).convert("RGB")

    # --- waiting -------------------------------------------------------
    def wait_stable(self, quiet=1.5, timeout=60, poll=0.5):
        """Block until the screen stops changing for `quiet` seconds.
        Useful only for settling an already-identified screen — never as proof
        that a screen has finished loading."""
        deadline = time.time() + timeout
        last = self._grab()
        calm_since = time.time()
        while time.time() < deadline:
            time.sleep(poll)
            cur = self._grab()
            if ImageChops.difference(last, cur).getbbox() is None:
                if time.time() - calm_since >= quiet:
                    return True
            else:
                calm_since = time.time()
            last = cur
        return False

    def wait_change(self, baseline, timeout=60, poll=1.0, min_pixels=500, box=None):
        """Block until the screen (optionally just `box`) differs from `baseline`."""
        base = baseline if isinstance(baseline, Image.Image) else Image.open(baseline).convert("RGB")
        if box:
            base = base.crop(box)
        deadline = time.time() + timeout
        while time.time() < deadline:
            cur = self._grab()
            if box:
                cur = cur.crop(box)
            bb = ImageChops.difference(base, cur).getbbox()
            if bb and (bb[2] - bb[0]) * (bb[3] - bb[1]) > min_pixels:
                return bb
            time.sleep(poll)
        return None

    def screen_score(self, ref_path, box=None):
        """Mean absolute pixel difference against a reference. 0 == identical.

        References in ref/ are stored pre-cropped to BUTTON_STRIP — that strip
        is the only region the match uses, and storing whole 1280x1024 frames
        cost 2.8 MB to compare 60 pixel rows."""
        box = box or BUTTON_STRIP
        ref = Image.open(ref_path).convert("RGB")
        if ref.size != (box[2] - box[0], box[3] - box[1]):
            ref = ref.crop(box)
        cur = self._grab().crop(box)
        diff = ImageChops.difference(ref, cur)
        px = list(diff.getdata())
        return sum(sum(p) for p in px) / (len(px) * 3)

    def wait_for_screen(self, ref_path, tol=8.0, timeout=180, poll=2.0, box=None):
        """Block until the screen matches `ref_path`. Raises with the best score
        seen, so a failure says how close it got rather than just timing out."""
        deadline = time.time() + timeout
        best = 1e9
        while time.time() < deadline:
            s = self.screen_score(ref_path, box)
            best = min(best, s)
            if s <= tol:
                return s
            time.sleep(poll)
        raise RuntimeError(
            f"{self.display}: screen never matched {Path(ref_path).name} within "
            f"{timeout}s (best score {best:.1f}, tolerance {tol})")

    # --- input ---------------------------------------------------------
    def focus(self, name="Lord of the Rings"):
        r = self._run("xdotool", "search", "--name", name)
        if not r.stdout.strip():
            raise RuntimeError(f"no window matching {name!r} on {self.display}")
        wid = r.stdout.split()[0]
        self._run("xdotool", "windowfocus", wid)
        time.sleep(0.4)
        return wid

    def move(self, x, y):
        self._run("xdotool", "mousemove", str(x), str(y))
        time.sleep(0.3)

    def click(self, x, y, settle=1.0):
        self.move(x, y)
        self._run("xdotool", "click", "1")
        time.sleep(settle)

    def key(self, k, settle=0.6):
        self._run("xdotool", "key", k)
        time.sleep(settle)

    def type(self, text, settle=0.5):
        self._run("xdotool", "type", "--delay", "40", text)
        time.sleep(settle)
