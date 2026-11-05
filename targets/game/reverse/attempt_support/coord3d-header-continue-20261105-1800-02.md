# Adopt the registered Coord3D header in 7 units

Base: `9d5877f13af835b797e37007ac6df2f91e67397d`. Native scope: 46 existing rows and 184 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdateScanClosestTarget.cpp` | 1 | 53 |
| `game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar_buildTerrainTexture.cpp` | 2 | 28 |
| `game/GameEngine/Source/GameLogic/AI/AIAttackSquadStateChooseVictim.cpp` | 1 | 24 |
| `game/GameEngine/Source/GameLogic/Object/Die/CreateCrateDie.cpp` | 5 | 30 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceCommandDispatch.cpp` | 2 | 5 |
| `game/GameEngine/Source/GameClient/InGameUIBodies.cpp` | 11 | 17 |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateCommands.cpp` | 24 | 27 |
