# Adopt the registered Coord3D header in 14 units

Base: `80199b75761b7af595b8b5fe205f615287b7fdb1`. Native scope: 30 existing rows and 277 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveUnitTowardsNearest_Thunk.cpp` | 2 | 13 |
| `game/GameEngine/Source/GameLogic/AI/AIMoveAwayFromRepulsorsState_onEnter_Thunk.cpp` | 1 | 9 |
| `game/GameEngine/Source/GameLogic/AI/AIGroupAttackMoveOrder.cpp` | 2 | 21 |
| `game/GameEngine/Source/GameLogic/AI/AIFearState_update.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/AIGroup_computeIndividualDestination.cpp` | 1 | 13 |
| `game/GameEngine/Source/Common/RTS/TeamRva000F10F0Recruit.cpp` | 3 | 11 |
| `game/GameEngine/Source/GameClient/MessageStream/SelectionXlatCanSelectDrawable.cpp` | 1 | 8 |
| `game/GameEngine/Source/GameLogic/AI/AIGuardOuterState_onEnter_Bfme.cpp` | 1 | 5 |
| `game/GameEngine/Source/Common/Rva006E2540.cpp` | 1 | 10 |
| `game/GameEngine/Source/GameLogic/AI/AIPlayerSelectTeamToReinforce.cpp` | 1 | 48 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerActionDoActionState_update.cpp` | 1 | 62 |
| `game/GameEngine/Source/Common/RTS/Team_updateState.cpp` | 1 | 31 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorCreateSpawn.cpp` | 2 | 32 |
| `game/GameEngine/Source/GameClient/DrawableBFME.cpp` | 12 | 13 |
