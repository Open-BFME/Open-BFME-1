# Pointer-global identity at VA 0x01341260

Corrected: the private PointGroupClass::PointMaterial spelling is canonical.

## Retail facts and receiver contract

This four-byte slot holds VertexMaterialClass*. Zero Hour pointgr.h declares it private; pointgr.cpp initializes it to null, obtains the PRELIT_DIFFUSE preset during initialization, uses it when submitting point geometry, and releases it on shutdown. Retail RVA 0x00917280 stores the preset result here, RVA 0x00913AF0 reads it for material binding, and RVA 0x00912CF0 decrements pointee refcount at offset 4, dispatches slot 0 when it reaches zero, and clears the slot. Its one existing definition remains in pointgr.cpp. Friend access replaces the initializer's public access macro.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 4 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/01341260-retail.log`. The containing bodies are VA 0x00D12CF0, VA 0x00D13AF0, VA 0x00D17280. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

The private declaration appears in 1 game file (pointgr.h). Before correction, the initializer exposed it as public in 1 translation unit. The two DIR32 spellings denote one pointer slot.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

The existing private static definition falls under the explicit private-static exception: add_data_match.py refuses its private-member sizeof probe. No data row is added; the one retail initial dword is verified zero and the canonical private DIR32 spelling already exists. A preset call resolving to another type, different refcount offset, or a nonzero initial dword would refute this correction.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.

The compiled private definition was also compared entry by entry with retail: both five-entry arrays and the one pointer scalar contain only zero dwords and have no COFF relocations in their extents. Raw COFF section, symbol offset, bytes, values and assertions are in `build/rlink/pointer-globals-1791191482/private-data-verify-final.log`.
