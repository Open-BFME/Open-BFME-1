# UpgradeMux slot 7 is removeUpgrade (EA WorldBuilder labels)

The BFME1 UpgradeMux tables' slot 7 holds a per-class body. Each one is
reached only through an ILT stub whose VA appears once in the image, in the
UpgradeMux table that the class's registered constructor stores
(`upgrademux-slot7-owner-names.md`, `module_registry.tsv`). This note names the
slot. It has no `name=structural` basis: the name comes from EA's own
`__FUNCTION__` strings in the BFME2 and RotWK WorldBuilder builds, which the
existing two-outcome rule accepts.

All addresses are RVAs (image base 0x00400000), read with pefile and capstone.

## The WorldBuilder labels

| Build | label string | referenced in body | table holding body (slot) | table stored by |
|---|---|---|---|---|
| BFME2 `Worldbuilder.exe` | `RadarUpgrade::removeUpgrade` @ 0x01AF70BC | 0x00E39010 (ref at 0x00E39050) | VA 0x01EF6EF8, slot 8 (entry at 0x01AF6F18) | 0x00E38CCF `mov [ecx+0x10], 0x01EF6EF8` in ctor 0x00E38CA0 |
| BFME2 `Worldbuilder.exe` | `WeaponBonusUpgrade::removeUpgrade` @ 0x01AF7E68 | 0x00E3AF70 (ref at 0x00E3AFB0) | VA 0x01EF7C40, slot 8 (entry at 0x01AF7C60) | 0x00E3AD8F `mov [ecx+0x10], 0x01EF7C40` in ctor 0x00E3AD60 |
| RotWK `Worldbuilder.exe` | `RadarUpgrade::removeUpgrade` @ 0x01B51FDC | 0x00E4EEB0 (ref at 0x00E4EEF0) | VA 0x01F51E08, slot 8 (entry at 0x01B51E28) | 0x00E4EB6F `mov [ecx+0x10], 0x01F51E08` in ctor 0x00E4EB40 |
| RotWK `Worldbuilder.exe` | `WeaponBonusUpgrade::removeUpgrade` @ 0x01B52DA4 | 0x00E50E20 (ref at 0x00E50E60) | VA 0x01F52B70, slot 8 (entry at 0x01B52B90) | 0x00E50C3F `mov [ecx+0x10], 0x01F52B70` in ctor 0x00E50C10 |

The WorldBuilder builds call bodies directly, with no ILT. Each body's
address appears once in data, in the listed table. That table is stored at
+0x10 (the UpgradeMux sub-object, as in BFME1) by the constructor shown.
Both bodies are `DEBUG_CRASH`-style reports ("If you are using RadarUpgrade,
please explain why. -MLo", "... WeaponBonusUpgrade ... This should be an
AttributeModifier -MLo", file
`C:\Projects\bfme2\Code\GameEngine\Source\GameLogic\Object\Upgrade\...`).
The label passed to the reporter is the body's own `__FUNCTION__`.

## Slot alignment: WorldBuilder slot 8 = BFME1 slot 7

- WorldBuilder `giveSelfUpgrade` (BFME2 0x007E8120, called from the shared
  attemptUpgrade 0x007E80E0) calls `+0x30`, `+0x3C`, `+0x28`, then
  `+0x24` with 1. That is performUpgradeFX (slot 12), processUpgradeRemoval
  (15), upgradeImplementation (10) and setUpgradeExecuted(true) (9). BFME1's
  attemptUpgrade (0x002D9AD0) makes the same sequence at slots 11, 13, 9 and 8.
- So WorldBuilder slot 9 = BFME1 slot 8 (setUpgradeExecuted) and WorldBuilder
  slot 10 = BFME1 slot 9 (upgradeImplementation). WorldBuilder slot 8, which
  sits directly before setUpgradeExecuted, = BFME1 slot 7. Slots 0-6 are
  laid out the same in both: shared bodies at 0-3, 5 and 6, and the per-class
  isSubObjectsUpgrade at 4. BFME2 inserts one shared virtual at slot 7
  (0x00CABD10 in BFME2, 0x00CBC630 in RotWK).
- The bodies agree. WorldBuilder `RadarUpgrade::removeUpgrade` ends
  `push 0; call [eax+0x24]` (setUpgradeExecuted(false)) after its report.
  BFME1's RadarUpgrade slot 7 (0x002D7A50) is exactly
  `mov eax,[ecx]; push 0; call [eax+0x20]; ret`. WorldBuilder
  `WeaponBonusUpgrade::removeUpgrade` is only the report, and BFME1's
  WeaponBonusUpgrade slot 7 (0x002DA300) is an empty `ret`. Retail compiles
  the debug report out.
- Zero Hour's `processUpgradeRemoval` is BFME1 slot 13 (its body calls
  `UpgradeMuxData::muxDataProcessUpgradeRemoval` 0x002D9C40), not slot 7.
  The earlier guess `upgradeRemovalImplementation` is not EA's name either.

## Access and mangling

Neither WorldBuilder build carries decorated method names, so access is not
visible there. Slot 7 itself is public in the interface. It is called from outside the class family
through the UpgradeModuleInterface pointer: the non-member helper 0x002D9A70
(`Rva002D9A70Invoke`) does `call [eax+0x1C]` (slot 7) and then `push 0; call [edx+0x20]`
(setUpgradeExecuted(false)). BFME1's Object code calls that helper at 0x001C36E3, through ILT
0x0003A2E7, from 0x001C36B0 (`Object::bfmeResetAllUpgrades`, which walks the behaviours'
upgrade interfaces). BFME2 WorldBuilder has the matching helper at RVA 0x007E7AA0
(VA 0x00BE7AA0). It calls its slots 7 (the inserted virtual) and 8 (removeUpgrade), then 9
(setUpgradeExecuted) with false, and the Object function at RVA 0x008D9290 (VA 0x00CD9290, the
counterpart of Object::removeUpgrade) calls it at 0x008D93D4 and 0x008D9450. CommandSetUpgrade's slot 6 body also calls slot 7, at 0x002D43AB.

The overrides are declared `protected: virtual void removeUpgrade()`, mangling
`?removeUpgrade@<Owner>@@MAEXXZ`. That access is inferred from Zero Hour's own pattern for an
interface hook. `isSubObjectsUpgrade` is public in UpgradeModuleInterface (`UpgradeModule.h:60`)
and protected in UpgradeMux (`:137`) and in every ZH override, as the slot-4 rows here are
(`?isSubObjectsUpgrade@<Class>@@MAE_NXZ`). The neighbouring slot 9 overrides
(`?upgradeImplementation@<Class>@@MAEXXZ`) are protected too. This is the same access the rows
already carried. The access letter is inferred, not proven.

## The 32 bodies

The rows and owners are in `upgrademux-slot7-owner-names.md` and
`upgrademux-slot9-upgradeimplementation.md`: ArmorUpgrade 0x002D2D20,
ModelConditionUpgrade 0x002D6930, ObjectCreationUpgrade 0x002D71D0,
CommandSetUpgrade 0x002D4470, CostModifierUpgrade 0x002D4770, GarrisonUpgrade
0x002D54A0, StealthUpgrade 0x002D81B0, UnpauseSpecialPowerUpgrade 0x002D9910,
StatusBitsUpgrade 0x002D7F40, FireWeaponWhenDamagedBehavior 0x001FB260,
FireWeaponWhenDeadBehavior 0x001FBB80, ReplenishUnitsBehavior 0x002043E0,
SpawnBehavior 0x0020A810, DetachableRiderBody 0x00212D20,
AttributeModifierAuraUpdate 0x0027FFA0, BroadcastStealthUpdate 0x002899F0,
CastleUpgrade 0x002D3DD0, DelayedUpgrade 0x002D4CF0, LevelUpUpgrade 0x002D5F70,
RadarUpgrade 0x002D7A50, SubObjectsUpgrade 0x002D8220, WeaponBonusUpgrade
0x002DA300, ExperienceScalarUpgrade 0x002D5120, MaxHealthUpgrade 0x002D6510,
DynamicPortalBehaviour 0x001F8DD0, TooltipUpgrade 0x002D9570, GeometryUpgrade
0x002D55F0, AutoHealBehavior 0x001EE810, WeaponSetUpgrade 0x002DA630,
AttributeModifierUpgrade 0x002D3000, AudioLoopUpgrade 0x002D34B0,
LocomotorSetUpgrade 0x002D62C0.

## Reproducing it

`tools/ea_wbslot.py` re-derives this chain mechanically: label -> body -> table -> constructor
store -> slot. It reads both call sequences from code and maps the slot through the anchors. It
writes route `wbslot`, basis `strong` rows to `ea_evidence.csv`: RadarUpgrade::removeUpgrade
0x002D7A50, WeaponBonusUpgrade::removeUpgrade 0x002DA300 and
WeaponBonusUpgrade::upgradeImplementation 0x002DA450. The same run re-derives the existing
label names CastleUpgrade/GeometryUpgrade::upgradeImplementation (0x002D3F90, 0x002D5980) and
agrees with them, which checks the slot alignment independently. `tools/ea_evidence.py` merges
these rows on every rewrite. `python3 tools/ea_wbslot.py --wb <BFME2 Worldbuilder.exe>
[--wb <RotWK Worldbuilder.exe>] --check` reports stale rows.
