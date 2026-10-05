# TheOptionGroupTarget at VA 0x012ED604

Corrected and verified. The owning definition has a matched data row whose complete four bytes equal retail and whose target relocation count is zero. Every retained changed source passes its scoped function gate. Raw data-registration, source-gate and link results are recorded in `build/worker-final.md`.

The supported spelling is `?TheOptionGroupTarget@@3PAXA`. This datum is one `void *` object in retail `.data`, with size 4 byte(s) and initial bytes `00000000`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

parseOptionGroup at RVA 0x000945A0 loads the pointer and passes it to INI::initFromINI with Bool, Int, String and Real entries constructed on the stack. The registration body at RVA 0x00094010 and the named-option constructor at RVA 0x0007F560 load the same receiver. Setters at RVA 0x000946D0, 0x00094700 and 0x00094730 notify it through the E9 thunk at RVA 0x0001A7DF, which reaches 0x00093050. That body traverses a receiver list and calls registered observers. No Zero Hour class counterpart was established. The existing role-describing TheOptionGroupTarget spelling accurately records a pointer to the option parser target without inventing a class identity. The two g_rva000946b0 definitions describe this same cell and are replaced by one owning definition in OptionGroup.cpp.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012ED604, 0x012ED608)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x0007F560`, `0x00094010`, `0x000945A0`, `0x000946B0`, `0x000946D0`, `0x00094700`, `0x00094730`, `0x00094760`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?TheBfmeManager_000946D0@@3PAVGen_000946D0Manager@@A` | 0 |
| `?TheBfmeManager_00094700@@3PAVGen_00094700Manager@@A` | 0 |
| `?TheBfmeManager_00094730@@3PAVGen_00094730Manager@@A` | 0 |
| `?TheOptionGroupTarget@@3PAXA` | 2 |
| `?g_rva0007F560Factory@@3PAVRva0007F560Factory@@A` | 0 |
| `?g_rva000946b0@@3PAVRva000946B0G@@A` | 4 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A parser that passes another receiver or evidence that this cell is an inline object rather than a loaded pointer would refute the correction. An EA class string or constructor publication would allow a more specific pointed-to type later.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
