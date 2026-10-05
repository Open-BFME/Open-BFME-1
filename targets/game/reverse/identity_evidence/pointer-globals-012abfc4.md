# PORTABLE_USER_MAPS at VA 0x012ABFC4

The datum is `const char *`, 4 bytes in retail .data. Its initial value is 0x01089294 (the NUL-terminated string `UserData\Maps\` in .rdata). This correction changes data declarations and definitions only; every matched function must retain its verified bytes.

The four GameState path-conversion bodies listed below directly read this pointer. No direct operand writes it. Zero Hour GameState.cpp line 869 defines PORTABLE_USER_MAPS with the identical initializer.

The storage is a mutable pointer to const narrow characters. Consumers compare or append the user-map prefix and compute its terminated length. GameState.cpp owns the datum.

The competing spellings and the number of game files that explicitly declare each exact type are measured in `build/rlink/pointer-globals-1791160230/inventory-corrected.log`. Counts do not decide the chosen identity.

| Spelling | Declaring game files |
|---|---:|
| `?PORTABLE_USER_MAPS@@3PBDB` | 3 |
| `?rva0010e580UserPrefix@@3PBDB` | 1 |
| `?rva0010f820UserMaps@@3PBDB` | 1 |

Direct retail operand xrefs, with each matched ledger boundary and the raw instructions, are in `build/rlink/pointer-globals-1791160230/retail-012abfc4.log`. The scan found no unmapped direct operand sites. It is a direct-xref census; generic helpers can also access a field through a supplied receiver.

| Retail body RVA | Ledger name |
|---|---|
| `0x0010F550` | `?portableMapPathToRealMapPath@GameState@@QBE?AVAsciiString@@ABV2@@Z` |
| `0x0010F280` | `?realMapPathToPortableMapPath@GameState@@QBE?AVAsciiString@@ABV2@@Z` |
| `0x0010E580` | `?rva0010e580MapPathCode@GameState@@QBE?AVAsciiString@@ABV2@@Z` |
| `0x0010F820` | `?rva0010f820MapPathCode@GameState@@QBE?AVAsciiString@@ABV2@@Z` |

Additional raw PE directories, storage bytes, vtable entries, initializer COFF relocations, and registry helpers are in `build/rlink/pointer-globals-1791160230/supplement-complete.log`. The image has no PE base-relocation directory. The portable-map initializers nevertheless reproduce IMAGE_REL_I386_DIR32 relocations to their verified string addresses; those compiler string constants are address mappings, not new data rows. Raw reference excerpts are in `build/rlink/pointer-globals-1791160230/reference-excerpts.log`. Raw EA-string reads are in `build/rlink/pointer-globals-1791160230/extra-retail-strings.log`.

A different pointer or string, or a writer inconsistent with this path-prefix contract, would refute the correction.
