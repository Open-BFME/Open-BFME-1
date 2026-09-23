# TerrainLogic farthest-edge identity at 0x001A38B0

The retail `TerrainLogicBase` constructor at 0x001ADB80 installs primary
vtable 0x0109C428. The terrain constructor at 0x006BE070 installs primary
vtable 0x0111D090. In both tables, slot 13 (`+0x34`) routes through ILT
0x0000B2E4 to 0x001A3770, the adjacent closest-edge body. Slot 14 (`+0x38`)
routes through ILT 0x0000D1CA to **0x001A38B0**. These are image pointers,
independent of the ledger's existing names.

The 151-byte body at 0x001A38B0 calls `this` vtable slots `+0x20` to get a
`Region3D` and `+0x18` to get ground height. It chooses the far x and y edges
by comparing the input against half the extent's width and height, then writes
the chosen x, y, and sampled z to the first stack pointer. The retail float at
VA 0x0107533C is exactly 0.5. It returns with `ret 8`: ECX is `this`, the
first stack argument is the hidden `Coord3D` return buffer, and the second is
`const Coord3D*`. The native declaration and implementation in
`Code/GameEngine/Include/GameLogic/TerrainLogic.h` and
`Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp` are named
`TerrainLogic::findFarthestEdgePoint(const Coord3D*) const` and have this
behavior and ABI.

`Code/GameEngine/Source/Common/BfmeConv1270.cpp` already reproduces all 151
retail bytes through the explicit-output C++ symbol
`?bfmeGet1270@BfmeA1270@@QAEXPAUBfmeVec1270@@0@Z`. The ledger uses
`object-symbol=` to retain that verified implementation while recording the
proven retail identity. The separately compiled native definition in
`TerrainLogic.cpp` remains marked `present-unmatched`; this correction does
not claim that its emitted bytes match.
