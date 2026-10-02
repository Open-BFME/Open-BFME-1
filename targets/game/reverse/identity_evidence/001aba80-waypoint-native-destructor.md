# Waypoint destructor at RVA 0x001ABA80

The Zero Hour twin is `GeneralsMD/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp:98` (`Waypoint::~Waypoint`). BFME constructors at 0x001AB600 and 0x001AB8B0, already byte-matched in `WaypointConstructor.cpp`, install the same vtable VA 0x0109C3DC and initialize the five string fields destroyed here (+8, +50, +54, +58, +64). The scalar deleting destructor at 0x001AC1B0 calls ILT 0x00035A21 to this body, then conditionally frees the object. This establishes the owner and destructor identity independently of the new match.

Retail PE bytes establish the extent: EH prologue at 0x001ABA80, final RET at 0x001ABB6A, then INT3 padding. Size is 235. The body unlinks the same +18/+1C doubly linked list used by the matched constructors and clears the same TerrainLogic+550 map.

The bank's handwritten string/cache declarations reproduced the instruction stream but mirrored ESI/EDI at 26 bytes. Reusing the constructors' native AsciiString and STLport map declarations removes the entire mirror. The resulting body is 235 bytes, exact modulo relocations before strict verification. No allocation trick or inline assembly is used.

Call targets were cross-checked against the retail PE and `callees.py`:

- Map clear calls ILT 0x0001FF82 -> 0x001A6D20, the same STLport erase specialization already used by both matched constructors.
- Five string destructions call StringBase<char>::releaseBuffer at 0x00887940, through the existing native header.
- The opaque trailing call uses ILT 0x0002E8A2 -> 0x00403860 (one RET byte followed by INT3). Retail pushes this and cleans four stack bytes; call through an explicit cdecl void(void*) function pointer preserves that observed ABI without inventing an identity or a pin.

The pre-existing BFME Waypoint declaration in the constructor TU is reused unchanged. The available ZH TerrainLogic header has a different linked-list layout and lacks BFME fields; it cannot substitute for that already-verified declaration.
