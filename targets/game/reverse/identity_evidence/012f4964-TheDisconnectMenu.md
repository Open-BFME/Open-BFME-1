# Datum identity at VA 0x012F4964

The conclusive spelling is `?TheDisconnectMenu@@3PAVDisconnectMenu@@A`. The datum is one `DisconnectMenu * (BFME APT implementation)` object, 4 bytes, in retail `.data`. It is not an array or a compiler constant.

ZH DisconnectMenu.h declares extern DisconnectMenu *TheDisconnectMenu. Existing symbols.csv pins that name at this VA. Retail BfmeAptScreenDisconnectScreen constructor at 0050F990 stores its primary this pointer; destructor at 0050EA10 compares it with this and clears it. ConnectionManager::processDisconnectChat at 006655C0 loads it as the menu receiver. Getter Rva004C1090Get returns the same pointer bits as an int.

The datum is in the virtual, zero-filled tail of retail `.data`, beyond its raw file-backed extent. These are loader-initialized bytes before any CRT dynamic construction. The initial bytes are `00 00 00 00`. Every initial word is zero, so there are no initial pointer relocations inside the datum. Retail has no PE base-relocation directory. The compiled definition and its relocations are independently checked by add_data_match and the scoped data gate. No other data row intersects this extent, and no DIR32 name lies strictly inside it. All spellings at its start are listed below; declaration counts and matching lines are retained in `build/rlink/identity-15/declaration-counts.log`. Counts do not establish identity. The measurement includes matching TU-private declarations for unscoped names, and restricts namespace spellings to their namespace. The raw lines identify any homonymous menus.

- `?TheDisconnectMenu@@3PAVDisconnectMenu@@A`: 8 game file(s) declaring the spelling and type.
- `?g_Va012F4964@@3HA`: 1 game file(s) declaring the spelling and type.

The receiver and argument contract is established by the producer and consumer operations described above. This correction changes declarations, definitions or relocation spellings only. It preserves every verified function byte. No function identity is changed.

A different object stored by the constructor, a pointer-adjustment discrepancy at the menu calls, or the existing pin mapping elsewhere would refute the correction.

Retail users, including initializers and teardown wrappers, appear in the raw disassembly log. Instructions label loads, stores and address-passing uses, and each E9 chain is decoded from its five retail bytes.

Raw evidence: `build/rlink/identity-15/012F4964-retail.log`, `build/rlink/identity-15/reference-uses.log`, `build/rlink/identity-15/reference-declarations.log`, `build/rlink/identity-15/extent-checks.log`, `build/rlink/identity-15/strings-and-sections.log`, `build/rlink/identity-15/data-reference-scan.log`, and the gate logs recorded in `build/worker-final.md`.
