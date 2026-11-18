# Existing enum contracts, cohort109

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
|1147|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardReturnState_update.cpp`|1|275|`{}`|
|1148|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardInnerState_update.cpp`|1|175|`{}`|
|1149|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardIdleState.cpp`|1|290|`{}`|
|1150|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardAttackAggressorState_onEnter.cpp`|1|354|`{}`|
|1151|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMoveToState_update_Bfme.cpp`|1|603|`{}`|
|1152|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerActionMoveToActionPosState_update.cpp`|1|310|`{}`|
|1153|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIChargeTargetState_onEnter.cpp`|1|342|`{}`|
|1154|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardIdleState_update_Bfme.cpp`|1|274|`{}`|
|1155|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIGuardAttackAggressorState_onEnter_Bfme.cpp`|1|284|`{}`|
|1156|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIHordeExitState_rva0016FB20.cpp`|1|218|`{}`|
|1157|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardReturnState_onEnter_Bfme.cpp`|1|123|`{}`|
|1158|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva001745B0AICowerState_onExit.cpp`|1|153|`{}`|
|1159|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIPanicState_onEnter_Thunk.cpp`|1|353|`{}`|
|1160|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardAttackAggressorState_onEnter.cpp`|1|279|`{}`|
|1161|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIGuardInnerStateUpdate.cpp`|1|293|`{}`|
|1162|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_update.cpp`|1|579|`{}`|
|1163|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_onEnter.cpp`|1|357|`{}`|
|1164|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIDeadState_onEnter.cpp`|1|214|`{}`|
|1165|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIGuardOuterState_onEnter_Bfme.cpp`|1|476|`{}`|
|1166|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveToState_onEnter_Thunk.cpp`|1|322|`{}`|
|1167|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIIdleState_update.cpp`|1|404|`{}`|
|1168|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeEngageState_onEnter.cpp`|1|641|`{}`|
|1169|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackAreaState_update_Bfme.cpp`|1|229|`{}`|
|1170|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardInnerState_onEnter.cpp`|1|411|`{}`|
|1171|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIPanicState_update_Thunk.cpp`|1|399|`{}`|
|1172|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerActionPickActionPosStateUpdate.cpp`|1|372|`{}`|
|1173|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00173B90State_onEnter.cpp`|1|178|`{}`|
|1174|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeApproachState_onEnter.cpp`|1|747|`{}`|
|1175|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackFollowWaypointPathState_update_Bfme.cpp`|1|342|`{}`|
|1176|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00174A20State_update.cpp`|1|536|`{}`|
|1177|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIHarvestWorkSiteState_update.cpp`|1|308|`{}`|
|1178|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIWanderState_update_Bfme.cpp`|1|428|`{}`|
|1179|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMeleeReAcquireState_update.cpp`|1|553|`{}`|
|1180|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveAwayFromRepulsorsState_onEnter_Thunk.cpp`|1|197|`{}`|
|1181|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIGuardInnerState_onEnter_Bfme.cpp`|1|439|`{}`|
|1182|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_updateInternal.cpp`|1|522|`{}`|
|1183|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetState_stateReturn_Bfme.cpp`|1|897|`{}`|
|1184|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveToState_update_Bfme.cpp`|1|522|`{}`|
|1185|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00174800State_onEnter.cpp`|1|328|`{}`|
|1186|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackFireWeaponState_onEnter.cpp`|1|586|`{}`|
|1187|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateIdle.cpp`|1|296|`{}`|
|1188|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeEngageState_updateInternal.cpp`|1|1314|`{}`|
|1189|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIFollowWaypointPathState_onEnter.cpp`|1|622|`{}`|
|1190|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdSwoopStateOnEnter.cpp`|1|1057|`{}`|
|1191|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetState_onEnter_Bfme.cpp`|1|523|`{}`|
|1192|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackFireWeaponStateUpdateThunk.cpp`|1|979|`{}`|
|1193|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetState_updateInternal.cpp`|1|1398|`{}`|
|1194|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIFollowPathAsTeamState_update.cpp`|1|1517|`{}`|
|1195|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateUpdate00172E70.cpp`|1|1166|`{}`|
|1196|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIInternalMoveToState_onEnter.cpp`|1|1524|`{}`|
|1197|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerActionDoActionState_update.cpp`|1|1936|`{}`|
|1198|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateAiDoCommand.cpp`|1|330|`{}`|
|1199|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathAppendNodeILT.cpp`|1|5|`{}`|
|1200|PathfindLayerEnum|`game/GameEngine/Source/Common/BfmeConv1974.cpp`|1|104|`{}`|
|1201|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderGroundCellPredicate.cpp`|1|96|`{}`|
|1202|PathfindLayerEnum|`game/GameEngine/Source/Common/Rva003EEB50_checkForTargetFwd.cpp`|1|50|`{}`|
|1203|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderGetCellTwin.cpp`|1|65|`{}`|
|1204|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderAdjustLOSPoints.cpp`|1|100|`{}`|
|1205|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfindLayerDestructor.cpp`|1|64|`{}`|
|1206|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfindLayerResetFull.cpp`|1|64|`{}`|
|1207|PathfindLayerEnum|`game/GameEngine/Source/Common/Rva003D6690_layerHeight.cpp`|1|116|`{"LAYER_GROUND": 0}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|PathfindLayerEnum|`game/GameEngine/Source/Common/game_type.h`|
|StateReturnType|`inputs/reference/shims/sweep/Common/StateMachine.h`|
