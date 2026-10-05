# rva0010e580UserCode at VA 0x012ABFD0

The correction consolidates this datum under `rva0010e580UserCode` with type `const char *`. Retail owns 4 bytes in `.data` with initial value 0x01089288 ("U"). The image has no PE base relocation directory; initialized pointer relocation targets are read from the retail dword and verified by add_data_match against the compiled initializer.

rva0010e580UserCode and rva0010f820UserCode each occur in one defining game file. Both retail inverse transforms load this cell; the decoded path uses PORTABLE_USER_MAPS. Zero Hour GameState.cpp line 869 declares that path prefix. The compact token is BFME-specific, so the existing role-describing spelling is retained.

The datum has no function receiver or arguments. Its consumer contract is the direct cell or array access shown in the raw retail log; the pointee or element type above is shared by its declarations. No executable instruction is intentionally changed.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012abfd0.log`, `cells-and-declarations.log`, `retail-xrefs.log` and `xref-bodies.json` in the same folder. These record every detected instruction reference, its containing retail boundary, and each observed E9 jump chain. No instruction writer was found for the initialized token/prefix/table cells; timed-operation head writes are recorded directly. The four-byte cells contain no other DIR32 start or existing data row inside their range.

A changed cell width, a different initializer target/string, a reference into the middle indicating another datum, a differing compiled instruction, or a thunk reaching a different node body would refute this correction. A stronger independent declaration could settle a more specific original spelling, without changing the established role.
