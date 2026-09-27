# D3DXCore::CBuffer::QueryInterface at 0x00A5710A

This 71-byte body was banked as the address-derived twin `d3dx9_twin_00a5710a`,
pinned to createmesh.obj's `CD3DXSkinInfo::QueryInterface`. The note on that row
said six masked-identical d3dx9.lib QueryInterface bodies could sit here and
that nothing in the image separates them.

The IID relocation does separate them.
- At +0x23 the body compares against the GUID at VA 0x0114DBC8, which is
  {932E6A7E-C68E-45DD-A7BF-53D19C86DB1F}.
- That GUID is `IID_ID3DXBuffer` (inputs/toolchains/dx81/include/d3dx8core.h).
- `CConstantTable::QueryInterface` (0x00A56226) resolves `_IID_ID3DXBuffer` to
  the same address. ID3DXConstantTable derives from ID3DXBuffer.
- CD3DXSkinInfo's own QueryInterface (0x00A04EA7, slot 0 of vtable 0x01149088)
  uses 0x0114DA98, {0E7DBBF3-421A-4DD8-B738-A5DAC3A48767}.

Of the six candidates, only `obj\i386\cbuffer.obj`'s
`?QueryInterface@CBuffer@D3DXCore@@UAGJABU_GUID@@PAPAX@Z` references
`_IID_ID3DXBuffer`. The other five reference the IIDs of ID3DXSkinInfo,
ID3DXRenderToSurface, ID3DXRenderToEnvMap and ID3DXSPMesh (two bodies).

The address is also inside cbuffer.obj's contribution. Its matched members sit
around it:
- ~CBuffer at 0x00A56E88
- Grow at 0x00A56F00
- AddString at 0x00A56FE1
- the CBuffer constructor at 0x00A57151
