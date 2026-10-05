# TextureBitDepth at VA 0x012D6DC0

Unresolved correction. The existing DX8Wrapper getters and texture setter are themselves protected. The source gate rejects their use from the free address-named bodies. These datum attempts and their data rows were restored without discarding the independent BitDepth correction. A separate proven member identity correction or an authorized adoption of an established access path is required; no invented wrapper, derived access class or header visibility change is added.

The supported spelling is `?TextureBitDepth@DX8Wrapper@@1HA`. This datum is one `int` object in retail `.data`, with size 4 byte(s) and initial bytes `10000000`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

The reference defines protected static int TextureBitDepth initially as 16. Registry_Save_Render_Device reads it as the texture-depth argument after display resolution and bit depth; Set_Texture_Bitdepth is an established protected inline setter. The RVA 0x008FE150 store writes its one stack int argument here and returns without stack cleanup. Its old Rva008FE150::s_value definition has no data row and initializes zero, which disagrees with retail. The address-named setter cannot legally call this protected inline API. The existing initialized DX8Wrapper definition owns the datum, but the source respelling and data registration remain unresolved.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012D6DC0, 0x012D6DC4)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x008FE150`, `0x00906A60`, `0x0090B960`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?TextureBitDepth@DX8Wrapper@@1HA` | 2 |
| `?s_value@Rva008FE150@@2HA` | 1 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A retail user treating this word as an address, a registry argument associated with another setting, or a differing byte in the setter would refute the correction.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.

A proven member identity or an existing legal access path that preserves all retail bytes would settle the blocked source correction. The raw access failures are in `build/rlink/identity-20261005-114922/build-after-GlobalDwordGetters.log`, `build-after-UnclaimedGlobalGetters.log` and `build-after-TinyGlobalStores.log`; restoration is recorded in `restore-protected-attempts.log`.
