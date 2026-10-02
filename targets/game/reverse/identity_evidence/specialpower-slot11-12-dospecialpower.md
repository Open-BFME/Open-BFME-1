# SpecialPowerModuleInterface slots 11 and 12: doSpecialPower / doSpecialPowerAtObject

Family note for the `<Class>::doSpecialPower` and
`<Class>::doSpecialPowerAtObject` renames. All facts were read from
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe` (image base
0x00400000) with pefile and capstone. Owners come from
`targets/game/reverse/module_registry.tsv` (`tools/module_registry.py`), which
reads ModuleFactory::init's string-literal registrations, not the ledger.

## Which tables

A table is in the family when slot 5, 6 or 7 holds the ILT stub of
SpecialPowerModule's `getPowerName` (0x00268A60), `getSpecialPowerTemplate`
(0x002687C0) or `getRequiredScience` (0x00268A30). All 21 such tables carry all
three. Each is stored at the SpecialPowerModuleInterface subobject (+0x10 in
the concrete powers) by exactly one registered constructor. Apart from that
constructor, only the same class's destructor (where it has one) references
the table.

## Why slot 11 is doSpecialPower and slot 12 is doSpecialPowerAtObject

BFME's `Object::doSpecialPower` (0x001C3790) matches Zero Hour's
(`Object.cpp:5339`): return if disabled (`[esi+0x1A4]`), check
`TheSpecialPowerStore->canUseSpecialPower` unless forced, then
`getSpecialPowerModule(template)` (ILT 0x000401BF), then
`call [edx+0x2C]` with one argument, commandOptions. Slot 11 (+0x2C) is
`doSpecialPower(UnsignedInt)`.

`Object::doSpecialPowerAtObject` (0x001C37F0) has the same prologue and calls
`[edx+0x30]` with (obj, commandOptions). Slot 12 (+0x30) is
`doSpecialPowerAtObject(Object *, UnsignedInt)`.

Every slot-11 body ends `ret 4` and every slot-12 body ends `ret 8`. Zero
Hour declares both `public:` virtuals in SpecialPowerModule and its
subclasses, so they mangle `?doSpecialPower@<C>@@UAEXI@Z` and
`?doSpecialPowerAtObject@<C>@@UAEXPAVObject@@I@Z`. The matched rows
`PlayerUpgradeSpecialPower::doSpecialPower` (0x00264100),
`ProductionSpeedBonus::doSpecialPower` (0x002645D0),
`CashHackSpecialPower::doSpecialPowerAtObject` (0x00258800) and
`DefectorSpecialPower::doSpecialPowerAtObject` (0x0025A0E0) already sit in
these slots.

A stub with refs > 1 is the base SpecialPowerModule body inherited by classes
that do not override it (0x0026A550 slot 11, 0x0026A5B0 slot 12). A stub with
refs = 1 is that class's own override.

## The tables

| Owner (registry) | literal / newModuleInstance | ctor | store (mov) | table VA | slot 11 ILT (refs) -> body | slot 12 ILT (refs) -> body |
|---|---|---|---|---|---|---|
| CashHackSpecialPower | 0x00C8FA90 / 0x0011FD70 | 0x00258250 | 0x00258271 `[+0x10]` | 0x010b3888 | 0x00041bcd (3) -> 0x0026a550 | 0x00048699 (1) -> 0x00258800 |
| CloudBreakSpecialPower | 0x00C8F9AC / 0x001205F0 | 0x00259010 | 0x00259031 `[+0x10]` | 0x010b3b68 | 0x0001374b (1) -> 0x00259250 | 0x00007752 (1) -> 0x00259210 |
| CombineHordeSpecialPower | 0x00C8F7F8 / 0x00121840 | 0x002596f0 | 0x00259711 `[+0x10]` | 0x010b3d58 | 0x0003ee9b (1) -> 0x00259910 | 0x00015ee7 (1) -> 0x00259770 |
| DarknessSpecialPower | 0x00C8F958 / 0x00120920 | 0x00259b80 | 0x00259ba1 `[+0x10]` | 0x010b3f80 | 0x0000bc7b (1) -> 0x00259e60 | 0x0004b3a3 (1) -> 0x00259e20 |
| DefectorSpecialPower | 0x00C8FA74 / 0x0011FE80 | 0x00259f50 | 0x00259f71 `[+0x10]` | 0x010b4180 | 0x00041bcd (3) -> 0x0026a550 | 0x00038023 (1) -> 0x0025a0e0 |
| DevastateSpecialPower | 0x00C8F84C / 0x00121510 | 0x0025a7c0 | 0x0025a7e1 `[+0x10]` | 0x010b4608 | 0x0000e0d4 (1) -> 0x0025a930 | 0x00019191 (1) -> 0x0025a910 |
| ElvenWoodSpecialPower | 0x00C8FA0C / 0x001202C0 | 0x0025b2b0 | 0x0025b2d1 `[+0x10]` | 0x010b4a60 | 0x00030a26 (1) -> 0x0025b920 | 0x00008242 (1) -> 0x0025b8e0 |
| FreezingRainSpecialPower | 0x00C8F974 / 0x00120810 | 0x0025d590 | 0x0025d5b1 `[+0x10]` | 0x010b4fb8 | 0x000343ce (1) -> 0x0025d870 | 0x0001a622 (1) -> 0x0025d830 |
| GrabPassengerSpecialPower | 0x00C83C20 / 0x00120A30 | 0x0025f0e0 | 0x0025f101 `[+0x10]` | 0x010b56d8 | 0x00006195 (1) -> 0x0025f2d0 | 0x0001c459 (1) -> 0x0025f6c0 |
| ManTheWallsSpecialPower | 0x00C8F8A4 / 0x001211E0 | 0x00260600 | 0x00260621 `[+0x10]` | 0x010b5d30 | 0x000197ea (1) -> 0x00262570 | 0x00047a78 (5) -> 0x0026a5b0 |
| OCLSpecialPower | 0x00C8FA28 / 0x001201B0 | 0x002628e0 | 0x00262901 `[+0x10]` | 0x010b6010 | 0x0000b00a (1) -> 0x00262da0 | 0x0001caee (1) -> 0x00262d60 |
| PlayerHealSpecialPower | 0x00C8F868 / 0x00121400 | 0x002639d0 | 0x002639f1 `[+0x10]` | 0x010b6390 | 0x0000af88 (1) -> 0x00263a40 | 0x000145b0 (1) -> 0x00263b80 |
| PlayerUpgradeSpecialPower | 0x00C8F884 / 0x001212F0 | 0x00263f50 | 0x00263f71 `[+0x10]` | 0x010b6558 | 0x0001c45e (1) -> 0x00264100 | 0x0001f3ca (1) -> 0x00263fd0 |
| ProductionSpeedBonus | 0x00C8FA3C / 0x001200A0 | 0x00264450 | 0x00264471 `[+0x10]` | 0x010b67c0 | 0x0001a56e (1) -> 0x002645d0 | 0x00047a78 (5) -> 0x0026a5b0 |
| RepairSpecialPower | 0x00C8F818 / 0x00121730 | 0x002647f0 | 0x00264811 `[+0x10]` | 0x010b69a0 | 0x00009bdd (1) -> 0x00264870 | 0x0003a814 (1) -> 0x002649f0 |
| ScavengerSpecialPower | 0x00C8F9C8 / 0x001204E0 | 0x002658b0 | 0x002658d1 `[+0x10]` | 0x010b6e88 | 0x00046e61 (1) -> 0x00265a00 | 0x00047a78 (5) -> 0x0026a5b0 |
| SpecialPowerModule | 0x00C8FAAC / 0x00119540 | 0x002693e0 | 0x00269432 `[+0x0]` | 0x010b7b00 | 0x00041bcd (3) -> 0x0026a550 | 0x00047a78 (5) -> 0x0026a5b0 |
| SplitHordeSpecialPower | 0x00C8F830 / 0x00121620 | 0x0026b030 | 0x0026b051 `[+0x10]` | 0x010b7f78 | 0x0003f850 (1) -> 0x0026b230 | 0x0001d97b (1) -> 0x0026b0b0 |
| StopSpecialPower | 0x00C8F8EC / 0x00120E80 | 0x0026b340 | 0x0026b361 `[+0x10]` | 0x010b8180 | 0x00035413 (1) -> 0x0026b3c0 | 0x00047a78 (5) -> 0x0026a5b0 |
| TaintSpecialPower | 0x00C8F994 / 0x00120700 | 0x0026b650 | 0x0026b671 `[+0x10]` | 0x010b83e0 | 0x00001aeb (1) -> 0x0026b820 | 0x000316f1 (1) -> 0x0026b7e0 |
| WeaponChangeSpecialPowerModule | 0x00C8F9E4 / 0x001203D0 | 0x0026cc80 | 0x0026cca1 `[+0x10]` | 0x010b8a50 | 0x00045c8c (1) -> 0x0026cf90 | 0x0002a1a8 (1) -> 0x0026cd20 |

## Open question (not used for naming here)

`Object::doSpecialPowerAtLocation` (0x001C38B0) calls slot 14 (+0x38) with
three arguments (loc, angle, commandOptions). The ledger names slot 13
0x0026A620 `doSpecialPowerAtLocation(const Coord3D *, UnsignedInt)` and slot 14
0x0026A690 `doSpecialPowerUsingWaypoints`. The slot-11 bodies of
OCLSpecialPower and its look-alikes call slot 13 with (position,
commandOptions), where Zero Hour calls doSpecialPowerAtLocation(position,
INVALID_ANGLE, commandOptions). Slots 13 and 14 need their own proof. Nothing
in this series renames them.
