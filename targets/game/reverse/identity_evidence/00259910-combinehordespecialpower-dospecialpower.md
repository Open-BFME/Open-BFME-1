# CombineHordeSpecialPower::doSpecialPower at 0x00259910 (identity only)

The 440-byte body at 0x00259910 is still the generated dump
`?d_00259910@@YAXXZ`. Earlier sessions said it had "no class-specific vtable,
only generic PartitionFilter vtables". Those are the tables of the filter
objects it builds on its stack. The body itself sits in CombineHordeSpecialPower's
own SpecialPowerModuleInterface table. This note records the identity for
whoever converts it. No ledger row changes.

## Facts from retail 1.03 (`lotrbfme.exe`, image base 0x400000)

- ILT 0x0003EE9B jumps to 0x00259910. Its VA 0x0043EE9B appears once in data:
  at 0x010B3D84, slot 11 (+0x2C) of the table at VA 0x010B3D58.
- Only CombineHordeSpecialPower's special members store 0x010B3D58, at +0x10:
  `??0CombineHordeSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z` (0x002596F0, at
  0x00259714) and `??1CombineHordeSpecialPower@@MAE@XZ` (0x00259740, at
  0x00259750). The class is named independently of this body:
  `getModuleNameKey@CombineHordeSpecialPower` (0x002597D0) has string-verified
  literals, and the literal getter 0x00259730 returns "CombineHordeSpecialPower".
- 0x010B3D58 is a SpecialPowerModuleInterface table. Its slots 2 and 5-8 are
  SpecialPowerModule's `getPercentReady`, `getPowerName`,
  `getSpecialPowerTemplate`, `getRequiredScience` and `onSpecialPowerCreation`,
  and slot 14 is `doSpecialPowerUsingWaypoints`.
- Slot 11 of the same interface in other special powers:
  - `?doSpecialPower@SpecialPowerModuleInterface@@QAEXI@Z` 0x0026A550 (base body;
    inherited by CashHackSpecialPower, DefectorSpecialPower and the base table
    0x010B7B00)
  - `?doSpecialPower@PlayerUpgradeSpecialPower@@UAEXI@Z` 0x00264100 (table
    0x010B6558 slot 11)
  - `?doSpecialPower@ProductionSpeedBonus@@UAEXI@Z` 0x002645D0 (table 0x010B67C0
    slot 11)
  - `?doSpecialPower@Object@@...` (0x001C3790) calls the module through slot +0x2C.

  This matches Zero Hour's SpecialPowerModuleInterface order, with BFME's extra
  slot 3: isModuleForPower, isReady, getPercentReady, (3), getReadyFrame,
  getPowerName, getSpecialPowerTemplate, getRequiredScience,
  onSpecialPowerCreation, setReadyFrame, pauseCountdown, **doSpecialPower**,
  doSpecialPowerAtObject, doSpecialPowerAtLocation, doSpecialPowerUsingWaypoints.
- The body ends `ret 4` (0x00259AC5). That is one stack argument, ZH's
  `UnsignedInt commandOptions`.

## Conclusion

0x00259910 is `CombineHordeSpecialPower::doSpecialPower(UnsignedInt)`,
mangled `?doSpecialPower@CombineHordeSpecialPower@@UAEXI@Z` like the
PlayerUpgradeSpecialPower and ProductionSpeedBonus rows. It is entered with ECX
at the +0x10 interface subobject. The PartitionFilter tables
(0x01085DD0/0x010B243C/0x01083B80/0x0109688C) inside it belong to the
stack-built filter chain it uses to find horde members to combine; they say
nothing about the owner.

## Wider observation

Several other slot-11 bodies in special-power tables still carry
address-derived names: 0x00259250 (table 0x010B3B68), 0x00259E60
(0x010B3F80), 0x0025A930 (0x010B4608, DevastateSpecialPower), 0x0025B920
(0x010B4A60), 0x0025D870 (0x010B4FB8), 0x00262570, 0x00265A00, 0x0026B230,
0x0026B3C0, 0x0026B820 (0x010B83E0, TaintSpecialPower). Each is
`<Class>::doSpecialPower` once its table's constructor is independently named.
