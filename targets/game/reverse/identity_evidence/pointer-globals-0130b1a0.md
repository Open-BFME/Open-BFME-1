# g_bfmeVideoTableEnd at VA 0x0130B1A0

The datum is `Video *`, 4 bytes in retail .data. Its initial value is 0 (zero-filled virtual tail of .data). This correction changes data declarations and definitions only; every matched function must retain its verified bytes.

This is the end field of the global vector whose begin is VA 0x0130B19C and capacity end is VA 0x0130B1A4. Direct readers subtract the begin pointer and divide by 28 or advance records by 0x1C. VideoPlayer::addVideo at RVA 0x0081D2C0 advances and stores the end pointer after constructing a Video. VideoPlayer::removeVideo at RVA 0x0081CF40 decrements and stores it after erase. VideoPlayer::getVideo and init traverse the same records. The subtitle query carries EA string VideoPlayer::getSubTitleMgrForVideo should not FAIL! at VA 0x0112CD30. The existing Video.h has the 28-byte Video record. Zero Hour VideoPlayer.cpp uses the corresponding VecVideo list; BFME places that list globally.

The pointee is Video, not either anonymous 28-byte shape used by the competing declarations. Direct scalar readers now use Video *, with a cast only where a preexisting return type remains anonymous. VideoPlayerAddVideo.cpp, the main append writer, owns this one pointer field. The neighboring vector symbol is a declaration, not a second data definition.

The competing spellings and the number of game files that explicitly declare each exact type are measured in `build/rlink/pointer-globals-1791160230/inventory-corrected.log`. Counts do not decide the chosen identity.

| Spelling | Declaring game files |
|---|---:|
| `?g_Rva0081C5C0End@@3PAURva0081C5C0Element@@A` | 1 |
| `?g_bfmeEndJD@@3PAVBfmeRecJD@@A` | 1 |
| `?g_bfmeVideoTableEnd@@3PAUVideo@@A` | 2 |

Direct retail operand xrefs, with each matched ledger boundary and the raw instructions, are in `build/rlink/pointer-globals-1791160230/retail-0130b1a0.log`. The scan found no unmapped direct operand sites. It is a direct-xref census; generic helpers can also access a field through a supplied receiver.

| Retail body RVA | Ledger name |
|---|---|
| `0x0081C5C0` | `?Rva0081C5C0Count@@YAHXZ` |
| `0x0081D2C0` | `?addVideo@VideoPlayer@@UAEXPAUVideo@@@Z` |
| `0x0081C5F0` | `?bfmeSlotAt@@YGPAVBfmeRecJD@@H@Z` |
| `0x0081CA10` | `?getSubTitleMgrForVideo@VideoPlayer@@UAEPAVSubtitleManager@@ABVAsciiString@@@Z` |
| `0x0081CD70` | `?getVideo@VideoPlayer@@UAEPBUVideo@@VAsciiString@@@Z` |
| `0x0081CB30` | `?init@VideoPlayer@@UAEXXZ` |
| `0x0081CF40` | `?removeVideo@VideoPlayer@@UAEXPAUVideo@@@Z` |

Additional raw PE directories, storage bytes, vtable entries, initializer COFF relocations, and registry helpers are in `build/rlink/pointer-globals-1791160230/supplement-complete.log`. The image has no PE base-relocation directory. The portable-map initializers nevertheless reproduce IMAGE_REL_I386_DIR32 relocations to their verified string addresses; those compiler string constants are address mappings, not new data rows. Raw reference excerpts are in `build/rlink/pointer-globals-1791160230/reference-excerpts.log`. Raw EA-string reads are in `build/rlink/pointer-globals-1791160230/extra-retail-strings.log`.

A stride other than 28, an append/erase update of a different field, or evidence that the vector elements are not the records used by the named VideoPlayer slots would refute the correction.
