# PresetOpaqueShader at VA 0x012D6E08

Corrected and verified. The owning definition has a matched data row whose complete four bytes equal retail and whose target relocation count is zero. Every retained changed source passes its scoped function gate. Raw data-registration, source-gate and link results are recorded in `build/worker-final.md`.

The supported spelling is `?_PresetOpaqueShader@ShaderClass@@2V1@A`. This datum is one `ShaderClass` object in retail `.data`, with size 4 byte(s) and initial bytes `1b581100`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

The reference shader.cpp preset sequence begins with _PresetOpaqueShader, followed by additive, bump-environment, alpha and other presets, each holding one ShaderBits word. The retail sequence in shader-preset-run.log has that ordering and the established public _PresetAdditiveSpriteShader pin at its corresponding position. Render2D and screen-filter users select the same opaque preset for the reference operation. Retail holds 0x0011581B; the reference-derived initializer in the current owner compiles to 0x0011441B, so the data initializer must use the verified BFME bits. The difference is in the primary-gradient field, not a pointer relocation.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012D6E08, 0x012D6E0C)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x006DA2D0`, `0x006EB500`, `0x00722640`, `0x007A1770`, `0x007B14A0`, `0x007BB060`, `0x007BBF80`, `0x007BC270`, `0x007BFB90`, `0x007CC430`, `0x007D1020`, `0x007D1AA0`, `0x007D1F00`, `0x007D31C0`, `0x007D47A0`, `0x007D62F0`, `0x007D7610`, `0x007D81C0`, `0x007D9240`, `0x007DAE30`, `0x007DC6A0`, `0x00988FD0`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?Rva012D6E08Shader@@3IA` | 0 |
| `?ScreenOpaqueShader@@3IA` | 1 |
| `?ScreenOpaqueShader@@3VShaderClass@@A` | 1 |
| `?_PresetOpaqueShader@ShaderClass@@2V1@A` | 8 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A different preset sequence around the pinned additive sprite member, an opaque caller routed to another word, a size other than four, or any changed function byte would refute the correction.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
