# Adopt the registered Coord3D header in 16 units

Base: `31c8ddea62d281e3e00d40b81be8aa90f4d3c24f`. Native scope: 20 existing rows and 99 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census. A full image link
and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBufferLoadMapBridges.cpp` | 1 | 9 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BD630StateTransition.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/Rva00354220ConditionSetType.cpp` | 1 | 13 |
| `game/GameEngine/Source/GameClient/System/FXParticleSystem/LifeEventSlot1.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/AIFollowPathAsTeamState_computePath_Bfme.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/Object/WeaponMakeAssistanceRequest.cpp` | 1 | 4 |
| `game/GameEngine/Source/Common/BfmeHostCW_Rva0033C120.cpp` | 1 | 2 |
| `game/GameEngine/Source/GameLogic/Object/Update/LaserUpdate_xfer.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/AI/AICommandInterfaceUnnamedBfmeCommands.cpp` | 5 | 17 |
| `game/GameEngine/Source/GameLogic/Object/Contain/OpenContainScatterToNearbyPosition.cpp` | 1 | 5 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate_findGoodBuildOrRepairPositionAndTarget.cpp` | 1 | 1 |
| `game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doCameraMotionBlurJump.cpp` | 1 | 4 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDrawDoDrawModule.cpp` | 1 | 10 |
| `game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdateInitializeBonePositions.cpp` | 1 | 11 |
| `game/GameEngine/Source/GameLogic/AI/AIMoveAndDeleteState_onEnter.cpp` | 1 | 11 |
| `game/GameEngine/Source/GameLogic/Map/TerrainLogicFlattenTerrain.cpp` | 1 | 8 |
