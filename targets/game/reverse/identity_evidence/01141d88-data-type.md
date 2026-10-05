# Datum identity at VA 0x01141D88

The chosen spelling is `g_bfmeApplyTableD` with type `const short[64]`, size 128 bytes, in retail `.rdata`.

The array is 64 signed 16-bit quantizer entries. The signed load at VA 0x00DA683E multiplies the selected entry by four before reciprocal arithmetic. The 16-bit loads in RVA 0x009A6630 use the same array for the second quantizer destination; an unsigned cast there preserves the low-word operation. The next named datum starts at VA 0x01141E08. No write to this array was found in the byte-pattern reference inventory; the initialization loop at RVA 0x009A4D00 uses 0x01141D88 only as the exclusive end of its preceding array.

The raw initial bytes are `2f 00 2f 00 2f 00 2f 00 2d 00 2b 00 2b 00 2b 00 2b 00 2b 00 2a 00 29 00 29 00 28 00 28 00 28 00 28 00 23 00 23 00 23 00 23 00 21 00 21 00 21 00 21 00 20 00 20 00 20 00 1b 00 1b 00 1a 00 1a 00 19 00 19 00 18 00 18 00 17 00 17 00 13 00 13 00 13 00 13 00 12 00 12 00 11 00 10 00 10 00 10 00 10 00 10 00 0f 00 0b 00 0b 00 0b 00 0a 00 0a 00 09 00 08 00 07 00 05 00 03 00 03 00 02 00 02 00`.

The reference inventory is a raw byte-pattern scan followed by instruction decoding at each containing ledger body. Each direct call or jump in those body logs follows every five-byte E9 in its chain. A pattern hit is a candidate until its instruction operand confirms a read, write or address transfer. The retail executable has no PE base-relocation directory; pointer fields are identified by the string/table use and checked against COFF DIR32 relocations, while the scalar quantizer and selector records contain no pointer relocations.

The receiver and argument contracts are visible in the body logs: indexed table loads use the datum directly; parser users pass its address as a names or userData argument; the selector constructors use ECX for their eight-word receiver and two stack pointers, while their paired readers take two stack output pointers. Team-key calls use ECX for StaticNameKey and return a 32-bit key without consuming a stack argument.

The data probe lists every nearby DIR32 name and every overlapping data row. No other DIR32 start lies strictly inside this chosen extent and no existing data row overlaps it. Neighboring padding is excluded. The competing spellings and their game declaration counts are in `build/rlink/identity-data-1791188974/spellings-declarations-before.log`; counts do not establish identity.

A different pointer string, a nonzero terminator, a code reference showing a conflicting element stride or use, a write requiring a different layout, an interior data/DIR32 start, or a different final E9 target would refute this correction. A reviewed original declaration can further refine constness that bytes alone do not prove.

Raw evidence is under `build/rlink/identity-data-1791188974`: `01141d88-data.log`, `01141d88.bin`, `table-audit.log`, `reference-bodies.csv`, `pins-nearby.log`, and `spellings-declarations-before.log`.

- `?Rva009A4D00Init@@YAXXZ` at `0x00DA4D00` (90 bytes), source `game/GameEngine/Source/Common/Rva009A4D00TableInit.cpp`, raw `body-00da4d00.log`.
- `?bfmeApply1040@@YAXPAUBfmeS1040@@H@Z` at `0x00DA6630` (277 bytes), source `game/GameEngine/Source/Common/BfmeConv1040.cpp`, raw `body-00da6630.log`.
- `?Rva009A6780BuildQuantizers@@YAXPAURva009A6780State@@H@Z` at `0x00DA6780` (945 bytes), source `game/GameEngine/Source/Common/Rva009A6780BuildQuantizers.cpp`, raw `body-00da6780.log`.
