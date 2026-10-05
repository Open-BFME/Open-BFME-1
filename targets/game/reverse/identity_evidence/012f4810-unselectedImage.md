# Datum identity at VA 0x012F4810

The conclusive spelling is `?unselectedImage@@3PBVImage@@B`. The datum is one `const Image *` object, 4 bytes, in retail `.data`. It is not an array or a compiler constant.

ZH WOLQuickMatchMenu.cpp declares const Image *unselectedImage and initializes it from CustomMatch_deselected. Retail initGadgets at 005091F0 calls the image lookup for that EA string and stores EAX in 012F4810. The native system handler chooses it for the opposite map-selection state and reads Image data at +0x24. Retail teardown clears it. The volatile GameWindow pointer parentWOLQuickMatch spelling describes another role.

The datum is in the virtual, zero-filled tail of retail `.data`, beyond its raw file-backed extent. These are loader-initialized bytes before any CRT dynamic construction. The initial bytes are `00 00 00 00`. Every initial word is zero, so there are no initial pointer relocations inside the datum. Retail has no PE base-relocation directory. The compiled definition and its relocations are independently checked by add_data_match and the scoped data gate. No other data row intersects this extent, and no DIR32 name lies strictly inside it. All spellings at its start are listed below; declaration counts and matching lines are retained in `build/rlink/identity-15/declaration-counts.log`. Counts do not establish identity. The measurement includes matching TU-private declarations for unscoped names, and restricts namespace spellings to their namespace. The raw lines identify any homonymous menus.

- `?parentWOLQuickMatch@@3RAVGameWindow@@A`: 1 game file(s) declaring the spelling and type.
- `?rva012F4810UnselectedImage@@3PBVImage@@B`: 2 game file(s) declaring the spelling and type.
- `?unselectedImage@@3PBVImage@@B`: 2 game file(s) declaring the spelling and type.

The receiver and argument contract is established by the producer and consumer operations described above. This correction changes declarations, definitions or relocation spellings only. It preserves every verified function byte. No function identity is changed.

A different lookup string, reversed selection-state branches or receiver accesses incompatible with Image would refute the identity.

Retail users, including initializers and teardown wrappers, appear in the raw disassembly log. Instructions label loads, stores and address-passing uses, and each E9 chain is decoded from its five retail bytes.

Raw evidence: `build/rlink/identity-15/012F4810-retail.log`, `build/rlink/identity-15/reference-uses.log`, `build/rlink/identity-15/reference-declarations.log`, `build/rlink/identity-15/extent-checks.log`, `build/rlink/identity-15/strings-and-sections.log`, `build/rlink/identity-15/data-reference-scan.log`, and the gate logs recorded in `build/worker-final.md`.

The teardown declarations use the canonical non-volatile pointer spelling. Its existing volatile dword writes are preserved through a volatile lvalue cast at each store. The source gate proves that these retyped accesses retain the same instructions.
