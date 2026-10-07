# 0x00610930 is not _Construct<Money>

The gen-alias row `?dup_00610930@@YAXXZ` (19 bytes) borrowed MoneyVectorPushBack.cpp's
`??$_Construct@VMoney@@V1@@_STL@@YAXPAVMoney@@ABV1@@Z`. Since f4b01f3dc5's twin rule
it failed: its one call (+0xD) goes through ILT 0x00018ACA to 0x0060FB70, the
matched `??0BfmeNodeAS@@QAE@PBUBfmeSpecAS@@@Z` (BfmeOneHundredSeventyOne.cpp), not
to Money's copy constructor (candidates 0x0002FF18 / 0x000E1540 / 0x00013476).

- Bytes: `mov ecx,[esp+4]; test ecx,ecx; je +0Ah; mov eax,[esp+8]; push eax;
  call 0x00018ACA; ret` -- STLport's null-checked placement construct.
  Boundary: the next row, `?Rva00610AC0Create@@...`, is past INT3 padding;
  0x00610920 (one-byte no-op) precedes it.
- The callee is a 16-byte linked-node constructor (owner +0, next/prev +4/+8,
  extra +0xC) taking one pointer/reference argument.

The element type is not recovered (BfmeNodeAS is the callee row's placeholder), so
the body is landed as the address-derived `Rva00610930Construct` in
game/GameEngine/Source/Common/Rva00610930PlacementConstruct.cpp.
