# Existing enum contracts, cohort110

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
|1208|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/AIPathfindGoalPosition.cpp`|1|114|`{}`|
|1209|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Map/TerrainLogic_addBridgeToLogic.cpp`|1|176|`{}`|
|1210|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderChooseBestLocomotor.cpp`|1|143|`{"LAYER_GROUND": 0}`|
|1211|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathUpdateLastNode.cpp`|1|109|`{}`|
|1212|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdAttackStateOnExit.cpp`|1|138|`{}`|
|1213|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderSnapPosition.cpp`|1|151|`{}`|
|1214|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate_chooseGoodLocomotorFromCurrentSet.cpp`|1|137|`{"LAYER_GROUND": 0}`|
|1215|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderSetDebugPath.cpp`|1|190|`{}`|
|1216|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfindSnapLineCellCallback.cpp`|1|189|`{}`|
|1217|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderCheckForTargetBfme.cpp`|1|170|`{}`|
|1218|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfindAdjustDeab0.cpp`|1|200|`{"PATHFIND_LAYER_GROUND": 0}`|
|1219|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Map/TerrainLogicGetHighestLayer.cpp`|1|165|`{}`|
|1220|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D7010.cpp`|1|449|`{}`|
|1221|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineMADStruct.cpp`|1|478|`{}`|
|1222|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfindCellCallbackDeda0.cpp`|1|104|`{}`|
|1223|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Map/TerrainLogicGetLayerForDestinationObject.cpp`|1|245|`{}`|
|1224|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/TightenPathStructCtor.cpp`|1|92|`{}`|
|1225|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003E4190.cpp`|1|328|`{"PATHFIND_LAYER_DUMMY": 0}`|
|1226|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/Rva0016F150.cpp`|1|352|`{}`|
|1227|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D7440.cpp`|1|433|`{}`|
|1228|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/Rva003EE9F0.cpp`|1|276|`{"PATHFIND_LAYER_GROUND": 0}`|
|1229|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderBfmeLayerForPosition.cpp`|1|330|`{}`|
|1230|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva003F5E20.cpp`|1|345|`{}`|
|1231|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderGetLayerHeight.cpp`|1|511|`{}`|
|1232|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderValidMovementPosition.cpp`|1|226|`{"PATHFIND_LAYER_GROUND": 0}`|
|1233|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/GroundCellsStructCellCallback.cpp`|1|284|`{}`|
|1234|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/AIStateTargetDispatch_attackOptimizedTarget.cpp`|1|194|`{}`|
|1235|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D7680.cpp`|1|666|`{}`|
|1236|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D79C0.cpp`|1|566|`{}`|
|1237|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfindE1fe0.cpp`|1|270|`{}`|
|1238|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/pathfind_tightenPath.cpp`|1|143|`{}`|
|1239|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateBuildPath00271010.cpp`|1|553|`{}`|
|1240|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderObjectCell.cpp`|1|210|`{"PATHFIND_LAYER_DUMMY": 0}`|
|1241|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003E3650.cpp`|1|538|`{}`|
|1242|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003F1690.cpp`|1|337|`{"RVA003F1690_LAYER_INVALID": 0}`|
|1243|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/Rva001709E0.cpp`|1|388|`{}`|
|1244|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderCheckForPossible.cpp`|1|181|`{"PATHFIND_LAYER_GROUND": 0}`|
|1245|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Contain/Rva226800RemoveContain.cpp`|1|337|`{"PATHFIND_LAYER_GROUND": 0}`|
|1246|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_rva001F1620.cpp`|1|449|`{}`|
|1247|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Behavior/ClearanceTestingSlowDeathBehavior.cpp`|1|675|`{}`|
|1248|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderRemoveGoal003E3D20.cpp`|1|466|`{}`|
|1249|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/RainOfFireUpdate.cpp`|1|789|`{}`|
|1250|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/AIGroup_computeIndividualDestination.cpp`|1|428|`{}`|
|1251|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateWaypointPath.cpp`|1|398|`{}`|
|1252|PathfindLayerEnum|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapIsClearLineOfSight.cpp`|1|1082|`{}`|
|1253|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Map/Bridge.cpp`|1|317|`{}`|
|1254|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/pathfinder_path.cpp`|1|946|`{}`|
|1255|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva003E7B90.cpp`|1|453|`{"PATHFIND_LAYER_GROUND": 1}`|
|1256|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/Rva001752A0.cpp`|1|943|`{}`|
|1257|PathfindLayerEnum|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUI_drawMoveHints.cpp`|1|650|`{}`|
|1258|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva003F5C70.cpp`|1|335|`{}`|
|1259|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/Rva003F82C0Pathfinder.cpp`|1|1044|`{}`|
|1260|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdate_exitObjectViaDoor.cpp`|1|534|`{"LAYER_GROUND": 0}`|
|1261|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderBfmeCheckAttackViewAltHelper.cpp`|1|678|`{}`|
|1262|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfindPrependCells.cpp`|1|987|`{}`|
|1263|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/BfmeAttackQueryCanAttackTarget.cpp`|1|771|`{}`|
|1264|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Rva001E7C30WeaponTemplateComputeScatter.cpp`|1|592|`{}`|
|1265|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_computePath_Bfme.cpp`|1|384|`{}`|
|1266|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainExitObjectInAHurry.cpp`|1|1040|`{}`|
|1267|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderIsAttackViewBlockedByObstacle.cpp`|1|501|`{}`|
|1268|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainExitObjectViaDoor.cpp`|1|1039|`{}`|
|1269|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva00270DF0RebuildPath.cpp`|1|424|`{}`|
|1270|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/AIPathfind_classifyCells.cpp`|1|1405|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|PathfindLayerEnum|`game/GameEngine/Source/Common/game_type.h`|
