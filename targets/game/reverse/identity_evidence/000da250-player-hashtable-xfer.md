# RVA 0x000DA250 transfers Player's AsciiString-keyed enum hashtable

The former GameSpyGroupRoom/callback description is misleading. Retail bytes
prove a Player serialization helper taking Xfer* and the table at Player
+0x200, with no use of incoming ECX. Its authentic C++ helper spelling and
whether it was originally static/member/template remain unknown.
All addresses use retail-1.03-unpacked lotrbfme.exe, base 0x00400000,
independently decoded with pefile and capstone.

## Calling owner and arguments

ILT RVA 0x0003959F reaches 0x000DA250 and has one direct caller: RVA
0x000DCF9F inside the 3401-byte serializer beginning 0x000DC270. This owner
is independently Player: primary table VA 0x010840CC has ILT 0x0001DD5E
at slot 3 (VA 0x010840D8), reaching 0x000DC270; the matched Player
constructor/deleting-destructor sources corroborate the table.

At 0x000DCF95 that serializer LEAs [EDI+200h], pushes the resulting table
pointer at 0x000DCF9B, pushes Xfer ESI at 0x000DCF9C, sets ECX=EDI, then
calls ILT 0x0003959F. This follows equivalent calls for Player+0x1D8 and
+0x1EC. The target reads Xfer from its first stack argument and table from
its second, uses RET 8 and never consumes the original incoming ECX.

The matched PlayerConstructor.cpp gives +0x200 as HashB: a native STLport
hash_map<AsciiString,Rva000D6C60Mapped> with enum mapped value. The leading
node pointer walk, bucket vector traversal and string/hash helper calls
are a hashtable traversal, not a GameSpy group-room pointer-range callback.
The nearby source filename alone cannot establish a class identity.

## Xfer virtual calls settle the subsystem

The target tests Xfer slot 2 (+8), which canonical matched xfer.h declares
IsStoring. It transfers count through slot 29 (+0x74), key through slot 26
(+0x68, AsciiString&) and mapped four-byte value through slot 30 (+0x78,
int&). Loads fetch a node value through helper 0x000D9870/ILT 0x00043C43.
All local string copy/destruction calls use StringBase<char>, not Unicode
StringBase<unsigned short>. These BFME virtual/callee facts refute the old
GameSpyGroupRoom/UnicodeString identity rationale.

The final RET 8 starts at 0x000DA3D8 and ends at 0x000DA3DB, followed by
INT3: 395 bytes. The verified opaque rva000da250 reconstruction uses these
proven Xfer/table contracts and matches all 395 bytes after relocation
resolution. ECX passed by the caller does not itself prove that this was an
authentic Player member. Its generic begin dependency has one opaque ABI
owner, documented in 000d0a30-opaque-begin-abi.md, and the native inline
hash_map begin wrapper preserves the retail aggregate-return temporary.
The exact source SHA256 is 848bcab6f89497f579e758e3828311bd18e326614c151c718d22e002e642ee9d.
Fresh strict production gates verify both the 395-byte body and 78-byte
dependency; this is source verification, not a fresh whole-program link.
