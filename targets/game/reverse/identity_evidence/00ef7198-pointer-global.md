# Datum identity at VA 0x012F7198

The datum is `?TheGameSpyGame@@3PAVGameSpyStagingRoom@@A` in `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp`. The current GameSpyStagingRoom singleton.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

The GameSpy setup/teardown and matched launch-game, NAT and lobby bodies use this pointer as the staging-room receiver. The map-select body at 0x00503FA0 calls the inherited GameInfo map getter on this same pointer. A GameInfo view at that use is a receiver cast, not a separate global identity.

Zero Hour GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp:56 defines GameSpyStagingRoom *TheGameSpyGame and Include/GameNetwork/GameSpy/StagingRoomGameInfo.h:159 declares it. The older GameSpyGameInfo reference is a separate legacy source declaration; the staged-room uses and retail launch-game contract support the active type.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheGameSpyGame@@3PAVBfmeEstablishGameSpyGame@@A` | 0 |
| `?TheGameSpyGame@@3PAVGameSpyStagingRoom@@A` | 28 |
| `?g_bfmeK1022@@3PAVBfmeK1022@@A` | 0 |
| `?g_rva004C84C0B@@3PAVRva004C84C0B@@A` | 0 |
| `?TheGameSpyGame@@3PAVGameInfo@@A` (additional source-only spelling) | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??0BfmeAptScreenOnlineQuickMatch@@QAE@H@Z` at RVA `0x00559400` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineQuickMatchConstructor.cpp)
- `??0LoadScreen0051BF30@@QAE@I@Z` at RVA `0x0051BF30` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptLoadScreen.cpp)
- `?BuddyControlSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004ED400` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyControlSystem.cpp)
- `?InitWOLGameGadgets@@YAXXZ` at RVA `0x004F2C00` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?Rva0009B6C0RecorderStart@RecorderClass@@IAEXHHHH@Z` at RVA `0x0009B6C0` (game/GameEngine/Source/Common/System/RecorderStartRecording.cpp)
- `?Rva00503FA0InitializeMapSelectMenu@@YAXXZ` at RVA `0x00503FA0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLMapSelectInitialize00503FA0.cpp)
- `?Rva00576C20@BfmeAptScreenScoreScreen@@QAEXPAVPlayer@@PAVGameSlot@@H@Z` at RVA `0x00576C20` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva00576C20.cpp)
- `?ShowEstablishConnectionsWindow@@YAXXZ` at RVA `0x004C8660` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/EstablishConnectionsWindow.cpp)
- `?StartPressed@@YAXXZ` at RVA `0x004F49E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?WOLGameSetupMenuUpdate@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x004F6B60` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?WOLLobbyMenuInit@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x004FBBE0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuUpdate.cpp)
- `?WOLLobbyMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004FC7C0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuSystem.cpp)
- `?addText@GameSpyInfo@@UAEHVUnicodeString@@HPAVGameWindow@@@Z` at RVA `0x00625570` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoAddText.cpp)
- `?applyLocalSlotToPreferences@BfmeAptScreenOnlineCustomMatch@@QAEXXZ` at RVA `0x005392B0` (game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchApplyLocalSlot.cpp)
- `?applySelectedMap@BfmeAptScreenOnlineCustomMatch@@QAE_NABVAsciiString@@@Z` at RVA `0x0053D650` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchApplySelectedMap.cpp)
- `?bfmeGo1022J@BfmeJ1022@@QAEXH@Z` at RVA `0x00558470` (game/GameEngine/Source/Common/BfmeConv1022.cpp)
- `?bfmeStartPressed@Rva0053DA20Screen@@QAEX_NPAX@Z` at RVA `0x0053DA20` (game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchStartPressed.cpp)
- `?createGame0053E390@OnlineStateUpdate00544E40@@QAEXXZ` at RVA `0x0053E390` (game/GameEngine/Source/GameClient/GUI/OnlineStateUpdateCreateGame0053E390.cpp)
- `?createGame@@YAXXZ` at RVA `0x004D58F0` (game/GameEngine/Source/GameNetwork/GameSpy/PopupHostGameCreateGame.cpp)
- `?d_004f52c0@@YAXXZ` at RVA `0x004F52C0` (game/gen_asm/d_004e1090.asm)
- `?d_00504600@@YAXXZ` at RVA `0x00504600` (game/gen_asm/d_004e1090.asm)
- `?d_0050aa30@@YAXXZ` at RVA `0x0050AA30` (game/gen_asm/d_005091f0.asm)
- `?d_0051c2d0@@YAXXZ` at RVA `0x0051C2D0` (game/gen_asm/d_0051b7e0.asm)
- `?d_0053dfc0@@YAXXZ` at RVA `0x0053DFC0` (game/gen_asm/d_00499050.asm)
- `?d_0053e870@@YAXXZ` at RVA `0x0053E870` (game/gen_asm/d_00536dc0.asm)
- `?d_005409a0@@YAXXZ` at RVA `0x005409A0` (game/gen_asm/d_00499050.asm)
- `?d_00545310@@YAXXZ` at RVA `0x00545310` (game/gen_asm/d_00545310.asm)
- `?dispatchEvents@BFMENetworkBackend@@QAEXXZ` at RVA `0x0065CA50` (game/GameEngine/Source/GameNetwork/native_network_dispatcher.cpp)
- `?establishConnectionPaths@NAT@@QAEXXZ` at RVA `0x00672A60` (game/GameEngine/Source/GameNetwork/NAT_establishConnectionPaths.cpp)
- `?handleMatched@Rva00559840QuickMatch@@QAEXAAVPeerResponse@@@Z` at RVA `0x00559840` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp)
- `?launchGame@GameSpyStagingRoom@@QAEXXZ` at RVA `0x00639950` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyStagingRoomLaunchGame.cpp)
- `?populatePlayerInfo@@YAXPAVPlayer@@H@Z` at RVA `0x004E5DF0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreen_populatePlayerInfo.cpp)
- `?processGameSpyStatsAuthKeyCommand@BFMEConnectionManager@@QAEXPAX@Z` at RVA `0x006645B0` (game/GameEngine/Source/GameNetwork/ConnectionManager_processGameSpyStatsAuthKey.cpp)
- `?rva004C84C0Teardown@@YAXXZ` at RVA `0x004C84C0` (game/GameEngine/Source/Common/Rva004C84C0Teardown.cpp)
- `?rva005091F0InitGadgets@BfmeAptScreenQuickMatchMenu@@QAEXXZ` at RVA `0x005091F0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuInitGadgets.cpp)
- `?savePlayerInfo@@YAXXZ` at RVA `0x004F1330` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLSavePlayerInfo.cpp)
- `?setGameOptions@GameSpyInfo@@UAEXXZ` at RVA `0x00635D90` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_setGameOptions.cpp)
- `?update@BFMEConnectionManager@@QAEXXZ` at RVA `0x0066AB30` (game/GameEngine/Source/GameNetwork/native_connection_timing.cpp)
- `?update@NAT@@QAE?AW4NATStateType@@XZ` at RVA `0x006727C0` (game/GameEngine/Source/GameNetwork/NAT_update.cpp)
- `?update@OnlineStateUpdate00544E40@@QAEXXZ` at RVA `0x00544E40` (game/GameEngine/Source/GameClient/GUI/OnlineStateUpdate00544E40.cpp)
- `?update@Rva00506720Layout@@QAEXPAX@Z` at RVA `0x00506720` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuUpdate.cpp)
- `?rva0055A240@Rva00559840QuickMatch@@QAEXXZ` at RVA `0x0055A240` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp)

Writers:

- `??0GameSpyInfo@@QAE@XZ` at RVA `0x00636D90` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp)
- `??1GameSpyInfo@@UAE@XZ` at RVA `0x00637590` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp)

## Supplemental retail accesses

`build/rlink/pointer-globals-20261005/012F7198-missing-refs.log` disassembles additional Ghidra extents from their recorded starts. These are retail instructions, not a decompiler draft. The additional containing bodies and instruction sites are:

- RVA `0xA5D40`, recorded extent 4125 bytes: `0x000A5D74`, `0x000A5D7F`, `0x000A5F99`, `0x000A6111`, `0x000A6145`, `0x000A64DD`, `0x000A66C8`, `0x000A6850`, `0x000A6867`.
- RVA `0x394260`, recorded extent 7640 bytes: `0x00394544`, `0x00395C6A`.

Local byte-hit candidates outside these extents are also preserved in that raw log. Their containing-body boundaries remain open and do not establish another datum identity. The original contract log retains the complete byte-hit inventory.

The body at RVA 0x00394260 reads this pointer at 0x00394544 and publishes it unchanged to TheGameInfo at 0x0039454D. This independently supports the existing GameInfo receiver view without inventing a new class relationship.

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F7198-retail.log`, `012F7198-routes.log`, `012F7198-source.log` and `012F7198-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
