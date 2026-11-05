# Adopt the registered Coord3D header in 13 units

Base: `9d1c7aedd1e7fc56f314feaa3c35d38febff1d32`. Native scope: 18 existing rows and 224 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsSkirmishSupplies.cpp` | 1 | 45 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonOnNearestEnemyBuildingClass.cpp` | 1 | 16 |
| `game/GameEngine/Source/GameLogic/Object/Update/RubbleRiseStep002A3B40.cpp` | 1 | 16 |
| `game/GameEngine/Source/Common/BfmeOneHundredOne.cpp` | 4 | 12 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUI_drawMoveHints.cpp` | 1 | 9 |
| `game/GameEngine/Source/Common/BfmeT1035Use.cpp` | 1 | 29 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doFireSpecialPowerOnNearestObjectTypeByPlayer.cpp` | 1 | 14 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveTeamTowardsNearest.cpp` | 1 | 23 |
| `game/GameEngine/Source/GameClient/InGameUISiegeDockSelection.cpp` | 1 | 15 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeWaitState_update.cpp` | 2 | 7 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonOnNearestGarrisonedBuilding.cpp` | 1 | 19 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamMoveToNearestObjectOfTypeOwnedByPlayer.cpp` | 1 | 16 |
| `game/GameEngine/Source/GameClient/BFMERopeDrawableInterpolatedPosition.cpp` | 2 | 3 |
