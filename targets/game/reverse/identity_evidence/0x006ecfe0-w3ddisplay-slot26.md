# RVA 0x006ECFE0 is W3DDisplay slot 26

The retail W3DDisplay vtable symbol `??_7W3DDisplay@@6B@` points to VA
`0x0111EDD0` in `targets/game/reverse/dir32_addresses.csv`. Entry 26 at VA
`0x0111EE38` contains ILT VA `0x0040E88B`. The generated thunk row for ILT RVA
`0x0000E88B` in `targets/game/reverse/functions.csv` routes to RVA
`0x006ECFE0`. This proves that the body belongs to W3DDisplay virtual slot 26.

The matched W3DDisplay destructor at RVA `0x006EFC20` uses the same vtable.
The constructor at RVA `0x006EF850` builds the same W3DDisplay-vtable object.
The matched `W3DDisplay::rva006E9B70` body is slot 44 and resets the Render2D
pointer at `this + 0x164`. The constructor source also lays out a vector at
`this + 0x29C`, where this body reads its begin and end pointers. These fields
support the W3DDisplay receiver layout in the recovered method.

The old bank name `BfmeHostEVG::bfmeClearEVG` came from the cleanup behavior,
not a caller, vtable entry, export, or string. Retail slot 26 supplies the
owner but no semantic method name, so the source keeps the address in
`W3DDisplay::rva006ECFE0`. The body uses `ItemSlot11At006ECFE0` only as an
address-qualified layout view for the element called through vtable offset
`+0x2C`; retail does not identify that element type by name.
