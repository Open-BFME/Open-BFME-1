# BFME1 network admission and client phases

Retail BFME 1.03 admits one logical command frame at a time and spreads its
simulation work across six engine phases. The packet router's 200 ms admission
quantum therefore does **not** describe a five-frame-per-second renderer, nor
does it measure total click-to-action latency.

This audit used the retail executable and the source/ledger at `82bfed56b`.
The installed configuration was separately read from `D:\BFME1` on
2026-09-07. These are static checks, not a multiplayer latency measurement.

## Proven caller chain

| Retail RVA | Evidence |
|---|---|
| `00681F70`, 395 B | `BFMENativeNetwork::getFrameAdvanceCount`: the router accumulates QPC elapsed ticks and subtracts `frequency / 5` for one successful admission. `Network::init` at `00681E40` obtains the frequency directly from QPF. |
| `0006BAE0`, 190 B | Exact `GameEngine::_bfme_updateNetworkAndLogic(int)`. Only phase 1 calls Network vtable `+3C` (`0006BB0E`). It tests the returned integer against zero; it does not loop that many times. A positive result brackets Network `update(1)` with begin/end hooks, then calls GameLogic vtable `+20` once. |
| `0006E910`, 392 B | Exact `GameEngine::update`. Each engine update performs client work and then advances its phase counter. Phases 2 through 6 bypass network admission. On wrapping past 6 it sets phase 1 and attempts admission. If `GameClient+C4` is false, it restores the prior counter above 6, so the next engine update retries phase 1. |
| `0038DA10`, 2129 B | GameLogic phase dispatcher, semantically recovered but not yet byte matched. `0038DB62..0038DB68` saves `phase == 1`; `0038E1BB` tests that flag before the final object work. The only increment of `GameLogic+3C` is `0038E225`, also conditioned on the game's frame-advance flags. |

On 2026-09-07 the focused gates freshly passed all four functions in
`GameEngineFramePacing.cpp` and the one function in `GameEngineUpdate.cpp`.
The native admission function was independently probed at 395/395 bytes.

Consequences:

- A healthy router normally admits five logical command frames per second.
  With six engine phases per logical frame, the installed 30 FPS client limit
  is consistent with six approximately 33 ms client iterations per 200 ms
  logical interval. This is a nominal relationship, not a guarantee about
  actual render output or the duration of each phase.
- A non-router's positive `frameCeiling - currentFrame + 1` is headroom. The
  caller consumes one logical frame at a time, even when the returned allowance
  is larger than one. Complete commands for the current frame are still needed.
- A denied phase 1 does not begin phases 2 through 6. Client servicing runs
  before the admission attempt, and its recovered path calls Network
  `liteupdate(0)`. The machine can therefore continue servicing transport and UI
  while waiting at the logical boundary.
- The router retains leftover QPC time for subsequent admission attempts;
  the native body resets an accumulator exceeding two seconds. This permits
  catch-up across later attempts, not a batch inside the admission caller.

The outer `GameEngine::execute` loop at `0006BBE0` is not fully matched. Its
959-byte bank currently differs in three stack displacements. Raw retail
instructions establish its one `update()` call per iteration and its pacing
formula based on `1000 / (maxFPS * scale)` plus the adjustment value. Router
headroom and peer pacing status affect the scale. The loop also has fast-mode,
frame-skip and pacing bypasses; the installed FPS limit is not an invariant
duration for every iteration.

## Execution-frame assignment is separate from retention slack

The actual gameplay-command path does not assign `currentFrame + runAheadSlack`:

1. `sendGameCommand` at `00666240` builds the command, explicitly sets its
   execution frame to `-1`, assigns the originating player and sends it through
   `sendLocalCommand` with relay mask `FF`.
2. Exact `sendLocalCommand` at `00664740` has a router branch that writes
   `max(GameLogic.frame, 2)` to `NetCommandMsg+8` at `006647A6`. A peer forwards
   its command to the packet router without that stamp. Special direct-send
   commands take a separate branch.
3. Exact `relayCommand` at `00663100` fills an execution frame of `-1` with the
   current GameLogic frame (`00663112..00663121`). It then rejects a command
   if `executionFrame + NetworkRunAheadSlack < currentFrame`
   (`00663124..00663142`). This is a stale-command window, not a delay added to
   the execution frame.

`NetworkRunAheadSlack` also sizes retained peer-CRC history (slack plus three
frames). The similarly named Connection `frameGrouping` field is an egress
interval used with millisecond timestamps; it is a different quantity again.
Neither name justifies adding its value to the command's scheduling horizon.
The evidence above does not quantify total input latency: capture time, router
arrival, phase boundaries, relaying and completeness checks all matter.

## Configuration actually read for this audit

Commands:

```
python tools/ini_value.py --game-dir D:/BFME1 FramesPerSecondLimit UseFPSLimit
python tools/ini_value.py --game-dir D:/BFME1 --all-network
```

The tool read `ini.big`, then `_patch222.big`. Every value below came from
`ini.big`; the overlay did not replace these keys. This identifies this local
installation's values, not every BFME installation or RotWK 2.02.

The retail initialization link is explicit: `GameEngine::init` loads
`TheGlobalData+24` at `0007A387` and passes it to its virtual FPS setter at
slot `+2C` (`0007A38F`). The loop's pacing formula then reads `GameEngine+8`.

| Key | Loaded value |
|---|---:|
| FramesPerSecondLimit | 30 |
| UseFPSLimit | Yes |
| NetworkFPSHistoryLength | 30 |
| NetworkLatencyHistoryLength | 200 |
| NetworkRunAheadMetricsTime | 5000 |
| NetworkCushionHistoryLength | 10 |
| NetworkRunAheadSlack | 10 |
| NetworkKeepAliveDelay | 20 |
| NetworkDisconnectTime | 15000 |
| NetworkPlayerTimeoutTime | 60000 |
| NetworkDisconnectScreenNotifyTime | 15000 |

The numeric history, slack and timeout values above retain their INI spelling;
their units must come from the relevant consumers rather than the key names.
