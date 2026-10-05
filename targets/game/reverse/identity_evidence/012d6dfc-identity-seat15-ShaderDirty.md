# ShaderDirty at VA 0x012D6DFC

Unresolved correction. Retail and the reference support the protected bool ShaderClass::ShaderDirty, but several free users and public local ShaderClass views cannot directly emit its protected spelling. A sanctioned adoption of the existing DX8Wrapper::Set_Shader friend implementation is needed; no invented access class or new wrapper is introduced in this run.

The supported spelling is `?ShaderDirty@ShaderClass@@1_NA`. This datum is one `bool` object in retail `.data`, with size 1 byte(s) and initial bytes `01`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

Retail uses byte tests and stores at this address, including the invalidate stores before shader application. shader.cpp initializes this flag true and ShaderClass::Apply tests then clears it; shader.h declares it protected and befriends DX8Wrapper. Public local declarations emit access digit 2 and are a spelling conflict with the reference access digit 1, not a second object. Retail initial byte is 01; the following padding is not part of this bool.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012D6DFC, 0x012D6DFD)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x006C5410`, `0x006C5AC0`, `0x006C90B0`, `0x006CCE70`, `0x006D3480`, `0x006DA2D0`, `0x006DC970`, `0x006E2AC0`, `0x00710620`, `0x00711F30`, `0x00715B70`, `0x0071A730`, `0x00722640`, `0x00722BD0`, `0x00726290`, `0x0072FEB0`, `0x00737B70`, `0x007A1770`, `0x007A1C80`, `0x007A2330`, `0x007A7240`, `0x007A8400`, `0x007A8FF0`, `0x007ACBD0`, `0x007B14A0`, `0x007BB060`, `0x007BFB90`, `0x007C33B0`, `0x007C34E0`, `0x007C3FD0`, `0x007C5600`, `0x007CBD90`, `0x007CC360`, `0x007CC430`, `0x007CCDE0`, `0x007D1020`, `0x007D1610`, `0x007D1AA0`, `0x007D2D30`, `0x007D31C0`, `0x007D3D40`, `0x007D47A0`, `0x007D62F0`, `0x007D7610`, `0x007D81C0`, `0x007D9240`, `0x007DAE30`, `0x007DC6A0`, `0x007DCC60`, `0x00903C50`, `0x009095A0`, `0x0090FEE0`, `0x00910DF0`, `0x00911020`, `0x00913AF0`, `0x00933590`, `0x00933E50`, `0x00934940`, `0x009436C0`, `0x00948BD0`, `0x00951AA0`, `0x00956F40`, `0x0095CE80`, `0x00960A30`, `0x00975100`, `0x0098ED30`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?Rva012D6DFCShaderDirty@@3_NA` | 1 |
| `?ScreenShaderDirty@@3_NA` | 10 |
| `?ShaderDirty@ShaderClass@@1_NA` | 2 |
| `?ShaderDirty@ShaderClass@@2_NA` | 5 |
| `?g_Va012D6DFC@@3EA` | 1 |
| `?g_bfmeDoneTDB@@3DA` | 1 |
| `?g_bfmeFlag1056@@3DA` | 1 |
| `?g_rva007A2330Flag@@3DA` | 4 |
| `?g_rva007A2330Flag@@3EA` | 2 |
| `?g_rva007A2330Flag@@3_NA` | 2 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A retail non-byte access spanning the next datum or independent evidence that BFME made the member public would change the identity or access decision.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
