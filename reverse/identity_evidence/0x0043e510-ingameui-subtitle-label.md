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

The existing ledger names slot 19's physical body 0x00441D30 as
`InGameUI::militarySubtitle(const AsciiString&, int)`. Retail slot 19 ends with
`ret 8` and inspects a wide code unit at +0x40 of that body; the slot-20 caller
supplies a UnicodeString by value. The Zero Hour InGameUI header and two
currently unmatched ScriptActions bodies spell an AsciiString-label
`militarySubtitle`, which supports the label interface but does not prove that
spelling belongs to BFME physical slot 19. This conversion does not rename or
repin slot 19; its source uses an address-qualified positional declaration.
