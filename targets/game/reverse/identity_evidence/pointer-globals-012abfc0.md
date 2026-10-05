# PORTABLE_MAPS at VA 0x012ABFC0

The datum is `const char *`, 4 bytes in retail .data. Its initial value is 0x010892A8 (the NUL-terminated string `Maps\` in .rdata). This correction changes data declarations and definitions only; every matched function must retain its verified bytes.

The four directly referring retail bodies are the address-named GameState path-code helpers at RVAs 0x0010E580 and 0x0010F820, GameState::portableMapPathToRealMapPath, and GameState::realMapPathToPortableMapPath. Their operands load the pointer; no direct operand writes it. The Zero Hour GameState.cpp definition at line 868 has this exact identifier and initializer.

The storage is a mutable pointer to const narrow characters. Consumers pass the pointee to string-prefix comparisons, append operations and strlen. There is no object receiver on the datum. The owning reference translation unit is GameState.cpp.

The competing spellings and the number of game files that explicitly declare each exact type are measured in `build/rlink/pointer-globals-1791160230/inventory-corrected.log`. Counts do not decide the chosen identity.

| Spelling | Declaring game files |
|---|---:|
| `?PORTABLE_MAPS@@3PBDB` | 3 |
| `?rva0010e580MapsPrefix@@3PBDB` | 1 |
| `?rva0010f820Maps@@3PBDB` | 1 |

Direct retail operand xrefs, with each matched ledger boundary and the raw instructions, are in `build/rlink/pointer-globals-1791160230/retail-012abfc0.log`. The scan found no unmapped direct operand sites. It is a direct-xref census; generic helpers can also access a field through a supplied receiver.

| Retail body RVA | Ledger name |
|---|---|
| `0x0010F550` | `?portableMapPathToRealMapPath@GameState@@QBE?AVAsciiString@@ABV2@@Z` |
| `0x0010F280` | `?realMapPathToPortableMapPath@GameState@@QBE?AVAsciiString@@ABV2@@Z` |
| `0x0010E580` | `?rva0010e580MapPathCode@GameState@@QBE?AVAsciiString@@ABV2@@Z` |
| `0x0010F820` | `?rva0010f820MapPathCode@GameState@@QBE?AVAsciiString@@ABV2@@Z` |

Additional raw PE directories, storage bytes, vtable entries, initializer COFF relocations, and registry helpers are in `build/rlink/pointer-globals-1791160230/supplement-complete.log`. The image has no PE base-relocation directory. The portable-map initializers nevertheless reproduce IMAGE_REL_I386_DIR32 relocations to their verified string addresses; those compiler string constants are address mappings, not new data rows. Raw reference excerpts are in `build/rlink/pointer-globals-1791160230/reference-excerpts.log`. Raw EA-string reads are in `build/rlink/pointer-globals-1791160230/extra-retail-strings.log`.

A different stored pointer, different terminated string, or a write showing that this datum is an array rather than a pointer would refute the correction.
