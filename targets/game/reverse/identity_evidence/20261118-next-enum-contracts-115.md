# Existing enum contracts, cohort115

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
|1460|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerMouseEvent.cpp`|1|1569|`{}`|
|1461|DamageType|`game/GameEngine/Source/Common/DamageFX_doDamageFX.cpp`|1|95|`{"DAMAGE_TYPE_ZERO": 0}`|
|1462|DamageType|`game/GameEngine/Source/GameLogic/Object/Update/Rva001FEB50Destructor.cpp`|1|178|`{}`|
|1463|DamageType|`game/GameEngine/Source/GameLogic/Object/Body/Rva0020F240DoDamageFX.cpp`|1|185|`{}`|
|1464|LocomotorSetType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate_chooseLocomotorSet.cpp`|1|123|`{}`|
|1465|LocomotorSetType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateModuleDataParseLocomotorSet.cpp`|1|412|`{}`|
|1466|LocomotorSetType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate_chooseLocomotorSetExplicit.cpp`|1|144|`{}`|
|1467|LocomotorSetType|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_endRepair.cpp`|1|76|`{}`|
|1468|LocomotorSetType|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_moveToNewRepairSpot.cpp`|1|267|`{}`|
|1469|LocomotorSetType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceCtorThunk.cpp`|1|1237|`{}`|
|1470|QMStatus|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerHandleQMMatch.cpp`|1|653|`{}`|
|1471|QMStatus|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerRoomMessageCallback.cpp`|1|825|`{}`|
|1472|QMStatus|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerPlayerMessageCallback.cpp`|1|1075|`{}`|
|1473|QMStatus|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PlayerLeftCallback.cpp`|1|559|`{}`|
|1474|ObjectStatusTypes|`game/GameEngine/Source/GameLogic/Object/ObjectClearStatusType.cpp`|1|71|`{"OBJECT_STATUS_DESTROYED": 0}`|
|1475|ObjectStatusTypes|`game/GameEngine/Source/Common/Gen00371090Remove.cpp`|1|107|`{"OBJECT_STATUS_UNUSED": 0}`|
|1476|ObjectStatusTypes|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorRva00371EE0StatusBit.cpp`|1|342|`{"OBJECT_STATUS_DESTROYED": 0}`|
|1477|ExitDoorType|`game/GameEngine/Source/GameLogic/Object/Contain/HordeGarrisonContainExitObjectViaDoor.cpp`|1|248|`{}`|
|1478|ObjectStatusTypes|`game/GameEngine/Source/GameLogic/Object/Object_rva001CBC20DefectionComplete.cpp`|1|257|`{"OBJECT_STATUS_LAST": 85}`|
|1479|ObjectStatusTypes|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00266EB0SiegeDeployBaseTransition.cpp`|1|684|`{"OBJECT_STATUS_PLACEHOLDER": 0}`|
|1480|ExitDoorType|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdateExitObjectViaDoor.cpp`|1|565|`{}`|
|1481|ObjectStatusTypes|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_setCorrectDamageState.cpp`|1|1574|`{"OBJECT_STATUS_4": 4}`|
|1482|GameMessageArgumentDataType|`game/GameEngine/Source/GameNetwork/NetGameCommandMsgFromGameMessage.cpp`|1|191|`{}`|
|1483|GameMessageArgumentDataType|`game/GameEngine/Source/GameNetwork/GameMessageParserCtorThunk.cpp`|1|142|`{}`|
|1484|SnapshotType|`game/GameEngine/Source/Common/System/SaveGame/GameStateAutoSave.cpp`|1|155|`{}`|
|1485|SnapshotType|`game/GameEngine/Source/Common/System/SaveGame/GameStateFindBlockInfoByToken.cpp`|1|271|`{}`|
|1486|SnapshotType|`game/GameEngine/Source/Common/System/SaveGame/GameState_missionSave_Thunk.cpp`|1|311|`{}`|
|1487|SnapshotType|`game/GameEngine/Source/GameClient/GUI/Rva56E070StateSave.cpp`|1|756|`{}`|
|1488|SnapshotType|`game/GameEngine/Source/Common/System/SaveGame/GameStateXferSaveData.cpp`|1|559|`{}`|
|1489|SnapshotType|`game/GameEngine/Source/Common/System/SaveGame/GameStateInit.cpp`|1|1368|`{}`|
|1490|SnapshotType|`game/GameEngine/Source/Common/System/SaveGame/GameStateGetSaveGameInfoFromFileThunk.cpp`|1|554|`{}`|
|1491|GameMessageArgumentDataType|`game/GameEngine/Source/GameNetwork/NetGameCommandMsg_constructGameMessage.cpp`|1|467|`{}`|
|1492|DisabledType|`game/GameEngine/Source/GameLogic/Object/MoneyObjectThunks.cpp`|1|5|`{"DisabledTypePlaceholder": 0}`|
|1493|DisabledType|`game/GameEngine/Source/GameLogic/Object/ObjectCheckDisabledStatus.cpp`|1|102|`{"DISABLED_DEFAULT": 0, "DISABLED_EMP": 2, "DISABLED_FREEFALL": 7, "DISABLED_HACKED": 1, "DISABLED_HELD": 3, "DISABLED_PARALYZED": 4, "DISABLED_SUBDUED": 8, "DISABLED_UNDERPOWERED": 6, "DISABLED_UNMANNED": 5}`|
|1494|SaveCode|`game/GameEngine/Source/Common/System/SaveGame/GameStateRva001127F0LoadByFilename.cpp`|1|254|`{}`|
|1495|DrawableStatus|`game/GameEngine/Source/Common/Thing/BFMEThingFactory_newDrawable.cpp`|1|38|`{}`|
|1496|SaveCode|`game/GameEngine/Source/GameClient/GUI/AptMainMenuStateStep.cpp`|1|484|`{}`|
|1497|DisabledType|`game/GameEngine/Source/GameLogic/Object/SpecialPower/WeaponChangeSpecialPowerModuleDoSpecialPower.cpp`|1|722|`{}`|
|1498|DisabledType|`game/GameEngine/Source/GameLogic/Object/Update/RespawnUpdateRva002A1F80.cpp`|1|489|`{"Disabled4": 4}`|
|1499|DisabledType|`game/GameEngine/Source/GameLogic/Object/ObjectSetDisabledUntil.cpp`|1|509|`{"DISABLED_PLACEHOLDER": 0}`|
|1500|DrawableStatus|`game/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdateChangeVisualDisguise.cpp`|1|390|`{}`|
|1501|DrawableStatus|`game/GameEngine/Source/GameLogic/Object/Update/StealthUpdateChangeVisualDisguise.cpp`|1|1085|`{}`|
|1502|DrawableStatus|`game/GameEngine/Source/GameClient/DrawableConstructor.cpp`|1|2484|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|DamageType|`inputs/reference/shims/sweep/GameLogic/Damage.h`|
|DisabledType|`inputs/reference/shims/bfmeobject/GameLogic/Object.h`|
|DrawableStatus|`inputs/reference/shims/swayclientupdate/GameClient/Drawable.h`|
|ExitDoorType|`game/GameEngine/Include/GameLogic/Module/UpdateModule.h`|
|GameMessageArgumentDataType|`inputs/reference/shims/sweep/Common/MessageStream.h`|
|LocomotorSetType|`inputs/reference/shims/sweep/GameLogic/Module/AIUpdate.h`|
|ObjectStatusTypes|`inputs/reference/shims/bfmeobject/GameLogic/Object.h`|
|QMStatus|`inputs/reference/shims/nat/GameNetwork/GameSpy/PeerThread.h`|
|SaveCode|`inputs/reference/shims/gamestatepristinemapname/Common/GameState.h`|
|SnapshotType|`inputs/reference/shims/gamestatepristinemapname/Common/GameState.h`|
|WindowMsgHandledType|`inputs/reference/shims/gamewindow/GameClient/GameWindow.h`|
