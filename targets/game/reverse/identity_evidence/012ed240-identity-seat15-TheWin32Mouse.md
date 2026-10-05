# TheWin32Mouse at VA 0x012ED240

Corrected and verified. The owning definition has a matched data row whose complete four bytes equal retail and whose target relocation count is zero. Every retained changed source passes its scoped function gate. Raw data-registration, source-gate and link results are recorded in `build/worker-final.md`.

The supported spelling is `?TheWin32Mouse@@3PAVWin32Mouse@@A`. This datum is one `Win32Mouse *` object in retail `.data`, with size 4 byte(s) and initial bytes `00000000`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

W3DGameClient::createMouse at RVA 0x006FBA50 allocates 0x5EAC bytes, calls the E9 thunk at RVA 0x0002B7B0 that reaches the W3DMouse constructor at RVA 0x007003E0, and publishes the result here; allocation failure publishes null. The reference W3DGameClient.h uses Win32Mouse *TheWin32Mouse for that publication and Win32Mouse.cpp clears the singleton at destruction. The zero store in BfmeThingSI::bfmeResetSI is a null-pointer clear, not proof of a counter.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012ED240, 0x012ED244)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x0005CC20`, `0x006BC080`, `0x006FBA50`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?TheWin32Mouse@@3PAVWin32Mouse@@A` | 1 |
| `?g_bfmeCountSI@@3HA` | 1 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A constructor thunk reaching another class, a publication of a numeric counter, or any differing byte in a changed function would refute the correction.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
