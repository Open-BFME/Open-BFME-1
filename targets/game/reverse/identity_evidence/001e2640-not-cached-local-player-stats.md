# 0x001E2640 is not GameSpyInfo::getCachedLocalPlayerStats

The gen-alias row `?dup_001e2640@@YAXXZ` (35 bytes) borrowed PeerDefs.cpp's
`?getCachedLocalPlayerStats@GameSpyInfo@@UAE?AVPSPlayerStats@@XZ`, which returns a
PSPlayerStats copied from this+0x80. Since f4b01f3dc5's twin rule it failed:
retail's one call (+0x18) goes directly to 0x00887B60, the out-of-line
`StringBase<char>` (AsciiString) copy constructor, not to a PSPlayerStats copy
constructor (0x006577D0).

- Bytes: `push ecx; push esi; mov esi,[esp+0Ch]; add ecx,80h; push ecx;
  mov ecx,esi; mov dword [esp+8],0; call 0x00887B60; mov eax,esi; pop esi;
  pop ecx; ret 4` -- a __thiscall by-value AsciiString return of the member at
  +0x80. Boundary: the next row, `?bfmeRangeBase@WeaponTemplate@@...`, starts at
  0x001E2670 after INT3 padding.
- Neighbours are WeaponTemplate / WeaponStore bodies (0x001E2670, 0x001E2730,
  0x001E27D0), not GameSpy code.

The owner is not recovered, so the body is re-homed as the address-derived
`Rva001E2640Owner::rva001E2640() const` in
game/GameEngine/Source/GameLogic/Object/Rva001E2640AsciiStringGetter.cpp.
