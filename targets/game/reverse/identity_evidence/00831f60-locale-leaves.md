# Two _Locale_impl table leaves

Retail vtable VA0112EB34 contains three pointers: 00C3B310,00C31F60,
00C31F70. The preceding COL at011DE150 names type descriptor012C7898;
its complete name is `.?AV_Locale_impl@_STL@@`. Slot0 is the existing
matched scalar-deleting destructor at0083B310. Matched constructor8364F0,
destructor836520 and classic-locale builder83B330 independently install
this same table. Ghidra read_memory at0112EB30 confirms the COL/table.

Each of00831F60 and00831F70 is a separate single-byte RET followed by
fifteen INT3 bytes. Ghidra read_memory at00C31F60 confirms all32 bytes.
The table supplies independent entry witnesses for both leaves; no ICF or
adjacency-only identity is assumed.

The ABI comes from existing matched callers, not from the identical RETs:

- `_STL::locale::locale` at00832120 loads the classic-locale object from
  VA0130BCA0 into ECX and calls `[vptr+4]` at00832134 without pushing any
  argument. It ignores the result and retains the receiver in EDI.
- `_STL::locale::~locale` at00832170 loads its implementation pointer
  into ECX and tail-jumps `[vptr+8]`, with no stack parameters or result.

Both existing source declarations are `virtual void ...(void)`. Their
semantic method spellings are not promoted: production uses distinct
fully address-qualified owner/method names. It needs no object fields,
duplicate canonical layout, inline assembly, vtable definition or pin.
