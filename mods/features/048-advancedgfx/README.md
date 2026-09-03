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

## Why it is UNSHIPPED

Only the trigger. A key is the wrong way into a settings screen — this wants a
button next to ACCEPT CHANGES, and the screen's three buttons are authored into
the movie. `tools/aptfile.py` can place one (see `docs/apt-ui.md`); wiring its
click back to the cave through the FSCommand path is the part that has not been
done. The tab itself is finished and works.

It also shares 046-optionsui's hook address, `AptOptions::update`, so build one
at a time until 046 is shipped or dropped.
