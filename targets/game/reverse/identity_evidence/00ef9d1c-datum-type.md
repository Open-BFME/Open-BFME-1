# Datum identity at VA 0x012F9D1C

The selected spelling is `?ShaderQuadBuffer@@3PAVVertexBufferClass@@A`. One initially null VertexBufferClass pointer, whose live allocation is the 32-byte DX8VertexBufferClass variant. This is a pointer cell, not an embedded vertex buffer.

Retail resource creator RVA 00716770 allocates 0x20 bytes and calls the DX8 vertex-buffer constructor at RVA 0091F2F0 with FVF 0x144, 200 vertices, dynamic usage 1, and vertex size 0, then stores the returned pointer here. Renderers RVAs 00716AD0 and 00716F50 use this buffer for quad append locks and stream setup. Resource release RVA 00717C90 and shutdown RVA 00717DA0 decrement the pointee reference count at offset 4, call its first virtual slot at zero references, and clear this cell. Constructor RVA 007165C0 clears it.

The datum is one element, 4 bytes, in retail `.data` virtual storage. Its initial bytes are all zero, with no initial pointer relocations. `retail-inventory.log` records the PE section boundaries, zero bytes, exact address references, nearby DIR32 names and data rows. `range-check.log` checks the selected exact extent against every existing data row and every DIR32 address. This is writable storage, not a compiler constant.

The caller and receiver contract follows the retail operations above. Interface globals store pointers and COM Release receives the loaded pointee; object initializers and destructors receive the datum address in ECX. Declaration changes retain the existing TU-local operation views where needed. Function names, calling conventions, bodies and verified extents remain unchanged. Existing pins and DIR32 spellings are retained.

The pre-edit direct game declaration counts are reproducible with `declarations.py`; reference-header-only declarations are excluded. Counts are attached to their exact decorated spellings below.

- `0x012F9D1C ?ShaderQuadBuffer@@3PAVVertexBufferClass@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x012F9D1C ?m_vertexBuffer012F9D1C@W3DShaderManager@@1PAVShaderVertexBuffer@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x012F9D1C ?rva012F9D1C@@3PAVBfmeDX8VertexBuffer@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x012F9D1C ?rva012F9D1C@@3PAVShaderVertexBufferRef@@A DIRECT_GAME_DECLARING_FILES 1`
- `0x012F9D1C ?rva012F9D1C@@3PAXA DIRECT_GAME_DECLARING_FILES 1`

Raw evidence is under `build/rlink/identity-data-15-1791202276/`: `retail-detail.log`, `retail-accesses.log`, `data-contract-sources.log`, `retail-inventory.log`, `declaration-counts.log`, and `range-check.log`. Source and data gates are recorded there and in `build/worker-final.md`.

A retail caller routed through a different final thunk target, a different access width, an access requiring storage beyond this exact extent, a conflicting independent datum within the range, or a source gate changing any verified instruction would refute this correction. For the EA-named fields, different reference declarations or retail behavior inconsistent with their stated role would also refute it.
