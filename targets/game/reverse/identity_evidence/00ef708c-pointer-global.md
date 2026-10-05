# Datum identity at VA 0x012F708C

The datum is `?TheGameInfo@@3PAVGameInfo@@A` in `game/GameEngine/Source/GameNetwork/GameInfo.cpp`. The pointer selects the active GameInfo view; its current receiver can come from several game modes.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

The matched GameInfo and gameplay/network callers load this global as a receiver, including isLocalAlliedVictory at 0x0035F380. The reader at 0x0038DA10 reads the interval field at pointee +8; the reader at 0x001A0390 invokes vtable +0x34. These are views of the same address, not additional GameInfo objects. The writer at 0x0066E078 clears the active pointer.

Zero Hour GameEngine/Source/GameNetwork/GameInfo.cpp:55 defines GameInfo *TheGameInfo; Include/GameNetwork/GameInfo.h declares the same type. The retail reader contracts are retained with local casts where the BFME layout differs.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheGameInfo@@3PAVGameInfo@@A` | 32 |
| `?g012F708C@@3PAURva001A0390GameInfo@@A` | 1 |
| `?g012F708C@@3PAURva0038DA10GameInfo@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?DiplomacySystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004C42D0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Diplomacy.cpp)
- `?DoAnyMapTransfers@@YA_NPAVGameInfo@@@Z` at RVA `0x0066E070` (game/GameEngine/Source/GameNetwork/FileTransfer_DoAnyMapTransfers.cpp)
- `?InitGadgets@AptPlayerStatus@@QAEXPBDPAXPAVGameWindow@@@Z` at RVA `0x0052B020` (game/GameEngine/Source/GameClient/GUI/AptPlayerStatusInitGadgets.cpp)
- `?PopulateInGameDiplomacyPopup@@YAXXZ` at RVA `0x004C3800` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/PopulateInGameDiplomacyPopup.cpp)
- `?_bfme_checkMsg@AptPlayerStatus@@QAEHHPAX0@Z` at RVA `0x0052AF40` (game/GameEngine/Source/GameClient/GUI/AptPlayerStatusInitGadgets.cpp)
- `?_bfme_getInternetPlayerStatus@@QAEHABVUnicodeString@@@Z` at RVA `0x00513740` (game/GameEngine/Source/GameClient/GUI/BfmeGetInternetPlayerStatus.cpp)
- `?_bfme_populateMultiPlayer@BfmeAptScreenScoreScreen@@QAEXH@Z` at RVA `0x005770E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptScoreScreenPopulateMultiPlayer.cpp)
- `?_bfme_quitLocalGame@GameLogic@@QAEXXZ` at RVA `0x003839E0` (game/GameEngine/Source/GameLogic/System/GameLogic_quitLocalGame.cpp)
- `?_bfme_send@BfmeAptScreenInGameChat@@QAEXPBD@Z` at RVA `0x00514000` (game/GameEngine/Source/GameClient/GUI/BfmeAptScreenInGameChatSend.cpp)
- `?_bfme_updateSkirmishBattleHonors@@YAXPAVPlayer@@@Z` at RVA `0x000A41F0` (game/GameEngine/Source/Common/BfmeUpdateSkirmishBattleHonors.cpp)
- `?bfmePopulateGameReport@GameLogic@@QAEXPAVGameInfo@@PAH@Z` at RVA `0x00393880` (game/GameEngine/Source/GameLogic/System/GameLogicPopulateGameReport.cpp)
- `?bfmeRva000A3820@@YAXAAVSkirmishBattleHonors@@@Z` at RVA `0x000A3820` (game/GameEngine/Source/Common/StatsReporter.cpp)
- `?bfme_notificationOtherMode@@YAXVAsciiString@@VUnicodeString@@@Z` at RVA `0x004EB2A0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva004EB2A0NotificationOtherMode.cpp)
- `?buildPlayerStatusText@BFMEConnectionManager@@QAEXPAX@Z` at RVA `0x00666300` (game/GameEngine/Source/GameNetwork/native_connection_timing.cpp)
- `?constructGameMessage@NetGameCommandMsg@@QAEPAVGameMessage@@XZ` at RVA `0x00675ED0` (game/GameEngine/Source/GameNetwork/NetGameCommandMsg_constructGameMessage.cpp)
- `?d_00392d00@@YAXXZ` at RVA `0x00392D00` (game/gen_asm/d_002e22f0.asm)
- `?disconnectPlayer@DisconnectManager@@IAEXHPAVConnectionManager@@@Z` at RVA `0x0066C040` (game/GameEngine/Source/GameNetwork/DisconnectManager_disconnectPlayer_Thunk.cpp)
- `?doFileTransfer@@YA_NVAsciiString@@H@Z` at RVA `0x0066CE60` (game/GameEngine/Source/GameNetwork/FileTransfer_doFileTransfer.cpp)
- `?generateGameSpyGameResultsPacket@GameSpyStagingRoom@@QAE?AVAsciiString@@_N@Z` at RVA `0x006386F0` (game/GameEngine/Source/GameNetwork/GameSpy/GenerateGameSpyGameResultsPacket.cpp)
- `?generateLadderGameResultsPacket@GameSpyStagingRoom@@QAE?AVAsciiString@@XZ` at RVA `0x00639190` (game/GameEngine/Source/GameNetwork/GameSpy/GenerateLadderGameResultsPacket.cpp)
- `?getSlotIndex@@YAHPBVGameSlot@@@Z` at RVA `0x0061ECE0` (game/GameEngine/Source/GameNetwork/GameInfo.cpp)
- `?grabMultiPlayerInfo@@YAXXZ` at RVA `0x004E8050` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenGrabMultiPlayerInfo.cpp)
- `?init@MapTransferLoadScreen@@` at RVA `0x00492C40` (game/GameEngine/Source/GameClient/GUI/LoadScreenInit.cpp)
- `?isLocalAlliedVictory@VictoryConditions@@UAE_NXZ` at RVA `0x0035F380` (game/GameEngine/Source/GameLogic/ScriptEngine/victory_conditions.cpp)
- `?isSlotLocalAlly@@YA_NPBVGameSlot@@@Z` at RVA `0x0061ED20` (game/GameEngine/Source/GameNetwork/GameInfo.cpp)
- `?method@Rva000D9D30Player@@QAEXXZ` at RVA `0x000D9D30` (game/GameEngine/Source/Common/RTS/Player.cpp)
- `?populatePlayerInfo@@YAXPAVPlayer@@H@Z` at RVA `0x004E5DF0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreen_populatePlayerInfo.cpp)
- `?populateRandomStartPosition@@YAXPAVGameInfo@@@Z` at RVA `0x00390F90` (game/GameEngine/Source/GameLogic/System/GameLogic.cpp)
- `?prepareForMP_or_Skirmish@SidesList@@QAEXXZ` at RVA `0x001A0390` (game/GameEngine/Source/GameLogic/Map/SidesList.cpp)
- `?processDestroyPlayerCommand@Network@@IAEXPAVNetDestroyPlayerCommandMsg@@@Z` at RVA `0x006827A0` (game/GameEngine/Source/GameNetwork/Network_processDestroyPlayerCommand.cpp)
- `?resolvePlayerFromName@BFMEConnectionManager@@QAEXPAX@Z` at RVA `0x00667060` (game/GameEngine/Source/GameNetwork/native_connection_timing.cpp)
- `?rva00511CC0@@YAXH@Z` at RVA `0x00511CC0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva00511CC0InGameChat.cpp)
- `?rva0052C220@BfmeAptScreenObjectives@@QAEXXZ` at RVA `0x0052C220` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptObjectivesMenu.cpp)
- `?setControlBarSchemeByPlayer@ControlBar@@QAEXPAVPlayer@@@Z` at RVA `0x0049F8B0` (game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarSetControlBarSchemeByPlayerThunk.cpp)
- `?setControlBarSchemeByPlayerTemplate@ControlBar@@QAEXPBVPlayerTemplate@@@Z` at RVA `0x0049FC90` (game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_setControlBarSchemeByPlayerTemplate_Thunk.cpp)
- `?setDebugPath@Pathfinder@@QAEXPAVPath@@@Z` at RVA `0x003D9880` (game/GameEngine/Source/GameLogic/AI/PathfinderSetDebugPath.cpp)
- `?translateGameMessage@CommandTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z` at RVA `0x005AFFB0` (game/GameEngine/Source/GameClient/MessageStream/CommandXlat.cpp)
- `?update@GameLogic@@UAEXH@Z` at RVA `0x0038DA10` (game/GameEngine/Source/GameLogic/System/GameLogic.cpp)
- `?update@MultiPlayerLoadScreen@@UAEXH@Z` at RVA `0x00491EB0` (game/GameEngine/Source/GameClient/GUI/LoadScreenUpdates.cpp)
- `?update@VictoryConditions@@UAEXXZ` at RVA `0x0035F920` (game/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditionsUpdate.cpp)
- `?updateChallengeMedals@@YAXAAH@Z` at RVA `0x004E27E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenChallengeMedals_Thunk.cpp)
- `?updateLoadProgress@GameLogic@@QAEXH@Z` at RVA `0x000DB020` (game/GameEngine/Source/Common/RTS/GameLogicUpdateLoadProgressThunk.cpp)
- `?populate@ControlBarPopulateObserverListShim@@QAEXXZ` at RVA `0x004A9CD0` (game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarObserver.cpp)

Writers:

- `?DoAnyMapTransfers@@YA_NPAVGameInfo@@@Z` at RVA `0x0066E070` (game/GameEngine/Source/GameNetwork/FileTransfer_DoAnyMapTransfers.cpp)

## Supplemental retail accesses

`build/rlink/pointer-globals-20261005/012F708C-missing-refs.log` disassembles additional Ghidra extents from their recorded starts. These are retail instructions, not a decompiler draft. The additional containing bodies and instruction sites are:

- RVA `0xA5D40`, recorded extent 4125 bytes: `0x000A5DE0`, `0x000A5E70`, `0x000A5F48`, `0x000A690F`.
- RVA `0x394260`, recorded extent 7640 bytes: `0x003944F8`, `0x0039453C`, `0x0039454D`, `0x003945AD`.

Local byte-hit candidates outside these extents are also preserved in that raw log. Their containing-body boundaries remain open and do not establish another datum identity. The original contract log retains the complete byte-hit inventory.

The body at RVA 0x00394260 is also a writer. Store 0x003944F8 clears the active pointer, 0x0039453C publishes the pointer returned by virtual slot +0xC0, and 0x0039454D copies the pointer from 0x012F7198 without adjustment. Store 0x003945AD publishes the selected other game-mode view, including a receiver +0x20 view on one branch. The datum is an active GameInfo view, not a separately allocated object in all modes.

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F708C-retail.log`, `012F708C-routes.log`, `012F708C-source.log` and `012F708C-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
