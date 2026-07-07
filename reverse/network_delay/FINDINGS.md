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

## Work plan

1. Unblock targeted ZH sweeps for the GameNetwork files with minimal compile shims.
2. Land byte-verified support files first: `NetworkUtil`, `FrameData`,
   `FrameDataManager`, `FrameMetrics`, and `NetPacket` if it locates cleanly.
3. Land or manually locate the core files: `Connection`, `ConnectionManager`,
   and `Network`.
4. Update this document with exact BFME RVAs, matched source paths, and any
   drift notes for the functions above.

## Non-goals

- Do not lower run-ahead values here.
- Do not add an opt-in patch profile here.
- Do not change matched source away from the original BFME behavior.
