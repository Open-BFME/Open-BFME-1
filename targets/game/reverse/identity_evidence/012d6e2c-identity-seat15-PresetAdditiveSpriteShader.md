# PresetAdditiveSpriteShader at VA 0x012D6E2C

Corrected and verified. The owning definition has a matched data row whose complete four bytes equal retail and whose target relocation count is zero. Every retained changed source passes its scoped function gate. Raw data-registration, source-gate and link results are recorded in `build/worker-final.md`.

The supported spelling is `?_PresetAdditiveSpriteShader@ShaderClass@@2V1@A`. This datum is one `ShaderClass` object in retail `.data`, with size 4 byte(s) and initial bytes `33401100`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

symbols.csv already pins ShaderClass::_PresetAdditiveSpriteShader to this VA from the StreakRendererClass constructor. The reference shader.cpp defines the same public ShaderClass preset and line, point and streak renderers use it. Retail contains 0x00114033, exactly the current owner compiled initializer. The Gen012D6E2C load copies that word into the constructor shader field; the competing pointer spelling has no corresponding pointer use.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012D6E2C, 0x012D6E30)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x005F1370`, `0x005F31A0`, `0x005F43B0`, `0x005F5570`, `0x005F8010`, `0x0090F650`, `0x00912580`, `0x0095C720`, `0x0095FE50`, `0x0095FFD0`, `0x00960990`, `0x00974F80`, `0x00975090`, `0x0098C2E0`, `0x0098D6B0`, `0x0098E9C0`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?Gen012D6E2C@@3HA` | 1 |
| `?TheBfmeShared012D6E2C@@3PAVBfmeShared012D6E2C@@A` | 0 |
| `?_PresetAdditiveSpriteShader@ShaderClass@@2V1@A` | 8 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A StreakRenderer constructor that reads another preset, a pointer dereference of this word, or any differing byte in a changed function would refute the correction.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.

The declared-unmatched gate also exposed the already tombstoned, unclaimed `Rva007D8880` constructor in this source. Its tombstone is `deleted_rows.csv` line 31, and the canonical 38-byte ScreenMotionBlurFilter constructor already has its own source and ledger row. The obsolete local class and constructor were removed after the raw user search in `build/rlink/identity-20261005-114922/orphan-constructor-users.log` established that no other game source refers to it. The canonical function and its ledger row are unchanged; the retained sixteen rows in this source pass `repair-build-R3ScalarFieldConstructors3.log`.
