# UpgradeCenter parser table contradiction

Severity: WRONG; no production or identity change in this record.

Rule: docs/matching.md, Relocations: the build checks what a reference points at. A masked DIR32 comparison alone does not validate the initializer. AGENTS.md requires real source and forbids guessed identities.

The surviving August 1 claim `?parseUpgradeDefinition@UpgradeCenter@@SAXPAVINI@@@Z`, RVA0010B280/172B, uses operand +0x7B to pass retail table VA01088B60. Fresh exact-input compilation of Common/System/Upgrade.cpp passes all fourteen existing function claims and their current code-reference checks. Its FieldParse initializer nonetheless has eight entries; the directly anchored retail table has twelve entries and a complete zero terminator (208B total). Ghidra read_memory independently agrees with the PE window.

| Key | Source offset | Retail offset | Retail callback VA |
|---|---:|---:|---:|
| DisplayName | 0x10 | 0x10 | 0xc51ee0 |
| Tooltip | absent | 0x14 | 0xc51ee0 |
| Type | 0x4 | 0x4 | 0xc51050 |
| BuildTime | 0x14 | 0x18 | 0xc52b20 |
| BuildCost | 0x18 | 0x1C | 0xc52a60 |
| ButtonImage | 0x100 | 0x110 | 0xc51ee0 |
| ResearchSound | 0x2C | 0x28 | 0x409e94 |
| UnitSpecificSound | 0x90 | 0x98 | 0x409e94 |
| UpgradeFX | absent | 0x24 | 0xc51ee0 |
| Cursor | absent | 0x118 | 0xc51ee0 |
| PersistsInCampaign | absent | 0x11C | 0xc52e00 |
| NoUpgradeDiscount | absent | 0x11D | 0xc52e00 |

Source-only key: AcademyClassify at offset0xF4. Retail Type userdata is VA012ABEA0. Both audio callbacks use ILT00409E94 -> RVA000BBB60. These are independently decoded routes, not owner-name evidence.

The complete 172B body includes RET at0010B327 and an owned alternate tail at0010B328 (`mov eax,edx; jmp 0010B2FA`) ending0010B32B, followed by CC at0010B32C. The RET alone is not its full extent. Callees were inspected before any proposed body work; no body reconstruction was written.

The source uses the shared upstream Common/Upgrade.h layout. Adding keys or hardcoding offsets beneath that layout would leave constructor, audio member stride and dependent accesses inconsistent. Repair requires a canonical BFME layout and its dependent bodies, then the required full gate. Do not infer C++ member names from serialized INI keys. No new pin, baseline, semantic rename or partial layout edit is made.

Fresh origin/master row check still contains the claim. This record is blocked/layout, not a new conversion. Scratch reproduction: build/audit_v3/s5_upgrade_parser_proof.json and s5_medium_o/14.log; the bounded evidence is fully enumerated above.
