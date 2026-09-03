# 048-advancedgfx — BFME's own Custom Graphics tab, which 2.22 never opens

Eleven graphics settings ship inside BFME1, finished on both sides, and the
retail game has no way to reach any of them. This turns them on.

| | |
|---|---|
| Anisotropic Texture Filtering | Smooth Water Border |
| Terrain Lighting | Show Props |
| 3D Shadows | Show Animations |
| 2D Shadows | Heat Effects |
| Dynamic LOD | |
| Texture Detail *(slider)* | Particle Cap *(slider)* |

A **CUSTOM GRAPHICS** button sits in the Options nav bar beside CANCEL. Click it
for the tab, click it again to come back. F11 does the same thing from the
keyboard.

## Why this is one call and not a mod

`Options.apt` carries the whole tab — eleven widgets, their labels, their
tooltips and an animated open and close, at frames 102..121 behind the label
`_open_advanced`. The engine side is finished too: every one of the eleven has a
slot on the screen object, a line in `AptOptions::Save` and a line in the load
path. Even the navigation exists.

    AptOptions::showAdvanced   RVA 0x0055DBA0   __thiscall(screen)

Nothing in the game calls it. That one function does both halves — it calls
`assignOpen("advanced")` on the movie through `WindowManager::callFunction`, and
it sets the screen state to 4.

**Both halves matter.** `AptOptions::InitGadgets` (RVA `0x005625C0`) is not a
lookup: it is the callback the APT runtime invokes per gadget as that gadget is
created, and its compare-and-store chain runs only when the state reads 4. Play
the movie without setting the state and the tab draws with nothing bound to it.

Going back needs no logic of its own. `AptOptions::update` opens a tab only out
of state 1, so dropping the state to 1 hands the screen to the game's own code
and it reopens the normal tab on its next frame.

## Measured, not assumed

The screen object's widget slots were read directly, through 047-uiprobe's F10
dump, on the live screen:

| | normal tab | after F11 |
|---|---|---|
| state (`screen+0x258`) | 2 | **4** |
| `HealthBars` — the control | non-null | non-null |
| all eleven advanced slots | **0** | **all non-null** |

`HealthBars` is the control: it is an authored widget that visibly loads its
value, so a run where it read null would mean the dump was wrong rather than the
registration.

Then end to end, with `HeatEffects = yes` in `Options.ini` and every other
advanced setting off: **Heat Effects came up as the one ticked box.** So
registration, the game's load path and the render are all proved together, and
`Save` writes them back through code that was already there.

## The button, and the Open-BFME block

`apt_panel.py` builds both, through `tools/aptfile.py`, without moving a byte of
the original movie.

The nav bar is sprite 147 and it places ONE character -- 146 -- three times,
telling Save, Reset and Cancel apart only by the instance name on each
placement. **A click dispatches on that name**: named `RefreshNat` the click
arrives at `AptOptions::RefreshNat`, measured as `{"hit":"RefreshNat","state":2}`
on a real mouse click. So the button costs one placement and one detour, and it
inherits the art, the hover glow and the click sound because it *is* the button
the other three are.

Its label is two text characters of our own, on two lines -- what ACCEPT CHANGES
and RESET SETTINGS do, and a fifteen-character label does not fit this button on
one line. They carry **font `0x1e`**, the button face. An earlier pass reused the
tab title's character, which is font `0xa`, and the wrong face was obvious on
sight. A button's own label cannot be set instead: it binds to the ActionScript
variable `_parent._parent.buttonName`, which appears nowhere in the executable.

The tab's panel has an empty column right of the slider box, and that is where
Open-BFME says what it has added -- the replay camera keys and the replay pause,
in the screen's own fonts and colours. Each row is two text characters at two x
positions, because the UI font is proportional and padding one string with
spaces does not line a column up. Every line is a feature actually shipped in
`mods/dist`; drop one from the build and its line comes out of `LINES`.

## Why it is UNSHIPPED

The button carries `RefreshNat` because that is a command the constructor
already registers, and a name with no callback behind it does nothing. Two
consequences, both real:

* the online tab's own Refresh NAT button shares the command. The handler guards
  on screen state -- it acts only on the normal and advanced tabs and falls
  through on the online one -- but this is a squat, not a design.
* the detour runs before the real `RefreshNat`, which still executes afterwards.
  On the normal tab that is a spurious NAT check, and it is visible: it writes
  `FirewallNeedToRefresh` and `FirewallPortAllocationDelta` into `Options.ini`.

The fix is to register `AptOptions::Advanced` properly. The pieces are known --
the constructor builds each binding from an AsciiString and a refcounted
delegate, whose constructor is at RVA `0x0055F140`. That is the next piece of
work, and it is what a custom Open-BFME tab would need anyway.

It also shares 046-optionsui's hook address, `AptOptions::update`, so build one
at a time until 046 is shipped or dropped.