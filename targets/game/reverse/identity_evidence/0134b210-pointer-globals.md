# Pointer-global identity at VA 0x0134B210

Corrected: _BoxMaterial is the shared VertexMaterialClass* datum.

## Retail facts and receiver contract

Zero Hour boxrobj.cpp defines static VertexMaterialClass* _BoxMaterial = NULL. Its initializer creates a material with ambient, diffuse and specular RGB all zero, emissive RGB all one, opacity one and shininess zero. Its renderer binds that material and its shutdown releases it. Retail RVA 0x009569A0 allocates 0x6C bytes, calls the independently ledgered VertexMaterialClass constructor at RVA 0x00921820, applies those same six setter calls, and stores the result at this VA. RVA 0x00956F40 is the matched BoxRenderObjClass::render_box reader. RVA 0x00956F10 releases the same refcount at pointee offset 4 and clears the pointer. These establish the reference identity independently of either invented spelling. The datum is now defined once in BfmeMaterialInitXP.cpp, which owns its main writer. The split renderer and cleanup declare _BoxMaterial with the same VertexMaterialClass* type. Cleanup casts only at its existing partial refcount ABI use. The original reference file-local name is retained with external visibility because the reconstructed functions occupy separate translation units.

The inspected storage is in .data and every byte of the candidate extent is loader-zero. No base relocation lies inside it, so there is no initialized pointer target to follow. The candidate extent in the raw probe is 4 bytes; unresolved member cases and the unresolved buffer do not claim an independent datum of that size. All confirmed instruction references and complete containing-body disassemblies are retained in `build/rlink/pointer-globals-1791191482/0134b210-retail.log`. The containing bodies are VA 0x00D569A0, VA 0x00D56F10, VA 0x00D56F40. The raw XREF lines distinguish absolute loads, stores and address uses; the complete bodies preserve indirect reads and writes for review.

## Competing spellings

g_bfme911Ptr and g_bfmeMaterialXP each had 1 extern declaration file. The old game boxrobj.cpp had 1 static _BoxMaterial definition. The chosen reference spelling is preferred over those counts. The new decorated spelling is appended beside old DIR32 rows, and its pin is additive; no old pin was removed.

`build/rlink/pointer-globals-1791191482/exact-declaration-counts.log` lists typed external declaration matches. Static-table access variants require the private declaration and initializer macro described above; their lexical declaration rows are shared text rather than independent public declarations. `build/rlink/pointer-globals-1791191482/address-ledgers.log` retains every original decorated spelling and pin.

## Refutation and verification

A different final constructor target, material setter values unlike the reference, a renderer read of another address, or a cleanup pointee with another refcount layout would refute this correction. add_data_match.py must verify a single zero-filled four-byte external symbol at this VA.

Raw direct-call bytes, each followed five-byte E9 jump chain, final targets, callee ledger rows and pins are in `build/rlink/pointer-globals-1791191482/supplement.log`. Raw reference lines with repository-relative paths and line numbers are in `build/rlink/pointer-globals-1791191482/reference-excerpts.log`. Build, datum and link receipts are recorded in `build/worker-final.md`. The functions ledger is not changed because these are datum and declaration corrections, not function identity corrections.
