# Datum identity at VA 0x012F9D8C

The selected spelling is `?m_needUpdate@W3DStatusCircle@@1_NA`. One initially false Bool flag, occupying one byte.

Retail setColor RVA 006FB4D0 and W3DGameClient::setTeamColor RVA 006FBD00 write byte value 1 here. Status-circle initData RVA 00725C00 sets the byte; updateScreenVB RVA 00725DE0 and updateCircleVB RVA 007260F0 clear it. Render RVA 00726290 reads one byte before updating vertex data. The Zero Hour W3DStatusCircle.cpp defines Bool W3DStatusCircle::m_needUpdate, and W3DStatusCircle.h declares this static flag and sets it from setColor. The existing owner already defines the correct spelling.

The datum is one element, 1 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x012F9D8C ?g_w3dStatusCircleNeedUpdate@@3_NA DIRECT_GAME_DECLARING_FILES 1`
- `0x012F9D8C ?m_needUpdate@W3DStatusCircle@@1_NA DIRECT_GAME_DECLARING_FILES 1`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-status-color.log`, `retail-accesses.log`, `reference-specific.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
