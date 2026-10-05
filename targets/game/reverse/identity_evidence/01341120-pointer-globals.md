# Pointer-global identity at VA 0x01341120

Unresolved correction: this address is a member array of an existing datum.

## Retail facts and receiver contract

The storage is the two-element VertexBufferClass* array DX8Wrapper::render_state.vertex_buffers at offset 0x260, occupying 8 bytes. It is not a pointer to a separately allocated BfmeStateBQ singleton. Release_Device at RVA 0x00907B00 loops over two four-byte slots, releases engine references and ordinary references, and clears them. The D3D apply helper at RVA 0x00904BA0 reads the first slot and accesses the DX8 vertex buffer through its offsets 0x14 and 0x18. This is the same first vertex-buffer object viewed through an invented partial structure. Both slots lie inside the existing 624-byte render_state datum. No independent datum was added and this address was left unchanged.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 8 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/01341120-retail.log`. The containing bodies are VA 0x00D03C50, VA 0x00D043D0, VA 0x00D04510, VA 0x00D04660, VA 0x00D04890, VA 0x00D04BA0, VA 0x00D06B40, VA 0x00D07960, VA 0x00D07B00, VA 0x00D082B0, VA 0x00D08FE0, VA 0x00D3A810, VA 0x00D3B340. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

Rva01341120VertexBuffers has 1 declaration file and g_bfmeStateBQ has 1. The exact lists are in the raw logs.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

The existing render_state definition must own this storage; the apply helper should cast its first vertex-buffer member only where its ABI view differs. A native offsetof probe differing from 0x260, a third release-loop element, or evidence that a user stores a non-VertexBufferClass object would refute this identification.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.

The compiler probe under the owning dxwrapper.cpp flags measured sizeof(RenderStateStruct) = 624, offsetof(material) = 4, and offsetof(vertex_buffers) = 608 (0x260). The three emitted COFF dwords and compile output are retained in `build/rlink/pointer-globals-1791191482/layout-probe.log`; these agree with both queried VAs and the existing data row.
