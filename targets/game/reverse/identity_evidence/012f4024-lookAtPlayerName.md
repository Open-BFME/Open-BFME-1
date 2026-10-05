# Datum identity at VA 0x012F4024

The conclusive spelling is `?lookAtPlayerName@@3V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@A`. The datum is one `std::string (STLport narrow basic_string)` object, 12 bytes, in retail `.data`. It is not an array or a compiler constant. The element type is char, with a dynamic character count. The object consists of three pointer fields.

ZH PopupPlayerInfo.cpp declares std::string lookAtPlayerName and SetLookAtPlayer assigns nick.str(). Retail SetLookAtPlayer at 004DBB50 supplies receiver 012F4024 to string assign via E9 0002B297 -> 000A5810. PopulatePlayerInfoWindows reads the first pointer as c_str. The CRT constructor at 00C6BAF0 calls E9 0004048A -> 004D4F40, which initializes the three pointer words at +0,+4,+8. Teardown 00C70170 calls E9 0001642D -> 000A5120.

The datum is in the virtual, zero-filled tail of retail `.data`, beyond its raw file-backed extent. These are loader-initialized bytes before any CRT dynamic construction. The initial bytes are `00 00 00 00 00 00 00 00 00 00 00 00`. Every initial word is zero, so there are no initial pointer relocations inside the datum. Retail has no PE base-relocation directory. The compiled definition and its relocations are independently checked by add_data_match and the scoped data gate. No other data row intersects this extent, and no DIR32 name lies strictly inside it. All spellings at its start are listed below; declaration counts and matching lines are retained in `build/rlink/identity-15/declaration-counts.log`. Counts do not establish identity. The measurement includes matching TU-private declarations for unscoped names, and restricts namespace spellings to their namespace. The raw lines identify any homonymous menus.

- `?TheBfmeObject_00C70170@@3VGen_00C70170Target@@A`: 1 game file(s) declaring the spelling and type.
- `?lookAtPlayerName@@3V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@A`: 3 game file(s) declaring the spelling and type.

The receiver and argument contract is established by the producer and consumer operations described above. This correction changes declarations, definitions or relocation spellings only. It preserves every verified function byte. No function identity is changed.

A constructor touching another word, non-narrow string assignment, or a destructor chain targeting another object type would refute this identity.

Retail users, including initializers and teardown wrappers, appear in the raw disassembly log. Instructions label loads, stores and address-passing uses, and each E9 chain is decoded from its five retail bytes.

Raw evidence: `build/rlink/identity-15/012F4024-retail.log`, `build/rlink/identity-15/reference-uses.log`, `build/rlink/identity-15/reference-declarations.log`, `build/rlink/identity-15/extent-checks.log`, `build/rlink/identity-15/strings-and-sections.log`, `build/rlink/identity-15/data-reference-scan.log`, and the gate logs recorded in `build/worker-final.md`.
