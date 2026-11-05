# Adopt the registered Coord3D header in 20 units

Base: `d81a9d6d7e1e65d4300005e7e77985898cd902fc`. Native scope: 33 existing rows and 139 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameClient/FXListDoFXObjThunk.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldRegionManager_Rva003C8B90.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Die/FXListDieOnDie.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderIterateCircular2.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/AI/Rva00173C70MoveAwayUpdates.cpp` | 2 | 2 |
| `game/GameEngine/Source/GameLogic/Map/TerrainLogicP48ClearNear.cpp` | 1 | 3 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewUpdateCameraMovementsBfme.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackState_onEnter.cpp` | 1 | 11 |
| `game/GameEngine/Source/GameLogic/AI/Rva003EE9F0.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_privateGuardPositionClipped.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameClient/RadiusDecalTemplate_createSelection.cpp` | 1 | 7 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/HeightMapLineMaxHeight_006C6910.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/AI/PathfinderRva003E4190.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/Rva00200DF0OnDie.cpp` | 1 | 19 |
| `game/GameEngine/Source/GameLogic/AI/AICommandInterfaceBfmeObjectCommands.cpp` | 7 | 19 |
| `game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateReleaseLastExit.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doFireSpecialPowerOnTeam.cpp` | 1 | 6 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva007202F0.cpp` | 1 | 14 |
| `game/GameEngine/Source/GameLogic/AI/AICommandInterfaceMovementOrders.cpp` | 7 | 19 |
| `game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_onContaining.cpp` | 1 | 13 |
