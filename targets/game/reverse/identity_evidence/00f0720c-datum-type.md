# Datum identity at VA 0x0130720C

The selected spelling is `?m_curFadeFrame@ScreenCrossFadeFilter@@1HA`. One initially zero signed 32-bit Int current fade frame.

Retail setters RVAs 0073A8D0 and 0073B540 reset it. Update RVA 007D35B0 increments it, uses it as an integer fade numerator, and clears it on completion. Cross-fade init RVA 007D3760 also resets it. The Zero Hour source defines Int ScreenCrossFadeFilter::m_curFadeFrame; the reference header declares the protected static member. The shim static spellings select a different class or access category and are not another datum.

The datum is one element, 4 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x0130720C ?R2Glob0130720C@@3HA DIRECT_GAME_DECLARING_FILES 1`
- `0x0130720C ?m_curFadeFrame@ScreenCrossFadeFilter@@1HA DIRECT_GAME_DECLARING_FILES 2`
- `0x0130720C ?m_curFadeFrame@ScreenCrossFadeFilterUpdateFadeLevelShim@@0HA DIRECT_GAME_DECLARING_FILES 0`
- `0x0130720C ?m_curFadeFrame@ScreenCrossFadeFilterUpdateFadeLevelShim@@2HA DIRECT_GAME_DECLARING_FILES 1`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-fade-update.log`, `retail-crossfade-init.log`, `retail-accesses.log`, `reference-specific.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
