# Datum identity at VA 0x012A75B8

The chosen spelling is `TheKey_teamName` with type `const StaticNameKey (mutable cached NameKeyType and const char *)`, size 8 bytes, in retail `.data`.

The first dword is zero and the second points to the exact EA string teamName. The reference Common/NameKeyGenerator.h declares StaticNameKey as a mutable 32-bit cached key and a const character pointer. Common/WellKnownKeys.h defines TheKey_teamName with that string and const object type. Common/RTS/Team.cpp reads these exact keys for team initialization. Retail ILT VA 0x00409304 is E9 87 6f 08 00 and reaches StaticNameKey::key at VA 0x00490290. That body reads receiver+0, reads receiver+4 when the key is invalid and writes the generated key back to receiver+0. Its contract is ECX receiver, no stack argument, enum/integer return. This refutes the competing Dict object spellings. The reference instantiates the keys in GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp.

The raw initial bytes are `00 00 00 00 28 c8 07 01`.

The reference inventory is a raw byte-pattern scan followed by instruction decoding at each containing ledger body. Each direct call or jump in those body logs follows every five-byte E9 in its chain. A pattern hit is a candidate until its instruction operand confirms a read, write or address transfer. The retail executable has no PE base-relocation directory; pointer fields are identified by the string/table use and checked against COFF DIR32 relocations, while the scalar quantizer and selector records contain no pointer relocations.

The receiver and argument contracts are visible in the body logs: indexed table loads use the datum directly; parser users pass its address as a names or userData argument; the selector constructors use ECX for their eight-word receiver and two stack pointers, while their paired readers take two stack output pointers. Team-key calls use ECX for StaticNameKey and return a 32-bit key without consuming a stack argument.

The data probe lists every nearby DIR32 name and every overlapping data row. No other DIR32 start lies strictly inside this chosen extent and no existing data row overlaps it. Neighboring padding is excluded. The competing spellings and their game declaration counts are in `build/rlink/identity-data-1791188974/spellings-declarations-before.log`; counts do not establish identity.

A different pointer string, a nonzero terminator, a code reference showing a conflicting element stride or use, a write requiring a different layout, an interior data/DIR32 start, or a different final E9 target would refute this correction. A reviewed original declaration can further refine constness that bytes alone do not prove.

Raw evidence is under `build/rlink/identity-data-1791188974`: `012a75b8-data.log`, `012a75b8.bin`, `table-audit.log`, `reference-bodies.csv`, `pins-nearby.log`, and `spellings-declarations-before.log`.

- `?rva000D1E30@Player@@QAEXABVAsciiString@@@Z` at `0x004D1E30` (830 bytes), source `game/GameEngine/Source/Common/RTS/PlayerRva000D1E30.cpp`, raw `body-004d1e30.log`.
- `?updateLoadProgress@GameLogic@@QAEXH@Z` at `0x004DB020` (3751 bytes), source `game/GameEngine/Source/Common/RTS/GameLogicUpdateLoadProgressThunk.cpp`, raw `body-004db020.log`.
- `?addSide@SidesList@@QAEXPBVDict@@@Z` at `0x004E0640` (897 bytes), source `game/GameEngine/Source/GameLogic/Map/SidesListAddSideThunk.cpp`, raw `body-004e0640.log`.
- `?initFromSides@TeamFactory@@QAEXPAVSidesList@@@Z` at `0x004F83C0` (260 bytes), source `game/GameEngine/Source/Common/RTS/Team.cpp`, raw `body-004f83c0.log`.
- `?composeTeamNameAt00195580@@YA?AVAsciiString@@PBVDict@@PA_N@Z` at `0x00595580` (275 bytes), source `game/GameEngine/Source/Common/RTS/Rva00195580TeamName.cpp`, raw `body-00595580.log`.
- `?isPlayerDefaultTeam@SidesList@@QAE_NPAVTeamsInfo@@@Z` at `0x005967F0` (380 bytes), source `game/GameEngine/Source/GameLogic/Map/SidesList_isPlayerDefaultTeam_Thunk.cpp`, raw `body-005967f0.log`.
- `?updateTeam@Rva0019BE80TeamRec@@QAEXH@Z` at `0x0059B850` (396 bytes), source `game/GameEngine/Source/GameLogic/Map/Rva0019B850TeamRecUpdate.cpp`, raw `body-0059b850.log`.
- `?apply@Rva0019BC00Owner@@QAEXHVAsciiString@@0@Z` at `0x0059BC00` (87 bytes), source `game/GameEngine/Source/GameLogic/Map/Rva0019BC00SetFields.cpp`, raw `body-0059bc00.log`.
- `?addPlayerByTemplate@SidesList@@QAEXVAsciiString@@@Z` at `0x0059C590` (722 bytes), source `game/GameEngine/Source/GameLogic/Map/SidesListAddPlayerByTemplate.cpp`, raw `body-0059c590.log`.
- `?validateSides@SidesList@@QAE_NXZ` at `0x0059C920` (1810 bytes), source `game/GameEngine/Source/GameLogic/Map/SidesList.cpp`, raw `body-0059c920.log`.
- `?fillHelper@Rva001A0320Owner@@AAEXHPAVRva0019A7D0Vector@@PAXPAVRva00197AE0Temporary@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z` at `0x0059F890` (900 bytes), source `game/GameEngine/Source/GameLogic/Map/Rva0019F890FillHelper.cpp`, raw `body-0059f890.log`.
- `?prepareForMP_or_Skirmish@SidesList@@QAEXXZ` at `0x005A0390` (2079 bytes), source `game/GameEngine/Source/GameLogic/Map/SidesList.cpp`, raw `body-005a0390.log`.
- `?dup_003865b0@@YAXXZ` at `0x007865B0` (655 bytes), source `game/GameEngine/Source/GameLogic/System/GameLogicDup003865B0.cpp`, raw `body-007865b0.log`.
- `?d_00392d00@@YAXXZ` at `0x00792D00` (2353 bytes), source `game/gen_asm/d_002e22f0.asm`, raw `body-00792d00.log`.

`MapObject.cpp` copied `INSTANTIATE_WELL_KNOWN_KEYS` from its WorldHeightMap source template and emitted duplicate strong definitions of all keys. The reference instantiates this key family only in `WorldHeightMap.cpp`. Removing that instantiation switch from MapObject leaves the existing canonical owner and changes no verified function bytes. `index-definitions.log` records the two pre-change strong definers. `literal-relocations.log` verifies the compiler literal spellings from each initializer against the exact retail strings before they are added to DIR32 addresses.
