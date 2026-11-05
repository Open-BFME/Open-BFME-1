# Adopt the registered Coord3D header in 4 units

Base: `818463cf1519e637dba0cc738fa909ccbad4505e`. Native scope: 4 existing rows and 27 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardInnerState_update.cpp` | 1 | 8 |
| `game/GameEngine/Source/GameLogic/Object/Behavior/RunwayInfoVectorInsertOverflowBody.cpp` | 1 | 4 |
| `game/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate_doDamageLine.cpp` | 1 | 5 |
| `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DView_initBfme.cpp` | 1 | 10 |
