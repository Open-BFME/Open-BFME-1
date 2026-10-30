# 0x002B26C0 Rva002B26C0Owner::method (756 B) — s497 bank (a1)

Identity unchanged (address-derived; GeometryUpgrade caller 0x002D5980).
Body: iterate ThePartitionManager (0x009F2960) around the owner object with a
six-filter chain, and move every eligible object away from the owner by
(center - owner position) * 3.0f, then adjustDestination + setPosition +
AI slot 0x28 ->bfmeGo1057A(10).

## Found this session (each verified by probe)

1. The ObjectStatus mask bit is **58**, not 26: retail's status filter sits at
   esp+0x6C (vptr 0x010956D4), m_next +0x70, mustSet +0x74..+0x7F, and the
   0x04000000 store lands at +0x78 = dword 1. The wrong bit was the cause of
   the "zero kept in EBP" regalloc symptom: 551 -> 210 diffs, EBP vanished.
2. PartitionFilterAcceptByKindOf ctor (ILT 0x382FD -> 0xC3DD0) is called
   (KINDOFMASK_NONE, mask(kInit,2)): retail pushes &mask first.
3. Scale constant is VA 0x01075338 (3.0f). A **literal 3.0f** (not the extern
   ?g_bfmeK1266A@@3MB) is needed so each product is `fmul [K]` instead of a
   hoisted x87 register (same lesson as WaterRenderObjGenerateVertexBuffer.cpp).
4. bfmeForwardWideC takes Int range (*(int *)&radius), as the ledger's HHHHH.
5. A `Coord3D delta` local (x,y = center - owner, z = 0; then x,y *= 3.0f)
   reproduces retail's frame (0xB8) and the dead 12-byte slot at esp+0x00.

## Best candidates

- Stash (attempts bank, k6): delta + in-place `Coord3D &dest = position;
  dest.x += delta.x; dest.y += delta.y;` -> 747/756, 177 non-reloc diffs,
  frame and everything up to +0x187 identical; float block differs (no z
  self-copy, spill/fxch order).
- 20261030-002b26c0-k7-dest-slot.cpp.txt (k7): delta + separate
  `Coord3D dest = {position.x + delta.x, position.y + delta.y, position.z}`
  -> instruction shape **0.995**, but dest gets its own 12-byte slot (frame
  +12, 771 B). Retail packs dest into position's slot (the `mov edx,[pos.z]`
  / `mov [dest.z],edx` self-copy at +0x20A/+0x232 is that copy).

## Remaining

Make VC7.1 place `dest` in `position`'s slot (position is dead once dest is
computed). Scalars dx/dy + dest pack dest into the dead mask temp slot instead
(k3, 746 B, 210 diffs); in-place forms drop the z copy. Untested: position in
its own scope ending before dest (needs dest's inputs carried in scalars),
dest declared before position, different temp lifetime of the mask.

Inert this session: next() spellings, two-statement dtor, for(;;) loop,
default NULL arg, m_next init forms, ZH-style set(), dest = position copy.
Compiler: bank's cl line (/DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc + ZH includes, STLport).
model=claude-opus-5-5 t=55min
