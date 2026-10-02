# SubObjectsUpgrade::upgradeImplementation at 0x002D8D90 (identity only)

The 1122-byte body at 0x002D8D90 is still the generated dump
`?d_002d8d90@@YAXXZ`. Earlier sessions blocked it because no caller or
declaration named its owner. Its UpgradeMux table slot names it. This note
records the identity for whoever converts the body. No ledger row changes.

## Facts from retail 1.03 (`lotrbfme.exe`, image base 0x400000)

- ILT 0x00031700 is `E9 8B 76 2A 00`, a jump to 0x002D8D90. Its VA 0x00431700
  appears once in data: at 0x010CDED4, slot 9 (+0x24) of the table at VA
  0x010CDEB0.
- `??0SubObjectsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z` (0x002D83A0) calls
  UpgradeModule's constructor (0x001F8970) and then stores its four tables:
  0x010CDFC4 at +0, 0x010CDF00 at +0x0C, **0x010CDEB0 at +0x10** (at 0x002D83C1,
  `C7 46 10 B0 DE 0C 01`), and 0x010CDE9C at +0x18. Only this constructor
  references 0x010CDEB0.
- The same table's slot 4 is `?isSubObjectsUpgrade@SubObjectsUpgrade@@MAE_NXZ`
  (0x002D8410), and slots 2/3 are `UpgradeMux::wouldUpgrade` / `resetUpgrade`.
  So this is SubObjectsUpgrade's UpgradeMux interface table.
- Slot 9 of the sibling UpgradeMux tables, each stored at +0x10 by its own
  upgrade constructor:

  | table VA | slot 9 ILT | body | ledger name |
  |---|---|---|---|
  | 0x010CBFD8 | 0x00044FCB | 0x002D3970 | `?upgradeImplementation@BaseUpgrade@@MAEXXZ` |
  | 0x010CC1B0 | 0x00005588 | 0x002D3F90 | `?upgradeImplementation@CastleUpgrade@@MAEXXZ` |
  | 0x010CC498 | 0x00036944 | 0x002D49E0 | `?upgradeImplementation@CostModifierUpgrade@@MAEXXZ` |
  | 0x010CC700 | 0x0002F44B | 0x002D4E90 | `?upgradeImplementation@DelayedUpgrade@@MAEXXZ` |
  | 0x010CDA50 | 0x0001297C | 0x002D7BD0 | `?upgradeImplementation@RadarUpgrade@@MAEXXZ` |
  | 0x010CDEB0 | 0x00031700 | 0x002D8D90 | (this body) |

  The base UpgradeModule table 0x010A36E0 has `_purecall` (0x0088C500) in slot
  9, as Zero Hour's `UpgradeMux::upgradeImplementation() = 0` would.
- The body takes no stack arguments (`ret` with no immediate at 0x002D91F1) and
  runs an EH frame (`push -1; push 0x01014D50; fs:[0]`). That fits
  `void upgradeImplementation()`.

## Conclusion

0x002D8D90 is `SubObjectsUpgrade::upgradeImplementation`, mangled
`?upgradeImplementation@SubObjectsUpgrade@@MAEXXZ` like its siblings. The body
is entered with ECX at the +0x10 UpgradeMux subobject, so member offsets inside
it are relative to that subobject.

## Wider observation

Slot 9 of the UpgradeMux tables is a ready naming lane. Of about 25 upgrade
tables, most slot-9 bodies still carry address-derived names
(`Rva002D5100::add`, `Rva002D53F0::dispatch`, `BfmeOwnerZD::bfmeAdjustZD`,
`Rva002D6840FlagPairUpgrade::applyFlagPair`, ...). Each can be named
`<Class>::upgradeImplementation` once its table's constructor is independently
named.
