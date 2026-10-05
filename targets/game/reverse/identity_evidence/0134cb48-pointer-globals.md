# Pointer-global identity at VA 0x0134CB48

Corrected: the datum is FileSystem* TheFileSystem.

## Retail facts and receiver contract

Zero Hour Common/FileSystem.h declares extern FileSystem* TheFileSystem and Common/System/FileSystem.cpp defines it as NULL. BFME retains that definition in the same source. Retail GameEngine startup at RVA 0x00079060 stores the newly created file-system pointer at VA 0x00479116; teardown at RVA 0x0007B420 clears it at VA 0x0047B532. The numerous matched callers load the pointer into ECX and call the FileSystem openFile, doesFileExist and getFileInfo bodies, rather than the LocalFileSystem virtual interface. These agree with the reference FileSystem facade. The competing TheLocalFileSystem with FileSystem* type is misplaced: the real LocalFileSystem* slot is VA 0x0134D060. The other two spellings have no current game declaration to move. The existing one definition receives its verified four-byte data row.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 4 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/0134cb48-retail.log`. The containing bodies are VA 0x00479060, VA 0x0047B420, VA 0x00484510, VA 0x0049B6C0, VA 0x004A2F60, VA 0x004B3730, VA 0x00502A60, VA 0x0050FB20, VA 0x00510170, VA 0x005107B0, VA 0x00511980, VA 0x00512A50, VA 0x005A9110, VA 0x006E55C0, VA 0x006EC840, VA 0x006ECF40, VA 0x00786A30, VA 0x00786DE0, VA 0x00788C10, VA 0x008389E0, VA 0x00838D50, VA 0x00839560, VA 0x0084F410, VA 0x00850560, VA 0x008508D0, VA 0x008516E0, VA 0x008550C0, VA 0x008577C0, VA 0x008578EB, VA 0x00857E70, VA 0x00857FB0, VA 0x00888B80, VA 0x0088C680, VA 0x008DE460, VA 0x008DE8E0, VA 0x008E1450, VA 0x00901B90, VA 0x00920BB0, VA 0x0096F1F0, VA 0x0099A3D0, VA 0x00A19900, VA 0x00A20510, VA 0x00A2BC60, VA 0x00A2BE40, VA 0x00A66A10, VA 0x00A69E20, VA 0x00A6A170, VA 0x00A94230, VA 0x00AAC1A0, VA 0x00ABA610, VA 0x00AC39D0, VA 0x00AF6170, VA 0x00AF63B0, VA 0x00AF6AB0, VA 0x00AF6BA0, VA 0x00B188B0, VA 0x00B18A10, VA 0x00B18B70, VA 0x00B85270, VA 0x00B89010, VA 0x00BAC7E0, VA 0x00BE35E0, VA 0x00BE5080, VA 0x00C53610, VA 0x00C53F10. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

TheFileSystem has 40 explicit extern declaration files; Rva0134CB48FileSystem, TheOpen2FileSystem, and TheLocalFileSystem with FileSystem* type each have 0. The distinct TheLocalFileSystem with LocalFileSystem* type has 9 and belongs at VA 0x0134D060. Exact typed declaration lists, not substring counts, are in exact-declaration-counts.log.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

A caller using this slot as the LocalFileSystem virtual interface, or startup storing an object whose established vtable is not the FileSystem facade, would refute the correction. The independently named LocalFileSystem slot and differing openFile dispatch at VA 0x0134D060 are the counter-check.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.
