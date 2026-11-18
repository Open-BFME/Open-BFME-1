# Existing enum contracts, cohort114

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
|1415|GeometryType|`game/GameEngine/Source/GameLogic/Map/TerrainRecordScan001AEFF0.cpp`|1|1099|`{}`|
|1416|GeometryType|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorCtorThunk.cpp`|1|661|`{}`|
|1417|GeometryType|`game/GameEngine/Source/Common/Thing/ThingTemplateInitForLTA.cpp`|1|1334|`{}`|
|1418|GeometryType|`game/GameEngine/Source/Common/BfmeT1035Use.cpp`|1|557|`{}`|
|1419|GeometryType|`game/GameEngine/Source/Common/System/BuildAssistant_moveObjectsForConstruction.cpp`|1|1109|`{}`|
|1420|ParticleSystemID|`game/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleSystemManagerCreateParticleSystem.cpp`|1|182|`{}`|
|1421|ParticleSystemID|`game/GameEngine/Source/GameClient/System/ParticleSystemManager_destroyByID.cpp`|1|84|`{}`|
|1422|ParticleSystemID|`game/GameEngine/Source/GameClient/System/Particle_loadPostProcess.cpp`|1|161|`{}`|
|1423|ParticleSystemID|`game/GameEngine/Source/GameClient/System/ParticleSystem_loadPostProcess.cpp`|1|329|`{"PARTICLE_SYSTEM_ID_NONE": 0}`|
|1424|ParticleSystemID|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_deleteAllParticleSystems.cpp`|1|234|`{}`|
|1425|ParticleSystemID|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_updateSubObjectsFromShroud.cpp`|1|244|`{}`|
|1426|ParticleSystemID|`game/GameEngine/Source/GameLogic/LivingWorld/Rva0061DA30BaseDestructor.cpp`|1|221|`{}`|
|1427|ParticleSystemID|`game/GameEngine/Source/GameClient/System/ParticleSystemManager_findByID.cpp`|1|171|`{}`|
|1428|ParticleSystemID|`game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_doParticleSystemAtBone.cpp`|1|323|`{}`|
|1429|ParticleSystemID|`game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateXfer.cpp`|1|435|`{}`|
|1430|ParticleSystemID|`game/GameEngine/Source/GameLogic/Object/Update/LaserUpdateClientUpdate.cpp`|1|846|`{}`|
|1431|ParticleSystemID|`game/GameEngine/Source/GameLogic/Object/Update/LaserUpdate_initLaser.cpp`|1|776|`{}`|
|1432|ParticleSystemID|`game/GameEngine/Source/GameClient/System/ParticleSys_ParticleSystem_ctor.cpp`|1|1426|`{}`|
|1433|SpecialPowerType|`game/GameEngine/Source/Common/BfmeConv408.cpp`|1|70|`{}`|
|1434|CrushSquishTestType|`game/GameEngine/Source/GameLogic/Object/Object_rva001CC790_crushPolicy.cpp`|1|113|`{}`|
|1435|SpecialPowerType|`game/GameEngine/Source/Common/RTS/Rva000EDF80TeamMemberScan.cpp`|1|90|`{"SPECIAL_INVALID": 0}`|
|1436|SpecialPowerType|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_getSpecialPowerType.cpp`|1|45|`{}`|
|1437|SpecialPowerType|`game/GameEngine/Source/GameLogic/ScriptEngine/ObjectDoSpecialPower.cpp`|1|183|`{"SPECIAL_POWER_TYPE_UNKNOWN": 0}`|
|1438|CrushSquishTestType|`game/GameEngine/Source/GameLogic/AI/PathfinderStepE0370.cpp`|1|458|`{}`|
|1439|CrushSquishTestType|`game/GameEngine/Source/GameLogic/Object/ObjectCanCrushOrSquish.cpp`|1|223|`{}`|
|1440|SpecialPowerType|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_isWithinStartAbilityRange.cpp`|1|696|`{"DummyPower002A79B0": 0}`|
|1441|CrushSquishTestType|`game/GameEngine/Source/GameLogic/AI/PathfinderStepE05B0.cpp`|1|715|`{"CRUSH_SQUISH_INVALID": 0}`|
|1442|DistanceCalculationType|`game/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFXRubbleNeighbors.cpp`|1|407|`{}`|
|1443|DistanceCalculationType|`game/GameEngine/Source/Common/System/BuildAssistant_clearRemovableForConstruction.cpp`|1|438|`{}`|
|1444|CrushSquishTestType|`game/GameEngine/Source/GameLogic/Object/ObjectRva001CFF30.cpp`|1|532|`{}`|
|1445|SpecialPowerType|`game/GameEngine/Source/GameClient/MessageStream/Rva005ACF80SpecialPower.cpp`|1|746|`{"SPECIAL_INVALID": 0}`|
|1446|DistanceCalculationType|`game/GameEngine/Source/Common/System/BuildAssistantAddBibs.cpp`|1|452|`{}`|
|1447|SpecialPowerType|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_startPreparation.cpp`|1|856|`{"DummyPower002A9420": 0}`|
|1448|DistanceCalculationType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardMachine_lookForInnerTarget.cpp`|1|1106|`{}`|
|1449|SpecialPowerType|`game/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdateScanClosestTarget.cpp`|1|974|`{"SPECIAL_POWER_INVALID": 0}`|
|1450|DistanceCalculationType|`game/GameEngine/Source/Common/RTS/Team_updateState.cpp`|1|1293|`{}`|
|1451|DistanceCalculationType|`game/GameEngine/Source/GameLogic/AI/AIPlayerIsLocationSafe.cpp`|1|388|`{}`|
|1452|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/IMECandidateWindowInput.cpp`|1|6|`{}`|
|1453|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/MessageBox.cpp`|1|680|`{}`|
|1454|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarBeacon.cpp`|1|62|`{}`|
|1455|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGameSystem.cpp`|1|764|`{}`|
|1456|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlaySystem.cpp`|1|784|`{}`|
|1457|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlayRCMenuSystem.cpp`|1|1023|`{}`|
|1458|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Rva004C0560.cpp`|1|1459|`{}`|
|1459|WindowMsgHandledType|`game/GameEngine/Source/GameClient/GUI/Gadget/GadgetPushButtonInput.cpp`|1|1444|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|CrushSquishTestType|`inputs/reference/shims/sweep/GameLogic/Object.h`|
|DistanceCalculationType|`inputs/reference/shims/partitiondataoutofline/GameLogic/PartitionManager.h`|
|GeometryType|`game/GameEngine/Source/Common/System/geometry.h`|
|ParticleSystemID|`inputs/reference/shims/particlecount/GameClient/ParticleSys.h`|
|SpecialPowerType|`inputs/reference/shims/bfmeobject/GameLogic/Object.h`|
|WindowMsgHandledType|`inputs/reference/shims/gamewindow/GameClient/GameWindow.h`|
