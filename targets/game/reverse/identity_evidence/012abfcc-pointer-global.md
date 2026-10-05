# rva0010e580MapsCode at VA 0x012ABFCC

The correction consolidates this datum under `rva0010e580MapsCode` with type `const char *`. Retail owns 4 bytes in `.data` with initial value 0x0108928C ("M"). The image has no PE base relocation directory; initialized pointer relocation targets are read from the retail dword and verified by add_data_match against the compiled initializer.

rva0010e580MapsCode and rva0010f820MapCode each occur in one defining game file. Retail RVAs 0x0010E580 and 0x0010F820 load the same cell. The former compares the compact token and expands it to PORTABLE_MAPS; the latter writes that token into the compact result. These are inverse path transforms. Zero Hour GameState.cpp declares PORTABLE_MAPS at line 868 and the inverse transforms below it, but does not declare the BFME compact token. The existing role-describing spelling is retained.

The datum has no function receiver or arguments. Its consumer contract is the direct cell or array access shown in the raw retail log; the pointee or element type above is shared by its declarations. No executable instruction is intentionally changed.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012abfcc.log`, `cells-and-declarations.log`, `retail-xrefs.log` and `xref-bodies.json` in the same folder. These record every detected instruction reference, its containing retail boundary, and each observed E9 jump chain. No instruction writer was found for the initialized token/prefix/table cells; timed-operation head writes are recorded directly. The four-byte cells contain no other DIR32 start or existing data row inside their range.

A changed cell width, a different initializer target/string, a reference into the middle indicating another datum, a differing compiled instruction, or a thunk reaching a different node body would refute this correction. A stronger independent declaration could settle a more specific original spelling, without changing the established role.
