# Datum identity at VA 0x012A6670

The chosen spelling is `BitFlags<86>::s_bitNameList` with type `const char *[87]`, size 348 bytes, in retail `.data`.

The entries are the 86 object-status strings DESTROYED through BUILD_BEING_CANCELED followed by a null pointer. Every entry and terminating dword was compared with the existing Object.cpp definition. Retail getSingleBitFromName at RVA 0x001C09C0 walks pointers until null; buildDescription at RVA 0x00209130 reads them for each set status bit. The reference BitFlags.h declares a private static array of pointers to const characters, not an array of integers and not a const-pointer array. The existing Object.cpp specialization owns this definition.

The raw initial bytes are `90 36 07 01 80 36 07 01 68 36 07 01 58 36 07 01 48 36 07 01 3c 36 07 01 28 36 07 01 18 36 07 01 0c 36 07 01 00 36 07 01 f8 35 07 01 f0 35 07 01 ec 35 07 01 d8 35 07 01 c8 35 07 01 bc 35 07 01 b4 35 07 01 a8 35 07 01 98 35 07 01 90 35 07 01 78 35 07 01 64 35 07 01 54 35 07 01 40 35 07 01 30 35 07 01 1c 35 07 01 04 35 07 01 f0 34 07 01 d8 34 07 01 c4 34 07 01 b8 34 07 01 ac 34 07 01 a0 34 07 01 94 34 07 01 88 34 07 01 7c 34 07 01 64 34 07 01 54 34 07 01 48 34 07 01 34 34 07 01 2c 34 07 01 24 34 07 01 1c 34 07 01 14 34 07 01 0c 34 07 01 04 34 07 01 fc 33 07 01 f4 33 07 01 e8 33 07 01 d8 33 07 01 c8 33 07 01 bc 33 07 01 b0 33 07 01 a4 33 07 01 7c 33 07 01 70 33 07 01 64 33 07 01 50 33 07 01 44 33 07 01 34 33 07 01 28 33 07 01 0c 33 07 01 04 33 07 01 f8 32 07 01 e8 32 07 01 d8 32 07 01 c8 32 07 01 b8 32 07 01 9c 32 07 01 68 32 07 01 58 32 07 01 48 32 07 01 34 32 07 01 1c 32 07 01 fc 31 07 01 ec 31 07 01 d8 31 07 01 c4 31 07 01 b0 31 07 01 90 31 07 01 7c 31 07 01 68 31 07 01 58 31 07 01 44 31 07 01 34 31 07 01 18 31 07 01 00 00 00 00`.

The reference inventory is a raw byte-pattern scan followed by instruction decoding at each containing ledger body. Each direct call or jump in those body logs follows every five-byte E9 in its chain. A pattern hit is a candidate until its instruction operand confirms a read, write or address transfer. The retail executable has no PE base-relocation directory; pointer fields are identified by the string/table use and checked against COFF DIR32 relocations, while the scalar quantizer and selector records contain no pointer relocations.

The receiver and argument contracts are visible in the body logs: indexed table loads use the datum directly; parser users pass its address as a names or userData argument; the selector constructors use ECX for their eight-word receiver and two stack pointers, while their paired readers take two stack output pointers. Team-key calls use ECX for StaticNameKey and return a 32-bit key without consuming a stack argument.

The data probe lists every nearby DIR32 name and every overlapping data row. No other DIR32 start lies strictly inside this chosen extent and no existing data row overlaps it. Neighboring padding is excluded. The competing spellings and their game declaration counts are in `build/rlink/identity-data-1791188974/spellings-declarations-before.log`; counts do not establish identity.

This private static template member already has exactly one source definition in `game/GameEngine/Source/GameLogic/Object/Object.cpp`. `tools/add_data_match.py` cannot name it for a sizeof probe, so it is retained without a data row, as the existing name tables are. `table-audit.log` compares every string pointer target and the terminator with retail. The chosen DIR32 spelling already exists at this address.

A different pointer string, a nonzero terminator, a code reference showing a conflicting element stride or use, a write requiring a different layout, an interior data/DIR32 start, or a different final E9 target would refute this correction. A reviewed original declaration can further refine constness that bytes alone do not prove.

Raw evidence is under `build/rlink/identity-data-1791188974`: `012a6670-data.log`, `012a6670.bin`, `table-audit.log`, `reference-bodies.csv`, `pins-nearby.log`, and `spellings-declarations-before.log`.

- `?getSingleBitFromName@?$BitFlags@$0FG@@@SAHPBD@Z` at `0x005C09C0` (71 bytes), source `game/GameEngine/Source/GameLogic/Object/Object.cpp`, raw `body-005c09c0.log`.
- `?bfmeLookup@Gen_001C6300@@QBEHI@Z` at `0x005C6300` (45 bytes), source `game/GameEngine/Source/Common/Bfme5SixtySix.cpp`, raw `body-005c6300.log`.
- `?bfmeSaveBH@BfmeSubTwoBH@@QAEXPAVBfmeAgentBH@@@Z` at `0x005CB4E0` (471 bytes), source `game/GameEngine/Source/Common/BfmeConv1912.cpp`, raw `body-005cb4e0.log`.
- `?parseToken@Rva00204770BitFlagsParser@@QAE_NPBDPA_N1@Z` at `0x00604770` (441 bytes), source `game/GameEngine/Source/Common/BitFlagsParseToken.cpp`, raw `body-00604770.log`.
- `?buildDescription@?$BitFlags@$0FG@@@QBEXPAVAsciiString@@H@Z` at `0x00609130` (165 bytes), source `game/GameEngine/Source/Common/BitFlags86BuildDescription.cpp`, raw `body-00609130.log`.
- `?get@Rva0022A200ConstantGetter@@QAEPAXXZ` at `0x0062A200` (6 bytes), source `game/GameEngine/Source/Common/Rva0022A1F0A200ConstantGetters.cpp`, raw `body-0062a200.log`.
- `?parseRiderInfo@RiderChangeContainModuleData@@SAXPAVINI@@PAX1PBX@Z` at `0x0062A360` (184 bytes), source `game/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContain.cpp`, raw `body-0062a360.log`.
- `?gatherDebugStats@W3DDisplay@@` at `0x00AF0300` (4490 bytes), source `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayGatherDebugStatsThunk.cpp`, raw `body-00af0300.log`.
