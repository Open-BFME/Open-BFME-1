# Rva012F4B50ScoreScreen at VA 0x012F4B50

The datum is `BfmeAptScreenScoreScreen *`, 4 bytes in retail .data. Its initial value is 0 (zero-filled virtual tail of .data). This correction changes data declarations and definitions only; every matched function must retain its verified bytes.

The constructor at RVA 0x00578160 stores its receiver here when the pointer is null. The matching destructor at RVA 0x00575050 clears it. RVA 0x005774E0 returns early when it exists, otherwise pushes ScoreScreen.apt and then calls the score-screen population methods on this receiver. RVA 0x00573000 reads the receiver game-type field at +0x25C before leaving the score screen. Existing constructor/destructor identities and the EA ScoreScreen.apt string prove the pointee role. The raw string at VA 0x010879C4 is in `build/rlink/pointer-globals-1791160230/score-ea-string.log`. The existing descriptive spelling is retained.

The value is the active BfmeAptScreenScoreScreen receiver. Its constructor takes a context pointer, and the leave/show bodies use the same object. All declarations use that pointer type. AptScoreScreenConstructor.cpp owns the definition at its main writer.

The competing spellings and the number of game files that explicitly declare each exact type are measured in `build/rlink/pointer-globals-1791160230/inventory-corrected.log`. Counts do not decide the chosen identity.

| Spelling | Declaring game files |
|---|---:|
| `?Rva012F4B50ScoreScreen@@3PAVBfmeAptScreenScoreScreen@@A` | 2 |
| `?g_obj12F4B50@@3PAVBfmeAptScreenScoreScreen@@A` | 1 |
| `?g_obj12F4B50@@3PAXA` | 1 |

Direct retail operand xrefs, with each matched ledger boundary and the raw instructions, are in `build/rlink/pointer-globals-1791160230/retail-012f4b50.log`. The scan found no unmapped direct operand sites. It is a direct-xref census; generic helpers can also access a field through a supplied receiver.

| Retail body RVA | Ledger name |
|---|---|
| `0x00578160` | `??0BfmeAptScreenScoreScreen@@QAE@PAX@Z` |
| `0x00575050` | `??1BfmeAptScreenScoreScreen@@UAE@XZ` |
| `0x00573000` | `?_bfme_leaveScoreScreen@@YAXXZ` |
| `0x005774E0` | `?_bfme_showScoreScreen@@YA_NXZ` |

Additional raw PE directories, storage bytes, vtable entries, initializer COFF relocations, and registry helpers are in `build/rlink/pointer-globals-1791160230/supplement-complete.log`. The image has no PE base-relocation directory. The portable-map initializers nevertheless reproduce IMAGE_REL_I386_DIR32 relocations to their verified string addresses; those compiler string constants are address mappings, not new data rows. Raw reference excerpts are in `build/rlink/pointer-globals-1791160230/reference-excerpts.log`. Raw EA-string reads are in `build/rlink/pointer-globals-1791160230/extra-retail-strings.log`.

A constructor storing a different receiver, an incompatible vtable/field offset, or a different screen string would refute the score-screen role.
