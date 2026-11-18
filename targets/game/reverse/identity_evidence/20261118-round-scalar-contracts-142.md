# Scalar alias contracts: cohort 142

One task replaces one consumer file's grouped private primitive typedefs
with the existing EA/BFME1 contract. Individual typedefs are not counted as
separate tasks. Only exact primitive spellings already present in both the
native BFME1 Precompiled/PreRTS.h and the EA BaseType.h qualify. Char remains
char, unsigned types remain unsigned, and no 64-bit/platform modernization is
inferred. Original provider headers are preserved. The narrow shared header
contains only the nine original scalar typedefs, without macros or runtime code.

Actual original source filenames compile into explicit private ordinary and Z7
controls before any edit. After adoption the normal build passes. Its complete
ordinary runtime inventory equals the actual pre-edit object: code, data,
definitions, relocations, raw directives, weak references and aliases. A fresh
actual-source ordinary object also equals the normal build object. All original
complete class contracts and all original enums remain identical in actual
Z7 records. Real-header traces and opened-input hashes are retained.

Additional private functions bind pointers to each adopted alias and return its
sizeof. Complete witness symbol names and bodies must remain identical, proving
primitive type identity and size even for aliases that contribute no runtime
instructions. A negative control changes unused Int from int to unsigned int:
ordinary runtime remains identical, but the exact primitive witness rejects it.
Witness code exists only in explicit diagnostic outputs. It is not game source,
retail identity evidence or authored-byte progress. CPP files included by other
CPPs are excluded unless all parent/namespace contexts are independently proven.

This source consistency work adds no newly reconstructed function bytes and
makes no crash, RAM/leak, FPS, multicore or runtime-start claim. No verifier,
baseline, pin, EH label or alias is weakened or manually altered. Linking is
separate; absent dependency receipts remain UNKNOWN for provider freshness.

|Task|Consumer|Grouped aliases|Rows|Retained row bytes|
|---|---|---|---:|---:|
|2850|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlayRCMenuSystem.cpp`|Int, Bool|1|1023|
|2851|`game/GameEngine/Source/GameLogic/AI/AIStateTargetDispatch_attackOrdinaryTarget.cpp`|Bool, Real|1|972|
|2852|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLobbyMenuPopulateLobbyPlayerListbox.cpp`|Int, Bool|1|1404|
|2853|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap_initHeightData.cpp`|Int, UnsignedShort|1|1648|
|2854|`game/GameEngine/Source/GameClient/Drawable_drawContained.cpp`|Int, Real|1|833|
|2855|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualRva00730590Init.cpp`|Bool, Int|1|684|
|2856|`game/GameEngine/Source/GameClient/GUI/Gadget/GadgetPushButtonInput.cpp`|UnsignedInt, Bool|1|1444|
|2857|`game/GameEngine/Source/Common/System/BuildAssistant_moveObjectsForConstruction.cpp`|Bool, Real|1|1109|
|2858|`game/GameEngine/Source/GameLogic/AI/PathfinderInternalFindPath.cpp`|Bool, UnsignedShort|1|2347|
|2859|`game/GameEngine/Source/GameNetwork/NetPacket_FillBufferWithGameCommand.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool, Real|2|554|
|2860|`game/GameEngine/Source/GameNetwork/Transport_queueSend.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|226|
|2861|`game/GameEngine/Source/GameLogic/AI/PathfindCellInfoRecord.cpp`|Int, UnsignedInt, UnsignedShort, Real, Bool|2|169|
|2862|`game/GameEngine/Source/GameNetwork/NetPacket_addRouterFallbackCommand.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|565|
|2863|`game/GameEngine/Source/GameNetwork/NetPacket_addFrameCommand.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|587|
|2864|`game/GameEngine/Source/GameNetwork/Connection_processAck.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Real|2|257|
|2865|`game/GameEngine/Source/GameLogic/Object/Object_rva001CA6C0_lookMask.cpp`|Bool, Real, Int, UnsignedInt, UnsignedShort|2|606|
|2866|`game/GameEngine/Source/GameNetwork/LANAPIBfmeSlotHandlers.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|207|
|2867|`game/GameEngine/Source/GameNetwork/NetPacket_isRoomForFileAndChat.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|315|
|2868|`game/GameEngine/Source/Common/System/GameMessage_copyConstructor.cpp`|Int, Real, Bool, UnsignedInt, UnsignedByte|2|1328|
|2869|`game/GameEngine/Source/Common/RTS/Team_DoXfer.cpp`|Bool, Int, Real, UnsignedInt, UnsignedShort, UnsignedByte|2|896|
|2870|`game/GameEngine/Source/GameNetwork/LANAPIGames.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|656|
|2871|`game/GameEngine/Source/GameNetwork/LANAPIOnGameJoin.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|899|
|2872|`game/GameEngine/Source/Common/System/RadarXferObjectList.cpp`|UnsignedByte, UnsignedShort, UnsignedInt, Int, Bool|2|796|
|2873|`game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar_buildTerrainTexture.cpp`|Int, Real, Bool, UnsignedByte, UnsignedInt|2|1780|
|2874|`game/GameEngine/Source/GameClient/DrawableCaptionAndAmbient.cpp`|UnsignedByte, UnsignedInt, Int, Real, Bool|2|654|
|2875|`game/GameEngine/Source/Common/BfmeConv2087.cpp`|UnsignedInt, UnsignedShort, UnsignedByte, Real|2|80|
|2876|`game/GameEngine/Source/GameNetwork/BFMEDisconnectManagerSendDisconnectScreenOff.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte|2|182|
|2877|`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdate_bfmeGetBonus.cpp`|Bool, Int, UnsignedInt, Real|2|280|
|2878|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_startSlavedEffects.cpp`|UnsignedInt, Bool, Int, Real|2|214|
|2879|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromTopFast_updateAnimateWindow_Thunk.cpp`|UnsignedInt, Int, Real, Bool|2|267|
|2880|`game/GameEngine/Source/GameNetwork/NetPacketChatReaders.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte|2|523|
|2881|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineSetToppleDirection.cpp`|Int, UnsignedShort, Real, Bool|2|468|
|2882|`game/GameEngine/Source/GameLogic/Object/Behavior/Rva00206B40ClaimNearest.cpp`|Real, Int, UnsignedInt, Bool|2|451|
|2883|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromRight_updateAnimateWindow.cpp`|UnsignedInt, Int, Real, Bool|2|260|
|2884|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromTop_reverseAnimateWindow.cpp`|UnsignedInt, Int, Real, Bool|2|293|
|2885|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromBottom_updateAnimateWindow_Thunk.cpp`|UnsignedInt, Int, Real, Bool|2|268|
|2886|`game/GameEngine/Source/GameNetwork/LANGameSlot_copy.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|299|
|2887|`game/GameEngine/Source/GameLogic/AI/AIMoveAndDeleteState_onEnter.cpp`|Int, UnsignedInt, UnsignedByte, Real, Bool|2|206|
|2888|`game/GameEngine/Source/GameNetwork/NetCommandWrapperList_getReadyCommands.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|2|267|
|2889|`game/GameEngine/Source/GameClient/System/Anim2DDrawing.cpp`|Int, Real, UnsignedByte, UnsignedShort|2|334|
|2890|`game/GameEngine/Source/GameClient/EvaUpdate.cpp`|Bool, Int, UnsignedInt, Real|2|178|
|2891|`game/GameEngine/Source/GameClient/Terrain/TerrainRoadType_setFXString.cpp`|Int, UnsignedInt, Real, Bool|2|183|
|2892|`game/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateCtorThunk.cpp`|Int, UnsignedInt, Bool, Real|2|405|
|2893|`game/GameEngine/Source/Common/BfmeConv1982.cpp`|Bool, Real, Int, UnsignedInt|2|549|
|2894|`game/GameEngine/Source/GameLogic/Object/Behavior/DynamicPortalBehaviourRva001F96E0.cpp`|Int, UnsignedInt, Real, Bool|2|1001|
|2895|`game/GameEngine/Source/GameLogic/AI/AIGuardIdleStateDestructor.cpp`|Int, UnsignedInt, Bool, Real|2|295|
|2896|`game/GameEngine/Source/GameNetwork/NetPacket_fillGameSpyStatsAuthKey.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte|2|426|
|2897|`game/GameEngine/Source/Common/BfmeAltAAV.cpp`|Int, UnsignedInt, UnsignedShort, Bool|2|485|
|2898|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowReverseAnimate.cpp`|UnsignedInt, Int, Real, Bool|2|523|
|2899|`game/GameEngine/Source/GameClient/Input/KeyboardEventProcessing.cpp`|UnsignedByte, UnsignedShort, UnsignedInt, Bool|2|360|
|2900|`game/GameEngine/Source/GameLogic/AI/PathfinderClearCellForDiameter.cpp`|Int, Bool, UnsignedInt, UnsignedByte|2|834|
|2901|`game/GameEngine/Source/GameNetwork/NetPacket_fill.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte|2|473|
|2902|`game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_allowedToStealthAt002ACD90.cpp`|Bool, Real, Int, UnsignedInt|2|750|
|2903|`game/GameEngine/Source/GameLogic/Object/Locomotor_rva001B7200.cpp`|Bool, Real, Int, UnsignedInt|2|692|
|2904|`game/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior_doScan.cpp`|Bool, Int, Real, UnsignedInt|2|803|
|2905|`game/GameEngine/Source/GameLogic/AI/AIGroupGroupAttackObjectPrivate.cpp`|Real, Bool, Int, UnsignedInt|2|587|
|2906|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva0032A710.cpp`|Int, UnsignedInt, UnsignedShort, Bool|2|963|
|2907|`game/GameEngine/Source/GameClient/MessageStream/HotKeyTranslator_translateGameMessage_Thunk.cpp`|Int, Bool, UnsignedByte, UnsignedInt|2|991|
|2908|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateComputeQuickPath.cpp`|Int, UnsignedInt, Bool, Real|2|577|
|2909|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdSwoopState_update.cpp`|Bool, Int, UnsignedInt, Real|2|1267|
|2910|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGiveNearestTeamUpgrade002FE270.cpp`|Bool, Int, Real, UnsignedInt|2|692|
|2911|`game/GameEngine/Source/GameLogic/AI/PathfinderStepD4F90.cpp`|Int, UnsignedInt, UnsignedShort, Bool, Real|2|1222|
|2912|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate_update.cpp`|Int, UnsignedInt, Bool, Real|2|1264|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
