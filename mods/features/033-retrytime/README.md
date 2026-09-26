# 033-retrytime — frame-gap p99: 1769 ms → 420 ms

`Connection::Connection` (RVA `0x006623A0`) seeds `m_retryTime` — `this+0x1C` —
to 2000. Rewritten to `RETRY_MS` (400) at RVA `0x006623DE`, the imm32 three bytes
into that store. No cave, no detour — one imm32.

Not `Connection::init`, which is what this file and `docs/net-fixes.md` used to
say: that name is Zero Hour's. BFME folds ZH's `init()` work into the
constructor, so grepping for `init` finds nothing. The body is C++ at
`game/GameEngine/Source/GameNetwork/Connection.cpp`.

**SHIPPED** in `mods/dist` as of 2026-08-29. See `docs/net-fixes.md` for
results; this file records the mechanism and the limits.

## Why 2000 is the wrong number

The age window is `NetworkRunAheadSlack` logic frames. It was 10 in the
measured installation: nominally 2000 ms at 5 Hz, matching the original retry
interval. A shorter retry interval provides more opportunities while a stamped
command is still retained. It does not guarantee an exact number of attempts:
the comparison is strict, acknowledgements can retire a reference sooner, and
logic-frame age advances with the simulation rather than wall time.

`Connection::doSend` updates the last-send time before testing command age.
Frame `-1` bypasses age removal; this is how an original guest command is kept
until the router can receive and stamp it.

## Recovery paths and their limits

The 2026-09-07 reconstruction corrects the earlier claim that the responder
has no callers. `processRequestFrameDataCommand` at `0x006659B0` calls
`resendFrameRangeToPlayer` at `0x00664B40`. The latter sends retained payloads
from every frame-data manager and then a fresh `FRAMEINFO` count for each frame.
`DisconnectManager::processDisconnectFrame` at `0x0066BD80` also calls it.

The outgoing type 9 request is emitted by
`processInformPlayerLeaveFrameCommand` at `0x00664430`: during router-departure
recovery it requests frames from current+1 through the announced leave frame.
The ordinary `areFrameCommandsComplete` gate remains an equality check; it does
not implement Zero Hour's tri-state resend mechanism.

History replay cannot recreate a guest command that the router never received:
it has not yet been stamped or inserted into the frame archive. Timer retries
are essential for that case. A permanently missing command can stall readiness
without causing a checksum mismatch, so checksum-only validation is insufficient.

## Duplicate delivery is safe, measured and traced

`FrameData::addCommand` matches by **identity** — player (`+0x0C`) and a 16-bit
command id (`+0x10`), compared between two distinct objects, so a retransmit at a
fresh allocation matches its original. Duplicates occur at 1.0–2.5% in **every**
arm including retail. Duplicate suppression is present in the recovered command-ID history and
frame insertion paths. No match wedged in the 29 recorded trials. The readiness
equality explains why an overcount could block a frame, but it does not prove
that all possible duplicates, reorderings or session lengths are safe.

IDs are 16 bits. The recovered `BFMECommandIDHistory::accept` path also
clears an older region of its bitmap before testing and setting a new ID, so
wraparound is not by itself proof that a legitimate command will be dropped.
These short-match measurements do not establish long-session or wraparound
behavior; that requires a separate test.

## The constant is proven to cause the behaviour

Duplicate-arrival gaps track the poked value, per event, across nine matches:
2000 → 1991/2019/2030/2034 ms; 400 → 416/417/381/446; 800 → 842. Outliers at
exact multiples (3996 = 2×2000). This is prediction, not fit — 800 was never
used to derive it.

## Tested RTT range

A timer shorter than the round trip can trigger redundant traffic before an
ACK returns. That is a tradeoff, not by itself a correctness failure. The later
500 ms RTT experiment in `035-adaptretry/README.md` retained the 400 ms timer
and recorded zero desync flags with improved stalls in those short two-player
runs. It supersedes this page's earlier advice to prefer 800 ms above 300 ms.
Higher RTTs, long sessions and larger lobbies remain separate validation work.

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
