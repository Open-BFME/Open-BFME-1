# 0x00121FA0 is the pool getter of UpgradeSoundSelectorClientBehavior, not Upgrade

Resolves the blocked audit in `00121fa0-upgrade-pool-owner-mismatch.md`
(the String-ref red on `?getClassMemoryPool@Upgrade@@...` in Player.cpp).

## Body

`tools/dis_retail.py 0x00121FA0 104`: the standard find-pool getter. Operand
+0x31 pushes VA `0x0108AD58` = "UpgradeSoundSelectorClientBehavior"; one call
through ILT `0x0003ADD7`; pool static VA `0x012EF1BC`, guard VA `0x012EF1C0`.

## Owner (independent of the string)

- ILT `0x000473FC` is `jmp 0x00521FA0`. It is slot 4 (+0x10) of vtable
  `0x0108AD18` (`??_7UpgradeSoundSelectorClientBehavior@@6BClientUpdateModule@@@`,
  per `tools/vtable_lookup.py 0x0108AD18`), whose ctor at `0x00121F60`
  (46 B) installs exactly that vtable. The getter sits at ctor+0x40, the same
  layout as the WeaponModeSpecialPowerUpdate / SpecialAbilityUpdate getters
  (identity_evidence/20261003-pool-getter-identities.md).
- Slot 4 is the module vtable's pool-getter slot, agreeing with the bound name.

## Repair

Row re-homed to `module_pool_glue_bulk.cpp` with a TU-scoped
`UpgradeSoundSelectorClientBehavior` declaration carrying the pool glue; pool
statics `0x012EF1BC/0x012EF1C0` and the 0x00C01240 EH funclet parent renamed.
Player.cpp still compiles its own (now unclaimed) Upgrade getter from
Common/Upgrade.h, as Weapon.cpp does.
