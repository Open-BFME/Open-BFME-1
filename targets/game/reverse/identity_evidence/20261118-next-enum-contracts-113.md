# Existing enum contracts, cohort113

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
|1364|ScienceType|`game/GameEngine/Source/GameLogic/System/ArmySummaryPlayerArmySync.cpp`|1|498|`{"Rva003C2720ScienceTypeValue": 0}`|
|1365|ScienceType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineNewMap.cpp`|1|1059|`{"Rva00342E40ScienceType": 0}`|
|1366|ScienceType|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_populateSpecialPowerShortcut.cpp`|1|624|`{}`|
|1367|DeathType|`game/GameEngine/Source/Common/Rva001EFA50Kill.cpp`|1|15|`{}`|
|1368|DeathType|`game/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehaviorCtorModuleFactory.cpp`|1|164|`{}`|
|1369|DeathType|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/MonsterDockUpdateOnExitReached.cpp`|1|174|`{}`|
|1370|DeathType|`game/GameEngine/Source/GameLogic/Object/Damage/ReflectDamage_onDamage.cpp`|1|148|`{}`|
|1371|DeathType|`game/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContainUpdate.cpp`|1|54|`{}`|
|1372|DeathType|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdateAction.cpp`|1|224|`{}`|
|1373|DeathType|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContainKillBlockedRiders.cpp`|1|80|`{}`|
|1374|DeathType|`game/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate_update.cpp`|1|115|`{"DEATH_LIFETIME": 0}`|
|1375|DeathType|`game/GameEngine/Source/GameLogic/Object/Upgrade/ObjectCreationUpgradeRemoveUpgrade.cpp`|1|224|`{"BFME_DEATH_TYPE_0": 0}`|
|1376|DeathType|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorOnDie.cpp`|1|298|`{}`|
|1377|DeathType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_KillHordeMembers.cpp`|1|301|`{}`|
|1378|DeathType|`game/GameEngine/Source/GameLogic/Object/WeaponSpawnAndFadeNuggetRva002DE9B0.cpp`|1|325|`{}`|
|1379|DeathType|`game/GameEngine/Source/GameLogic/Object/ObjectAttemptHealingFromSoleBenefactor.cpp`|1|342|`{}`|
|1380|DeathType|`game/GameEngine/Source/GameLogic/Object/Update/FlammableUpdateOnDamage.cpp`|1|346|`{}`|
|1381|DeathType|`game/GameEngine/Source/Common/RTS/Team_killTeam.cpp`|1|636|`{}`|
|1382|DeathType|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate_setDockCrippledMethodThunk.cpp`|1|142|`{}`|
|1383|DeathType|`game/GameEngine/Source/GameLogic/Object/Behavior/RunOffMapBehaviorRva00205440.cpp`|1|354|`{}`|
|1384|DeathType|`game/GameEngine/Source/Common/Rva21ABF0WorkerVisit.cpp`|1|484|`{}`|
|1385|DeathType|`game/GameEngine/Source/GameLogic/Object/Update/ToppleUpdateApplyTopplingForce.cpp`|1|832|`{}`|
|1386|SlotState|`game/GameEngine/Source/GameNetwork/GameSlotIsPlayerUnicodeThunk.cpp`|1|58|`{}`|
|1387|SlotState|`game/GameEngine/Source/GameNetwork/GameInfo_allSameTeam.cpp`|1|174|`{}`|
|1388|SlotState|`game/GameEngine/Source/GameNetwork/GameInfo_IsSlotLocalAlly_Rva000A3170.cpp`|1|61|`{}`|
|1389|SlotState|`game/GameEngine/Source/GameNetwork/GameSlotIsPlayerAsciiThunk.cpp`|1|133|`{}`|
|1390|SlotState|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva00525080PlayerState.cpp`|1|318|`{}`|
|1391|SlotState|`game/GameEngine/Source/GameNetwork/LANGameSlot_getUser_Thunk.cpp`|1|145|`{}`|
|1392|SlotState|`game/GameEngine/Source/GameClient/GUI/SkirmishScreenStateHandlePlayerSelection.cpp`|1|391|`{}`|
|1393|SlotState|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoHost.cpp`|1|390|`{}`|
|1394|SlotState|`game/GameEngine/Source/GameClient/GUI/SkirmishScreenStateFlush15.cpp`|1|583|`{}`|
|1395|SlotState|`game/GameEngine/Source/GameNetwork/GameInfoAdjustSlotsForMap.cpp`|1|1308|`{}`|
|1396|SlotState|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchApplySlotState.cpp`|1|507|`{}`|
|1397|SlotState|`game/GameEngine/Source/Common/BfmeUpdateSkirmishBattleHonors.cpp`|1|1932|`{}`|
|1398|SlotState|`game/GameEngine/Source/GameNetwork/SinglePlayerSkirmishGameInfo_xfer.cpp`|1|901|`{}`|
|1399|SlotState|`game/GameEngine/Source/GameClient/GUI/BfmeAptScreenSkirmishRva0057BE50.cpp`|1|1000|`{}`|
|1400|SlotState|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/SkirmishScreenStateRefreshPlayerTypeCombo.cpp`|1|911|`{}`|
|1401|SlotState|`game/GameEngine/Source/GameNetwork/LANAPIHandleJoinAcceptRva0068CF00.cpp`|1|818|`{}`|
|1402|SlotState|`game/GameEngine/Source/GameNetwork/LANAPIRequestGameCreateThunk.cpp`|1|722|`{}`|
|1403|SlotState|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu_StartPressed.cpp`|1|2229|`{}`|
|1404|GeometryType|`game/GameEngine/Source/Common/Rva00C6DBB0StaticAAOInit.cpp`|1|41|`{}`|
|1405|GeometryType|`game/GameEngine/Source/Common/Rva009F66F0.cpp`|1|253|`{}`|
|1406|GeometryType|`game/GameEngine/Source/Common/System/GeometryInfoDefaultConstructor.cpp`|1|111|`{}`|
|1407|GeometryType|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRemoveTreesForConstruction.cpp`|1|302|`{}`|
|1408|GeometryType|`game/GameEngine/Source/Common/System/GeometryInfoConstructor.cpp`|1|170|`{}`|
|1409|GeometryType|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferRemovePropsForConstruction.cpp`|1|300|`{}`|
|1410|GeometryType|`game/GameEngine/Source/Common/System/GeometryInfoRva0087E370.cpp`|1|734|`{}`|
|1411|GeometryType|`game/GameEngine/Source/Common/System/GeometryInfoRva0087E190.cpp`|1|469|`{}`|
|1412|GeometryType|`game/GameEngine/Source/Common/System/GeometryInfoRva0087E650.cpp`|1|636|`{}`|
|1413|GeometryType|`game/GameEngine/Source/Common/System/GeometryInfoSet.cpp`|1|273|`{}`|
|1414|GeometryType|`game/GameEngine/Source/GameLogic/Map/TerrainRecordRemoval001AE4D0.cpp`|1|252|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|DeathType|`inputs/reference/shims/sweep/GameLogic/Damage.h`|
|GeometryType|`game/GameEngine/Source/Common/System/geometry.h`|
|ScienceType|`inputs/reference/shims/science/Common/Science.h`|
|SlotState|`inputs/reference/shims/nat/GameNetwork/GameInfo.h`|
