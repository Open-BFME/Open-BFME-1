# Measuring the guest's input lag

`mods/features/030-netlatprobe` instruments the wire; `tools/netlat.py` reads it.
The probe is UNSHIPPED — it writes tens of lines a second and `--dist` refuses it.

```bash
python3 tools/modbuild.py --only 020-gameresult --only 030-netlatprobe -o build/mods/probe.exe
python3 tools/netlat.py --preflight run1/*.jsonl
```

Each client appends JSONL to `%APPDATA%\My Battle for Middle-earth Files\NetLat.jsonl`
(or `BFME_LAT_PATH`). All seats share the host's QueryPerformanceCounter, so
timestamps compare across wine prefixes with no synchronisation.

## The hooks

| RVA | Function | Emits |
|---|---|---|
| `0x0008A4E0` | `GameMessageList::appendMessage` | a command entering a list |
| `0x00664740` | `ConnectionManager::sendLocalCommand` | it leaving the machine |
| `0x00663100` | `ConnectionManager::relayCommand` | the router binding it to a frame |
| `0x00682A90` | `Network::relayCommandsToCommandList` | the per-logic-frame heartbeat |
| `0x00665D10` | `ConnectionManager::sendFrameInfo` | the ceiling being published |

All hooked at entry, which is what lets the shim lift the target's own first
argument (`cave.py`'s `args=("ecx","stack:0")`).

## Metrics that survived

* **held** — creation → the command leaving. Bounded by one quantum for retail,
  ~0 for a send-side fix. The most reliable quantity here: within one seat's
  clock, no cross-machine comparison, no baseline subtraction.
* **creation→run** — the player-facing latency. Never anchor this at *send*: that
  starts the clock where a send-side fix acts and credits retail with a free
  ~90 ms.
* **frame gaps** — freeze count and length, independent of command class.
* **excess time** and **net game time lost** — threshold-free; a freeze cutoff
  inside the spread of the arms' own freeze lengths manufactures the ratio.

## Traps, all of which cost real time here

* **The instrument must be identical across arms**, and "same build" is not
  enough — a hook whose fire rate depends on the feature (the admit hook) writes
  6× the I/O in one arm and heats what it measures.
* **Selection commands (1001/1003) are not simulation state.** A rig that clicks
  a citadel measures a command class that cannot desync. Build orders are type
  **1048**; the rig needs to place a Gondor farm to generate one.
* **Retail's p50 varies 843→1534 ms between identical runs.** Its *tail* is
  stable (p90 within 78 ms). Compare at p90, not p50.
* **Read the value the process loaded, not the binary's default.**
  `NetworkDisconnectTime` is 15000 at runtime, not 5000;
  `NetworkRunAheadSlack` is 10, confirmed live.

## Closed avenues

The guest's one-frame lag is the protocol's correctness margin, not slack:
`getFrameAdvanceCount` is a boolean to its caller, `areFrameCommandsComplete`
compares a snapshot so extra polls desync (`034-framedrain`, frame 102), and the
wait is exactly one quantum with no phase component (1.2 ms spread over three
matches). BFME has no run-ahead to shorten. The router's relay blackout is real
but worth only ~20 ms. Do not raise `FramesPerSecondLimit` — it changes game
speed.
