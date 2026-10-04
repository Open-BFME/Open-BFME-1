# RVA 0x00415AA0: correct the bank's string type and retain opaque ownership

The 46-byte retail body reads its argument's buffer pointer, tests the 16-bit
length at buffer+4, and adjusts ECX by 0x2D8 before either clearing or assigning
the receiver's string. Its clear path ends in `ret 4`; its assignment path ends
in a tail jump. Eight INT3 bytes follow the extent.

`TooltipUpgrade::upgradeImplementation` at RVA 0x002D9510 calls this updater
through ILT RVA 0x00025162, which jumps to 0x00415AA0. This establishes an
ordinary receiver update, but does not independently name its declaring class
or method. The bank explicitly labelled `BfmeOwnAU` as identity unknown;
`Rva00415AA0` therefore preserves rather than discards that uncertainty.

The bank's `UnicodeString` declaration is contradicted by the resolved callees:

- clear calls RVA 0x00887940: canonical `StringBase<char>::releaseBuffer()`;
- assignment jumps to RVA 0x00887C90: canonical
  `StringBase<char>::set(const StringBase<char>&)`.

The replacement includes `game/Libraries/Source/WWVegas/WWLib/string_base.h`
instead of redeclaring the string. Its row-scoped verification resolves both
calls to the exact retail targets and matches all 46 bytes. The canonical
length accessor uses the witnessed unsigned-short header field.

The naming checker pairs both removed bank types (`BfmeOwnAU` and
`UnicodeString`) with the new receiver type. The latter pairing is false:
`UnicodeString` is replaced by the included canonical `StringBase<char>`, not
by `Rva00415AA0`. Snapshot-specific corrections document both findings without
preserving a contradicted string identity or guessing a Drawable method name.
