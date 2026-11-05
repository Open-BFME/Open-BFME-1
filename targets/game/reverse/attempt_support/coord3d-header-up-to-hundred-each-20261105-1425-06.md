# Adopt the registered Coord3D header in 19 units

Base: `c01e38222ffe094b42e4dcca05b991fd0ae16570`. Native scope: 28 existing rows and 159 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_createSpecialObject.cpp` | 1 | 19 |
| `game/GameEngine/Source/GameLogic/AI/AICommandInterfaceFollowPathCommands.cpp` | 8 | 33 |
| `game/GameEngine/Source/GameLogic/Object/Update/OCLUpdateUpdate.cpp` | 1 | 7 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapRva0074B480.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BCB60GoalRouting.cpp` | 2 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Update/OneRingTrajectory00299400.cpp` | 1 | 27 |
| `game/GameEngine/Source/GameLogic/AI/AIEnterState_onEnter_Bfme.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamCaptureNearestUnownedFactionUnit.cpp` | 1 | 17 |
| `game/GameEngine/Source/Common/Rva006DF650TriggerArea.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/Object/Die/crushLocationCheck_Thunk.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackState_xfer.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderCheckForPossible.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderIterateCircular3.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_projectileFire.cpp` | 1 | 12 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/ParkingPlaceInfoVectorInsertOverflow.cpp` | 2 | 4 |
| `game/GameEngine/Source/GameClient/MessageStream/GUICommandTranslator_doAttackMoveCommand.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeWaitPathState_update.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/AI/AIPlayerComputeCenterAndRadiusOfBase.cpp` | 1 | 9 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D7680.cpp` | 1 | 3 |
