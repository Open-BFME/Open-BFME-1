# Existing enum contracts, cohort117

One task replaces one private enum declaration with its already-existing BFME1
contract in a narrow shared header. The original owned provider headers/shims
are preserved, avoiding the unsupported broad context change from the previous
session. Source consistency is counted; new authored function bytes are not.

Before any edit, ordinary and Z7 controls compile the actual original source
filename into explicit private outputs. After adoption, the normal build must
pass and its entire runtime COFF inventory must match that actual control:
code,data,relocations,definitions,raw directives,weak externals and aliases.
An additional fresh actual-source ordinary probe must match the normal object.
Actual-source Z7 records preserve every original complete class and every other
enum, with the exact selected enum primitive type,size4 and active member values.
Both real-header include traces and opened-input hashes are retained.
Discovery wrappers alone are not accepted as actual-source/retail proof.

No native verifier, baseline, pin or alias is changed. A missing dependency
receipt would not become a current-provider proof through these source checks.
No full-image gain, crash/RAM/leak,64-bit,multicore,FPS or game-start claim.

The read-only BFME2 reference is147fd3e52b36ee0306aaeef5b316beb09f7c7671.
Its relevant subsystem views and source names are reviewed as donor leads;
existing BFME1 headers/shims and independently matched consumers establish the
actual contracts here. No donor address, compiler configuration or body is
imported. Extra unused enumerators retain native-source provenance; they are
not promoted to newly proven retail semantics.

|Task|Enum|Consumer|Rows|Retained bytes|Unused private differences|
|---|---|---|---:|---:|---|
|1546|MouseButtonState|`game/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse_translateEvent.cpp`|1|520|`{}`|
|1547|CpuType|`game/GameEngine/Source/Common/GameLODManagerInit.cpp`|1|1074|`{}`|
|1548|WorldAnimationOptions|`game/GameEngine/Source/GameLogic/Object/Object_rva001CEAD0_onVeterancyLevelChanged.cpp`|1|664|`{}`|
|1549|StaticGameLODLevel|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit_Bfme.cpp`|1|1824|`{"RvaLODMinusOne": -1}`|
|1550|ValueOrThreat|`game/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBD00.cpp`|1|1252|`{"VOT_CashValue": 0, "VOT_ThreatValue": 1}`|
|1551|CommandButtonMappedBorderType|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_setControlCommand_GameWindow.cpp`|1|603|`{}`|
|1552|ArmorSetType|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_onVeterancyLevelChanged.cpp`|1|520|`{}`|
|1553|StateReturnType|`game/GameEngine/Source/GameLogic/AI/TurretAIRecenterTurretState_update.cpp`|2|168|`{}`|
|1554|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerActionStateLifecycle.cpp`|2|104|`{}`|
|1555|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00173C70MoveAwayUpdates.cpp`|2|230|`{}`|
|1556|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardIdleStateOnEnter.cpp`|2|81|`{}`|
|1557|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveAndDeleteState_onEnter.cpp`|2|206|`{}`|
|1558|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowPathStateOnEnter.cpp`|2|390|`{}`|
|1559|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowWaypointPathState_update.cpp`|2|573|`{}`|
|1560|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate.cpp`|2|363|`{}`|
|1561|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIGuardIdleStateDestructor.cpp`|2|295|`{}`|
|1562|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeWaitState_update.cpp`|2|545|`{}`|
|1563|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIChargeTargetState_update.cpp`|2|577|`{}`|
|1564|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdSwoopState_update.cpp`|2|1267|`{}`|
|1565|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerPrimaryIdleState_update.cpp`|2|831|`{}`|
|1566|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathAppendNodeCopy.cpp`|2|233|`{}`|
|1567|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp`|2|322|`{}`|
|1568|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathNodeInsertion.cpp`|2|284|`{}`|
|1569|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderClearCellForDiameter.cpp`|2|834|`{}`|
|1570|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderDestinationWork.cpp`|2|334|`{}`|
|1571|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderNewMap.cpp`|2|760|`{}`|
|1572|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderBuildGroundPath.cpp`|2|733|`{}`|
|1573|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Locomotor_rva001B7200.cpp`|2|692|`{}`|
|1574|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003E49F0.cpp`|2|1446|`{}`|
|1575|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateComputeQuickPath.cpp`|2|577|`{}`|
|1576|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderStepD4F90.cpp`|2|1222|`{}`|
|1577|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetState_computePath_Bfme.cpp`|2|1149|`{}`|
|1578|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorCreateScaffoldingThunk.cpp`|2|2418|`{}`|
|1579|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/WeaponStore_allocateNewWeapon_Thunk.cpp`|2|111|`{"WEAPON_SLOT_PLACEHOLDER": 0}`|
|1580|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Collide/FireWeaponCollideCtorThunk.cpp`|2|155|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|ArmorSetType|`inputs/reference/shims/sweep/GameLogic/ArmorSet.h`|
|CommandButtonMappedBorderType|`inputs/reference/shims/sweep/GameClient/ControlBar.h`|
|CpuType|`inputs/reference/shims/gamelod/Common/GameLOD.h`|
|MouseButtonState|`inputs/reference/shims/mouselayout/GameClient/Mouse.h`|
|PathfindLayerEnum|`game/GameEngine/Source/Common/game_type.h`|
|StateReturnType|`inputs/reference/shims/sweep/Common/StateMachine.h`|
|StaticGameLODLevel|`inputs/reference/shims/gamelod/Common/GameLOD.h`|
|ValueOrThreat|`inputs/reference/shims/partitiondataoutofline/GameLogic/PartitionManager.h`|
|WeaponSlotType|`game/GameEngine/Source/Common/game_type.h`|
|WorldAnimationOptions|`inputs/reference/shims/mouselayout/GameClient/InGameUI.h`|
