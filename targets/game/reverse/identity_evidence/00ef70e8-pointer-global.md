# Datum identity at VA 0x012F70E8

The datum is `?TheLadderList@@3PAVLadderList@@A` in `game/GameEngine/Source/GameNetwork/GameSpy/LadderDefs.cpp`. The LadderList singleton for online ladder selection.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

SetUpGameSpy constructs and publishes this pointer at RVA 0x00637A35; TearDownGameSpy deletes it and clears it at 0x006335B7. HandleQMLadderSelection, HandleCustomLadderSelection and the quick-match update at 0x005053C0 use it as the ladder-list receiver. The BfmeK1058 view names that same receiver and is retained only as a cast for its existing callee pin.

Zero Hour GameEngine/Source/GameNetwork/GameSpy/LadderDefs.cpp:48 defines LadderList *TheLadderList; Include/GameNetwork/GameSpy/LadderDefs.h:86 declares it.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheLadderList@@3PAVLadderList@@A` | 8 |
| `?g_bfmeK1058@@3PAVBfmeK1058@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?HandleCustomLadderSelection@@YAXH@Z` at RVA `0x004D3E80` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGame.cpp)
- `?HandleQMLadderSelection@@YAXH@Z` at RVA `0x00505300` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenu.cpp)
- `?PopulateCustomLadderComboBox@@YAXXZ` at RVA `0x004D6420` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopulateCustomLadderComboBox.cpp)
- `?PopulateCustomLadderListBox@@YAXPAVGameWindow@@@Z` at RVA `0x004D5D90` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopulateCustomLadderListBox.cpp)
- `?PopupLadderSelectSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004D8A80` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupLadderSelect.cpp)
- `?RCGameDetailsMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004D8440` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupLadderSelect.cpp)
- `?TearDownGameSpy@@YAXXZ` at RVA `0x00633390` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp)
- `?UpdateStartButton@@YAXXZ` at RVA `0x00505570` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenu.cpp)
- `?WOLLobbyMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004FC7C0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuSystem.cpp)
- `?bfmeGo1058D@BfmeD1058@@QAEXXZ` at RVA `0x005053C0` (game/GameEngine/Source/Common/BfmeConv1058.cpp)
- `?createGame@@YAXXZ` at RVA `0x004D58F0` (game/GameEngine/Source/GameNetwork/GameSpy/PopupHostGameCreateGame.cpp)
- `?d_00508660@@YAXXZ` at RVA `0x00508660` (game/gen_asm/d_004e1090.asm)
- `?d_0053e870@@YAXXZ` at RVA `0x0053E870` (game/gen_asm/d_00536dc0.asm)
- `?d_00559e60@@YAXXZ` at RVA `0x00559E60` (game/gen_asm/d_00557c00.asm)
- `?d_0055ae10@@YAXXZ` at RVA `0x0055AE10` (game/gen_asm/d_00557c00.asm)
- `?d_0055b200@@YAXXZ` at RVA `0x0055B200` (game/gen_asm/d_00557c00.asm)
- `?dispatch@Rva005584B0Owner@@QAEXXZ` at RVA `0x005584B0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva005584B0Dispatch.cpp)
- `?gameTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z` at RVA `0x0062CFF0` (game/GameEngine/Source/GameNetwork/GameSpy/GameTooltipThunk.cpp)
- `?insertGame@@YAHPAVGameWindow@@PAVGameSpyStagingRoom@@_N@Z` at RVA `0x0062DB90` (game/GameEngine/Source/GameNetwork/GameSpy/LobbyUtils_insertGame.asm)
- `?populateLadderList@BfmeQuickMatchLadderPanel@@QAEXXZ` at RVA `0x00508C80` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchPopulateLadder.cpp)
- `?populateQuickMatchMapSelectListbox@BfmeAptScreenQuickMatchMenu@@QAEXAAVQuickMatchPreferences@@@Z` at RVA `0x00507F70` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuPopulateMapSelectListbox.cpp)
- `?rva005091F0InitGadgets@BfmeAptScreenQuickMatchMenu@@QAEXXZ` at RVA `0x005091F0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuInitGadgets.cpp)
- `?rva00509B30Request@BfmeAptScreenQuickMatchMenu@@QAEXPAVGameWindow@@@Z` at RVA `0x00509B30` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuRequest.cpp)
- `?rva005585B0SaveOptions@BfmeAptScreenOnlineQuickMatch@@QAEXXZ` at RVA `0x005585B0` (game/GameEngine/Source/GameClient/GUI/OnlineQuickMatchSaveOptions.cpp)
- `?saveQuickMatchOptions@BfmeAptScreenQuickMatchMenu@@QAEXXZ` at RVA `0x005063E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuSaveOptions.cpp)
- `?system@BfmeAptScreenQuickMatchMenu@@QAE?AW4WindowMsgHandledType@@III@Z` at RVA `0x0050A470` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuSystem.cpp)
- `?updateLadderDetails@@YAXHPAVGameWindow@@0@Z` at RVA `0x004D7E60` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupLadderSelect.cpp)

Writers:

- `?SetUpGameSpy@@YAXPBD0@Z` at RVA `0x006377D0` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_SetUpGameSpy_Thunk.cpp)
- `?TearDownGameSpy@@YAXXZ` at RVA `0x00633390` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F70E8-retail.log`, `012F70E8-routes.log`, `012F70E8-source.log` and `012F70E8-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
