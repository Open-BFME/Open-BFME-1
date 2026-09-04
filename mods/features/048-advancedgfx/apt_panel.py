#!/usr/bin/env python3
"""Build the Open-BFME Options panel: the nav button, and our own info block.

Two edits, both through `tools/aptfile.py`, neither of which moves a byte of the
original movie.

**The button.** The nav bar is sprite 147, and it places ONE character -- 146 --
three times, telling Save, Reset and Cancel apart only by the instance name on
each placement:

    f0  char 146  depth 33  (-170, -6)  name=Save
    f4  char 146  depth 17  (   2, -6)  name=Reset
    f9  char 146  depth  1  ( 172, -6)  name=Cancel

Those names are exactly the callbacks the screen's constructor registers, and a
click dispatches on the name -- measured. So a fourth placement at the next
170-unit step is the whole button, and it inherits the art, the hover glow and
the click sound because it IS the button the other three are.

**Its label.** A button's own text binds to the ActionScript variable
`_parent._parent.buttonName`, which the screen's script sets per authored
instance and which appears nowhere in the executable, so a fourth instance keeps
the placeholder. The label is therefore a text character we add. It must carry
the BUTTON font (0x1e at 16pt) and not the panel-label font (0xa at 18pt) --
they are visibly different faces, which is what the first attempt got wrong by
reusing the tab title's own character.

**The info block.** The Custom Graphics tab has an empty band under its sliders,
and that is where Open-BFME says what it has added to the player's game. New
text characters, our own words: a string with no leading `$` renders literally,
so none of this needs a CSF entry or a `lang/english.big` edit.
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), "..", "..", "..", "tools"))
import bigpack                                          # noqa: E402
import aptfile                                          # noqa: E402
from aptfile import Apt                                 # noqa: E402

NAV_SPRITE, NAV_BUTTON = 147, 146

# The button goes on the MOVIE's own tab frames, not into the shared nav sprite.
# Both would look identical, but the nav bar is drawn on every tab including the
# online one -- and the online tab has the game's own Refresh NAT button, which
# carries the same command ours does. Two buttons, one command, no way to tell
# them apart from the handler. Placing ours only where the normal and advanced
# tabs rest keeps the online tab's button unambiguous.
BUTTON_FRAMES = (29, 120)

# The nav bar sits at (512.2, 740) on the movie, so its own three buttons are at
# -170, 2 and 172 from there. Ours continues the row at +342.
NAV_X, NAV_Y = 512.2, 740.0
BUTTON_X, BUTTON_Y = NAV_X + 342.0, NAV_Y - 6.0
BUTTON_DEPTH, LABEL_DEPTH = 960, 962
BUTTON_NAME = "RefreshNat"
# Two lines, because that is what ACCEPT CHANGES and RESET SETTINGS do -- a
# fifteen-character label on one line overflows a button this width.
LABEL_LINES = ["CUSTOM", "GRAPHICS"]
LABEL_SIZE = 16.0                    # what the authored button labels use
LABEL_X, LABEL_Y, LABEL_LINE_H = NAV_X + 232.0, NAV_Y - 26.0, 19.2

# The nav button draws its label twice -- 140 is the dark shadow, 130 the light
# face on top -- and both carry "...\r...." as their initial text, taking their
# real words from `buttonName`. The three authored buttons set that variable, so
# the placeholder never shows for them; ours cannot, so it does, as a dashed row
# straight through the second line. Clearing the initial text removes it and
# costs the authored buttons nothing, because the variable supplies their text
# either way.
#
# The carriage return is why a first attempt cleared the wrong pair: a scan for
# placeholder text that filters on printable characters skips these two and
# finds only 31 and 46, which belong to a different button style.
PLACEHOLDER_CHARS = (130, 140)
LABEL_COLOR = 0xFFD7A34D             # the warm gold the other three labels use

# The advanced tab's resting frame, and the empty column inside its panel --
# right of the slider box, under the right-hand checkboxes. Putting the block
# there keeps it inside the frame and gives it the same shape as the two
# authored columns beside it, instead of a wide band spilling over the border.
ADV_FRAME = 120
BLOCK_X, BLOCK_Y, LINE_H = 655.0, 468.0, 19.0
BLOCK_DEPTH = 940
HEAD_COLOR, KEY_COLOR, BODY_COLOR = 0xFFE99A44, 0xFFD7A34D, 0xFFFFFFFF

# What Open-BFME actually adds to the player's game. Every line is a feature
# shipped in mods/dist -- drop one from the build and its line comes out here.
# (key, description) -- a heading is a key with no description. The two are
# separate text characters at two x positions, because the UI font is
# proportional and padding a single string with spaces does not line a column up.
KEY_DX = 96.0
LINES = [
    ("OPEN-BFME", None),
    ("Replay camera", None),
    ("[  ]", "rotate"),
    (",  .", "pitch"),
    ("PgUp/PgDn", "zoom"),
    ("/", "controls"),
    ("Replay", None),
    ("ctrl+period", "pause"),
]


def build(src, dst):
    out = []
    for name, data in bigpack.read(src):
        if name == "Options.apt":
            a = Apt(data)
            nav = {p["name"] for p in
                   (a.place_info(o) for f in range(len(a.frames_of(NAV_SPRITE)))
                    for o in a.ops(f, NAV_SPRITE) if a.u32(o) == 3)
                   if p["char"] == NAV_BUTTON}
            if nav != {"Save", "Reset", "Cancel"}:
                raise SystemExit(f"nav bar is not the expected three buttons: {sorted(nav)}")
            if "_open_advanced" not in a.labels():
                raise SystemExit("Options.apt has no _open_advanced tab -- wrong file?")

            for c in PLACEHOLDER_CHARS:
                a.set_text_string(c, "")

            for frame in BUTTON_FRAMES:
                a.place(frame, NAV_BUTTON, BUTTON_DEPTH, BUTTON_X, BUTTON_Y,
                        name=BUTTON_NAME)
                for i, line in enumerate(LABEL_LINES):
                    c = a.add_text(line, font=aptfile.FONT_BUTTON, size=LABEL_SIZE,
                                   color=LABEL_COLOR, align=aptfile.ALIGN_CENTER,
                                   width=226.5)
                    a.place(frame, c, LABEL_DEPTH + i, LABEL_X,
                            LABEL_Y + LABEL_LINE_H * i)

            for i, (key, desc) in enumerate(LINES):
                y = BLOCK_Y + LINE_H * i
                head = desc is None
                c = a.add_text(key, font=aptfile.FONT_LABEL, size=13.0,
                               color=HEAD_COLOR if i == 0 else
                               (KEY_COLOR if head else BODY_COLOR),
                               align=aptfile.ALIGN_LEFT, width=220.0)
                a.place(ADV_FRAME, c, BLOCK_DEPTH + 2 * i,
                        BLOCK_X + (0.0 if head else 10.0), y)
                if desc:
                    d = a.add_text(desc, font=aptfile.FONT_LABEL, size=13.0,
                                   color=BODY_COLOR, align=aptfile.ALIGN_LEFT,
                                   width=220.0)
                    a.place(ADV_FRAME, d, BLOCK_DEPTH + 2 * i + 1,
                            BLOCK_X + KEY_DX, y)

            print(f"  Options.apt {len(data):,} -> {len(a.bytes()):,} B; "
                  f"button {BUTTON_NAME!r}, {len(LINES)} info lines, "
                  f"{a.char_count} characters")
            data = a.bytes()
        out.append((name, data))
    magic, align, gap, bias = bigpack.conventions_of(src)
    bigpack.write(dst, out, magic=magic, align=align, gap=gap, header_bias=bias)
    print(f"  wrote {dst} ({os.path.getsize(dst):,} B)")


if __name__ == "__main__":
    src = sys.argv[1] if len(sys.argv) > 1 else os.path.expanduser(
        "~/.wine/drive_c/BFME1/apt/options.big")
    build(src, sys.argv[2] if len(sys.argv) > 2 else "options.big")
