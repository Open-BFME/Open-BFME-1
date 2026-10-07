# 0x002DF500 is not W3DModelDraw::setTerrainDecalSize

The gen-alias row `?dup_002df500@@YAXXZ` (15 bytes) borrowed
`?setTerrainDecalSize@W3DModelDraw@@UAEXMM@Z` (`if (m_shadow) m_shadow->setSize(x, y)`).
Since f4b01f3dc5's twin rule it failed: its tail jump (+0x7) goes through ILT
0x00040412 to 0x001D6860, the matched `?bfmeTellHF@BfmeThingHF@@QAEXPAX0@Z`
(walks a pointer range calling virtual slot 4 with both arguments), not to
Shadow::setSize (candidates 0x0002133C / 0x001E4250 / 0x001D5EE7 / 0x002DAD67).

- Bytes: `mov ecx,[ecx+58h]; test ecx,ecx; je +5; jmp 0x00040412; ret 8`.
  Boundary: the next row, `?Rva002DF520@@YAXPAVINI@@PAX@Z`, starts at 0x002DF520
  after INT3 padding.
- Neighbours are anonymous GameLogic/INI bodies (0x002DF4C0, 0x002DF4E0 tests,
  0x002DF520 INI parse callback), not W3DModelDraw code.

The owner is not recovered, so the body is landed as the address-derived
`Rva002DF500Owner::rva002DF500(void *, void *)` in
game/GameEngine/Source/Common/Rva002DF500ListenerForward.cpp.
