# g_timedOperationHead at VA 0x012ED584

The correction consolidates this datum under `g_timedOperationHead` with type `TimedOperationNode *`. Retail owns 4 bytes in `.data` with initial value 0. The image has no PE base relocation directory; initialized pointer relocation targets are read from the retail dword and verified by add_data_match against the compiled initializer.

g_bfmeListCK is declared by one game file; g_timedOperationHead by three. Retail RVA 0x0007BA90 allocates 0x18 bytes, initializes next at +4 and key at +0x14, and stores the first node into this cell. RVAs 0x0007B5F0 and 0x0007B720 traverse that next field and compare the same key. RVA 0x0007B990 calls ILT VA 0x00410DDE (e9 fd aa 06 00), which jumps to VA 0x0047B8E0. symbols.csv independently pins update@TimedOperationNode at RVA 0x0007B8E0 and the descriptive head spelling at RVA 0x00EED584. The pump advances the same head and invokes the node deleting destructor. The opaque BfmeEntryCK view remains local, with explicit casts at its use sites.

The datum has no function receiver or arguments. Its consumer contract is the direct cell or array access shown in the raw retail log; the pointee or element type above is shared by its declarations. No executable instruction is intentionally changed.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-012ed584.log`, `cells-and-declarations.log`, `retail-xrefs.log` and `xref-bodies.json` in the same folder. These record every detected instruction reference, its containing retail boundary, and each observed E9 jump chain. No instruction writer was found for the initialized token/prefix/table cells; timed-operation head writes are recorded directly. The four-byte cells contain no other DIR32 start or existing data row inside their range.

A changed cell width, a different initializer target/string, a reference into the middle indicating another datum, a differing compiled instruction, or a thunk reaching a different node body would refute this correction. A stronger independent declaration could settle a more specific original spelling, without changing the established role.
