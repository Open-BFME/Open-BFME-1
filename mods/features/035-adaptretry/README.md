# 035-adaptretry — DESIGNED, NOT BUILT

An adaptive replacement for `033-retrytime`'s constant. **Do not build this
without reading the two blockers below.**

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

## Parked

A two-level clamp with a conservative default is preferable to a computed timer:
it degrades toward 800 on an uncharacterised link where a computed one degrades
toward 400. Not needed unless 400 proves unsafe above 300 ms RTT — which four
stress matches at 300 ms RTT did not show.
