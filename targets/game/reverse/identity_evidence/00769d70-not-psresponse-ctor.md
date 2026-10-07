# 0x00769D70 is not PSResponse's constructor

The gen-alias row `?dup_00769d70@@YAXXZ` (15 bytes) borrowed PopupPlayerInfo.cpp's
`??0PSResponse@@QAE@XZ`, which constructs a PSPlayerStats at +4. Since f4b01f3dc5's
twin rule it failed: retail's one call goes through ILT 0x0004048A (target
FUN_008d4f40) to 0x004D4F40, the matched STLport
`??0?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ`, not to a
PSPlayerStats constructor (0x00658EF0).

- Bytes: `push esi; mov esi,ecx; lea ecx,[esi+4]; call 0x0004048A; mov eax,esi;
  pop esi; ret` -- a __thiscall constructor whose only work is a std::string
  member at +4. Boundary: the next row, `?bfmeGoCFA@BfmeThingCFA@@QAEXXZ`, starts
  at 0x00769D90 after INT3 padding.
- Neighbours are ModelConditionInfo / W3DModelDraw bodies (0x00769D00 set<int>
  erase wrapper, 0x00769DD0 ModelConditionInfo preloadAssets), not GameSpy code.

The owning type is not recovered, so the body is re-homed as the address-derived
`Rva00769D70Record::Rva00769D70Record()` in
game/GameEngine/Source/GameClient/Rva00769D70StringRecordCtor.cpp.
