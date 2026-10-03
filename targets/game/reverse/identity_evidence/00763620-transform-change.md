# W3DModelDraw transform callback at RVA 00763620

The complete retail extent is 487 bytes, through RET 0Ch at 00763804.
Primary W3DModelDraw table VA01123D38 slot35 routes through ILT00022DEA.
The existing GeneralsMD W3DModelDraw::reactToTransformChange twin supplies
both the render-transform and terrain-track behavior and the three-argument
signature. BFME additionally updates the height-map footprint using the old
and current positions, and supports translation-only transforms.

The retail receiver stores module data at +4, Drawable at +8, render object
at +34, track at +44, and the witnessed m_fullyObscuredByShroud at +2D.
The inherited reference accessors have different offsets. This implementation
includes their canonical headers and uses explicit local BFME offset views.
The template uses the actual OVERRIDE<ThingTemplate> conversion; template+3A0
and module-data+69 deliberately have no invented semantic member names.

Calls follow the retail ILTs: 22BB -> 87A80 (canonical final override),
4B12D -> 41D090 (position), 17512 -> 41CEC0 (matrix pointer, legacy int
return spelling), 1B572 -> 74B480 (WorldHeightMap footprint, thiscall, three
stack arguments/RET0C), 26350 -> 7629F0 (writable matrix adjustment),
191EB -> 72F390 (cap), 19FF1 -> 131B20 (terrain test), and 471F4 -> 72F760
(track edge). The map uses a checked four-byte member-pointer bridge to the
existing address-named ILT rather than a second member identity. Its canonical
header is included. TheTerrainRenderObject is VA012F7FE0; +2FF4 is the map.
The render object's canonical Set_Transform dispatch is slot +54.

Ghidra decompilation was cross-checked against the unpacked PE's complete
487-byte Capstone disassembly. Instruction-mask probes are not binding proof;
the scoped add_match/build gate supplies relocation-aware validation.

Validation: scoped add_match passed487/487 bytes, one float constant and two
DIR32 operands; the original TU retains153/153 verified claims. Its unchanged
8-byte cleanup uw_00c4f960 was reselected from $L124986 to $L124886.
