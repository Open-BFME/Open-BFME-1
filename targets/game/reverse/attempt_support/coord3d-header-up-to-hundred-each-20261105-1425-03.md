# Adopt the registered Coord3D header in 20 units

Base: `f5c1b5d38a81a56a09af463e82071b287bd1f5dc`. Native scope: 32 existing rows and 138 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate_aiDoCommand.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002C3FE0HeightClearance.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameClient/Drawable_getPristineBonePositions.cpp` | 2 | 2 |
| `game/GameEngine/Source/GameClient/MapMetaData_assign.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/AIFaceState_update_Bfme.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/Pathfinder/PathfinderValidMovementPosition.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameLogic/AI/AICommandInterfaceObjectCommands.cpp` | 6 | 18 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSkirmishAttackNearestGroupWithValue.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameLogic/AI/AIMoveToStateSA_onEnter_rva001737C0.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderObjectCell.cpp` | 1 | 4 |
| `game/Libraries/Source/WWVegas/WWLib/Coord3DVectorInsertOverflow.cpp` | 1 | 3 |
| `game/GameEngine/Source/Common/FillDamageInfo002DD390.cpp` | 1 | 1 |
| `game/GameEngine/Source/Common/Rva0016D5F0PathTest.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/AICommandInterfaceGuardCommands.cpp` | 5 | 17 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitTeleportToWaypoint.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameLogic/AI/AIGroup_groupDoSpecialPowerAtObject.cpp` | 1 | 47 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior_doPhaseStuff_Thunk.cpp` | 1 | 14 |
| `game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitInterface.cpp` | 3 | 3 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva0032A550.cpp` | 1 | 1 |
| `game/GameEngine/Source/Common/Rva00618740MoveArmyToPosition.cpp` | 1 | 1 |
