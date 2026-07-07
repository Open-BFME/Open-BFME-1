# Multiplayer delay reconstruction

Goal: recover the original BFME 1 multiplayer command-delay path, byte-verify it,
and document the exact BFME addresses needed for any future opt-in patch. This
track does not change gameplay behavior.

## Current hypothesis

Zero Hour schedules synchronized network commands for a future logic frame:

- `Network::GetCommandsFromCommandList` forwards local network `GameMessage`s.
- `Network::getExecutionFrame` returns `TheGameLogic->getFrame() + m_runAhead`.
- `ConnectionManager::sendLocalGameMessage` stores that future frame on the
  generated `NetGameCommandMsg`.
- `ConnectionManager::allCommandsReady` gates logic-frame advancement until
  every player has command data for the current frame.
- `ConnectionManager::updateRunAhead` computes and broadcasts later run-ahead
  values from latency/FPS metrics.
- `Network::processRunAheadCommand` applies those values and adjusts packet
  frame grouping.

BFME may drift from ZH, so ZH is only the search map. The BFME binary remains the
source of truth.

## BFME targets

| Area | Function | BFME RVA | Status |
| --- | --- | --- | --- |
| constants | `MAX_FRAMES_AHEAD`, `MIN_RUNAHEAD`, `FRAME_DATA_LENGTH`, `FRAMES_TO_KEEP` | TBD | not recovered |
| scheduling | `Network::getExecutionFrame` | TBD | not recovered |
| setup | `Network::init` | TBD | not recovered |
| local commands | `ConnectionManager::sendLocalGameMessage` | TBD | not recovered |
| command relay | `ConnectionManager::sendLocalCommand` | TBD | not recovered |
| readiness gate | `ConnectionManager::allCommandsReady` | TBD | not recovered |
| dynamic delay | `ConnectionManager::updateRunAhead` | TBD | not recovered |
| apply delay | `Network::processRunAheadCommand` | TBD | not recovered |
| frame pacing | `Network::timeForNewFrame` | TBD | not recovered |

## Landed evidence

- `src/zh/connectionmanager.cpp` is present from ZH and byte-verifies 5 emitted
  functions. `land_zh.py` marked 88 drifted definitions `present-unmatched`.
- `src/zh/network.cpp` is present from ZH and byte-verifies 2 emitted functions.
  `land_zh.py` marked 55 drifted definitions `present-unmatched`.
- The current matched network rows are:
  - `ConnectionManager::processProgress` at `0x00662D20`.
  - `NetworkInterface::createNetwork` at `0x0065C1F0`.
  - `Network::isPacketRouter` at `0x00681B20`.
  - Three STL helper/template rows emitted from `connectionmanager.cpp`.
- The core delay functions in the table above are now source-visible in `src/zh/`,
  but still not byte-matched. Treat their bodies as a map for manual BFME
  reconciliation, not as proven BFME code.

## Work plan

1. DONE: unblock targeted ZH sweeps for the GameNetwork files with minimal
   compile shims.
2. DONE: land the first byte-verified `ConnectionManager` and `Network` rows.
3. NEXT: reconcile or manually locate the core delay functions listed above.
4. NEXT: update this document with exact BFME RVAs and drift notes for each core
   function as they are proven.

## Non-goals

- Do not lower run-ahead values here.
- Do not add an opt-in patch profile here.
- Do not change matched source away from the original BFME behavior.
