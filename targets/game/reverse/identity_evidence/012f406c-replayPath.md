# Datum identity at VA 0x012F406C

The conclusive spelling is `?replayPath@PopupReplayState@@3V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@A`. The datum is one `std::string (STLport narrow basic_string)` object, 12 bytes, in retail `.data`. It is not an array or a compiler constant. The element type is char, with a dynamic character count. The object consists of three pointer fields.

ZH PopupReplay.cpp declares std::string replayPath, assigns the full replay path and reads c_str in reallySaveReplay. Retail saveReplay at 004DE8E0 assigns receiver 012F406C through E9 0002B297 -> 000A5810; reallySaveReplay reads its first pointer. The CRT initializer at 00C6BB10 and registered teardown at 00C70180 use the same constructor and destructor as the other twelve-byte narrow strings. The BFME state owner already uses namespace PopupReplayState.

The datum is in the virtual, zero-filled tail of retail `.data`, beyond its raw file-backed extent. These are loader-initialized bytes before any CRT dynamic construction. The initial bytes are `00 00 00 00 00 00 00 00 00 00 00 00`. Every initial word is zero, so there are no initial pointer relocations inside the datum. Retail has no PE base-relocation directory. The compiled definition and its relocations are independently checked by add_data_match and the scoped data gate. No other data row intersects this extent, and no DIR32 name lies strictly inside it. All spellings at its start are listed below; declaration counts and matching lines are retained in `build/rlink/identity-15/declaration-counts.log`. Counts do not establish identity. The measurement includes matching TU-private declarations for unscoped names, and restricts namespace spellings to their namespace. The raw lines identify any homonymous menus.

- `?TheBfmeObject_00C70180@@3VGen_00C70180Target@@A`: 1 game file(s) declaring the spelling and type.
- `?replayPath@PopupReplayState@@3V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@A`: 3 game file(s) declaring the spelling and type.

The receiver and argument contract is established by the producer and consumer operations described above. This correction changes declarations, definitions or relocation spellings only. It preserves every verified function byte. No function identity is changed.

A non-path use of the assigned string, a different constructor extent, or a teardown that targets another slot would refute the identity.

Retail users, including initializers and teardown wrappers, appear in the raw disassembly log. Instructions label loads, stores and address-passing uses, and each E9 chain is decoded from its five retail bytes.

Raw evidence: `build/rlink/identity-15/012F406C-retail.log`, `build/rlink/identity-15/reference-uses.log`, `build/rlink/identity-15/reference-declarations.log`, `build/rlink/identity-15/extent-checks.log`, `build/rlink/identity-15/strings-and-sections.log`, `build/rlink/identity-15/data-reference-scan.log`, and the gate logs recorded in `build/worker-final.md`.
