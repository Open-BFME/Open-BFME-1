# Datum identity at VA 0x012F463C

The conclusive spelling is `?TheLobbyQueuedUTMs@@3V?$list@VPeerResponse@@V?$allocator@VPeerResponse@@@_STL@@@_STL@@A`. The datum is one `std::list<PeerResponse> (STLport)` object, 4 bytes, in retail `.data`. It is not an array or a compiler constant. The element type is PeerResponse, with a dynamic node count. Construction produces an empty list whose only object field is its sentinel pointer.

ZH WOLLobbyMenu.cpp defines std::list<PeerResponse> TheLobbyQueuedUTMs and uses clear/push_back; WOLGameSetupMenu.cpp consumes front/pop_front. Retail WOLGameSetupMenuUpdate reads its sentinel and compares the first node against it. Lobby response paths clear or append using receiver 012F463C. CRT initializer 00C6BB50 calls E9 00039022 -> 004FD8A0: the constructor writes only [this], allocates a 0x338-byte node, and links the first two words to itself. Teardown 00C701A0 follows E9 0003C4CA -> 004FD8D0: clear, load sentinel [this], delete sentinel.

The datum is in the virtual, zero-filled tail of retail `.data`, beyond its raw file-backed extent. These are loader-initialized bytes before any CRT dynamic construction. The initial bytes are `00 00 00 00`. Every initial word is zero, so there are no initial pointer relocations inside the datum. Retail has no PE base-relocation directory. The compiled definition and its relocations are independently checked by add_data_match and the scoped data gate. No other data row intersects this extent, and no DIR32 name lies strictly inside it. All spellings at its start are listed below; declaration counts and matching lines are retained in `build/rlink/identity-15/declaration-counts.log`. Counts do not establish identity. The measurement includes matching TU-private declarations for unscoped names, and restricts namespace spellings to their namespace. The raw lines identify any homonymous menus.

- `?TheBfmeObject_00C701A0@@3VGen_00C701A0Target@@A`: 1 game file(s) declaring the spelling and type.
- `?TheLobbyQueuedUTMs@@3V?$list@VPeerResponse@@V?$allocator@VPeerResponse@@@_STL@@@_STL@@A`: 4 game file(s) declaring the spelling and type.

The receiver and argument contract is established by the producer and consumer operations described above. This correction changes declarations, definitions or relocation spellings only. It preserves every verified function byte. No function identity is changed.

A second object field in the constructor, a node payload incompatible with PeerResponse, or a queue consumer operating on another slot would refute this identity.

Retail users, including initializers and teardown wrappers, appear in the raw disassembly log. Instructions label loads, stores and address-passing uses, and each E9 chain is decoded from its five retail bytes.

Raw evidence: `build/rlink/identity-15/012F463C-retail.log`, `build/rlink/identity-15/reference-uses.log`, `build/rlink/identity-15/reference-declarations.log`, `build/rlink/identity-15/extent-checks.log`, `build/rlink/identity-15/strings-and-sections.log`, `build/rlink/identity-15/data-reference-scan.log`, and the gate logs recorded in `build/worker-final.md`.

The teardown keeps the existing opaque callee `Gen_00C701A0Target::bfmeForward` at ILT RVA `0x0003C4CA`, called through a receiver cast from the address of the correctly declared `TheLobbyQueuedUTMs`. This is the same preexisting niladic member-call ABI and E9 target. It does not claim that the datum has that opaque callee-view type. No pin is added or changed. The final target, RVA `0x004FD8D0`, already has an opaque ledger row whose object-symbol view names `_List_base<QueuedDownload>`. The datum evidence establishes a `list<PeerResponse>`, but does not settle the exact destructor function identity against that competing view. The conflict is recorded in `build/rlink/identity-15/list-destructor-existing-claims.log` and is separate work.
