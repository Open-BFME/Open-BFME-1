# 0x00667060 ConnectionManager::processChat (561 B)

Identity correction: the row was the naked mnemonic-asm lift
`?resolvePlayerFromName@BFMEConnectionManager@@QAEXPAX@Z` in `native_connection_timing.cpp`. The
body is `?processChat@ConnectionManager@@QAEXPAVNetChatCommandMsg@@@Z`.

## BFME 1 target evidence
- `ilt_oracle.py check ?processChat@ConnectionManager@@QAEXPAVNetChatCommandMsg@@@Z 0x00667060`:
  CONFIRMED (p_false 3.91e-04, exact). symbols.csv already pinned this name at the address with
  the dispatcher evidence. The earlier `identity-suspect` verdict (re_attempts.log) is what
  established this; the later "converted" verdict only came from the source-path pruning pass.
- Caller: the CHAT (type 14) arm 0x0066A5C4 of the matched incoming-command dispatcher
  (BFMEConnectionManager::processIncomingCommand) calls ILT 0x00004A07, which jumps here. In
  source, that arm now calls `processChat`, and the dispatcher stays byte-exact.
- Body:
  - It formats `L"[%ls] %ls"` (VA 0x01117AEC) from `getPlayerName(id)` and
    `NetChatCommandMsg::getText()`.
  - It returns for a sender id of 8 or more.
  - It looks up the sender's Player through the slot's name key, `nameToKey` and
    `findPlayerWithNameKey`.
  - When there is no Player, it shows `L"%ls"` with the line. When the local slot's bit is set
    in `getPlayerMask()` and the sender can be seen, it shows the line in the Player's colour.
  - It ends `ret 4`.
- Boundary: the `ret 4` is at +0x22E, followed by INT3. That gives 561 bytes, and the ledger
  extent is unchanged.

## Donor evidence (BFME 2, Open-BFME-2 59e3f8f825)
- `Code/GameEngine/Source/GameNetwork/ConnectionManager_processChat.cpp`:
  ConnectionManager::processChat (BFME 2 0x004D10F1, 449 B, matched there). It supplies the Zero
  Hour structure:
  - format first;
  - the slot-8 early return;
  - the name-key Player lookup;
  - the plain message without a Player;
  - the coloured `messageColor` for a recipient that can see the chat;
  - the chat sound in both branches.

## BFME 1 adaptations (retail body, not donor)
- The name key is the AsciiString at GameSlot +0x2C, passed to `nameToKey(const char *)`.
- The mute flag is GameSlot +0x0A. A sender whose Player is not active cannot be seen
  (`!isPlayerActive`), as in Zero Hour's fromObserver.
- The Player colour is at +0x1C4.
- The InGameUI virtuals are messageColor +0x38 and message +0x40.
- The no-Player branch inlines the chat sound: TheAudio slot +0x124 (misc audio), then slot
  +0x44 with misc audio +0xC40. The coloured branch calls
  `BFMEConnectionManager::playMessageReceivedSound` (0x00662CE0) instead.
- There is no chat-history call.
