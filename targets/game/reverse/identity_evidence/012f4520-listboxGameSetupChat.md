# Datum identity at VA 0x012F4520

The conclusive spelling is `?listboxGameSetupChat@@3PAVGameWindow@@A`. The datum is one `GameWindow *` object, 4 bytes, in retail `.data`. It is not an array or a compiler constant.

ZH WOLGameSetupMenu.cpp defines GameWindow *listboxGameSetupChat. Retail InitWOLGameGadgets resolves the GameSpy setup chat-window key and stores the window result at 008F306A. WOLGameSetupMenuShutdown reads this widget for text-window unregistration; the game-setup handlers pass it as their chat target. bfmeClearStateVJ clears the same dword at 008F098B.

The datum is in the virtual, zero-filled tail of retail `.data`, beyond its raw file-backed extent. These are loader-initialized bytes before any CRT dynamic construction. The initial bytes are `00 00 00 00`. Every initial word is zero, so there are no initial pointer relocations inside the datum. Retail has no PE base-relocation directory. The compiled definition and its relocations are independently checked by add_data_match and the scoped data gate. No other data row intersects this extent, and no DIR32 name lies strictly inside it. All spellings at its start are listed below; declaration counts and matching lines are retained in `build/rlink/identity-15/declaration-counts.log`. Counts do not establish identity. The measurement includes matching TU-private declarations for unscoped names, and restricts namespace spellings to their namespace. The raw lines identify any homonymous menus.

- `?g_bfmeState05VJ@@3HA`: 1 game file(s) declaring the spelling and type.
- `?listboxGameSetupChat@@3PAVGameWindow@@A`: 1 game file(s) declaring the spelling and type.

The receiver and argument contract is established by the producer and consumer operations described above. This correction changes declarations, definitions or relocation spellings only. It preserves every verified function byte. No function identity is changed.

A different gadget ID feeding this store or an arithmetic-only use contradicting the chat-window calls would refute the correction.

Retail users, including initializers and teardown wrappers, appear in the raw disassembly log. Instructions label loads, stores and address-passing uses, and each E9 chain is decoded from its five retail bytes.

Raw evidence: `build/rlink/identity-15/012F4520-retail.log`, `build/rlink/identity-15/reference-uses.log`, `build/rlink/identity-15/reference-declarations.log`, `build/rlink/identity-15/extent-checks.log`, `build/rlink/identity-15/strings-and-sections.log`, `build/rlink/identity-15/data-reference-scan.log`, and the gate logs recorded in `build/worker-final.md`.
