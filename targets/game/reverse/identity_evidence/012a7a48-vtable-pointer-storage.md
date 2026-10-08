# Pointer storage at VA 0x012A7A48

The existing `?RvaGlobal012A7A48@@3PAIA` spelling denotes the four-byte vtable-pointer cell at VA 0x012A7A48, RVA 0x00EA7A48. Its retail `.data` bytes are `dc c7 07 01`, an initialized pointer to VA 0x0107C7DC. Retail's base-relocation directory is stripped, but the final section retains the original linker blocks. tools/retail_relocs.py confirms the HIGHLOW entry for this cell, the pointee's one slot, both startup-store address fields and the loader's immediate address field. The proposed COFF definition supplies one DIR32 fixup to the existing vtable spelling and the data gate reproduces every initial byte. This records the pointer cell rather than assigning a guessed class or array extent to the surrounding object. The adjacent cell at VA 0x012A7A4C holds the list head and is outside this four-byte datum.

Retail facts

Retail VA 0x0106FCC0 is the complete 11-byte callback `c7 05 48 7a 2a 01 dc c7 07 01 c3`; it writes the same vtable pointer to this cell and returns. Retail VA 0x0106AA40 writes VA 0x012A7A4C to the separate list-head pointer at VA 0x012ED5DC. The loader at VA 0x00B4ACB0 passes the address of VA 0x012A7A48, rather than loading that cell as a heap-object pointer. Its ObjectsList constructor stores this context at receiver offset 0x0C.

The complete pointee is the one-slot vtable at VA 0x0107C7DC: `bc 3d 42 00`. Its five-byte ILT entry at VA 0x00423DBC is `e9 af 35 06 00`, which reaches VA 0x00487370. That complete scalar deleting destructor restores this vtable, conditionally calls delete when argument bit 0 is set, returns the receiver in EAX and uses RET 4. The next dword at VA 0x0107C7E0 is a different vtable, proven by the MapObject constructor at VA 0x00488160 and destructor at RVA 0x00088350. The existing DIR32 identity `??_7Rva00087320@@6B@` supplies the pointer initializer; no raw address, new vtable identity or pin is introduced.

Receiver and argument contract

ObjectsList dispatch slot 1 at VA 0x0107C814 follows ILT VA 0x004167E8 to VA 0x00489060. That body reads the context at receiver offset 0x0C and passes it to the per-object registration constructor through ILT VA 0x004120C1. Its dispatch slot 1 follows ILT VA 0x004039CC to VA 0x00488F10, which calls the object parser through ILT VA 0x00426823, then writes the returned node into the previous context offset 4 and retains the new node. The object parser at VA 0x00488B70 allocates 0x60 bytes and calls the MapObject constructor through ILT VA 0x0041230A. Cleanup at VA 0x00B46E90 loads the separate pointer at VA 0x012ED5DC, deletes its head through the head vtable, and zeros the head cell. This distinguishes the vtable-pointer cell from the adjacent mutable list head and from an inline integer array. The Zero Hour WorldHeightMap.cpp ObjectsList registration and freeListOfMapObjects provide the reference role; retail supplies BFME’s changed layout.

Spellings and scope

Before the repair, `RvaGlobal012A7A48` and `g_Va012A7A48` were each declared in one game source. After the repair, `RvaGlobal012A7A48` is declared in both scoped sources; the existing `g_Va012A7A48` declaration remains in the map loader. Before the repair, neither spelling had a ledger owner at this VA. The full current COFF scan finds only those two actual source consumers, one DIR32 reference each. The ordinary identifiers and explanatory comments are retained. The loader references `&RvaGlobal012A7A48` with the recorded pointer type; a blank declaration line is reused so the original line positions remain unchanged. Its original char-array declaration remains present and contributes no compiled relocation. A genuine four-byte definition under the exact existing decorated spelling is appended to the startup source. No other datum or DIR32 identity lies inside [0x012A7A48, 0x012A7A4C).

Verification

The unchanged official pass test succeeds and deletes only the served VA 0x012A7A48 exemption. The subsequent all-user build verifies all 12 rows across the four assigned sources. `coff-preservation-whole.log` compares complete CODE sections, relocation kinds and resolved targets, original readonly and RTTI data payloads, every compiler `.xdata$x` EH table, and the decoded SafeSEH handler. The only changed compiler-local EH spelling is `$T1656` to `$T1657`; both identify the same fourth `.xdata$x` section at offset 152, with the same complete payload and graph edges (`coff-differences.log`). The decoded handler is retail VA 0x0104DFA0 and its FuncInfo is VA 0x0123DAF0 (`safeseh-retail-handler.log`). No original pin, function row or source line position is changed.

Raw evidence

All outputs and original same-path sources and complete objects are in `build/rlink/identity-012a7a48-012b2c98-1791448188/`. Retail evidence is `retail-probe-initial.log`, `extent-proof.log`, `routes-first.log`, `routes-parser-producers.log`, `routes-object-consumer.log`, `routes-object-allocation.log` and `routes-list-setup-cleanup.log`. Scope evidence is `spellings.log`, `spellings-broader.log` and `all-coff-users.log`. Original object receipts are in `object-save.log`; the source and byte gate is `build-original-all.log`.

Refutation

An overlapping owner inside the four-byte cell, another actual COFF consumer outside the two scoped sources, an initial byte other than `dc c7 07 01`, a pointer fixup to another vtable, or a thunk chain reaching another destructor would refute this record. Any changed original CODE section, relocation kind or resolved target, readonly payload, recursive EH graph or decoded SafeSEH handler would reject the candidate. The neighboring list-head cell is not claimed by this record.
