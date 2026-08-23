#!/usr/bin/env python3
"""The four ways a client leaves a match: demolish, quit, kill and freeze.

The first two are driven through the client's own UI, and both controls fail
silently when missed -- Demolish gives no tooltip and does nothing when the
pointer is four pixels off, and the pause menu's EXIT sits among buttons that
also change the screen when clicked -- so "the screen changed" is never taken as
evidence that the right thing was pressed. Each of those clicks is preceded by a
positive identification of what is under the pointer, and anything that cannot
be identified raises rather than proceeding.

The last two are signals delivered to the client's process, and they differ in
kind rather than in degree. SIGKILL has the kernel close the client's sockets on
the way out, so its peers see a connection go. SIGSTOP sends nothing at all: the
sockets stay open and silent, and the peers can only reach the same conclusion
through their timeout path.
"""
import os
import signal
import time
from pathlib import Path

from PIL import Image

from driver import UI

REF = Path(__file__).resolve().parent / "ref640"

# Both panels these references come from are translucent, so a mean pixel
# difference measures the terrain showing through rather than the words on top:
# the same Demolish tooltip over castle stone and over open ground differ by 26,
# three times the tolerance driver.screen_score is used with. The lettering is
# the invariant, so only the bright pixels are compared, as a set.
BRIGHT = 150
MATCH = 0.5

# The Demolish tooltip's title line. Only the title line: the citadel's own
# "Gondor Citadel / Health: 4000" tooltip fills the same panel, and over the
# whole panel the two overlap enough to be confusable.
TOOLTIP_FRAC = (0.3859, 0.7992, 0.6203, 0.8323)

# "EXIT" in the confirmation dialog's title bar.
CONFIRM_FRAC = (0.3625, 0.3271, 0.6359, 0.3727)

# Where to look for this client's citadel. The camera opens on the castle, but
# not identically on every machine -- UI["CITADEL"] selected it on one client and
# missed on another -- so the point is searched for per client rather than
# assumed. The step is smaller than the citadel's own footprint, so a citadel
# anywhere inside the span is hit by some node of the grid.
CITADEL_STEP = (0.047, 0.046)
CITADEL_SPAN = 4


def _point(d, frac):
    """A fraction of the client area as a rounded screen point.

    Rounded, not truncated the way Driver.at() is: flooring puts DEMOLISH at
    (127, 486) where the button answers at (128, 487). That is still inside its
    couple of pixels of tolerance, but there is no reason to spend the margin on
    arithmetic."""
    x, y, w, h = d.client_rect()
    return round(x + frac[0] * w), round(y + frac[1] * h)


def _box(d, frac):
    x, y, w, h = d.client_rect()
    return (round(x + frac[0] * w), round(y + frac[1] * h),
            round(x + frac[2] * w), round(y + frac[3] * h))


def _mask(image):
    return [sum(pixel) > 3 * BRIGHT for pixel in image.getdata()]


def _text_score(d, ref_name, frac):
    """How much of a stored lettering mask the screen reproduces, 0 to 1."""
    ref = _mask(Image.open(REF / ref_name).convert("RGB"))
    cur = _mask(d._grab().crop(_box(d, frac)))
    if len(ref) != len(cur):
        raise RuntimeError(
            f"{d.display}: {ref_name} is {len(ref)} pixels, the box on this screen "
            f"is {len(cur)}; the reference was captured at another resolution")
    union = sum(a or b for a, b in zip(ref, cur))
    return sum(a and b for a, b in zip(ref, cur)) / union if union else 0.0


def _citadel_points():
    """Grid nodes around UI["CITADEL"], nearest first, so the usual case costs
    one probe and the unusual one costs a search rather than a wrong answer."""
    cx, cy = UI["CITADEL"]
    sx, sy = CITADEL_STEP
    grid = [(cx + i * sx, cy + j * sy)
            for i in range(-CITADEL_SPAN, CITADEL_SPAN + 1)
            for j in range(-CITADEL_SPAN, CITADEL_SPAN + 1)]
    return sorted(grid, key=lambda p: (p[0] - cx) ** 2 + (p[1] - cy) ** 2)


def arm_demolish(d):
    """Select this client's citadel and leave the pointer on Demolish with its
    tooltip up. Returns the button's point, so the caller clicks without moving.

    The tooltip proves both halves at once: it is drawn only when the citadel is
    selected *and* the pointer is on the button, which is exactly the state a
    blind click cannot tell apart from failure."""
    button = _point(d, UI["DEMOLISH"])
    points = _citadel_points()
    best, best_at = 0.0, None
    for n, frac in enumerate(points, start=1):
        d.click(*_point(d, frac), settle=0.6)
        d.move(*button)
        time.sleep(0.4)
        score = _text_score(d, "demolish-tooltip.png", TOOLTIP_FRAC)
        if score > best:
            best, best_at = score, frac
        if score >= MATCH:
            print(f"    citadel at {frac[0]:.3f},{frac[1]:.3f} "
                  f"(probe {n}, tooltip {score:.2f})", flush=True)
            d.shot("demolish-armed")
            return button
    raise RuntimeError(
        f"{d.display}: none of {len(points)} probes selected a citadel whose Demolish "
        f"button answered (best tooltip {best:.2f} at {best_at}, needed {MATCH})")


def demolish(d):
    """Destroy this client's citadel, which defeats that player on the spot with
    leave=0 -- a real loss rather than a quit. There is no confirmation."""
    d.click(*arm_demolish(d), settle=2)
    d.shot("demolish-clicked")


def quit(d):
    """Leave the match through the pause menu: ESC, EXIT, confirm.

    The confirmation dialog is identified before YES is pressed. EXIT shares the
    menu with buttons that open something of their own, so without that a missed
    EXIT looks exactly like a hit one until YES lands on whatever the other
    dialog put in its place."""
    d.focus()
    playing = d._grab()
    d.key("Escape", settle=1.5)
    if d.wait_change(playing, timeout=20, min_pixels=5000) is None:
        raise RuntimeError(f"{d.display}: ESC opened no pause menu")
    menu = d.shot("esc-menu")
    d.tap("ESC_EXIT", settle=2)
    d.park()
    best = 0.0
    for _ in range(10):
        best = max(best, _text_score(d, "exit-confirm.png", CONFIRM_FRAC))
        if best >= MATCH:
            break
        time.sleep(1.5)
    else:
        d.shot("no-exit-dialog")
        raise RuntimeError(
            f"{d.display}: EXIT was clicked but no exit confirmation appeared "
            f"(best {best:.2f}, needed {MATCH}); the click landed on something else")
    print(f"    exit confirmation up ({best:.2f})", flush=True)
    d.shot("exit-dialog")
    d.tap("CONFIRM_YES", settle=3)
    if d.wait_change(menu, timeout=30, min_pixels=5000) is None:
        raise RuntimeError(f"{d.display}: confirming EXIT left the screen unchanged")
    d.shot("quit-confirmed")


# --- the two that are done to the process rather than through the UI --------

# Everything under one WINEPREFIX shares that prefix, wineserver included, and
# wineserver is not the client: the sockets the peers are watching belong to the
# processes that opened them. Both the desktop launcher and the game itself
# carry the exe on their command line, and both are the client as far as a peer
# is concerned, so both are signalled together.
CLIENT_EXE = "lotrbfme"

# How long to give the kernel to act on a signal we have already sent. This is
# not a readiness wait -- the process is ours and already exists -- so a second
# would do; the margin is for a machine loaded with four wine clients.
SIGNAL_TIMEOUT = 30


def _environ(pid):
    """One process's environment as a dict, or None if it is not ours to read.

    Unreadable means another user's process, or one already reduced to a zombie.
    Either way it is not a client of ours, and it is skipped rather than guessed
    at -- the rule kill-mine.sh follows, for the same reason: this machine is
    shared, and another agent's clients run this very binary."""
    try:
        raw = Path(f"/proc/{pid}/environ").read_bytes()
    except OSError:
        return None
    return dict(entry.split("=", 1)
                for entry in raw.decode("utf-8", "replace").split("\0") if "=" in entry)


def _state(pid):
    """The scheduler state letter from /proc/<pid>/stat -- `T` while stopped.

    Taken from after the last `)`, because the field before it is the comm and
    a comm is allowed to contain both spaces and brackets."""
    stat = Path(f"/proc/{pid}/stat").read_text()
    return stat[stat.rindex(")") + 2]


def _clients(prefix):
    """The live client pids running under this WINEPREFIX, with their names.

    Matched on the prefix in the process's own environment, never on the exe
    name alone."""
    found = {}
    for entry in Path("/proc").iterdir():
        if not entry.name.isdigit():
            continue
        try:
            args = (entry / "cmdline").read_bytes().decode("utf-8", "replace")
            name = (entry / "comm").read_text().strip()
        except OSError:
            continue
        if CLIENT_EXE not in args and CLIENT_EXE not in name:
            continue
        env = _environ(entry.name)
        if env is None or env.get("WINEPREFIX") != prefix:
            continue
        found[int(entry.name)] = name
    return found


def _signal(prefix, sig, verb):
    """Send one signal to every client process under `prefix`, or raise."""
    found = _clients(prefix)
    if not found:
        raise RuntimeError(
            f"{prefix}: no live client process to {verb}; nothing under this prefix "
            f"has {CLIENT_EXE!r} on its command line")
    for pid in found:
        os.kill(pid, sig)
    print(f"    {verb}: " + ", ".join(f"{pid} ({name})" for pid, name in sorted(found.items())),
          flush=True)
    return found


def kill(prefix):
    """SIGKILL this client -- a crash, with no chance to say anything.

    The client writes nothing on the way out, so what this exit looks like is
    entirely a question of what its peers record about it."""
    _signal(prefix, signal.SIGKILL, "kill -9")
    deadline = time.time() + SIGNAL_TIMEOUT
    while time.time() < deadline:
        left = _clients(prefix)
        if not left:
            return
        time.sleep(0.5)
    raise RuntimeError(f"{prefix}: still running {SIGNAL_TIMEOUT}s after SIGKILL: {left}")


def freeze(prefix):
    """SIGSTOP this client -- it is still there, holding its sockets open, and
    saying nothing.

    Every caller owes the client it froze a thaw(): a stopped process holds its
    wine prefix open, and the next run that reaches for that prefix attaches to
    the wineserver the stopped client never let go of."""
    found = _signal(prefix, signal.SIGSTOP, "kill -STOP")
    deadline = time.time() + SIGNAL_TIMEOUT
    while time.time() < deadline:
        awake = {pid: _state(pid) for pid in found if _state(pid) not in "Tt"}
        if not awake:
            return
        time.sleep(0.5)
    raise RuntimeError(
        f"{prefix}: {SIGNAL_TIMEOUT}s after SIGSTOP these are still scheduled: {awake}")


def thaw(prefix):
    """Resume a frozen client. Returns the pids that were actually stopped.

    Sent to every client under the prefix rather than only to the ones found
    stopped, because a process that stopped after the survey is exactly the one
    that must not be left behind. SIGCONT to a running process does nothing."""
    found = _clients(prefix)
    stopped = sorted(pid for pid in found if _state(pid) in "Tt")
    for pid in found:
        os.kill(pid, signal.SIGCONT)
    print(f"    thawed {len(stopped)} stopped of {len(found)} client process(es) "
          f"under {prefix}", flush=True)
    return stopped
