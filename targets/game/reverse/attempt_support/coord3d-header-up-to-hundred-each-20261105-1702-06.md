# Adopt the registered Coord3D header in 12 units

Base: `d40aada48c7f102ad50fc2ac08875f526fdc8b02`. Native scope: 27 existing rows and 303 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Map/TerrainLogicNameLookups.cpp` | 7 | 15 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardMachine_lookForInnerTarget.cpp` | 1 | 48 |
| `game/GameEngine/Source/GameLogic/AI/AIPlayerOnUnitProduced.cpp` | 1 | 68 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdSwoopStateOnEnter.cpp` | 1 | 7 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAttackMoveToStateOnEnter.cpp` | 4 | 8 |
| `game/GameEngine/Source/GameLogic/AI/AIPlayerIsLocationSafe.cpp` | 1 | 14 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/TeamCommandQuery002FBC90.cpp` | 4 | 43 |
| `game/GameEngine/Source/GameLogic/Object/Update/StealthUpdateChangeVisualDisguise.cpp` | 1 | 14 |
| `game/GameEngine/Source/Common/System/Rva00101820BuildObjectNow.cpp` | 1 | 43 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderStepD4F90.cpp` | 2 | 11 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsUseCommandButtonOnNearestThing.cpp` | 3 | 27 |
| `game/GameEngine/Source/GameLogic/Object/Object_clearDisabled_Thunk.cpp` | 1 | 5 |
