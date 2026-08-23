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

# Everything is expressed as a FRACTION of the game's client area, never as a
# screen coordinate. Re-deriving fifteen hardcoded points every time the
# resolution changes is how a harness rots; this way -xres/-yres are free.
# Measured once against a 1024x768 client, then divided through.
UI = {
    "MULTIPLAYER":  (0.2676, 0.9570),
    "SOLO_PLAY":    (0.1123, 0.9570),
    "SKIRMISH":     (0.4033, 0.9570),
    "NETWORK":      (0.4199, 0.9570),
    "FIREWALL_OK":  (0.4141, 0.6302),
    "CREATE_GAME":  (0.4150, 0.9557),
    "PLAY_GAME":    (0.4150, 0.9557),
    "START_GAME":   (0.4170, 0.9557),
    "JOIN_GAME":    (0.5820, 0.9557),
    "CANCEL":       (0.5820, 0.9557),   # HOST GAME screen, beside PLAY GAME
    # BACK is NOT in a fixed column -- its position depends on how many buttons
    # the screen has. Assuming one position walked a run into the LOAD screen
    # and left it stuck there.
    "BACK_2BTN":    (0.5820, 0.9557),   # skirmish setup: START GAME | BACK
    "BACK_4BTN":    (0.7920, 0.9570),   # solo play: CAMPAIGN|SKIRMISH|LOAD|BACK
    "BACK_FAR":     (0.9420, 0.9460),   # load screen: BACK at the far right
    # Interior widgets do NOT scale the same way the button strip does -- the
    # game reflows them. These two were re-measured at 640x480; if the strip
    # points ever drift, suspect the same thing.
    "GAME_ROW1":    (0.4350, 0.3250),
    "NICKNAME":     (0.4280, 0.5300),
    "ESC_EXIT":     (0.5020, 0.5768),
    "CONFIRM_YES":  (0.4121, 0.5625),
    "DIALOG_OK":    (0.5010, 0.5938),
    "PROFILE_NAME": (0.4209, 0.4987),
    "PROFILE_OK":   (0.4209, 0.5990),
    # In-game. Selecting the citadel (camera starts centred on it) fills the
    # palantir ring; DEMOLISH -- "Destroys your Citadel" -- is the pale icon at
    # its lower left. This is the only way to make a player lose on demand:
    # it defeats them instantly, with leave=0, so the record is a genuine loss
    # rather than a quit. There is no confirmation prompt.
    "CITADEL":      (0.5000, 0.4250),
    "DEMOLISH":     (0.1953, 0.9544),
}

# The button strip, as a fraction of the client area rather than a pixel box.
STRIP_FRAC = (0.0, 0.9193, 1.0, 0.9974)

# wine's own decoration inside the virtual desktop
WINE_BORDER, WINE_TITLE = 3, 26


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
    def _capture(self, path):
        """Grab the whole screen.

        `import -window root` works on a real X server but returns nothing under
        Xwayland, because the X root is not what the Wayland compositor
        composites into. xwd works on both, so it is the only path used here --
        the GPU-backed headless display is Xwayland, and silently capturing a
        blank root would have made every screen match fail for no visible
        reason."""
        xwd = subprocess.run(["xwd", "-root", "-silent"],
                             env=dict(os.environ, DISPLAY=self.display),
                             capture_output=True)
        if xwd.returncode != 0 or not xwd.stdout:
            raise RuntimeError(f"xwd failed on {self.display}: {xwd.stderr[:200]}")
        conv = subprocess.run(["convert", "xwd:-", str(path)],
                              input=xwd.stdout, capture_output=True)
        if conv.returncode != 0:
            raise RuntimeError(f"convert failed: {conv.stderr[:200]}")
        return path

    def shot(self, label=""):
        self.n += 1
        p = self.out / f"{self.n:02d}-{label or 'shot'}.png"
        return self._capture(p)

    def _grab(self):
        return Image.open(self._capture(self.out / ".tmp.png")).convert("RGB")

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

    # --- geometry ------------------------------------------------------
    def client_rect(self, name="Lord of the Rings"):
        """(x, y, w, h) of the game's client area on this display, derived from
        the window rather than assumed, so any -xres/-yres works."""
        r = self._run("xdotool", "search", "--name", name)
        if not r.stdout.strip():
            raise RuntimeError(f"no window matching {name!r} on {self.display}")
        wid = r.stdout.split()[0]
        g = self._run("xdotool", "getwindowgeometry", wid).stdout
        pos = [t for t in g.split() if "," in t][0]
        size = [t for t in g.split() if "x" in t and t[0].isdigit()][0]
        px, py = (int(v) for v in pos.split(","))
        pw, ph = (int(v) for v in size.split("x"))
        return (px + WINE_BORDER, py + WINE_TITLE,
                pw - 2 * WINE_BORDER, ph - WINE_BORDER - WINE_TITLE)

    def at(self, name):
        """Screen coordinate of a named UI point at the current resolution."""
        fx, fy = UI[name]
        x, y, w, h = self.client_rect()
        return int(x + fx * w), int(y + fy * h)

    def tap(self, name, settle=1.0):
        x, y = self.at(name)
        self.click(x, y, settle=settle)
        return x, y

    def strip_box(self):
        x, y, w, h = self.client_rect()
        f = STRIP_FRAC
        return (int(x + f[0] * w), int(y + f[1] * h),
                int(x + f[2] * w), int(y + f[3] * h))

    def screen_score(self, ref_path, box=None):
        """Mean absolute pixel difference against a reference. 0 == identical.

        References in ref/ are stored pre-cropped to BUTTON_STRIP — that strip
        is the only region the match uses, and storing whole 1280x1024 frames
        cost 2.8 MB to compare 60 pixel rows."""
        box = box or self.strip_box()
        ref = Image.open(ref_path).convert("RGB")
        cur = self._grab().crop(box)
        # References are stored at whatever resolution they were captured at;
        # compare like for like rather than assuming they match this run.
        if ref.size != cur.size:
            ref = ref.resize(cur.size)
        diff = ImageChops.difference(ref, cur)
        px = list(diff.getdata())
        return sum(sum(p) for p in px) / (len(px) * 3)

    def park(self):
        """Move the pointer off the button strip before comparing screens.
        A button under the cursor draws highlighted, and the strip is precisely
        what the match reads -- leaving the pointer there adds ~9 to every
        score and fails a screen that is in fact correct."""
        x, y, w, h = self.client_rect()
        self.move(int(x + w * 0.5), int(y + h * 0.35))

    def wait_for_screen(self, ref_path, tol=8.0, timeout=180, poll=2.0, box=None):
        """Block until the screen matches `ref_path`. Raises with the best score
        seen, so a failure says how close it got rather than just timing out."""
        self.park()
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
    def place(self, name="Lord of the Rings"):
        """Move the game window flush to the desktop origin.

        Wine places it at -80,-92 inside its virtual desktop, so the left and
        top of the game -- the player-name column and the team dropdowns -- sit
        outside the screen and cannot be captured or clicked. Nothing warns you:
        the buttons along the bottom still work, so a run seats players happily
        and only fails when it reaches for something up there."""
        r = self._run("xdotool", "search", "--name", name)
        wins = r.stdout.split()
        if not wins:
            raise RuntimeError(f"{self.display}: no window named {name!r} to place")
        self._run("xdotool", "windowmove", wins[0], "0", "0")
        time.sleep(0.5)

    def focus(self, name="Lord of the Rings"):
        r = self._run("xdotool", "search", "--name", name)
        if not r.stdout.strip():
            raise RuntimeError(f"no window matching {name!r} on {self.display}")
        wid = r.stdout.split()[0]
        self._run("xdotool", "windowfocus", wid)
        time.sleep(0.4)
        return wid

    def dismiss_profile_prompt(self, ref_setup, name="tester", tol=8.0):
        """A wine prefix with no skirmish profile opens a modal "Create Profile"
        over the skirmish setup screen, dimming the button strip so the screen
        match fails with no explanation. Detect that by the match failing, fill
        the dialog in, and then require the real screen -- so a prefix's first
        run works and a genuinely wrong screen still fails loudly.

        Returns True if a profile was created."""
        try:
            self.wait_for_screen(ref_setup, tol=tol, timeout=25)
            return False
        except RuntimeError:
            pass
        self.shot("profile-prompt")
        self.click(674, 592, settle=1)          # the name field
        self.type(name)
        self.click(674, 669, settle=3)          # ACCEPT
        self.wait_for_screen(ref_setup, tol=tol, timeout=60)
        return True

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
