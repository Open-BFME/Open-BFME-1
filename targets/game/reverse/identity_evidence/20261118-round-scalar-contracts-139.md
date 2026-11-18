# Scalar alias contracts: cohort 139

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
|2656|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPlayerJoinedCallback.cpp`|Int, UnsignedInt|1|301|
|2657|`game/GameEngine/Source/GameLogic/System/Rva00397350GlobalRallyPointFeedback.cpp`|Int, Bool, Real|1|390|
|2658|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGuardForFramecount.cpp`|Bool, Int, Real|1|202|
|2659|`game/GameEngine/Source/Common/RTS/Player_newMap.cpp`|Int, Bool|1|352|
|2660|`game/GameEngine/Source/Common/RTS/Rva000C4740.cpp`|Bool, Int|1|105|
|2661|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlayRefreshIgnoreList.cpp`|Int, UnsignedByte|1|539|
|2662|`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogicSetMissionObjectiveVisible.cpp`|Bool, Int|1|402|
|2663|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadPlayerFlagsChangedCallback.cpp`|Int, UnsignedInt|1|295|
|2664|`game/GameEngine/Source/Common/RTS/Team_evacuateTeam.cpp`|Bool, UnsignedInt|1|326|
|2665|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0073B290ViewGetRegion.cpp`|Real, Int|1|550|
|2666|`game/GameEngine/Source/GameClient/GUI/BfmeGetInternetPlayerStatus.cpp`|Int, Bool|1|404|
|2667|`game/GameEngine/Source/GameLogic/AI/AIPlayerDoUpgradesAndSkills.cpp`|Int, Bool|1|740|
|2668|`game/GameEngine/Source/GameLogic/AI/AIPlayerRva00164750TeamUnitCost.cpp`|Bool, Int|1|476|
|2669|`game/GameEngine/Source/GameNetwork/GameSpy/CacheLocalPlayerStatsWithLocale.cpp`|Int, UnsignedInt, Bool|1|452|
|2670|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule_isReady_Thunk.cpp`|UnsignedInt, Int|1|123|
|2671|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00237070HordeContainRecentDamage.cpp`|Bool, UnsignedInt|1|269|
|2672|`game/GameEngine/Source/GameLogic/Object/Behavior/Rva00370730CastleMemberState.cpp`|Int, Bool|1|286|
|2673|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_bfmeQueryWD.cpp`|Bool, Int|1|268|
|2674|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/GlobalKeyChangedCallback.cpp`|Int, UnsignedInt|1|310|
|2675|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamSetHealth.cpp`|Bool, Real|1|227|
|2676|`game/GameEngine/Source/GameClient/System/ParticleSystemManagerUpdate.cpp`|Bool, Real|1|467|
|2677|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonAbilityAtWaypoint_Thunk.cpp`|Bool, Int|1|169|
|2678|`game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_doParticleSystemAtBone.cpp`|Bool, Int|1|323|
|2679|`game/GameEngine/Source/GameLogic/Object/ObjectUpdateUpgradeModulesBody.cpp`|Bool, UnsignedInt|1|349|
|2680|`game/GameEngine/Source/GameLogic/AI/AIGuardRetaliateReturnState_onEnter_Bfme.cpp`|UnsignedInt, Bool|1|215|
|2681|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ReplayMenuInit.cpp`|Int, Bool|1|808|
|2682|`game/GameEngine/Source/Common/Rva006187D0MoveArmyToPosition.cpp`|Bool, UnsignedInt|1|111|
|2683|`game/GameEngine/Source/GameClient/GUI/FontLibraryBFMERetail_bfmeBuildFont.cpp`|Int, Real|1|361|
|2684|`game/GameEngine/Source/GameLogic/AI/AITNGuardOuterState_onEnter.cpp`|UnsignedInt, Bool|1|224|
|2685|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadDisconnectedCallback.cpp`|Bool, Int|1|345|
|2686|`game/GameEngine/Source/GameClient/GUI/GameWindowManager_processDestroyList.cpp`|Int, UnsignedInt, Bool|1|131|
|2687|`game/GameEngine/Source/GameLogic/System/Rva00382460ExperienceLevelParser.cpp`|Bool, Int|1|399|
|2688|`game/GameEngine/Source/GameClient/GUI/Rva56E070StateSave.cpp`|Int, Bool|1|756|
|2689|`game/GameEngine/Source/GameLogic/AI/AIExitState_rva0016FC30.cpp`|Int, Bool|1|190|
|2690|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsGarrisonedUnits.cpp`|Bool, Int|1|420|
|2691|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DLeftHUDDraw_Thunk.cpp`|Int, Bool|1|271|
|2692|`game/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdateCtorThunk.cpp`|UnsignedInt, Bool|1|278|
|2693|`game/GameEngine/Source/GameNetwork/PopulatePlayerTemplateComboBox.cpp`|Bool, Int|1|764|
|2694|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/getRoomKeysCallback.cpp`|Int, UnsignedInt|1|395|
|2695|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamSetAutoAbility.cpp`|Bool, Int|1|330|
|2696|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva00736150.cpp`|Int, Real|1|860|
|2697|`game/GameEngine/Source/Common/System/BuildAssistant_isPossibleToMakeUnit.cpp`|Int, Bool|1|444|
|2698|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/insertPlayerInListbox_Thunk.cpp`|Int, Bool|1|333|
|2699|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsRva00303910.cpp`|Bool, Real|1|340|
|2700|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommandButton.cpp`|Bool, Int, UnsignedInt|1|140|
|2701|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_FireSpecialPowerHelper.cpp`|Bool, UnsignedShort|1|289|
|2702|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva0023D230RepresentativeMember.cpp`|Bool, UnsignedInt|1|409|
|2703|`game/GameEngine/Source/GameLogic/Object/Update/OneRingPenaltyUpdateRva00299080.cpp`|Bool, Int, Real|1|257|
|2704|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamMoveToNearestObjectOfKindof.cpp`|Bool, Real, UnsignedInt|1|443|
|2705|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptRva0035C0C0Parse.cpp`|Int, Bool|1|579|
|2706|`game/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateOnObjectCreated.cpp`|Bool, Int|1|380|
|2707|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_getMoodMatrixActionAdjustment.cpp`|Bool, UnsignedInt|1|408|
|2708|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUI_drawPlaceAngle.cpp`|Real, Int, Bool|1|475|
|2709|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarBeacon.cpp`|Bool, UnsignedInt|1|62|
|2710|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnUnitBehaviorUpdate.cpp`|UnsignedInt, Bool|1|361|
|2711|`game/GameEngine/Source/GameClient/GUI/Rva0059E320MainMenuMediumInit.cpp`|Int, Bool|1|293|
|2712|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainAddOrRemoveObjFromWorld.cpp`|Bool, UnsignedInt|1|200|
|2713|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva00736940.cpp`|Int, UnsignedInt|1|342|
|2714|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva007209F0.cpp`|Int, UnsignedInt|1|348|
|2715|`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdate_xfer.cpp`|Int, UnsignedInt|1|582|
|2716|`game/GameEngine/Source/Common/SkirmishBattleHonorsConstructor.cpp`|Bool, Int|1|534|
|2717|`game/GameEngineDevice/Source/W3DDevice/GameClient/MapObjectDestructor.cpp`|Int, Real|1|236|
|2718|`game/GameEngine/Source/GameLogic/AI/AIAttackMoveToState_update_Bfme.cpp`|Bool, UnsignedInt|1|603|
|2719|`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogicSetMissionObjectiveCompleted.cpp`|Bool, Int|1|525|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
