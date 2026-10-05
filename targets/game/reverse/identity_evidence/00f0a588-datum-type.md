# Datum identity at VA 0x0130A588

The selected spelling is `?gInstance@ServiceHubImpl@@2PAV1@A`. One initially null ServiceHubImpl pointer, the ServiceHubImpl::gInstance static singleton.

Retail factory RVA 007EB1C0 tests this cell and passes the EA assertion string !ServiceHubImpl::gInstance at VA 01129CB8 and the source string hubsingle.cpp at VA 01129CD4 to the diagnostic receiver. It allocates 0x2B0 bytes, invokes the already pinned ServiceHubImpl constructor RVA 007EAE30, and stores its returned pointer here. Teardown bodies RVAs 007EB270, 007EB2C0, and 007EB310 load the pointer as their destruction receiver and clear this cell. The next flags at VAs 0130A58C and 0130A58D are outside its four-byte range. Authored callers already use the EA-named singleton; none still declare any of the four g_Va0130A588 spellings.

The datum is one element, 4 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x0130A588 ?g_Va0130A588@@3HA DIRECT_GAME_DECLARING_FILES 0`
- `0x0130A588 ?g_Va0130A588@@3PAVServiceHubImpl@@A DIRECT_GAME_DECLARING_FILES 0`
- `0x0130A588 ?g_Va0130A588@@3PAVT_007ea120@@A DIRECT_GAME_DECLARING_FILES 0`
- `0x0130A588 ?g_Va0130A588@@3URva0130A588State@@A DIRECT_GAME_DECLARING_FILES 0`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-service-factory.log`, `retail-detail.log`, `retail-accesses.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
