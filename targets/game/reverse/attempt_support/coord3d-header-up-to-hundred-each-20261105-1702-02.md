# Adopt the registered Coord3D header in 20 units

Base: `8e75cf11b3b2aaf15f0b5928b547c911332415fe`. Native scope: 54 existing rows and 341 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Object/Object_rva001CC250.cpp` | 1 | 7 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineNamedMapReveal.cpp` | 6 | 44 |
| `game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainTrackTargets.cpp` | 3 | 7 |
| `game/GameEngine/Source/GameNetwork/NetPacket_FillBufferWithGameCommand.cpp` | 2 | 12 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_update.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/Rva003273A0SpecialPowerAction.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/System/CastleBehaviorRva0036F4D0EvaNotify.cpp` | 1 | 19 |
| `game/GameEngine/Source/GameLogic/AI/pathfind_iterateCellsAlongLine_world.cpp` | 13 | 13 |
| `game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_update.cpp` | 2 | 13 |
| `game/GameEngine/Source/Common/BfmeConv1982.cpp` | 2 | 32 |
| `game/GameEngine/Source/GameClient/InGameUIRva00442FD0.cpp` | 1 | 17 |
| `game/GameEngine/Source/GameLogic/System/BfmeCellGrid.cpp` | 7 | 9 |
| `game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUnderConstruction.cpp` | 1 | 31 |
| `game/GameEngine/Source/GameLogic/AI/Rva00174A20State_update.cpp` | 1 | 7 |
| `game/GameEngine/Source/GameLogic/Object/Update/Rva00257DB0PartitionScan.cpp` | 1 | 73 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsCamera.cpp` | 2 | 4 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetRefToNearestTeamOfTypeOwnedByPlayer.cpp` | 1 | 14 |
| `game/GameEngine/Source/GameLogic/AI/AITNGuardIdleState_update_Bfme.cpp` | 1 | 19 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderLineQueries.cpp` | 6 | 7 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/MoodTargetCheck0027ACF0.cpp` | 1 | 6 |
