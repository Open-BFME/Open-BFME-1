# 0x0066AB30 ConnectionManager::update (814 B)

Identity correction: the row was the naked mnemonic-asm lift `?update@BFMEConnectionManager@@QAEXXZ`
in `native_connection_timing.cpp`. The body is `?update@ConnectionManager@@UAEX_NH@Z`.

## BFME 1 target evidence
- `ilt_oracle.py check ?update@ConnectionManager@@UAEX_NH@Z 0x0066AB30`: CONFIRMED (p_false
  5.22e-04, exact). The body is reached through ILT 0x00005178. The old niladic
  `BFMEConnectionManager::update()` name is CONTRADICTED (outside every window of the target's
  slots).
- ABI: the body ends `ret 8` and reads two stack arguments:
  - The first is a byte flag (`mov al,[esp+0x64]`) that gates the disconnect/relay/frame-info
    block.
  - The second is a dword (`cmp [esp+0x68],0`) that gates sendFrameInfo.

  This matches Zero Hour's `update(Bool isInGame, Int frameAdvanced)`. The `U` (virtual)
  decoration agrees with the matched virtual `?init@ConnectionManager@@UAEXXZ` sibling.
- Boundary: the final `ret 8` is at +0x32B, followed by INT3. That gives 814 bytes, and the
  ledger extent is unchanged.
- Callees, all through existing ledger rows or pins:
  - Transport::doRecv and doSend.
  - BFMEDisconnectManager::update and BFMEConnectionManager::runRelayPass.
  - Network vtable slot 55 (isRouterLeavePending, as in runRelayPass).
  - BFMEConnectionManager::sendFrameInfo and sendKeepAliveCommand.
  - _GetChallenge and _goastrdup.
  - The BFMENetRequestGameSpyStatsAuthKeyCommandMsg constructor (`new 0x20`) and setText1C.
  - DoesCommandRequireACommandID, GenerateNextCommandID, sendLocalCommandDirect and detach.
  - _GenerateAuthA.
  - GameSpyStagingRoom::getGameSpySlot, and GameSpyGameSlot getLoginName, setLoginName and
    setLocale.
  - Connection::doSend, isQueueEmpty and ~Connection (0x006652B0).
  - FrameDataManager::getIsQuitting, getQuitFrame and its virtual deleting destructor.

## Donor evidence (BFME 2, Open-BFME-2 59e3f8f825)
- `Code/GameEngine/Source/GameNetwork/ConnectionManager_update.cpp`: ConnectionManager::update
  (BFME 2 0x004D342A, 802 B, vtable 0x008601C0 slot 3, matched there). It supplies:
  - the Zero Hour update order;
  - the zero address/port early return;
  - the one-shot GameSpy stats-auth step behind the +0x12115 flag (NULLGAME challenge test,
    type-5 request broadcast, GenerateAuthA over the buddy queue's secret, and the local slot's
    login name and locale when the login is empty);
  - the connection and frame-data quit sweep.

## BFME 1 adaptations (retail body, not donor)
- The relay pass is `runRelayPass` (0x0066A740). The disconnect sweep is
  `BFMEDisconnectManager::update` (0x0066C8D0).
- On a frame advance, the router skips sendFrameInfo while a router leave is pending. There is
  no frame-ceiling store (BFME 2 raises +0x1205C there).
- The auth request has no timestamp. Its execution frame is -1, and its player id is the local
  slot.
- The request message is 0x20 bytes, with its AsciiString at +0x1C. The response buffer is
  64 bytes (frame 0x44).
- The connection's +0 dword is compared unsigned with the logic frame as its quit frame.
- The NULLGAME test is a 9-byte compare (`repe cmpsb`).
- Retail sets the player id before the execution frame, and compares the frame-data quit frame
  against the logic frame in that order. Writing either the other way leaves register-order
  differences.
