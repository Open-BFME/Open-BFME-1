# 035-adaptretry — CLOSED, NOT BUILT

An adaptive replacement for `033-retrytime`'s constant. **It is not needed:
the constant was measured at 500 ms RTT and holds. See CLOSED below.** The
finding and the two blockers are kept for whoever reopens it.

## The finding

BFME measures its own round trip and discards the result. `Connection+0x20` is
`m_averageLatency`, a running mean over 200 acked commands, updated on every ACK
by `processAck` (RVA `0x661CC0`). Layout: `+0x1C` retryTime, `+0x20`
averageLatency, `+0x24..+0x343` latencies[200], `+0x344` frameGrouping.

EA wrote the adaptive version and commented it out three lines from the constant
we change:

```c
m_retryTime = m_averageLatency * 1.5;   // dead code
```

That formula brackets every value measured to work: 150 ms RTT → 225 (400 works),
300 ms RTT → 450 (400 works, 800 worse), 500 ms RTT → 750 (predicted: 400 breaks).

## Why a constant is wrong at both ends

**The HIGH end of this argument is refuted — see CLOSED below.** It is kept
because the reasoning is the natural one and the measurement is the only thing
that beats it: 400 ms at 500 ms RTT does retransmit before the ack, and that is
what recovers the loss rather than what breaks it. The low-end half (400 ms is
13x the round trip at 30 ms) is untested and costs only bandwidth.

The timer must exceed the round trip or it retransmits before an ack can arrive.
At 500 ms RTT a 400 ms timer fires early on essentially every command. At 30 ms
RTT, 400 ms is 13× the round trip and wastes most of the recovery budget. No
single value serves the range a real ladder spans.

## Blocker 1 — the mean is understated for the whole match

`m_averageLatency` divides by a fixed 200 regardless of how many samples exist,
so after N acks it reads low by 200/N. A four-minute match carries roughly 200
commands **total**, so the average is understated for essentially all of it. With
50 acks, a 300 ms link reads 75 ms — and the naive ladder then picks the *most
aggressive* timer on the *least* evidence, which is exactly the choice that
fires before every ack. The failure mode is worst where the feature is needed
most.

Fixing it means maintaining a sample count the engine does not keep — per-
connection state in a detour inside a hot function, a materially larger feature
than one imm32.

## Blocker 2 — no floating point in a payload

`modbuild.py` hard-fails on `__fltused`, which MSVC 7.1 emits for *any* float in
the translation unit, including a comparison against a literal. Compare the raw
bits as unsigned ints instead — IEEE-754 positive floats are monotonic in their
bit pattern:

```
80.0f → 0x42A00000   160.0f → 0x43200000
320.0f → 0x43A00000  640.0f → 0x44200000
```

Test `avg == 0` first: it doubles as "no samples yet" and must map to the
conservative 2000, not the aggressive branch.

## CLOSED — 400 ms measured at 500 ms RTT, and it is where the fix matters most

This entry asked for one thing: "not needed unless 400 proves unsafe above
300 ms RTT". That was measured on 2026-08-30, four matches on the rig at
**500 ms RTT and 3% loss per direction**, two arms differing in exactly two
bytes (`0x6623DE`: `D0 07` -> `90 01`).

| pooled over 2 matches/arm | retail 2000 ms | 400 ms |
|---|---|---|
| desync flag | 0 | **0** |
| logic rate (engine's 5 Hz) | 4.60 router / 5.53 guest | **5.00 / 5.08** |
| guest frame-gap p99 | 1952 / 1938 ms | **420 / 420** |
| guest freezes >1 s | 7.0 per min | **0.4 per min** |
| commands discarded, guest | 48 of 1331 (3.61%) | **2 of 3008 (0.07%)** |
| worst discard margin | −10 frames | **−2 frames** |
| Connection::numRetries, median | 1 | **38** (max 86) |

**The prediction in this file was right about the traffic and wrong about the
consequence.** At 500 ms RTT the 400 ms timer does fire before an ack can
return, and the retransmission counter shows it — median 1 to 38. That extra
traffic is not a cost paid for nothing: it is the recovery. The early retry is
what takes discarded commands from 3.61% to 0.07% and guest freezes from 7.0
per minute to 0.4.

The sharpest number is the one that does NOT move: **guest p99 is 420 ms at
500 ms RTT and 420 ms at 150 ms RTT** (docs/net-fixes.md). The freeze floor is
set by the retry interval, not by the link — so a constant does not degrade as
RTT rises, which is the whole premise of "no single value serves the range".

Retail is the arm that fails here: it cannot hold the engine's 5 Hz at this RTT
(4.60 router, 5.53 guest catching up), and `tools/netlat.py --preflight`
rejects its capture for exactly that reason while passing the 400 ms arm.

So the two blockers below were never the reason not to build this. **The reason
is that the constant is not wrong at the high end**, and an adaptive timer
computed from an understated mean (blocker 1) would replace a measured-good
value with a worse one. Reopen only if a link above 500 ms RTT is measured and
400 ms is shown to lose there; the blockers stay recorded for whoever does.

Captures are under `build/netlat/rtt500-*/`, which is gitignored, so the table
above is the record rather than a pointer to one. The prediction was banked to
`build/netlat/rtt500-PREDICTION.md` before either arm ran, and all four of its
calls held: desync 0, retransmissions up sharply, freezes no worse (in fact far
better), and 5 Hz kept on the fixed arm. Reproduce with two arms from
`tools/modbuild.py --only 020-gameresult --only 030-netlatprobe [--only
033-retrytime]` and `BFME_NETEM="delay 250ms loss 3%" run_latency.py 120 <label> 2`.
