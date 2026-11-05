# Adopt the registered Coord3D header in 15 units

Base: `f4de767d7c270b8cab03b33678ba8344c400082d`. Native scope: 21 existing rows and 221 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Pathfinder/PathfinderIsAttackViewBlockedByObstacle.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Pathfinder/PathfindPrependCells.cpp` | 1 | 27 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonOnNearestKindof.cpp` | 1 | 15 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUIDraw.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Object/Update/SpecialEnemySenseUpdateUpdate.cpp` | 1 | 60 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/Rva002F9FF0.cpp` | 1 | 28 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsBuildBase.cpp` | 3 | 4 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamUseCommandButtonOnNearestEnemy.cpp` | 1 | 37 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_updateInternal.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate_doToppleDelayBurstFX.cpp` | 1 | 8 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_joinTeam.cpp` | 1 | 20 |
| `game/GameEngine/Source/Common/Rva002DCAE0WeaponRecord.cpp` | 3 | 3 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackSquadStateOnEnter.cpp` | 3 | 4 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardInnerState_onEnter.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameClient/InGameUI_updateAndDrawWorldAnimationsMethodThunk.cpp` | 1 | 4 |
