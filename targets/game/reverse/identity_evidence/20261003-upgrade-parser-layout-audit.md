# Early parser-table layout and binding contradictions

Severity: WRONG. These are direct table-operand checks against the unpacked
retail PE, with all five table windows independently confirmed through Ghidra
memory. Existing function bytes still match; masked DIR32 sites do not prove
the data they reference. No identities or shared layouts are changed here.

Applicable rules: docs/matching.md, Relocations, requires checking referenced
contents; AGENTS.md requires one identity per body and forbids guessed names.
The shorter shared Zero Hour schema must be repaired with its dependents.
Changing individual numeric offsets while retaining the wrong layout would
not repair the type or the table.

## Table VA 0x10898a0

Anchor: `?buildFieldParse@ActiveShroudUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z`, RVA `0x00124670`, operand `+0x8`.

| Key | Source offset | Retail offset | Retail callback VA |
|---|---:|---:|---:|
| TriggeredBy | 0xc | 0x30 | 0xc542b0 |
| ConflictsWith | 0x18 | 0x3c | 0xc542b0 |
| RemovesUpgrades | 0x24 | 0x48 | 0xc542b0 |
| FXListUpgrade | 0x30 | 0x54 | 0x404b47 |
| RequiresAllTriggers | 0x54 | 0x58 | 0xc52e00 |
| CustomAnimAndDuration | absent | 0x5c | 0x445ef3 |

The next 16-byte record is all zero.

## Table VA 0x108d6dc

Anchor: `?buildFieldParse@ActiveShroudUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z`, RVA `0x00124670`, operand `+0x16`.

| Key | Source offset | Retail offset | Retail callback VA |
|---|---:|---:|---:|
| DelayTime | absent | 0x70 | 0x4324de |

Source-only keys: NewShroudRange.

The next 16-byte record is all zero.

## Table VA 0x108b330

Anchor: `?buildFieldParse@FireOCLAfterWeaponCooldownUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z`, RVA `0x00123180`, operand `+0x8`.

| Key | Source offset | Retail offset | Retail callback VA |
|---|---:|---:|---:|
| StartsActive | absent | 0x70 | 0xc52e00 |
| ReactionWeaponPristine | absent | 0x7c | 0x40cbdf |
| ReactionWeaponDamaged | absent | 0x80 | 0x40cbdf |
| ReactionWeaponReallyDamaged | absent | 0x84 | 0x40cbdf |
| ReactionWeaponRubble | absent | 0x88 | 0x40cbdf |
| ContinuousWeaponPristine | absent | 0x8c | 0x40cbdf |
| ContinuousWeaponDamaged | absent | 0x90 | 0x40cbdf |
| ContinuousWeaponReallyDamaged | absent | 0x94 | 0x40cbdf |
| ContinuousWeaponRubble | absent | 0x98 | 0x40cbdf |
| DamageTypes | absent | 0x74 | 0x41096f |
| DamageAmount | absent | 0x78 | 0xc52b20 |

Source-only keys: WeaponSlot, OCL, MinShotsToCreateOCL, OCLLifetimePerSecond, OCLLifetimeMaxCap.

The next 16-byte record is all zero.

## Table VA 0x10cd10c

Anchor: `?buildFieldParse@MaxHealthUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z`, RVA `0x002D6370`, operand `+0x16`.

| Key | Source offset | Retail offset | Retail callback VA |
|---|---:|---:|---:|
| AddMaxHealth | 0x60 | 0x70 | 0xc52b20 |
| ChangeType | 0x64 | 0x74 | 0xc51050 |

The next 16-byte record is all zero.

## Table VA 0x10cdbb4

Anchor: `?buildFieldParse@StatusBitsUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z`, RVA `0x002D7DA0`, operand `+0x16`.

| Key | Source offset | Retail offset | Retail callback VA |
|---|---:|---:|---:|
| StatusToSet | 0x60 | 0x70 | 0x429b9a |
| StatusToClear | 0x68 | 0x7c | 0x429b9a |

The next 16-byte record is all zero.

## Extents and interpretation

The four builders at RVAs 00124670, 00123180, 002D6370, and 002D7DA0
are each 35 bytes, ending in RET at +0x22 followed by INT3. Both calls
in every body target MultiIniFieldParse::add at RVA00850920. The shared
UpgradeMux table is added at object offset8; the per-class table at offset0.

The shared table has six fields plus terminator (112 bytes), while the source
has five plus terminator (96 bytes). The MaxHealth and StatusBits tables
retain the same keys with contradicted layout offsets. ActiveShroud instead
points to DelayTime, and FireOCLAfterWeaponCooldown instead points to eleven
weapon/damage keys. Those are table-binding contradictions; no alternative
full member/function name is inferred from the key strings alone.

A further source binding at RVA004582D0 claims ChallengeGenerals::parseGeneralPersona.
Its +9 operand actually points to RadiusDecal data VA010F6440 (Texture,
Texture2, Style, etc.), not its 26 persona keys. RET4582E3/INT3 confirms20bytes.
This overlaps the already recorded RadiusDecal table/layout finding, but
the wrong ChallengeGenerals binding is a distinct contradiction.

All these claims remain unchanged on the inspected origin/master snapshot.
Ledger retirement is blocked locally by two inherited aliases whose bodies
are held elsewhere; no guard or baseline is bypassed. The shared-header
layout repair needs dependent-body verification and a full gate. Record
findings now so a canonical repair can include the entire affected family.
