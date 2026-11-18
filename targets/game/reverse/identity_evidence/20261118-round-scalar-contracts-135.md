# Scalar alias contracts: cohort 135

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
|2473|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetStoppingDistance.cpp`|Bool, Real|1|135|
|2474|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicExtent.cpp`|Real, Int|1|98|
|2475|`game/GameEngine/Source/GameClient/Rva0040F160.cpp`|UnsignedInt, Real|1|202|
|2476|`game/GameEngine/Source/GameLogic/Object/Contain/SiegeEngineContainIsValidContainerFor.cpp`|Bool, Int|1|147|
|2477|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_doPush.cpp`|Bool, Int|1|163|
|2478|`game/GameEngine/Source/GameLogic/Object/Rva0018E210TurretAngleConditions.cpp`|Int, Bool|1|405|
|2479|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowPathStateOnExit.cpp`|Int, UnsignedInt|1|185|
|2480|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainMemberNameMatches.cpp`|Bool, Int|1|106|
|2481|`game/GameEngine/Source/GameLogic/AI/Rva0016F150.cpp`|Int, Bool|1|352|
|2482|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleDoSpecialPowerAtObject.cpp`|UnsignedInt, Int, Bool|1|83|
|2483|`game/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditionsHideEndGame.cpp`|Int, Bool|1|119|
|2484|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeContainSlotRecenter0023B9F0.cpp`|Int, UnsignedInt|1|321|
|2485|`game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarAlphaBlob6x6.cpp`|Int, UnsignedByte|1|748|
|2486|`game/GameEngine/Source/GameLogic/Map/TerrainLogicIsUnderwater.cpp`|Bool, Real|1|144|
|2487|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva004EB2A0NotificationOtherMode.cpp`|Int, Bool|1|348|
|2488|`game/GameEngine/Source/GameLogic/Object/Helper/Rva0026E380.cpp`|Int, UnsignedInt, Bool|1|173|
|2489|`game/GameEngine/Source/GameLogic/LivingWorld/ArmySummaryCollectionXfer.cpp`|Bool, UnsignedInt, Int|1|612|
|2490|`game/GameEngine/Source/Common/Rva0046F060DrawImageAt.cpp`|Int, Real|1|137|
|2491|`game/GameEngine/Source/GameLogic/Object/Update/Rva002A7DB0_check.cpp`|UnsignedInt, Bool|1|168|
|2492|`game/GameEngine/Source/Common/RTS/ActionManager_canResumeConstructionOf_Thunk.cpp`|Bool, Int|1|92|
|2493|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/KeyboardOptionsMenuPopulateCategoryBox.cpp`|Bool, Int|1|296|
|2494|`game/GameEngine/Source/GameLogic/Object/Object_rva001CC660.cpp`|Bool, UnsignedInt|1|238|
|2495|`game/GameEngine/Source/Common/RTS/TeamDeleteCallback.cpp`|Int, UnsignedInt|1|31|
|2496|`game/GameEngine/Source/GameLogic/Object/Contain/BfmeHordeContainApplyMemberFormationState.cpp`|Bool, UnsignedInt|1|156|
|2497|`game/GameEngine/Source/Common/Audio/AudioEventRTSAdjustForLocalization.cpp`|Int, Bool|1|272|
|2498|`game/GameEngine/Source/GameLogic/Map/BfmeHostBJXfer.cpp`|UnsignedByte, Bool|1|279|
|2499|`game/GameEngine/Source/GameLogic/Object/Update/Rva00256AE0StatusAttach.cpp`|Int, Bool|1|108|
|2500|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_setIndestructible.cpp`|Bool, Int|1|121|
|2501|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BCE00StateAction.cpp`|Real, Int|1|168|
|2502|`game/GameEngine/Source/GameLogic/Map/Bridge_isCellOnSide_Thunk.cpp`|Real, Bool|1|504|
|2503|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceCalculateMaxBlockedSpeed.cpp`|Real, Int|1|289|
|2504|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate_chooseLocomotorSet.cpp`|Bool, Real|1|123|
|2505|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva00747670SetDrawOrg.cpp`|Int, Bool|1|202|
|2506|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamDecreasePriorityThunk.cpp`|Bool, Int|1|196|
|2507|`game/GameEngine/Source/GameLogic/AI/AIIdleState_onEnter.cpp`|Bool, UnsignedShort|1|198|
|2508|`game/GameEngine/Source/GameLogic/AI/PathfinderGetLayerHeight.cpp`|Real, Bool|1|511|
|2509|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerPrimaryStateMachine_isBuildMostImportantTwin.cpp`|Bool, Int|1|76|
|2510|`game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_xfer.cpp`|UnsignedInt, Int|1|419|
|2511|`game/GameEngine/Source/GameLogic/ScriptEngine/BfmeShouldShowGameOverEvent.cpp`|Bool, Int|1|70|
|2512|`game/GameEngine/Source/Common/Rva0046F490DrawBoundsOverlay.cpp`|Real, Int|1|480|
|2513|`game/GameEngine/Source/GameClient/GUI/WindowManager_bfmeRva0046E170.cpp`|Int, Bool|1|371|
|2514|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainAddMemberSyncXP_rva00245b20.cpp`|Int, Bool|1|156|
|2515|`game/GameEngine/Source/Common/Rva0015A960FormationProcess.cpp`|Real, Int|1|278|
|2516|`game/GameEngine/Source/Common/RTS/Rva000EDDE0TeamMinSpeed.cpp`|Bool, Real|1|177|
|2517|`game/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleTerrainCollisionModuleUpdate.cpp`|Bool, Real|1|367|
|2518|`game/GameEngine/Source/GameLogic/Object/FiringTrackerBFMESpeedUp.cpp`|Bool, UnsignedInt|1|374|
|2519|`game/GameEngine/Source/GameClient/FXList_parseCullingInfo.cpp`|UnsignedInt, Real|1|324|
|2520|`game/GameEngine/Source/GameLogic/AI/PathfinderTintSlowObject.cpp`|UnsignedInt, Real|1|159|
|2521|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenuIsAgeOkay.cpp`|Bool, Int|1|593|
|2522|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doFindHomeBaseOfPlayer.cpp`|Bool, UnsignedShort|1|167|
|2523|`game/GameEngine/Source/GameLogic/Object/Upgrade/DelayedUpgradeImplementation.cpp`|Bool, UnsignedInt|1|151|
|2524|`game/GameEngine/Source/Common/Rva0015A600FormationOffsets.cpp`|Real, Int|1|308|
|2525|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamChangeObjectStatus.cpp`|Int, Bool|1|159|
|2526|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorIsPlayerAllowedToCapture.cpp`|Bool, Int|1|184|
|2527|`game/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgradePostUpgradeCheck.cpp`|Bool, UnsignedInt|1|157|
|2528|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/updateMPBattleHonors.cpp`|Int, UnsignedInt|1|427|
|2529|`game/GameEngine/Source/GameLogic/LargeGroupAudio/LargeGroupAudioKeyMapXfer.cpp`|UnsignedByte, Bool|1|165|
|2530|`game/GameEngine/Source/Common/Glo012F1024Type_selectEntry.cpp`|Int, Bool|1|131|
|2531|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate_aiDoCommand.cpp`|Bool, Int|1|261|
|2532|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIAttackSwoopThenIdleStateMachineRva002BC870.cpp`|Bool, Real|1|139|
|2533|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002C12E0GiantBirdLocomotorUpdate.cpp`|Int, UnsignedInt, Bool|1|322|
|2534|`game/GameEngine/Source/Common/LadderPreferences_write_Bfme.cpp`|Int, Bool|1|534|
|2535|`game/GameEngine/Source/GameClient/GUI/FadeScreenRegionToMapBlack.cpp`|Bool, Int|1|228|
|2536|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_projectileFire.cpp`|Int, Bool|1|236|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
