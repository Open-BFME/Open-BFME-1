# BitDepth at VA 0x012D6DBC

Corrected and verified. The owning definition has a matched data row whose complete four bytes equal retail and whose target relocation count is zero. Every retained changed source passes its scoped function gate. Raw data-registration, source-gate and link results are recorded in `build/worker-final.md`.

The supported spelling is `?BitDepth@DX8Wrapper@@1HA`. This datum is one `int` object in retail `.data`, with size 4 byte(s) and initial bytes `20000000`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

Get_Render_Target_Resolution, RVA 0x00906990, returns this cell through its bitDepth output, alongside the width, height and windowed outputs. DX8Wrapper::Init writes 32 and Set_Render_Device changes it as the requested display bit depth. The reference declares protected static int BitDepth. The BfmeRenderBitDepth declaration occurs inside the same owning member implementation and can directly use BitDepth.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012D6DBC, 0x012D6DC0)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x00902170`, `0x00906990`, `0x00906A60`, `0x00906AA0`, `0x0090AB60`, `0x0090B020`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?BfmeRenderBitDepth@@3HA` | 1 |
| `?BitDepth@DX8Wrapper@@1HA` | 2 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A caller that uses this output as an unrelated quantity, or a differing byte in the changed source, would refute the correction.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
