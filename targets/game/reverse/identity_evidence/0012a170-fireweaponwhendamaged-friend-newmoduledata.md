# FireWeaponWhenDamagedBehavior::friend_newModuleData at 0x0012A170

The 54-byte body at RVA 0x0012A170 (ret at +0x35) is a module-data factory:

- It allocates 0x9C bytes with `operator new`.
- It constructs them through ILT 0x00012233, which jumps to the matched
  `FireWeaponWhenDamagedBehaviorModuleData::FireWeaponWhenDamagedBehaviorModuleData`
  at 0x0012A100.
- When the INI argument is non-null, it calls `INI::initFromINIMultiProc` with
  ILT 0x0002969A. That ILT jumps to
  `FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse` at 0x00123180,
  whose table holds Zero Hour's FireWeaponWhenDamaged keys
  (identity_evidence/00123180-fireweaponwhendamaged-buildfieldparse.md).

A factory that builds a module's data and registers that data's own field-parse
builder is that module's `friend_newModuleData`
(MAKE_STANDARD_MODULE_MACRO, Common/Module.h). The row kept the address-derived
name `Rva0012A170ModuleFactory::create`. The FireWeaponWhenDamaged name sat on
0x00117420, which is ReplenishUnits' factory
(identity_evidence/00117420-replenishunits-friend-newmoduledata.md).
