# Adopt the registered Coord3D header in 19 units

Base: `9f253a48f994d9e56fc4bec300fef9896705218b`. Native scope: 33 existing rows and 174 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewResetCameraBfme.cpp` | 1 | 1 |
| `game/GameEngine/Source/Common/BfmeConv1872.cpp` | 2 | 2 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva00720D10.cpp` | 2 | 9 |
| `game/GameEngine/Source/GameLogic/Map/WaypointXfer.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Update/RainOfFireUpdate.cpp` | 1 | 6 |
| `game/GameEngine/Source/GameLogic/AI/AICommandParmsStorage.cpp` | 2 | 28 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowWaypointPathState_update.cpp` | 2 | 3 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceLoadPostProcess.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/AIGroup_recompute.cpp` | 1 | 12 |
| `game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_update_Thunk.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedUnitProperties.cpp` | 5 | 7 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_FireSpecialPowerHelper.cpp` | 1 | 9 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DQuadrupedDrawBonePositions.cpp` | 1 | 20 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamOrders.cpp` | 6 | 10 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamMoveToNearestObjectOfType.cpp` | 1 | 12 |
| `game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManagerParticleSystem.cpp` | 2 | 33 |
| `game/GameEngine/Source/GameLogic/Object/ObjectGetAbleToAttackSpecificObjectBFME.cpp` | 1 | 3 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/LuaEvaluateCondition.cpp` | 1 | 8 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewInitHeightForMapBfme.cpp` | 1 | 4 |
