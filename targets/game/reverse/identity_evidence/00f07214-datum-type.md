# Datum identity at VA 0x01307214

The selected spelling is `?g_bfmeCurrentCZ@@3VBfmeHandleCX@@A`. One four-byte BfmeHandleCX object containing a reference-counted texture pointer. It is neither a TextureBaseClass object nor a second separately owned object pointer.

Dynamic initializer RVA 00C6C660 supplies the address of this cell as ECX to ILT RVA 000110D6, whose E9 bytes route to RVA 0044F3C0, a null-handle initializer, and registers teardown RVA 00C70B40. The teardown E9 chain reaches VA 0045CC00 (RVA 0005CC00), as the raw five-byte E9 chain in retail-detail.log records. Getter RVA 007CC3F0 copies the cell into its hidden return object and increments the pointed-to 16-bit reference count at offset 4. Cross-fade init RVA 007D3760 binds an exmask_g.tga handle, releases the prior pointed-to texture, and stores the new pointer. The peek helper at RVA 0090DC60 loads the pointer from its receiver before examining the texture. The existing getter spells this four-byte counted object BfmeHandleCX. Its canonical definition is trivial storage in the existing manual initializer TU, so it adds no initializer or destructor body.

The datum is one element, 4 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x01307214 ?TheBfmeObject_00C70B40@@3VGen_00C70B40Target@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x01307214 ?g_bfmeCurrentCZ@@3VBfmeHandleCX@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x01307214 ?g_bfmeCurrentCZ@@3VGen_0044f3c0@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x01307214 ?g_bfmeCurrentCZ@@3VShroudTexture@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x01307214 ?g_bfmeCurrentCZ@@3VTextureBaseClass@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x01307214 ?g_bfmeObjUDC@@3PAVBfmeSrcUDC@@A DIRECT_GAME_DECLARING_FILES 1`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-detail.log`, `retail-handle.log`, `retail-crossfade-init.log`, `retail-accesses.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
