# Retail data identities from VA 0x012A77A8 through VA 0x012AC510

Thirteen queried addresses have a conclusive datum identity. Twelve receive data rows; the already defined private `BitFlags<116>::s_bitNameList` receives corrected direct users and is verified entry by entry without a data row. VA 0x012A77A8 and VA 0x012A9200 remain unchanged because their remaining source contracts cannot be corrected conclusively in this run.

The retail image is `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`, image base 0x00400000. All fifteen objects are in `.data`. Raw per-address probes are `build/rlink/<eight-digit-lowercase-VA>-retail.log`. `extra-probe.log` records the complete selector record and all terminating table entries. `ranges.log` checks each exact range against every data row and DIR32 name and records the next named boundary. `literal-pins-initial.log` records compiled initializer bytes and every string relocation target. The image has no PE base-relocation directory; pointer fields are independently proven by the compiled initializers and consumer accesses, rather than a speculative pointer scan.

## Corrected objects

| VA | Chosen datum | Type and extent | Retail initial value and relocation count |
|---|---|---|---|
| 0x012A7918 | `TheKey_playerName` | `const StaticNameKey`, 8 bytes | `{0, "playerName"}`, one string pointer |
| 0x012A7920 | `TheKey_playerIsHuman` | `const StaticNameKey`, 8 bytes | `{0, "playerIsHuman"}`, one string pointer |
| 0x012A7930 | `TheKey_playerDisplayName` | `const StaticNameKey`, 8 bytes | `{0, "playerDisplayName"}`, one string pointer |
| 0x012A7938 | `TheKey_playerFaction` | `const StaticNameKey`, 8 bytes | `{0, "playerFaction"}`, one string pointer |
| 0x012A7940 | `TheKey_playerEnemies` | `const StaticNameKey`, 8 bytes | `{0, "playerEnemies"}`, one string pointer |
| 0x012A7948 | `TheKey_playerAllies` | `const StaticNameKey`, 8 bytes | `{0, "playerAllies"}`, one string pointer |
| 0x012A7988 | `TheKey_playerAIType` | `const StaticNameKey`, 8 bytes | `{0, "playerAIType"}`, one string pointer |
| 0x012A79D0 | `CameraYawAngleKey` | `StaticNameKey`, 8 bytes | `{0, "cameraYawAngle"}`, one string pointer |
| 0x012A7D38 | `g_ObfRecord012A7D38` | `BigObfSelectorRecord`, two five-element `unsigned int` arrays, 40 bytes | `162921CE 1CA40D0E C6F8CD0E D7F1AD0E 0; 5E893B8B 54885F4B C2D49F4B 9F5DBF4B 0`, no pointers |
| 0x012A8380 | `BezierSegment::s_bezBasisMatrix` | protected `const _D3DXMATRIX`, sixteen floats, 64 bytes | Bezier basis values detailed in `012a8380-BezierSegment-basis-matrix.md`, no pointers |
| 0x012A8D40 | `BitFlags<116>::s_bitNameList` | private `const char *[117]`, 468 bytes | 116 special-power string pointers and null |
| 0x012A9FE0 | `TimeOfDayNames` | `char *[7]`, 28 bytes | `NONE, MORNING, AFTERNOON, EVENING, NIGHT, INTERPOLATE, null`, six string pointers |
| 0x012AC510 | `ThingClassNames012AC510` | `const char *const[17]`, 68 bytes | sixteen ThingClass string pointers and null |

The complete initial bytes and pointer VAs are recorded in the raw probes. Each data-row addition runs `add_data_match.py`; its separate `add-data-<VA>.log` proves compiler `sizeof`, allocation bounds, exact retail bytes, and every relocation. There is no interior DIR32 name or overlapping datum in any accepted range. Array terminators are included in their extents; alignment bytes after a terminator are excluded.

## Key identity and receiver contract

Zero Hour `Common/NameKeyGenerator.h` declares `StaticNameKey` as a mutable `NameKeyType` cache followed by `const char *m_name`. `Common/WellKnownKeys.h` declares the six reference player keys as `extern const StaticNameKey`; `WorldHeightMap.cpp` instantiates those keys. Retail string pointers identify the names independently of the existing pins. `playerAIType` is a BFME extension proven by the shipped string and its Dict users; it retains the established `TheKey_` naming convention rather than an invented semantic name. The existing `CameraYawAngleKey` pin identifies the remaining key.

Every witnessed key call places the global's address in ECX and calls ILT RVA 0x00009304. The exact five bytes `E9 87 6F 08 00` at VA 0x00409304 jump to body VA 0x00490290. That 33-byte body compares receiver word zero with zero, loads the name pointer at receiver+4, calls the name generator, writes the generated key back to receiver word zero, and returns EAX with a plain `ret`. `key-accessor.log` contains the disassembly. The cache write is the observed runtime write to each key; the name pointer is read. The trailing const decoration does not imply read-only storage because the cache is mutable.

The per-address raw files name and disassemble the direct users, including Player, PlayerList, SidesList, the fill helpers, and W3DView. The relevant calls follow the real key thunk, not the old invented `GenKey` ABI. The camera fallback load now declares the actual `Dict::getReal(NameKeyType, bool *) const` contract: the flag pointer pushed before the key call belongs to the subsequent Dict call, and the key takes no argument. The instruction bytes remain unchanged. A different key string, a callee that consumes a stack argument, a wider receiver, or a different final ILT destination would refute these corrections.

## Selector record

Retail RVA 0x0009A430 indexes both arrays with `rdtsc & 3`, stores the second array's value into the receiver, and uses the first array's value in its xor chain. RVA 0x00099350 reads the same two arrays and stores the values through output arguments. `selector-reader-exact.log`, `selector-constructor-exact.log` and `012a7d38-retail.log` record those accesses; `extra-probe.log` records all ten dwords. These are numeric xor inputs, not pointers. The old pointer-array record view is removed only for this address. Its reader retains the existing output ABI and casts the numeric words into the existing raw-word carriers without dereferencing them. No retail body observed by this probe writes the global record. A dereference of these entries, an independent name inside the 40-byte extent, or an initializer mismatch would refute this interpretation.

## Special-power, time-of-day and ThingClass tables

The special-power table has exactly 116 names and null at VA 0x012A8F10. Retail RVA 0x001C0A30 is the established `BitFlags<116>::getSingleBitFromName` lookup and scans this table as pointers until null. The named transfer at RVA 0x001CB730 tests a 116-bit mask and loads names from this address. The getter at RVA 0x000EB110 returns the same address, and the indexed reader at RVA 0x001C6390 loads four-byte entries. The existing definition in `GameLogic/Object/Object.cpp` already contains all 116 verified entries; the raw initializer probe independently rechecks every entry and the null. The three direct invented-array declarations are respelled to that existing private member's exact external spelling. `add_data_match.py` refuses to size a private template member (`data-private-size-probe.log`), so no data row is added for this table, as permitted by the identity-seat instructions. All 116 pointer targets are verified, and its exact DIR32 spelling is present. An unverified generic `BitFlags<13>` COMDAT reference in Object.cpp is not evidence that this table belongs to a thirteen-bit specialization; that existing broad-port blocker remains for a separate body-identity question.

Zero Hour `Common/System/GameType.cpp` defines mutable `char *TimeOfDayNames[]`. Retail retains that use and adds `INTERPOLATE` before the terminating null at VA 0x012A9FF8. `INI::parseWaterSettingDefinition` at RVA 0x000C37E0 scans the pointer array, and the time-of-day parser at RVA 0x00778000 passes its address to `INI::scanIndexList`. No observed direct consumer writes the table. The array is defined in the existing main-user INIWater translation unit because the reference GameType translation unit is absent from this tree.

The sixteen strings at VA 0x012AC510 describe ThingClass values. The retail ThingTemplate FieldParse entry has keyword `ThingClass`, the byte-sized index parser, table pointer VA 0x012AC510, and destination offset 0x496. The builder at RVA 0x0013B990 sign-extends the byte at template+0x496 and indexes the same pointer table. `ranges.log` records the retail data-table pointer candidate; the byte-verified native `ThingTemplate::s_objectFieldParseTable` provides the structured interpretation. `ThingClassNames012AC510` describes the confirmed role while retaining the address because the original EA variable name is not known. The competing `Strip::Stripify::s_mod` spelling is misplaced: the actual modulo table is integer `{0,1,2,0,1,2}`, whereas this datum consists of sixteen string pointers and null. The real modulo source is not renamed to a ThingClass table. No observed consumer writes the ThingClass pointers. Different FieldParse user data, numeric rather than string entries, or a builder reading another offset would refute these table interpretations.

## Unresolved addresses

At VA 0x012A77A8, retail conclusively contains `{0, "waypointName"}` with the same eight-byte key layout and key thunk. The existing setter reconstruction nevertheless treats the first call as a `Dict::setAsciiString(AsciiString)` returning a pointer. Replacing that view with the reference's key getter and `Dict::setAsciiString(NameKeyType, const AsciiString&)` changes the verified 31-byte setter's argument setup from `mov eax,[esp+4]` to a stack-address `lea`; `build-group-2-fixed.log` contains both byte sequences. That source is restored, and no data row or new literal pin is kept for this address. The getter and static initializer independently prove the key identity, but the setter's string parameter contract must be established from a named caller before respelling its declaration without hiding the ABI dispute.

At VA 0x012A9200, retail contains eleven disabled-state string pointers and null, giving a 48-byte table. RVA 0x001C0870 scans it; RVA 0x001C4CC0 indexes its strings during transfer; RVA 0x0029C7B0 uses it for bit-token parsing. Zero Hour `Common/System/DisabledTypes.cpp` establishes the role but contains thirteen names. The old `BitFlags<67>` spelling has no independent width proof, while assigning `BitFlags<11>` would conflict with the separately proven armor table at VA 0x012A68D8. The existing evidence file `bitflags-name-lookup-family.md` records the same unresolved specialization. A named disabled-mask member with an independently verified BFME width and use of this exact table would settle the identity. No source, data row, DIR32 spelling or pin for this address is changed.

## Spelling measurements and verification

`objects-before.log` records every exact competing decoration emitted by the 24 affected or owning source objects and its file count, before edits. Counts are explicitly scoped to those compiled objects, not a claim about every incidental generic declaration in the tree. `game-declarations-start.log` contains the independent repository-wide textual declaration/use search. The chosen names follow the retail and reference evidence rather than popularity. `declaration-counts-fixed.log` records the full direct-declaration inventory separately.

All new literal DIR32 records are additive and each points at the byte-verified retail string used by its initializer. No existing symbols.csv pin is rewritten or deleted. The matrix constructor correction additionally tombstones the wrong tag spelling and preserves the remaining ledger records' original relative order. Verification and the per-file LINKED measurements are recorded in `build/worker-final.md`, with raw logs under `build/rlink/`.

The following pre-edit counts are derived from that direct-declaration inventory. A generic template emission is counted in its emitting file; it is not independent identity proof.

| VA | Competing decorated spelling | Declaring game files |
|---|---|---|
| 0x012A77A8 | `?TheKey_waypointName@@3VStaticNameKey@@B` | 1 |
| 0x012A77A8 | `?g_theWaypointNameDict@@3VDict@@A` | 1 |
| 0x012A7918 | `?GenKey0012A7918@@3VGenKey@@A` | 2 |
| 0x012A7918 | `?TheKey_playerName@@3VStaticNameKey@@A` | 0 |
| 0x012A7918 | `?TheKey_playerName@@3VStaticNameKey@@B` | 8 |
| 0x012A7918 | `?g012A7918@@3VStaticNameKey@@A` | 0 |
| 0x012A7920 | `?TheKey_playerIsHuman@@3VStaticNameKey@@A` | 1 |
| 0x012A7920 | `?TheKey_playerIsHuman@@3VStaticNameKey@@B` | 2 |
| 0x012A7920 | `?g012A7920@@3VStaticNameKey@@A` | 1 |
| 0x012A7930 | `?TheKey_playerDisplayName@@3VStaticNameKey@@B` | 2 |
| 0x012A7930 | `?g012A7930@@3VStaticNameKey@@A` | 1 |
| 0x012A7938 | `?TheKey_playerFaction@@3VStaticNameKey@@B` | 4 |
| 0x012A7938 | `?g012A7938@@3VStaticNameKey@@A` | 1 |
| 0x012A7940 | `?TheKey_playerEnemies@@3VStaticNameKey@@A` | 1 |
| 0x012A7940 | `?TheKey_playerEnemies@@3VStaticNameKey@@B` | 2 |
| 0x012A7940 | `?g012A7940@@3VStaticNameKey@@A` | 1 |
| 0x012A7948 | `?TheKey_playerAllies@@3VStaticNameKey@@A` | 1 |
| 0x012A7948 | `?TheKey_playerAllies@@3VStaticNameKey@@B` | 2 |
| 0x012A7948 | `?g012A7948@@3VStaticNameKey@@A` | 1 |
| 0x012A7988 | `?GenKey0012A7988@@3VGenKey@@A` | 1 |
| 0x012A7988 | `?g012A7988@@3VStaticNameKey@@A` | 1 |
| 0x012A79D0 | `?CameraYawAngleKey@@3VStaticNameKey@@A` | 1 |
| 0x012A79D0 | `?GenKey0012A79D0@@3VGenKey@@A` | 1 |
| 0x012A7D38 | `?g_ObfRecord012A7D38@@3UBigObfSelectorRecord@@A` | 1 |
| 0x012A7D38 | `?g_twoBitSelectorRecord012A7D38@@3UTwoBitSelectorRecord@@A` | 1 |
| 0x012A8380 | `?s_bezBasisMatrix@BezierSegment@@1UD3DXMATRIX@@B` | 4 |
| 0x012A8380 | `?s_bezBasisMatrix@BezierSegment@@1U_D3DXMATRIX@@B` | 2 |
| 0x012A8D40 | `?g_bfmeTableENb@@3PAHA` | 1 |
| 0x012A8D40 | `?names1CB730@@3PAPBDA` | 2 |
| 0x012A8D40 | `?s_bitNameList@?$BitFlags@$0HE@@@0PAPBDA` | 1 |
| 0x012A8D40 | `?s_bitNameList@?$BitFlags@$0N@@@0PAPBDA` | 1 |
| 0x012A9200 | `?g_bfmeTableDJa@@3PAHA` | 2 |
| 0x012A9200 | `?s_bitNameList@?$BitFlags@$0ED@@@0PAPBDA` | 1 |
| 0x012A9200 | `?s_bitNameList@Rva0029C7B0BitFlagsParser@@0QBQBDB` | 1 |
| 0x012A9FE0 | `?Rva00778000TimeOfDayNames@@3QBQBDB` | 1 |
| 0x012A9FE0 | `?TimeOfDayNames@@3PAPADA` | 1 |
| 0x012AC510 | `?g_012AC510@@3QBQBDB` | 2 |
| 0x012AC510 | `?s_mod@Stripify@Strip@@0PAHA` | 1 |
