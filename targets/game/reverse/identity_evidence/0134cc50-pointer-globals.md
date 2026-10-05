# Pointer-global identity at VA 0x0134CC50

Corrected: the datum is ArchiveFileSystem* TheArchiveFileSystem.

## Retail facts and receiver contract

Zero Hour ArchiveFileSystem.h declares the pointer and Common/System/ArchiveFileSystem.cpp defines it as NULL. The BFME source already has that one definition. The bootstrap at RVA 0x009C87A0 allocates 0x2C bytes, calls ArchiveFileSystem construction, stores the returned pointer here, and dispatches init. FileSystem::openFile at RVA 0x009C8860 uses vtable offset 0x14 for this slot, whereas the independently named LocalFileSystem slot uses offset 8. The wide openFile variant uses offsets 0x18 and 0x0C respectively. Retail cleanup at RVA 0x009C8740 invokes scalar deletion through slot zero with argument 1, then clears both distinct slots. The invented BfmeResTXB spelling in that cleanup describes its partial deletion view of the same object. Its declaration is replaced with ArchiveFileSystem*, with a cast at that existing ABI use; no inheritance or wrapper is introduced. The existing definition receives the four-byte data row.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 4 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/0134cc50-retail.log`. The containing bodies are VA 0x00463BA0, VA 0x00479060, VA 0x0086DF00, VA 0x00A9D0A0, VA 0x00ABA610, VA 0x00DC86A0, VA 0x00DC8740, VA 0x00DC87A0, VA 0x00DC8860, VA 0x00DC89F0, VA 0x00DC8BB0, VA 0x00DC8C70. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

TheArchiveFileSystem has 8 explicit extern declaration files; g_bfmeTwoTXB has 1. The independently typed reference declaration and retail vtable dispatch decide the identity.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

An archive open call at a different slot, constructor resolving to another class, or evidence that the cleanup address differs from the openFile address would refute the correction. add_data_match.py must verify the existing symbol as one four-byte zero-filled datum.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.
