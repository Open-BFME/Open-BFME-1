# Pointer-global identity at VA 0x0134D060

Corrected: the datum is LocalFileSystem* TheLocalFileSystem.

## Retail facts and receiver contract

Zero Hour LocalFileSystem.h declares this pointer and Common/System/LocalFileSystem.cpp defines it as NULL. The matching BFME bootstrap writer at RVA 0x009C87A0 allocates four bytes, calls LocalFileSystem construction, stores the result here, and dispatches init. FileSystem::openFile uses vtable offset 8 for its narrow form and 0x0C for its wide form, distinct from the archive pointer at VA 0x0134CC50. Retail cleanup at RVA 0x009C8740 dispatches scalar deletion through slot zero with argument 1 and clears this slot. The datum is now defined once in BfmeConv2018.cpp, which owns the main writer. Its competing cleanup spelling becomes a LocalFileSystem* declaration; a cast preserves that existing partial deletion ABI view. There is no alias object, invented inheritance, or wrapper.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 4 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/0134d060-retail.log`. The containing bodies are VA 0x00DC86A0, VA 0x00DC8740, VA 0x00DC87A0, VA 0x00DC8860, VA 0x00DC89F0, VA 0x00DC8BB0, VA 0x00DC8C70, VA 0x00DC8DC0, VA 0x00DCC710, VA 0x00DCDB90, VA 0x00DD1560. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

TheLocalFileSystem with LocalFileSystem* type has 9 explicit extern declaration files and g_bfmeOneTXB has 1. The TheLocalFileSystem with FileSystem* type has 0 and its VA 0x0134CB48 claim is misplaced.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

A constructor identifying another class, different openFile dispatch, or a writer storing a facade FileSystem object here would refute the correction. add_data_match.py must verify one four-byte zero-filled datum.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.
