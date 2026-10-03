# PlayerTemplate parser initializer audit (2026-10-03, v3)

RVA000E4210/284B, `PlayerTemplateStore::parsePlayerTemplateDefinition`, passesVA010847E0 at both operands+4F/+7F. The source has45FieldParse entries plus terminator (736B); retail has49plus terminator (800B). Ghidra and the local unpacked PE agree on the entire800Btable and288Bbody/padding window. The body endsRET at000E432B thenINT3 at000E432C; its earlier return is000E4284.

This is a confirmed initializer/layout contradiction under docs/matching.md Relocations, not a proposed replacement identity. The old ordinary gate passes because it verifies code and selected references, not this complete TU-local table.

| Retail key | Retail offset | Current source offset |
|---|---:|---:|
| Side | 0x8 | 0x8 |
| PlayableSide | 0xBD | 0xB9 |
| DisplayName | 0x4 | 0x4 |
| StartMoney | 0x1C | 0x20 |
| PreferredColor | 0x28 | 0x2C |
| StartingBuilding | 0x34 | 0x38 |
| StartingUnit0 | 0x38 | 0x3C |
| StartingUnit1 | 0x3C | 0x40 |
| StartingUnit2 | 0x40 | 0x44 |
| StartingUnit3 | 0x44 | 0x48 |
| StartingUnit4 | 0x48 | 0x4C |
| StartingUnit5 | 0x4C | 0x50 |
| StartingUnit6 | 0x50 | 0x54 |
| StartingUnit7 | 0x54 | 0x58 |
| StartingUnit8 | 0x58 | 0x5C |
| StartingUnit9 | 0x5C | 0x60 |
| ProductionCostChange | 0x0 | 0x0 |
| ProductionTimeChange | 0x0 | 0x0 |
| ProductionVeterancyLevel | 0x0 | 0x0 |
| IntrinsicSciences | 0x8C | 0x88 |
| IntrinsicSciencesMP | 0x98 | absent |
| PurchaseScienceCommandSet | 0xA4 | absent |
| PurchaseScienceCommandSetMP | 0xA8 | absent |
| SpecialPowerShortcutCommandSet | 0xAC | 0xA0 |
| SpecialPowerShortcutWinName | 0xB0 | 0xA4 |
| SpecialPowerShortcutButtonCount | 0xB4 | 0xA8 |
| IsObserver | 0xBC | 0xB8 |
| IntrinsicSciencePurchasePoints | 0xC0 | 0xBC |
| ScoreScreenImage | 0xCC | 0xC0 |
| LoadScreenImage | 0xD0 | 0xC4 |
| LoadScreenMusic | 0xB8 | 0xAC |
| HeadWaterMark | 0xD4 | 0xC8 |
| FlagWaterMark | 0xD8 | 0xCC |
| EnabledImage | 0xDC | 0xD0 |
| SideIconImage | 0xE0 | 0xD4 |
| BeaconName | 0xE4 | 0xDC |
| LightPointsUpSound | 0x100 | absent |
| ObjectiveAddedSound | 0x104 | absent |
| ObjectiveCompletedSound | 0x108 | absent |
| InitialUpgrades | 0xE8 | absent |
| DefaultPlayerAIType | 0x10C | absent |
| SpellBook | 0x110 | absent |
| SpellBookMp | 0x114 | absent |
| MaxLevelMP | 0xC4 | absent |
| MaxLevelSP | 0xC8 | absent |
| Evil | 0x118 | absent |
| BuildableHeroesMP | 0xF4 | absent |
| SpellStoreCurrentPowerLabel | 0x11C | absent |
| SpellStoreMaximumPowerLabel | 0x120 | absent |

Current-only keys: BaseSide, PurchaseScienceCommandSetRank1, PurchaseScienceCommandSetRank3, PurchaseScienceCommandSetRank8, OldFaction, ScoreScreenMusic, GeneralImage, ArmyTooltip, Features, MedallionRegular, MedallionHilite, MedallionSelect.

The correction must coordinate the canonical PlayerTemplate layout and dependent bodies; no isolated offsetof changes or guessed C++ members are authorized by these serialized key names. Existing old method identities remain unchanged. The held inherited-alias integration issue also prevents ledger edits locally. No production edit or improved reconstruction bank is included.

Evidence artifacts: build/audit_v3/s4_player_template_raw.json and s4_fieldparse_wide_n.json. Current source body and references passed in the1548-claim expansionN; that does not validate the contradicted initializer.
