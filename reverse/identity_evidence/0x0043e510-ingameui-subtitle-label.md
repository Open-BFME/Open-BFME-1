# InGameUI subtitle label wrapper at 0x0043E510

The retail 132-byte body at 0x0043E510 is reached through ILT thunk
0x0002346B from slot 20 (+0x50) of vtables 0x010F5B38 and 0x01120590.
The matched InGameUI constructor 0x0044B800 installs the first table; the
matched W3DInGameUI constructor 0x006FBE10 installs the second. Both tables
have the same slot-20 target. This proves the InGameUI virtual owner, but the
BFME method spelling is not present in a matched caller, so the new name keeps
the body address.

The body returns with `ret 8`. It reads a pointer to an AsciiString from the
first argument slot and an integer duration from the second. It constructs a
by-value narrow string through the StringBase<char> copy body 0x00887B60,
calls `TheGameText` vtable slot 9 (+0x24) to fetch a UnicodeString, then copies
that wide result through 0x00888400. It passes the UnicodeString by value and
the duration to the receiver's vtable slot 19 (+0x4C), followed by wide string
cleanup at 0x008881D0. The clean C++ source reproduces all 132 bytes outside
eight relocation operands. The scoped `add_match.py` gate verified the physical
string callees and `TheGameText` global during relocation resolution.

The subsequent identity correction at
`0x00441d30-ingameui-slot-rehome.md` gives the AsciiString-label
`militarySubtitle` name to this slot-20 body. Slot 19 takes the forwarded
UnicodeString by value and keeps an address-qualified ledger name. Both source
symbols remain unchanged, with explicit `object-symbol` aliases in the ledger.
