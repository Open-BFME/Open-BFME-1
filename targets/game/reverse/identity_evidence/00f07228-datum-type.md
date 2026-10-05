# Datum identity at VA 0x01307228

The selected spelling is `?Rva007D6B70Instance01307228@@3VRva007D6B70@@A`. One 72-byte Rva007D6B70 filter instance. It contains its vptr and seventeen initialized dwords, including a three-pointer POD sample vector. Its original EA class name is unknown.

Dynamic initializer RVA 00C6C680 sets ECX to VA 01307228 and calls ILT RVA 0002821D, which jumps to constructor RVA 007D6B70. The constructor installs vtable VA 01128B24 and clears every dword from offsets 4 through 0x44. The existing full init declaration has exactly this 0x48-byte layout. Init RVA 007D65E0 publishes this instance address to filter slot VA 012F9CEC. Atexit forwarder RVA 00C70B50 takes this same receiver address and its E9 chain reaches destructor RVA 007D6AB0. The former initializer storage declaration was only 0x34 bytes, too small for the witnessed writes, and is retyped to 0x48 bytes. The next named filter instance is at VA 01307284, outside this object.

The datum is one element, 72 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x01307228 ?Rva007D6B70Instance01307228@@3VRva007D6B70@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x01307228 ?TheBfmeObject_00C70B50@@3VGen_00C70B50Target@@A DIRECT_GAME_DECLARING_FILES 1`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-detail.log`, `retail-filter-constructors.log`, `filter-layout-sources.log`, `retail-accesses.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
