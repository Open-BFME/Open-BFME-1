# 033-retrytime: frame-gap p99 1,769 ms → 420 ms

On a lossy link, a lost command packet stalls the match until retail resends it,
2000 ms later. This mod resends after 400 ms. Shipped in the repository
bundle, `mods/dist`, since 2026-08-29; `031-earlysend` ships with it.

## What players get

Two clients over `netem` at 150 ms round trip and 3% loss per direction, three
matches per arm:

| | retail | with 033 |
|---|---|---|
| frame-gap p99 | 1740 / 1769 / 1800 ms | **420 / 419 / 420 ms** |
| worst stall | 2031 / 3724 / 3719 ms | **805 / 806 / 800 ms** |
| game time lost | 3.2 / 11.0 / 7.7% | **~0%** |

The worst freeze fell from 3.7 s to 0.8 s. That is what three matches recorded,
not a guaranteed maximum. With `031-earlysend` as well, a Gondor farm placement
took 0.43–0.65 s from click to construction, against 0.7–2.6 s in retail.

## How it works

`Connection::Connection` (RVA `0x006623A0`) sets the resend interval
`m_retryTime` (`this+0x1C`) to 2000 ms. The mod rewrites that imm32, at RVA
`0x006623DE`, to `RETRY_MS` (400): four bytes, no code cave, no detour.

Unacknowledged commands are resent each interval; a stamped command is dropped
once older than `NetworkRunAheadSlack` logic frames, nominally 2000 ms where
measured. A 400 ms interval gives a lost command more resend opportunities
inside that window. Unstamped guest commands (frame
`-1`) skip the age test and are kept until the router stamps them.

The constant is proven to cause the change: the gap between an original command
and its duplicate follows the poked value, with per-match medians of
1991–2034 ms at 2000, 842 ms at 800 and 381–446 ms at 400.

## Build

`python3 tools/modbuild.py --dist` builds the bundle into `mods/dist/`.

## Safety and limits

* Every player in a lobby must run the same build; the launcher's MD5 check
  enforces this.
* Retail already delivers duplicate commands at the same rate (1.19% stock,
  0.45–2.20% fixed). `FrameData::addCommand` rejects them by player and 16-bit
  command ID.
* The engine's desync flag stayed zero in every match at 150, 300 and 500 ms
  round trip. A permanently missing command can stall the game without a
  checksum mismatch, so checksum-only validation is insufficient.
* Tested to 500 ms round trip, two matches per arm. Above about 400 ms the timer
  fires before an acknowledgement returns, adding traffic (median retries
  1 → 38) with no checksum divergence observed; frame-gap p99 stays at 420 ms.
  Above 500 ms is unmeasured.
* Retail's engine discards 2.52% of router game commands at 150 ms; the fix
  discarded none there, and 0.07% against retail's 3.61% at 500 ms. Every
  discard checked at 150 ms was of a command the peer had already received;
  that check was not repeated at 500 ms.
* All evidence comes from two-player, four-minute matches. Eight-player
  behaviour is modelled, not measured; long sessions and 16-bit command-ID
  wraparound are untested.

Protocol and evidence:
[multiplayer-lockstep.md](../../../targets/game/reverse/network_delay/multiplayer-lockstep.md),
[FINDINGS.md](../../../targets/game/reverse/network_delay/FINDINGS.md).
