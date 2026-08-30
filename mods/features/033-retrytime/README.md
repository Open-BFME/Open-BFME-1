# 033-retrytime — frame-gap p99: 1769 ms → 420 ms

`Connection::init` sets `m_retryTime = 2000`. Rewritten to `RETRY_MS` (400) at
RVA `0x006623DE`. No cave, no detour — one imm32.

**SHIPPED** in `mods/dist` as of 2026-08-29. See `docs/net-fixes.md` for
results; this file records the mechanism and the limits.

## Why 2000 is the wrong number

The abandonment horizon is `NetworkRunAheadSlack` frames — 10 at runtime
(confirmed live, not assumed), which at 5 Hz is exactly 2000 ms. The retry
interval is also 2000 ms. So a lost command's single retransmission fires at the
instant it becomes eligible to be discarded: one attempt, no margin.

`Connection::doSend` order verified: `mov [esi+0x10],edx` (timeLastSent) at
`0x00A6208E` precedes the horizon test at `0x00A620A4`. Resend, then discard.

## Why nothing else recovers a lost command

BFME diverges from Zero Hour here, and it matters:

* `areFrameCommandsComplete` (`0x006633E0`) is a plain `Bool` equality. ZH returns
  a tri-state with `FRAMEDATA_RESEND`.
* `resendFrameRangeToPlayer` exists with **no callers** — the responder half of a
  protocol whose requester was never wired.
* Type 9 (`REQUESTFRAMEDATA`) is constructed only on the receive path and on
  player-leave.

So a missing command blocks its frame forever, and the symptom would be a
**stuck seat and a drop**, not a CRC mismatch — a desync gate cannot see this.

**But that is the consequence of losing a command, not of every discard.** See
below: every discard actually observed was of a command the peer already had.

## Duplicate delivery is safe, measured and traced

`FrameData::addCommand` matches by **identity** — player (`+0x0C`) and a 16-bit
command id (`+0x10`), compared between two distinct objects, so a retransmit at a
fresh allocation matches its original. Duplicates occur at 1.0–2.5% in **every**
arm including retail. The proof they are absorbed is structural: the readiness
test uses `==` with no recovery path, so one tolerated duplicate wedges a seat
permanently. No match wedged in 29.

Caveat: the id is 16 bits and wraps after ~3 hours of play. A wrap drops a
legitimate command rather than executing a duplicate — it fails safe.

## The constant is proven to cause the behaviour

Duplicate-arrival gaps track the poked value, per event, across nine matches:
2000 → 1991/2019/2030/2034 ms; 400 → 416/417/381/446; 800 → 842. Outliers at
exact multiples (3996 = 2×2000). This is prediction, not fit — 800 was never
used to derive it.

## Upper bound

The timer must exceed the round trip or it retransmits before an ack can arrive.
400 ms works at 300 ms RTT (1.33×) and is the best arm there. EA's own
commented-out `m_retryTime = m_averageLatency * 1.5` brackets every value we
found to work. Above ~300 ms RTT prefer 800; see `035-adaptretry`.

## The discard branch, measured at the decision site

`netlat_discard` hooks the decision itself and records the engine's own margin.
One retail match, ~700 router game-command decisions:

| | retail | 400 ms timer |
|---|---|---|
| game commands discarded | **18 / 713 (2.52%)** | **0 / 684** |
| closest approach to the cliff | −8 frames | **+5 frames** |

Retail crosses the guard routinely; the fix never comes within five frames of it.

**Two results that cut against the alarming reading, both worth keeping:**

* **Every discard observed was harmless.** All 18 had already reached the peer —
  the guard fires when an *acknowledgement* is lost, and dropping an
  already-delivered command costs nothing. The harmful case needs a discard AND
  non-delivery (~p²) and has never been observed. So the fix removes a
  *precondition*, not a measured disconnect.
* **Only the router can discard a game command**, and structurally: a guest's own
  commands carry `exec == -1` until the router binds them, and the guard skips
  unbound commands (`cmp eax,-1; je`). A guest reaches this site only for frame
  info. An earlier headroom argument for the same conclusion was withdrawn as
  wrong reasoning; this is the measurement.

## Still unsettled

All evidence is 2-player, 4-minute matches. The harmful discard — one that was
never delivered — has not been observed in any arm, and at ~0.3 expected per
match that is the predicted outcome rather than evidence of absence.
