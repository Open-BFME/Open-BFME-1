# Pointer-global identity at VA 0x0134CB50

Unresolved: inline path-buffer identity is proven, but its exact allocation size is not.

## Retail facts and receiver contract

This address starts an inline writable character array, not a char* pointer slot. The setter at RVA 0x009C8600 takes one const char* cdecl argument, copies bytes directly into this VA, computes the copied string length, and appends a backslash unless the last byte is slash or backslash. FileSystem::openFile at RVAs 0x009C8860 and 0x009C89F0 tests the byte at this address and passes the address itself to the string constructor before concatenating the requested filename. parseCommandLine calls the setter with the global-data mod directory after loading its archives. The 256 bytes up to the independently named TheArchiveFileSystem slot are initially zero and contain no other DIR32 name or data row. That next boundary bounds a plausible char[256] allocation, but the unbounded copy and strlen access do not prove its exact declared capacity, and the Zero Hour reference does not declare this BFME-added buffer. No row or source change was kept.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 256 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/0134cb50-retail.log`. The containing bodies are VA 0x00DC8600, VA 0x00DC8860, VA 0x00DC89F0. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

Rva009C8600Path and byte_134CB50 each have 1 extern array declaration file. Both describe the same inline path prefix; neither is a pointer scalar. Their PADA decoration is also used for unsized char arrays.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

An EA or independently verified declaration specifying the buffer capacity, or a retail operation whose fixed bound establishes the full allocation, would settle the size. A load of an initialized pointer followed by indirection, rather than passing this VA directly, would refute the inline-array conclusion.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.
