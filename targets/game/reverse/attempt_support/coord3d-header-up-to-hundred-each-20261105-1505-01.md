# Adopt the registered Coord3D header in 20 units

Base: `2316a4f8426e107ab94dd5180d845b8944875da2`. Native scope: 33 existing rows and 281 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingBehaviorXfer.cpp` | 1 | 22 |
| `game/GameEngine/Source/GameLogic/Object/Locomotor_maintainCurrentPositionWings.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameLogic/Object/AttackNugget_create_Thunk.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceFollowPath.cpp` | 3 | 6 |
| `game/GameEngine/Source/Common/Rva006DF730ClampToArea.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGuardForFramecount.cpp` | 1 | 11 |
| `game/GameEngine/Source/GameLogic/AI/AICommandInterfacePositionCommands.cpp` | 10 | 22 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewResetBfme.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainLoadGarrisonPoints.cpp` | 1 | 25 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetPlayersNearestUnitOfTypeToReference.cpp` | 1 | 13 |
| `game/GameEngine/Source/GameLogic/AI/AIWanderInPlaceState_onEnter.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_rva001F1B90.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva00245010RecordBuild.cpp` | 1 | 58 |
| `game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldRegionManager_Rva003C8160.cpp` | 1 | 8 |
| `game/GameEngine/Source/GameLogic/Map/FindPositionAround001AF610.cpp` | 1 | 6 |
| `game/GameEngine/Source/GameLogic/Object/ObjectDoCommandButtonAtObject.cpp` | 1 | 29 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGuard.cpp` | 1 | 11 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderDestinationWork.cpp` | 2 | 4 |
| `game/GameEngine/Source/GameClient/MapUtil_loadMap.cpp` | 2 | 40 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_SkirmishFireSpecialPowerAtMostCost.cpp` | 1 | 8 |
