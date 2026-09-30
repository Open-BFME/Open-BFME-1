# 0x001D95B0 is a pointer-element `_Vector_base` constructor, not the AsciiString one

The 97-byte body at 0x001D95B0 was claimed as
`??0?$_Vector_base@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@IABV?$allocator@VAsciiString@@@1@@Z`
by an `__emit` lift with no identity evidence.

- The body's first call (+0x1E) builds `_M_end_of_storage` through ILT 0x0002087E -> 0x000CCC70,
  the 11-byte `_STLP_alloc_proxy<T**, T*, allocator<T*>>` constructor (pinned as the
  `Rva002622D0Subject *` proxy). A clean `AsciiString` instantiation compiles to the same bytes but
  its `_STLP_alloc_proxy<AsciiString*, AsciiString, ...>` callee resolves to 0x00094CD0, so
  `tools/build.py` rejects it: the element type is a pointer, not `AsciiString`.
- The matched caller `?collectAt002622D0@Rva002622D0Owner@@...` (0x002622D0) copies a
  `vector<Rva002622D0Subject *>` and calls this body, and symbols.csv already pins
  `??0?$_Vector_base@PAVRva002622D0Subject@@...` here ("exact97B scoped pointer-vector base
  constructor body").

The body therefore takes the caller's opaque, address-derived element name
`Rva002622D0Subject *`; the real pointee class stays unproven.
