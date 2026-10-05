# Datum identity at VA 0x012F71C8

The datum is `?TheGameSpyPeerMessageQueue@@3PAVGameSpyPeerMessageQueueInterface@@A` in `game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp`. The GameSpy peer request and response queue interface singleton.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

SetUpGameSpy publishes this pointer at RVA 0x00637927. TearDownGameSpy clears it at RVA 0x0063354B after deletion. The many matched peer callbacks and lobby/online UI bodies submit requests and pump responses through its vtable.

Zero Hour GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp:180 defines GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue; Include/GameNetwork/GameSpy/PeerThread.h:390 declares the same type.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheGameSpyPeerMessageQueue@@3PAVGameSpyPeerMessageQueueInterface@@A` | 61 |
| `?TheGameSpyPeerMessageQueue@@3PAVRva0050D030ReferencePeerMessageQueueInterface@@A` | 0 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??0BfmeAptScreenOnlineHome@@QAE@H@Z` at RVA `0x005484E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineHomeConstructor.cpp)
- `?HandleBuddyResponses@@YAXXZ` at RVA `0x004EE510` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyResponses.cpp)
- `?QRAddErrorCallback@@YAXPAXW4qr2_error_t@@PAD0@Z` at RVA `0x00646D80` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/QRAddErrorCallback.cpp)
- `?Rva0053DEA0SendRoomUtmEUI@@YAXXZ` at RVA `0x0053DEA0` (game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchSendRoomUtmEUI.cpp)
- `?Rva005406E0@BfmeAptScreenOnlineCustomMatch@@QAE_NXZ` at RVA `0x005406E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchRva005406E0.cpp)
- `?Rva00646E10CounterCallback@@YAXPAX00HHIHIIPAURva00646E10Owner@@@Z` at RVA `0x00646E10` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/QRAddErrorCallback.cpp)
- `?SendStatsToOtherPlayers@@YAXPBVGameInfo@@@Z` at RVA `0x004F3B10` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SendStatsToOtherPlayers.cpp)
- `?StartPressed@@YAXXZ` at RVA `0x004F49E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?TearDownGameSpy@@YAXXZ` at RVA `0x00633390` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp)
- `?Thread_Function@PeerThreadClass@@UAEXXZ` at RVA `0x0064FB90` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread_ThreadFunction.cpp)
- `?WOLGameSetupMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004F5D10` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?WOLGameSetupMenuUpdate@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x004F6B60` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?WOLLobbyMenuInit@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x004FBBE0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuUpdate.cpp)
- `?WOLLobbyMenuShutdown@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x004FAF70` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuShutdown_Thunk.cpp)
- `?WOLLobbyMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x004FC7C0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuSystem.cpp)
- `?WOLLobbyMenuUpdate@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x004FD9B0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuUpdate.cpp)
- `?WOLLoginMenuUpdate@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x005001D0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenuUpdate.cpp)
- `?WOLWelcomeMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` at RVA `0x0050D030` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLWelcomeMenu.cpp)
- `?WOLWelcomeMenuUpdate@Rva0050CA80Twin@@YAXPAVWindowLayout@@PAX@Z` at RVA `0x0050CA80` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLWelcomeMenuUpdateTwin.cpp)
- `?_bfme_stopQuickMatchRequest@@YGXH@Z` at RVA `0x005592D0` (game/GameEngine/Source/GameNetwork/GameSpy/StopQuickMatchRequest.cpp)
- `?_bfme_update@BfmeAptScreenOnlineLogin@@UAEXXZ` at RVA `0x00552100` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineLoginUpdate.cpp)
- `?applySlotColor@BfmeAptScreenOnlineCustomMatch@@QAE_NPAVGameSlot@@H@Z` at RVA `0x0053CB90` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchApplySlotColor.cpp)
- `?applySlotPlayerTemplate@BfmeAptScreenOnlineCustomMatch@@QAE_NPAVGameSlot@@H@Z` at RVA `0x0053CE60` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchApplySlotPlayerTemplate.cpp)
- `?applySlotStartPos@Rva0053D7D0OnlineCustomMatch@@QAE_NPAVGameSlot@@H@Z` at RVA `0x0053D7D0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchApplySlotStartPos.cpp)
- `?applySlotState@BfmeAptScreenOnlineCustomMatch@@QAE_NPAVGameSlot@@HH@Z` at RVA `0x0053D3D0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchApplySlotState.cpp)
- `?applySlotTeam@BfmeAptScreenOnlineCustomMatch@@QAE_NPAVGameSlot@@H@Z` at RVA `0x0053D170` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchApplySlotTeam.cpp)
- `?bfmeAcceptPressed@Rva0053DBE0Screen@@QAEX_N@Z` at RVA `0x0053DBE0` (game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchAcceptPressed.cpp)
- `?bfmeQuitEAV@@YAXPAXHPAD@Z` at RVA `0x00647100` (game/GameEngine/Source/GameNetwork/GameSpy/BfmeQuitEAV.cpp)
- `?bfmeResetEAY@BfmeHostEAY@@QAEXXZ` at RVA `0x00635230` (game/GameEngine/Source/GameNetwork/GameSpy/BfmeHostEAY_bfmeResetEAY.cpp)
- `?bfmeStartPressed@Rva0053DA20Screen@@QAEX_NPAX@Z` at RVA `0x0053DA20` (game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchStartPressed.cpp)
- `?createGame0053E390@OnlineStateUpdate00544E40@@QAEXXZ` at RVA `0x0053E390` (game/GameEngine/Source/GameClient/GUI/OnlineStateUpdateCreateGame0053E390.cpp)
- `?createGame@@YAXXZ` at RVA `0x004D58F0` (game/GameEngine/Source/GameNetwork/GameSpy/PopupHostGameCreateGame.cpp)
- `?d_004dd2b0@@YAXXZ` at RVA `0x004DD2B0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupPlayerInfo_responses.cpp)
- `?d_004f52c0@@YAXXZ` at RVA `0x004F52C0` (game/gen_asm/d_004e1090.asm)
- `?d_005351c0@@YAXXZ` at RVA `0x005351C0` (game/gen_asm/d_0052b540.asm)
- `?d_0053dfc0@@YAXXZ` at RVA `0x0053DFC0` (game/gen_asm/d_00499050.asm)
- `?d_0053e870@@YAXXZ` at RVA `0x0053E870` (game/gen_asm/d_00536dc0.asm)
- `?d_0053ff10@@YAXXZ` at RVA `0x0053FF10` (game/gen_asm/d_0052bd50.asm)
- `?d_005409a0@@YAXXZ` at RVA `0x005409A0` (game/gen_asm/d_00499050.asm)
- `?d_0055b200@@YAXXZ` at RVA `0x0055B200` (game/gen_asm/d_00557c00.asm)
- `?d_00649790@@YAXXZ` at RVA `0x00649790` (game/gen_asm/d_00610140.asm)
- `?d_0064b6b0@@YAXXZ` at RVA `0x0064B6B0` (game/gen_asm/d_004e8320.asm)
- `?d_00651054@@YAXXZ` at RVA `0x00651054` (game/gen_asm/d_00644950.asm)
- `?disconnectedCallback@@YAXPAXPBD0@Z` at RVA `0x00646F50` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadDisconnectedCallback.cpp)
- `?doQuickMatch@PeerThreadClass@@AAEXPAX@Z` at RVA `0x0064EFD0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread_DoQuickMatch.cpp)
- `?errorCallback@BuddyThreadClass@@QAEXPAPAXPAUGPErrorArg@@@Z` at RVA `0x0063D210` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThreadErrorCallback.cpp)
- `?getRoomKeysCallback@@YAXPAXHW4RoomType@@PBDHPAPAD30@Z` at RVA `0x0064EA90` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/getRoomKeysCallback.cpp)
- `?globalKeyChangedCallback@@YAXPAXPBD110@Z` at RVA `0x0064AC70` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/GlobalKeyChangedCallback.cpp)
- `?handleColorSelection@@YAXH@Z` at RVA `0x004F3F20` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?handlePlayerTemplateSelection@@YAXH@Z` at RVA `0x004F41E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?handleQMMatch@PeerThreadClass@@QAEXPAXHHQAPAD11111@Z` at RVA `0x00649180` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerHandleQMMatch.cpp)
- `?handleStartPositionSelection@@YAXHH@Z` at RVA `0x004F44E0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?handleTeamSelection@@YAXH@Z` at RVA `0x004F4750` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?handleText@GameSpyInfo@@UAE_NVUnicodeString@@@Z` at RVA `0x006260C0` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoHandleText.cpp)
- `?joinBestGroupRoom@GameSpyInfo@@UAEXXZ` at RVA `0x00634EF2` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfo_joinBestGroupRoomMethodThunk.cpp)
- `?joinGame@@YAXVAsciiString@@@Z` at RVA `0x004D7580` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupJoinGameJoin.cpp)
- `?joinGroupRoom@GameSpyInfo@@UAEXH@Z` at RVA `0x00634BF0` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfo_joinGroupRoom.cpp)
- `?joinRoomCallback@@YAXPAXHW4PEERJoinResult@@W4RoomType@@0@Z` at RVA `0x0064ECC0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadJoinRoomCallback.cpp)
- `?leaveGroupRoom@GameSpyInfo@@UAEXXZ` at RVA `0x00634CE0` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfo_leaveGroupRoom_Thunk.cpp)
- `?listGroupRoomsCallback@@YAXPAXHH0PBDHHHH0@Z` at RVA `0x00649610` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerListGroupRoomsCallback.cpp)
- `?lookupServer@Rva00648220PeerThreadMapView@@QAEHPAU_SBServer@@@Z` at RVA `0x00648220` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva00648220PeerThreadStaleServerLookup.cpp)
- `?nickErrorCallback@PeerThreadClass@@QAEXPAXHPBD@Z` at RVA `0x00649AE0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadNickErrorCallback.cpp)
- `?notifyTargetOfProbe@NAT@@IAEXPAVGameSlot@@@Z` at RVA `0x00671100` (game/GameEngine/Source/GameNetwork/NAT_notifyTargetOfProbe.cpp)
- `?notifyUsersOfConnectionDone@NAT@@IAEXH@Z` at RVA `0x006712E0` (game/GameEngine/Source/GameNetwork/NAT_notifyUsersOfConnectionDone.cpp)
- `?notifyUsersOfConnectionFailed@NAT@@IAEXH@Z` at RVA `0x006715C0` (game/GameEngine/Source/GameNetwork/NAT_notifyUsersOfConnectionFailed.cpp)
- `?playerChangedNickCallback@@YAXPAXW4RoomType@@PBD20@Z` at RVA `0x0064B240` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PlayerChangedNickCallback.cpp)
- `?playerFlagsChangedCallback@@YAXPAXW4RoomType@@PBDHH0@Z` at RVA `0x0064B540` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPlayerFlagsChangedCallback.cpp)
- `?playerInfoCallback@@YAXPAXW4RoomType@@PBDIH0@Z` at RVA `0x0064B3D0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPlayerInfoCallback.cpp)
- `?playerJoinedCallback@@YAXPAXW4RoomType@@PBD0@Z` at RVA `0x0064AE00` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPlayerJoinedCallback.cpp)
- `?playerLeftCallback@@YAXPAXW4RoomType@@PBD20@Z` at RVA `0x0064AF80` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PlayerLeftCallback.cpp)
- `?playerMessageCallback@@YAXPAXPBD1W4MessageType@@0@Z` at RVA `0x0064A2E0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerPlayerMessageCallback.cpp)
- `?playerUTMCallback@@YAXPAXPBD11H0@Z` at RVA `0x0064A950` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PlayerUTMCallback.cpp)
- `?postPeerRequest19@@YAXXZ` at RVA `0x0053AB90` (game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchPeerRequest19.cpp)
- `?pushStats@BfmePushStatsHost@@QAEXH@Z` at RVA `0x00559360` (game/GameEngine/Source/GameNetwork/GameSpy/PushStatsRequest.cpp)
- `?quickmatchEnumPlayersCallback@@YAXPAXHW4RoomType@@HPBDH0@Z` at RVA `0x00648FF0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadQuickmatchEnumPlayersCallback.cpp)
- `?roomKeyChangedCallback@@YAXPAXW4RoomType@@PBD220@Z` at RVA `0x0064E8F0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/RoomKeyChangedCallback.cpp)
- `?roomMessageCallback@@YAXPAXW4RoomType@@PBD2W4MessageType@@0@Z` at RVA `0x00649ED0` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerRoomMessageCallback.cpp)
- `?roomUTMCallback@@YAXPAXW4RoomType@@PBD22H0@Z` at RVA `0x0064A820` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/RoomUTMCallback.cpp)
- `?rva00509B30Request@BfmeAptScreenQuickMatchMenu@@QAEXPAVGameWindow@@@Z` at RVA `0x00509B30` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuRequest.cpp)
- `?send@NATSendMangledPortShim@@QAEXGPAVGameSlot@@@Z` at RVA `0x006718A0` (game/GameEngine/Source/GameNetwork/NATSendMangledPortNumberToTarget.cpp)
- `?sendChat@GameSpyInfo@@UAE_NVUnicodeString@@_NPAVGameWindow@@@Z` at RVA `0x00626230` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoSendChat.cpp)
- `?setGameOptions@GameSpyInfo@@UAEXXZ` at RVA `0x00635D90` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_setGameOptions.cpp)
- `?shutdownCompleteWOLGameSetupMenu@@YAXPAVWindowLayout@@@Z` at RVA `0x004F0DE0` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLGameSetupMenu.cpp)
- `?startGameList@GameSpyInfo@@QAEXXZ` at RVA `0x00634DD0` (game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfo_startGameList_Thunk.cpp)
- `?stop@BfmeQuickMatchStopBody@@QAEXXZ` at RVA `0x00506230` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenu.cpp)
- `?system@BfmeAptScreenQuickMatchMenu@@QAE?AW4WindowMsgHandledType@@III@Z` at RVA `0x0050A470` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuSystem.cpp)
- `?update@OnlineStateUpdate00544E40@@QAEXXZ` at RVA `0x00544E40` (game/GameEngine/Source/GameClient/GUI/OnlineStateUpdate00544E40.cpp)
- `?update@Rva00506720Layout@@QAEXPAX@Z` at RVA `0x00506720` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuUpdate.cpp)
- `?updatePeerResponses00547160@BfmeAptScreenOnlineHome@@UAEXXZ` at RVA `0x00547160` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineHomePeerResponses.cpp)
- `?rva0055A240@Rva00559840QuickMatch@@QAEXXZ` at RVA `0x0055A240` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineQuickMatch.cpp)

Writers:

- `?SetUpGameSpy@@YAXPBD0@Z` at RVA `0x006377D0` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_SetUpGameSpy_Thunk.cpp)
- `?TearDownGameSpy@@YAXXZ` at RVA `0x00633390` (game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp)

## Supplemental retail accesses

`build/rlink/pointer-globals-20261005/012F71C8-missing-refs.log` disassembles additional Ghidra extents from their recorded starts. These are retail instructions, not a decompiler draft. The additional containing bodies and instruction sites are:

- RVA `0x541480`, recorded extent 241 bytes: `0x00541507`.
- RVA `0x63E490`, recorded extent 1042 bytes: `0x0063E522`, `0x0063E535`, `0x0063E5BD`, `0x0063E60A`, `0x0063E619`, `0x0063E7C6`.

Local byte-hit candidates outside these extents are also preserved in that raw log. Their containing-body boundaries remain open and do not establish another datum identity. The original contract log retains the complete byte-hit inventory.

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F71C8-retail.log`, `012F71C8-routes.log`, `012F71C8-source.log` and `012F71C8-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
