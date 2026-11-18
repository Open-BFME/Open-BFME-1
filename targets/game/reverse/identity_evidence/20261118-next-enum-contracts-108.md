# Existing enum contracts, cohort108

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
|1082|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowWaypointPathStateOnEnter.cpp`|1|78|`{}`|
|1083|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIQuarrelState_update.cpp`|1|36|`{}`|
|1084|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva0016CF40State_onEnter.cpp`|1|118|`{}`|
|1085|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00178AE0State_onEnter.cpp`|1|66|`{}`|
|1086|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeWaitPathState_onEnter.cpp`|1|91|`{}`|
|1087|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00173B20State_update.cpp`|1|90|`{}`|
|1088|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00170120State_update.cpp`|1|101|`{}`|
|1089|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva0017C8A0ChooseWeapon.cpp`|1|80|`{}`|
|1090|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIBackAwayAndCowerState_onEnter.cpp`|1|178|`{}`|
|1091|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00173990State_onEnter.cpp`|1|101|`{}`|
|1092|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00173900AIMoveToStateSA_update.cpp`|1|111|`{}`|
|1093|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00174520AICowerState_onEnter.cpp`|1|113|`{}`|
|1094|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowPathState_update.cpp`|1|261|`{}`|
|1095|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveAndTightenState_onEnter_Thunk.cpp`|1|7|`{}`|
|1096|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveOntoWallState_onEnter.cpp`|1|155|`{}`|
|1097|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_update.cpp`|1|96|`{}`|
|1098|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetState_update_Bfme.cpp`|1|161|`{}`|
|1099|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMoveToState_onEnter.cpp`|1|109|`{}`|
|1100|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva001703C0AIStateMachine_update.cpp`|1|118|`{}`|
|1101|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00174730State_update.cpp`|1|159|`{}`|
|1102|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIWaitUntilFinishedFiringState_onEnter.cpp`|1|134|`{}`|
|1103|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIFaceState_update_Bfme.cpp`|1|198|`{}`|
|1104|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveToPositionAndEnterState_onEnter.cpp`|1|146|`{}`|
|1105|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva000A19E0StateBase_onEnter.cpp`|1|148|`{}`|
|1106|StateReturnType|`game/GameEngine/Source/GameLogic/AI/TurretAI_updateTurretAI.cpp`|1|261|`{}`|
|1107|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva0017DA80.cpp`|1|98|`{}`|
|1108|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardReturnState_update_Bfme.cpp`|1|96|`{}`|
|1109|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIIdleState_onEnter.cpp`|1|198|`{}`|
|1110|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AICowerState_update.cpp`|1|334|`{}`|
|1111|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIEnterState_onEnter_Bfme.cpp`|1|246|`{}`|
|1112|StateReturnType|`game/GameEngine/Source/Common/StateMachine_updateStateMachineTwin.cpp`|1|124|`{}`|
|1113|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveToPositionAndDieState_onEnter.cpp`|1|134|`{}`|
|1114|StateReturnType|`game/GameEngine/Source/Common/StateMachine_internalSetState.cpp`|1|200|`{}`|
|1115|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardAttackAggressorState_update_Bfme.cpp`|1|85|`{}`|
|1116|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeWaitPathState_update.cpp`|1|358|`{}`|
|1117|StateReturnType|`game/GameEngine/Source/GameLogic/AI/TurretAI_setTurretTargetPosition.cpp`|1|241|`{}`|
|1118|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveToStateSA_onEnter_rva001737C0.cpp`|1|237|`{}`|
|1119|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIRampageState_onEnter_Bfme.cpp`|1|285|`{}`|
|1120|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardOuterState_update_Bfme.cpp`|1|114|`{}`|
|1121|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerActionDoActionStateOnEnterBfme.cpp`|1|71|`{}`|
|1122|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIWanderInPlaceState_onEnter.cpp`|1|301|`{}`|
|1123|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIGuardRetaliateReturnState_update.cpp`|1|226|`{}`|
|1124|StateReturnType|`game/GameEngine/Source/GameLogic/AI/WanderWaypointEntry0017AEC0.cpp`|1|323|`{}`|
|1125|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva0017DB30State_onEnter.cpp`|1|275|`{}`|
|1126|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardReturnState_onEnter.cpp`|1|230|`{}`|
|1127|StateReturnType|`game/GameEngine/Source/GameLogic/AI/WaypointPathEntry0017AC30.cpp`|1|319|`{}`|
|1128|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardInnerState_update_Bfme.cpp`|1|258|`{}`|
|1129|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIGuardOuterState_update_Bfme.cpp`|1|360|`{}`|
|1130|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/BfmeGiantBirdFollowThruStateOnEnter.cpp`|1|492|`{}`|
|1131|StateReturnType|`game/GameEngine/Source/GameLogic/AI/RangeCheckedMove00176580.cpp`|1|293|`{}`|
|1132|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardInnerState_onEnter.cpp`|1|197|`{}`|
|1133|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIWanderInPlaceState_update.cpp`|1|339|`{}`|
|1134|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva001775A0.cpp`|1|299|`{}`|
|1135|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AICombineStateInternalUpdate.cpp`|1|238|`{}`|
|1136|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIMoveToPositionAndDieState_update_Bfme.cpp`|1|210|`{}`|
|1137|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdAttackState_update.cpp`|1|199|`{}`|
|1138|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00174670State_onEnter.cpp`|1|88|`{}`|
|1139|StateReturnType|`game/GameEngine/Source/GameLogic/AI/Rva00178C30StateOnEnter.cpp`|1|246|`{}`|
|1140|StateReturnType|`game/GameEngine/Source/GameLogic/AI/FollowPathEntry00178EA0.cpp`|1|463|`{}`|
|1141|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIGuardRetaliateReturnState_onEnter_Bfme.cpp`|1|215|`{"STATE_RETURN_DEFAULT": 0}`|
|1142|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AITNGuardOuterState_onEnter.cpp`|1|224|`{}`|
|1143|StateReturnType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdFollowThruStateUpdate.cpp`|1|347|`{}`|
|1144|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIExitState_rva0016FC30.cpp`|1|190|`{}`|
|1145|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIFearState_update.cpp`|1|402|`{}`|
|1146|StateReturnType|`game/GameEngine/Source/GameLogic/AI/AIHarvestPrepareSiteState_update.cpp`|1|272|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|StateReturnType|`inputs/reference/shims/sweep/Common/StateMachine.h`|
