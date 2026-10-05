# Data identity at VA 0x012C56A8

Corrected: LZHLDecoderStat::symbolTable0, HUFFINT[274] where HUFFINT is signed 16-bit.

## Retail facts and extent

The accepted row is `?symbolTable0@LZHLDecoderStat@@2PAFA` at VA 0x012C56A8, RVA 0x00EC56A8, with 548 bytes in `.data`, owned by `game/Libraries/Source/Compression/LZHCompress/CompLibSource/Huff.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012C56A8-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

The vendored _huff.h defines HUFFINT as INT16 and NHUFFSYMBOLS as 256 + 16 + 2. Huff.cpp defines symbolTable0 with hdec_s.tbl. The retail constructor and both reset bodies copy 0x89 dwords, agreeing with the compiler-proven array size. Every entry compares equal and there are no relocations. Dword values resembling addresses are pairs of 16-bit numbers, not pointers. The old Rva00826740BigInit object pin is stale; current readers already use symbolTable0.

Initial bytes: `00 01 01 01 02 01 03 01 04 01 05 01 06 01 07 01 08 01 09 01 0a 01 0b 01 0c 01 0d 01 0e 01 0f 01 00 00 20 00 30 00 ff 00` (prefix; the complete initializer is in the raw retail log).

The verified COFF initializer has 0 relocation(s). The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x00826660` (`??0LZHLDecoderStat@@QAE@XZ`, address immediate), `0x00826740` (`?resetTables@Rva00826740Owner@@QAEXXZ`, address immediate), `0x00826840` (`?resetTables@Rva00826840Owner@@QAEXXZ`, address immediate).

## Receiver and argument contract

The constructor and reset bodies have ECX receivers and copy into an allocated member buffer. The initializer is read as copied numeric storage and never dereferenced as a pointer table.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012C56A8-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?Rva00826740BigInit@@3URva00826740Big@@B`: 0 game file(s).
- `?symbolTable0@LZHLDecoderStat@@2PAFA`: 2 game file(s).

## Change and verification

Added a data row for the existing Huff.cpp definition. No source body or header changed, and the existing selected DIR32 spelling and old pins remain.

The raw datum gate output is `build/rlink/identity-data-20261005/add-lzh-symbol.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A 32-bit element access inconsistent with the signed 16-bit declaration, any initializer mismatch, a different bound, or a relocation within the table would refute this correction.
