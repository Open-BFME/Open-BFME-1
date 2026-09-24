# 0x0074BD10 cliff texture-class comparison

The int3-delimited retail body is 246 bytes, from 0x0074BD10 through the
`ret 8` at +0xF3. It is a two-int thiscall returning a bool in AL. It has no
direct calls or relocations. Two anonymous callers reach it through ILT
0x000354EA; neither establishes the exporting class or method name. The
source therefore uses `Rva0074BD10Owner::rva0074BD10`, without asserting a
WorldHeightMap method identity.

The body forms an index from origin X/Y at +0x120E0/+0x120E4, stride +0x08
and two coordinates; bounds checks against +0x20. It copies nine dwords of a
cliff-info record from the vector control pointer at +0x80B0 using the index
table at +0x94. It compares the tile index from +0x8C with the copied
record's index at +0x22, both shifted right two, against 40-byte texture-class
records beginning +0x80C0. Matching class membership returns false; a
different class, no class or an out-of-range index returns true. The matched
`WorldHeightMap::getUVForTileIndex` at 0x0074BEB0 independently uses the same
36-byte cliff record, 40-byte texture class and field offsets. The matched
WorldHeightMap destructor and draw-origin setter corroborate the vector and
origin layout. The local source view begins its STLport vector at the three
control pointers, leaving the unreferenced allocator word at +0x80AC in
padding.

The first natural pointer-vector draft was 246 bytes with 25 non-relocation
differences. Using the observed STLport vector view reduced that to 15, all
from a four-byte frame/home difference and initial bool scheduling. Declaring
`sameClass` before the index expression gave a 246/246 exact probe with zero
non-relocation differences and zero relocation slots. The final strict scoped
build and ledger checks are the landing gate; this note does not infer a
semantic owner from byte equality alone.
