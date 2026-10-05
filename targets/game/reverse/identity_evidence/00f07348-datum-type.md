# Datum identity at VA 0x01307348

The selected spelling is `?RingFilterObject@@3VRva007DB820@@A`. One 84-byte Rva007DB820 filter instance, with a vptr and twenty initialized dwords including two three-pointer sample vectors. RingFilterObject retains the existing confirmed ring-filter role; it is not a char.

Dynamic initializer RVA 00C6C710 sets ECX to VA 01307348 and calls ILT RVA 0000281F, which jumps to constructor RVA 007DB820. The constructor installs vtable VA 01128C0C and clears every dword at offsets 4 through 0x50. The full init declaration has exactly this 0x54-byte layout and loads ring.nvp, ring1.nvp, ring2.nvp and EXVapor textures. Init RVA 007DB1F0 publishes this instance address at VA 012F9CE8. Atexit forwarder RVA 00C70BA0 uses the same receiver and routes through its E9 thunk to destructor RVA 007DB700. The next named datum at VA 013073B4 is outside the object.

The datum is one element, 84 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x01307348 ?RingFilterObject@@3DA DIRECT_GAME_DECLARING_FILES 1`
- `0x01307348 ?TheBfmeObject_00C70BA0@@3VGen_00C70BA0Target@@A DIRECT_GAME_DECLARING_FILES 1`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-detail.log`, `retail-filter-constructors.log`, `filter-layout-sources.log`, `retail-accesses.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
