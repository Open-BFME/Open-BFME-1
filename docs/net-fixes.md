# Network fixes — worst freeze 3.7 s → 0.8 s

Two patches, both shipped in `mods/dist`. Measured on two clients over `netem`
at 150 ms round trip and 3% loss per direction — a bad-but-real ladder link.

## `033-retrytime` — frame-gap p99: 1769 ms → 420 ms

Four bytes. The headline row across three matches per arm:

| | retail | fixed |
|---|---|---|
| frame-gap p99 | 1740 / 1769 / 1800 ms | **420 / 419 / 420** |
| worst stall | 2031 / 3724 / 3719 ms | **805 / 806 / 800** |
| game time lost | 3.2 / 11.0 / 7.7% | **~0%** |
| host stalls per minute | 49.98 | **0.23** |

**How.** BFME retransmits a lost command **once**, and that retry fires at the
exact moment the command becomes eligible to be discarded — the retry interval
and the abandonment horizon are both 2000 ms (`m_retryTime` = 2000;
`NetworkRunAheadSlack` = 10 frames × 200 ms). There is no receiver-side resend
request in the engine, so the sender's timer is the only recovery that exists.
Setting the timer to 400 ms gives five attempts inside the same horizon instead
of one. The store is `mov dword ptr [edx+0x1C], 2000` in **`Connection::Connection`,
RVA `0x006623A0`** — `m_retryTime` at `this+0x1C`; the imm32 sits three bytes into
the instruction, at `0x006623DE`, which is what `tools/modbuild.py` pokes. No code
cave, no detour.

Earlier revisions of this page and of `mods/features/033-retrytime/README.md`
called the owner `Connection::init`, borrowing the name from Zero Hour. BFME has
no `Connection::init`: it folds what ZH does in `init()` into the constructor,
which takes no arguments, calls nothing and returns `this`. The body is real C++
at `Code/GameEngine/Source/GameNetwork/Connection.cpp`; until it was converted the
repo served it only as the byte dump `?d_006623a0@@YAXXZ`, which is why grepping
for either name used to come up empty.

**Also: it makes the numbers predictable.** Retail's worst stall varies 83%
between identical runs; the fix varies 0.1% (805 vs 806). For competitive play
that is the stronger claim — *"your worst stall is 800 ms, every game"* is a
different product from *"somewhere between 2 and 3.7 seconds, depending on
luck."*

## `031-earlysend` — off-host send delay: 92 ms → 0 ms

~106 bytes in a code cave. Ships **with** `033`, never alone.

**How.** All game logic runs at a compiled-in 5 Hz. Retail drains the outbound
command list only from `Network::update`, on a logic tick, so a guest's command
waits up to a 200 ms quantum before it even leaves the machine. The host pays
nothing — it stamps and executes inside the same tick. A detour at
`0x0006BA44` drains the list from the client half, which runs ~30 Hz, so a
command leaves on the tick it was created.

The removal is deterministic, not an average: the local hold reads 87–96 ms in
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
  counter shows it — `Connection::numRetries` median 1 → 38. It is extra traffic
  and it is not a correctness problem: desync stayed 0, and the early retry is
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
`reverse/network_delay/FINDINGS.md`. Instrument: `docs/measuring.md`.
