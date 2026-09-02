# Measuring BFME: the rigs, and the traps that cost real time

Two kinds of measurement live here — game-end fixtures (`reverse/game_end/`)
and network latency (`030-netlatprobe`). They share a machine and most of the
traps, so they share a document.

## Tests that need nothing but a checkout

```bash
python3 -m pytest tools/tests/test_cave.py tools/tests/test_mods_build.py \
                 tools/tests/test_game_records.py
```

`test_cave` needs the committed baseline exe and `capstone`; `test_mods_build`
also builds the feature, so it needs wine and the MSVC 7.1 toolchain. Both
disassemble what the build actually produced. `test_game_records` holds every
row in `reverse/game_end/measured.jsonl` against the prediction
`tools/tests/rows.py` declared before it ran. None launch the game.

## The rig, if you are rebuilding one

The rig is **not in this repo** — it hardcodes a wine layout, a Windows
username and prebuilt prefixes, so it runs on one machine and would be dead
weight in a clone. It lives at `dginovker/bfme-lan-rig`.

* Retail BFME 1.03 under wine, and **one prefix per client with a distinct CD
  key** — never `cp -a` a prefix, the serial at `…\ergc` comes with it.
* **One network stack per client.** See below; this is not a quirk.
* **A hostname per namespace resolving to its own address**, and
  `nsswitch.conf` forced to `hosts: files`; otherwise systemd-resolved answers
  `::1`, the mesh never forms, and the broadcast lobby hides it.
* **A window manager.** On bare Xvfb every synthetic click is silently dropped
  — DirectInput never acquires without something foreground. A wine virtual
  desktop is enough.
* **GPU rendering.** llvmpipe costs ~200% CPU per client and four of them drop
  each other's heartbeats.
* **Clean up between runs.** Leftover wine service processes outlive a client,
  and the next launch attaches to a wineserver in the dead namespace and dies
  on window creation — which surfaces as a seating failure nowhere near its
  cause. `kill-mine.sh <displays> <prefixes>`.

## Why one network stack per client

**BFME keys a LAN participant on an address pair — four-byte IP then two-byte
port, and it compares both halves.** The reference engine this derives from
compares a bare `m_localIP` with no port at all.

`LANAPI::RequestGameOptions` is the clearest place to see it, walking the slot
array looking for itself:

```c
for (player = 0; player < 8; ++player)
    if (slot->m_ip == me->m_ip && slot->m_port == me->m_port)
```

`me` is whatever vtable slot 55 (+0xDC) returns, not a stored local IP. The slot
array starts at `LANGameInfo+0x88`, each record 0x68 bytes with the address pair
at its start, stopping at +0x340 — eight slots. `LANAPI::RequestSetName` shows
the same pair at `LANPlayer+0x14`; the callbacks carrying it are `OnGameOptions`
(+0x98), `OnNameChange` (+0xA4) and `LookupPlayer` (+0xD8).

So **two clients sharing an address are one participant to BFME.** Every client
gets the same lobby port, so the IP is the only half separating them: without a
veth per client, announcements all attribute to whichever slot matched first and
the rest age out as "player was not responding". Debugging a mesh that will not
form, check addresses before anything else.

Every offset above is read from a body that reproduces retail byte for byte.

## Message-type numbers are not the reference's

BFME's `LANMessage` enum carries two more types ahead of `MSG_INACTIVE` than the
Zero Hour source, so the type byte on the wire is **0x10** where a build from the
reference enum computes 0xE. Read from `LANAPI::setIsActive` (`0x00685320`),
which stores the constant directly.

The enum is positional, so *every* type after the two additions is renumbered by
two. Clients built from the two enums would misread each later type as its
neighbour. Debugging a mesh where clients connect and then talk past each other,
compare wire type numbers against this before suspecting payloads. The two extra
types are unidentified — only that there are exactly two and they precede
`MSG_INACTIVE`, which is what 0x10 pins. `LANAPI::m_isActive` is at +0x58.

## The latency probe

`030-netlatprobe` instruments the wire; `tools/netlat.py` reads it. UNSHIPPED —
it writes tens of lines a second and `--dist` refuses it.

```bash
python3 tools/modbuild.py --only 020-gameresult --only 030-netlatprobe -o build/mods/probe.exe
python3 tools/netlat.py --preflight run1/*.jsonl
```

Each client appends JSONL to `%APPDATA%\My Battle for Middle-earth
Files\NetLat.jsonl` (or `BFME_LAT_PATH`). All seats share the host's
QueryPerformanceCounter, so timestamps compare across prefixes with no
synchronisation.

| RVA | Function | Emits |
|---|---|---|
| `0x0008A4E0` | `GameMessageList::appendMessage` | a command entering a list |
| `0x00664740` | `ConnectionManager::sendLocalCommand` | it leaving the machine |
| `0x00663100` | `ConnectionManager::relayCommand` | the router binding it to a frame |
| `0x00682A90` | `Network::relayCommandsToCommandList` | the per-logic-frame heartbeat |
| `0x00665D10` | `ConnectionManager::sendFrameInfo` | the ceiling being published |
| `0x006620A4` | `Connection::update`, the discard decision | the engine's own margin to the cliff |

All hooked at entry, which is what lets the shim lift the target's own first
argument (`cave.py`'s `args=("ecx","stack:0")`).

## The frame probe

`036-fpsprobe` hashes the backbuffer and `tools/fpsmeter.py` reads it. UNSHIPPED
— it reads pixels back off the GPU. Hook address, cell grid, burst schedule and
the two calibration controls: `mods/features/036-fpsprobe/README.md`. What it
then measured: `docs/fps60.md`. Three traps from it generalise:

**The present rate is not the measurement.** A build that presents twice as
often while repeating every second frame doubles it and changes nothing a
player sees. The metric is *new images per second* — `(1 - duplicate rate) x
present rate`, per cell — which only a change that puts more DIFFERENT images
on the screen can move.

**Animation speed is invisible to every pixel metric.** A torch flickering
twice as fast still changes on the same fraction of presented frames, so cell
hashes, duplicate rates and new-images rates are all blind to it. It needs its
own clock — the probe reads `WW3D::SyncTime` and slopes it against the wall
clock. `docs/fps60.md` for what that clock turned out to be driven by.

**The network frame rate is not the game-speed gate.** It is paced by the
network at 5 Hz whatever the loop does, so a build whose simulation advances
the world twice as far per network frame reads a reassuring 5.000/s. Use the
walk (`--walk`), or read the resource counter off the phase screenshots: gold
accrues per simulation step, so at matched elapsed times it is a direct measure
of game speed that no frame-rate change can fake.

## Metrics that survived

* **held** — creation → the command leaving. Bounded by one quantum for retail,
  ~0 for a send-side fix. The most reliable quantity here: one seat's clock, no
  cross-machine comparison, no baseline subtraction.
* **creation→run** — the player-facing latency. Never anchor at *send*: that
  starts the clock where a send-side fix acts and credits retail with a free
  ~90 ms.
* **frame gaps** — freeze count and length, independent of command class.
* **excess time** and **net game time lost** — threshold-free; a freeze cutoff
  inside the spread of the arms' own freeze lengths manufactures the ratio.
* **discard margin** — `exec + slack - now` at the decision point. Per-event, so
  one match gives hundreds of samples rather than one number.

## Traps, all of which cost real time here

* **The instrument must be identical across arms**, and "same build" is not
  enough — a hook whose fire rate depends on the feature (the admit hook) writes
  6× the I/O in one arm and heats what it measures.
* **Selection commands (1001/1003) are not simulation state.** A rig clicking a
  citadel measures a class that cannot desync. Build orders are type **1048**;
  the rig must place a Gondor farm to generate one.
* **Retail's p50 varies 843→1534 ms between identical runs.** Its *tail* is
  stable (p90 within 78 ms). Compare at p90, not p50.
* **Read the value the process loaded, not the binary's default.** Six of nine
  `Network*` fields differ, the largest by 120×. `tools/ini_value.py`.
* **Anchor a metric to the thing the change moves**, not to a reference frame
  the change is defined against. A phase-within-frame statistic is degenerate at
  the frame boundary and reported an 84% effect as 9%.
* **Pinning a single-threaded game to one core is not a throttle.** BFME's main
  loop is one thread, so one core is all it ever wanted: `taskset -a -pc 0` on
  a client moved its present rate 30.3 -> 30.6 Hz and left its spare frame
  budget unmoved at 25 ms. A weak machine has to be modelled by CONTENDING for
  the core -- busy loops pinned to the same one, so the client gets
  1/(N+1) of it. The pin alone is a gate that cannot fail, which is worse than
  no gate, because it reads as "the build absorbs it".
* **A consistency check against a broken input reproduces the break.** Two
  parties then hold the same wrong number with more confidence than either
  started with. At least one check must return to the raw quantity.

## Closed avenues

The guest's one-frame lag is the protocol's correctness margin, not slack:
`getFrameAdvanceCount` is a boolean to its caller, `areFrameCommandsComplete`
compares a snapshot so extra polls desync (`034-framedrain`, frame 102), and the
wait is exactly one quantum with no phase component. BFME has no run-ahead to
shorten. The router's relay blackout is real but worth ~20 ms.

**An extra draw in the frame limiter has nothing new to draw.**
`GameEngine::update` runs a six-step cycle per 5 Hz network frame and renders at
`FramesPerSecondLimit` — 38 from `_patch222.big`, not the compiled 30 — so
retail already draws more often than the world changes, and ~22% of a host's
frames are repeats before anything is modded. Raising `FramesPerSecondLimit`
alone changes game speed, because with no network to pace it the cycle turns
over at the loop rate.

Those six steps ARE simulation sub-steps, settled by `037-fps60`'s defect:
doubling the count doubled the speed of content authored in frames, which a
client-side interpolation pass could not do. Raising the count is therefore
closed -- `Lifetime` appears 2,735 times across 724 ini files and every one of
them is denominated in those steps. `docs/fps60.md` has the numbers.

## Adding a game-end row

Declare it in `tools/tests/rows.py` **before** running it — shape, each seat's
exit mode and order, the records that seat should hold, the expected winning
team. That is what makes a fixture a measurement rather than a transcription.

Then play it, append its records to `reverse/game_end/measured.jsonl` with `row`
and `seat` prepended, and run the tests. A row whose measurement contradicts its
declaration is a finding about the engine — correct the declaration in a commit
saying why the original model was wrong, never to make a test pass.

`reverse/game_end/measured.md` lists what the existing rows established.
