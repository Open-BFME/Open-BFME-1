# Datum identity at VA 0x012F9D14

The selected spelling is `?m_resource012F9D14@W3DShaderManager@@1PAUShaderComResource@@A`. One initially null COM pixel-shader pointer. The ShaderComResource type is the existing structural COM view, with the interface vptr at offset zero; the original BFME member name is unknown and remains address qualified.

Retail init RVA 00718E90 passes this cell to the loader together with the EA string shaders\Glow.pso at VA 01120D08. Retail RVA 00719090 loads this cell and supplies the value to device vtable offset 0x1AC. Shutdown RVA 00717DA0 calls interface vtable offset 8 and clears the cell. Constructor RVA 007165C0 also clears it.

The datum is one element, 4 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x012F9D14 ?m_resource012F9D14@W3DShaderManager@@1PAUShaderComResource@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x012F9D14 ?rva012F9D14@@3PAXA DIRECT_GAME_DECLARING_FILES 1`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-shader-init.log`, `retail-shader-use.log`, `retail-shader-shutdown.log`, `retail-detail.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
