# ReplenishUnitsBehavior::friend_newModuleData at 0x00117420

The 110-byte body at RVA 0x00117420 (ret at +0x6D) is a module-data factory:

- It allocates 0x90 bytes with `operator new`.
- It constructs them through ILT 0x0003025B, which jumps to the matched
  `ReplenishUnitsBehaviorModuleData::ReplenishUnitsBehaviorModuleData` at
  0x00204ED0.
- When the INI argument is non-null, it calls `INI::initFromINIMultiProc` with
  ILT 0x0002B1F7. That ILT jumps to
  `ReplenishUnitsBehaviorModuleData::buildFieldParse` at 0x00204F30, whose table
  holds the seven Replenish keys (identity_evidence/00204f30-replenishunits-buildfieldparse.md).

The factory directly follows the matched
`ReplenishUnitsBehavior::friend_newModuleInstance` at 0x001173A0, the way the
other modules' friend_newModuleInstance/friend_newModuleData pairs sit in
retail.

The row was `FireWeaponWhenDamagedBehavior::friend_newModuleData`, ModuleFactory.cpp's
Zero Hour MAKE_STANDARD_MODULE_MACRO emission. It matched only because the
constructor and builder calls go through thunks whose names the byte check
masks. FireWeaponWhenDamaged's own factory is 0x0012A170: it allocates 0x9C
bytes, constructs FireWeaponWhenDamagedBehaviorModuleData (0x0012A100) and
pushes the ILT of 0x00123180.
