#!/usr/bin/env python3
"""Add a fourth button to the Options screen's nav bar.

The bar is sprite 147. It places ONE character -- 146, the nav-button sprite --
three times, at frames 0, 4 and 9, and tells them apart only by the instance
name on each placement:

    f0   char 146  depth 33  (-170, -6)  name=Save
    f4   char 146  depth 17  (   2, -6)  name=Reset
    f9   char 146  depth  1  ( 172, -6)  name=Cancel

Those names line up exactly with the callbacks the screen's constructor
registers -- `AptOptions::Save`, `AptOptions::Reset`, `AptOptions::Cancel` --
so a fourth placement of the same character, at the next 170-unit step, is the
whole button. It inherits the art, the hover glow and the click sound because it
IS the button the other three are.

Whether the instance name is also what dispatches the click is the open
question; `RefreshNat` is used because it is a command the constructor already
registers, so a click either arrives at a handler we can hook or does not
arrive at all, and both answers are worth one run.
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "..", "..", "tools"))
import bigpack                                          # noqa: E402
from aptfile import Apt                                 # noqa: E402

NAV_SPRITE = 147
NAV_BUTTON = 146
FRAME = 0            # where Save is placed, so the button is up from the start

# The next step in the row the other three sit on.
BUTTON_X, BUTTON_Y = 342.0, -6.0
BUTTON_DEPTH = 40    # clear of the authored 1, 17 and 33
BUTTON_NAME = "RefreshNat"

# The button's own label is an ActionScript variable -- its text characters bind
# to `_parent._parent.buttonName`, which the screen's script sets per authored
# instance and which `buttonName` being absent from the executable says no C++
# ever touches. A fourth instance therefore keeps the placeholder dashes.
#
# So the label is placed rather than assigned: character 189 is the movie's own
# `$CustomGraphics` text, the very words the tab titles itself with, and putting
# it over the button costs no ActionScript and no string-table entry.
LABEL_CHAR = 189
LABEL_SCALE = 0.55
LABEL_X, LABEL_Y = 281.0, -9.0
LABEL_DEPTH = 41


def build(src, dst):
    out = []
    for name, data in bigpack.read(src):
        if name == "Options.apt":
            a = Apt(data)
            nav = {p["name"]: p for p in
                   (a.place_info(o) for f in range(len(a.frames_of(NAV_SPRITE)))
                    for o in a.ops(f, NAV_SPRITE) if a.u32(o) == 3)
                   if p["char"] == NAV_BUTTON}
            if set(nav) != {"Save", "Reset", "Cancel"}:
                raise SystemExit(f"nav bar is not the expected three buttons: {sorted(nav)}")
            a.place(FRAME, NAV_BUTTON, BUTTON_DEPTH, BUTTON_X, BUTTON_Y,
                    name=BUTTON_NAME, cid=NAV_SPRITE)
            a.place(FRAME, LABEL_CHAR, LABEL_DEPTH, LABEL_X, LABEL_Y,
                    cid=NAV_SPRITE,
                    scale=(LABEL_SCALE, 0.0, 0.0, LABEL_SCALE))
            print(f"  Options.apt {len(data):,} -> {len(a.bytes()):,} B, "
                  f"{BUTTON_NAME!r} added to the nav bar")
            data = a.bytes()
        out.append((name, data))
    magic, align, gap, bias = bigpack.conventions_of(src)
    bigpack.write(dst, out, magic=magic, align=align, gap=gap, header_bias=bias)
    print(f"  wrote {dst} ({os.path.getsize(dst):,} B)")


if __name__ == "__main__":
    src = sys.argv[1] if len(sys.argv) > 1 else os.path.expanduser(
        "~/.wine/drive_c/BFME1/apt/options.big")
    build(src, sys.argv[2] if len(sys.argv) > 2 else "options.big")
