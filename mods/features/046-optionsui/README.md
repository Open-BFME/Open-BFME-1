# 046-optionsui — three Open-BFME settings in BFME's own Options screen

**UNSHIPPED, and not yet driven by hand.** The code is written against addresses
measured from the game's own `AptOptions::Save`, it builds, and its two hooks
land. What has not happened is a person clicking the boxes: the test rig lost
its display mid-way and no replacement would deliver mouse input to the game
(see *Why there are no screenshots* below). Nothing here should be believed to
work until someone has ticked one.

## What it is

Not a panel drawn over the game — the real APT Options screen, with the real
widgets. Three checkboxes become Open-BFME settings:

| label | was | drives |
|---|---|---|
| Camera: rotate | Show All Health Bars | 043's `[` and `]` |
| Camera: tilt | Show Unit Decals | 043's `,` and `.` |
| Camera: free zoom | Alternate Mouse Setup | 043's zoom cap release |

The chrome, the font, the hover glow and the click sounds are the game's,
because the widgets **are** the game's. `Options.apt` builds itself out of
`GameWindowGadgets/CheckBox` and `MenuExport/Button`, so there is nothing for a
mod to imitate and nothing to keep in sync when it changes.

The labels are a data change: `apt_labels.py` rewrites them inside `Options.apt`
and repacks with `tools/bigpack.py`. A replacement may not be longer than the
slot its original occupies, and the script fails rather than shifting anything —
the movie is a memory image addressed by file offset. See `docs/apt-ui.md`.

## Taking a widget over means taking its side effect too

A relabelled checkbox that still wrote the game's own option would be exactly
the silent surprise this project refuses: tick "Camera: tilt" and unit decals
quietly turn off in `Options.ini`.

So `AptOptions::Save` is hooked **at its entry**, before it has read a single
widget, and the three checkboxes are put back to the values the game had in
them. The game then persists what it always would have, and the only place
these three settings live is the mod bus.

That is also why this feature is UNSHIPPED without its archive. Shipped alone,
a box still reading "Show All Health Bars" would drive the replay camera. Ship
the pair or neither.

## The mod bus

Features are compiled and linked one at a time with no linker between them, so
one cannot name a symbol in another. What they *can* share is an address, and
the cave's own base is the one address every feature already knows. `modbuild.py`
reserves the first `0x40` bytes of the cave, zeroed, and never allocates them to
a payload.

```
+0x00  u32  magic 'OBFM'
+0x04  u8   camera: rotate enabled
+0x05  u8   camera: tilt enabled
+0x06  u8   camera: free zoom enabled
```

**The magic is the gate, not the byte.** A build without 046 leaves the bus
zeroed, and zero must not read as "every camera axis off" — so an unclaimed bus
means everything is enabled, which is exactly how 043 behaved before the bus
existed. That is why `mods/dist` is behaviourally unchanged by this commit even
though 043 now reads the bus.

The bus VA is compiled into each feature as a literal, because there is no way
to tell a payload about it at link time. `modbuild.py` therefore checks that the
reserved block really lands at `MOD_BUS_VA` and fails the build if it does not,
so a moved cave is a build error rather than every feature silently reading
somebody else's memory.

## Measured, not inferred

Every address came off a call site or a constructor.

| Thing | Where | From |
|---|---|---|
| `BfmeAptScreenOptions` singleton | VA `0x012F4AD4` | stored in the ctor at RVA `0x009634C3` |
| its vtable | VA `0x0110912C` | the ctor's own store |
| `update()` — ticks while the screen is up | vtable `+0x14` → RVA `0x0055DC00` | |
| `AptOptions::Save` | RVA `0x00560280` | bound in the ctor at `0x00963532`; the ledger pins this body as `OptionsMenuInit`, which is wrong |
| `AptOptions::OnInitialized` / `Reset` | RVA `0x0055DCA0` / `0x0055E470` | same three-way binding |
| `AptOptions::InitGadgets` | RVA `0x005625C0` | where every widget offset below comes from |
| `GadgetCheckBoxIsChecked(w)` | RVA `0x004B3230` | `__cdecl`, returns bit 2 of the window status |
| `GadgetCheckBoxSetChecked(w, b)` | RVA `0x004B31D0` | `__cdecl`, and it repaints |

`InitGadgets` caches every widget on the singleton by name, which is the whole
map:

```
+0x284 Resolution   +0x288 Detail      +0x28C OnlineIp
+0x290 HealthBars   +0x294 AlternateMouseSetUp   +0x29C ShowUnitDecals
+0x2BC AnisotropicTextureFiltering     +0x2C0 TerrainLighting
+0x2C4 3dShadows    +0x2C8 2dShadows   +0x2CC SmoothWaterBorder
+0x2D0 ShowProps    +0x2D4 ShowAnimations        +0x2D8 HeatEffects
+0x2DC DisableDynamicLOD                +0x2E0..+0x2F0 the five volume sliders
+0x2F4 ScrollSpeed  +0x2F8 Brightness  +0x2FC TextureDetail
```

**Eleven of those widgets are real, and BFME1 simply never shows them.** They
are authored into `Options.apt` as a complete Custom Graphics tab and they bind
themselves the moment the screen is put into state 4 -- which is what
`AptOptions::showAdvanced` at RVA `0x0055DBA0` does, and what nothing in the
game calls. See `mods/features/048-advancedgfx/`. (An earlier note here said
those widgets were missing from the movie. They are not.)

## Why there are no screenshots

The rig's display died part-way through and nothing would replace it:

* the headless sway displays `gpu-displays.sh` makes now log
  `[xwayland ei] Setup failed` / `EI setup failed`, and XTest input never
  reaches the client — the pointer moves at the X level and the game sees
  nothing, no hover, no clicks
* on a plain `Xvfb`, the **keyboard reaches the game** (Escape visibly changes
  the screen) but the mouse still does not, so menu buttons cannot be pressed
* `grim`, which the rig screenshots with, only speaks to a wlroots compositor,
  so it cannot capture Xvfb at all — `scratchpad/x11shot.py` uses `import`
  instead and works

The feature needs a mouse to demonstrate, so it waits. **Next session: fix the
display first, then tick a box.** If the rig stays broken, the fallback is a
throwaway probe keyed to the keyboard — which does work — that calls
`showAptScreen` to open the screen and flips a bus byte, since watching the
checkbox follow the bus exercises the same `SetChecked` path the feature uses.
