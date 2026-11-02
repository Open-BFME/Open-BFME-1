# Seventeen address-derived +0x14 setters (0x00097090 ... 0x008088E0)

Each address holds its own 10-byte body (int3-padded on both sides):

    8b 44 24 04    mov eax, [esp+4]
    89 41 14       mov [ecx+0x14], eax
    c2 04 00       ret 4

i.e. a thiscall member storing one dword argument at this+0x14. No ILT stub
reaches any of the four (ilt_oracle: UNTESTABLE, not a thunk target), no pin or
dir32 name sits at them, and no caller or vtable slot recovered so far names
them.

Before: `?dup_XXXXXXXX@@YAXXZ` gen-alias placeholders (two rows per address,
`?dup_007f09b0` and `?dup_7f09b0` etc.) borrowing a byte-identical COMDAT from
another unit; no identity was ever claimed. The short-form second rows are
tombstoned in deleted_rows.csv (one identity per address).

After: `?set@RvaXXXXXXXX@@QAEXH@Z` in
game/GameEngine/Source/Common/UnclaimedOffset14Setters.cpp.
The names are derived from the address and say only what the bytes do; the
argument type (int) is a placeholder for an unwitnessed dword. Identity is not
recovered.

## Thirteen more (same session)

0x00097090 0x001A1A10 0x002B9D20 0x0036ADB0 0x0037D090 0x004E25B0 0x005376C0
0x006013E0 0x00662780 0x006D4520 0x006DF630 0x00751B40 0x007B7F90 have the same
ten bytes and were single `?dup_` gen-alias rows. Each is the target of a gen-thunk
ILT stub (`?j_XXXXXXXX`, noted per body in the source), so it is an external
function with a real decorated name; ilt_oracle contradicts the address-derived
`?set@RvaXXXXXXXX@@QAEXH@Z` spelling as it would any placeholder. The real names
are not recovered; these rows only replace the borrowed-COMDAT placeholders with
their own C++ bodies.
