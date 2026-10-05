# Datum identity at VA 0x012F70E4

The datum is `?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A` in `game/GameEngine/Source/GameNetwork/GameSpy/GSConfig.cpp`. The GameSpy configuration interface singleton.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

SetUpGameSpy at 0x006377D0 calls the configuration factory and stores its returned pointer at VA 0x012F70E4 (store at RVA 0x00637A0C). TearDownGameSpy at 0x00633390 deletes it virtually and clears it at 0x006335CD. Network and menu callers invoke configuration methods through the interface vtable.

Zero Hour GameEngine/Source/GameNetwork/GameSpy/GSConfig.cpp:47 and Include/GameNetwork/GameSpy/GSConfig.h:71 both use GameSpyConfigInterface *TheGameSpyConfig. A concrete implementation exists behind the interface; the global type is the interface.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheGameSpyConfig@@3PAVGameSpyConfig@@A` | 0 |
| `?TheGameSpyConfig@@3PAVGameSpyConfigInterface@@A` | 26 |
| `?g_obj12F70E4@@3PAVBfmeThresholdSource@@A` | 0 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??0LadderList@@QAE@XZ` at RVA `0x0062C020` (game/GameEngine/Source/GameNetwork/GameSpy/LadderListConstructor.cpp)
- `?PopulateLobbyPlayerListbox@@YAXXZ` at RVA `0x004FB500` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuPopulateLobbyPlayerListbox.cpp)
- `?Rva005406E0@BfmeAptScreenOnlineCustomMatch@@QAE_NXZ` at RVA `0x005406E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchRva005406E0.cpp)
- `?TearDownGameSpy@@YAXXZ` at RVA `0x00633390` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp)
- `?WOLDisplaySlotList@@YAXXZ` at RVA `0x004F1E10` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?WOLLobbyMenuInit@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x004FBBE0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuUpdate.cpp)
- `?WOLLobbyMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004FC7C0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuSystem.cpp)
- `?_bfme_checkLogin@BfmeAptScreenOnlineLogin@@QAEXXZ` at RVA `0x00550AD0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineLoginCheckLogin.cpp)
- `?addGroupRoom@GameSpyInfo@@UAEXVGameSpyGroupRoom@@@Z` at RVA `0x00636650` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoAddGroupRoomThunk.cpp)
- `?bfmeAddSavedIgnoreFromEntryE6B@@YGXPAVGameWindow@@@Z` at RVA `0x0052E680` (game/GameEngine/Source/GameNetwork/GameSpy/BfmeAddSavedIgnoreFromEntry.cpp)
- `?createGame0053E390@OnlineStateUpdate00544E40@@QAEXXZ` at RVA `0x0053E390` (game/GameEngine/Source/GameClient/GUI/OnlineStateUpdateCreateGame0053E390.cpp)
- `?createGame@@YAXXZ` at RVA `0x004D58F0` (game/GameEngine/Source/GameNetwork/GameSpy/PopupHostGameCreateGame.cpp)
- `?d_004dafa0@@YAXXZ` at RVA `0x004DAFA0` (game/gen_asm/d_004d3970.asm)
- `?d_005337e0@@YAXXZ` at RVA `0x005337E0` (game/gen_asm/d_00499050.asm)
- `?d_0053ff10@@YAXXZ` at RVA `0x0053FF10` (game/gen_asm/d_0052bd50.asm)
- `?d_0055ae10@@YAXXZ` at RVA `0x0055AE10` (game/gen_asm/d_00557c00.asm)
- `?d_0055b200@@YAXXZ` at RVA `0x0055B200` (game/gen_asm/d_00557c00.asm)
- `?detectionBeginUpdate@FirewallHelperClass@@QAE_NXZ` at RVA `0x0066EFA0` (game/GameEngine/Source/GameNetwork/FirewallHelperDetectionBeginUpdate.cpp)
- `?getManglerName@FirewallHelperClass@@SAXHPAD@Z` at RVA `0x0066EF00` (game/GameEngine/Source/GameNetwork/FirewallHelper.cpp)
- `?getPingValue@GameSpyInfo@@UAEHABVAsciiString@@@Z` at RVA `0x00631700` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfo_getPingValue.cpp)
- `?handleMatched@Rva00559840QuickMatch@@QAEXAAVPeerResponse@@@Z` at RVA `0x00559840` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp)
- `?insertGame@@YAHPAVGameWindow@@PAVGameSpyStagingRoom@@_N@Z` at RVA `0x0062DB90` (game/GameEngine/Source/GameNetwork/GameSpy/LobbyUtils_insertGame.asm)
- `?joinBestGroupRoom@GameSpyInfo@@UAEXXZ` at RVA `0x00634EF2` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfo_joinBestGroupRoomMethodThunk.cpp)
- `?parseLadder@@YAPAVLadderInfo@@VAsciiString@@@Z` at RVA `0x0062AD50` (game/GameEngine/Source/GameNetwork/GameSpy/LadderParse.cpp)
- `?pick@BfmeAptScreenPickByThreshold@@QAEPAXH@Z` at RVA `0x0055BDD0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptScreenPickByThreshold.cpp)
- `?populateGroupRoomListbox_004FA240@@YAXPAVGameWindow@@@Z` at RVA `0x004FA240` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuUpdate.cpp)
- `?populateQuickMatchMapSelectListbox@BfmeAptScreenQuickMatchMenu@@QAEXAAVQuickMatchPreferences@@@Z` at RVA `0x00507F70` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuPopulateMapSelectListbox.cpp)
- `?rva005091F0InitGadgets@BfmeAptScreenQuickMatchMenu@@QAEXXZ` at RVA `0x005091F0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuInitGadgets.cpp)
- `?rva00509B30Request@BfmeAptScreenQuickMatchMenu@@QAEXPAVGameWindow@@@Z` at RVA `0x00509B30` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuRequest.cpp)
- `?rva0052E990@BfmeAptScreenOnlineChat@@QAEXXZ` at RVA `0x0052E990` (game/GameEngine/Source/GameClient/GUI/OnlineChatRva0052E990.cpp)
- `?rva005397D0PopulateGroupRoomListbox@Rva005397D0AptScreen@@QAEXXZ` at RVA `0x005397D0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptScreenPopulateGroupRoomListboxRva005397D0.cpp)
- `?rva00558A30Ready@BfmeAptScreenOnlineQuickMatch@@QAE_NXZ` at RVA `0x00558A30` (game/GameEngine/Source/GameClient/GUI/OnlineQuickMatchPopulateMaxPing.cpp)
- `?saveQuickMatchOptions@BfmeAptScreenQuickMatchMenu@@QAEXXZ` at RVA `0x005063E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuSaveOptions.cpp)
- `?startPings@@YAXXZ` at RVA `0x005019A0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenuStartPings.cpp)
- `?startPings@Rva00550500@@YAXXZ` at RVA `0x00550500` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva00550500StartPings.cpp)
- `?update@BFMEDisconnectManager@@QAEXPAX@Z` at RVA `0x0066C8D0` (game/GameEngine/Source/GameNetwork/native_connection_timing.cpp)
- `?update@Rva00506720Layout@@QAEXPAX@Z` at RVA `0x00506720` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuUpdate.cpp)
- `?classify@Rva005329Classify@@QAEXPAVRva005329C0Obj@@H@Z` at RVA `0x00532280` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva00532280Classify.cpp)

Writers:

- `?SetUpGameSpy@@YAXPBD0@Z` at RVA `0x006377D0` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_SetUpGameSpy_Thunk.cpp)
- `?TearDownGameSpy@@YAXXZ` at RVA `0x00633390` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F70E4-retail.log`, `012F70E4-routes.log`, `012F70E4-source.log` and `012F70E4-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
