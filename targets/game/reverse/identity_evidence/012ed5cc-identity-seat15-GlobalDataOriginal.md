# GlobalDataOriginal at VA 0x012ED5CC

Unresolved registration. The private static identity and existing definition are supported. tools/data_rows.py refuses to size a private member, including an uninitialized-definition probe. No data row is fabricated and no private-access workaround or shared-header edit is made.

The supported spelling is `?m_theOriginal@GlobalData@@0PAV1@A`. This datum is one `GlobalData *` object in retail `.data`, with size 4 byte(s) and initial bytes `00000000`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

GlobalData constructor RVA 0x00084510 compares the pointer with null then stores this. Destructor RVA 0x00084030 compares it with this and clears it, together with TheWritableGlobalData. reset uses it as the original override-list endpoint. The reference GlobalData.cpp defines GlobalData::m_theOriginal=NULL and GlobalData.h declares it private. The losing free name has no current game declaration. The existing canonical source definition is already present in GlobalDataDestructor.cpp.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012ED5CC, 0x012ED5D0)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x00083110`, `0x00084030`, `0x00084510`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?g_bfmeGlobalDataOriginal@@3PAVGlobalData@@A` | 0 |
| `?m_theOriginal@GlobalData@@0PAV1@A` | 2 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A legal data-tool sizeof proof for the private member would settle registration. A different construction/destruction identity would refute the name.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.

The actual registration refusal is preserved in `build/rlink/identity-20261005-114922/add-data-private-original.log`. The independent uninitialized-definition compile probe and its sizing refusal are preserved in `private-size-probe.log`.
