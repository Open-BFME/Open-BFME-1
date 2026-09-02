# 60 FPS — three closed doors, and an instrument that lied

**Nothing here ships.** `036`, `037` and `038` are all `UNSHIPPED` and `--dist`
refuses them. This document exists so the next attempt does not re-walk the
three routes that are closed, and does not trust the instruments as far as this
attempt did.

The goal was the whole game at 60 fps — units included, multiplayer and single
player and menus. What exists is `038-fpsrender`: nine lines that raise the
render limit to 60 **in a network match only**. Units still step at 30 Hz,
skirmish and menus stay at 38. That is roughly a quarter of the ask, and on the
machine it was tried on a separate ~100 ms stall dominates whatever the render
rate is.

## The three closed doors

**1. Doubling the simulation sub-step count (`037-fps60`).** Smooths unit motion
and breaks everything authored in frames: `Lifetime` 2,735 times,
`SystemLifetime` 1,965, `BurstDelay` 1,517 across 724 ini files. Every
instrument read green; the Heal spell still ran visibly fast in play. The
sub-step count is a UNIT that subsystems count in and there is no list of which.
Also settles a question `docs/measuring.md` used to leave open: those six phases
ARE simulation sub-steps, because a client-side interpolation pass could not
have changed spell timing.

**2. Extrapolating at `RenderObjClass::Set_Transform` (`0x009201A0`, vtable slot
21).** The game does not call it on the frames between simulation steps — the
repeats it does see are same-frame resubmissions from the shadow and other
passes. Proved with three diagnostic builds of one payload: displacing every
repeat by ±60 units drove p25 cell-duplicate 95.5–98.9% → **70.9%** (the path
runs and reaches the screen); restricting to non-zero velocity → **82.3%** (the
velocities are real); the actual `vel × age` scaled ×20 → **97.1%**, inside the
band. `vel` is non-zero and `vel × age` is zero, so `age` is zero. Feature
deleted once settled.

Writing the drawable's position instead does not work either, and that was
measured: `GameClient+0x10` heads an intrusive list, `Drawable+0x104` next,
`Drawable+0x108` previous (named from `Drawable::prependToList`, `0x00411C50`).
282 drawables a frame, `Thing::setPosition` moved them (3395.0 → 3365.0,
exactly the −30 asked), picture unchanged. Transforms reach render objects
through ~70 draw-module call sites; there is no single bridge above
`Set_Transform`, and `Set_Transform` is below where the frames need changing.

**3. The ~101 ms judder is not ours.** On a stalled frame the engine accounts
for **1 ms of a 101 ms frame** (`work`/`idle` at `0x012ED514`/`0x012ED510`,
`limited` at `0x012ED520`); the rest is inside `Present`, before any game code
runs. It reproduces on a build carrying nothing but the timing probe, so it is
in stock BFME under wine on that machine, at 4–5% of frames.

Eleven candidates eliminated, each with a patch or config change rather than an
argument: the frame limit (38/60/76 all identical); every feature here; the
floating text (gated to logic frames, anchored to a fixed world position — it
cannot move backwards); the probe's frame readback; the probe's file write
(tmpfs); the wine virtual desktop; vsync (`vblank_mode=0`; the display runs at
164.94 Hz); CFS bandwidth throttling (`nr_throttled 0` at every level); CPU
pinning to idle cores; the limiter's own `Sleep(0)` (NOPped to a busy-wait); and
window focus. The limiter's spin loop is at `0x46BF6B`/`0x1358F30`
(`KERNEL32!Sleep`) if someone wants to re-check that one.

## The measurement apparatus, and where it failed

Read this before trusting any number above.

**The pixel metrics do not answer the question anyone asks.** They measure how
OFTEN the screen changes; a player asks how the motion LOOKS. A sawtooth — a
thing that rises and snaps back — changes on every frame and therefore scores
perfectly. Measured: the oscillation test rated the raised-limit build
**healthier** than retail (0.2% vs 1.1%) while a player watching that same build
reported the citadel's floating "+15" rising and snapping back. The same
blindness passed `037` with a double-speed spell.

**What held up** is clock-based: the animation clock (`WW3D::SyncTime` at
`0x0133F420`, slope against wall time — it caught `037` at 2.068×), the frame
budget (`work + idle`), and the liveness guard once it existed.

**The method that worked when reasoning did not:** build the change, measure the
delta, require it outside a three-run baseline band. Every time a cause was
argued from a number that merely matched, it was wrong — three times in one
session (starvation share, the probe's readback, the limiter's `Sleep(0)`).

Specific defects, each of which produced a wrong answer before it was found:

* **A statistic that picks its own sample is not a statistic.** "The 48 cells
  that moved most" selects a different set every run: two captures of an
  IDENTICAL binary read 64.9% and 75.3%, manufacturing a regression that was
  written up as fact. Use a fixed percentile of the fixed 16×12 partition —
  signal-to-noise 7.2 against 1.5. Three baselines minimum; a band from one run
  is not a band.
* **A dead capture reports plausible numbers.** A match that ended mid-run
  leaves the client presenting a static menu at a steady rate. Two multiplayer
  arms were 22% and 14% in-match while reporting confident figures.
  `fpsmeter.require_live()` now refuses them.
* **The instrument's cost scales with what it measures.** The probe copies the
  whole frame GPU→CPU: 0.34 MP at the rig's 660×520, 1.44 MP at a real desktop.
  Build `036-fpsprobe-timing` when resolution matters.
* **Read the limit from the budget, not the frame rate.** `work + idle` is what
  the limiter enforced: ~16 ms means 60, ~26 ms means 38. A present rate cannot
  tell "backed off to 38" from "limit is 60 and this machine delivers 38".
* **Reading the wrong thing entirely.** A `find … | head -1` picked a stale
  capture from another wine prefix and a success was reported that was the exact
  opposite of the run. `/proc/<pid>/stat` fields 12/13 were read as utime/stime
  (they are 14/15) and a process burning 82 s of CPU was called hung at 0%.
  `strace` interleaves calls, and a 1 ms timespec and a 100.5 ms duration read
  off different lines became a headline finding. Pin the path; check the field
  index; use `strace -ff`.
* **Look at it.** Both defects that reached a player — `037`'s spell and the
  `+15` sawtooth — were found by eye, after the instruments reported green.

## Anchors

| what | where |
|---|---|
| `GameEngine::update` (detour for `037`/`038`) | `0x0006E910` |
| `FramesPerSecondLimit` on the engine | `GameEngine+0x08` |
| sub-step immediates (`037`'s two pokes) | `0x0006E986`, `0x0006E9D9` |
| animation ms per sub-step | VA `0x012BB1CC` (33), written at `0x006F40E8` |
| `WW3D::SyncTime` | `0x0133F420` |
| `TheNetwork` | `0x012F7714` |
| frame work / idle / limited | `0x012ED514` / `0x012ED510` / `0x012ED520` |
| the limiter's no-limit path | `0x0006BEC2` |
| `_bfme_updateNetworkAndLogic` | `0x0006BAE0` |
| `RenderObjClass::Set_Transform` — slot 21, matrix by pointer, translation at elements 3/7/11, stored to `this+0x18` | `0x009201A0` |
| the probe's hook (after EndScene, before Present) | `0x00909039` |

The shipped render rate is **38**, from `_patch222.big`, not the compiled 30.
`tools/ini_value.py` reads the value the process actually loaded.

## Single player is a missing gate, not a missing capability

`038` holds skirmish and menus at 38 because with no network nothing paces the
cycle: the game's speed IS the frame rate over six, so raising the limit alone
runs a skirmish fast. But the engine already renders faster than it simulates in
a match, and every solo capture in this work was one human with no peer running
at the raised limit with the clock at 0.99. The capability is there; skirmish
just has nothing gating it.

`_bfme_updateNetworkAndLogic` (`0x0006BAE0`) splits on the phase at once:

```
0006BAEE  jne 0x46BB83          ; phases 2..6 go straight to the update call
0006BAF5  call 0x422C96         ; isGamePaused  -> bl = ready
0006BB08  test ecx, ecx         ; ecx = TheNetwork
0006BB0A  je  0x46BB60          ; NO NETWORK -> tail with ready still 1
0006BB0E  call [eax + 0x3C]     ; getFrameAdvanceCount()
0006BB13  jle 0x46BB5E          ; <= 0 -> xor bl,bl : ready = 0
0006BB81  je  0x46BB8D          ; not ready -> skip the update
0006BB86  call [eax + 0x20]     ; GameLogic::update(phase)
```

One branch is the whole difference: the `je` at `0x0006BB0A`.

Two obstacles before anyone builds on this. `ready` lives in `bl`, and the shim
`cave.py` generates restores every register around the payload — gating it needs
either a shim that can hand a payload the saved-register slot, or a hook site
whose displaced bytes hold no relative branch (the four bytes there are two
relative branches). And what paces the six-phase cycle is **not established**:
phases 2..6 reach `GameLogic::update` unconditionally at `0x0006BB83` and the
period increments every iteration, which predicts ~63 sub-steps/s at a 76 Hz
loop against a measured 30. Resolve that before building against the branch.

## Reproducing

```bash
python3 tools/modbuild.py --only 020-gameresult --only 036-fpsprobe \
                          --only 038-fpsrender -o build/mods/arm.exe
python3 -m pytest tools/tests/test_fps60.py tools/tests/test_fpsprobe.py
python3 tools/fpsmeter.py --phases build/fps/<run>/phases.json build/fps/<run>/P1.jsonl
python3 tools/fpssmooth.py <run> --phase walk     # pacing and staleness
```

`tools/fpssmooth.py` reports the animation clock and calls anything under 0.80
struggling — healthy captures read 0.984–1.009, starved ones 0.104–0.105, and it
returns UNKNOWN rather than a verdict for a capture with no clock. Watch that,
not the frame rate: starving a client halves the present rate and divides the
simulation clock by ten.
