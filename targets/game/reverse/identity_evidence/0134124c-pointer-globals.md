# Pointer-global identity at VA 0x0134124C

Corrected: the private PointGroupClass::_QuadVertexUVFrameTable[5] spelling is canonical.

## Retail facts and receiver contract

This is a 20-byte array of five Vector2* values. Zero Hour pointgr.h declares it private and pointgr.cpp defines five null entries. Retail RVA 0x00917280 runs five iterations, allocates 4*(1<<i)^2 Vector2 elements, stores each pointer at this base plus i*4, and fills pairs of floats with quad UV coordinates. RVA 0x00916CD0 selects an entry with FrameRowColumnCountLog2 and advances four Vector2 elements per frame. RVA 0x00912CF0 deletes all five entries. The single existing definition stays in pointgr.cpp; the initializer's private-to-public macro was replaced with friend access for its existing free function.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 20 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/0134124c-retail.log`. The containing bodies are VA 0x00D12CF0, VA 0x00D16CD0, VA 0x00D17280. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

The private declaration appears in 2 game files (pointgr.h and PointGroupClassUVFill.cpp). The initializer previously produced the public spelling in 1 translation unit. Both decorated spellings denote the same array.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

The private-static exception applies because add_data_match.py refuses private-member sizeof probes. No data row is added; all five initial retail dwords were checked and are zero, and the canonical private DIR32 spelling already exists. A sixth table element, non-Vector2 stride, or a differing initial pointer would refute this correction.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.

The compiled private definition was also compared entry by entry with retail: both five-entry arrays and the one pointer scalar contain only zero dwords and have no COFF relocations in their extents. Raw COFF section, symbol offset, bytes, values and assertions are in `build/rlink/pointer-globals-1791191482/private-data-verify-final.log`.
