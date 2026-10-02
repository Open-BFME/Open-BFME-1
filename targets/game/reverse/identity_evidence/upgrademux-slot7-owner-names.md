# UpgradeMux slot 7: owner-proven, address-named bodies

Slot 7 of every UpgradeMux table is a BFME-only pure virtual (`_purecall` in
UpgradeModule's table 0x010A36E0). UpgradeMux::attemptUpgrade (0x002D9AD0) never
calls it. Where a class has a real body there, it undoes that class's slot-9
upgradeImplementation (see `upgrademux-slot9-upgradeimplementation.md`). No Zero
Hour twin, EA WorldBuilder label or in-exe name table names it, so these bodies
take `<Owner>::rva<address>` (protected virtual, no arguments, plain `ret`).
The owner of each comes from its table: the slot-7 ILT stub's VA appears once
in the image, in the UpgradeMux table that the class's registered constructor
(`module_registry.tsv`) stores.

The 8-byte bodies are `mov eax,[ecx]; push 0; call [eax+0x20]; ret`: slot 8 with
false. attemptUpgrade calls slot 8 last with true, where Zero Hour's giveSelfUpgrade
calls setUpgradeExecuted(true). So these say "upgrade no longer executed",
the inverse of SpawnBehavior's slot-9 body (slot 8 with true). The 1-byte bodies
are empty overrides (`ret`).

| Owner (registry) | registered ctor | table | slot-7 ILT | body | size | ledger name before |
|---|---|---|---|---|---|---|
| FireWeaponWhenDamagedBehavior | 0x001FB5D0 | 0x010A3DE8 | 0x0003F049 | 0x001FB260 | 8 | `?d_001fb260@@YAXXZ` |
| FireWeaponWhenDeadBehavior | 0x001FBC70 | 0x010A3F40 | 0x0000A7A4 | 0x001FBB80 | 8 | `?d_001fbb80@@YAXXZ` |
| ReplenishUnitsBehavior | 0x002044E0 | 0x010A5AC0 | 0x0000F245 | 0x002043E0 | 8 | `?d_002043e0@@YAXXZ` |
| SpawnBehavior | 0x0020AE30 | 0x010A6B70 | 0x0000CD8D | 0x0020A810 | 8 | `?d_0020a810@@YAXXZ` |
| DetachableRiderBody | 0x00212EC0 | 0x010A7FC0 | 0x0001C71A | 0x00212D20 | 1 | `?Rva00212D20Noop@@YAXXZ` |
| AttributeModifierAuraUpdate | 0x002800D0 | 0x010BAD08 | 0x00033703 | 0x0027FFA0 | 8 | `?d_0027ffa0@@YAXXZ` |
| BroadcastStealthUpdate | 0x00289880 | 0x010BCAF0 | 0x00020AC7 | 0x002899F0 | 8 | `?d_002899f0@@YAXXZ` |
| CastleUpgrade | 0x002D3E30 | 0x010CC1B0 | 0x0003AECC | 0x002D3DD0 | 1 | `?b_002d3dd0@@YAXXZ` |
| DelayedUpgrade | 0x002D4D20 | 0x010CC700 | 0x00025BA3 | 0x002D4CF0 | 1 | `?b_002d4cf0@@YAXXZ` |
| LevelUpUpgrade | 0x002D5F10 | 0x010CCE50 | 0x000319FD | 0x002D5F70 | 1 | `?method@Rva002D5F70@@QAEXXZ` |
| RadarUpgrade | 0x002D7AA0 | 0x010CDA50 | 0x0003B200 | 0x002D7A50 | 8 | `?d_002d7a50@@YAXXZ` |
| SubObjectsUpgrade | 0x002D83A0 | 0x010CDEB0 | 0x00047EBF | 0x002D8220 | 1 | `?Rva002D8220Noop@@YAXXZ` |
| WeaponBonusUpgrade | 0x002DA320 | 0x010CE5B8 | 0x00011E73 | 0x002DA300 | 1 | `?empty@Rva002DA300Empty@@QAEXXZ` |

## Non-trivial slot-7 bodies (second batch)

| Owner (registry) | registered ctor | table | slot-7 ILT | body | size | ledger name before | what it undoes |
|---|---|---|---|---|---|---|---|
| ExperienceScalarUpgrade | 0x002D4FD0 | 0x010CC890 | 0x0000AC04 | 0x002D5120 | 26 | `?sub@Rva002D5120@@QAEXXZ` | subtracts the +0x70 scalar that slot 9 (0x002D5100) adds |
| MaxHealthUpgrade | 0x002D63A0 | 0x010CD158 | 0x0000AD44 | 0x002D6510 | 46 | `?update@Rva002D6510@@QAEXXZ` | max-health change of slot 9 (0x002D64D0), reversed |
| DynamicPortalBehaviour | 0x001F8B80 | 0x010A3868 | 0x00025A09 | 0x001F8DD0 | 62 | `?bfmeCloseZJ@BfmeOwnerZJ@@QAEXXZ` | slot 8 with false, then module teardown |
| TooltipUpgrade | 0x002D93E0 | 0x010CE1A0 | 0x00036750 | 0x002D9570 | 69 | `?bfmeGoUYA@BfmeThingUYA@@QAEXXZ` | clears the two strings slot 9 (0x002D9510) applies, then slot 8 with false |
| GeometryUpgrade | 0x002D5790 | 0x010CCC48 | 0x00028B69 | 0x002D55F0 | 269 | `?bfmeTeardown002D55F0@Rva002D55F0Owner@@QAEXXZ` | tears down what slot 9 (0x002D5980) sets up |
| AutoHealBehavior | 0x001EE950 | 0x010A1C20 | 0x00049C60 | 0x001EE810 | 15 | `?reset@Rva001EE810@@QAEXXZ` | clears the +0xC field and calls slot 8 with false |
| WeaponSetUpgrade | 0x002DA4E0 | 0x010CE710 | 0x0001FD48 | 0x002DA630 | 32 | `?bfmeGoTEB@BfmeThingTEB@@QAEXXZ` | calls a different Object callee than slot 9 (0x002DA610) with the same constant 3, then slot 8 with false |
| AttributeModifierUpgrade | 0x002D2EB0 | 0x010CBBC0 | 0x0001C698 | 0x002D3000 | 45 | `?bfmeGo1040F@BfmeF1040@@QAEXXZ` | passes the +0x70 module-data field to a different Object callee than slot 9 (0x002D2FD0) does, then slot 8 with false |
| AudioLoopUpgrade | 0x002D32B0 | 0x010CBD08 | 0x000417E0 | 0x002D34B0 | 48 | `?bfmeGo1024C@BfmeC1024@@QAEXXZ` | kills the audio handle slot 9 (0x002D33E0) starts |
