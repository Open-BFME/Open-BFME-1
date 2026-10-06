# 0x00516BB0 forwards two stack arguments to Gen_00523380::bfmeSetSlot

Old row: `?invoke@Rva00516BB0@@QAEXXZ` (MemberOffsetTailThunks.cpp, generic
no-argument offset tail thunk). New row: `?bfmeSetSlot@Rva00516BB0@@QAEXGE@Z`,
same 11-byte extent, same TU.

`tools/dis_retail.py 0x00516BB0 11`: `add ecx, 0x25C; jmp 0x00048C89`. The
jmp leaves the caller's stack words in place for the target; ILT 0x00048C89
leads to 0x00523380, matched as `?bfmeSetSlot@Gen_00523380@@QAEXGE@Z`
(Bfme5TinyTwentyNine.cpp: `if (index < 8) m_bfmeSlots[index] = value;`, two
stack arguments, `ret 8`).

The matched caller `?OnAccept@LANAPI@@UAEXPAUBfmeNetAddress@@I@Z`
(0x006889B0, LANAPIOnAccept.cpp) pushes a slot index and a byte value and calls
this wrapper (via ILT 0x00007248) as
`Rva00516BB0::bfmeSetSlot(UnsignedShort, UnsignedByte)`; that name is also the
symbols.csv pin at 0x00516BB0. The no-argument `invoke()` spelling had no
caller and hid the two forwarded arguments, so the census left the caller's
name unresolved (alias of `invoke`). The wrapper now forwards both arguments to
the matched setter, with the same bytes.
