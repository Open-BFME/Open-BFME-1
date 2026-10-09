# CastleBehavior packing at 0x00376C70

The complete reconstruction of `[0x00376C70, 0x00376F8C)` matches retail. Its emitted name is `?initiatePack@Rva00376C70@@QAEXXZ`. The retail CRC trace proves the semantic method name `CastleBehavior::initiatePack`. `Rva00376C70` is a non-owning receiver adapter with no declared fields or invented base classes. The source includes `CastleBehaviorRecovery.h` rather than defining a second CastleBehavior layout. That shared slice does not declare this member, and this assignment does not change shared headers.

The tested base revision is `1d420eb6792fca0c5ecbeeace4694608e16693ea`. The final source is `game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorInitiatePack.cpp`. Raw instructions, compiler trials and unedited tool output are preserved under `build/pack-00376c70/`. No Zero Hour implementation of this BFME-specific method supplied the body.

## Retry hypothesis and result

Earlier attempts left the object lookup out of line and did not reproduce the frame or float conversion sequence. The current landed `CastleBehaviorRva00371EE0StatusBit.cpp` contains the native inline object lookup, and `CastleBehaviorInitiateUnpack.cpp` supplies nearby packing declarations. I read those sources and verified their layouts against the actual instructions. The new hypothesis was that forced visibility of the native hash lookup, native model-condition bit accessors and typed Drawable calls would recover the missing inline code and scheduling. A failure to improve the measured body would refute that experiment.

| Preserved trial | Measured result | Change under test |
| --- | --- | --- |
| `trial01.cpp`, `probe01b.log` | 780 bytes with 243 non-relocation differences | Complete body with independently inlined hash walks and the retail frame size. |
| `trial02.cpp`, `trial02-probe.log` | 780 bytes with 239 non-relocation differences | Define the data pointer before the Object pointer. |
| `trial03.cpp`, `trial03-probe.log` | 779 bytes with 208 non-relocation differences | Use the existing typed Drawable calls around the virtual getter. |
| `trial04.cpp`, `trial04-probe.log` | 794 bytes with 71 non-relocation differences | Preserve native bitset reset and set operations. |
| `trial05.cpp`, `trial05-probe.log` | Exact | Use the native AsciiString accessor for the player name. |
| `trial06.cpp`, `trial06-probe.log` | Exact | Adopt the canonical AsciiString header. |
| `trial07.cpp`, `trial07-probe.log` | Exact | Include the shared CastleBehavior and GameLogic headers and remove the private receiver layout. |
| `trial08.cpp`, `trial08-probe.log` | Exact | Use canonical AsciiString access for the template name. |
| Final source, `final-objectid-probe.log` | Exact | Use the shared ObjectID declaration for all three vectors. |

Each exact result covers the entire retail extent with 27 relocation slots masked. The strict scoped gate additionally validates relocation destinations, the literal and the floating-point constant. The initial `probe01.log` failed because of a relative include path; it is retained and supplies no byte-match evidence. The hypothesis succeeded through source structure and canonical accessors, without register or x87 assembly experiments.

## Boundary, identity and receiver

`retail-target.txt` contains the complete target followed by padding. Its final instruction is `ret` at `+0x31B`, followed by INT3 at `+0x31C`. All conditional branches and loop backedges target instructions inside the function. The null-object path reaches the shared epilogue without the conditional EBX push. There is no external tail jump or EH registration in this target. `checked-callees.log` validates decoding of all 796 bytes and enumerates all twelve direct call targets.

`abi-evidence-corrected.log` reads the actual retail literal: `CAMP: Frame %d: Castle %s(%d) ::initiatePack(aka:DIE) called by %s`. The target passes this literal to the existing CRC logger. The receiver fields at `+4`, `+8`, `+0x9C`, `+0xA8`, `+0xB8`, `+0xC4`, `+0xDC` and `+0x108` agree with the surrounding CastleBehavior family. The complete constructor at `0x00376250` installs the update-interface vtable at receiver `+0x10`; its decoded output and callee inventory are in `retail-castle-ctor.txt` and `checked-castle-ctor.log`. The constructor is used here to anchor the receiver and interface adjustment. This recovery does not reconstruct its EH cleanup.

Both complete callers prove a no-argument thiscall receiver. `retail-caller1d1020.txt` and `checked-caller1d1020.log` retain the complete dispatcher extent. Its call through ILT `0x000427DF` uses ECX and supplies no stack argument. The update caller at `0x00377740` adjusts its interface receiver by `-0x10`, puts the resulting owner in ECX and calls the same thunk without a stack argument. `caller-switch.log` proves that its six switch destinations are instruction-aligned inside its 502-byte code extent. The remaining ledger bytes contain alignment and the six-entry jump table. `checked-caller77740-code.log` checks the code extent; the earlier failed linear decode of all 528 bytes is retained in `checked-caller77740.log`. Neither caller uses a result. The target's plain `ret` confirms zero stack arguments; it has no hidden return storage.

## Container value evidence

The three vectors contain ObjectID values, rather than Object pointers or small pairs. The complete `registerOwnedObject` body at `0x00373220` loads Object `+0x74` and passes the address of that scalar to the append thunk for receiver fields `+0xB8`, `+0xC4` and `+0xDC`. `retail-register-owned.txt` and `checked-register-owned.log` preserve the complete caller. ILT `0x000169CD` reaches `0x00152780`. Its complete append path copies one dword and advances by four bytes. Its overflow path at `0x001523D0` copies only one source dword per element in every prefix, insertion and suffix path. The complete decodes and checked extents are `retail-vectorappend.txt`, `checked-vectorappend.log`, `retail-vectoroverflow.txt` and `checked-vectoroverflow.log`. The shared ObjectID enum supplies the source declaration.

The GameLogic lookup at `+0xB0` maps a four-byte ObjectID key to an Object pointer. The complete `addObjectToLookupTable` body at `0x0038E490` reads Object `+0x74`, invokes subscript at `0x0038B980` through ILT `0x00005E11`, then stores the incoming Object pointer through the returned address. The complete subscript body compares node `+4` with the supplied key and returns node `+8`. Its insertion path constructs a two-field value whose second field starts at zero. The reached insertion helper at `0x00389A20` calls ILT `0x0002D074`, which reaches the complete 23-byte copy helper at `0x00385E30`. That helper reads source `+0` and `+4` and writes destination `+0` and `+4`, with no other field accesses on either return path. `retail-addlookup.txt`, `retail-hashsubscript.txt`, `retail-hashinsert-part.txt`, `retail-hashvalue.txt` and the corresponding `checked-*.log` files retain this evidence. Existing generated and STL pins name other byte-identical value instantiations; those names are not the type proof and no such pin or ledger row was changed.

The tree at CastleBehavior `+0x108` is cleared by the target. Its actual writer at `0x00373E30` builds a two-field value with a scalar index and initial zero, inserts it into that receiver field, then stores the GameLogic frame at node `+0x14`. The complete insert path at `0x000A3F30` performs signed key comparisons against node `+0x10`. Its reached node insertion at `0x000A3D70` copies the value through ILT `0x0002C3A4` to `0x000A36F0`. That complete copy helper reads and writes exactly two dwords. The complete eraser at `0x000A3660` recursively visits right and left links and releases nodes without a payload destructor. The EVA reader at `0x0036F4D0` reads the frame payload at node `+0x14`. These complete bodies and checked extents are retained as `retail-treewriter.txt`, `retail-treeinsert-part.txt`, `retail-treenodeinsert.txt`, `retail-treevalue.txt`, `retail-a3660.txt`, `retail-eva.txt` and their `checked-*.log` files. The final source declares only the four-field tree node header needed by clear, not an invented payload class. Allocation size alone was not used to establish either container value.

## Calls and canonical declarations

All routes below were resolved from decoded ILT instructions. Complete callee decodes and `checked_callees.py` outputs are retained in the named files. Arguments are listed in source order after the receiver.

| Actual body | Target contract | Raw evidence |
| --- | --- | --- |
| `0x0036F4D0` | Castle receiver; no argument; plain returns. | `retail-eva.txt`, `checked-eva.log` |
| `0x00375650` | Castle receiver; one Object pointer; all normal exits reach `ret 4`; result unused. The semantic method name stays unknown. | `retail-375650.txt`, `checked-375650.log` |
| `0x009F6E38` | Float on ST0; integer result in EDX:EAX; the caller retains EAX. All paths return without stack arguments. | `retail-ftol2.txt`, `checked-ftol2.log` |
| `0x00410D30` | Drawable receiver; one four-byte integer delay; `ret 4`. | `retail-410d30.txt`, `checked-delay.log` |
| `0x001BE1C0` | Object receiver; no argument. Its AI notification tail uses the adjusted AI receiver and no argument. | `retail-notifymodel.txt`, `checked-notifymodel.log`, `retail-notifyai.txt`, `checked-notifyai.log` |
| `0x001C7370` | Object receiver; pointer to three-dword BitFlags value, then a low-byte bool; `ret 8`. | `retail-setstatus.txt`, `checked-setstatus.log` |
| `0x0041AA90` | Drawable receiver; one low-byte bool in a stack slot; `ret 4`. | `retail-applypending.txt`, `checked-applypending.log` |
| `0x00371EE0` | Castle receiver; four-byte status index, then low-byte bool; `ret 8`. | `retail-371ee0.txt`, `checked-statusloop.log` |
| `0x000A3660` | Tree receiver; one node pointer; both paths use `ret 4`. | `retail-a3660.txt`, `checked-treeerase.log` |
| `0x001BE3F0` | Object receiver; no argument; Player pointer in EAX. The Team tail returns its controlling Player without extra arguments. | `retail-player.txt`, `checked-player.log`, `retail-teamplayer.txt`, `checked-teamplayer.log` |
| `0x00087A80` | Override receiver; no argument; final override pointer in EAX. | `retail-override.txt`, `checked-override.log` |
| `0x00065C80` | Cdecl logger; sink, format, frame, template name, ObjectID and player name. The target removes all six stack slots. | `retail-log.txt`, `checked-log.log` |

The virtual Object call is checked separately. The actual constructor-installed primary vtable is `0x0109EE58`; slot `+0x28` resolves through ILT `0x0002074D` to `0x001BE440`. That complete getter returns Object `+0x80` in EAX with no receiver adjustment or arguments. `abi-evidence-corrected.log` and `checked-getdrawable.log` retain the route and body. The first vtable check used an older header address and failed; `abi-evidence.log` is retained but is not supporting evidence. The final source uses the canonical Object virtual declaration, canonical AsciiString accessors, the shared ObjectID enum and the existing Drawable method pins. Its native model-condition accessors preserve the separate reset and set operations required by retail.

The target constructs no owning members and has no EH unwind states. Its only local status value is a zero-initialized three-dword bitset with bit 3 set. The constructor-specific cleanup check is therefore inapplicable to this body. Unknown helper semantics remain behind existing address-derived thunk names, with their independently decoded argument and return contracts. Static forced-inline adapters do not create a second strong definition of any landed helper. All image references use registered global symbols or source literals; no numeric image address appears in game source.

## Verification receipts

`final-objectid-probe.log` records the exact compiler result after canonical ObjectID adoption. `add-match.log` records the normal ledger replacement and its byte verification. `scoped-final.log` records the repository scoped gate on the ledger-backed source; `scoped-final-annotated.log` repeats that gate after adding the inline tree-clear annotation. `scoped-final-padding.log` verifies the final source after expressing the observed one-byte node color store and its three padding bytes explicitly. Pin consistency, class-gate and declared-definition checks pass in `pin-consistency-final.log`, `class-gate-final-padding.log` and `declared-unmatched-final-padding.log`. The CSV check in `check-csv-final.log` reports exactly one issue: the new source exists but is not tracked. This run prohibits Git writes, so the coordinator must stage the new source and rerun that check. No check was bypassed. The failed Windows launcher attempts are preserved in `scoped-launch-failure.log` and `scoped-python-launcher-failure.log`; the successful scoped gate invokes the repository build script through Git Bash. No shared header or shim changed, so this change does not require a full gate. Only this source and its evidence and ledger records are changed; no tooling, policy, baseline or symbol pin is changed.

The landed name is `?initiatePack@CastleBehavior@@QAEXXZ`, which the import thunk table confirms at this address, while it contradicts the address-derived `?initiatePack@Rva00376C70@@QAEXXZ` of the worker's draft. The shared CastleBehavior slice in `CastleBehaviorRecovery.h` gained the non-virtual member declaration; its layout is unchanged.
