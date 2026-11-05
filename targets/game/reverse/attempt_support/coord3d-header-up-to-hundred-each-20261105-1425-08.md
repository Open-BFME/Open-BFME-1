# Adopt the registered Coord3D header in 1 units

Base: `39e1df0ce84409c193a2b82a10a4def2ebbb4d9e`. Native scope: 1 existing rows and 1 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/AI/AIMoveToStateSA_computePath_rva00173680.cpp` | 1 | 1 |
