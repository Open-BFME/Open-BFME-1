# CurRenderDevice at VA 0x012D6DB0

Unresolved correction. The identity is supported, but the free getter cannot access the protected member. The existing pin identifies the routed getter as WW3D::Get_Render_Device, which requires a separate body identity correction to remove the last free datum spelling without an invented access shim.

The supported spelling is `?CurRenderDevice@DX8Wrapper@@1HA`. This datum is one `int` object in retail `.data`, with size 4 byte(s) and initial bytes `ffffffff`. It is mutable storage, not a compiler constant. It has no initialized pointer relocations: the scalar and shader bits are values, and the pointer and Dict cells start null. Retail has no PE base-relocation directory, so that absence alone is not relocation proof; the owning compiler object and the retail accesses provide the contract.

DX8Wrapper::Init at RVA 0x0090AB60 writes -1; Set_Render_Device at 0x0090B020 reads and replaces this signed device index. Get_Render_Device_Desc at 0x00903E80 reads it to select a descriptor. Zero Hour dx8wrapper.cpp defines CurRenderDevice=-1 and its header declares protected static int. The reset-device caller uses the five-byte E9 at RVA 0x008FD180 (e9db4f0000), which reaches the six-byte load at RVA 0x00902160. symbols.csv pins that route as WW3D::Get_Render_Device, so the free getter must not be relabeled DX8Wrapper::Get_Render_Device on its load alone.

The contract is one mutable cell. Code accesses this cell directly or, for pointer objects, loads its pointed-to receiver before a member dispatch. Scalars accept their shown arithmetic values; shader presets contain one unsigned ShaderBits word; pointer cells accept null or their owner instance. No array element count, terminator table, inheritance, alias identity or additional wrapper is inferred.

No data row or DIR32 name lies strictly inside `[0x012D6DB0, 0x012D6DB4)`; the raw boundary audit is `build/rlink/identity-20261005-114922/retail-objects.log`. The chosen DIR32 spelling is already present beside the competing rows, so it is retained without inserting a duplicate or removing any pin. No functions.csv row is renamed or reordered.

The decoded retail bodies accessing this exact VA have RVAs `0x00902160`, `0x00903E80`, `0x00906A60`, `0x0090AB60`, `0x0090AE60`, `0x0090B020`, `0x0090B410`. Each access and its bytes are recorded in `retail-objects.log`, with complete bodies and followed E9 chains in `retail-bodies.log`. `supplemental-xrefs.log` preserves packed-address occurrences beyond interrupted linear decodes; those windows are marked as windows, not new boundary or identity claims.

Before correction, the game files declaring each decorated spelling are:

| Spelling | Declaring game files |
|---|---:|
| `?CurRenderDevice@DX8Wrapper@@1HA` | 2 |
| `?g_Va012D6DB0@@3HA` | 1 |

The source paths behind those declaration counts are in `build/rlink/identity-20261005-114922/declaration-counts-before.log`; historical DIR32 spellings with no current declaration remain listed as zero. The counts do not decide identity. The reference declarations and the retail receiver, value and lifetime operations decide it.

The observation that would refute or settle this decision is: A named device-selection caller routing to another cell, or a byte-preserving existing public access path for the free getter, would change this decision.

Raw evidence: `build/rlink/identity-20261005-114922/retail-objects.log`, `retail-bodies.log`, `supplemental-xrefs.log`, `shader-preset-run.log`, `inspect-candidates.log`, `reference-names.log`, and `reference-singleton-owners.log`. The unresolved private-size probe is in `private-size-probe.log`. Build and linking receipts, including any pre-existing blockers, are recorded in `build/worker-final.md`.
