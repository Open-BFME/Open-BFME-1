# g_bfmeTableBZ at VA 0x01141708

The correction consolidates this datum under `g_bfmeTableBZ` with type `const unsigned [64]`. Retail owns 256 bytes in `.rdata` with initial value 64 verified unsigned integers. The image has no PE base relocation directory; initialized pointer relocation targets are read from the retail dword and verified by add_data_match against the compiled initializer.

g_Rva01141708 is declared in two game files and g_bfmeTableBZ in one. This is a 256-byte .rdata array, not a pointer global. RVA 0x009A65E0 copies all 64 dwords; RVA 0x009A6630 reads each low word with a four-byte stride, and RVA 0x009A6780 uses four-byte indexed loads for quantizer construction. The next table starts at VA 0x01141808. quantizer-values.log verifies every entry and absence of interior DIR32 names or existing data rows. The scalar values are direct integer operands, not relocated pointers. No Zero Hour twin was found. The existing table spelling is retained, and all users declare its const unsigned element type.

The datum has no function receiver or arguments. Its consumer contract is the direct cell or array access shown in the raw retail log; the pointee or element type above is shared by its declarations. No executable instruction is intentionally changed.

Raw evidence is `build/rlink/pointer-globals-20261005/retail-01141708.log`, `cells-and-declarations.log`, `retail-xrefs.log` and `xref-bodies.json` in the same folder. These record every detected instruction reference, its containing retail boundary, and each observed E9 jump chain. No instruction writer was found for the initialized token/prefix/table cells; timed-operation head writes are recorded directly. The four-byte cells contain no other DIR32 start or existing data row inside their range.

A changed cell width, a different initializer target/string, a reference into the middle indicating another datum, a differing compiled instruction, or a thunk reaching a different node body would refute this correction. A stronger independent declaration could settle a more specific original spelling, without changing the established role.
