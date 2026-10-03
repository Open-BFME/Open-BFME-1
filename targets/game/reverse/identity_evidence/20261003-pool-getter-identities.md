# 0x002B2B30 and 0x002A6520 are pool getters of WeaponModeSpecialPowerUpdate and SpecialAbilityUpdate

Resolves the two pool-getter rows blocked in
`20261003-reference-prefix-audit.md`. Their ledger names (`Weapon`,
`SpecialAbility`) were shim-class guesses that only matched while the string
check was a prefix test.

## Bodies

`tools/dis_retail.py 0x002B2B30 104` and `0x002A6520 104`: the standard
find-pool getter (guard byte, `push <pool name>`, one call through ILT
`0x0003ADD7` -> `0x0008FFC0`, store to a static pool pointer). Operand +49
binds `0x1090424` = "WeaponModeSpecialPowerUpdate" and `0x109025c` =
"SpecialAbilityUpdate". Statics: pool `0x012F0230` / guard `0x012F0234`, and
pool `0x012F0050` / guard `0x012F0054`.

## Owner (independent of the string)

- The only call to `0x002B2B30` is ILT `0x0003ADDC`; the only pointer to that
  ILT is the file/RVA `0x00CC54EC` word. The vtable symbol
  `??_7WeaponModeSpecialPowerUpdate@@6BWeaponModeSpecialPowerUpdateBase@@@`
  is at `0x010C54DC`, so VA `0x010C54EC` is its slot 4 (the module vtable's
  `getObjectMemoryPool`). The getter sits 0xA0 bytes before that class's
  ctor at `0x002B2BD0`.
- The only call to `0x002A6520` is ILT `0x00025261`; pointers to that ILT are
  RVA `0x00CC37C8` (vtable `0x010C37B8` slot 4, the
  `SpecialAbilityUpdate@@6BUpdateModule@@@` vtable) and the code word at
  `0x00046A6B`. The getter sits after the `SpecialAbilityUpdate` ctor
  (`0x002A6360`, 356 B).

Both slots agree with the pool name each body binds. Weapon and SpecialAbility
(the ZH shim classes) have no getter in retail at all: nothing else reaches a
find-pool body named "Weapon" or "SpecialAbility" at these slots.

## Repair

`module_pool_glue_bulk.cpp` now emits `SpecialAbilityUpdate`'s pool glue from
the ZH header's `MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( SpecialAbilityUpdate,
"SpecialAbilityUpdate" )` and carries a TU-scoped `WeaponModeSpecialPowerUpdate`
declaration with the same macro. The `Weapon` row is retired by the
re-homing; `Weapon.cpp` still compiles its own unclaimed getter from the
shim header. The static pool symbols at `0x012F0230` and `0x012F0050` are
renamed to the real classes.
