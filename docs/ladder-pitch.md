# BFME 1: a two-byte fix for the two-second freezes

**For the BFME Arena admin.** The long version, with every measurement and every
correction we made along the way, is `docs/net-freeze-fix.md`. This is the case.

## The problem

On any connection that drops packets, BFME stops for about two seconds at a
time. Not one player — **everyone**. The game is lockstep, so nobody advances
until the missing command arrives.

The cause is one 32-bit constant. `Connection::init` sets the retransmit timer to
2000 ms, so a lost command waits two full seconds before it is sent again. That
wait *is* the freeze.

## The fix

Change that constant to 400. **Two bytes**, at file offset `0x006623DE`. No code
added, no protocol change, no new behaviour — a number that was already there,
set to a different value.

## What it does

Measured on two machines playing a real match on separate network stacks, with
150 ms round trip and 3% packet loss each way — a bad-but-real ladder link.

**A player placing a building, timed from click to construction starting:**

| | click → build starts |
|---|---|
| stock | **2192 ms** |
| fixed | **584 ms** |

The fixed build's *worst* placement (651 ms) is faster than stock's *best*
(731 ms). Ranges do not overlap.

**And the freezes stop being a lottery.** This matters more than the median for
competitive play:

| | stock | fixed |
|---|---|---|
| worst stall in a match | 2031 – **3724 ms** | **805 / 806 ms** |
| longest frame gap (p99) | 1740 – 1769 ms | 420 / 419 ms |
| game time lost | 3.2 – 11.0% | **0.0%** |

Two runs of the *same* stock build on the *same* rig gave worst stalls of 2031
and 3724 ms — an 83% swing. The fixed build gave 805 and 806. *"Your worst stall
is 800 ms, every game"* is a different product from *"somewhere between 2 and 3.7
seconds, depending on luck."*

**It costs nothing.** Traffic is unchanged (measured). It needs no protocol
change and no server-side work.

## Why we are confident it is this constant

Not a correlation. Every duplicate arrival on the wire is a retransmission, so
the gap between the original and the duplicate *is* the timer. Across nine
matches at three different values of the constant:

| timer set to | measured gap, median |
|---|---|
| 2000 ms | 1991, 2019, 2030, 2034 |
| 800 ms | 842 |
| 400 ms | 416, 417, 381, 446 |

Every median within ~6% of the value we set. Hundreds of individual
retransmissions, not a per-match average.

## Safety

The concern with a faster timer is a command arriving twice, because in lockstep
that would desync. It does not happen:

* **Duplicates already occur in stock BFME** at the same rate — 1.19% on stock,
  0.45–2.20% on the fixed build. This is a condition the engine meets routinely,
  not one the fix introduces.
* **They are rejected by identity.** `FrameData::addCommand` looks a command up
  before inserting it, comparing player and command id. Every duplicate observed
  across both test campaigns was absorbed.
* **The engine's own desync flag stayed at zero** in every match, at 150 ms and
  at 300 ms round trip.
* Every player in a lobby must run the same build — which the launcher's MD5
  check already guarantees.

## What we are not claiming

* Tested at up to 300 ms round trip. Above ~400 ms the timer would start firing
  before an acknowledgement could return; that is extra traffic rather than a
  correctness problem, but it is unmeasured.
* The engine can also discard a command outright. We measured that branch
  directly: stock crosses it, the fixed build never comes within five frames of
  it. But every discard we caught was of a command the other player had *already
  received*, so we are not claiming this fix prevents disconnects — only that it
  removes the precondition.
* Results are from a two-player rig. Eight-player behaviour is modelled, not
  measured.

## What would help most

**Your disconnect and drop rate**, bucketed by player count, match length and
map. We can predict how it should scale; we cannot measure it at ladder scale on
two machines. It needs no new build and no cooperation beyond a query.

## Also available, unrelated to this

Client builds already write a `desync` flag into every match record. **A desynced
match has no single winner** — the seats are simulating different games, so each
reports its own result, and whichever record you happen to ingest decides the
match. Stock BFME detects this and tells nobody. `desync != 0` on any seat means
that match should not be rated. It costs nothing to check and needs no network
change.
