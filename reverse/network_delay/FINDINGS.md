# Multiplayer delay reconstruction

Goal: recover the original BFME 1 multiplayer command-delay path, byte-verify it,
and document the exact BFME addresses needed for any future opt-in patch. This
track does not change gameplay behavior.

## The answer: a router-published frame ceiling

The delay is recovered and byte-matched. It is not Zero Hour's run-ahead. BFME
clamps every client to a shared **frame ceiling** stored on the connection
manager at `+0x1205C`, which the packet router republishes from its own current
frame on a fixed timer.

| Item | RVA | Size | Role |
| --- | --- | --- | --- |
| `BFMENativeNetwork::getFrameAdvanceCount` | `0x00681F70` | 395 | native vtable `0x0111A968` slot `+0x3C`; how many logic frames may run now |
| `BFMENativeNetwork::getFramePacingStatus` | `0x00682160` | 214 | slot `+0x40`; same two paths, returns 0/1/2 |
| `BFMEConnectionManager::update` | `0x0066AB30` | 814 | the per-tick pass; the only caller of sendFrameInfo |
| `BFMEConnectionManager::sendFrameInfo` | `0x00665D10` | 354 | builds command type 3 and, as router, sets the ceiling |
| `BFMEConnectionManager::processIncomingCommand` | `0x0066A3F0` | 580 | case 3 raises a client's ceiling to the announced frame |
| `BFMEConnectionManager::areFrameCommandsComplete` | `0x006633E0` | 89 | the readiness gate |
| `BFMEConnectionManager::getFrameHeadroom` | `0x00664320` | 142 | ceiling minus current frame, for both roles |
| `BFMEConnectionManager::runRelayPass` | `0x0066A740` | 792 | the router's receive-and-relay pass |
| `BFMEDisconnectManager::update` | `0x0066C8D0` | 1122 | the timeout sweep update runs alongside it |

### How a frame is released

`getFrameAdvanceCount` returns 1 when `+0x0C` says we are not in a network game,
and 1 again on frame 0. Otherwise it splits on the virtual predicate at native
slot `+0x8C`:

* **Not the packet router.** `allowance = connectionManager->+0x1205C - TheGameLogic->getFrame() + 1`.
  If that is positive it consults `areFrameCommandsComplete`; when the frame's
  commands are not yet in it calls its own slot `+0x24` and returns 0, otherwise
  it clears the stall flag at `+0x28` and returns the allowance. When the
  allowance is already non-positive it bumps the stall counter at `+0x2C`,
  records the frame in the `0x012F7728` global, and returns the non-positive
  value.
* **Packet router.** If `hasPacketRouterFrameStall` (`0x00664260`) it zeroes the
  QPC accumulator at `+0x20` and returns 0. Otherwise it adds the
  `QueryPerformanceCounter` delta to that accumulator and compares it against
  **`QueryPerformanceFrequency / 5`** -- a fixed 200ms, five logic ticks per
  second, independent of ping and of frame rate. Below the quantum it returns 0;
  at or above it subtracts one quantum, clamps a backlog of more than two quanta
  (bumping `0x012F7724`, the counter behind the string "Total # of times we've
  hit the run-ahead ceiling" at `0x006EE800`), and returns 1.

### How the ceiling is published

`update` is the only caller of `sendFrameInfo`, so the cadence above is exactly
the cadence of the ceiling. `sendFrameInfo` allocates a `0x28`-byte command type
3, stamps `TheGameLogic->getFrame()` at `+0x1C`, sums `getCommandCount(frame)`
over the eight `FrameDataManager`s at `+0x120E4`, records that total on the local
manager with `setFrameCommandCount` and copies it into the message at `+0x24`.
Then, as packet router, it broadcasts with relay `~(1 << localSlot)` and sets
`+0x1205C` to **its own current frame**; as a client it sends only to the router.

`processIncomingCommand` case 3 is the receiving half: it updates
`m_playerLatestFrame[sender]` at `+0x12060` and the aux dword at `+0x120A0`, and
-- only when it is *not* the router -- raises its own `+0x1205C` to the announced
frame. If that frame is not behind the current one and the message's count at
`+0x24` is not `-1`, it stores the count on the local manager as the expected
total.

So the host runs free and every other player is clamped to a frame the host
published at most 200ms ago. **That is BFME's off-host delay, and it is a
property of the fixed quantum rather than of latency**, which is why it does not
shrink on a LAN. Any future opt-in patch has to change that quantum or the
ceiling it feeds, not hunt for a run-ahead value.

### Readiness

`areFrameCommandsComplete` sums `FrameDataManager::getCommandCount(frame)` over
the eight managers at `+0x120E4`, skipping null and quitting ones, and returns
whether that total equals the local manager's `getFrameCommandCount(frame)`.
BFME therefore tracks one aggregate expected count where Zero Hour matches
counts per player.

### Ruled out

The ZH `Network`/`ConnectionManager` run-ahead path is not merely unmatched, it
is absent: `sendLocalGameMessage`, `allCommandsReady`, `updateRunAhead`,
`setFrameGrouping`, `processRunAheadCommand`, `timeForNewFrame`,
`GetCommandsFromCommandList` and `Network::update` all classify absent in the ZH
sweep, a locate-only probe of the 256-byte `timeForNewFrame` body returned
`0 located`, and BFME has no code xrefs to the `NetworkRunAheadSlack` or
`NetworkRunAheadMetricsTime` strings beyond their INI parse rows.

## BFME command-type correction

The old ZH run-ahead command trail is now ruled out for BFME retail. The BFME
command-type string mapper at `0x00683020` names the relevant values as:

| Value | BFME name |
| --- | --- |
| `3` | `NETCOMMANDTYPE_FRAMEINFO` |
| `4` | `NETCOMMANDTYPE_GAMECOMMAND` |
| `5` | `NETCOMMANDTYPE_REQUEST_GAMESPY_STATS_AUTHKEY` |
| `6` | `NETCOMMANDTYPE_GAMESPY_STATS_AUTHKEY` |
| `7` | `NETCOMMANDTYPE_REQUESTPLAYERLEAVE` |
| `8` | `NETCOMMANDTYPE_INFORMPLAYERLEAVEFRAME` |
| `9` | `NETCOMMANDTYPE_REQUESTFRAMEDATA` |
| `10` | `NETCOMMANDTYPE_PLAYERLEAVE` |
| `11` | `NETCOMMANDTYPE_DESTROYPLAYER` |

This differs from Zero Hour, where values `6` and `7` are run-ahead metrics and
run-ahead. In BFME:

- `0x006741F0` is byte-matched as the command type `7` constructor and initializes
  a single dword payload at `+0x1C`; it is now named
  `BFMENetRequestPlayerLeaveCommandMsg::construct`.
- `0x00674240` and `0x00674250` are byte-matched as the payload setter/getter.
- `0x00677530` writes the type `7` wire payload as a four-byte `D` field after
  `T/R/P/C`; there is no ZH-style frame-rate byte.
- `0x00675BE0` constructs command type `6`, whose callers populate two
  `AsciiString`-like fields. It is GameSpy stats auth-key traffic, not
  run-ahead metrics.

So a future delay fix should not patch BFME command types `6` or `7` as if they
were ZH `NetRunAhead*` classes.

The incoming command dispatcher at `0x0066A3F0` uses the command type at message
offset `+0x14` and a jump table at `0x0066A634`. For the frame-delay path:

| Value | Dispatcher evidence |
| --- | --- |
| `3` | inline frame-info-ish state update for per-player latest frame fields at `+0x12060`/`+0x120A0` |
| `8` | calls `0x00664430`, the next frame-info/request helper to recover |
| `9` | calls matched `BFMEConnectionManager::processRequestFrameDataCommand` at `0x006659B0` |

## BFME-native path

The BFME binary routes the proven multiplayer entry point through a smaller
network wrapper/backend pair. These addresses are current reverse-engineering
anchors, not behavior changes.

| Item | Address | Evidence | Status |
| --- | --- | --- | --- |
| `TheNetwork` global | VA `0x012F76F0` / RVA `0x00EF76F0` | caller at `0x006377D0` stores the `createNetwork` return value, then calls vtable slot `+0x04` | recovered |
| `NetworkInterface::createNetwork` | RVA `0x0065C1F0`, ILT `0x000362C3` | byte-matched row; allocates `0xA8` bytes | matched |
| BFME network wrapper constructor | RVA `0x0065AC30`, ILT `0x00029C12` | byte-matched as `BFMENetwork::construct`; installs vtable VA `0x01119C8C` and initializes wrapper queues/list | matched |
| BFME network wrapper vtable | VA `0x01119C8C` / RVA `0x00D19C8C` | referenced by constructor | recovered |
| backend constructor | RVA `0x006547F0`, ILT `0x00040E44` | byte-matched as `BFMENetworkBackend::construct`; stores owner pointer at backend `+0x68` and initializes list at `+0x5C` | matched |
| backend vtable | VA `0x0111988C` / RVA `0x00D1988C` | installed by backend constructor | recovered |
| backend deleting destructor | RVA `0x00654890` | byte-matched as `BFMENetworkBackend::destroyAndMaybeDelete`; backend vtable slot `+0x00` | matched |
| backend live-handle opener | RVA `0x009DB650` | byte-matched as `BFMENetworkBackend::openLiveHandle`; backend vtable slot `+0x04`, starts thread and stores handle at `+0x48` | matched |
| backend thread start | RVA `0x009DB630` | byte-matched as `BFMENetworkBackendThreadStart`; calls global slot `+0x58`, then backend vtable slot `+0x08` | matched |
| backend event callback | RVA `0x006549C0`, ILT `0x000276B0` | byte-matched as `BFMENetworkBackendEventCallback`; dispatcher calls it through the ILT in multiple cases, callback returns with `ret 0x28` | matched |
| wrapper deleting destructor | RVA `0x0065ADB0` | byte-matched as `BFMENetwork::destroyAndMaybeDelete`; wrapper vtable slot `+0x00` | matched |
| wrapper init | RVA `0x006548C0` | byte-matched as `BFMENetwork::init`; creates backend at wrapper `+0x64` and calls backend vtable slot `+0x04` | matched |
| backend handle check | RVA `0x009DB590` | byte-matched as `BFMENetworkBackend::hasLiveHandle`; reads backend `+0x48` | matched |
| backend handle clear | RVA `0x009DB5A0` | byte-matched as `BFMENetworkBackend::closeLiveHandle`; waits on/clears backend `+0x48` and `+0x44` | matched |
| lock-ref release | RVA `0x009DB400` | byte-matched as `BFMEAutoLockRef::~BFMEAutoLockRef`; releases lock handle at `+0x00` when `+0x04` is false | matched |
| wrapper queue 0 push | RVA `0x0065E050` | byte-matched as `BFMENetwork::pushQueue0`; locks wrapper `+0x04`, appends to queue at `+0x14` | matched |
| wrapper queue 0 pop | RVA `0x0065ADE0` | byte-matched as `BFMENetwork::popQueue0`; locks wrapper `+0x04`, pops queue at `+0x14` into caller output | matched |
| wrapper queue 1 push | RVA `0x0065E120` | byte-matched as `BFMENetwork::pushQueue1`; locks wrapper `+0x0C`, appends to queue at `+0x3C` | matched |
| wrapper queue 1 pop | RVA `0x00658E20` | byte-matched as `BFMENetwork::popQueue1`; locks wrapper `+0x0C`, pops queue at `+0x3C` into caller output | matched |
| wrapper payload-list push | RVA `0x0065E340` | byte-matched as `BFMENetwork::pushList90`; dispatcher calls wrapper slot `+0x20` after building a payload, appending to list at `+0x90` | matched |
| wrapper payload-list find/create | RVA `0x0065AEB0` | byte-matched as `BFMENetwork::findList90`; wrapper slot `+0x24` searches or materializes an entry in list at `+0x90` | matched |
| wrapper state-copy helpers | RVAs `0x00655060`, `0x00655090`, `0x006550C0` | byte-matched as `BFMENetwork::copyState6C`, `copyState78`, `copyState84`; callback uses these to copy wrapper fields `+0x6C`, `+0x78`, `+0x84` | matched |
| backend event dispatcher | RVA `0x0065CA50` | byte-matched as `BFMENetworkBackend::dispatchEvents`; backend vtable slot `+0x08`; body ends at `0x0065D6F2` before EH catch thunk and switch table | matched |
| dispatcher catch thunk | RVA `0x0065D6F3` | byte-matched as `BFMENetworkBackendDispatchCatch`; returns cleanup resume VA `0x00A5CAEB` | matched |
| registered callback | RVA `0x0065C260` | byte-matched as `BFMENetworkRegisteredCallback`; dispatcher pushes callback VA `0x00A5C260` before call to `0x009D5330`; callback calls wrapper slots `+0x18` and `+0x10` | matched |

Known wrapper slots from vtable VA `0x01119C8C`:

| Slot | Body RVA | Current role |
| --- | --- | --- |
| `+0x00` | `0x0065ADB0` | matched as `BFMENetwork::destroyAndMaybeDelete`; scalar deleting destructor wrapper |
| `+0x04` | `0x006548C0` | matched as `BFMENetwork::init`; allocates backend object and calls backend slot `+0x04` |
| `+0x08` | `0x00652AB0` | matched as `BFMENetwork::destroyBackend`; releases lock-ref `+0xA4`, backend handle, then backend `+0x64` |
| `+0x0C` | `0x00651780` | matched as `BFMENetwork::backendHasLiveHandle`; proxies backend pointer at wrapper `+0x64` |
| `+0x10` | `0x0065E050` | matched as `BFMENetwork::pushQueue0`; pushes queue at wrapper `+0x14` |
| `+0x14` | `0x0065ADE0` | matched as `BFMENetwork::popQueue0`; pops queue at wrapper `+0x14`, returns bool |
| `+0x18` | `0x0065E120` | matched as `BFMENetwork::pushQueue1`; pushes queue at wrapper `+0x3C` |
| `+0x1C` | `0x00658E20` | matched as `BFMENetwork::popQueue1`; pops queue at wrapper `+0x3C`, returns bool |
| `+0x20` | `0x0065E340` | matched as `BFMENetwork::pushList90`; appends payload list at wrapper `+0x90` |
| `+0x24` | `0x0065AEB0` | matched as `BFMENetwork::findList90`; searches or creates payload list entry at wrapper `+0x90` |

The wrapper constructor initializes locks at `+0x04`, `+0x0C`, and `+0x9C`;
queue/list structures at `+0x14` and `+0x3C`; object/array regions at `+0x6C`,
`+0x78`, and `+0x84`; backend pointer at `+0x64`; and a current/session-ish
field at `+0x68`.

The dispatcher at `0x0065CA50` is now bounded and byte-matched. Its switch table
starts at `0x0065D6FC`; that table is data and is intentionally not part of the
function row. Cases `4`, `8`, and `9` share the cleanup block at `0x0065D69E`;
case `10` calls helper `0x0062F7F2`; case `0` registers callback VA
`0x00A5C260`; and case `1` reads `LoTRB4MEOnline\MiscPref%d.ini` keys `"0"`
through `"5"` with default value `10`. Treat those key/default reads as GameSpy
misc-preference evidence until another caller proves they feed gameplay delay.

## BFME timing fields

The first native timing slice is now byte-matched:

| Function | RVA | Timing evidence |
| --- | --- | --- |
| `BFMEConnectionManager::isPlayerConnected` | `0x00662A50` | uses `timeGetTime`; compares elapsed time against `TheGlobalData + 0xCC0` (`NetworkPlayerTimeoutTime`); before frame threshold `0x010EAD50`, uses `NetworkPlayerTimeoutTime * 4` |
| `BFMEConnectionManager::isPlayerConnectedForTimeout` | `0x00662B00` | same connection timestamp at peer object `+0x34C`; normally uses caller timeout, but startup path still falls back to `NetworkPlayerTimeoutTime * 4` |
| `BFMEConnectionManager::hasPacketRouterFrameStall` | `0x00664260` | only runs when local player is packet router; after frame `5`, uses `TheGlobalData + 0xCB4` (**`NetworkRunAheadSlack`**) to detect stale per-player frame data |
| `BFMEDisconnectManager::hasDisconnectScreenNotifyTimedOut` | `0x0066B510` | compares elapsed time against `TheGlobalData + 0xCC4` (`NetworkDisconnectScreenNotifyTime`) |
| `BFMEConnectionManager::processRequestFrameDataCommand` | `0x006659B0` | command type `9` handler; rejects/clamps requested resend windows using `NetworkRunAheadSlack` (`+0xCB4`), then calls `0x0040D8CD` with player id and frame range |

These are timeout/readiness gates, not the delay patch itself, but they expose the
retail frame and keep-alive timing constants that a later patch design must not
confuse with ZH run-ahead command traffic.

## BFME frame pacing

ZH `Network::timeForNewFrame` is not a BFME byte match. A locate-only probe of
the 256-byte ZH-shaped body returned `0 located`, and BFME has no code xrefs to
the `NetworkRunAheadSlack`/`NetworkRunAheadMetricsTime` strings beyond their INI
parse-table rows. That rules out the ZH run-ahead pacing body as the direct patch
site.

The BFME-native `Network` object instead initializes QPC pacing state in the
constructor body at `0x006818B0`, now byte-matched as
`BFMENativeNetwork::construct`:

| Field | Constructor evidence |
| --- | --- |
| `+0x08` | connection manager pointer initialized to null |
| `+0x0C` | local/network status initialized to `0` |
| `+0x10` | `QueryPerformanceFrequency` output |
| `+0x18` | initial `QueryPerformanceCounter` output |
| `+0x20`/`+0x24` | QPC accumulator initialized to `0` |
| `+0x28`, `+0x34`, `+0x35` | pacing/status flags initialized to false |
| `+0x38` | frame/player sentinel initialized to `-1` |

The native vtable at `0x0111A968` resolves slot `+0x3C` to `0x00681F70` and
slot `+0x40` to `0x00682160`. Slot `+0x40` is now byte-matched as
`BFMENativeNetwork::getFramePacingStatus`:

| Function | RVA | Pacing evidence |
| --- | --- | --- |
| `BFMENativeNetwork::getFramePacingStatus` | `0x00682160` | returns `1` when not in active network status; without packet-router timing mode, returns `connectionManager->+0x1205C - currentFrame + 1`; otherwise accumulates QPC ticks and returns `0`, `1`, or `2` based on elapsed budget |

Slot `+0x3C` at `0x00681F70` is now byte-matched as
`BFMENativeNetwork::getFrameAdvanceCount` -- see the first section, which is
where the QPF/5 quantum and the four globals `0x012F7718`, `0x012F771C`,
`0x012F7724` and `0x012F7728` are described.

## Landed evidence

- `ConnectionManager.cpp`, `Network.cpp`, `NetCommandMsg.cpp` and
  `MessageStream.cpp` are now trimmed to
  byte-matched surfaces only; the previous unclaimed ZH bodies were removed
  rather than treated as progress.
- `Code/GameEngine/Source/GameNetwork/native_network.cpp` contains the first byte-matched BFME-native
  wrapper/backend code:
  - `BFMENetworkBackend::construct` at `0x006547F0` (constructor body).
  - `BFMENetworkBackend::destroyAndMaybeDelete` at `0x00654890`.
  - `BFMENetworkBackend::openLiveHandle` at `0x009DB650`.
  - `BFMENetworkBackendThreadStart` at `0x009DB630`.
  - `BFMENetworkBackendEventCallback` at `0x006549C0`.
  - `BFMENetwork::construct` at `0x0065AC30` (constructor body).
  - `BFMENetwork::destroyAndMaybeDelete` at `0x0065ADB0`.
  - `BFMENetwork::init` at `0x006548C0`.
  - `BFMENetwork::backendHasLiveHandle` at `0x00651780`.
  - `BFMENetwork::destroyBackend` at `0x00652AB0`.
  - `BFMENetwork::pushQueue0` at `0x0065E050`.
  - `BFMENetworkBackend::hasLiveHandle` at `0x009DB590`.
  - `BFMENetworkBackend::closeLiveHandle` at `0x009DB5A0`.
  - `BFMEAutoLockRef::~BFMEAutoLockRef` at `0x009DB400`.
  - `BFMENetwork::popQueue0` at `0x0065ADE0`.
  - `BFMENetwork::pushQueue1` at `0x0065E120`.
  - `BFMENetwork::popQueue1` at `0x00658E20`.
  - `BFMENetwork::pushList90` at `0x0065E340`.
  - `BFMENetwork::findList90` at `0x0065AEB0`.
  - `BFMENetwork::copyState6C`, `copyState78`, and `copyState84` at
    `0x00655060`, `0x00655090`, and `0x006550C0`.
- `Code/GameEngine/Source/GameNetwork/native_network_callback.cpp` contains `BFMENetworkRegisteredCallback`
  at `0x0065C260`.
- `Code/GameEngine/Source/GameNetwork/native_network_dispatcher.cpp` contains `BFMENetworkBackend::dispatchEvents`
  at `0x0065CA50` and its EH catch thunk at `0x0065D6F3`.
- `Code/GameEngine/Source/GameNetwork/native_netcommandmsg.cpp` contains the BFME command type `7`
  request-player-leave constructor/destructor and its single dword payload
  setter/getter at `0x006741F0`, `0x00674230`, `0x00674240`, and `0x00674250`.
- `Code/GameEngine/Source/GameNetwork/native_connection_timing.cpp` contains the first byte-matched BFME
  player-timeout, packet-router stall, disconnect-screen timeout, and request
  frame-data handler checks at `0x00662A50`, `0x00662B00`, `0x00664260`,
  `0x0066B510`, and `0x006659B0`.
- `Code/GameEngine/Source/GameNetwork/native_network_interface.cpp` contains the native BFME `Network`
  constructor body at `0x006818B0`, anchoring the QPC frame-pacing fields, and
  the QPC-backed pacing-status helper at `0x00682160`.
- The current matched network rows are:
  - `ConnectionManager::processProgress` at `0x00662D20`.
  - `NetworkInterface::createNetwork` at `0x0065C1F0`.
  - `Network::isPacketRouter` at `0x00681B20`.
  - Three STL helper/template rows emitted from `connectionmanager.cpp`.
- The old ZH delay functions are not proven BFME code. Treat ZH as an intent map
  and the BFME-native rows above as the patchable evidence.

## Object layouts pinned by the matched bodies

### ConnectionManager

| Offset | Field |
| --- | --- |
| `+0x00004` | `Connection *m_connections[8]` |
| `+0x12028` | `m_localSlot` |
| `+0x1202C` | `m_packetRouterSlot` |
| `+0x12030` | per-player dword[8], init `-1` |
| `+0x12050` / `+0x12054` / `+0x12058` | dword / word / dword |
| `+0x1205C` | **frame ceiling** |
| `+0x12060` | per-player latest frame[8] |
| `+0x12080` | per-player state[8]: 0 empty, 1 in game, 2-3 leaving |
| `+0x120A0` | per-player dword[8], from FRAMEINFO `+0x20` |
| `+0x120C0` | per-player dword[8] |
| `+0x120E4` | `FrameDataManager *m_frameData[8]` |
| `+0x12104` / `+0x12108` | the two pending-command lists the ack path searches |
| `+0x1210C` .. `+0x12130` | further owned objects, all released by `destroy` |

The constructor (`0x00669630`) and init (`0x00669050`) write the whole tail; the
destructor (`0x00668D90`) releases it. Note the constructor stores **no vtable**
at `+0x00`, so whatever occupies that dword is not a vptr.

### DisconnectManager

36 bytes smaller than the ZH reference: no `m_packetRouterFallback[8]`, no
`m_currentPacketRouterIndex`, no `m_packetRouterTimeout` -- the same edit that
removed PACKETROUTERQUERY and PACKETROUTERACK from its command block.

| Offset | Field |
| --- | --- |
| `+0x000` | vptr |
| `+0x004` | `m_lastFrame` |
| `+0x008` | `m_lastFrameTime` |
| `+0x00C` | `m_disconnectState` |
| `+0x010` | `m_lastKeepAliveSendTime` |
| `+0x014` | `m_playerTimeouts[7]` |
| `+0x030` | `m_playerVotes[8][8]`, row stride 0x40 |
| `+0x230` | `m_disconnectFrames[8]` |
| `+0x250` | `m_disconnectFramesReceived[8]` |
| `+0x258` | `m_haveNotifiedOtherPlayersOfCurrentFrame` |
| `+0x25C` | `m_timeOfDisconnectScreenOn` |
| `+0x260` / `+0x264` / `+0x268` | `m_pingsSent` / `m_pingsRecieved` / `m_pingFrame` |

Carried by `reference/shims/disconnectmanager`. `turnOffScreen` (`0x0066B270`)
is a BFME addition with no ZH counterpart, called unconditionally at the end of
`processDisconnectScreenOff`.

### FrameData

20 bytes, not the ZH reference's 24 -- ZH's leading `m_frame` is gone because the
ring index already is the frame. `m_frameCommandCount` `+0x00`,
`m_commandCount` `+0x04`, `m_commandList` `+0x08`, `m_lastFailedCC` `+0x0C`,
`m_lastFailedFrameCC` `+0x10`. `FrameDataManager` keeps the ZH layout.
`FRAME_DATA_LENGTH` is the runtime global at VA `0x012BA088`. Carried by
`reference/shims/framedata`.

### NetCommandRef

De-pooled and 20 bytes: `m_msg` `+0x00` (where ZH has a vptr), `m_next` `+0x04`,
`m_prev` `+0x08`, `m_relay` `+0x0C`. Proven by `relayCommand` (`0x00663100`) and
`NetCommandList::reset` (`0x006731A0`), which plain-deletes its nodes rather than
returning them to a pool.

## The GlobalData network block, corrected 2026-08-29

Every offset this file gave for the network timing block was one slot low. The
INI parse table settles it: each row is 16 bytes and the field offset is the
FOURTH dword, not the third.

Confirmed three independent ways, after a challenge that the block was shifted
one slot: (1) the INI parse table's fourth dword maps seven names to seven
consecutive offsets in order; (2) the retail imm32 initialisers match Zero Hour's
documented defaults exactly and in order -- 500 / 20 / 5000 / 60000 / 15000 at
`+0xCAC` / `+0xCB8` / `+0xCBC` / `+0xCC0` / `+0xCC4`; (3) the semantics fit
(a 60-second compiled player timeout, a 15-second disconnect-screen notice); and (4) the
def-use scan later in this file, which counts TEN reads of `+0xCB4` and ZERO of
`+0xCB8` -- a field named KeepAliveDelay that is never read is exactly what
"parsed, never read" means, and a live stall tolerance is not. BFME
preserves Zero Hour's field ORDER and spacing here and drops nothing, so any
derivation that assumes a dropped member is working from pins one slot low.

There are **three** layers, not two, and a value can change at either of the
last two:

| Offset | Field | Compiled `imm32` | `ini.big` | `_patch222.big` | **Shipped** |
| --- | --- | --- | --- | --- | --- |
| `+0xCA4` | `NetworkFPSHistoryLength` | 30 | 30 | 38 | **38** |
| `+0xCA8` | `NetworkLatencyHistoryLength` | 200 | 200 | 200 | 200 |
| `+0xCAC` | `NetworkRunAheadMetricsTime` | 500 | 5000 | 60000 | **60000** |
| `+0xCB0` | `NetworkCushionHistoryLength` | 10 | 10 | 120 | **120** |
| `+0xCB4` | **`NetworkRunAheadSlack`** | 10 | 10 | 10 | **10** |
| `+0xCB8` | `NetworkKeepAliveDelay` | 20 | 20 | 360 | **360** |
| `+0xCBC` | `NetworkDisconnectTime` | 5000 | **15000** | 15000 | **15000** |
| `+0xCC0` | `NetworkPlayerTimeoutTime` | 60000 | 60000 | 100000 | **100000** |
| `+0xCC4` | `NetworkDisconnectScreenNotifyTime` | 15000 | 15000 | 30000 | **30000** |

**Six of nine differ from their compiled default, the largest by 120×.** Read
the shipped value with `tools/ini_value.py`, which extracts
`Data/INI/GameData.ini` from both archives and applies the game's load order. It
needs no running game.

Two details the three-column view exposes that a two-column one hides.
`NetworkDisconnectTime` is raised to 15000 by **`ini.big` itself** — the patch
leaves it alone — so "the patch archive overrides everything" is not the rule; a
base-archive value can differ from the binary all by itself.
`NetworkRunAheadMetricsTime` moves at *both* layers, 500 → 5000 → 60000.

Cross-checked two ways: the `+0xCB4` row is 9,984 live reads taken inside three
matches by `netlat_discard`, and `+0xCB8`/`+0xCBC`/`+0xCC0` were read from live
client memory in a parallel session. Archive and process agree on all four.

**Quote the shipped value for any behavioural claim.** This project published
wrong numbers twice from the compiled column, both read correctly out of the
image and both wrong about the game: "voted out after 60 seconds" was wrong by
forty, and dividing a stall by the compiled 5000 ms disconnect time overstated
how close a player came to dropping by 3×.

**The identification argument is unaffected.** It rests on the compiled
initialisers matching Zero Hour's declaration order, which they do, and an INI
override moves a value, never a field. That is why the compiled column is kept:
it proves *which* field this is, and the shipped column says what it *does*.

**This generalises past the network block.** 378 GlobalData fields are
INI-parseable, so for any of them a disassembled `imm32` is a starting point and
not an answer. Anywhere in this repository that quotes a GlobalData constant as
behaviour, check it with `tools/ini_value.py` first.

`NetworkRunAheadSlack` is written at `0x00795F79` (value 2) or `0x00795F94`
(value 5) -- but **neither write executes in a normal match**. Both are gated on
the flags at `0x012ED4E5`/`0x012ED4E6`, and those are DEBUG CRC MODES: the
function that sets `0x012ED4E5` at `0x00461313` also ORs `0x10000` into the
flags word at `0x012A6FA0` and handles the strings `"debug.add l + NETWORK_CRC"`
and `"Do not specify both -deepCRC and -liteCRC in your commandline arguments."`
So those two values apply only under `-deepCRC`/`-liteCRC`.

The runtime value comes from the INI row (parse table at `0x01078668`, field
offset `+0xCB4`) and is **10** — `NetworkRunAheadSlack = 10` in `GameData.ini`
inside `ini.big`. At 5 Hz that is exactly 2000 ms, the same as retail's
`m_retryTime`, so the staleness cutoff, the router stall threshold and the
send-queue retention horizon all coincide with the retry interval. Any argument that depends on slack being 2 or 5 specifically
is unsupported.

It is a FRAME count, not milliseconds, and it is the router's stall tolerance:
`hasPacketRouterFrameStall` returns true -- freezing every seat -- as soon as any
active player satisfies `m_playerLatestFrame[i] + slack < currentFrame`. So a
guest frozen for longer than `slack * 200 ms` drags the router down with it,
which is why router freezes appear at all in the loss captures and why they
nearly vanish when the guest's freezes are shortened.

## Corrections to earlier notes in this file

* `0x00655360` and `0x006386F0` are **GameSpy persistent-storage serialization**
  (`\wins%d\%d`, `\desyncs%d\%d`), not the lockstep desync reporter. The real
  desync writer is `0x00065470`, which recomputes `GameLogic::getCRC`, compares
  it against a stored value, and on mismatch formats `CLIENT_DESYNC_%s.txt` and
  "Desync detected on frame %d on %u-%u-%u %u:%u:%u". Its only caller is
  `0x0006B910`.
* The `0x0080E000`-`0x0081A000` band is EA's DirtySock middleware -- `commudp`,
  `commtcp`, `protoadvt`, `NetGameUtil`, `comm/datamodem` -- with no counterpart
  in the Zero Hour reference. It carries the GameSpy/online transport, not the
  lockstep path, which still runs through SAGE's own `udp.cpp`.
* `NetCommandList::reset` was pointed at ILT thunk `0x00015479`, which jumps to
  `0x0040AD80`, a different function. Retail's call sites reach the real body at
  `0x006731A0` through thunk `0x0000B9CE`.
* `ConnectionManager::sendFrameDataToPlayer` (`0x00664D20`, two arguments) only
  raises a per-player watermark at `+0x12060`. The three-argument resend that
  actually re-sends stored commands is a different function, `0x00664B40`,
  recorded here as `resendFrameRangeToPlayer`.

## Work plan

1. DONE: unblock targeted ZH sweeps for the GameNetwork files with minimal
   compile shims.
2. DONE: land the first byte-verified `ConnectionManager` and `Network` rows.
3. DONE: prove that the needed path is BFME-native enough that ZH is a search
   map, not the source of truth.
4. DONE: recover the native dispatcher boundary and name the remaining wrapper
   fields before attempting any patch design.
5. DONE: rule out the ZH `NetRunAhead*` command classes for BFME command types
   `6` and `7`.
6. DONE: match the first BFME timing/readiness gates that consume
   `NetworkPlayerTimeoutTime`, `NetworkKeepAliveDelay`, and
   `NetworkDisconnectScreenNotifyTime`.
7. DONE: trace the BFME frame scheduler end to end. Both halves are matched --
   the router publishes the ceiling in `sendFrameInfo` on a
   `QueryPerformanceFrequency / 5` quantum driven by `update`, and clients raise
   theirs in `processIncomingCommand` case 3. `getFrameAdvanceCount` at native
   slot `+0x3C` is the gate that reads it.
8. NEXT: the pieces around the scheduler that are still unclaimed -- the desync
   writer at `0x00065470` and its caller `0x0006B910`, `GameLogic::getCRC`
   (matched only as a MASM dump), and the remaining unnamed bodies in
   `0x00660000`-`0x00672000`, most of which are GameSpy/lobby rather than
   lockstep.

## Non-goals

- Do not lower run-ahead values here.
- Do not add an opt-in patch profile here.
- Do not change matched source away from the original BFME behavior.

---

# The scheduler, decoded (2026-08-02)

`getFrameAdvanceCount` (0x00681F70, vtable +0x3C) is the whole delay. It is still
`__declspec(naked)` assembly in our tree, so nobody had read it. Decoded:

```
int BFMENativeNetwork::getFrameAdvanceCount()
{
    if (m_state(+0x0C) != 1)          return 1;      // not in a network game: free-run

    if (this->vtable[0x8C]())         goto quantum;  // <-- SELECTOR, still unidentified

    if (TheGameLogic->getFrame() == 0) return 1;

    if (!m_stallFlag(+0x28)) {                        // first tick of a stall
        g_stallStart(0x12F7718) = timeGetTime();
        m_stallFlag(+0x28) = 1;
    }

    allowance = m_conMgr(+8)->m_frameCeiling(+0x1205C) - TheGameLogic->getFrame() + 1;

    if (allowance > 0) {
        if (areFrameCommandsComplete(curFrame, FALSE)) {   // 0x006633E0
            m_stallFlag(+0x28) = 0;
            return allowance;                              // <-- the release
        }
        this->vtable[0x24](FALSE);
        return 0;                                          // commands missing: hold
    }
    ... bookkeeping on 0x12F7728, returns allowance ...

quantum:                                                   // the 200ms path
    if (m_conMgr->hasPacketRouterFrameStall()) {           // 0x00664260
        m_accum(+0x20/+0x24) = 0;
        return 0;
    }
    QueryPerformanceCounter(&now);                         // [0x1358EB4]
    m_accum += now - m_lastCounter(+0x18/+0x1C);
    m_lastCounter = now;

    quantum = m_freq(+0x10/+0x14) / 5;                     // __alldiv, divisor 5
    if (m_accum < quantum) return 0;                       // not yet
    m_accum -= quantum;
    if (m_accum > quantum * 2) { g_overrun(0x12F7724)++; m_accum = 0; }  // catch-up clamp
    g_lastAdvance(0x12F771C) = timeGetTime();
    return 1;                                              // exactly ONE frame
}
```

`m_freq` really is the performance frequency: `construct` (0x006818D4) calls
[0x1358EB8] then [0x1358EB4] -- QueryPerformanceFrequency then
QueryPerformanceCounter -- storing them at +0x10/+0x14 and +0x18/+0x1C.

So on the quantum path the caller is released **one logic frame per 200ms**, and
on the normal path it is released `ceiling - currentFrame + 1` frames gated on
`areFrameCommandsComplete`. Nothing here consults ping, which is why the delay
does not shrink on a LAN.

## The selector is isPacketRouter -- so the host paces the world at 5Hz

Virtual slot +0x8C resolves to `?isPacketRouter@Network@@UAE_NXZ` (0x00681B20,
25 bytes) through the vtable at 0x00D1A968. The call at 0x00681F8B is a virtual
call on `this` (mov eax,[esi]; mov ecx,esi; call [eax+0x8C]), so the branch reads:

    if (isPacketRouter()) -> quantum path (one logic frame per 200ms)
    else                  -> ceiling path (ceiling - currentFrame + 1)

The packet router therefore advances its own logic at exactly **5 frames per
second**, and every client is clamped to a ceiling that only the router
publishes. No client can outrun it, so the router's 5Hz is the whole game's
logic rate in a network game, and the resulting command latency is a flat ~200ms
that does not move with ping. That is the delay.

The fix is the literal 5 in `m_freq / 5`. It is not reachable today because this
body is still `__declspec(naked)` assembly; converting getFrameAdvanceCount to
real C++ is the prerequisite, and it is a single constant afterwards.

Two things to respect when changing it:

  - the catch-up clamp discards the accumulator when it exceeds two quanta, so a
    smaller quantum makes that clamp fire more readily under load;
  - hasPacketRouterFrameStall still gates the path on
    m_playerLatestFrame[i] + NetworkRunAheadSlack, so a faster router raises the
    rate at which a laggard trips the stall. That is the coupling to watch on
    the frame-time p99 gate, and it is the one place NetworkRunAheadSlack
    becomes relevant after the change even though it is irrelevant before it.

# The nine network INI fields: six are dead

The GameData block parses nine network timing fields. A def-use scan -- decode
each function, track the register loaded from TheWritableGlobalData (0x012ED5C8),
let callee-saved registers survive calls, then look for [reg+offset] -- gives:

| INI key | offset | reads | verdict |
|---|---|---|---|
| NetworkFPSHistoryLength | 0xCA4 | 0 | parsed, never read |
| NetworkLatencyHistoryLength | 0xCA8 | 0 | parsed, never read |
| NetworkRunAheadMetricsTime | 0xCAC | 0 | parsed, never read |
| NetworkCushionHistoryLength | 0xCB0 | 0 | parsed, never read |
| NetworkKeepAliveDelay | 0xCB8 | 0 | parsed, never read |
| NetworkDisconnectScreenNotifyTime | 0xCC4 | 0 | parsed, never read |
| NetworkRunAheadSlack | 0xCB4 | 10 | live |
| NetworkDisconnectTime | 0xCBC | 3 | live |
| NetworkPlayerTimeoutTime | 0xCC0 | 4 | live |

`NetworkCushionHistoryLength` being dead rules out an adaptive cushion layer.

`NetworkRunAheadSlack` is NOT a lead. It is a stall tolerance:
`hasPacketRouterFrameStall` returns TRUE when any
`m_playerLatestFrame[i] + slack < TheGameLogic->getFrame()`, and its only caller
is the scheduler. Before frame 5 the slack is a hardcoded 3. In
`Connection::doSend` the same field is a retention window -- drop queued commands
more than `slack` frames stale. Neither use shortens command-to-execution
latency, so varying it in INI cannot fix the delay.

# Delay-path functions still needing C++

## What the command-type sweep turned up

Working the packet path end to end named every remaining `NetCommandMsg`
subclass, and three of them matter here.

**Type 22 is the per-player frame ratios.** The shim's enum leaves 22 and 23
unnamed and files them under "disconnect menu"; 22 is nothing of the sort. Its
command class carries eight `Int`s, one per slot, and
`BFMEConnectionManager::computePlayerFrameRatios` (`0x00666000`) is what fills
them. `ConstructNetCommandMsgFromRawData` tests for it *third*, immediately
after FRAMEINFO and well before any disconnect type -- and that chain is ordered
by frequency, so this is per-frame traffic, not lobby traffic. Reader
`0x00678AA0`, setter `0x00673A50`, both matched.

**Types 5 to 9 are BFME's, and two of them bypass the packet router.**

| type | class | reader |
|---|---|---|
| 5 | `BFMENetRequestGameSpyStatsAuthKeyCommandMsg` | `0x0067EB80` |
| 6 | `BFMENetGameSpyStatsAuthKeyCommandMsg` | `0x0067EC70` |
| 7 | `BFMENetRequestPlayerLeaveCommandMsg` | `0x00679300` |
| 8 | `BFMENetInformPlayerLeaveFrameCommandMsg` | `0x00679250` |
| 9 | `BFMENetRequestFrameDataCommandMsg` | `0x00679390` |

`CommandRequiresDirectSend` (`0x00682E80`) is the reference's list minus
FRAMERESENDREQUEST plus all five of these. Types 8 and 9 -- inform-player-leave
-frame and request-frame-data -- therefore go straight to their destination
rather than through the router, which is the only frame-path traffic in the game
that does.

**The acks carry an execution frame the reference's do not.** All three ack
classes have a BFME-only `m_originalExecutionFrame` at `+0x20`, and the readers
write it straight to the field -- there is no setter for it anywhere in the
image. So an ack tells the sender not just which command was seen but which
frame it was bound to.

**FRAMEINFO's payload is three dwords**, and the reader (`0x006789E0`) pins
them: `+0x1C` the sender's frame, `+0x20` the value the receiver copies into
`ConnectionManager+0x120A0`, `+0x24` the frame's command count. The count starts
at `-1`, the same "not yet known" sentinel the base uses for `m_executionFrame`.

**`NetCommandRef::m_relay` is at `+0x0C`, settled.** The dispatcher inlines
`setRelay` and stores a byte to `+0x0C`; the constructor at `0x00676240` zeroes
the same offset. The ledger row `?setRelay@NetCommandRef@@QAEXE@Z` at
`0x003BC6B0`, which stores to `+0x10`, is a fold onto some other class.

### doSend drops stale commands, and RunAheadSlack is the horizon

`Connection::doSend` (`0x00661F10`) does not retry an ack-pending command
forever. After the retry bookkeeping it reads the command's frame -- the frame
field for a FRAMEINFO command, the execution frame for anything else -- and if

    TheWritableGlobalData->[+0xCB4] + frame < TheGameLogic->getFrame()

it drops the command from the queue instead of keeping it for another round.

`+0xCB4` is **NetworkRunAheadSlack**, not NetworkKeepAliveDelay: the INI offset
table puts KeepAliveDelay at `+0xCB8` with zero reads, and RunAheadSlack at
`+0xCB4` with ten. Two places in this file previously said otherwise and are now
corrected. So the same staleness horizon that makes
`hasPacketRouterFrameStall` declare a router stall also decides when a queued
command is too old to keep sending -- which makes RunAheadSlack a send-path knob
as well as a stall tolerance, and worth varying in a sweep.

Three other BFME changes in the same function: a clock-wrap guard that pulls
`m_lastTimeSent` back if the clock goes backwards, so the frame-grouping gate
cannot lock a connection out for 49 days; the destination address copied out of
the Connection as an eight-byte struct rather than through a user object; and a
parameter the reference's `doSend` has no counterpart for, which stops the loop
after five packets when set.

### Ledger corrections made along the way

Three of the four heuristic `??0NetCommandMsg@@QAE@XZ` pins in `symbols.csv`
pointed at other classes' constructors, and one at a body outside the family
entirely. Those extra candidates had let six reader names settle on
`GameEngine::createMessageStream`'s body at `0x0006C090`, `readProgressMessage`
on `readPlayerLeaveMessage`'s, and two disconnect readers on
`readDestroyPlayerMessage`'s. Every reader is now identified by the constructor
it actually calls, which is checkable rather than inferred.
`readPacketRouterQueryMessage`, `readPacketRouterAckMessage` and
`readFrameResendRequestMessage` are marked absent-from-retail: BFME has no such
command types, so there is no body for them to claim.

Generated from the call graph: two levels of callees from the scheduler
(0x00681F70), the frame-pacing status (0x00682160), the stall detector
(0x00664260), both runtime ceiling writers (0x00665D10, 0x0066A3F0), the
readiness gate (0x006633E0), Connection::doSend (0x00661F10), the frame ring
(0x00670A30) and the connection-manager lifecycle -- filtered to what is still
unnamed, asm-only, or claimed only by a thunk row.

**88 of 139 matched, 7248 of 15498 bytes** as of the last sweep. What is left
splits three ways, and the split matters because two of the three cannot be
closed by writing better C++:

  * **~15 are compiler runtime.** `0x009F7210` is `__allmul` and `0x009F70E0`
    is `__alldiv` -- hand-written CRT assembly that MSVC *calls* for 64-bit
    arithmetic and never emits from source, so no C++ produces them.
    `0x009F7E88`, `0x009F6F2E` and `0x009F7EC3` are `__ehvec_*` unwind helpers,
    same story. `0x0082AD50`, `0x0082DA10`, `0x0082C920` and `0x000800C0` are
    STLport `__node_alloc` internals, and `0x006651C0`, `0x00665120`,
    `0x00665170`, `0x00667B50`, `0x006652B0` and `0x00669560` are STL map and
    list internals -- those are real C++, but they are STLport's, not the
    game's.

  * **~10 are blocked on a register or stack-slot tie-break.** Their bodies are
    written and instruction-for-instruction correct; what differs is which
    register or frame slot MSVC picks. `Connection::doSend`,
    `ConstructNetCommandMsgFromRawData`, `NetPacket::getCommandList`, both
    NetPacket constructors and the four by-value-string readers are all in this
    state. Each carries a note recording exactly what was ruled out.

  * **the rest are game code needing a name.** The behaviour is legible from the
    image but the symbol is not, and the repo's convention for that -- an
    offset- or behaviour-derived name, as in `copyState6C@BFMENetwork` -- is
    what these need.

Regenerate with the call-graph walk described above; this is the complete list,
not a sample.

**139 functions, 15498 bytes.** Regenerate with the call-graph walk described
above; this is the complete list, not a sample.

| bytes | addr | state | name |
|---|---|---|---|
| 1380 | `0x680980` | unnamed |  |
| 937 | `0x67EE40` | unnamed |  |
| 750 | `0x66C3B0` | asm-only | `?updateDisconnectStatus@DisconnectManager@@IAEXPAVConnectionManager@@@Z` |
| 608 | `0x673200` | asm-only | `?addMessage@NetCommandList@@QAEPAVNetCommandRef@@PAVNetCommandMsg@@@Z` |
| 581 | `0x661F10` | unnamed |  |
| 502 | `0x6624A0` | unnamed |  |
| 448 | `0x670A30` | unnamed |  |
| 433 | `0x67E3F0` | unnamed |  |
| 284 | `0x67E8C0` | unnamed |  |
| 272 | `0x67E760` | unnamed |  |
| 261 | `0x67EA30` | unnamed |  |
| 256 | `0x676890` | unnamed |  |
| 256 | `0x66A030` | unnamed |  |
| 255 | `0x6655C0` | unnamed |  |
| 251 | `0x67EC70` | unnamed |  |
| 251 | `0x67E620` | unnamed |  |
| 215 | `0x678AA0` | unnamed |  |
| 204 | `0x669B50` | unnamed |  |
| 187 | `0x67EB80` | unnamed |  |
| 187 | `0x66B2D0` | asm-only | `?sendKeepAlive@DisconnectManager@@IAEXPAVConnectionManager@@@Z` |
| 174 | `0x679730` | unnamed |  |
| 171 | `0x9D2AB0` | unnamed |  |
| 170 | `0x9F70E0` | unnamed |  |
| 169 | `0x82C920` | unnamed |  |
| 164 | `0x683830` | unnamed |  |
| 162 | `0x82E540` | asm-only | `?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z` |
| 156 | `0x6645B0` | unnamed |  |
| 153 | `0x6789E0` | unnamed |  |
| 152 | `0x678920` | unnamed |  |
| 152 | `0x678860` | unnamed |  |
| 152 | `0x6787A0` | unnamed |  |
| 150 | `0x6658F0` | unnamed |  |
| 130 | `0x679390` | unnamed |  |
| 130 | `0x679250` | unnamed |  |
| 126 | `0x669960` | unnamed |  |
| 121 | `0x669560` | unnamed |  |
| 114 | `0x678F10` | unnamed |  |
| 112 | `0x50EF20` | unnamed |  |
| 108 | `0x6794D0` | unnamed |  |
| 108 | `0x679440` | unnamed |  |
| 108 | `0x679300` | unnamed |  |
| 105 | `0x86AF90` | unnamed |  |
| 103 | `0x679650` | unnamed |  |
| 96 | `0x6688D0` | unnamed |  |
| 91 | `0x662270` | unnamed |  |
| 87 | `0x66BD10` | thunk-only | `?processDisconnectVote@DisconnectManager@@IAEXPAVNetCommandMsg@@PAVConnectionManager@@@Z` |
| 86 | `0x682E80` | unnamed |  |
| 86 | `0x679010` | unnamed |  |
| 86 | `0x678FA0` | unnamed |  |
| 86 | `0x678D40` | unnamed |  |
| 86 | `0x678CD0` | unnamed |  |
| 85 | `0x82E5F0` | asm-only | `?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z` |
| 82 | `0x6652B0` | unnamed |  |
| 75 | `0x675CE0` | unnamed |  |
| 75 | `0x675C50` | unnamed |  |
| 75 | `0x675A20` | unnamed |  |
| 75 | `0x6380F0` | unnamed |  |
| 75 | `0x638060` | unnamed |  |
| 74 | `0x9F6EE4` | asm-only | `??_L@YGXPAXIHP6EX0@Z1@Z` |
| 74 | `0x6731A0` | unnamed |  |
| 70 | `0x66BFE0` | unnamed |  |
| 69 | `0x673840` | unnamed |  |
| 68 | `0x673740` | unnamed |  |
| 62 | `0x8543B0` | unnamed |  |
| 62 | `0x6832C0` | unnamed |  |
| 61 | `0x667B50` | unnamed |  |
| 61 | `0x50E5A0` | unnamed |  |
| 60 | `0x6651C0` | unnamed |  |
| 59 | `0x9F7E88` | unnamed |  |
| 58 | `0x0800C0` | unnamed |  |
| 55 | `0x9D2EB0` | unnamed |  |
| 54 | `0x385570` | unnamed |  |
| 53 | `0x6738A0` | unnamed |  |
| 53 | `0x665170` | unnamed |  |
| 53 | `0x665120` | unnamed |  |
| 52 | `0x9F7210` | unnamed |  |
| 51 | `0x6739B0` | unnamed |  |
| 50 | `0x9D39A0` | unnamed |  |
| 49 | `0x6776C0` | unnamed |  |
| 49 | `0x674030` | unnamed |  |
| 49 | `0x105750` | unnamed |  |
| 48 | `0x675BE0` | unnamed |  |
| 48 | `0x674260` | unnamed |  |
| 47 | `0x6737A0` | unnamed |  |
| 45 | `0x676240` | unnamed |  |
| 45 | `0x6759B0` | unnamed |  |
| 45 | `0x673B10` | unnamed |  |
| 45 | `0x673AA0` | unnamed |  |
| 42 | `0x673B80` | unnamed |  |
| 42 | `0x065250` | unnamed |  |
| 40 | `0x662CE0` | unnamed |  |
| 38 | `0x6811B0` | unnamed |  |
| 37 | `0x675610` | unnamed |  |
| 37 | `0x675450` | unnamed |  |
| 37 | `0x6735D0` | unnamed |  |
| 35 | `0x670640` | unnamed |  |
| 33 | `0x682E50` | unnamed |  |
| 32 | `0x675CB0` | unnamed |  |
| 32 | `0x675C20` | unnamed |  |
| 32 | `0x6759F0` | unnamed |  |
| 32 | `0x675310` | unnamed |  |
| 32 | `0x6751E0` | unnamed |  |
| 32 | `0x638030` | unnamed |  |
| 32 | `0x61E8B0` | unnamed |  |
| 24 | `0x9F6F2E` | unnamed |  |
| 18 | `0x9F6E26` | thunk-only | `_atexit` |
| 18 | `0x50E5F0` | unnamed |  |
| 17 | `0x9F7EC3` | unnamed |  |
| 16 | `0x676550` | unnamed |  |
| 12 | `0x674090` | unnamed |  |
| 12 | `0x673A10` | unnamed |  |
| 12 | `0x673910` | unnamed |  |
| 12 | `0x673800` | unnamed |  |
| 10 | `0x6742D0` | unnamed |  |
| 10 | `0x6742C0` | unnamed |  |
| 10 | `0x6740B0` | unnamed |  |
| 10 | `0x673B60` | unnamed |  |
| 10 | `0x673B00` | unnamed |  |
| 10 | `0x673A30` | unnamed |  |
| 10 | `0x673930` | unnamed |  |
| 10 | `0x673820` | unnamed |  |
| 8 | `0x82DA10` | unnamed |  |
| 8 | `0x6765B0` | unnamed |  |
| 8 | `0x664D80` | unnamed |  |
| 8 | `0x383730` | unnamed |  |
| 7 | `0x82AD50` | unnamed |  |
| 5 | `0x674080` | unnamed |  |
| 5 | `0x673FF0` | unnamed |  |
| 4 | `0x674300` | unnamed |  |
| 4 | `0x6742F0` | unnamed |  |
| 4 | `0x6741E0` | unnamed |  |
| 4 | `0x6741D0` | unnamed |  |
| 4 | `0x6740A0` | unnamed |  |
| 4 | `0x674010` | unnamed |  |
| 4 | `0x673F90` | unnamed |  |
| 4 | `0x673F80` | unnamed |  |
| 4 | `0x673CB0` | unnamed |  |
| 4 | `0x673600` | unnamed |  |
| 0 | `0x665350` | unnamed |  |

# BFME de-pooled the whole netcode object graph

Six classes drop the reference's `MemoryPoolObject` base. This is not cosmetic:
against the reference's base the compiler emits an SEH frame retail does not
have, and every field shifts down four bytes because there is no vptr.

| class | evidence |
|---|---|
| `FrameData` | 20-byte stride, m_frameCommandCount at +0 |
| `FrameDataManager` | destructor stores a vptr but carries no SEH frame |
| `NetCommandList` | -- |
| `NetCommandRef` | m_msg at +0, m_next/m_prev at +4/+8 |
| `NetPacket` | constructor stores a vptr, no base constructor call |
| `Connection` | plain Int at this+0, not a vptr |

They still have vtables where the reference had them; only the pool base is
gone. This was the blocker on FrameDataManager and it will be the blocker on
anything else in that graph.

# The egress pacer is dead code

`Connection::doSend` gates every send on

    if ((curtime - m_lastTimeSent) < m_frameGrouping) return 0;

with `m_frameGrouping` at Connection+0x344 and `m_lastTimeSent` at +0x348. Two
sites initialise the field to 1 (0x00661E99, 0x006623E2). The only code that can
change it is `ConnectionManager::setFrameGrouping` (0x00663530, landed), whose
eight unrolled stores are the only other writes to +0x344 in the image -- and an
exhaustive scan of every section for a call or jump reaching either that body or
its thunk at 0x00049DB4 finds exactly one reference: the thunk's own jump into
the body. **Nothing calls the thunk.**

Reachability VERIFIED 2026-08-29, not inferred: `0x00A63530` has no direct
callers, its single jmp thunk at `0x00449DB4` has no callers, and its address is
never stored as a dword anywhere in the image, so it is not reached through a
vtable either. It is unreachable code. That is what makes RotWK's delay fix
non-portable in a stronger sense than "the field is initialised low" -- the
throttle RotWK removes cannot be set in BFME 1 at all.

So m_frameGrouping stays at 1ms and that gate never fires. There is no second
delay source to remove. The function also halves the interval when the machine
is the packet router -- BFME-only, and dead along with the rest of it.

# Every writer of the frame ceiling

`ConnectionManager+0x1205C` has exactly five writers, and only two carry runtime
semantics:

| address | function | kind |
|---|---|---|
| 0x006654F5 | reset at 0x00665350 | lifecycle |
| 0x00669126 | `init` | lifecycle |
| 0x0066969E | `construct` | lifecycle |
| 0x00665E45 | `sendFrameInfo` | **runtime** -- router publishes its own frame |
| 0x0066A4BE | `processIncomingCommand` | **runtime** -- client raises it from FRAMEINFO |

Nothing else can move the ceiling.

# Connection layout

| offset | field | pinned by |
|---|---|---|
| 0x000 | m_id / quit state, compared to -1 | doSend, isPlayerConnected |
| 0x004 | m_quitTime, +0x7530 (30s) flush timeout | doSend |
| 0x008 | m_transport | doSend passes it to queueSend |
| 0x00C | m_addr | copied into the packet |
| 0x010 | m_port | copied into the packet |
| 0x018 | m_netCommandList | isQueueEmpty, doSend |
| 0x01C | m_retryTime | doSend retransmit test |
| 0x344 | m_frameGrouping | the dead egress gate |
| 0x348 | m_lastTimeSent | same |
| 0x350 | m_numRetries | doRetryMetrics |
| 0x354 | m_retryMetricsTime | 10-second window |

Retransmit: a queued command is resent when
`(curtime - timeLastSent) > m_retryTime`, or immediately if timeLastSent is -1.
`doRetryMetrics` is inlined into doSend on a 10-second window.

`doSend` also takes a Bool argument that caps it at five packets per call, and
drops queued commands whose execution frame plus `NetworkRunAheadSlack` has
fallen behind TheGameLogic's frame.

# NetPacket layout, and the address struct

sizeof is 0x200, which is what doSend hands operator new.

| offset | field |
|---|---|
| 0x000 | vptr |
| 0x004 | m_packet[0x1DC] (0x1DC == 476 == MAX_PACKET_SIZE) |
| 0x1E0 | m_packetLen |
| 0x1E4 | m_addr |
| 0x1E8 | m_port |
| 0x1EC | m_numCommands |
| 0x1F0 | m_lastCommand, then m_lastFrame, m_lastCommandID, m_lastPlayerID, m_lastCommandType, m_lastRelay |

m_addr and m_port are adjacent in BFME and separated in the reference, and
doSend passes `&packet->m_addr` straight into `Transport::queueSend` -- so that
pair IS the address struct queueSend takes, embedded in the packet rather than
built on the stack.

`NetPacket::init` assigns the pair as a whole struct (a dword at +0x1E4 and a
dword at +0x1E8 out of an eight-byte stack temp), so it carries two bytes of
tail padding and is **not** packed. The transport shim declares TransportAddress
under `#pragma pack(1)` at six bytes, which is wrong; nothing landed depends on
it, since Transport::init only reads through a pointer.

# BFMENativeNetwork vtable (0x00D1A968)

| slot | body | name |
|---|---|---|
| +0x24 | 0x00681930 | called when commands are incomplete |
| +0x3C | 0x00681F70 | `getFrameAdvanceCount` |
| +0x40 | 0x00682160 | `getFramePacingStatus` |
| +0x8C | 0x00681B20 | `isPacketRouter` -- selects the 200ms path |

# Mechanical gotcha: double incremental-link thunks

Retail's call sites reach `FrameData::init` through **two** hops,
0x0003BB6F -> 0x00670220 -> 0x00670170. `build_call_thunks` follows one, so the
call resolved to the body and three bytes of REL32 stayed wrong until the outer
thunk was pinned explicitly in reverse/symbols.csv.

# The NetCommandMsg constructor family (15 of the unnamed entries)

The small unnamed functions clustered in 0x673000-0x678000 are not miscellaneous:
they are the NetCommandMsg subclass constructors, and each one identifies itself.
Every body stores its class vptr and stamps its own NetCommandType into m_type at
+0x14 -- the same offset CommandRequiresAck reads and Connection::doSend tests for
FRAMEINFO. Reading the stamped constant off each constructor names it:

| addr | bytes | type stamped | class |
|---|---|---|---|
| `0x673840` | 69 | 1 ACKBOTH | `NetAckBothCommandMsg` |
| `0x6738A0` | 53 | 1 ACKBOTH | `NetAckBothCommandMsg` |
| `0x673AA0` | 45 | 10 PLAYERLEAVE | `NetPlayerLeaveCommandMsg` |
| `0x673B10` | 45 | 11 DESTROYPLAYER | `NetDestroyPlayerCommandMsg` |
| `0x673B80` | 42 | 12 KEEPALIVE | `NetKeepAliveCommandMsg` |
| `0x673BD0` | 42 | 24 DISCONNECTKEEPALIVE | `NetDisconnectKeepAliveCommandMsg` |
| `0x673C20` | 48 | 25 DISCONNECTPLAYER | `NetDisconnectPlayerCommandMsg` |
| `0x673CD0` | 48 | 26 DISCONNECTVOTE | `NetDisconnectVoteCommandMsg` |
| `0x673D60` | 45 | 15 PROGRESS | `NetProgressCommandMsg` |
| `0x673DD0` | 64 | 18 WRAPPER | `(wrapper: no ??2 row seen)` |
| `0x674030` | 49 | 21 FILEPROGRESS | `NetFileProgressCommandMsg` |
| `0x6740C0` | 45 | 27 DISCONNECTFRAME | `NetDisconnectFrameCommandMsg` |
| `0x674310` | 45 | 28 DISCONNECTSCREENOFF | `NetDisconnectScreenOffCommandMsg` |
| `0x6750E0` | 45 | 13 DISCONNECTCHAT | `NetDisconnectChatCommandMsg` |
| `0x675210` | 48 | 14 CHAT | `NetChatCommandMsg` |

The class names are the ones already established in the ledger by the matched
`??2Net<X>CommandMsg@@SAPAXIW4...MagicEnum@0@@Z` allocation rows, so these are not
invented. Two constructors stamp ACKBOTH and share the vptr 0x0111A49C, so they
are two constructors of one class rather than two classes.

This also independently validates the NetCommandType numbering recovered from the
type-to-string mapper at 0x00683020: every stamped constant lands on the class you
would expect from its name.

Shape, from 0x006738A0 (53 bytes, ACKBOTH):

```
m_?(+0x04)  = 0
m_executionFrame(+0x08) = -1     // addNetCommandMsg reads +8 as the frame
m_?(+0x0C)  = 0
m_?(+0x10)  = 0   (word)
m_type(+0x14) = <the class's NetCommandType>
m_?(+0x18)  = same constant as m_type
vptr(+0x00) = <the class's vtable>
m_?(+0x1C)  = 0   (word)
m_?(+0x1E)  = 0   (byte)
m_?(+0x20)  = -1
```

Writing these needs the de-pooled NetCommandMsg base -- BFME de-pooled this graph
like the rest -- and the usual care over member declaration order, since the
compiler emits the stores in declaration order rather than the order above.

## BFME has no run-ahead, and the router relays late in its own frame period

Two structural facts read out of the retail exe on 2026-08-29, both of which
change what "the delay" is made of. Neither matches the Zero Hour reference.

**There is no run-ahead.** Zero Hour schedules a command `m_runAhead` frames into
the future (`getFrame() + m_runAhead`, initialised to 30). BFME does not:

* `sendLocalCommand` (`0x00A6478D`), router path: `executionFrame = max(currentFrame, 2)`
* `relayCommand` (`0x00A63121`), for an unbound guest command: `executionFrame = router's current frame`

So a command executes on the frame the **router** is on when it sees it. The
host's own input has essentially no scheduled delay, which is why the router seat
measures ~0.2 ms while a guest measures hundreds. A guest's delay is therefore
transit plus frame quantum, not a schedulable offset — there is no run-ahead
constant to lower, and looking for one is wasted effort.

It also explains why `034-framedrain` desynced. The router keeps binding arriving
commands to its current frame right up until it runs that frame, so the guest's
one-quantum lag is the entire ordering margin. Removing the lag removes the
margin.

**The router relays late in its frame period.** Measured across three captures
(150-300 ms round trip, ~2,300 relays each), as a phase within the router's own
200 ms logic-frame period:

| arm | p10 | p50 | p90 | share in the first 10% |
|---|---|---|---|---|
| s9-retail-1 | 0.17 | 0.75 | 1.00 | **0.0%** |
| s9-both-1 | 0.15 | 0.75 | 1.00 | **0.0%** |
| s9x-both400-1 | 0.26 | 0.62 | 1.00 | **0.0%** |

Not batching — a relay batched to the frame tick would pile up at phase 0, and
none do. The opposite: the router never relays in the first tenth of its period
and typically relays around three-quarters through, so a command arriving just
after a frame boundary waits most of a quantum before being passed on. The
binding frame is unaffected (it is bound to the frame the router is on either
way), so this does not change *which* frame a command lands on — it changes how
much of that frame remains for the guest to receive it and run.

**Candidate, not a finding — and now sized, which kills it.** The blackout is
real and independently reproduced (0.0% of 1623 router relays in the first tenth
of the period), but the mean phase is **0.590 against 0.500 for uniform**, so only
about **20 ms** is recoverable on a 225 ms quantum — not the ~100 ms first
estimated. That does not justify a detour in the router's hot loop. Recorded with
the number attached so nobody revives it believing it is bigger.

The original, over-large estimate: polling the network earlier in the router's
loop would relay commands up to ~100 ms sooner on average and would *increase* the
guest's ordering margin rather than reduce it, which is the safe direction.
Unquantified and unbuilt. Note the caution — this is a cadence change on the
relay side, and the send-side cadence change (`031-earlysend`) has a benefit that
replication has so far failed to distinguish from retail's own spread at
150 ms/3%. Do not assume a cadence fix is worth what it looks like on paper.

## Where a guest's remaining delay actually sits

Measured on the guest's own clock, so no cross-seat alignment is involved — the
error that produced the send-anchored-clock artifact earlier in this work.

| leg | retail | both400 |
|---|---|---|
| input → send (local) | p50 **173.4** p90 495.1 | p50 **191.7** p90 517.3 |
| send → next frame run | p50 0.1 p90 0.2 | p50 0.1 p90 95.8 |

Nearly all of the guest's controllable delay is **before the packet leaves the
machine**, and the send→run leg is ~0. Phases within the guest's own 200 ms frame
period say why:

| | input phase | send phase | gap between sends |
|---|---|---|---|
| retail | p50 **0.00** | p50 **1.00** | p50 173.2 |
| both400 | p50 0.00 | p50 1.00, **p10 0.50** | p50 191.3, **p10 34.8** |

Inputs are appended at the top of a frame period; the resulting network command
is sent at the end of it. That is the engine's message pipeline — a `GameMessage`
appended during one client update is translated to a network command by the
logic update that follows — and it costs most of a quantum.

**This bounds what any future latency work can win.** The transit and frame-wait
legs are structural (there is no run-ahead to shorten — see above), so the only
compressible leg is this local ~190 ms.

**An earlier revision of this paragraph said compressing it "reorders simulation
input". That is too strong and is corrected here.** A guest does not execute its
own command locally: it sends to the router, the router assigns an execution
frame and relays, and the guest executes only when the command comes back. That
is visible in the measurements — a guest's creation-to-run is 545-843 ms where
purely local execution would be ~200 ms. So sending a guest's command earlier is
a **transport-side** change. It does not reorder anything locally, because local
order is decided by the router's frame assignment, and that assignment is
authoritative and broadcast to every seat identically.

What it does change is *which* frame the command binds to — an earlier one. That
is the entire benefit, and it lands on all seats alike rather than on one.

So this is a real candidate rather than a dead end, with three caveats that have
to be discharged before anyone builds it:

* `031-earlysend` already flushes the connection earlier and moves only ~9% of
  sends, because it cannot send a command that has not been created yet. The
  lever is whatever creates the network command, not the flush.
* All ~16 callers of `sendLocalCommand` (`0x00A64740`, via thunk `0x0043F17A`)
  are internal protocol sends inside `ConnectionManager`. The game-command path
  has not been isolated, so the thing to hook is not yet identified.
* Every "obviously safe" change on this track has so far been wrong three times.
  The argument above is structural and untested, and `034-framedrain` had a
  structural argument too.

### A metric that measured the boundary instead of the effect

Recorded because it produced a confident, wrong, load-bearing number, and the
failure mode is easy to repeat.

To evaluate `031-earlysend` mechanically, a *phase* statistic was used: where a
send falls within the guest's own 200 ms frame period, and specifically the share
landing in the first half. It reported that retail put 0.0% of sends in the first
half and earlysend 8.3–9.5% — perfect separation across nine matches, which
looked like decisive evidence and was adopted by both sessions.

**It is degenerate at exactly the point that matters.** A send 0.2 ms *before* a
frame event has phase ~1.00; one 0.2 ms *after* has phase ~0.00. Same instant,
opposite ends of the bucket. Distance to the nearest frame event instead:

| arm | p10 | p50 | p90 | within 5 ms of a boundary |
|---|---|---|---|---|
| retail | −0.2 ms | −0.2 ms | −0.1 ms | **99.7%** |
| + earlysend | −65.8 ms | −0.2 ms | +87.8 ms | **15.8%** |

Retail pins 99.7% of sends to the frame tick and earlysend releases 84% of them.
The phase statistic reported that as "9% move" because it was measuring which
side of a tick the boundary noise fell on.

**What it cost.** From "9% of sends move by at most half a quantum" came a mean
saving of ~9 ms, and from that the conclusion that earlysend's effect was two
orders of magnitude below the noise floor and could never be resolved — an
argument for *stopping* measurement. The true effect is ~100 ms p50 and ~170 ms
p95, and it is disjoint at n=2 once measured against a baseline whose own spread
is not 700 ms.

**The metric that was right the whole time** was `held` — send minus command
creation, from `netlat.creation_to_run` — which read 86.9–96.1 ms in every retail
arm and 0.1 ms in every earlysend arm, in every capture, from the beginning. It
was looked past by both sessions because it was labelled a validity check rather
than a result.

The distinction that separates them: `held` is anchored to the **command's own
creation**, while phase is anchored to a **frame boundary the effect is defined
relative to**. Anchoring a measurement to the thing an intervention moves is how
this class of error is avoided.

### Two ways this measurement goes wrong, both hit in practice

* **Bucketing by phase instead of by distance.** See above — degenerate at the
  frame boundary, understates an 84% effect as 9%.
* **Not filtering to game commands.** A guest emits ~1326 per-tick frame-info
  sends (type 3) against ~336 game commands (type 4). Frame info is pinned to the
  tick by construction and cannot move, so an unfiltered measurement dilutes the
  effect 4:1 and reports ~82% pinned for an arm that is 84% *released*.

**And the reason the first error survived a review.** A second session checked
the ~9 ms figure for arithmetic consistency against the phase statistic and it
passed — 9% of sends times half a quantum genuinely is about 9 ms. What went
unchecked was whether the phase statistic measured what it claimed. *A
consistency check against a broken input reproduces the break*, and both parties
then hold the same wrong number with increased confidence.

## The "6x more polling" finding was the instrument, measured

Pre-registered before the data existed, in the batch script that collected it:
*"counters ~6x -> the effect is real and the hook merely observed it; counters
~1x -> THE 6x WAS THE INSTRUMENT, not 'the effect disappeared'; in between ->
real but amplified."* Recorded in advance precisely because the ~1x case is the
one most easily mis-told.

**It is ~1x.** Clean counters that only increment an integer and write nothing,
reported on a line already being emitted per logic frame:

| arm | seat | loops / frame | driver entries / frame |
|---|---|---|---|
| retail | router | 6.00 | 6.00 |
| retail | guest | 6.00 | 6.00 |
| + earlysend | router | 6.00 | 6.00 |
| + earlysend | guest | 6.00 | 6.00 |

Identical across arms and seats, p50 and p90. 6.00 is simply the ~30 Hz client
loop divided by the 5 Hz logic rate.

The earlier measurement — a guest reaching the frame driver 6x more often under
`031-earlysend` — came from `netlat_admit`, which wrote a **flushed line per
poll**. A seat that polls more pays more to be watched polling, and the cost
scales with the very ratio being measured. That arm wrote 19,349 lines against
its control's 3,239, and removing the hook moved the same retail arm from 8.5% to
3.2% net game time lost.

**So the guest's main loop is not slow, and never was.** Both seats iterate six
times per logic frame and enter the frame driver on every iteration. Any account
of guest lag that rests on the guest polling less often is describing the probe.
