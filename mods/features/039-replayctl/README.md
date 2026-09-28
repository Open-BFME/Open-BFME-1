# 039-replayctl: pause a replay with ctrl+period

Press **ctrl+period** while watching a replay to freeze the simulation; press it
again to resume. The camera and the rest of the client keep working while
paused; only the logic tick stops. It is in the repository bundle, `mods/dist`.

Replay-only: the hook returns immediately unless `TheGameLogic`'s mode is
`GAME_REPLAY`, so it cannot affect a match, a skirmish or the shell. It also
clears its own bit on leaving a replay, so a pause cannot leak into the next
game.

## How it works

One detour at RVA `0x0006B910`, the body behind GameEngine vtable slot 32: the
**client** half of the engine frame. It runs on every engine iteration,
including those where the logic tick is skipped. A hook on the logic side would
stop being called once it paused the logic, and could never see the key that
unpauses it.

The pause is bit 1 of `GameLogic+0x11C`. `updateNetworkAndLogic` reads it and
skips the logic tick; `TheNetwork` is NULL in a replay, so nothing overrides
that; and `RecorderClass::updatePlayback` keys off the logic frame, so the
recorded command stream stalls with the frame counter. The pause is frame-exact
by construction: only the gated phase-1 step advances `m_frame`.

`GameLogic::setGamePaused` (`0x00783490`) is deliberately not used. It writes
the same byte, then disables input and forces the arrow cursor, the opposite of
what a replay wants. In BFME it takes three arguments,
`(Bool paused, Int mode, Bool affectMouse)`, not Zero Hour's two.

## Build

`python3 tools/modbuild.py --dist` builds the bundle into `mods/dist/`.

## Verified

Retail 1.03 (patch 2.22), `LastReplay.rep` on Nanduhirion, screenshots 8 s
apart:

| State | Screen change |
|---|---|
| playing | 5437 px |
| paused | **0 px** |
| resumed | 3603 px |

Instrumented, the logic frame held at 937 for 3,176 consecutive client
iterations while the camera panned. With the bit set mid-cycle, the case that
does leak sub-steps, the frame still did not advance.

## Limits

* An engine-initiated pause (quit menu, popup) clears the bit, because
  `setGamePaused` stores the whole byte.
* There is no step-back. In eight instrumented runs the engine's save/load path
  would not restore state into a running game, so stepping back needs a
  different state-capture mechanism.
