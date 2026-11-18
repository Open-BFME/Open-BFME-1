# 0x000F8520 TunnelTracker::getContainMax

Previously `?rva000F8520Get@@YAHXZ` (address-derived free function,
Rva000F8520Get.cpp). Now `?getContainMax@TunnelTracker@@QBEHXZ` in
game/GameEngine/Source/Common/RTS/TunnelTracker_getContainMax.cpp.

BFME 1 target evidence:
- Body (12 B): `mov eax,[TheWritableGlobalData 0x012ED5C8]; mov eax,[eax+0xB60];
  ret`. It ignores ecx, so a const thiscall member and a cdecl free
  function give the same bytes.
- ILT 0x000456E2 -> 0x000F8520 has exactly two retail users, both tail jumps:
  - 0x002198D0 (25 B): `mov eax,[ecx+0xBC]; mov ecx,[TheCaveSystem];
    push eax; call ILT 0x2F52C (CaveSystem::getTunnelTrackerForCaveIndex
    0x00378340); mov ecx,eax; jmp ILT 0x456E2`. That is Zero Hour's
    CaveContain::getContainMax,
    `TheCaveSystem->getTunnelTrackerForCaveIndex(m_caveIndex)->getContainMax()`,
    so ecx at the jump is a TunnelTracker.
  - 0x0022F2C0 (19 B): the object's controlling player (ILT 0x20824,
    Object::getControllingPlayer), a tracker pointer from player+0x22C, then the
    same tail jump: TunnelContain's getContainMax shape.
- Placement: 0x000F8520 opens the TunnelTracker code block (0x000F85C0 to
  0x000F9170: healObject, getContainCount, removeFromContain, ctor,
  iterateContained, ...).
- The only byte-identical retail body: a scan of .text for
  `A1 xx xx xx xx 8B 80 60 0B 00 00 C3` finds 0x000F8520 alone.

Zero Hour reference: GeneralsMD/Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp:105
`Int TunnelTracker::getContainMax() const { return TheGlobalData->m_maxTunnelCapacity; }`.
BFME's GlobalData puts the field at +0xB60. TunnelTracker_getContainCount.cpp's
matched inline view already reads the same offset.

Link-queue row #63 (census 6c4dd9e650): TunnelTracker_getContainCount.cpp's
copy was a duplicate of TunnelTracker.cpp's non-retail Zero Hour copy (offset
0x7D4), which is now under #if 0.
