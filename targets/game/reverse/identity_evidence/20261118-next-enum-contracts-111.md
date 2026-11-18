# Existing enum contracts, cohort111

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
|1271|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp`|1|654|`{}`|
|1272|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_projectileFireAtObjectOrPosition.cpp`|1|846|`{}`|
|1273|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003E5E40.cpp`|1|460|`{"PATHFIND_LAYER_GROUND": 0}`|
|1274|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderFindSafePathBfme.cpp`|1|750|`{}`|
|1275|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003DF250.cpp`|1|648|`{"PATHFIND_LAYER_GROUND": 0}`|
|1276|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderAdjustToPossibleDestination.cpp`|1|1108|`{"LAYER_GROUND": 0}`|
|1277|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/LocomotorHandleBehaviorZ.cpp`|1|1615|`{}`|
|1278|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderAdjustDestination003F6090.cpp`|1|1142|`{}`|
|1279|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/AIStateTargetDispatch_attackOrdinaryTarget.cpp`|1|972|`{}`|
|1280|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_update.cpp`|1|1733|`{}`|
|1281|PathfindLayerEnum|`game/GameEngine/Source/GameLogic/AI/PathfinderInternalFindPath.cpp`|1|2347|`{}`|
|1282|WeaponSlotType|`game/GameEngine/Source/Common/Bfme5FourSlotPredicate.cpp`|1|94|`{}`|
|1283|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/Rva0016C990AttackCheck.cpp`|1|86|`{}`|
|1284|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/WeaponStore_createAndFireTempWeaponConstTarget.cpp`|1|96|`{}`|
|1285|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/Rva0016AF70Predicate.cpp`|1|125|`{}`|
|1286|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/AIGroup_setWeaponLockForGroup.cpp`|1|163|`{}`|
|1287|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/AttackNugget_ctor_Thunk.cpp`|1|90|`{}`|
|1288|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/AssistedTargetingObjectShim_find.cpp`|1|47|`{}`|
|1289|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/WeaponConstructor.cpp`|1|158|`{"WEAPON_SLOT_PLACEHOLDER": 0}`|
|1290|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/AIAttackState_loadPostProcess.cpp`|1|154|`{"WEAPON_SLOT_TYPE_UNSPECIFIED": 0}`|
|1291|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_getCanAnySlavesUseWeaponAgainstTarget.cpp`|1|206|`{"WEAPON_SLOT_DUMMY": 0}`|
|1292|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/AIAttackFireWeaponState_onExit.cpp`|1|161|`{}`|
|1293|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Update/FireWeaponUpdateCtorThunk.cpp`|1|168|`{}`|
|1294|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_killSpecialObjects.cpp`|1|262|`{}`|
|1295|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Update/WeaponFireSpecialAbilityUpdateCtorThunk.cpp`|1|212|`{}`|
|1296|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_doGuardLogic.cpp`|1|204|`{"WEAPON_SLOT_CURRENT": 0}`|
|1297|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior.cpp`|1|244|`{}`|
|1298|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeSquishState_computePath.cpp`|1|475|`{}`|
|1299|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/WeaponSet_updateWeaponSet.cpp`|1|379|`{}`|
|1300|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Update/DemoTrapUpdate.cpp`|1|380|`{"WEAPON_SLOT_UNKNOWN": 0}`|
|1301|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/Rva0016AEE0WeaponRangePosition.cpp`|1|109|`{}`|
|1302|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00237E50MemberRange.cpp`|1|281|`{"Rva00237E50WeaponSlotUnknown": 0}`|
|1303|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva002435F0Formation.cpp`|1|737|`{"Rva002435F0WeaponSlotUnknown": 0}`|
|1304|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehaviorUpdate.cpp`|1|570|`{}`|
|1305|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/Rva0015F420GuardRetaliateAttackEnter.cpp`|1|527|`{}`|
|1306|WeaponSlotType|`game/GameEngine/Source/GameClient/InGameUI_canSelectedObjectsEffectivelyUseWeapon_Thunk.cpp`|1|269|`{}`|
|1307|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateAttackPosition.cpp`|1|562|`{}`|
|1308|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/AIAttackState_onEnter.cpp`|1|970|`{}`|
|1309|WeaponSlotType|`game/GameEngine/Source/GameClient/MessageStream/CommandTranslator_issueFireWeaponCommand.cpp`|1|685|`{}`|
|1310|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_addValidObjectsToGarrisonPoints.cpp`|1|489|`{"FORCE_WEAPONSLOTTYPE_TO_LONG_SIZE": 134217727}`|
|1311|WeaponSlotType|`game/GameEngine/Source/GameClient/InGameUI_setRadiusCursor_Thunk.cpp`|1|531|`{}`|
|1312|WeaponSlotType|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00775470ProjectileLaunchOffset.cpp`|1|599|`{}`|
|1313|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/Collide/SquishCollide.cpp`|1|1138|`{}`|
|1314|WeaponSlotType|`game/GameEngine/Source/GameLogic/Object/WeaponSet_getAbleToUseWeaponAgainstTarget.cpp`|1|1065|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|PathfindLayerEnum|`game/GameEngine/Source/Common/game_type.h`|
|WeaponSlotType|`game/GameEngine/Source/Common/game_type.h`|
