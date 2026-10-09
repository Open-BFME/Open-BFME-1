# FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse at 0x00123180

The 35-byte body at RVA 0x00123180 (ret at +0x22) adds the table at VA
0x0108B330 at offset 0, then UpgradeMuxData's table at VA 0x010898A0 at offset
8. The first table holds eleven rows and a NULL terminator: StartsActive
(+0x70), ReactionWeaponPristine/Damaged/ReallyDamaged/Rubble (+0x7C..+0x88),
ContinuousWeaponPristine/Damaged/ReallyDamaged/Rubble (+0x8C..+0x98),
DamageTypes (+0x74) and DamageAmount (+0x78). This is Zero Hour's
FireWeaponWhenDamagedBehaviorModuleData key set.

The body's only reference is ILT 0x0002969A. The only reference to that thunk
is the `push 0x0042969A` at RVA 0x0012A197, inside the module-data factory at
0x0012A170. That factory allocates 0x9C bytes, constructs them through ILT
0x00012233, which jumps to the matched
`FireWeaponWhenDamagedBehaviorModuleData` constructor at 0x0012A100, and hands
the thunk to `INI::initFromINIMultiProc`.

So the body is `FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse`.
Four names claimed it: CountermeasuresBehavior and SpyVisionUpdate (Zero Hour
header inlines emitted by ModuleFactory.cpp), FireOCLAfterWeaponCooldownUpdate
and GenerateMinefieldBehavior. They matched only because the table address is
a masked relocation; the last two carried `static` body-guard debt for the
table mismatch. The FireWeaponWhenDamaged name was freed from 0x001298A0, which
is AutoHeal's builder (identity_evidence/001298a0-autoheal-buildfieldparse.md).
