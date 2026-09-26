# Network fixes — worst freeze 3.7 s → 0.8 s

Two patches, both present in `mods/dist`. The executable hash and the early-send
detour / 400 ms retry operand were checked again on 2026-09-07. Performance
numbers below are the earlier recorded experiments, not a new multiplayer run.
See [the lockstep guide](multiplayer-lockstep.md) for the reconstructed protocol.

Measured on two clients over `netem`
at 150 ms round trip and 3% loss per direction — a bad-but-real ladder link.

## `033-retrytime` — frame-gap p99: 1769 ms → 420 ms

Four bytes. The headline row across three matches per arm:

| | retail | fixed |
|---|---|---|
| frame-gap p99 | 1740 / 1769 / 1800 ms | **420 / 419 / 420** |
| worst stall | 2031 / 3724 / 3719 ms | **805 / 806 / 800** |
| game time lost | 3.2 / 11.0 / 7.7% | **~0%** |
| host stalls per minute | 49.98 | **0.23** |

**How.** The constructor sets the resend interval to 2000 ms. In the
installation used for these measurements, `NetworkRunAheadSlack` was 10 logic
frames: nominally 2000 ms at 5 Hz. `Connection::doSend` retries eligible
commands and then removes stamped commands whose execution frame is older than
the configured window. Unstamped guest commands have frame `-1` and bypass
that age test. Thus the number of retries is not universally one; it depends
on acknowledgements, command age and simulation progress. A 400 ms timer gives
more retry opportunities before stamped commands age out.

Frame-history replay also exists. Type 9 requests and disconnect-frame
synchronization can resend retained command payloads plus their frame counts.
The type 9 emitter is part of router-departure recovery, not a generic missing-
command poll in the ordinary readiness gate. Sender retries remain essential
for a guest command lost before the router receives and assigns it a frame.

The store is `mov dword ptr [edx+0x1C], 2000` in **`Connection::Connection`,
RVA `0x006623A0`** — `m_retryTime` at `this+0x1C`; the imm32 sits three bytes into
the instruction, at `0x006623DE`, which is what `tools/modbuild.py` pokes. No code
cave, no detour.

Earlier revisions of this page and of `mods/features/033-retrytime/README.md`
called the owner `Connection::init`, borrowing the name from Zero Hour. The timer store belongs to the BFME constructor,
which takes no arguments, calls nothing and returns `this`. A separate BFME
peer-configuration routine at `0x00661E00` takes address, name and transport
arguments; it should not be conflated with the timer constructor. The body is real C++
at `game/GameEngine/Source/GameNetwork/Connection.cpp`; until it was converted the
repo served it only as the byte dump `?d_006623a0@@YAXXZ`, which is why grepping
for either name used to come up empty.

Across these three tested matches, the fixed build's worst recorded stall was
800-806 ms, while retail varied from 2031 to 3724 ms. That is evidence of lower
variation under the tested conditions, not a universal 800 ms maximum.

## `031-earlysend` — off-host send delay: 92 ms → 0 ms

~106 bytes in a code cave. Ships **with** `033`, never alone.

**How.** Logical frame admission runs at 5 Hz, with work divided among six
engine phases. Retail drains the outbound
command list only from `Network::update`, on a logic tick, so a guest's command
waits up to a 200 ms quantum before it even leaves the machine. The host avoids this extra outbound guest hold — it stamps and executes inside the same tick. A detour at
`0x0006BA44` drains the list from the client half, which runs ~30 Hz, so a
command leaves on the tick it was created.

In the recorded captures, the local hold reads 87–96 ms in
every retail capture and **0.1 ms in every fixed one**, including all 11 real
build orders measured.

**It is invisible on a bad link**, which is why it ships paired. Against retail
at 150 ms/3% its ranges overlap — the ~2000 ms freeze floor swamps 92 ms. Its
benefit shows on a good link (−152 ms clean LAN) and against a baseline whose
freezes are already fixed (−100 ms p50, disjoint at n=2).

## Together, on a real order

A Gondor farm placement, click to construction starting, same condition:

**0.7–2.6 s unpredictable → 0.43–0.65 s consistent.** The fixed build's worst
placement beats retail's best.

## Why it is this constant, not a correlation

Every duplicate arrival on the wire is a retransmission, so the gap between the
original and the duplicate *is* the timer. Across nine matches at three values:

| timer | measured gap, median |
|---|---|
| 2000 ms | 1991, 2019, 2030, 2034 |
| 800 ms | 842 |
| 400 ms | 416, 417, 381, 446 |

Outliers land on exact multiples (3996 = 2×2000). Hundreds of individual
retransmissions rather than ten events a match.

## Safety

* **Duplicates already occur in retail** at the same rate — 1.19% stock,
  0.45–2.20% fixed. Not a condition the fix introduces.
* They are rejected by identity: `FrameData::addCommand` looks a command up
  before inserting, comparing player and command id.
* The engine's own desync flag stayed zero in every match, at 150 ms, 300 ms and
  500 ms round trip — 5,423 frame events across the eight 500 ms captures.
* Every player in a lobby must run the same build, which the launcher's MD5
  check already enforces.

## Not claimed

* **Tested to 500 ms round trip** (2026-08-30, two matches per arm). Above
  ~400 ms the timer does fire before an ack can return, and the retransmission
  counter shows it — `Connection::numRetries` median 1 → 38. It is extra traffic;
  no checksum divergence was observed in these captures. The early retry is
  what holds discarded commands to 0.07% against retail's 3.61% at that RTT.
  Guest frame-gap p99 is 420 ms at 500 ms RTT — the same 420 ms as at 150 ms,
  because the freeze floor is the retry interval and not the link. Above 500 ms
  is still unmeasured. See `mods/features/035-adaptretry/README.md`.
* The engine can discard a command outright, and the fix largely removes that:
  retail crosses the guard on 2.52% of router game commands, and at 150 ms the
  fix never comes within five frames. **That margin is RTT-dependent and the
  "never" does not survive 500 ms**: there the fix still crosses, twice in four
  matches, worst margin −2 frames — against retail's −10 on every capture, and
  0.07% of decisions against 3.61%. In the 150 ms work **every discard observed
  was of a command the peer had already received**, so this prevents a
  precondition, not an observed disconnect — that cross-seat check was NOT
  repeated on the 500 ms captures, so it is not claimed for them.
* Two-player rig. Eight-player behaviour is modelled, not measured — the
  ladder's own drop-rate data would settle it.

---

Evidence, corrections and the measurement traps behind all of this:
`targets/game/reverse/network_delay/FINDINGS.md`. Instrument: `docs/measuring.md`.
