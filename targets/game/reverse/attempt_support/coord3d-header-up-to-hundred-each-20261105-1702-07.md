# Adopt the registered Coord3D header in 1 units

Base: `192ee1d93575be3f035016e9f88ed69bbba7e31b`. Native scope: 3 existing rows and 12 emitted code definitions.
Native header acceptance retired 0 queue keys.

The compiler reports the same field offsets, sizes and class kind before and after.
The normal byte and frozen-file checks pass. Complete non-debug object sections,
code definitions and relocation bindings agree. The existing canonical header is
the only addition to the resolved dependency set in each source.

Linking is evaluated separately against the dated census.
A full image link and runtime behaviour remain outside this evidence.

| Source | Existing rows | Emitted code definitions |
| --- | ---: | ---: |
| `game/GameEngine/Source/GameLogic/Object/Update/Rva00291F20Update.cpp` | 3 | 12 |
