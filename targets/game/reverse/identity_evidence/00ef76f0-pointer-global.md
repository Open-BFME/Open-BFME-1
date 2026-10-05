# Datum identity at VA 0x012F76F0

The datum is `?TheGameSpyPSMessageQueue@@3PAVGameSpyPSMessageQueueInterface@@A` in `game/GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp`. The GameSpy persistent-storage message queue interface singleton.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

Setup/teardown store and clear this pointer; statistics, ladder and persistent-storage callbacks dispatch through its interface. RVA 0x0065B350 invokes vtable slot +0x18 for a response; player-tooltip RVA 0x0053AF50 uses the same pointer for player statistics. The BfmeQueueEUG spelling is a local view of this same queue.

Zero Hour GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp:425 defines GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue; Include/GameNetwork/GameSpy/PersistentStorageThread.h:184 declares it.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheGameSpyPSMessageQueue@@3PAVGameSpyPSMessageQueue@@A` | 0 |
| `?TheGameSpyPSMessageQueue@@3PAVGameSpyPSMessageQueueInterface@@A` | 24 |
| `?g_bfmeQueueEUG@@3PAVBfmeQueueEUG@@A` | 2 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?MpOwnerUpdatePlayerTooltip@AptOnlineCustomMatch@@QAEXVAsciiString@@@Z` at RVA `0x005307B0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva005307B0ChatPlayerTooltip.cpp)
- `?PopulatePlayerInfoWindows@@YAXVAsciiString@@@Z` at RVA `0x004DBE80` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupPlayerInfo_populate.cpp)
- `?Rva0053AF50PlayerTooltip@@YGXPAVGameSpyGameSlot@@@Z` at RVA `0x0053AF50` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva0053AF50StagingPlayerTooltip.cpp)
- `?SendStatsToOtherPlayers@@YAXPBVGameInfo@@@Z` at RVA `0x004F3B10` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SendStatsToOtherPlayers.cpp)
- `?TearDownGameSpy@@YAXXZ` at RVA `0x00633390` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp)
- `?UpdateBestLadderRanks004DBBF0@@YAXPAVPSPlayerStats@@@Z` at RVA `0x004DBBF0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/UpdateBestLadderRanks004DBBF0.cpp)
- `?WOLBuddyOverlayRCMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004EFED0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlayRCMenuSystem.cpp)
- `?WOLGameSetupMenuUpdate@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x004F6B60` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?WOLLocaleSelectSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004FF2E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLocaleSelectPopup.cpp)
- `?_bfme_cacheLocalPlayerStatsWithLocale@@YAXXZ` at RVA `0x0055CD80` (game/GameEngine/Source/GameNetwork/GameSpy/CacheLocalPlayerStatsWithLocale.cpp)
- `?_bfme_update@BfmeAptScreenOnlineLogin@@UAEXXZ` at RVA `0x00552100` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineLoginUpdate.cpp)
- `?bfmeRequestEUG@@YAXXZ` at RVA `0x006300D0` (game/GameEngine/Source/Common/BfmeConv1990.cpp)
- `?d_004dd2b0@@YAXXZ` at RVA `0x004DD2B0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupPlayerInfo_responses.cpp)
- `?d_0051c2d0@@YAXXZ` at RVA `0x0051C2D0` (game/gen_asm/d_0051b7e0.asm)
- `?d_005337e0@@YAXXZ` at RVA `0x005337E0` (game/gen_asm/d_00499050.asm)
- `?d_0055b200@@YAXXZ` at RVA `0x0055B200` (game/gen_asm/d_00557c00.asm)
- `?d_00649790@@YAXXZ` at RVA `0x00649790` (game/gen_asm/d_00610140.asm)
- `?dispatchEvents@BFMENetworkBackend@@QAEXXZ` at RVA `0x0065CA50` (game/GameEngine/Source/GameNetwork/native_network_dispatcher.cpp)
- `?doCDKeyAuthentication@@YA?AW4SerialAuthResult@@PAX@Z` at RVA `0x00648E30` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadDoCDKeyAuthentication.cpp)
- `?generateLadderGameResultsPacket@GameSpyStagingRoom@@QAE?AVAsciiString@@XZ` at RVA `0x00639190` (game/GameEngine/Source/GameNetwork/GameSpy/GenerateLadderGameResultsPacket.cpp)
- `?getPersistentDataCallback@@YAXHHW4persisttype_t@@HHJPADHPAX@Z` at RVA `0x0065C260` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageDataCallback.cpp)
- `?getPreorderCallback@@YAXHHW4persisttype_e@@HHHPADHPAX@Z` at RVA `0x0065AFE0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PSPlayerStats_Destructor.cpp)
- `?handle@Rva0065B350@@QAEHPAXHPBDHH@Z` at RVA `0x0065B350` (game/GameEngine/Source/GameNetwork/Rva0065B350MapLookupResponse.cpp)
- `?handleXKResponse@Rva0065B350@@QAEHPAXHPBDHH@Z` at RVA `0x0065B500` (game/GameEngine/Source/GameNetwork/Rva0065B350XKResponse.cpp)
- `?init@GameSpyLoadScreen@@` at RVA `0x00493120` (game/GameEngine/Source/GameClient/GUI/LoadScreenInit.cpp)
- `?insertPlayerInListbox@Rva00530550@@YAHPAVGameWindow@@ABVPlayerInfo@@H@Z` at RVA `0x00530550` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/InsertPlayerInListbox00530550.cpp)
- `?launchGame@GameSpyStagingRoom@@QAEXXZ` at RVA `0x00639950` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyStagingRoomLaunchGame.cpp)
- `?method@Rva0062A7D0Owner@@QAE_NXZ` at RVA `0x0062A7D0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchPopulateLadder.cpp)
- `?populatePlayerInfo@@YAXPAVPlayer@@H@Z` at RVA `0x004E5DF0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreen_populatePlayerInfo.cpp)
- `?rva004F2410PlayerTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z` at RVA `0x004F2410` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?rva00509B30Request@BfmeAptScreenQuickMatchMenu@@QAEXPAVGameWindow@@@Z` at RVA `0x00509B30` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuRequest.cpp)
- `?shutdown@BfmeAptScreenOnlineShell@@UAEHXZ` at RVA `0x0055D680` (game/GameEngine/Source/GameClient/GUI/OnlineShellShutdown.cpp)
- `?stagingRoomPlayerEnum@@YAXPAXHW4RoomType@@HPBDH0@Z` at RVA `0x006494B0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp)
- `?update@NAT@@QAE?AW4NATStateType@@XZ` at RVA `0x006727C0` (game/GameEngine/Source/GameNetwork/NAT_update.cpp)
- `?update@Rva00506720Layout@@QAEXPAX@Z` at RVA `0x00506720` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuUpdate.cpp)
- `?method0065B100@Rva0065B350@@QAEHPAXHPBDHH@Z` at RVA `0x0065B100` (game/GameEngine/Source/GameNetwork/Rva0065B350MapLookupResponse.cpp)
- `?rva0055A240@Rva00559840QuickMatch@@QAEXXZ` at RVA `0x0055A240` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp)

Writers:

- `?SetUpGameSpy@@YAXPBD0@Z` at RVA `0x006377D0` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_SetUpGameSpy_Thunk.cpp)
- `?TearDownGameSpy@@YAXXZ` at RVA `0x00633390` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp)

## Supplemental retail accesses

`build/rlink/pointer-globals-20261005/012F76F0-missing-refs.log` disassembles additional Ghidra extents from their recorded starts. These are retail instructions, not a decompiler draft. The additional containing bodies and instruction sites are:

- RVA `0xA5D40`, recorded extent 4125 bytes: `0x000A5DAE`, `0x000A5FF8`, `0x000A61AA`, `0x000A62BB`, `0x000A6B7E`, `0x000A6BC3`, `0x000A6BFE`.

Local byte-hit candidates outside these extents are also preserved in that raw log. Their containing-body boundaries remain open and do not establish another datum identity. The original contract log retains the complete byte-hit inventory.

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F76F0-retail.log`, `012F76F0-routes.log`, `012F76F0-source.log` and `012F76F0-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
