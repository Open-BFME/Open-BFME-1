# Writable FieldParse storage at RVA 0x00EBB650

The retail image SHA-256 is 1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75. Its image base is 0x00400000. Both extents lie in writable .data. This establishes storage and the callback contract; it does not establish the owning class.

## Primary extent and initializer

The 176 bytes at VA 0x012BB650 contain ten 16-byte descriptors followed by sixteen zero bytes. The fields are a token pointer, a four-argument cdecl callback, a userData pointer and a 32-bit instance offset. The original identity is ?g_012BB650@@3PAUFieldParse@@A.

| Descriptor VA | Token | Callback VA | userData VA | Offset |
|---|---|---|---|---|
| 0x012BB650 | Animation | 0x00B74FD0 | 0x00000000 | 0x2C |
| 0x012BB660 | StateName | 0x00C51EE0 | 0x00000000 | 0x0 |
| 0x012BB670 | Flags | 0x00C50E70 | 0x012BB5DC | 0x38 |
| 0x012BB680 | ShareAnimation | 0x00C52E00 | 0x00000000 | 0x40 |
| 0x012BB690 | EnteringStateFX | 0x00404B47 | 0x00000000 | 0x44 |
| 0x012BB6A0 | BeginScript | 0x00C522A0 | 0x00000000 | 0x48 |
| 0x012BB6B0 | FrameForPristineBonePositions | 0x00C52A60 | 0x00000000 | 0x3C |
| 0x012BB6C0 | FXEvent | 0x00B76A90 | 0x00000000 | 0x0 |
| 0x012BB6D0 | ParticleSysBone | 0x00B6E7B0 | 0x00000000 | 0x0 |
| 0x012BB6E0 | SimilarRestart | 0x00C52E00 | 0x00000000 | 0x6C |
| 0x012BB6F0 | (null) | 0x00000000 | 0x00000000 | 0x0 |

The EnteringStateFX callback is E9 34 43 0B 00 at VA 0x00404B47, which jumps to 0x004B8E80. The other eight distinct callback addresses start real bodies rather than E9 thunks. Existing matched rows bind the named callbacks. BeginScript can retain the existing address-derived provider ?d_008522a0@@YAXXZ at RVA 0x008522A0; no owner identity follows from the folded bfmeApplyVSO provider. A storage definition can cast that provider address to the actual four-argument cdecl callback type.

At VA 0x00B7D17A, the retail body stores its fourth argument at 0x012BB658, the first descriptor userData field. At 0x00B7D246 it pushes VA 0x012BB650 before calling INI::initFromINI with the local element. A byte-address scan of every raw section finds only these two external references into the primary extent. Its userData field must therefore remain writable. The original ordinary identifier occurs in exactly one game source, Rva0077D150ParseConditionState.cpp; its compiler references are the userData store and the table argument. The auxiliary identifier has no existing source users.

## Auxiliary extent and full strings

The 40 bytes at VA 0x012BB5DC are nine pointers followed by one null pointer. A byte-address scan of every raw section finds exactly one reference into this range: VA 0x012BB678 contains VA 0x012BB5DC. This is the Flags descriptor userData field. No existing data row, DIR32 identity or symbol pin intersects either extent. A bounded reconstruction can use the opaque identity ?g_00EBB5DC@@3PAPBDA.

| Index | String VA | Complete text before NUL |
|---|---|---|
| 0 | 0x01081700 | RANDOMSTART |
| 1 | 0x01123808 | START_FRAME_FIRST |
| 2 | 0x011237F4 | START_FRAME_LAST |
| 3 | 0x011237C4 | ADJUST_HEIGHT_BY_CONSTRUCTION_PERCENT |
| 4 | 0x011237A0 | MAINTAIN_FRAME_ACROSS_STATES |
| 5 | 0x01123780 | RESTART_ANIM_WHEN_COMPLETE |
| 6 | 0x0112375C | MAINTAIN_FRAME_ACROSS_STATES2 |
| 7 | 0x01123738 | MAINTAIN_FRAME_ACROSS_STATES3 |
| 8 | 0x01123714 | MAINTAIN_FRAME_ACROSS_STATES4 |
| 9 | 0x00000000 | (null) |

Every complete compiler-literal payload, including its terminal NUL, equals the bytes at the corresponding retail pointer. The complete payload check permits compiler-literal RVA pins without literal DIR32 identities or data ownership rows. The unchanged add_data_match.py independently verified a 40-byte bounded pointer array with nine relocations and a 176-byte bounded FieldParse array with 21 relocations, including every scalar and the complete null descriptors.

The Zero Hour reference GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp, lines 235 through 249, has ten flags including PRISTINE_BONE_POS_IN_FINAL_FRAME. Retail has nine and omits that entry. The reference therefore does not prove the identity ACBitsNames for this datum.

## Receiver and argument contract

INI::findFieldParse at RVA 0x00850880 walks records in 16-byte steps, stops on a null token, returns the callback from +4, obtains userData from +8 and the instance offset from +12. INI::initFromINIMulti at VA 0x00C519F2 through 0x00C51A13 pushes userData, instance plus offset, instance and INI in that order, calls the callback, then removes sixteen argument bytes. The callback contract is void __cdecl(INI *, void *, void *, const void *).

INI::parseBitString32 at RVA 0x00850E70 loads its fourth argument into EBP at VA 0x00C50E74, rejects a null list or null first entry, and loads its third argument into EDI at VA 0x00C50EB4. DWORD reads and writes through EDI implement flags. Calls at VA 0x00C50EEC, 0x00C50F08 and 0x00C50F3B push EBP as the second argument to the actual lookup at RVA 0x008509E0. The lookup advances through four-byte pointers until null and returns the matched index; that index selects 1 shifted left by index. Flags storage is instance +0x38. The second callback argument is unused by this parser.

The other callback bodies consume their arguments consistently with the descriptor offsets. parseAnimation reads the fourth argument as its mode; parseAsciiString and the opaque BeginScript provider write the third argument; parseBool writes one byte and parseInt writes one DWORD through the third argument. parseFXList resolves a token and writes a list pointer through the third argument. parseFXEvent and parseParticleSysBone use the instance argument at +0x50, with FXEvent also deriving +0x54 and +0x60. No function body, wrapper, alias or inheritance change is needed.

## Refuting observations

A nonzero byte in the null descriptor, a different callback target after following every E9 hop, any additional flag pointer before the null, a missing NUL or differing literal byte, an existing owner intersecting either extent, or a different fourth-argument name-list and third-argument DWORD contract would refute this storage reconstruction. A reference into either extent not accounted for by the stated scans would require a new boundary or user analysis. An unchanged data or source gate refusing the bounded definitions prevents landing the repair even when the retail evidence is conclusive.

## Compiled storage and unchanged checks

The bounded primary array preserves the existing ordinary declaration and defines genuine storage under its exact existing COFF identity through the compiler identifier. The auxiliary is a bounded ten-element pointer array under its opaque identity. There is one storage definition per datum, with no linker alias or additional caller. The unchanged normal data tool verifies both compiler allocation extents and every initialized byte. The unchanged original repair_queue.py CLI accepts the primary row and removes only its served exemption. All assigned source, ledger, pin and declaration gates pass.

Complete object comparison preserves every stable named CODE section, each relocation site and target, and recursively referenced compiler-local EH payloads. Compiler-local symbol numbering can change without changing those payloads. The complete initializer and CLI receipts are retained beside the original and candidate in build/rlink/ebb650-dependency-20261008/.
