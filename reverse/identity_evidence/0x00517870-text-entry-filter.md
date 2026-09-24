# 0x00517870: opaque text-entry filter

The generated dump fixes a 220-byte body at 0x00517870. Retail handles message
0x19 specially, consumes comma, colon, and semicolon, then obtains the
`GameWindow` at receiver+8. It compares unnamed user-data halfwords at +0x1C
and +0x1E. When they agree, it calls `GadgetTextEntryGetText` through ILT
0x000220B1 and consumes an alphanumeric character if the returned string is
already at least 12 characters long. Other cases forward the three message
arguments through ILT 0x00003DF0 to physical body 0x00479270. Both retail
exit paths use `ret 0xC`.

`tools/callees.py 0x00517870 220` finds the `GameWindow::winGetUserData`
thunk, `GadgetTextEntryGetText` thunk, `StringBase<unsigned short>` release,
and fallback thunk, all with ledger bodies. The retail IAT call is
`MSVCR71.dll!iswalnum`. The existing matched `Rva004BE120Input::input` body
uses the same three-argument fallback route, so this implementation follows
that witnessed ABI without changing the fallback pin. The canonical
`unicode_string.h` supplies the string type; `_WCTYPE_INLINE_DEFINED` keeps
MSVC 7.1 on the imported `iswalnum` call seen in retail.

`tools/callers_of.py` finds no named direct caller, and the nearby LAN-lobby
constructor registers other callback bodies, not this one. The owning class
and original method spelling therefore remain unproven. The claimed symbol
`Rva00517870Owner::rva00517870` retains the address instead of asserting a
semantic identity. The clean C++ probe matches 220/220 bytes with 11 aligned
relocation sites; the strict replacement gate verifies the final ledger claim.
