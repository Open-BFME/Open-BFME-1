# 039-replayctl — pause a replay with ctrl+period

Press **ctrl+period** while watching a replay to freeze the simulation; press it
again to resume. The camera keeps working while paused, and so does the rest of
the client — only the logic tick stops.

Replay-only: the hook returns immediately unless `TheGameLogic`'s mode is
`GAME_REPLAY`, so it cannot affect a match, a skirmish or the shell. It also
clears its own bit on leaving a replay, so a pause cannot leak into the next
game.

## How it works

One detour, RVA `0x0006B910` — the body behind GameEngine vtable slot 32, the
**client** half of the engine frame. That target is load-bearing: it runs on
every engine iteration including the ones where the logic tick is skipped. A
hook on the logic side would stop being called the moment it paused the logic
and could never see the key that unpauses it.

The pause itself is bit 1 of `GameLogic+0x11C`. `updateNetworkAndLogic` reads it
and skips the logic tick; `TheNetwork` is NULL in a replay so nothing overrides
that; and `RecorderClass::updatePlayback` keys off the logic frame, so the
recorded command stream stalls *with* the frame counter rather than running
ahead of it.

Do **not** switch this to `GameLogic::setGamePaused` (`0x00783490`). It writes
the same byte and then disables input and forces the arrow cursor — the opposite
of what a replay wants.

That setter takes **three** arguments in BFME — `(Bool paused, Int mode, Bool
affectMouse)`, the middle one a dword tested against 1 and 2 — not Zero Hour's
`(Bool paused, Bool pauseMusic)`. The 300-byte retail body is byte-verified in
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/BfmeGameLogicPause_setGamePaused.cpp`,
where the class is spelled `BfmeGameLogicPause` as a TU-local call view. The
two-argument `GameLogic::setGamePaused` in `GameLogic.cpp` is Zero Hour's and
is not what retail runs.

Bit 1 rather than the value 1: all 28 `isGamePaused` call sites do `test al,al`
and none compares against 1, so any non-zero reads as paused and a bit stays
composable with another writer. Two known limits, both acceptable here:
`setGamePaused` does a whole-byte store, so an engine-initiated pause (quit
menu, popup) clears the bit; and `GameLogic+0x11D` is a separate live flag, so
this is a byte-width write, never a word.

## Verified

Retail 1.03 (patch 2.22), `LastReplay.rep` on Nanduhirion. Screenshots 8s apart:

| State | Screen change |
|---|---|
| playing | 5437 px |
| paused | **0 px** |
| resumed | 3603 px |

Earlier, instrumented: the logic frame held at 937 for 3,176 consecutive client
iterations while `Recorder+0x2B0` froze with it, camera panning throughout.

It is frame-exact by construction, not by luck. Only the gated phase-1 step
advances `m_frame` — phases 2..6 interpolate and leave it alone — so however
many ungated sub-steps run between setting the bit and the gate, the logic frame
cannot move. Confirmed with the bit set mid-cycle (`GameEngine+0x30 == 4`), the
case that *does* leak sub-steps: the frame still did not advance.

## Step-back does not work — do not retry it blind

A 30-second step-back was the other half of the original request. Eight
instrumented runs say the engine's save/load path will not restore state into a
running game. Two walls, from opposite directions:

| Route | Dies at |
|---|---|
| live world, logic-only set (8 blocks) | `CHUNK_Players`, inside a Player's own xfer |
| reset + full set (25) + `clearScratchPadMaps` | `CHUNK_GameStateMap` |

**Already eliminated — do not spend runs on these again:**

1. loading over a live world (tested with a reset first — still throws)
2. a malformed save (the 9 MB artifact was read directly: `ALAE2STR`, version 1,
   all 25 blocks in registration order, `SG_EOF` terminator — well formed)
3. missing SaveGameInfo setup (`TheGameState+0x40`/`+0x44` set as `saveGame` does)
4. the map block being the sole obstacle (removing it moves the wall to `CHUNK_Players`)
5. a player-count mismatch (measured: 12 in the file, 12 live)
6. missing `clearScratchPadMaps`

The one route that looked promising and probably is not: stripping
`CHUNK_GameStateMap` from the file so the loader skips it (an unknown token calls
`SkipBadBlock`, it does not throw). After a reset there are no players, so the
live count is 0 against the file's 12, and `PlayerList::xfer` throws on exactly
that. It likely just moves the wall from block 6 to block 9.

`PlayerList::xfer` is `0x004DF740`: `xferVersion`, then count, then
`if (loaded != live) throw`, then `xferSnapshot` per player. That validation is
the lifecycle showing through — the path rebuilds a world from scratch after a
reset, and pushing state into a live one fights it.

Anything genuinely new needs a different state-capture mechanism, not this one.

## Useful facts banked along the way

* `xferSaveData`'s load branch does **not** throw on an unknown block token — it
  calls `SkipBadBlock` and continues. Selectively dropping blocks from a save is
  therefore viable.
* The xfer walk costs ~30 ms; writing it to disk costs ~4-6 s. The cost is
  ~99.4% file I/O, and identical whether it walks 8 blocks or 25. Any future
  snapshot work wants a memory buffer from the start.
* A snapshot is ~9.0 MB (25 blocks) or ~6.5 MB (8) — trimming blocks saves only
  27%; the logic state dominates.
* Every millisecond figure above is an **upper bound**: this box carried a load
  average of ~15 on 16 cores from unrelated VMs throughout. Sizes, frame counts
  and pixel diffs are unaffected.
