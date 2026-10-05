# Datum identity at VA 0x012A687C

The chosen spelling is `BitFlags<10>::s_bitNameList` with type `const char *[11]`, size 44 bytes, in retail `.data`.

The ten entries are TAUNT, CHEER, HERO_CHEER, POINT, FEAR, UNCONTROLLABLE_FEAR, TERROR, DOOM, QUARRELSOME, ALERT, then null. The existing Drawable.cpp definition equals every retail entry. Retail getSingleBitFromName at RVA 0x0037A9D0 walks that pointer array; Parameter::getUiText at RVA 0x00352E80 indexes it for Emotion text. The reference BitFlags.h declares the private static pointer array.

The raw initial bytes are `d8 39 07 01 d0 39 07 01 c0 39 07 01 b8 39 07 01 b0 39 07 01 98 39 07 01 90 39 07 01 88 39 07 01 78 39 07 01 70 39 07 01 00 00 00 00`.

The reference inventory is a raw byte-pattern scan followed by instruction decoding at each containing ledger body. Each direct call or jump in those body logs follows every five-byte E9 in its chain. A pattern hit is a candidate until its instruction operand confirms a read, write or address transfer. The retail executable has no PE base-relocation directory; pointer fields are identified by the string/table use and checked against COFF DIR32 relocations, while the scalar quantizer and selector records contain no pointer relocations.

The receiver and argument contracts are visible in the body logs: indexed table loads use the datum directly; parser users pass its address as a names or userData argument; the selector constructors use ECX for their eight-word receiver and two stack pointers, while their paired readers take two stack output pointers. Team-key calls use ECX for StaticNameKey and return a 32-bit key without consuming a stack argument.

The data probe lists every nearby DIR32 name and every overlapping data row. No other DIR32 start lies strictly inside this chosen extent and no existing data row overlaps it. Neighboring padding is excluded. The competing spellings and their game declaration counts are in `build/rlink/identity-data-1791188974/spellings-declarations-before.log`; counts do not establish identity.

This private static template member already has exactly one source definition in `game/GameEngine/Source/GameClient/Drawable.cpp`. `tools/add_data_match.py` cannot name it for a sizeof probe, so it is retained without a data row, as the existing name tables are. `table-audit.log` compares every string pointer target and the terminator with retail. The chosen DIR32 spelling already exists at this address.

A different pointer string, a nonzero terminator, a code reference showing a conflicting element stride or use, a write requiring a different layout, an interior data/DIR32 start, or a different final E9 target would refute this correction. A reviewed original declaration can further refine constness that bytes alone do not prove.

Raw evidence is under `build/rlink/identity-data-1791188974`: `012a687c-data.log`, `012a687c.bin`, `table-audit.log`, `reference-bodies.csv`, `pins-nearby.log`, and `spellings-declarations-before.log`.

- `?m@Gen_00350110@@QAEIXZ` at `0x00750110` (6 bytes), source `game/gen_small/getters_000.cpp`, raw `body-00750110.log`.
- `?getUiText@Parameter@@QBE?AVAsciiString@@XZ` at `0x00752E80` (4012 bytes), source `game/GameEngine/Source/GameLogic/ScriptEngine/ParameterGetUiText.cpp`, raw `body-00752e80.log`.
- `?getSingleBitFromName@?$BitFlags@$09@@SAHPBD@Z` at `0x0077A9D0` (71 bytes), source `game/GameEngine/Source/GameClient/Drawable.cpp`, raw `body-0077a9d0.log`.
