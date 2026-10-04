# 0x0090F2E0 unreferenced indexed dword load

Retail body (11 bytes): `8b 44 24 04 / 8b 44 81 14 / c2 04 00`, a this-call that loads `[this + arg*4 + 0x14]`.

- A scan of every E8/E9 relative call and every absolute reference in lotrbfme.exe finds no reference to 0x0090F2E0 and no ILT jump to it.
- No vtable slot or matched caller names it. Its only former emitter was the Zero Hour copy of `getCanAttackObject` in ActionManager.cpp, which inlined `Object::getWeaponInWeaponSlotCommandSourceMask`.
- The Zero Hour name `WeaponTemplateSet::getNthCommandSourceMask` therefore rests on byte shape alone. The row now carries the address-derived `Rva0090F2E0IndexedMasks::get`.
