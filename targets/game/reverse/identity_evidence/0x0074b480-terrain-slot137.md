# 0x0074B480: terrain render object slot 137 has no evidenced name

The banked stash for 0x0074B480 declared the tail call as
`Rva0074B480Callback::update(bounds, map, mode)`.  That member name was a
placeholder chosen by the stash author (its own verdict says "Assumed the
byte-vector role and local callback declaration"); no evidence supported it.

What the image proves:

- The call is `call dword ptr [eax+0x224]` on `TheTerrainRenderObject`
  (0x012F7FE0): vtable slot 137, arguments (IRegion2D *, WorldHeightMap *
  this, 0).
- In the HeightMapRenderObjClass primary vtable 0x0111DC88, slot 137
  (+0x224, VA 0x0111DEAC) holds ILT 0x0042E087, which jumps to 0x006D1D80.
- 0x006D1D80 is an anonymous generated dump (`?d_006d1d80@@YAXXZ`,
  game/gen_asm/d_006c0fa0.asm); no symbol, string literal, or matched caller
  names it.

So the slot keeps its address token: `rva006D1D80`, on a TU-local
`Rva0074B480TerrainAbi` view of the terrain object.  The rewrite of the body
(game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapRva0074B480.cpp)
byte-matches retail with this declaration.
