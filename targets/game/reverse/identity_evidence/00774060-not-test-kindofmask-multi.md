# 0x00774060 is not TEST_KINDOFMASK_MULTI

The gen-alias row `?dup_00774060@@YAXXZ` claimed Player.obj's inline
`TEST_KINDOFMASK_MULTI(m, set, clear)` COMDAT (`return m.testSetAndClear(set, clear)`)
as retail 0x00774060. Since f4b01f3dc5's gen-alias rule (a masked call is admitted
only to a retail twin of the named callee) the row fails in Player.cpp's gate, and
the bytes refute the identity:

- 0x00774060 (20 bytes): `mov eax,[esp+0Ch]; mov ecx,[esp+8]; push eax; push ecx;
  mov ecx,[esp+0Ch]; call 0x0003A8D7; ret` -- a __cdecl free function passing its
  2nd/3rd arguments to a __thiscall member of its 1st. Boundary: the next row,
  `?invoke@Rva00774080FieldPairForwarder@@QAEXXZ`, starts at 0x00774080.
- ILT 0x0003A8D7 (`?j_0003a8d7@@YAXXZ`, target=FUN_00b710f0) jumps to 0x007710F0
  (`?d_007710f0@@YAXXZ`, 970 bytes, ends `ret 8`). That body sets up an EH frame,
  keeps `this` in EBP, tests the first byte of its first argument, indexes 20-byte
  records at this+0x134/+0x138, reads TheGameLODManager (0x012ED5AC) +0x16C4 and
  dereferences AsciiString data (+8, empty literal 0x0107388B). It is not
  BitFlags<116>::testSetAndClear (pins 0x00019BCD/0x000E9FD6/0x00132B2D/0x00132B44,
  none of which is 0x0003A8D7).
- 0x00774060 sits among W3DModelDraw / ModelConditionInfo bodies
  (0x007730A0 parseWeaponBoneName ... 0x00774B60 ModelConditionInfo::clear),
  not in Player's code.

So the body is re-homed as the address-derived `Rva00774060` forwarder in
game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00774060Forwarder.cpp,
calling `Rva007710F0Owner::method`, pinned at ILT 0x0003A8D7 (which jumps to the
0x007710F0 gen dump).
