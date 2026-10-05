# Datum identity at VA 0x012A68B0

The chosen spelling is `g_bfmeNames012A68B0` with type `const char *const[8]`, size 32 bytes, in retail `.data`.

The seven string pointers are NONE, LEADERSHIP, FORMATION, SPELL, WEAPON, STRUCTURE, LEVEL, then null. Retail parseToken at RVA 0x00368EA0 passes this array to INI::scanIndexList. SpecialPowerModuleData::buildFieldParse at RVA 0x002683D0 stores this array address in its parser userData. These facts establish the bonus-source role; no evidence establishes an original EA variable spelling, so the existing role-bearing address name is retained. The definition is placed in SpecialPowerModuleData_buildFieldParse.cpp, the main table user.

The raw initial bytes are `d8 36 07 01 10 3a 07 01 04 3a 07 01 fc 39 07 01 f4 39 07 01 e8 39 07 01 e0 39 07 01 00 00 00 00`.

The reference inventory is a raw byte-pattern scan followed by instruction decoding at each containing ledger body. Each direct call or jump in those body logs follows every five-byte E9 in its chain. A pattern hit is a candidate until its instruction operand confirms a read, write or address transfer. The retail executable has no PE base-relocation directory; pointer fields are identified by the string/table use and checked against COFF DIR32 relocations, while the scalar quantizer and selector records contain no pointer relocations.

The receiver and argument contracts are visible in the body logs: indexed table loads use the datum directly; parser users pass its address as a names or userData argument; the selector constructors use ECX for their eight-word receiver and two stack pointers, while their paired readers take two stack output pointers. Team-key calls use ECX for StaticNameKey and return a 32-bit key without consuming a stack argument.

The data probe lists every nearby DIR32 name and every overlapping data row. No other DIR32 start lies strictly inside this chosen extent and no existing data row overlaps it. Neighboring padding is excluded. The competing spellings and their game declaration counts are in `build/rlink/identity-data-1791188974/spellings-declarations-before.log`; counts do not establish identity.

A different pointer string, a nonzero terminator, a code reference showing a conflicting element stride or use, a write requiring a different layout, an interior data/DIR32 start, or a different final E9 target would refute this correction. A reviewed original declaration can further refine constness that bytes alone do not prove.

Raw evidence is under `build/rlink/identity-data-1791188974`: `012a68b0-data.log`, `012a68b0.bin`, `table-audit.log`, `reference-bodies.csv`, `pins-nearby.log`, and `spellings-declarations-before.log`.

- `?get@Rva00268100ConstantGetter@@QAEPAXXZ` at `0x00668100` (6 bytes), source `game/GameEngine/Source/Common/Rva00268100ConstantGetter.cpp`, raw `body-00668100.log`.
- `?buildFieldParse@SpecialPowerModuleData@@SAXAAVMultiIniFieldParse@@@Z` at `0x006683D0` (745 bytes), source `game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleData_buildFieldParse.cpp`, raw `body-006683d0.log`.
- `?parseToken@Rva00368EA0BitFlagsParser@@QAE_NPBDPA_N1@Z` at `0x00768EA0` (405 bytes), source `game/GameEngine/Source/Common/BitFlagsParseToken.cpp`, raw `body-00768ea0.log`.
