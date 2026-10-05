# Datum identity at VA 0x012A732C

The chosen spelling is `g_ObfRecord012A732C` with type `BigObfSelectorRecord (two unsigned int[5] arrays)`, size 40 bytes, in retail `.data`.

The record has two five-dword arrays at offsets 0 and 0x14. In each array four nonzero integer entries precede a zero fifth entry. The constructor loads a key by a two-bit index, multiplies it repeatedly and XORs its products into the receiver. The paired selector reader copies the same scalar values to its two output words. The arithmetic key values and most seed values are outside the retail image. At VA 0x012A732C the fourth seed is 0x0119148B, an in-image numeric coincidence; no pointer dereference or address use of that seed is present. The witnessed uses treat the entries as 32-bit scalar words. The pointer-table spelling therefore misstates the element type; the existing BigObfSelectorRecord spelling accurately describes the witnessed scalar layout. No writes to this record were found in the byte-pattern inventory. The owner is BigObfHookWrappers.cpp, whose constructor consumes its keys and seeds.

The raw initial bytes are `8a 32 e8 7a 4a 13 17 89 0a 89 47 09 ca 04 b9 1d 00 00 00 00 cb 72 60 32 0b 0b 3f 89 4b 91 67 01 8b 14 19 01 00 00 00 00`.

The reference inventory is a raw byte-pattern scan followed by instruction decoding at each containing ledger body. Each direct call or jump in those body logs follows every five-byte E9 in its chain. A pattern hit is a candidate until its instruction operand confirms a read, write or address transfer. The retail executable has no PE base-relocation directory; pointer fields are identified by the string/table use and checked against COFF DIR32 relocations, while the scalar quantizer and selector records contain no pointer relocations.

The receiver and argument contracts are visible in the body logs: indexed table loads use the datum directly; parser users pass its address as a names or userData argument; the selector constructors use ECX for their eight-word receiver and two stack pointers, while their paired readers take two stack output pointers. Team-key calls use ECX for StaticNameKey and return a 32-bit key without consuming a stack argument.

The data probe lists every nearby DIR32 name and every overlapping data row. No other DIR32 start lies strictly inside this chosen extent and no existing data row overlaps it. Neighboring padding is excluded. The competing spellings and their game declaration counts are in `build/rlink/identity-data-1791188974/spellings-declarations-before.log`; counts do not establish identity.

A different pointer string, a nonzero terminator, a code reference showing a conflicting element stride or use, a write requiring a different layout, an interior data/DIR32 start, or a different final E9 target would refute this correction. A reviewed original declaration can further refine constness that bytes alone do not prove.

Raw evidence is under `build/rlink/identity-data-1791188974`: `012a732c-data.log`, `012a732c.bin`, `table-audit.log`, `reference-bodies.csv`, `pins-nearby.log`, and `spellings-declarations-before.log`.

- `?Rva00072BC0@@YAXPAPAH0@Z` at `0x00472BC0` (45 bytes), source `game/GameEngine/Source/Common/R3SelectorRecordReadersEbp.cpp`, raw `body-00472bc0.log`.
- `??0Obf00076710@@QAE@PAH0@Z` at `0x00476710` (171 bytes), source `game/GameEngine/Source/Common/BigObfHookWrappers.cpp`, raw `body-00476710.log`.

The data-row gate checks all 40 initial bytes with zero relocations. The four reachable entries in each group are selected by index & 3; the fifth dwords are zero and unused by these readers. The repeated 40-byte record spacing and neighboring record or scalar starts delimit the chosen allocation.
