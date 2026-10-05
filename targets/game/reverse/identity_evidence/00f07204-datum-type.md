# Datum identity at VA 0x01307204

The selected spelling is `?m_fadeDirection@ScreenCrossFadeFilter@@1HA`. One initially zero signed 32-bit Int fade direction.

Retail setters RVAs 0073A8D0 and 0073B540 write the second fade parameter here. Update RVA 007D35B0 tests this cell with signed positive and negative branches and clears it when fading finishes. The Zero Hour W3DShaderManager.cpp defines Int ScreenCrossFadeFilter::m_fadeDirection and uses the same signed direction contract. The reference header declares this protected static Int.

The datum is one element, 4 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x01307204 ?R2Glob01307204@@3HA DIRECT_GAME_DECLARING_FILES 1`
- `0x01307204 ?m_fadeDirection@ScreenCrossFadeFilter@@1HA DIRECT_GAME_DECLARING_FILES 2`
- `0x01307204 ?m_fadeDirection@ScreenCrossFadeFilterUpdateFadeLevelShim@@0HA DIRECT_GAME_DECLARING_FILES 0`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-fade-update.log`, `retail-accesses.log`, `reference-specific.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
