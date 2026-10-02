# UpgradeMux slot 4 is isSubObjectsUpgrade: the per-class false overrides

Family note for the `<Class>::isSubObjectsUpgrade` renames. Facts were read from
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe` (image base
0x00400000) with pefile and capstone. Owners come from
`targets/game/reverse/module_registry.tsv` (string-literal registrations).

## Slot meaning

Zero Hour declares `UpgradeModuleInterface` as isAlreadyUpgraded,
attemptUpgrade, wouldUpgrade, resetUpgrade, **isSubObjectsUpgrade**,
forceRefreshUpgrade, testUpgradeConditions
(`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h`). The BFME
tables match that order where it can be checked:
- slot 1 is the shared body 0x002D9AD0, ZH's attemptUpgrade/giveSelfUpgrade
  sequence (see `upgrademux-slot9-upgradeimplementation.md`);
- slots 2 and 3 are the matched `UpgradeMux::wouldUpgrade` (0x002D9D00) and
  `UpgradeMux::resetUpgrade` (0x002D9DF0) bodies; that is what defines the family;
- in slot 4, SubObjectsUpgrade's table 0x010CDEB0 alone holds a `B0 01 C3`
  (return true) body, `SubObjectsUpgrade::isSubObjectsUpgrade` 0x002D8410. Zero Hour's
  SubObjectsUpgrade.h is the only header whose override returns TRUE; the other ZH
  overrides (ArmorUpgrade.h, AutoHealBehavior.h, RadarUpgrade.h, ...) return FALSE.
  DelayedUpgrade's slot 4 (0x002D4D80) was named the same way in 4c4dba6803.

Every ZH override is `protected: virtual Bool isSubObjectsUpgrade()`, so the
name is `?isSubObjectsUpgrade@<Class>@@MAE_NXZ`. Every body below is `32 C0 C3`
(return false), and its slot-4 ILT stub's VA appears exactly once in the image, in
the table that the class's registered constructor stores. The body is therefore
that class's own override, not an inherited one. (0x001F8370, the slot-4 body of
UpgradeModule's own table and of seven non-overriding classes, is not renamed here.)

| Owner (registry) | ctor | table | slot-4 ILT | body | ledger name before |
|---|---|---|---|---|---|
| AutoHealBehavior | 0x001ee950 | 0x010a1c20 | 0x00025964 | 0x001ee800 | `?value@Rva001EE800False@@QBE_NXZ` |
| FireWeaponWhenDamagedBehavior | 0x001fb5d0 | 0x010a3de8 | 0x00013584 | 0x001fb250 | `?value@Rva001FB250@@QBE_NXZ` |
| FireWeaponWhenDeadBehavior | 0x001fbc70 | 0x010a3f40 | 0x00035fa3 | 0x001fbec0 | `?get@Rva001FBEC0False@@QBE_NXZ` |
| ReplenishUnitsBehavior | 0x002044e0 | 0x010a5ac0 | 0x00042712 | 0x002043d0 | `?invoke@Rva002043D0@@QBE_NXZ` |
| SpawnBehavior | 0x0020ae30 | 0x010a6b70 | 0x000492bf | 0x0020b0e0 | `?invoke@Rva0020B0E0@@QBE_NXZ` |
| DetachableRiderBody | 0x00212ec0 | 0x010a7fc0 | 0x00011aae | 0x00212d90 | `?invoke@Rva00212D90@@QBE_NXZ` |
| AttributeModifierAuraUpdate | 0x002800d0 | 0x010bad08 | 0x00024a0a | 0x0027ffb0 | `?getByte@Rva0027FFB0@@QBEEXZ` |
| BroadcastStealthUpdate | 0x00289880 | 0x010bcaf0 | 0x000416e1 | 0x00289a00 | `?Rva00289A00False@@YA_NXZ` |
| ArmorUpgrade | 0x002d2ab0 | 0x010cba40 | 0x000341b7 | 0x002d2b10 | `?method@Rva002D2B10@@QBE_NXZ` |
| BaseUpgrade | 0x002d3800 | 0x010cbfd8 | 0x0003b561 | 0x002d3860 | `?method@Rva002D3860@@QBE_NXZ` |
| CommandSetUpgrade | 0x002d41a0 | 0x010cc330 | 0x00042e74 | 0x002d4200 | `?method@Rva002D4200@@QBE_NXZ` |
| CostModifierUpgrade | 0x002d4570 | 0x010cc498 | 0x00008c24 | 0x002d4600 | `?m@Gen_002d4600@@QAE_NXZ` |
| ExperienceScalarUpgrade | 0x002d4fd0 | 0x010cc890 | 0x00026954 | 0x002d5030 | `?method@Rva002D5030@@QBE_NXZ` |
| GarrisonUpgrade | 0x002d5280 | 0x010cca40 | 0x0004a520 | 0x002d52e0 | `?method@Rva002D52E0@@QBE_NXZ` |
| LevelUpUpgrade | 0x002d5f10 | 0x010cce50 | 0x00035a58 | 0x002d5f80 | `?method@Rva002D5F80@@QBE_NXZ` |
| LocomotorSetUpgrade | 0x002d6160 | 0x010ccfa8 | 0x0003d0fa | 0x002d61c0 | `?method@Rva002D61C0@@QBE_NXZ` |
| MaxHealthUpgrade | 0x002d63a0 | 0x010cd158 | 0x0004424c | 0x002d6400 | `?method@Rva002D6400@@QBE_NXZ` |
| ModelConditionUpgrade | 0x002d66d0 | 0x010cd378 | 0x00015528 | 0x002d6730 | `?m@Gen_002d6730@@QAE_NXZ` |
| ObjectCreationUpgrade | 0x002d6d90 | 0x010cd620 | 0x0001721a | 0x002d6be0 | `?method@Rva002D6BE0@@QBE_NXZ` |
| RadarUpgrade | 0x002d7aa0 | 0x010cda50 | 0x0004ac64 | 0x002d7b00 | `?method@Rva002D7B00@@QBE_NXZ` |
| StatusBitsUpgrade | 0x002d7dd0 | 0x010cdc00 | 0x0002dd76 | 0x002d7e30 | `?value@Rva002D7E30@@QBE_NXZ` |
| StealthUpgrade | 0x002d8000 | 0x010cdd58 | 0x0001effb | 0x002d8060 | `?value@Rva002D8060@@QBE_NXZ` |
| TooltipUpgrade | 0x002d93e0 | 0x010ce1a0 | 0x00027caf | 0x002d9440 | `?value@Rva002D9440@@QBE_NXZ` |
| UnpauseSpecialPowerUpgrade | 0x002d9760 | 0x010ce350 | 0x0001aa55 | 0x002d97c0 | `?value@Rva002D97C0@@QBE_NXZ` |
| WeaponBonusUpgrade | 0x002da320 | 0x010ce5b8 | 0x00049ec2 | 0x002da380 | `?value@Rva002DA380@@QBE_NXZ` |
| WeaponSetUpgrade | 0x002da4e0 | 0x010ce710 | 0x0001d84a | 0x002da540 | `?value@Rva002DA540@@QBE_NXZ` |
