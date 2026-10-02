# 0x002D4D80 is DelayedUpgrade::isSubObjectsUpgrade

The 3-byte body at RVA 0x002D4D80 (`32 C0 C3`, `xor al,al; ret`, followed by
`CC` padding) was claimed as the address placeholder `?Rva002D4D80False@@YA_NXZ`
because no caller or vtable slot had been tied to it. A vtable slot under an
independently named owner now identifies it. All facts below were read from
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe` (image base
0x00400000) with pefile and capstone.

## The only route to the body is one vtable slot

- Retail has no direct `call`/`jmp` to VA 0x006D4D80 except the ILT stub at RVA
  0x0003FBE8 (`E9` -> 0x006D4D80; ledger row `?j_0003fbe8@@YAXXZ`), and no
  absolute pointer to 0x006D4D80.
- The image has exactly one dword equal to the stub's VA 0x0043FBE8: VA
  0x010CC710, slot 4 (+0x10) of the vtable that starts at VA 0x010CC700 (the
  8 bytes before it are zero).

## The vtable belongs to DelayedUpgrade

`??0DelayedUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z` (RVA 0x002D4D20, 53 B,
matched) calls the UpgradeModule constructor and then stores its four vtables:

    0x006D4D34  mov dword ptr [esi],       0x010CC814   ; ??_7DelayedUpgrade@@6B@
    0x006D4D3A  mov dword ptr [esi+0x0C],  0x010CC750
    0x006D4D41  mov dword ptr [esi+0x10],  0x010CC700   ; this table
    0x006D4D48  mov dword ptr [esi+0x18],  0x010CC6EC

The table at 0x010CC700 is the one stored at the UpgradeMux subobject (+0x10),
i.e. DelayedUpgrade's UpgradeModuleInterface vtable. Its slots, followed
through their ILT stubs:

| Slot | Body | Ledger name |
|---|---|---|
| 0 | 0x002D9AB0 | (generated) |
| 1 | 0x002D9AD0 | (placeholder) |
| 2 | 0x002D9D00 | `UpgradeMux::wouldUpgrade` |
| 3 | 0x002D9DF0 | `UpgradeMux::resetUpgrade` |
| 4 | **0x002D4D80** | this body |
| 5 | 0x002D9AC0 | (placeholder) |
| 6 | 0x001EE7C0 | |
| 7 | 0x002D4CF0 | (placeholder) |
| 9 | 0x002D4E90 | `DelayedUpgrade::upgradeImplementation` |
| 10 | 0x001F8920 | `UpgradeModule::getUpgradeActivationMasks` |
| 11 | 0x001F8930 | `UpgradeModule::performUpgradeFX` |

## SubObjectsUpgrade's twin table names slot 4

`??0SubObjectsUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z` (RVA 0x002D83A0) stores
VA 0x010CDEB0 at `[esi+0x10]` in the same position. That table equals
DelayedUpgrade's in slots 0-3, 5, 6, 8, 10, 11 and 12 (same ILT stubs). Its slot 4
is stub 0x00429997 -> RVA 0x002D8410 (`B0 01 C3`, return true), the matched row
`?isSubObjectsUpgrade@SubObjectsUpgrade@@MAE_NXZ`.

## Zero Hour order agrees

`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h`
declares `UpgradeModuleInterface` as isAlreadyUpgraded, attemptUpgrade,
wouldUpgrade, resetUpgrade, **isSubObjectsUpgrade**, forceRefreshUpgrade,
testUpgradeConditions. Slots 2 and 3 carry the BFME names wouldUpgrade and
resetUpgrade, so slot 4 is isSubObjectsUpgrade. In Zero Hour each concrete
upgrade module defines its own inline override (e.g.
`SubObjectsUpgrade.h:88` returns true; `RadarUpgrade.h:77`,
`StatusBitsUpgrade.h:98`, `WeaponBonusUpgrade.h:82` return false), which is why
DelayedUpgrade has a body of its own at 0x002D4D80 rather than sharing one.

## Conclusion

0x002D4D80 is DelayedUpgrade's override of `isSubObjectsUpgrade`, a protected
virtual returning false, mangled like SubObjectsUpgrade's:
`?isSubObjectsUpgrade@DelayedUpgrade@@MAE_NXZ`. The body is unchanged
(3 bytes); only the name and source TU change.
