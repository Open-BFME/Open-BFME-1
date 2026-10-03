# WeaponTemplateSet parser table layout contradiction

Severity: WRONG. Rule: docs/matching.md Relocations requires referenced contents to agree, not just a masked table-address operand.

The survivingAugust1 parseWeaponTemplateSet claim atRVA001ECE50/28B passes tableVA010A17A8 through operand+8 to INI::initFromINI8520A0. Ghidra and the local PE independently agree on all28B through RET8at1ECE69..1ECE6B, followed byCC1ECE6C, and on the complete128B retail table. Source has six keys/112B; retail has seven keys/128B, including a16B zero terminator.

| Key | Source offset | Retail offset | Callback body RVA (decoded route) |
|---|---:|---:|---:|
| Conditions | 0x4 | 0x4 | 0x1eb560 |
| Weapon | 0x0 | 0x0 | 0x1eac70 |
| AutoChooseSources | 0x0 | 0x0 | 0x1eacb0 |
| PreferredAgainst | 0x0 | 0x0 | 0x1ecdc0 |
| OnlyAgainst | absent | 0x0 | 0x1ece00 |
| ShareWeaponReloadTime | 0x50 | 0xE8 | 0x852e00 |
| WeaponLockSharedAcrossSets | 0x51 | 0xE9 | 0x852e00 |

OnlyAgainst is wholly missing. The two trailing booleans belong at0xE8/0xE9, not source0x50/0x51. This source compiles against the upstream GameLogic/WeaponSet.h: three slot-indexed arrays and the older KindOf mask layout. The source already hardcodes BFME's autoChoose base0x18 in one callback and points to a separate preferred-against conversion, but its shared declared owner remains the older shape.

The complete fresh source audit passes its existing functions and code-reference checks; the bounded initializer contradiction remains. Repair the canonical BFME owner/mask/slot layout and its dependent callbacks and bodies together, with the required full gate. Do not infer C++ member spelling or exact full layout from serialized keys alone. No partial table-offset substitution, new callback identity, source/header/pin/ledger/baseline edit is made. Existing origin/master claim checked before acquisition; record-only claim is released afterward.

Scratch bounded proof: build/audit_v3/s5_weaponset_proof.json; fresh object/input receipt and successful code gates in s5_medium_p/08.log.
