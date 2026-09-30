# ContestableContain object-data const find at 0x0021B110

`dup_21b110` claimed the 71-byte body at 0x0021B110 as an alias of Image.cpp's
`map<UnsignedInt, Image *>` tree find. That instantiation already has its own
matched body at 0x005D2780, and retail was linked without identical-COMDAT
folding, so one mangled name owns one body: 0x0021B110 is a different
instantiation whose bytes happen to coincide.

The body sits beside 0x0021B0B0, the mutable
`_Rb_tree<Object *, pair<Object * const, ContestableMapEntry>, ...>::find`
that `ContestableContain::updateObject` (0x0021BAF0) reaches through ILT
0x00047848. Both are 71 bytes and byte-identical, as a mutable/const pair of
the same pointer-key tree find must be.

Its caller fixes the map. 0x0021BA10 is ContestableContain's
ContainModuleInterface slot 0xC8 (secondary vtable 0x010AB140, ILT
0x0003C277); with `this` at the +0x20 interface it passes `this+0x9A4`, which
is ContestableContain+0x9C4 `m_objectData`, to ILT 0x0000F22C -> 0x0021B110
twice, and reads the mapped `ContestableMapEntry::m_object` at node+0x14. A
const member lookup on `m_objectData` emits exactly the `QBE ... _Const_traits`
find, the one instantiation of this map distinct from 0x0021B0B0. Compiled in
ContestableContain.cpp, it matches all 71 bytes of 0x0021B110, and the caller
matches all 170 bytes of 0x0021BA10 with both REL32 calls resolving to
ILT 0x0000F22C.
