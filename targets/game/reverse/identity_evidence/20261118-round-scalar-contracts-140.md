# Scalar alias contracts: cohort 140

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
|2720|`game/GameEngine/Source/GameLogic/AI/PathfinderCheckForPossible.cpp`|Int, Bool|1|181|
|2721|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicGetLayerHeight.cpp`|Real, Bool|1|267|
|2722|`game/GameEngine/Source/GameLogic/Object/Contain/Rva226800RemoveContain.cpp`|Bool, UnsignedInt|1|337|
|2723|`game/GameEngine/Source/GameLogic/Object/Rva00189E80ObjectVisionQuery.cpp`|Real, Bool|1|189|
|2724|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_rva001F1620.cpp`|Bool, UnsignedInt|1|449|
|2725|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorCtorThunk.cpp`|Real, Bool|1|661|
|2726|`game/GameEngine/Source/GameLogic/AI/AITNGuardIdleState_update_Bfme.cpp`|UnsignedInt, Real|1|274|
|2727|`game/GameEngine/Source/GameNetwork/Network_GetCommandsFromCommandList.cpp`|Int, UnsignedInt|1|352|
|2728|`game/GameEngine/Source/GameLogic/AI/Rva00168AE0TeamBuildCheck.cpp`|Bool, Int|1|486|
|2729|`game/GameEngine/Source/GameLogic/AI/PathfindObstacleCallbackDebb0.cpp`|Int, Bool|1|390|
|2730|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva005082D0.cpp`|Int, Bool|1|726|
|2731|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPlayerInfoCallback.cpp`|Int, UnsignedInt|1|295|
|2732|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doPlaySoundEffectAtTeam.cpp`|Int, Bool|1|242|
|2733|`game/GameEngine/Source/Common/RTS/ActionManagerCanPlayerGarrison.cpp`|Bool, Int|1|138|
|2734|`game/GameEngine/Source/GameLogic/Object/Object_bfmePrepare.cpp`|Bool, UnsignedInt|1|408|
|2735|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DWaypointBufferCtor.cpp`|Int, Char|1|297|
|2736|`game/GameEngine/Source/Common/System/SaveGame/GameStateXferSaveData.cpp`|UnsignedShort, Bool|1|559|
|2737|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DCameoMovieDraw_Thunk.cpp`|Int, Real|1|148|
|2738|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/doSingleBoneName.cpp`|Int, Bool|1|909|
|2739|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGuardNearestKindof.cpp`|Bool, Real, UnsignedInt|1|419|
|2740|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuPopulateMapSelectListbox.cpp`|Int, Bool|1|684|
|2741|`game/GameEngine/Source/GameClient/LanguageFilter_filterLine.cpp`|Int, Bool|1|410|
|2742|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/BfmeVolumetricShadowManagerAdd.cpp`|Bool, Real|1|305|
|2743|`game/GameEngine/Source/GameClient/ViewRva0045C2F0.cpp`|Int, Real|1|229|
|2744|`game/GameEngine/Source/GameLogic/AI/AIHordeExitState_rva0016FB20.cpp`|Int, Bool|1|218|
|2745|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva00576C20.cpp`|Int, Bool|1|775|
|2746|`game/GameEngine/Source/GameLogic/Object/Object_rva001CCB20_applyContainedCondition.cpp`|Bool, UnsignedInt|1|400|
|2747|`game/GameEngine/Source/GameLogic/AI/AITNGuardReturnState_onEnter_Bfme.cpp`|UnsignedInt, Real|1|123|
|2748|`game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchStartPressed.cpp`|Int, Bool|1|353|
|2749|`game/GameEngine/Source/GameLogic/System/Rva003A01E0AttributeXfer.cpp`|UnsignedByte, UnsignedInt|1|437|
|2750|`game/GameEngine/Source/GameLogic/Object/Object_rva001CCD20_transferContainedCondition.cpp`|Bool, UnsignedInt|1|528|
|2751|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/RoomKeyChangedCallback.cpp`|Int, UnsignedInt|1|323|
|2752|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsSkirmishPlayerHasComparisonCapturedUnits.cpp`|Bool, Int|1|360|
|2753|`game/GameEngine/Source/GameLogic/Map/TerrainLogic_setActiveBoundary_Thunk.cpp`|Real, Int|1|183|
|2754|`game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchAcceptPressed.cpp`|Int, Bool|1|554|
|2755|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualAddFactionBibDrawable.cpp`|Bool, Real|1|780|
|2756|`game/GameEngine/Source/GameClient/Input/Mouse_createStreamMessages.cpp`|Int, UnsignedInt|1|1140|
|2757|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/RestartMissionMenu.cpp`|Bool, Int|1|508|
|2758|`game/GameEngine/Source/Common/ExperienceLevelSystemRva0037F280.cpp`|Bool, Int|1|459|
|2759|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroudRenderBfme.cpp`|UnsignedByte, UnsignedShort|1|572|
|2760|`game/GameEngine/Source/GameLogic/Object/Update/RainOfFireUpdate.cpp`|Real, Bool|1|789|
|2761|`game/GameEngine/Source/Common/RTS/SpecialPowerStoreParseSpecialPowerDefinition.cpp`|UnsignedInt, Bool|1|639|
|2762|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamMoveToSkirmishApproachPath.cpp`|Bool, Int|1|461|
|2763|`game/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_uint_byte_insert.cpp`|Int, UnsignedInt, UnsignedByte|1|176|
|2764|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_aiDoCommand.cpp`|Bool, Int|1|397|
|2765|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarPopulateObserverInfoWindow.cpp`|Int, UnsignedInt, Bool|1|923|
|2766|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitReceiveUpgrade_Thunk.cpp`|Int, Bool, UnsignedInt|1|117|
|2767|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer_removeTreeAtIndex_Rva00733FD0.cpp`|Int, UnsignedInt, UnsignedByte|1|341|
|2768|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateHasUnits_Thunk.cpp`|Bool, Int|1|346|
|2769|`game/GameEngine/Source/Common/System/SaveGame/GameStateGetSaveGameInfoFromFileThunk.cpp`|Bool, UnsignedShort|1|554|
|2770|`game/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_ushort_int_insert.cpp`|Int, UnsignedShort|1|178|
|2771|`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/SalvageCrateCollide_executeCrateBehavior.cpp`|Bool, Int, UnsignedInt|1|263|
|2772|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_reset.cpp`|Int, Bool|1|496|
|2773|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainOnRemoving.cpp`|Int, Bool|1|525|
|2774|`game/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehaviorUpdate.cpp`|Int, Bool|1|570|
|2775|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_updateBodyParticleSystems_Thunk.cpp`|UnsignedInt, Int, Bool|1|828|
|2776|`game/GameEngine/Source/Common/BfmeT1035Use.cpp`|Bool, Real|1|557|
|2777|`game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineInit.cpp`|Int, Bool|1|703|
|2778|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainCreatePayload.cpp`|Bool, UnsignedInt|1|345|
|2779|`game/GameEngine/Source/Common/RTS/Team_killTeam.cpp`|Bool, UnsignedInt|1|636|
|2780|`game/GameEngine/Source/GameLogic/Map/Bridge.cpp`|Bool, Real|1|317|
|2781|`game/GameEngine/Source/Common/System/XferKindOf.cpp`|Bool, Int|1|250|
|2782|`game/GameEngine/Source/GameLogic/AI/AIAttackAreaState_update_Bfme.cpp`|Bool, UnsignedInt|1|229|
|2783|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsTeamAttackedByType.cpp`|Bool, Int|1|344|
|2784|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptScoreScreenPopulateMultiPlayer.cpp`|Bool, Int|1|708|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
