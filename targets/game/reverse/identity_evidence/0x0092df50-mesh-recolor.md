# RVA 0x0092DF50: MeshClass color application

The old `?Recolor_Mesh@W3DAssetManager@@QAEHH@Z` identity is wrong.
Retail loads Model at ECX+0xC8, adds its reference, and dispatches the same
receiver through +0x150 (material info) and +0x18 (name). The MeshClass
vtable at VA 0x0113C390 contains VA 0x00D2DF50 at slot +0x1F8; this was
independently read from the baseline image. The sole stack argument is
consumed by ret 4 at +0x4BF. It is a packed color: logical right shifts and
unsigned integer-to-float conversions recover its RGB components.
The epilogue supplies no return value, unlike the old int declaration.

Zero Hour W3DAssetManager::Recolor_Mesh(RenderObjClass*, int) provides the
HOUSECOLOR vertex-material and ZHC texture logic, but has a manager receiver
and two stack arguments. BFME moved this operation into the mesh virtual
interface and added the single-pass shader/texture path. No evidence here
proves the original BFME method spelling, so use the address-bearing virtual
`?Recolor0092DF50@MeshClass@@UAEXI@Z`, not an invented historical name.

The full extent is 1218 bytes, ending immediately after ret 4. Reconstruction
uses the witnessed Model+0xC8 and CurMatDesc+0x9C, owning four-byte texture
handles with 16-bit refcounts, and native ShaderClass value-copy forwarding.
All direct callees retain their established ledger spellings or ILT identities.
The format literal at VA 0x0113C5B0 is #%d#%s (two percent format markers).
