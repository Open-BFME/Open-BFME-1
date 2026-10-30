# 0x0037B0D0 Config0037B9F0::copyString0037B0D0 (32 B)

Facts from BFME 1 retail:
- 0x0037B0D0..0x0037B0EF: thiscall, hidden return slot at [esp+4]; copies
  `this+0x3C` through StringBase<char>'s copy constructor 0x00887B60, zeroes
  the EH-state word, returns the slot (RET 4).
- Reached only through ILT 0x00041BF0, from 0x0037BA38 and 0x0037BA89
  (matched `Rva0037C310Owner::update0037B9F0`, which already spells
  `?copyString0037B0D0@Config0037B9F0@@QAE?AVAsciiString@@XZ`, pinned at
  0x0037B0D0 by 0037B9F0-finish-callee-visibility.md) and from 0x0037C770 /
  0x0037C7BC inside the unconverted 0x0037C600 body.

The previous row `?dup_0037b0d0@@YAXXZ` was a gen-alias to a byte-equal
TerrainRoadType::getBridgeModelNameDamaged copy emitted by TerrainRoads.cpp
(that name also aliases 0x006015F0); it named no identity for this address.
Nothing defined the caller's spelling (link queue #64, census 1d5131d3f1).
The address-derived name is kept; the owning class is unproven.
