# Existing enum contracts, cohort112

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
|1315|WeaponSlotType|`game/GameEngine/Source/GameLogic/AI/AIAttackSquadStateChooseVictim.cpp`|1|949|`{}`|
|1316|StateExitType|`game/GameEngine/Source/GameLogic/Object/Update/Rva002B7F40_clearModelCondition.cpp`|1|48|`{}`|
|1317|StateExitType|`game/GameEngine/Source/Common/BfmeConv619.cpp`|1|52|`{}`|
|1318|StateExitType|`game/GameEngine/Source/Common/BfmeThreeHundredTwentyEight.cpp`|1|47|`{}`|
|1319|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva00177A40State_onExit.cpp`|1|61|`{"STATE_EXIT_NORMAL": 0}`|
|1320|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva0017AE70State_onExit.cpp`|1|59|`{"STATE_EXIT_NORMAL": 0}`|
|1321|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva0017ADC0State_onExit.cpp`|1|63|`{"STATE_EXIT_NORMAL": 0}`|
|1322|StateExitType|`game/GameEngine/Source/Common/StateMachineDestructorThunk.cpp`|1|224|`{}`|
|1323|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva001741B0StateExitCleanup.cpp`|1|72|`{"STATE_EXIT_NORMAL": 0}`|
|1324|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva0017EE60State_onExit.cpp`|1|102|`{"STATE_EXIT_NORMAL": 0}`|
|1325|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva00178B40State_onExit.cpp`|1|95|`{"STATE_EXIT_NORMAL": 0}`|
|1326|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva00179A90State_onExit.cpp`|1|94|`{"STATE_EXIT_NORMAL": 0}`|
|1327|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva00170460AIStateMachine_clear.cpp`|1|90|`{}`|
|1328|StateExitType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdSwoopStateOnExit.cpp`|1|176|`{"STATE_EXIT_UNKNOWN": 0}`|
|1329|StateExitType|`game/GameEngine/Source/GameLogic/AI/AIExitStateOnExit.cpp`|1|54|`{}`|
|1330|StateExitType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowWaypointPathStateOnExit.cpp`|1|172|`{"STATE_EXIT_UNKNOWN": 0}`|
|1331|StateExitType|`game/GameEngine/Source/GameLogic/AI/AIAttackStateOnExitClean.cpp`|1|328|`{"STATE_EXIT_NORMAL": 0}`|
|1332|StateExitType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowPathStateOnExit.cpp`|1|185|`{"STATE_EXIT_UNKNOWN": 0}`|
|1333|StateExitType|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_onExit.cpp`|1|174|`{"STATE_EXIT_NORMAL": 0}`|
|1334|StateExitType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdFollowThruStateOnExit.cpp`|1|210|`{"STATE_EXIT_UNKNOWN": 0}`|
|1335|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva0017DC90State_onExit.cpp`|1|131|`{"STATE_EXIT_NORMAL": 0, "STATE_EXIT_RESET": 1}`|
|1336|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva0017BF00State_onExit.cpp`|1|89|`{"STATE_EXIT_NORMAL": 0}`|
|1337|StateExitType|`game/GameEngine/Source/GameLogic/AI/Rva00170BD0AIGuardState_onExit.cpp`|1|120|`{}`|
|1338|StateExitType|`game/GameEngine/Source/Common/BfmeConv613.cpp`|1|53|`{}`|
|1339|StateExitType|`game/GameEngine/Source/Common/BfmeConv1861.cpp`|1|91|`{}`|
|1340|StateExitType|`game/GameEngine/Source/Common/BfmeConv2063.cpp`|1|111|`{}`|
|1341|ScienceType|`game/GameEngine/Source/Common/RTS/ScienceStoreInternalName.cpp`|1|62|`{}`|
|1342|ScienceType|`game/GameEngine/Source/Common/RTS/ProductionPrerequisiteCopyCtor.cpp`|1|157|`{}`|
|1343|ScienceType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineNotifyAcquiredScience.cpp`|1|68|`{"Rva0034E1B0ScienceType": 0}`|
|1344|ScienceType|`game/GameEngine/Source/Common/RTS/PlayerAddScienceIncrementalThunk.cpp`|1|5|`{}`|
|1345|ScienceType|`game/GameEngine/Source/Common/RTS/PlayerRva000D42A0Sciences.cpp`|1|146|`{}`|
|1346|ScienceType|`game/GameEngine/Source/Common/Rva002CF610Flags.cpp`|1|86|`{"SCIENCE_PLACEHOLDER": 0}`|
|1347|ScienceType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineIsScienceAcquired.cpp`|1|90|`{"Rva0034C830ScienceType": 0}`|
|1348|ScienceType|`game/GameEngine/Source/GameLogic/Object/SpecialPower/OCLSpecialPowerFindOCL.cpp`|1|78|`{}`|
|1349|ScienceType|`game/GameEngine/Source/GameLogic/Object/SpecialPower/CashHackSpecialPowerFindAmountToStealThunk.cpp`|1|78|`{"SCIENCE_UNRECONSTRUCTED": 0}`|
|1350|ScienceType|`game/GameEngine/Source/Common/Rva003C2720ScienceVectorCopy.cpp`|1|134|`{"Rva003C2720ScienceType": 0}`|
|1351|ScienceType|`game/GameEngine/Source/Common/INI/INI_parseScienceVector.cpp`|1|199|`{}`|
|1352|ScienceType|`game/GameEngine/Source/Common/GenDtor006952C0.cpp`|1|226|`{}`|
|1353|ScienceType|`game/GameEngine/Source/Common/RTS/ProductionPrerequisiteIsSatisfied.cpp`|1|254|`{}`|
|1354|ScienceType|`game/GameEngine/Source/Common/INI/ScienceGroupVectorFillInsert.cpp`|1|421|`{}`|
|1355|ScienceType|`game/GameEngine/Source/Common/System/XferScienceElement.cpp`|1|258|`{}`|
|1356|ScienceType|`game/GameEngine/Source/Common/RTS/Player_setRankLevel.cpp`|1|471|`{}`|
|1357|ScienceType|`game/GameEngine/Source/GameClient/GUI/Palantir/AptScreenSpellStoreUpdate000062DF.cpp`|1|441|`{}`|
|1358|ScienceType|`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/CrateCollide_isValidToExecute.cpp`|1|260|`{}`|
|1359|ScienceType|`game/GameEngine/Source/Common/RTS/Player_resetSciences.cpp`|1|250|`{"SCIENCE_VALUE": 0}`|
|1360|ScienceType|`game/GameEngine/Source/GameLogic/AI/AIPlayerDoUpgradesAndSkills.cpp`|1|740|`{}`|
|1361|ScienceType|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_bfmeQueryWD.cpp`|1|268|`{}`|
|1362|ScienceType|`game/GameEngine/Source/Common/System/XferScienceVector.cpp`|1|294|`{}`|
|1363|ScienceType|`game/GameEngine/Source/Common/INI/ScienceGroupVectorInsertOverflow.cpp`|1|284|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|ScienceType|`inputs/reference/shims/science/Common/Science.h`|
|StateExitType|`inputs/reference/shims/sweep/Common/StateMachine.h`|
|WeaponSlotType|`game/GameEngine/Source/Common/game_type.h`|
