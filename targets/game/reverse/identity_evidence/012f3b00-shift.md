# Datum identity at VA 0x012F3B00

The conclusive spelling is `?shift@@3VUnicodeString@@A`. The datum is one `UnicodeString` object, 4 bytes, in retail `.data`. It is not an array or a compiler constant. The character element type is a 16-bit Unicode code unit, with a dynamic text length. The object holds one shared-buffer pointer.

KeyboardOptionsMenu.cpp declares shift. Retail KeyboardOptionsMenuInit assigns the fetched modifier text to receiver 012F3B00. Modifier key handlers copy and compare that UnicodeString. Its CRT initializer at RVA 00C6BAB0 uses constructor thunk 00041C95 -> 00083D10 and registers destructor wrapper 00C70150. That wrapper follows E9 0003B304 -> 0005EEA0 -> 008881D0. The authentic vector destructor uses four-byte UnicodeString elements.

The datum is in the virtual, zero-filled tail of retail `.data`, beyond its raw file-backed extent. These are loader-initialized bytes before any CRT dynamic construction. The initial bytes are `00 00 00 00`. Every initial word is zero, so there are no initial pointer relocations inside the datum. Retail has no PE base-relocation directory. The compiled definition and its relocations are independently checked by add_data_match and the scoped data gate. No other data row intersects this extent, and no DIR32 name lies strictly inside it. All spellings at its start are listed below; declaration counts and matching lines are retained in `build/rlink/identity-15/declaration-counts.log`. Counts do not establish identity. The measurement includes matching TU-private declarations for unscoped names, and restricts namespace spellings to their namespace. The raw lines identify any homonymous menus.

- `?TheBfmeObject_00C70150@@3VGen_00C70150Target@@A`: 1 game file(s) declaring the spelling and type.
- `?shift@@3VUnicodeString@@A`: 3 game file(s) declaring the spelling and type.

The receiver and argument contract is established by the producer and consumer operations described above. This correction changes declarations, definitions or relocation spellings only. It preserves every verified function byte. No function identity is changed.

A different modifier string assigned to this slot, a constructor using more than four bytes, or an E9 chain ending outside the UnicodeString teardown would refute this identity.

Retail users, including initializers and teardown wrappers, appear in the raw disassembly log. Instructions label loads, stores and address-passing uses, and each E9 chain is decoded from its five retail bytes.

Raw evidence: `build/rlink/identity-15/012F3B00-retail.log`, `build/rlink/identity-15/reference-uses.log`, `build/rlink/identity-15/reference-declarations.log`, `build/rlink/identity-15/extent-checks.log`, `build/rlink/identity-15/strings-and-sections.log`, `build/rlink/identity-15/data-reference-scan.log`, and the gate logs recorded in `build/worker-final.md`.

The retail fetched key is `KEYBOARD:Shift+` at VA `0x010FEF74`. The four-byte element size is independently present in the vector destructor at RVA `0x0048D3F0`, saved in `build/rlink/identity-15/unicode-element-size.log`.
