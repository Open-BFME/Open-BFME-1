# Data identity at VA 0x012C5628

Corrected: LZHLDecoderStat::Group[16], each Group is two int fields.

## Retail facts and extent

The accepted row is `?groupTable0@LZHLDecoderStat@@2PAUGroup@1@A` at VA 0x012C5628, RVA 0x00EC5628, with 128 bytes in `.data`, owned by `game/Libraries/Source/Compression/LZHCompress/CompLibSource/Huff.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012C5628-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

The existing vendored _huff.h declares Group as { int nBits; int pos; }. Huff.cpp defines groupTable0 with hdec_g.tbl. The retail constructor at RVA 0x00826660 and reset bodies at RVAs 0x00826740 and 0x00826840 copy 0x20 dwords from this address. Its end is exactly the next symbol table at VA 0x012C56A8. All 16 entries are byte-equal to the existing initializer. The old Rva00826740SmallInit pin is stale; current game sources already name groupTable0.

Initial bytes: `02 00 00 00 00 00 00 00 03 00 00 00 04 00 00 00 03 00 00 00 0c 00 00 00 04 00 00 00 14 00 00 00 04 00 00 00 24 00 00 00` (prefix; the complete initializer is in the raw retail log).

The verified COFF initializer has 0 relocation(s). The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x00826660` (`??0LZHLDecoderStat@@QAE@XZ`, address immediate), `0x00826740` (`?resetTables@Rva00826740Owner@@QAEXXZ`, address immediate), `0x00826840` (`?resetTables@Rva00826840Owner@@QAEXXZ`, address immediate).

## Receiver and argument contract

All three readers receive their destination in ECX. The memcpy destinations are member storage at receiver +4, or +12 in the second reset layout. The initializer has no receiver or arguments.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012C5628-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?Rva00826740SmallInit@@3URva00826740Small@@B`: 0 game file(s).
- `?groupTable0@LZHLDecoderStat@@2PAUGroup@1@A`: 2 game file(s).

## Change and verification

Added a data row for the existing Huff.cpp definition. No source body or header changed. The selected DIR32 spelling already exists and was retained; old pins were retained.

The raw datum gate output is `build/rlink/identity-data-20261005/add-lzh-group.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

Different Group member widths, a copy extent other than 128 bytes, any initializer mismatch, or a relocation-bearing element would refute this correction.
