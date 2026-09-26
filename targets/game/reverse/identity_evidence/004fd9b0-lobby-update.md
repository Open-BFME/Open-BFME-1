# WOLLobbyMenuUpdate, 004FD9B0

The retail FunctionLexicon record at VA012A9B88 is `{0,010868C4,00436AF2}`.
VA010868C4 contains `WOLLobbyMenuUpdate`; ILT 00036AF2 jumps to 004FD9B0.
FunctionLexicon.cpp supplies the same literal/callback pair. This independently
establishes the callback identity and its WindowLayout*/void* cdecl signature.

The full native extent is 4536 bytes (0x11B8). Executable bytes end with RET
at +1140, followed by three alignment bytes, the 16-address main switch table
at +1144, the 9-address join-result table at +1184, and the 4-address staging-action
table at +11A8. INT3 padding starts at 004FEB68. The old 4417-byte lift excluded
these tables; targets/game/reverse/lift_extents.csv independently records the
corrected 4536-byte extent. All tables participate in the exact scoped gate.

## BFME behavior and layouts

The initial transition changes have an increment/decrement critical-section
lifetime. The independent 31/90-byte native Glo00EF3330 methods at 004893E0 and
00489410 prove the two existing call contracts (through 000260EE/000204DC).
The callback checks the transition handler before each operation. Disconnect
tears down GameSpy and leaves the switch. Staging-player matching copies at most
255 nickname bytes and strips the final hyphen suffix before comparison. Retail
join-result 9 selects GUI:JoinFailedGameInPlay; the value retains an address-derived
label rather than asserting an unsupported SDK enumerator.

PeerResponseCopies.cpp independently proves the 0x330-byte response and string
prefix. Retail staging-payload accesses prove id/action+0/+4, flags+8/+9/+A,
version/checksums+C/+10/+14, opaque+18, port+1C, four eight-element player arrays
at +20/+40/+60/+80 and color+A0, counts+C0/+C4/+C8, completion+CC and stats+D0.
GameSpyStagingRoom's independent copy at 004FA490 and constructor 006385A0 prove
its 0x468-byte extent, GameInfo base 0x58 and eight 0x78-byte slots. Aligned accesses
place its name+418, ID+41C, password+428, allow-observers+429, version/checksums
+42C/+430/+434, opaque+438, ladder address+444 and port+450. Unsupported members
retain address/offset names. GameSlot's independently matched 440-byte setState
at 0061F210 takes SlotState, UnicodeString by value and const GameSlotConnectInfo*;
this caller initializes the connection temporary's DWORD+0 and WORD+4 to zero.

Visible private populateGroupRoomListbox, fillPlayerInfo and shutdown-complete
helpers reproduce their independent 310/262/88-byte retail bodies. The compiler-generated copy of the 32-byte GameSpyGroupRoom record uses
the existing copy contract; its visible string members reproduce each caller's
inline or out-of-line destruction lifetime. Canonical string
headers provide the native string representation. The unchanged reference TU
retains its generated EH funclet claims; no emission-only calls are introduced.

## Dependency ownership repairs, no new pins

* 004FB170, 51 bytes: the emitted map<AsciiString,PlayerInfo,AsciiComparator>::clear
  replaces a gen-tgrid integer/pair placeholder. The independent body tests the
  node count, erases the root and resets header links/count. Its call 00035F12
  reaches 004FA6A0, the already native 61-byte erase implementation owned by
  GameNetwork/GameSpy/PeerDefs.cpp with this exact typed container. The complete
  clear body and call resolve exactly, establishing identity beyond this caller.
* 004FD970, 51 bytes: list<PeerResponse>::push_back replaces the opaque
  list<Rva004FD970Element> ownership claim. The independent body allocates 0x338
  bytes (two links plus 0x330 response), constructs the payload and links it,
  returning with four-byte argument cleanup. Call 0003BB51 reaches 004FC4B0, whose
  guarded placement-copy constructor calls 0001E74F -> 004FB2E0, the independently
  native 426-byte PeerResponse copy. The canonical _Construct pin already exists.
  STLport's no-exceptions insertion implementation reproduces the entire 51 bytes;
  response construction/destruction in Update still retain their native C++ EH.

The two private helper clones also move ownership to the native Update TU:
populateGroupRoomListbox_004FA240 (310 bytes) and fillPlayerInfo_004F9920 (262
bytes) retain their independently proven retail bodies. Address-qualified local
names distinguish the separate Lobby/Overlay helper copies; otherwise the
resolver selects other existing helper addresses. No identity is inferred from
adjacency and no additional pins are needed.

All helpers pass complete scoped verification. The old generated and multi-body
opaque source files remain untouched. The 674 helper bytes are ownership repairs,
excluded from new native coverage. Only the 4536-byte naked callback replacement
is credited. No symbols.csv pins are added; pin-consistency and route checks pass.
