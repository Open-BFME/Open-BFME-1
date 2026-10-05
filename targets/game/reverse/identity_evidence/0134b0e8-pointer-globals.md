# Pointer-global identity at VA 0x0134B0E8

Unresolved correction: canonical pointer identity conflicts with a shared header that this run may not edit.

## Retail facts and receiver contract

Retail holds one four-byte DX8MeshRendererClass* singleton, initially null. Initialization at RVA 0x0090ADC0 allocates and constructs a renderer, stores it here, and calls Init. Shutdown at RVA 0x0090B640 deletes the pointee and clears the slot. Mesh operations load this slot into ECX; for example RVA 0x00946540 checks for null and calls renderer unregister behavior, while RVA 0x008FD2A0 calls Invalidate(false). The existing pointer pin names TheDX8MeshRenderer. Zero Hour defines a value object, whereas BFME retail uses a pointer. The game dx8renderer.h still declares the value object and dx8renderer.cpp defines it, while TU-local users spell a pointer and other code casts the value object's address to a pointer slot. Defining a second independent pointer without correcting those declarations would preserve competing identities. The requested shared-header prohibition prevents the coherent type correction in this run. No change for this address was kept.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 4 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/0134b0e8-retail.log`. The containing bodies are VA 0x00B14810, VA 0x00B15340, VA 0x00B15530, VA 0x00B158F0, VA 0x00B89E60, VA 0x00B9DE40, VA 0x00BB6D30, VA 0x00CFD2A0, VA 0x00CFE3C0, VA 0x00CFE730, VA 0x00D07960, VA 0x00D082B0, VA 0x00D0ADC0, VA 0x00D0B640, VA 0x00D46540, VA 0x00D46650, VA 0x00D47D30, VA 0x00D47E50, VA 0x00D48220, VA 0x00D48BD0, VA 0x00D4DFD0, VA 0x00D4ED60, VA 0x00D4F900. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

TheDX8MeshRenderer pointer spelling has 22 explicit external declaration files. g_rva008fd2a0 has no extern declaration and 1 tentative pointer definition file. The shared header and dx8renderer.cpp additionally declare and define a value object; these are a separate decorated value spelling, not a second retail object.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

A later correction must permit changing the shared value-object declaration and byte-verify every affected source against the one pointer definition. Retail using the address as a renderer object instead of loading its dword, or the initializer constructing the object in-place at this VA, would refute the pointer identity.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.
