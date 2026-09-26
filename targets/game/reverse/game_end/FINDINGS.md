# Game end: leave, quit, victory and results reporting

Goal: give BFME Arena the retail leave/quit state machine and the win-detection
and results path with every address machine-checked, so the quit freeze can be
measured on a LAN and the ladder results path switched on without guessing.
Addresses are RVAs unless marked VA. Every `0x` literal in this file is a row
in `targets/game/reverse/game_end/claims.csv`, `targets/game/reverse/functions.csv` or
`targets/game/reverse/symbols.csv`; `tools/tests/test_inventory.py` enforces that, checks
every claim against the retail image, and applies the patch rows to a copy.

## The answer: a routed leave handshake with three places to wait

BFME does not leave the way Zero Hour does. ZH's `quitGame` sends one direct
PLAYERLEAVE to every peer and tears down. BFME's `Network::quitGame` (vtable VA
`0x0111A968` slot `+0x78`, body `0x006822E0`) sends a **REQUESTPLAYERLEAVE**
(command type 7) to every peer, and only the packet router turns it into the
frame-synchronized **PLAYERLEAVE** (10) and **DESTROYPLAYER** (11) pair the
other machines execute. The leaver that called `quitGame` does not wait: it
posts `MSG_CLEAR_GAME_DATA` and is on the score screen a tick later. Three
machines can wait: (a) a leaver whose game ended while still in the in-game
state (the end-game timer, or any other poster of `MSG_CLEAR_GAME_DATA` while
`Network+0x0C == 1`), which asks the router for its own PLAYERLEAVE and has a
10 s fallback; (b) a leaving packet router, which holds its own leave until
every connected peer has reached the frame its PLAYERLEAVE executed on; (c)
the survivors of a router that quit, who hold a request the router never
answers and fall through to the DisconnectManager's timeout path. The
constants: 10 000 ms in `hasLeaveRequestTimedOut` (`0x00662E30`), 30 000 ms in
`Connection::doSend` (`0x00661F10`; the `add ecx, 0x7530` at `0x00661F57`),
and the INI-driven `NetworkPlayerTimeoutTime`. Which one the quit freeze is,
and on which machine, is what the LAN test in the hook table decides; byte
patches for the two constants are measured and ready.

Win detection is simpler than the ledger suggested. `VictoryConditions::update`
(`0x0035F920`) is the only place a defeat is registered; a leaver is never
"defeated" by the network layer, only by having no objects left after its
DESTROYPLAYER. The results packet is built and sent by the ZH `.wnd` score
screen's `populatePlayerInfo`, gated on a victory flag, a desync or a detected
disconnect **and** a ladder IP/port that retail clients already read from the
GameSpy room keys `ladIP`/`ladPort` -- but 1.03 opens an APT score screen
instead and nothing pushes the `.wnd` one, so the sender is dead code. Arena
needs the keys **and** a hook that runs the send from the APT path.

## The leave handshake

Command types (the name mapper in `network_delay/FINDINGS.md`): 7
REQUESTPLAYERLEAVE, 8 INFORMPLAYERLEAVEFRAME, 9 REQUESTFRAMEDATA, 10
PLAYERLEAVE, 11 DESTROYPLAYER. `TheNetwork` is the VA `0x012F7714`.
`Network+0x0C` is the local status (0 pregame, 1 in game, 2 left, 3 postgame;
there is no ZH LEAVING value), `Network+0x38` the frame the router's own leave
executes on (-1 when none), `ConnectionManager+0x12080[slot]` the per-player
leave state (0 in game, 1 leave requested, 2 PLAYERLEAVE issued, 3
disconnected) and `+0x12110` the `timeGetTime` stamp of the local leave request.

### Two entries

1. **`quitGame` `0x006822E0`**, thiscall on `TheNetwork`, reached only through
   the slot (callers in hook 1). It calls `sendRequestPlayerLeaveCommand`
   `0x006648A0` -- type 7 with the local slot at `+0x1C`,
   `sendLocalCommandDirect` `0x00663300` with relay `~(1 << local)` so every
   peer gets it without the router, `flushConnections` `0x006636F0`, then
   `+0x12110 = timeGetTime()` if unset -- appends `MSG_CLEAR_GAME_DATA`
   (GameMessage `0x1D`) to `TheMessageStream` (VA `0x012ED5EC`, slot `+0x34`)
   and sets status 3. Because the status is no longer 1,
   `GetCommandsFromCommandList` does not intercept that message; it reaches the
   GameLogic dispatcher `0x00397540` (arm `0x00397771`) and `clearGameData`
   `0x00396B00`, which opens the score screen and resets the engine. The
   leaver's own quit is immediate; the 10 s stamp matters only if the Network
   object outlives the reset, which is one of the things to log.
2. **`MSG_CLEAR_GAME_DATA` while the status is 1.** `GetCommandsFromCommandList`
   `0x006828D0`, the command-list pump `Network::update` `0x00682C70` runs
   first, consumes the message when `status == 1 && TheGameLogic+0x6C == 0` (no
   desync) and calls `sendPlayerLeaveCommands` `0x00665C10`, which builds
   **only** type 10 (leaving player = local, execution frame -1), sends it
   through the router with `sendLocalCommand` `0x00664740`, relay `0xFF`, and
   stamps `+0x12110`. The game goes on until the router's PLAYERLEAVE executes;
   this is the end-game timer's path, and the one with the fallback: the pump's
   tail calls `hasLeaveRequestTimedOut` `0x00662E30` (stamp set and older than
   10 000 ms) and, when true, runs `beginPlayerLeave(local)`, builds a
   DESTROYPLAYER for the local slot, executes it locally through
   `processDestroyPlayerCommand` `0x006827A0` and sets status 2. A router that
   never answers is bypassed after 10 s.

### The router's half

Every receiver of a type 7 runs the dispatcher `processIncomingCommand`
`0x0066A3F0` case 7 (jump table VA `0x00A6A634`) into
`processRequestPlayerLeaveCommand` `0x00662D90`, the only writer of state 1.
Only the router acts on it: each tick `runRelayPass` `0x0066A740` builds, for
each slot in state 1 with an open connection (or itself), a type 10 (leaving
player = slot, sender = router) and a type 11 (player index = slot), sends both
with relay `0xFF` and writes state 2 (`0x0066A89A`). Types 10 and 11 have no
dispatcher handler (the reader's table VA `0x00A80EE4` only parses them), so
they are filed into the sender's FrameDataManager like game commands and
execute in the frame tick `RelayCommandsToCommandList` `0x00682A90`, which
takes them from `getFrameCommandList` `0x00663450`:

* **10**: `id = getLeavingPlayerID()`. If this machine is the router
  (`isPacketRouter` `0x00681B20`) and `id` is itself, it stores the message's
  execution frame in `Network+0x38` (`0x00682B52`) and clears the stamp with
  `clearLeaveRequestTime` `0x00662E70`; otherwise `beginPlayerLeave(id)`
  `0x00667320`, and if that returns LOCAL (1) the status becomes 2. Either way
  `bfme_setPlayerLeaveStatus(id, 1)` `0x00383BC0` records a graceful leave on
  the GameLogic.
* **11**: `processDestroyPlayerCommand` `0x006827A0` resolves the slot's
  Player and posts `MSG_SELF_DESTRUCT` (`0x447`) with TRUE.
* **After the list**: if `Network+0x38 != -1` (`0x00681BD0`) and
  `haveAllConnectedPlayersReachedFrame(Network+0x38)` `0x00662D50` -- every
  slot with a Connection has a latest FRAMEINFO frame at `+0x12060` not below
  it -- then `beginPlayerLeave(local)`, status 2, `+0x38 = -1` (`0x00682BFA`).
  **This is the router's wait.** There is no constant in it; it ends when the
  slowest peer catches up or is disconnected.

`beginPlayerLeave(id)` `0x00667320` is ZH's `processPlayerLeave`: for the local
id every Connection gets `clearCommandsExceptFrom(local)` `0x00661C30` and
`setQuitting(frame + 1)` `0x00661CA0`; for a remote id only that Connection is
marked quitting and its FrameDataManager gets the quit frame
`frame + 1 + NetworkRunAheadSlack` (`TheWritableGlobalData+0xCB4`). Then
`disconnectPlayer(id)` `0x00666300`: the last-frame stamp on the GameInfo slot,
`Network:PlayerLeftGame`, frame-data and non-quitting Connection deletion,
**state 3** (`0x0066641B`), and packet-router succession over the id list at
`+0x12030`. If that returns PACKETROUTER (2), the caller sends **type 8**
(leaving player, current frame) directly to every still-open connection; the
receiver's `processInformPlayerLeaveFrameCommand` `0x00664430` records the
frame and, if it is ahead of the receiver, asks the sender for **type 9** frame
data, answered by `processRequestFrameDataCommand` `0x006659B0` through
`resendFrameRangeToPlayer` `0x00664B40`. That is how survivors catch up after
the router leaves.

Teardown is `Network::update` at status 2: `disconnectLocalPlayer`
`0x006665E0`, a second `MSG_CLEAR_GAME_DATA`, status 3 (`0x00682CB3`), and the
dispatcher arm ends the game. Quitting Connections linger until
`ConnectionManager::update` `0x0066AB30` sees `quitFrame <= frame &&
isQueueEmpty()` or `doSend` drops the queue 30 s after the `setQuitting` stamp
at `Connection+0x04` -- the `0x7530` at `0x00661F57`. Nothing gates the state
machine on that flush (ZH's `canILeave()` 2->3 gate is absent); its only cost
is the lingering connection and the unacked commands it keeps re-sending.

The DisconnectManager path (types 25-28: timeouts, the disconnect screen, votes)
never writes `+0x12080`: `updateDisconnectStatus` `0x0066C3B0` calls
`DisconnectManager::disconnectPlayer` `0x0066C040`, which calls the same
`ConnectionManager::disconnectPlayer`. Survivors take it when the router quit
through entry 1: their state 1 for the router's slot never becomes 2, so the
next event is `hasPlayerTimedOut` `0x0066B510` on `NetworkPlayerTimeoutTime`,
the disconnect screen (`turnOnScreen` `0x0066BFE0`), and succession. The timing
fields are INI, not code: `NetworkPlayerTimeoutTime` `TheWritableGlobalData+0xCBC`,
`NetworkKeepAliveDelay` `+0xCB8`, `NetworkDisconnectScreenNotifyTime` `+0xCC0`,
`NetworkRunAheadSlack` `+0xCB4`, consumed by `isPlayerConnectedDefaultTimeout`
`0x00662A50`, `isPlayerConnectedForTimeout` `0x00662B00` and
`hasPacketRouterFrameStall` `0x00664260`.

## Logging and hook table

All bodies are thiscall unless stated (`this` in `ecx`, stack arguments right
to left, callee cleans). Log `timeGetTime()`, `TheGameLogic->getFrame()`
(`TheGameLogic` VA `0x012F0898`, frame at `+0x3C`), the local slot and
`isPacketRouter` on every line; the gaps between lines are the answer.

| # | hook | `this` | log | discriminates |
|---|---|---|---|---|
| 1 | `Network::quitGame` `0x006822E0` | `TheNetwork` | t0; the return address (`0x0050F24F` disconnect screen `0x0050F1A0`, `0x0056982C` QuitMenu dtor `0x00569720`, `0x0038B841` CRC `0x0038B430`, `0x0066CB0D` DisconnectManager `0x0066C8D0`) | which entry the UI took |
| 2 | `sendRequestPlayerLeaveCommand` `0x006648A0` / `sendPlayerLeaveCommands` `0x00665C10` | ConnectionManager | the `+0x12110` stamp | start of the 10 s window; entry 1 vs 2 |
| 3 | `processRequestPlayerLeaveCommand` `0x00662D90` (arg: msg) | ConnectionManager, every receiver | slot (`msg+0x1C`), own router flag | the request arrived, and at the router |
| 4 | `runRelayPass` state-2 write `0x0066A89A` | router only | slot, frame | the router answered (never logged: suspects a and c) |
| 5 | `RelayCommandsToCommandList` `0x00682A90` case 10 (`0x00682B52`) and the poll `0x00662D50` | `TheNetwork` | `Network+0x38`, each `+0x12060[slot]`, the poll result | the router-leave wait (suspect b) |
| 6 | `hasLeaveRequestTimedOut` `0x00662E30` | ConnectionManager | return value, elapsed ms | a freeze that clears at ~10 s is suspect a |
| 7 | `Connection::doSend` `0x00661F10` (Bool) at the `0x00661F57` branch | Connection | quit frame `+0x00`, stamp `+0x04`, queue length | a ~30 s tail is the flush |
| 8 | `beginPlayerLeave` `0x00667320` / `disconnectPlayer` `0x00666300` (Int slot) | ConnectionManager | slot, return code, the new router from `+0x12030` | succession; who became router |
| 9 | `processInformPlayerLeaveFrameCommand` `0x00664430` / `processRequestFrameDataCommand` `0x006659B0` | ConnectionManager | announced frame, own frame, range | survivors stuck catching up |
| 10 | `Network::update` `0x00682C70` (Bool) | `TheNetwork` | status `+0x0C` transitions 1->2->3 | the whole leaver-side duration |
| 11 | `DisconnectManager::turnOnScreen` `0x0066BFE0` / `disconnectPlayer` `0x0066C040` | DisconnectManager | slot, `NetworkPlayerTimeoutTime` | the timeout path (suspect c) |
| 12 | `GameLogic::clearGameData` `0x00396B00` (Bool, Bool) / `??1Network` `0x006823B0` | `TheGameLogic` / `TheNetwork` | t-end; when the Network dies | the end of the freeze on each machine |

Three questions the LAN test answers with this table. **Who freezes:** the
leaver (hooks 2, 6 and 10 show a 1->2 gap: entry 2 or the router-leave wait) or
the survivors (hooks 3 and 4 show a request without an answer, hook 11 the
timeout path). **When it clears:** ~10 s is hook 6, ~30 s is hook 7,
`NetworkPlayerTimeoutTime` is hook 11, and a wait that ends only when the
slowest peer's `+0x12060` reaches `Network+0x38` is hook 5. **LAN vs internet:**
the code path is identical, but the direct sends (type 7 to every peer, type 8
to the open connections) and the type 9 catch-up need a peer-to-peer path that
a LAN always has and the internet has only through the NAT negotiator attached
at launch (`GameSpyStagingRoom::launchGame` `0x00639950`), so an internet-only
freeze points at hook 3 on the router and at hook 9.

## Patch candidates

Both are `patch` rows in `claims.csv`: `address` is the RVA, `expected` is
`<original hex>-><replacement hex>|<post-patch capstone text>`. The claims test
checks that retail still holds the original bytes; the patch-apply test copies
the baseline under `build/`, writes the replacement, disassembles the site and
asserts the copy differs from the baseline only there.

| RVA | original | replacement | post-patch | effect | risk |
|---|---|---|---|---|---|
| `0x00661F57` | `81 C1 30 75 00 00` (`add ecx, 0x7530`) | `81 C1 D0 07 00 00` | `add ecx, 0x7d0` | `doSend` drops a quitting connection's queue after 2 s instead of 30 s | the flush exists so unacked commands still reach slow peers; shortening it can drop a leaver's final frames on a lossy link, and it changes nothing for the state machine, which never waits on it |
| `0x00662E4D` | `B9 10 27 00 00` (`mov ecx, 0x2710`) | `B9 B8 0B 00 00` | `mov ecx, 0xbb8` | `hasLeaveRequestTimedOut` forces the local leave after 3 s instead of 10 s | the timer is the fallback for a router that never answers; at 3 s it races a slow but live router, and the forced path runs the local DESTROYPLAYER outside frame sync (harmless to the leaver, who is gone, but worth logging) |

The router-leave wait has no constant to patch; the hook point is the poll at
`0x00662D50`. The timeout family is INI (`NetworkPlayerTimeoutTime`,
`NetworkKeepAliveDelay`, `NetworkDisconnectScreenNotifyTime`): change the keys,
not bytes. Neither patch should ship before the LAN test says which constant
the freeze is; patching the wrong one proves nothing and hides the real wait.

## Victory determination

### VictoryConditions

`TheVictoryConditions` is the VA `0x012F079C`; the object is `0xC4` bytes
(factory `0x0035F810`, constructor `0x0035F430`, reset `0x0035F1E0`, update
`0x0035F920`); vtable VA `0x010E8D90`, slots 0-8 the SubsystemInterface
positions, 9-17 the ZH interface order, 18-21 BFME-only:

| slot | off | body | name |
|---|---|---|---|
| 9 | `+0x24` | `0x0035F270` | `hasAchievedVictory(Player*)` |
| 10 | `+0x28` | `0x0035F320` | `hasBeenDefeated(Player*)` |
| 11 | `+0x2C` | `0x0035FDF0` | `hasSinglePlayerBeenDefeated(Player*)` |
| 12 | `+0x30` | `0x0035F4E0` | `cachePlayerPtrs` (ledger: `findSkirmishSideInfo`) |
| 13 | `+0x34` | `0x0035F380` | `isLocalAlliedVictory` |
| 14 | `+0x38` | `0x0035F3D0` | `isLocalAlliedDefeat` |
| 15 | `+0x3C` | `0x0035F410` | `isLocalDefeat` |
| 16 | `+0x40` | `0x0035F4A0` | `amIObserver` |
| 17 | `+0x44` | `0x0035F4B0` | `getEndFrame` |
| 18 | `+0x48` | `0x0035F600` | `showEndGameScreen(titleKey, evil, screenName, cheer)` |
| 19 | `+0x4C` | `0x0035F770` | `hideEndGameScreen` |
| 20 | `+0x50` | `0x0035F4C0` | `isPlayerDefeated(idx)` |
| 21 | `+0x54` | `0x0035F1A0` | `updateEndGameScreenTimer` (auto-hide after 7000 ms) |

Layout: `+0x08` `m_victoryConditions` (NOBUILDINGS, plus NOUNITS in game mode
6), `+0x0C`/`+0x10` end-screen shown byte and time, `+0x14` `m_players[32]`,
`+0x94` `m_localSlotNum`, `+0x98` `m_endFrame`, `+0x9C` `m_isDefeated[32]`,
`+0xBC` `m_localPlayerDefeated`, `+0xBD` `m_singleAllianceRemaining`, `+0xBE`
`m_isObserver`, `+0xC0` a BFME defeat counter.

`update` is where defeat happens. For each cached player it calls
`hasSinglePlayerBeenDefeated` (no objects counted for victory under the mask,
or `Player::isPlayerDead` at `Player+0x680`, which `killPlayer` sets and which
is true for observers from creation) and, on the first true, sets
`m_isDefeated[i]`, bumps `+0xC0` (`0x0035FEB9`), records the frame on the
GameLogic through `bfme_setPlayerDefeatFrame(i)` `0x00383C00` and on the Player
at `Player+0x484` (`0x0035FA84`), reveals the map, shows the defeat message and
EVA, shows the APT defeat screen (`APT:EndDefeat`) through slot `+0x48` for
the local player, and calls `killPlayer`. When one alliance remains it sets
`m_singleAllianceRemaining` (`0x0035FA00`), `m_endFrame = frame` (`0x0035FA07`)
and clears `TheGameLogic+0x90`. The predicates keep ZH's meaning behind one
BFME gate, `+0xC0 > 0`: `hasAchievedVictory(p)` is "one alliance remains and
some undefeated player is p or p's ally", `hasBeenDefeated(p)` its complement
under the same condition, `isLocalAlliedVictory` is `!observer &&
hasAchievedVictory(local)`, `isLocalAlliedDefeat` is `observer ?
singleAllianceRemaining : hasBeenDefeated(local)`, and `isLocalDefeat` returns
`m_localPlayerDefeated`, which in BFME is written only by reset and by
`cachePlayerPtrs` (together with `m_isObserver`, when there is no local slot).
The ZH end-of-update block that set it on the local player's own defeat is
gone, so the local defeat reaches the score-screen gate through
`isLocalAlliedDefeat`, not `isLocalDefeat` (derived from the writer list; a run
should confirm it).

### What "defeated" means for a leaver

Nothing in the network layer defeats a leaver. DESTROYPLAYER's
`MSG_SELF_DESTRUCT` kills the objects, and some frames later `update` finds
`hasSinglePlayerBeenDefeated` true and records the defeat like any other. So on
every surviving machine the leaver's defeat frame is later than its leave
frame, and a survivor that leaves before that frame never sees a victory. The
GameLogic keeps both events in eight `PlayerLeaveStatus` records at
`TheGameLogic+0x1B0` (stride `0x1C`, reset by `0x00383B00` from `Network::init`
`0x00681E40`): `+0x00` leave status (1 graceful, from the PLAYERLEAVE tick at
`0x00682B81`; 2 voted out, from `Network::voteForPlayerDisconnect`
`0x00682270`), `+0x04` the leave frame, `+0x08` the defeat frame
(`0x00383C00`), `+0x0C` the victory frame (`bfme_setPlayerVictoryFrame`
`0x00383C30`, written for every surviving allied index), then a present byte
and an AsciiString. At `MSG_CLEAR_GAME_DATA` the dispatcher arm calls
`bfme_appendGameOverDetails` `0x00387A50` (ledger:
`endMenu@EstablishConnectionsMenu`), which formats them as "Game Over Details"
(graceful / voted out / n/a) and copies the leave status into `Player+0x484`
(`0x00387B49`), over the defeat frame `update` stored there.

Observers are excluded from `m_players` by `cachePlayerPtrs`; with no local
slot it sets `m_localPlayerDefeated` and `m_isObserver`, so an observer's
`isLocalAlliedVictory` and `isLocalDefeat` are false and `isLocalAlliedDefeat`
mirrors `m_singleAllianceRemaining`.

### VictorySystem, scripts and the end screens

`VictorySystem` is BFME-only and separate: `TheVictorySystem` VA `0x012EF734`,
constructor `0x001E0160`, vtable VA `0x0109FD8C` with init `0x001E0370`, reset
`0x001DE5B0`, update `0x001DFBA0` and a `newMap` `0x001DF4A0` that
`GameLogic::startNewGame` calls after `ThePlayerList->newMap`. It is the
territory-cell scoring machinery (`BfmeCellGrid` `0x001B1830`;
`FactionVictoryParameters` found or created by `0x001E04B0`) fed by the INI
blocks `VictorySystemData` -> `0x000C3060` and `FactionVictoryData` ->
`0x000C31B0` (ledger: `SidesList::removeSide`). No identified body of it writes
into `VictoryConditions`; the defeat decision above does not depend on it.

The script side: `ScriptActions::executeAction`'s jump table (VA `0x0070D6A0`)
sends `VICTORY` (index 3) to `0x002F7B60` -- the `doVictory` core plus
`SetVictorious(TRUE)` and `startEndGameTimer`, which later posts the
`MSG_CLEAR_GAME_DATA` that takes entry 2 of the handshake -- `DEFEAT` (4) to
`doDefeat` and `LOCAL_DEFEAT` (299) to `doLocalDefeat`; the ledgered `doVictory`
`0x002F1C10` is only the screen half (index 510; index 327 uses the
`0x002F1520` variant). All three replace the ZH `.wnd` windows with slot
`+0x48` and `APT:EndVictorious` / `APT:EndGameOver` / `APT:EndDefeat`;
`0x002ED8F0` picks the GameOver variant when the local player is an observer or
dead, when the multiplayer local defeat was already shown, or in LAN/INTERNET
with `TheGameLogic+0x290 == 0` -- the disconnect blame the DisconnectManager
writes (0 at `0x0066C583`, 1 at `0x0066C7A7`) from the ping success ratio
(`hasPingSuccessRatioAtLeast` `0x0066B150` at 0.25, then 0.1).

## Results reporting

### The gate, as retail wrote it

`populatePlayerInfo` `0x004E5DF0` (ZH `ScoreScreen.cpp`) sends results only
inside `screenType == SCORESCREEN_INTERNET` (3; `cmp [0x012F4134], 3` at
`0x004E6B5A`), in this order: local GameSpy profile id non-zero; the player is
the local player; `TheGameSpyGame` (VA `0x012F7198`) has the local slot;
`!TheVictoryConditions->amIObserver()` (`0x004E6BBC`); an eight-slot scan that
sets `anyNonAI`, the last frame of the game and `gameEndedInDisconnect` (some
occupied slot `disconnected()`, not cleared by a live non-local slot that
lasted to the end nor explained by the ping frame and pings at
`TheNetwork+0x80/+0x84/+0x88`); `!anyNonAI` returns; then

```
sawEndOfGame = isLocalAlliedDefeat()        (+0x38, 0x004E6D70)
            || isLocalAlliedVictory()       (+0x34, 0x004E6D7F)
            || isLocalDefeat()              (+0x3C, 0x004E6D90)
            || TheGameLogic+0x6C            (desync, 0x004E6D9F)
            || gameEndedInDisconnect
```

and FALSE returns. The ladder POST happens iff `TheGameSpyGame+0x450` (the
ladder port, `0x004E6DBC`) is non-zero and `getLadderIP()` `0x004D7AC0`
(`+0x444`) is non-empty: a `GameResultsRequest` {hostname = ladder IP, port,
results = `generateLadderGameResultsPacket()` `0x00639190`} goes to
`TheGameResultsQueue` (VA `0x012F71C4`) `->addRequest` (slot `+0x30`,
`0x004E6EC3`). Only then the GameSpy stats block: `getEndFrame() < 125` (25 s
at 5 logic frames per second) with a non-zero end frame returns, else the real
`generateGameSpyGameResultsPacket` `0x006386F0` (the ledger's name sits on
`0x0085E420`, a Peer SDK callback) and the `PSREQUEST_UPDATEPLAYERSTATS` path.
BFME deltas from ZH: no `getUseStats`/`isQMGame`/`anyAI` early returns, no
`lastLadderPort/Host` writes, `TheGameLogic+0x6C` instead of
`TheNetwork->sawCRCMismatch()`.

### The gate is not reached in 1.03

`populatePlayerInfo` has two callers, `grabMultiPlayerInfo` (`0x004E8237`) and
`grabSinglePlayerInfo` (`0x004E8393`), and those run only from the `.wnd`
`ScoreScreenInit` `0x004E8DC0`, which nothing calls: it is reached through the
FunctionLexicon entry at `0x00EA9AD8` when a layout named `ScoreScreenInit`
as its init, and the image holds 38 `Menus/*.wnd` literals but no
`Menus/ScoreScreen.wnd`. `clearGameData` opens `ScoreScreen.apt` instead
(`_bfme_showScoreScreen` `0x005774E0`, the literal at VA `0x010879C4` pushed
at `0x005775DD`), and that APT screen's init calls only the battle-honours
updater `0x000A41F0` (skirmish, `0x00576ECC`) and the online stats updater
`0x000A5D40` (internet, `0x00576EEC`, and only when `m_isQM`, `0x00576EE3`),
neither of which touches the ladder fields or the results queue -- the only
loads of `TheGameResultsQueue` in the image are `0x0007B454`, `0x004E6EAF`
(inside `populatePlayerInfo`) and `0x00641F1A`. So the gate, the packet and
the TCP thread are intact, but no retail path executes the send. Arena has to
add one: a hook at the APT init (next to `0x00576EEC`) that evaluates the gate
and queues a `GameResultsRequest`, or a pushed `.wnd` layout whose init is
`ScoreScreenInit`. `populatePlayerInfo` itself fills `.wnd` controls, so
calling it from the APT path without the layout is not the shortcut.

### The packet

`generateLadderGameResultsPacket` `0x00639190` (format literals pinned as
`string` claims at VAs `0x01118CF0`, `0x01118CCC`, `0x01118C9C`, `0x01118C60`,
`0x01118C14`, `0x01118BEC`, `0x01118BE4`, `0x01118BD8`):

```
seed=%d,slotNum=%d,sawDesync=%d,sawGameEnd=%d,winningTeam=%d,disconEnd=%d,duration=%d,numPlayers=%d,isQM=%d,map=%s
,ladderIP=%s,ladderPort=%d
per present player: ,player%d=%s,playerID%d=%d,locale%d=%d
                    ,unitsKilled%d=%d,unitsLost%d=%d,unitsBuilt%d=%d
                    ,buildingsKilled%d=%d,buildingsLost%d=%d,buildingsBuilt%d=%d
                    ,cash%d=%d,discon%d=%d,side%d=%s
,size=%10.10d        (the length of everything before it, plus 10)
```

The only deltas from ZH `StagingRoomGameInfo.cpp:697` are the missing `fps%d`
and `capturedTech%d` fields and the desync source. The semantics are ZH's:
`sawGameEnd` is `getEndFrame() > 0` (slot `+0x44` at `0x006391B6`),
`winningTeam` is the team of any player for whom `hasAchievedVictory` (slot
`+0x24` at `0x00639253`) is true and stays **-1** otherwise, `disconEnd` is
"fewer than two teams still had a non-disconnected player", `duration` is the
end frame, `isQM` the byte at `TheGameSpyGame+0x43C`. Transport:
`Thread_Function` `0x00641E70` dequeues through slot `+0x34` of
`TheGameResultsQueue`, resolves the host and calls `sendGameResults`
`0x00640830` -- a blocking TCP `socket/connect/send/closesocket` -- then builds
the response but **never calls `addResponse`**; nothing in the game learns
whether the POST landed. The queue is built once by `GameEngine::init` through
`0x006426E0` (`new(0x80)` plus the real constructor `0x00642300`; vtable VA
`0x01119380`: `startThreads` `0x006406D0`, `endThreads` `0x006407D0`,
`addRequest` `0x006427F0`).

### Three ways to set the ladder fields

BFME renamed ZH's `ladderIP`/`ladderPort` QR2 server keys to **`ladIP`** (key
id `0x38`, registered at `0x0064FD71`) and **`ladPort`** (`0x39`, `0x0064FD7D`)
in the PeerThread body `0x0064FB90`; the host's `QRServerKeyCallback`
`0x0064DA00` emits them (ladPort from `PeerThreadClass+0x158` at `0x0064DDD8`),
the joiner's listing callback `0x0064B6B0` reads them (`0x0064B9A0`,
`0x0064B9C5`) and on join they are copied into `TheGameSpyGame+0x444/+0x450`
(`0x004FCB8C`-`0x004FCBA9` in the lobby, `0x0053EB2D`-`0x0053EB3D`,
`0x0053E19D`-`0x0053E1BA`). The game-options string (`GameInfoToAsciiString`,
really `0x00621600`) carries no ladder field; the room keys are the only
channel. Hence:

1. **Host ladder selection.** The host-game popup `0x0053E390` copies the
   chosen ladder's port from the `PeerRequest` (`+0x11A`) into
   `TheGameSpyGame+0x450` at `0x0053E655`; the combo is
   `PopulateCustomLadderComboBox` `0x004D6420` over `LadderList` (`0x0062C020`;
   local files from `loadLocalLadders` `0x0062BE40` under
   `LoTRB4MEOnline\Ladders\`) and `LadderPreferences::loadProfile` `0x000AE0A0`
   (`Ladders%d.ini`). A shipped ladder definition pointing at the Arena host is
   inherited by every joiner through the keys.
2. **Room keys.** Whatever publishes the room -- a retail host or an Arena-side
   lobby -- only has to answer the QR2 query with a non-empty `ladIP` and a
   non-zero `ladPort`; the retail reader and the join-time copy already exist.
3. **Setters.** `setLadderIP` `0x004D4810` and `setLadderPort` `0x004D3E40`
   exist out of line (the port setter has no retail caller; every live write is
   inlined), and QuickMatch shows the pattern in the `QM:MATCHED` handler
   ending at `0x00507365`: `m_isQM = 1` (`+0x43C`), the ladder type (`+0x440`),
   IP and port from `TheLadderList` (VA `0x012F4820`, loaded at `0x0050730D`)
   or the `localhost` fallback at VA `0x010FFEB4`. The Arena GameSpy ladders
   25909/25911 reached by `ghttp` (`0x0065BD40`, `0x0065BE50`) are a different,
   read-only path.

### Retail edge cases the receiver must expect

* **Quit before the engine registers a defeat.** A leaver that takes entry 1
  reaches the score screen with no victory flag, no desync and (unless someone
  else dropped) no disconnect: the gate stays shut and the leaver sends
  nothing. The survivors send once `VictoryConditions::update` has counted the
  leaver's defeat -- only if they are still in the game on that frame. A
  survivor that leaves earlier sends, if at all, `winningTeam=-1,sawGameEnd=0`.
* **Both leave.** Neither machine registers the other's defeat: no packet, or
  packets with `winningTeam=-1`. The receiver has to treat "no result" as an
  outcome class, not as a network error.
* **Desync.** `TheGameLogic+0x6C` is set by the reporter `0x00388C10` (writes
  `DESYNC-%s-%s.txt`; called from the per-frame CRC consensus `0x0038B430`,
  which also calls `quitGame`), cleared by `startNewGame` (`0x00395E8F`), read
  by the pump (`0x00682960`: no leave command after a mismatch), the gate
  (`0x004E6D9F`), the ladder packet (`0x0063933F`) and the online stats updater
  (`0x000A5EFC`). Every machine that saw the mismatch opens the gate and sends
  `sawDesync=1,winningTeam=-1`.
* **Disconnect.** `gameEndedInDisconnect` opens the gate and sets the
  per-player `discon%d`; `disconEnd=1` when fewer than two teams had a
  non-disconnected player left.
* **No acknowledgement.** `Thread_Function` never posts a response, so the
  client cannot retry or warn; only the receiver can detect a missing report.
* The 25 s minimum applies to the GameSpy stats path only.

## Ruled out

* **The results thread cannot freeze the UI.** `areGameResultsBeingSent`
  `0x0063FD50` is slot `+0x40` of vtable `0x01119380`; the three loads of
  `TheGameResultsQueue` call `+0x28` (`endThreads`, `0x0007B454`), `+0x30`
  (`addRequest`, `0x004E6EAF`) and `+0x34` (`getRequest`, `0x00641F1A`). ZH's
  score screen polled it; BFME's does not.
* **`TheNetwork` is `0x012F7714`, not `0x012F76F0`.** The latter is the GameSpy
  persistent-storage queue (`TheGameSpyPSMessageQueue`, slots `+0x10`
  addRequest, `+0x24` findPlayerStatsByID) that `SetUpGameSpy` stores from
  `createNetwork@NetworkInterface` `0x0065C1F0`; every `+0x28`/`+0x38`/`+0x78`
  virtual call the seeds describe loads `0x012F7714`, written by
  `GameEngine::init` (`0x0007A482`) and the factory `0x00682320`.
* **ZH's `Network::sawCRCMismatch` slot does not exist.** The ledgered
  `setSawCRCMismatch` `0x00681BA0` / `_bfme_clearSawCRCMismatch` `0x00681BB0`
  set and clear `Network+0x35` around `Network::update` in the engine core
  `0x0006BAE0` -- an in-update flag. The desync flag is `TheGameLogic+0x6C`.
* **No LEAVING state, no `canILeave` gate, no packet-router ack path.**
  `resendPendingCommands` `0x006649A0` and `sendDisconnectScreenOff`
  `0x0066B190` have no retail caller.
* **The game-options string carries no ladder field**, and the
  `ladderstats.sdk`/`ladderrank.sdk` HTTP calls are unrelated to the TCP
  results path.
* **`0x00065470` is not the lockstep desync writer.** It is `??1BFMEDesyncCheck`
  (unwind funclet `0x00BF2AD0`), the client-side `CLIENT_DESYNC_%s.txt` check
  that `GameEngine` slot `+0x80` `0x0006B910` builds on its stack each frame;
  the lockstep reporter is `0x00388C10`.

## Corrections to earlier notes

* `network_delay/FINDINGS.md` describes `ConnectionManager+0x12080` as "1 in
  game, 2-3 leaving". The complete writer list says **0 in game, 1 leave
  requested (only `0x00662D90`), 2 PLAYERLEAVE and DESTROYPLAYER issued (only
  `runRelayPass` at `0x0066A89A`), 3 disconnected (only `disconnectPlayer` at
  `0x0066641B`)**. The ledger names are inverted accordingly: `isPlayerInGame`
  `0x00662BE0` tests `== 1` (has requested leave) and `isPlayerSlotActive`
  `0x00662C30` tests 1..3 (is leaving); the vote counters and router succession
  skip the slots for which the latter is true.
* The `VictoryConditions` slot order is `+0x34` isLocalAlliedVictory, `+0x38`
  isLocalAlliedDefeat, `+0x3C` isLocalDefeat, `+0x40` amIObserver, `+0x44`
  getEndFrame -- the ZH interface order shifted by the nine SubsystemInterface
  slots. Earlier planning notes had the allied pair the other way round; the
  score-screen call sites (`0x004E6D7F`, `0x004E6D70`) and the skirmish sibling
  (`0x004E66A3`) settle it.
* The comment in `native_connection_timing.cpp` saying `sendPlayerLeaveCommands`
  builds types 10 and 11 is wrong: it builds only 10; `runRelayPass` builds both.
* The comment that retail reaches `sendLocalCommandDirect` through ILT
  `0x0003F17A` is wrong: that thunk lands on `sendLocalCommand` `0x00664740`;
  the direct one is `0x000411D7` -> `0x00663300`.
* `network_delay/FINDINGS.md` calls `0x00065470` "the real desync writer"; see
  Ruled out.
* The phase-3 notes treat `populatePlayerInfo` as the live results gate; it is
  the gate's logic, in a screen 1.03 never opens (above).

## Ledger corrections

Pinned under the correct name in `symbols.csv`, logged `identity-suspect` in
`re_attempts.log`; the source rename happens at conversion (`conversion_gate`
Rule A).

| body | ledger name | what it is |
|---|---|---|
| `0x00662D90` | `markPlayerInGame@BFMEConnectionManager` | `processRequestPlayerLeaveCommand` |
| `0x00666300` | `buildPlayerStatusText@BFMEConnectionManager` | `ConnectionManager::disconnectPlayer` |
| `0x00667060` | `resolvePlayerFromName@BFMEConnectionManager` | `ConnectionManager::processChat` |
| `0x00387A50` | `endMenu@EstablishConnectionsMenu` | `GameLogic::bfme_appendGameOverDetails` |
| `0x0038C1E0` | `popSleepyUpdate@GameLogic` | 2876 B body posting `MSG_CLEAR_GAME_DATA` (sighting) |
| `0x00681BA0` / `0x00681BB0` | `setSawCRCMismatch` / `_bfme_clearSawCRCMismatch` | the in-update flag bracket |
| `0x000C31B0` | `removeSide@SidesList` | `iniParseFactionVictoryDefinition` |
| `0x0035F4E0` | `findSkirmishSideInfo@SidesList` | `VictoryConditions::cachePlayerPtrs` |
| `0x0085E420` | `generateGameSpyGameResultsPacket@GameSpyStagingRoom` | Peer SDK `piAddListingGamesCallback`; the real builder is `0x006386F0` |
| `0x003107F0` / `0x003307E0` | `ScriptEngine::init` / `ScriptConditions::evaluateCondition` | the action and condition template builders; the real init is `0x00340B80` |
| `0x00621600` | `isSandbox@GameInfo` | `GameInfoToAsciiString` |
| `0x0057F5B0` | `hide@Shell` (ILT pin) | `Shell::hideShell` |
| `0x0063E240` / `0x0063E170` | `createNewGameResultsInterface` / `??_GGameResultsQueue` | buddy-queue factory and deleting dtor (vtable `0x01118E70`); the GameResultsQueue ones are `0x006426E0` / `0x00642410` |
| `0x000E0B40` / `0x000E0B60` | `getSideIconImage` / `getGeneralImage@PlayerTemplate` (converted C++) | read `+0xD4` HeadWaterMark / `+0xD8` FlagWaterMark; SideIconImage is `+0xE0`, body `0x000E0B80` |

## Open questions

* Does `TheGameEngine->reset()` inside `clearGameData` delete the Network on
  entry 1, as ZH does, or does the object outlive the score screen (hook 12)?
* On the survivors' side, does a quitting Connection (kept until its queue
  drains or 30 s) count as connected for `hasPlayerTimedOut`, i.e. can the
  flush put the leaver's slot on the disconnect screen?
* `0x00598F30` (ledger `hidePurchaseScience@ControlBar`) sits at ZH's
  `HideQuitMenu()` position in `DisconnectMenu::showScreen` on the window
  global `0x012F4C38`, while `?HideQuitMenu@@YAXXZ` is matched at `0x0055DB80`
  and `g_quitMenuLayout` is pinned at `0x012F4AD4`; which global is the
  QuitMenu's is unresolved.
* `createNetwork@NetworkInterface` `0x0065C1F0` builds the `0xA8`-byte
  GameSpy-side queue, not the `0x40`-byte `BFMENativeNetwork` the factory
  `0x00682320` builds; the ledger name looks wrong (tier 2, not logged).
* `TheGameLogic+0x90`, cleared when the single alliance is detected (probably
  `m_isScoringEnabled`), is unpinned; so are `TheShell` `0x012F4B58` and the UI
  singleton `0x012F148C`.
* The listing callback `0x0064B6B0` (1836 B, no Ghidra function, no ledger row)
  and the PeerThread body `0x0064FB90` need a peer-thread pass.
* `0x006E8800` (762 B, `gen_asm` dump, reached through ILT `0x0002F8D8` from
  `0x006E8DF0`) loads `TheNetwork` and dispatches on an index over roughly
  seventeen cases, reading `TheGameLogic+0x3C` and the globals `0x012F8054` and
  `0x012F81A9`. It entered the closure only when the virtual-call scan stopped
  using a byte window, and it is the one function of E tier 0-1 still unnamed.
* `writeReportIfMismatched@BFMEDesyncCheck` `0x00065470` is a destructor;
  `native_desync_report.cpp` declares it as a plain method. Rename the pair when
  the constructor `0x000652C0` is converted.

## Landed evidence

* `targets/game/reverse/game_end/claims.csv`: 1840 rows from phases 2-3 plus the rows this
  document adds (the two `patch` rows and the sites cited here that no earlier
  pass had claimed), every one checked against the retail image by
  `test_game_end_claims_hold_against_retail`.
* `targets/game/reverse/symbols.csv`: 119 pins (phase 2, group E) and 173 pins (phase 3,
  groups A-D) with call-site evidence; `targets/game/reverse/re_attempts.log`: 122 + 174
  rows (`mapped` / `identity-suspect`).
* `tools/callers_of.py --closure targets/game/reverse/game_end/seeds.json`: every anonymous
  function of A/B/C/D/E tiers 0-1 is named except four leftovers (`0x00067940`
  shared slot-6 stub, `0x00340C9E` SEH continuation, `0x00624B90` ICF twin,
  `0x00BF2AD0` unwind funclet); `CLOSURE_BASELINE` in `test_inventory.py` pins
  it.

## Object layouts pinned by the matched bodies

| object | field | meaning |
|---|---|---|
| `BFMENativeNetwork` (`0x40` B, vtable `0x0111A968`) | `+0x08` | `m_conMgr` |
| | `+0x0C` | local status 0/1/2/3 |
| | `+0x38` | router's own leave frame, -1 = none |
| `ConnectionManager` (`0x12190` B) | `+0x12030` | router succession list |
| | `+0x12060[8]` | latest FRAMEINFO frame per slot |
| | `+0x12080[8]` | leave state 0/1/2/3 |
| | `+0x12110` | leave-request stamp (ms) |
| `Connection` | `+0x00` | quit frame, -1 = live |
| | `+0x04` | quit stamp (ms) for the 30 s flush |
| `GameLogic` | `+0x6C` | desync byte |
| | `+0x1B0` | `PlayerLeaveStatus[8]`, stride `0x1C` |
| | `+0x290` | disconnect blame (0 = none) |
| `Player` | `+0x484` | defeat frame, then leave status at game over |
| `GameSpyStagingRoom` (`TheGameSpyGame`) | `+0x43C` | `m_isQM` |
| | `+0x440` | QM ladder type |
| | `+0x444` | `m_ladderIP` |
| | `+0x450` | `m_ladderPort` (word) |

## Work plan

1. NEXT: the LAN test with the hook table -- two machines, then three with a
   third-party router; record which machine waits and for how long, and match
   the duration to hook 5, 6, 7 or 11.
2. Apply whichever `patch` row the measurement implicates (or an INI change for
   the timeout family) and re-measure; do not ship both.
3. Arena results: a hook at the APT score-screen init that runs the gate and
   queues the ladder `GameResultsRequest`, a ladder definition or room-key
   publisher that sets `ladIP`/`ladPort`, and a TCP receiver for the packet
   grammar above that treats "no packet" and `winningTeam=-1` as outcomes.
4. Convert the tier-0 bodies still in MASM dumps -- `GetCommandsFromCommandList`,
   `RelayCommandsToCommandList`, `Network::update`, `doSend`,
   `haveAllConnectedPlayersReachedFrame`, the leave-timer pair -- and retire the
   wrong ledger names above at that point.
5. Peer-thread pass for `0x0064B6B0` / `0x0064FB90`.

## Non-goals

* No behaviour change in matched source; the `patch` rows are measured
  candidates, not a profile.
* No timing claims beyond the constants and the INI fields until the LAN test
  has run.
* No GameSpy stats (`PSREQUEST_UPDATEPLAYERSTATS`) work; Arena needs the ladder
  POST, not persistent storage.
