# Datum identity at VA 0x012A68D8

The chosen spelling is `BitFlags<11>::s_bitNameList` with type `const char *[12]`, size 48 bytes, in retail `.data`.

The eleven entries are VETERAN, ELITE, HERO, PLAYER_UPGRADE, WEAK_VERSUS_BASEDEFENSES, ALTERNATE_FORMATION, MOUNTED, PLAYER_UPGRADE_2, PLAYER_UPGRADE_3, UNBESIEGEABLE, AS_TOWER, then null. Every entry equals the existing BattlePlanUpdate.cpp definition. Retail getSingleBitFromName at RVA 0x0020E380 walks this table, and xfer at RVA 0x0020F000 iterates exactly eleven bits before serializing their names. This establishes BitFlags<11>; BitFlags<116> is not an identity of this table. Object.cpp independently defines the 116-entry special-power table at VA 0x012A8D40.

The raw initial bytes are `a0 3a 07 01 98 3a 07 01 b8 41 07 01 84 3a 07 01 64 3a 07 01 80 3f 07 01 18 42 07 01 50 3a 07 01 3c 3a 07 01 2c 3a 07 01 20 3a 07 01 00 00 00 00`.

The reference inventory is a raw byte-pattern scan followed by instruction decoding at each containing ledger body. Each direct call or jump in those body logs follows every five-byte E9 in its chain. A pattern hit is a candidate until its instruction operand confirms a read, write or address transfer. The retail executable has no PE base-relocation directory; pointer fields are identified by the string/table use and checked against COFF DIR32 relocations, while the scalar quantizer and selector records contain no pointer relocations.

The receiver and argument contracts are visible in the body logs: indexed table loads use the datum directly; parser users pass its address as a names or userData argument; the selector constructors use ECX for their eight-word receiver and two stack pointers, while their paired readers take two stack output pointers. Team-key calls use ECX for StaticNameKey and return a 32-bit key without consuming a stack argument.

The data probe lists every nearby DIR32 name and every overlapping data row. No other DIR32 start lies strictly inside this chosen extent and no existing data row overlaps it. Neighboring padding is excluded. The competing spellings and their game declaration counts are in `build/rlink/identity-data-1791188974/spellings-declarations-before.log`; counts do not establish identity.

This private static template member already has exactly one source definition in `game/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp`. `tools/add_data_match.py` cannot name it for a sizeof probe, so it is retained without a data row, as the existing name tables are. `table-audit.log` compares every string pointer target and the terminator with retail. The chosen DIR32 spelling already exists at this address.

A different pointer string, a nonzero terminator, a code reference showing a conflicting element stride or use, a write requiring a different layout, an interior data/DIR32 start, or a different final E9 target would refute this correction. A reviewed original declaration can further refine constness that bytes alone do not prove.

Raw evidence is under `build/rlink/identity-data-1791188974`: `012a68d8-data.log`, `012a68d8.bin`, `table-audit.log`, `reference-bodies.csv`, `pins-nearby.log`, and `spellings-declarations-before.log`.

- `?Rva00122290Get@@YAPAXXZ` at `0x00522290` (6 bytes), source `game/GameEngine/Source/Common/Bfme/Rva00122290Get.cpp`, raw `body-00522290.log`.
- `?bfmeBuildABF@@YAXPAVMultiIniFieldParse@@@Z` at `0x005245F0` (97 bytes), source `game/GameEngine/Source/Common/BfmeConv2129.cpp`, raw `body-005245f0.log`.
- `?parseToken@Rva00141320BitFlagsParser@@QAE_NPBDPA_N1@Z` at `0x00541320` (405 bytes), source `game/GameEngine/Source/Common/BitFlagsParseToken.cpp`, raw `body-00541320.log`.
- `?getSingleBitFromName@?$BitFlags@$0L@@@SAHPBD@Z` at `0x0060E380` (71 bytes), source `game/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp`, raw `body-0060e380.log`.
- `?bfmeLookup@Gen_0020EC30@@QBEHH@Z` at `0x0060EC30` (39 bytes), source `game/GameEngine/Source/Common/Bfme5FortyOne.cpp`, raw `body-0060ec30.log`.
- `?xfer@BitFlagSnapshot0020F000@@QAEXPAVFlagXfer0020F000@@@Z` at `0x0060F000` (460 bytes), source `game/GameEngine/Source/Common/BitFlagSnapshot0020F000.cpp`, raw `body-0060f000.log`.
