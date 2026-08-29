# Stopping BFME 1 freezing when a packet drops

`033-retrytime`. Four bytes. Shipped in `mods/dist`.

## The bug

When a command is lost, the sender retransmits **once** — and that retry fires at
the exact moment the command becomes eligible to be thrown away, because the
retry interval and the abandonment horizon are the same 2000 ms
(`m_retryTime` = 2000; `NetworkRunAheadSlack` = 10 frames × 200 ms).

There is no second chance. `Connection::doSend` (RVA `0x006620A4`) discards the
command once `slack + execFrame < currentFrame`, and BFME has **no receiver-side
resend request** — `resendFrameRangeToPlayer` exists with no callers, the
responder half of a protocol whose requester was never wired. The readiness test
`areFrameCommandsComplete` is a plain equality, so a missing command blocks that
frame forever: the victim freezes while everyone plays on, then the disconnect
timers drop them. That is the ordinary "game froze and someone dropped".

## The fix

`Connection::init`'s `mov dword ptr [edx+0x1C], 2000` → `400` (RVA `0x006623DE`).
No cave, no detour — a constant the engine already reads. Five delivery attempts
inside the same horizon instead of one.

## Results

150 ms RTT, 3% loss per direction, guest seat, n=3 per arm:

| | retail | retry400 |
|---|---|---|
| gap p99 | 1740 / 1769 / 1800 | **420 / 419 / 420** |
| worst stall | 2031 / 3724 / 3719 | **805 / 806 / 800** |
| excess time | 16.1 / 25.8 / 22.7% | **4.1 / 3.6 / 4.0%** |
| game time lost | 3.2 / 11.0 / 7.7% | **~0%** |
| host stalls/min | 49.98 | **0.23** |
| packets/s | 9.90–10.70 | 10.91–11.03 |

Disjoint on every row, and **far more predictable**: retail's worst stall varies
83% between identical runs; the fix varies 0.1%.

On real build orders (Gondor farm placement), 150 ms/3%, both fixes together:
**placement goes 0.7–2.6 s unpredictable → 0.43–0.65 s consistent.**

## Causal proof, per event

Duplicate-arrival gaps track the poked constant across nine matches:
timer 2000 → gaps 1991/2019/2030/2034; timer 400 → 416/417/381/446; timer 800 →
842. Outliers land at exact multiples (3996 = 2×2000). Hundreds of individual
retransmissions, not ten events per match.

## Safety

Zero desync and zero stuck seats in 29 matches, including four at 300 ms RTT
where a 400 ms timer fires inside the round trip. Duplicates occur at 1.0–2.5% in
**every** arm including retail and are absorbed by identity matching (player +
16-bit command id, compared between objects — a tolerated duplicate would wedge a
seat permanently; none wedged). Detector validated: `034-framedrain` trips it.

## Not established

The discard branch has never been *caught* executing — the mechanism is read from
disassembly with strong circumstantial support. All evidence is 2-player,
4-minute matches; the failure scales with players, commands and duration, so this
is the least-exposed configuration. `NetworkDisconnectTime` is **15000 ms** at
runtime (not the binary's 5000 default), so stock spends 14–25% of its
disconnect budget on a bad stall, not the 41–74% an earlier revision claimed.
