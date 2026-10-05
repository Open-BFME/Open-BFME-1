# TheWorldDict at VA 0x012ED5E0

Corrected and verified. The owning definition has a matched data row whose complete four bytes equal retail and whose target relocation count is zero. Every retained changed source passes its scoped function gate. Raw data-registration, source-gate and link results are recorded in `build/worker-final.md`.

The supported spelling is `?TheWorldDict@MapObject@@2VDict@@A`. This datum is one `Dict` object in retail `.data`, with size 4 byte(s) and initial bytes `00000000`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

Retail users put the immediate address into ECX, rather than loading a pointer from it. WorldHeightMap::freeListOfMapObjects at RVA 0x00746E90 reaches the E9 thunk at RVA 0x00033F46, whose final body at RVA 0x00068530 releases Dict data then zeroes its sole pointer field. W3DView::buildCameraTransform at RVA 0x00741D30 calls setReal on the same receiver. The lookup thunk at RVA 0x000184B2 reaches 0x00067EC0 and returns a float from the keyed dictionary. The reference MapObject.h declares static Dict TheWorldDict and WorldHeightMap.cpp defines it. Dict.h contains only DictPairData *m_data, and the compiler sizeof probe proves four bytes; the initial eight-byte audit window was a probe window, not an extent claim.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012ED5E0, 0x012ED5E4)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x0042E340`, `0x00432010`, `0x0045A000`, `0x006DF290`, `0x006DF2E0`, `0x006DF330`, `0x006DF380`, `0x006DF3D0`, `0x00741D30`, `0x00746E90`, `0x00746F60`, `0x0074ACB0`, `0x00C6AA50`, `0x00C6FCD0`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?BfmeTheMapObjectExtra@@3VBfmeMapObjectExtra@@A` | 1 |
| `?GenTable0012ED5E0@@3VGenTable@@A` | 1 |
| `?TheWorldDict@MapObject@@2VDict@@A` | 3 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A named Dict method routed to another object, a field access beyond this four-byte object, an overlapping datum, or a differing byte in a changed function would refute the correction.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
