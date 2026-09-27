# GameInfo::adjustSlotsForMap, 00620B00

The existing GameInfo vtable identifies this virtual at slot8, with four anchors
recorded in symbols.csv. The original GameInfo.cpp algorithm counts occupied
slots, then opens or closes each unoccupied slot according to the selected map's
player capacity. Retail has that same pair of eight-slot loops. The complete
native body is 00620B00..0062101C, 1308 bytes, through the terminal RET.

The recovered GameSlot connection record is eight bytes, independently proved
by setState0061F210 copying argument words0/4 to GameSlot+30/+34. Its IP is a
32-bit integer and its port is a 16-bit integer; padding remains native padding.
The parser proof00621c40-gameinfo-parser.md records the independent member layout
and string ABI. GameInfo stores its eight pointers at+14 and map name at+3C;
MapMetaData's player count is+20, matching the original map metadata layout.

The visible default GameSlot constructor initializes UnicodeString+28,
AsciiString+2C and connection+30, then calls reset. Its independent retail body
0061F0C0/82 performs exactly that work, installs VA01075D50 and calls reset through
ILT00017D7D. The authored GameSlot copy constructor0006E600/189 in
LANGameSlot_copy.cpp independently emits the SAME generic GameSlot vtable symbol
against VA01075D50. Its slot0 resolves to reset0061EC70/87; the two unused slots
point to address-derived three-byte null-return methods0006E6F0/0006E700.
The legacy BfmeOwnVSW vtable label is not new identity evidence or a new pin.

Native implicit GameSlot destruction releases its AsciiString and UnicodeString
without writing a vtable. This is independently consistent with retail destructor
00072490/77. An explicit user-provided empty destructor caused the compiler to
re-seat the vptr and allocate a saved receiver; the old bank's volatile stores
were unnecessary. The current source uses ordinary member construction,
assignment and implicit destruction, with no asm or volatile shaping.

All eight direct targets were read before reconstruction: MapCache::findMap
00454500 takes AsciiString by value and returns a const metadata pointer;
GameInfo::setSlot0061F630 takes an index and a complete by-value44-byte GameSlot;
GameSlot copy0006E600 takes const GameSlot&; the remaining five target contracts
are native StringBase<char/unsigned short> construction, release and assignment.
Strict resolution verifies20 encoded calls with zero unresolved targets.

Non-string data operands agree with independent owners: TheMapCache (native
map-cache callers), TheGameText VA012F147C (existing GameText callers), empty
UnicodeString VA01336E54 (the parser and existing WOL callback owners), and the
GameSlot vtable VA01075D50 (authored copy constructor). The two label addresses
resolve to GUI:Open and GUI:Closed. There is no new pin or shared-header change.

Verification: build/four-hour-adjustslots/strict-clean.txt and strict-result.json
show1308/1308 bytes exact with20 direct calls and33 object relocations; probe2.txt
also reports exact. Independent receipts are retail.asm, slot-ctor.asm and
callees.txt. Model GPT-6; t=10 minutes, starting from the existing bank and using
the newly recovered parser layout. Normal add_match and commit/push gates apply.
