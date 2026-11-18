# Existing enum contracts, cohort116

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
|1503|TimeOfDay|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapSetTimeOfDay.cpp`|1|71|`{"TIME_OF_DAY_FIRST": 0}`|
|1504|GameWindowMessage|`game/GameEngine/Source/GameClient/MessageStream/Rva005A67E0Translator.cpp`|1|970|`{}`|
|1505|GameWindowMessage|`game/GameEngine/Source/GameClient/MessageStream/WindowXlat.cpp`|1|176|`{}`|
|1506|TimeOfDay|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicLoadMap.cpp`|1|607|`{"TIME_OF_DAY_COUNT": 6, "TIME_OF_DAY_INTERPOLATE": 5}`|
|1507|TimeOfDay|`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenZoomFilterSet.cpp`|1|641|`{"TIME_OF_DAY_COUNT": 6, "TIME_OF_DAY_INTERPOLATE": 5}`|
|1508|GameWindowMessage|`game/GameEngine/Source/GameClient/Input/Mouse_createStreamMessages.cpp`|1|1140|`{}`|
|1509|GameWindowMessage|`game/GameEngine/Source/GameClient/MessageStream/Rva005B9C70WindowTranslator.cpp`|1|908|`{}`|
|1510|SaveFileType|`game/GameEngine/Source/Common/System/SaveGame/BfmeGameStateSaveListPopulate.cpp`|1|798|`{}`|
|1511|TimeOfDay|`game/GameEngine/Source/GameLogic/Object/Contain/CaveContainRecalcApparentControllingPlayer.cpp`|1|227|`{}`|
|1512|SaveFileType|`game/GameEngine/Source/Common/System/SaveGame/GameStatePopulateSaveGameListboxBFME.cpp`|1|1286|`{}`|
|1513|RadarEventType|`game/GameEngine/Source/Common/System/RadarCreateEventThunk.cpp`|1|5|`{"RadarEventTypeDummy": 0}`|
|1514|NetLocalStatus|`game/GameEngine/Source/GameNetwork/Network_AllCommandsReady.cpp`|1|41|`{}`|
|1515|AttitudeType|`game/GameEngine/Source/Common/BfmeThreeHundredTwenty.cpp`|1|45|`{}`|
|1516|NetLocalStatus|`game/GameEngine/Source/GameNetwork/Network_init.cpp`|1|185|`{}`|
|1517|RadarEventType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsDoTeamRadarCreateEventThunk.cpp`|1|96|`{}`|
|1518|NetLocalStatus|`game/GameEngine/Source/GameNetwork/Network_isPlayerConnected.cpp`|1|47|`{}`|
|1519|NetLocalStatus|`game/GameEngine/Source/GameNetwork/Network_quitGame.cpp`|1|37|`{}`|
|1520|SerialAuthResult|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadDisconnectedCallback.cpp`|1|345|`{}`|
|1521|RadarEventType|`game/GameEngine/Source/GameLogic/System/CastleBehaviorRva0036F4D0EvaNotify.cpp`|1|504|`{"RADAR_EVENT_INVALID": -1}`|
|1522|NetLocalStatus|`game/GameEngine/Source/GameNetwork/Network_GetCommandsFromCommandList.cpp`|1|352|`{}`|
|1523|NetLocalStatus|`game/GameEngine/Source/GameNetwork/Network_RelayCommandsToCommandList.cpp`|1|375|`{}`|
|1524|AttitudeType|`game/GameEngine/Source/GameLogic/Object/ObjectSetOrRestoreTeam.cpp`|1|581|`{"ATTITUDE_ZERO": 0}`|
|1525|BuildableStatus|`game/GameEngine/Source/GameLogic/System/BuildableStatusHashResize.cpp`|1|418|`{}`|
|1526|BuildableStatus|`game/GameEngine/Source/Common/RTS/Player_canBuild.cpp`|1|303|`{}`|
|1527|BuildableStatus|`game/GameEngine/Source/GameLogic/System/GameLogicReset.cpp`|1|614|`{}`|
|1528|GameSpyBuddyStatus|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/updateBuddyStatus.cpp`|1|580|`{}`|
|1529|MoodMatrixAction|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_getMoodMatrixActionAdjustment.cpp`|1|408|`{}`|
|1530|GameSpyBuddyStatus|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadJoinRoomCallback.cpp`|1|626|`{}`|
|1531|ParticlePriorityType|`game/GameEngine/Source/GameClient/System/ParticleSystemGetPriority.cpp`|1|4|`{"PARTICLE_PRIORITY_NONE": 0}`|
|1532|ParticlePriorityType|`game/GameEngine/Source/GameClient/System/ParticleSystemManagerRemoveOldestParticles.cpp`|1|95|`{"PARTICLE_PRIORITY_NONE": 0}`|
|1533|ModuleType|`game/GameEngine/Source/Common/Thing/Rva00140070CollectModuleAssets.cpp`|1|235|`{}`|
|1534|ModuleType|`game/GameEngine/Source/Common/Thing/ModuleFactory_rva00127e80.cpp`|1|95|`{}`|
|1535|ObjectScriptStatusBit|`game/GameEngine/Source/Common/System/BuildAssistant_canMakeUnit.cpp`|1|411|`{}`|
|1536|SlowDeathPhaseType|`game/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior_doPhaseStuff_Thunk.cpp`|1|504|`{}`|
|1537|ObjectScriptStatusBit|`game/GameEngine/Source/Common/BfmeObjNotify3F0Notify.cpp`|1|332|`{}`|
|1538|ControlBarContext|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_reset.cpp`|1|496|`{}`|
|1539|ControlBarContext|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateVirtual.cpp`|1|684|`{}`|
|1540|WindowVideoPlayType|`game/GameEngine/Source/GameClient/GUI/WindowVideoManager.cpp`|1|135|`{}`|
|1541|ScienceAvailabilityType|`game/GameEngine/Source/Common/RTS/Player_getScienceAvailabilityTypeFromString.cpp`|1|134|`{}`|
|1542|CpuType|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerMinimumRequirements.cpp`|1|182|`{}`|
|1543|AIStateType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceWaypointGoalPathSize.cpp`|1|77|`{}`|
|1544|CBCommandStatus|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarProcessCommandTransitionUIThunk.cpp`|1|63|`{}`|
|1545|ShadowType|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawXfer.cpp`|1|312|`{}`|

|Enum|Existing BFME1 source of contract|
|---|---|
|AIStateType|`inputs/reference/shims/sweep/GameLogic/AIStateMachine.h`|
|AttitudeType|`inputs/reference/shims/aicommandoutofline/GameLogic/AI.h`|
|BuildableStatus|`inputs/reference/shims/sweep/Common/ThingTemplate.h`|
|CBCommandStatus|`inputs/reference/shims/sweep/GameClient/ControlBar.h`|
|ControlBarContext|`inputs/reference/shims/sweep/GameClient/ControlBar.h`|
|CpuType|`inputs/reference/shims/gamelod/Common/GameLOD.h`|
|GameSpyBuddyStatus|`inputs/reference/shims/peerdefs/GameNetwork/GameSpy/PeerDefs.h`|
|GameWindowMessage|`inputs/reference/shims/gamewindow/GameClient/GameWindow.h`|
|ModuleType|`game/GameEngine/Include/Common/Module.h`|
|MoodMatrixAction|`inputs/reference/shims/sweep/GameLogic/Module/AIUpdate.h`|
|NetLocalStatus|`inputs/reference/shims/firewall/GameNetwork/NetworkDefs.h`|
|ObjectScriptStatusBit|`inputs/reference/shims/bfmeobject/GameLogic/Object.h`|
|ParticlePriorityType|`inputs/reference/shims/particlecount/GameClient/ParticleSys.h`|
|RadarEventType|`inputs/reference/shims/radar/Common/Radar.h`|
|SaveFileType|`inputs/reference/shims/gamestatepristinemapname/Common/GameState.h`|
|ScienceAvailabilityType|`inputs/reference/shims/player/Common/Player.h`|
|SerialAuthResult|`inputs/reference/shims/nat/GameNetwork/GameSpy/PeerThread.h`|
|ShadowType|`inputs/reference/shims/sweep/GameClient/Shadow.h`|
|SlowDeathPhaseType|`inputs/reference/shims/slowdeathmoduledatadtor/GameLogic/Module/SlowDeathBehavior.h`|
|TimeOfDay|`game/GameEngine/Source/Common/game_type.h`|
|WindowVideoPlayType|`game/GameEngine/Source/GameClient/window_video_manager.h`|
