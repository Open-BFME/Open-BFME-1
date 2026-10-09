# AutoHealBehaviorModuleData::buildFieldParse at 0x001298A0

The 35-byte body at RVA 0x001298A0 (ret at +0x22) adds the table at VA
0x0108EE60 at offset 0, then UpgradeMuxData's table at VA 0x010898A0 at offset
8. The first table holds thirteen rows and a NULL terminator: StartsActive
(+0x70), ButtonTriggered (+0x71), SingleBurst (+0x72), HealingAmount (+0x74),
HealingDelay (+0x78), Radius (+0x80), KindOf (+0x88, through thunk 0x0002032E
to BitFlags<116>::parseFromINI), UnitHealPulseFX (+0xA4), StartHealingDelay
(+0x7C), AffectsWholePlayer (+0x84), HealOnlyIfNotUnderAttack (+0x85),
HealOnlyIfNotInCombat (+0x86) and HealOnlyOthers (+0xA0). These are the Zero
Hour AutoHealBehavior keys plus BFME's additions.

The body's only reference is ILT 0x0003AF21. The only reference to that thunk is
the `push` at RVA 0x00129E68, inside the matched
`AutoHealBehavior::friend_newModuleData` (0x00129E40). That factory constructs
the matched `AutoHealBehaviorModuleData` constructor (0x00129D50, through ILT
0x0001528A) and hands the thunk to `INI::initFromINIMultiProc`.

So the body is `AutoHealBehaviorModuleData::buildFieldParse`. The old name,
`FireWeaponWhenDamagedBehaviorModuleData::buildFieldParse`, came from
ModuleFactory.cpp's Zero Hour header inline and matched only because the table
address is a masked relocation. FireWeaponWhenDamaged's real builder is
0x00123180: the factory at 0x0012A170 constructs a
FireWeaponWhenDamagedBehaviorModuleData (0x0012A100) and pushes that body's ILT
0x0002969A, and its table at 0x0108B330 holds StartsActive, the four
ReactionWeapon and four ContinuousWeapon keys, DamageTypes and DamageAmount.
