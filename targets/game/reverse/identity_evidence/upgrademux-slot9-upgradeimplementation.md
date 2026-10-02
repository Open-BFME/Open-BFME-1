# UpgradeMux slot 9 is upgradeImplementation: every concrete table

Family note for the `<Class>::upgradeImplementation` renames. All facts were
read from `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`
(image base 0x00400000) with pefile and capstone; owners come from
`targets/game/reverse/module_registry.tsv` (`tools/module_registry.py`), which
reads ModuleFactory::init's string-literal registrations, not the ledger.

## Which tables are UpgradeMux tables

A table is in the family when its slot 2 is the ILT stub VA 0x0040204F
(-> 0x002D9D00 `UpgradeMux::wouldUpgrade`) or its slot 3 is 0x0041C071
(-> 0x002D9DF0 `UpgradeMux::resetUpgrade`). A scan of `.rdata` for those two
dwords finds 36 tables. Two (0x010A36E0, UpgradeModule's own, and 0x010CE518)
have `_purecall` (0x0088C500) in slot 9; one (0x010CD848) is stored only by an
unregistered constructor (0x002D7770) and is left alone here.

## Why slot 9 is upgradeImplementation

Slot 1 of every table is the shared body 0x002D9AD0, BFME's
`UpgradeMux::attemptUpgrade`. It reads, in full:

    0x002D9ADC  call [eax+0x08]     ; wouldUpgrade(keyMask)  (slot 2)
    0x002D9AE1  je   -> return false
    0x002D9AE7  call [edx+0x2C]     ; slot 11
    0x002D9AEE  call [eax+0x34]     ; slot 13
    0x002D9AF5  call [edx+0x24]     ; slot 9
    0x002D9AFE  call [eax+0x20] (1) ; slot 8, argument true
    0x002D9B01  mov al,1 ; ret 4

Zero Hour's `UpgradeMux::attemptUpgrade` (`GeneralsMD/Code/GameEngine/Source/
GameLogic/Object/Upgrade/UpgradeModule.cpp:116`) is `if (wouldUpgrade(keyMask))
{ giveSelfUpgrade(); return true; } return false;`, and `giveSelfUpgrade`
(line 164) is `performUpgradeFX(); processUpgradeRemoval();
upgradeImplementation(); setUpgradeExecuted(true);`. The retail body inlines
exactly that sequence, so slot 11 = performUpgradeFX, slot 13 =
processUpgradeRemoval, **slot 9 = upgradeImplementation**, slot 8 =
setUpgradeExecuted. Two independent checks agree:

- slot 13's shared body 0x001F8950 calls
  `UpgradeMuxData::muxDataProcessUpgradeRemoval` (0x002D9C40) through ILT
  0x0002E320, which is ZH's `UpgradeModule::processUpgradeRemoval`;
- `targets/game/reverse/ea_evidence.csv` carries EA's WorldBuilder labels
  `CastleUpgrade::upgradeImplementation` at 0x002D3F90 and
  `GeometryUpgrade::upgradeImplementation` at 0x002D5980, both slot-9 bodies
  in the table below.

In the UpgradeModule base table 0x010A36E0, slot 9 is `_purecall`, as ZH's
`virtual void upgradeImplementation() = 0` requires. Every ZH override is a
`protected:` virtual taking no arguments (`virtual void upgradeImplementation();`
in ArmorUpgrade.h, AutoHealBehavior.h, FireWeaponWhenDamagedBehavior.h, ...),
so each mangles `?upgradeImplementation@<Class>@@MAEXXZ`. Every slot-9 body
below ends in a plain `ret` (no stack arguments).

Slot 7 is a second, BFME-only pure virtual (`_purecall` in 0x010A36E0) that
`attemptUpgrade` does not call. Where both are visible, slot 7 undoes what slot
9 does (ArmorUpgrade 0x002D2D20 vs 0x002D2C20, ModelConditionUpgrade 0x002D6930
vs 0x002D6840, ObjectCreationUpgrade 0x002D71D0 vs 0x002D6E60), so the three
ledger rows that named slot-7 bodies `upgradeImplementation` are wrong.

## The tables

Owner = the module whose registered constructor (module_registry.tsv
`constructor_rva`, reached from the name literal through newModuleInstance)
stores the table. "refs" counts the slot-9 stub's VA in the whole image; 1
means the stub appears in this one table only, so the body is introduced by
this class and not shared or inherited.

| Owner (registry) | name literal / newModuleInstance | ctor | store | table VA | slot-9 ILT (refs) | body | ledger name before this series |
|---|---|---|---|---|---|---|---|
| AutoHealBehavior | 0x00C90DC4 / 0x00114200 | 0x001ee950 | 0x001ee9e3 `mov dword ptr [edi], 0x10a1c20` | 0x010a1c20 | 0x0000524f (1) | 0x001ee8d0 | `?invoke@Rva001EE8D0@@QAEXXZ` |
| DynamicPortalBehaviour | 0x00C90B3C / 0x001156B0 | 0x001f8b80 | 0x001f8bba `mov dword ptr [esi + 0x10], 0x10a3868` | 0x010a3868 | 0x0002f4b4 (1) | 0x001f9c60 | `?d_001f9c60@@YAXXZ` |
| FireWeaponWhenDamagedBehavior | 0x00C909A4 / 0x00116F30 | 0x001fb5d0 | 0x001fb64b `mov dword ptr [edi], 0x10a3de8` | 0x010a3de8 | 0x0000e98a (1) | 0x001fb550 | `?invoke@Rva001FB550@@QAEXXZ` |
| FireWeaponWhenDeadBehavior | 0x00C90984 / 0x00116FC0 | 0x001fbc70 | 0x001fbcfb `mov dword ptr [edi], 0x10a3f40` | 0x010a3f40 | 0x000455ed (1) | 0x001fbeb0 | `?m@Gen_001fbeb0@@QAEXXZ` |
| ReplenishUnitsBehavior | 0x00C908EC / 0x001173A0 | 0x002044e0 | 0x00204570 `mov dword ptr [edi], 0x10a5ac0` | 0x010a5ac0 | 0x0001a730 (1) | 0x00204430 | `?invoke@Rva00204430@@QAEXXZ` |
| SpawnBehavior | 0x00C90BE4 / 0x00115590 | 0x0020ae30 | 0x0020aedf `mov dword ptr [edi], 0x10a6b70` | 0x010a6b70 | 0x00009af7 (1) | 0x0020a800 | `?d_0020a800@@YAXXZ` |
| DetachableRiderBody | 0x00C8FB0C / 0x0011FA50 | 0x00212ec0 | 0x00212f1d `mov dword ptr [esi], 0x10a7fc0` | 0x010a7fc0 | 0x0002e9dd (1) | 0x00212d10 | `?m@Gen_00212d10@@QAEXXZ` |
| AttributeModifierAuraUpdate | 0x00C90278 / 0x0011A8D0 | 0x002800d0 | 0x00280161 `mov dword ptr [edi], 0x10bad08` | 0x010bad08 | 0x0001b734 (1) | 0x002802d0 | `?invoke@Rva002802D0@@QAEXXZ` |
| BroadcastStealthUpdate | 0x00C907B8 / 0x0011B370 | 0x00289880 | 0x00289904 `mov dword ptr [edi], 0x10bcaf0` | 0x010bcaf0 | 0x00031101 (1) | 0x00289830 | `?invoke@Rva00289830@@QAEXXZ` |
| ArmorUpgrade | 0x00C8FFF4 / 0x0011D090 | 0x002d2ab0 | 0x002d2ad4 `mov dword ptr [esi + 0x10], 0x10cba40` | 0x010cba40 | 0x0001366a (1) | 0x002d2c20 | `?d_002d2c20@@YAXXZ` |
| AttributeModifierUpgrade | 0x00C8FE64 / 0x0011DE20 | 0x002d2eb0 | 0x002d2ed4 `mov dword ptr [esi + 0x10], 0x10cbbc0` | 0x010cbbc0 | 0x00026413 (1) | 0x002d2fd0 | `?bfmeGoTCB@BfmeThingTCB@@QAEXXZ` |
| AudioLoopUpgrade | 0x00C8FE04 / 0x0011E0B0 | 0x002d32b0 | 0x002d3345 `mov dword ptr [edi], 0x10cbd08` | 0x010cbd08 | 0x0004617d (1) | 0x002d33e0 | `?bfmeUpdateERR@BfmeHostERR@@QAEXXZ` |
| BaseUpgrade | 0x00C8FFE4 / 0x0011D110 | 0x002d3800 | 0x002d3824 `mov dword ptr [esi + 0x10], 0x10cbfd8` | 0x010cbfd8 | 0x00044fcb (1) | 0x002d3970 | `?upgradeImplementation@BaseUpgrade@@MAEXXZ` |
| CastleUpgrade | 0x00C8FE54 / 0x0011DEA0 | 0x002d3e30 | 0x002d3e54 `mov dword ptr [esi + 0x10], 0x10cc1b0` | 0x010cc1b0 | 0x00005588 (1) | 0x002d3f90 | `?upgradeImplementation@CastleUpgrade@@MAEXXZ` |
| CommandSetUpgrade | 0x00C8FFCC / 0x0011D220 | 0x002d41a0 | 0x002d41c4 `mov dword ptr [esi + 0x10], 0x10cc330` | 0x010cc330 | 0x00017ae9 (1) | 0x002d4310 | `?bfmeApplyXC@Gen_002D4310@@QAEXXZ` |
| CostModifierUpgrade | 0x00C90004 / 0x0011D9D0 | 0x002d4570 | 0x002d459b `mov dword ptr [esi + 0x10], 0x10cc498` | 0x010cc498 | 0x00036944 (1) | 0x002d49e0 | `?upgradeImplementation@CostModifierUpgrade@@MAEXXZ` |
| DelayedUpgrade | 0x00C8FFB8 / 0x0011D2A0 | 0x002d4d20 | 0x002d4d44 `mov dword ptr [esi + 0x10], 0x10cc700` | 0x010cc700 | 0x0002f44b (1) | 0x002d4e90 | `?upgradeImplementation@DelayedUpgrade@@MAEXXZ` |
| ExperienceScalarUpgrade | 0x00C8FEB4 / 0x0011DAF0 | 0x002d4fd0 | 0x002d4ff4 `mov dword ptr [esi + 0x10], 0x10cc890` | 0x010cc890 | 0x0000c59f (1) | 0x002d5100 | `?add@Rva002D5100@@QAEXXZ` |
| GarrisonUpgrade | 0x00C8FE2C / 0x0011D950 | 0x002d5280 | 0x002d52a4 `mov dword ptr [esi + 0x10], 0x10cca40` | 0x010cca40 | 0x00009a3e (1) | 0x002d53f0 | `?dispatch@Rva002D53F0@@QAEXXZ` |
| GeometryUpgrade | 0x00C8FE40 / 0x0011DF20 | 0x002d5790 | 0x002d57d1 `mov dword ptr [esi + 0x10], 0x10ccc48` | 0x010ccc48 | 0x0002a784 (1) | 0x002d5980 | `?d_002d5980@@YAXXZ` |
| LevelUpUpgrade | 0x00C8FFA4 / 0x0011D320 | 0x002d5f10 | 0x002d5f34 `mov dword ptr [esi + 0x10], 0x10cce50` | 0x010cce50 | 0x00030c9c (1) | 0x002d6050 | `?bfmeAdjustZD@BfmeOwnerZD@@QAEXXZ` |
| LocomotorSetUpgrade | 0x00C8FF38 / 0x0011D3A0 | 0x002d6160 | 0x002d6184 `mov dword ptr [esi + 0x10], 0x10ccfa8` | 0x010ccfa8 | 0x0000744b (1) | 0x002d6290 | `?bfmeGo1034C@BfmeC1034@@QAEXXZ` |
| MaxHealthUpgrade | 0x00C8FEA0 / 0x0011DC00 | 0x002d63a0 | 0x002d63c4 `mov dword ptr [esi + 0x10], 0x10cd158` | 0x010cd158 | 0x0000f155 (1) | 0x002d64d0 | `?forwardValue@Rva002D64D0Owner@@QAEXXZ` |
| ModelConditionUpgrade | 0x00C8FE84 / 0x0011DD10 | 0x002d66d0 | 0x002d66f4 `mov dword ptr [esi + 0x10], 0x10cd378` | 0x010cd378 | 0x0001131a (1) | 0x002d6840 | `?applyFlagPair@Rva002D6840FlagPairUpgrade@@QAEXXZ` |
| ObjectCreationUpgrade | 0x00C8FF1C / 0x0011D420 | 0x002d6d90 | 0x002d6de5 `mov dword ptr [edi], 0x10cd620` | 0x010cd620 | 0x0001e4f7 (1) | 0x002d6e60 | `?bfmeSleepIS@BfmeUpdIS@@QAEXXZ` |
| RadarUpgrade | 0x00C8FF50 / 0x0011D540 | 0x002d7aa0 | 0x002d7ac4 `mov dword ptr [esi + 0x10], 0x10cda50` | 0x010cda50 | 0x0001297c (1) | 0x002d7bd0 | `?upgradeImplementation@RadarUpgrade@@MAEXXZ` |
| StatusBitsUpgrade | 0x00C8FF8C / 0x0011D5C0 | 0x002d7dd0 | 0x002d7df4 `mov dword ptr [esi + 0x10], 0x10cdc00` | 0x010cdc00 | 0x000034d6 (1) | 0x002d7f00 | `?bfmeOneSLA@BfmeThingSLA@@QAEXXZ` |
| StealthUpgrade | 0x00C8FF60 / 0x0011D6C0 | 0x002d8000 | 0x002d8024 `mov dword ptr [esi + 0x10], 0x10cdd58` | 0x010cdd58 | 0x0000e304 (1) | 0x002d8170 | `?setStatus18@Rva002D81StatusOwner@@QAEXXZ` |
| SubObjectsUpgrade | 0x00C8FF74 / 0x0011D640 | 0x002d83a0 | 0x002d83c4 `mov dword ptr [esi + 0x10], 0x10cdeb0` | 0x010cdeb0 | 0x00031700 (1) | 0x002d8d90 | `?d_002d8d90@@YAXXZ` |
| TooltipUpgrade | 0x00C8FE18 / 0x0011E030 | 0x002d93e0 | 0x002d9404 `mov dword ptr [esi + 0x10], 0x10ce1a0` | 0x010ce1a0 | 0x0002dbf0 (1) | 0x002d9510 | `?applyAndDirty@Rva002D9510Owner@@QAEXXZ` |
| UnpauseSpecialPowerUpgrade | 0x00C8FEFC / 0x0011D740 | 0x002d9760 | 0x002d9784 `mov dword ptr [esi + 0x10], 0x10ce350` | 0x010ce350 | 0x000437b6 (1) | 0x002d9890 | `?process@Rva002D9890@@QAEXXZ` |
| WeaponBonusUpgrade | 0x00C8FEE4 / 0x0011D850 | 0x002da320 | 0x002da344 `mov dword ptr [esi + 0x10], 0x10ce5b8` | 0x010ce5b8 | 0x0000301c (1) | 0x002da450 | `?setNestedFlag@Rva002DA450@@QAEXXZ` |
| WeaponSetUpgrade | 0x00C8FED0 / 0x0011D8D0 | 0x002da4e0 | 0x002da504 `mov dword ptr [esi + 0x10], 0x10ce710` | 0x010ce710 | 0x000397a2 (1) | 0x002da610 | `?bfmeGoTFA@BfmeThingTFA@@QAEXXZ` |

For the `[edi]` / `[esi]` stores, the constructor first does
`lea edi,[esi+0x20]` (AutoHealBehavior, AudioLoopUpgrade, and the other
multiply-inherited behaviours) or `lea esi,[edi+0xE0]` (DetachableRiderBody):
the table is stored at that UpgradeMux subobject. ObjectCreationUpgrade
(0x002D6D90) stores 0x010CD620 at `[edi]` with edi = this, its primary table:
its UpgradeMux base comes first.

## Conclusion

Each body in the table is `<Owner>::upgradeImplementation`, mangled
`?upgradeImplementation@<Owner>@@MAEXXZ`, entered with ECX at the owner's
UpgradeMux subobject (offsets inside it are relative to that subobject).
