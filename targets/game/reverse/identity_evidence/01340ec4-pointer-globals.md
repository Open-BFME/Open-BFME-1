# Pointer-global identity at VA 0x01340EC4

Unresolved correction: this address is a member of an existing datum.

## Retail facts and receiver contract

The pointee is VertexMaterialClass. The four-byte slot is DX8Wrapper::render_state.material at offset 4, matching RenderStateStruct in the Zero Hour dx8wrapper.h. Retail material swaps increment and release the RefCountClass count at pointee offset 4; DX8 material application reads the same slot. ScreenMaterial and Rva01340EC4Material both describe this slot, not independent objects. The existing matched data row ?render_state@DX8Wrapper@@1URenderStateStruct@@A owns VA 0x01340EC0 through 0x01341130 (624 bytes) in dxwrapper.cpp. A new row at this address would violate the non-overlap rule. No source or row for this address was changed.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 4 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/01340ec4-retail.log`. The containing bodies are VA 0x00ACCE70, VA 0x00ACD990, VA 0x00ACDD70, VA 0x00AD3480, VA 0x00ADA2D0, VA 0x00AE2AC0, VA 0x00AF9380, VA 0x00B11600, VA 0x00B171F0, VA 0x00B1A730, VA 0x00B22640, VA 0x00B22BD0, VA 0x00B25710, VA 0x00B26290, VA 0x00B2FEB0, VA 0x00B8B4F0, VA 0x00BA1770, VA 0x00BA1C80, VA 0x00BA6460, VA 0x00BA7240, VA 0x00BB14A0, VA 0x00BBFB90, VA 0x00BC19F0, VA 0x00BC3FD0, VA 0x00BCC430, VA 0x00BD1AA0, VA 0x00BD31C0, VA 0x00BD3D40, VA 0x00BD7610, VA 0x00BD81C0, VA 0x00BD9240, VA 0x00BDAE30, VA 0x00BDC6A0, VA 0x00D03C50, VA 0x00D04890, VA 0x00D06B40, VA 0x00D07960, VA 0x00D08FE0, VA 0x00D0FEE0, VA 0x00D13AF0, VA 0x00D33E50, VA 0x00D34940, VA 0x00D391B0, VA 0x00D3A810, VA 0x00D3B340, VA 0x00D48BD0, VA 0x00D51AA0, VA 0x00D56F40, VA 0x00D5CE80, VA 0x00D60A30, VA 0x00D75100, VA 0x00D8ED30. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

ScreenMaterial has 15 explicit external declaration files in the initial lexical probe; Rva01340EC4Material has 2. The raw declaration list is authoritative if a count is disputed.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

All users must eventually reference the existing render_state owner and its material member, preserving their verified code generation. A native offsetof probe differing from 4, or a retail access requiring another pointee type, would refute the member identification.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.

The compiler probe under the owning dxwrapper.cpp flags measured sizeof(RenderStateStruct) = 624, offsetof(material) = 4, and offsetof(vertex_buffers) = 608 (0x260). The three emitted COFF dwords and compile output are retained in `build/rlink/pointer-globals-1791191482/layout-probe.log`; these agree with both queried VAs and the existing data row.
