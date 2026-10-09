# 0x0035E030 copy-constructor reconstruction

## Collection decision

Bank the complete C++ constructor. Do not claim a recovery or edit the function ledger or STL pins during the STLport pause. The final candidate has the exact 352-byte parent shape with relocation slots masked, but the strict scoped byte gate fails. The original owner remains unknown and the candidate keeps the address-derived `Rva0035E030` name. Reopening requires permission to repair the relevant STL helper bindings, review the scalar payload interpretation, and reconcile the embedded catch row with the complete parent extent.

The tested checkout revision is `fa85ca905773144924bb9a4c345cba7df32052f1`. Raw retail decodes, compiler probes, helper comparisons and strict gate output are retained under `build/target-0035e030/`. These files must be collected with the bank because the build directory is untracked.

## New hypothesis and refutation

The newly available complete 605-byte reconstruction in `game/GameEngine/Source/Common/Rva0035CEE0StringRecordCopy.cpp`, the actual 107-byte value constructor in `game/GameEngine/Source/Common/Open2Construct.cpp`, and the separately decoded record cleanup helpers make an address-derived native-container constructor testable. Earlier records supplied no candidate. The hypothesis is that this constructor copies its first word range, initializes a second record vector, reserves storage, deep-copies each record into a temporary, pushes a shallow memberwise copy into the vector, and releases only the temporary string on success. An inner catch drains the temporary nodes if insertion throws. An outer catch drains all successfully inserted records. The complete parent, copy helper and unwind maps can refute the proposed field offsets, ownership, ABI or catch scopes independently of a masked parent match.

## Boundary and caller ABI

The decoded target begins at `0x0035E030`. Its conditional branch at `+0xB4` reaches `0x0035E17B`, and the normal epilogue ends with `ret 4` at `0x0035E18D`. The complete contiguous extent is therefore 352 bytes, ending at `0x0035E190`. The 307-byte ledger head ends immediately after a rethrow call and contains no normal return. The existing 24-byte `0x0035E163` catch row lies inside the complete parent. No catch row was changed.

The complete 123-byte caller at `0x0035E3B0` computes source `+0x0C`, pushes it, sets ECX to destination `+0x0C`, and calls ILT `0x0002BA7B`. Its decoded jump reaches `0x0035E030`. The target consumes one four-byte source address, receives its destination in ECX, returns that destination in EAX, and pops four argument bytes. There is no hidden return-storage argument in this constructor. The earlier pin `NestedAt0C` is ABI screening evidence and does not establish an original owner identity.

Raw evidence: `retail-decode.log`, `thunks-decode.log`, `callees-full.log`, and `callees-caller.log` in the retained build folder. Complete decoded extents have no unexplained outgoing conditional branches. The temporary record destructor is a tail jump at `0x00351970`; it adjusts ECX by eight and reaches StringBase release at `0x00887940`.

## Payload and ownership evidence

The actual deep-copy callee is `0x0035CEE0`, reached through ILT `0x0001CADF`. Its entire 605-byte body was decoded, including its catch and both normal destructor-tail return paths. It copies dwords at `+0x00` and `+0x04`, assigns the canonical AsciiString at `+0x08`, copies the byte at `+0x0C` and word at `+0x0E`, zeros the node pointer at `+0x10`, and reconstructs the source node chain. Byte `+0x0D` is not copied. The actual shallow value constructor at `0x00355050`, reached through ILT `0x00036C2D`, copies those same scalar fields and the node pointer, invokes StringBase copy at `0x00887B60`, and skips `+0x0D`. It is a two-argument cdecl placement-copy helper with a plain return.

The candidate uses the existing descriptive `Rva00359330Record` field names and canonical `ascii_string.h`. `Open2Gap<1>` represents the untouched padding byte using the same empty-copy mechanism as the inspected Open2Construct donor. An ordinary char member at that offset was experimentally rejected: it emitted a 113-byte value helper with 28 differing bytes over the 107-byte retail helper. The corrected padding emits a 107-byte helper with zero differences outside its relocation slots. The parent constructor is unchanged by this type correction, demonstrating why the parent-only masked match was insufficient.

The second container lies at owner `+0x0C` and stores twenty-byte records. The source counts at `+0x18` and `+0x1C` are copied as dwords. The successful temporary destruction releases its name and leaves the transferred node chain in the vector element. The inner cleanup calls `clearRva00359330Nodes` at `0x003593F0`; its complete 54-byte body drains the `+0x10` chain. The outer cleanup calls `bfmeUnregister` at `0x0035AC30`; its complete 92-byte body drains each element's nodes, steps the finish pointer backward by twenty bytes, and invokes the element destructor. The vector destructor at `0x0035A980` then destroys remaining strings and frees storage with scalar delete or the small-block deallocator. These cleanup bodies and every return path were decoded.

The first container is a contiguous four-byte range copied with the imported `MSVCR71.dll!memmove` at IAT slot `0x0135945C`. Its cleanup at `0x000D0190` releases the allocation without element destruction. The independently decoded lower-bound sibling `0x003568C0` reads a word from a same-layout leading range, multiplies that value by twenty, and indexes the record array at owner `+0x0C`. This supports the candidate's `int` index representation, but the constructor itself only copies raw words. The original owner relationship and payload signedness are not independently established by this constructor or by the matching native template. Keep that interpretation provisional when collecting this bank.

Raw evidence: `retail-decode.log`, `cleanup-and-vector-decode.log`, `type-siblings-decode.log`, `callees-copy.log`, `callees-value.log`, `callees-cleanup-index.log`, `callees-cleanup-records.log`, `callees-cleanup-record.log`, `callees-unregister.log`, `callees-clear-nodes.log`, `callees-index-type.log`, and `callees-release-type.log`.

## Exception metadata

Retail FuncInfo has seven states. Its predecessors are `[-1, 0, 1, 2, 3, 3, 1]`. The compiled candidate agrees in every state. State zero destroys the first vector on the saved owner at `[ebp-0x14]`; state one destroys the record vector at owner `+0x0C`; state three destroys the temporary at `[ebp-0x28]`. The compiled adjustment instructions agree with the retail cleanup actions. The corresponding native cleanup bodies match the retail helper shapes with relocation slots masked, but their final symbol bindings have not passed a strict gate.

Both catch-all descriptors have zero adjectives, type and catch-object displacement. The inner try range is `[4,4]` with catch-high state five and handler `0x0035E14E`. The outer try range is `[2,5]` with catch-high state six and handler `0x0035E163`. The candidate agrees in both ranges and catch counts. Reserve precedes the outer try, and deep copy precedes the inner try. Raw evidence: `eh-retail.log`, `eh-cleanup-actions.log`, `eh-compare04.log`, and `helper-compare04.log`.

## Measured experiments

| Source | Complete retail extent | Emitted bytes | Differing bytes outside relocation slots | First difference |
| --- | ---: | ---: | ---: | --- |
| `trial01.cpp` | 352 | 350 | 144 | `+0x9E` |
| `trial02.cpp` | 352 | 348 | 99 | `+0xB6` |
| `trial03.cpp` | 352 | 352 | 0 | None in the parent; padding copy helper still wrong |
| `trial04.cpp` | 352 | 352 | 0 | None in the parent; padding copy helper corrected |

Trial one put reserve inside the outer try and reloaded the source end each iteration. Trial two moved reserve before that try and captured the source end once. Trial three moved deep copy before the inner try, restoring the retail transition from state three to state four. Trial four replaced the copied padding member with the inspected non-copying gap. All trial sources and the unedited `probe01-full.log` through `probe04-full.log` remain available.

The required mechanical EH generator ran before hand iteration. Its sixteen measured variants did not improve trial one. It tested callee `throw()` declarations, the `/EHsc` toggle and nothrow array delete in finite combinations; its trial sources and measurement manifest remain in `build/shape_search/41562799d0614e11974a2e0c401808ca/`, with raw output in `eh-search.log`. No register-only or x87 experiments were used.

Eight emitted native helper shapes were compared independently over their complete retail sizes: allocator return (7), first-vector base constructor (130), record reserve (160), record placement copy (107), record insertion overflow (287), first-vector destructor (45), record-vector destructor (167), and record destructor (8). After the padding correction, each has zero differences outside relocation slots. These comparisons are shape evidence and do not authorize new pins.

## Remaining strict gate failures

`gate04.log` is the unedited result of the repository's `build.verify_functions` scoped to this candidate over 352 bytes, without changing any ledger row or symbol map. It reports four unresolved names and one mismatched existing binding:

| Emitted helper | Parent relocation offset | Required retail route |
| --- | --- | --- |
| `?get_allocator@?$vector@HV?$allocator@H@_STL@@@_STL@@QBE?AV?$allocator@H@2@XZ` | `+0x30` | `0x0003CF51 -> 0x001F8F80` |
| `??0?$_Vector_base@HV?$allocator@H@_STL@@@_STL@@QAE@IABV?$allocator@H@1@@Z` | `+0x41` | `0x000212D3 -> 0x001F9330`; current candidates select `0x00066A90` |
| `?reserve@?$vector@URva00359330Record@@V?$allocator@URva00359330Record@@@_STL@@@_STL@@QAEXI@Z` | `+0xA0` | `0x00038FA0 -> 0x00359A80` |
| `??$_Construct@URva00359330Record@@U1@@_STL@@YAXPAURva00359330Record@@ABU1@@Z` | `+0xE7` | `0x00036C2D -> 0x00355050` |
| `?_M_insert_overflow@?$vector@URva00359330Record@@V?$allocator@URva00359330Record@@@_STL@@@_STL@@IAEXPAURva00359330Record@@ABU3@ABU__false_type@2@I_N@Z` | `+0x106` | `0x000396AD -> 0x0035AFC0` |

The unwind cleanup symbols also need independently verified bindings before a landing: `??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ` through `0x0001627A -> 0x000D0190`, `??1?$vector@URva00359330Record@@V?$allocator@URva00359330Record@@@_STL@@@_STL@@QAE@XZ` through `0x00017E63 -> 0x0035A980`, and `??1Rva00359330Record@@QAE@XZ` through `0x0004884C -> 0x00351970`. No pin was added or changed.

The current banking measurement uses the ledger's 307-byte extent. A 352-byte exact masked parent consequently receives a lower preferred-bank score because the measuring tool penalizes the additional 45 bytes. The explicit 352-byte probe is the authoritative shape measurement. Neither score substitutes for callee binding, payload evidence or a passing byte gate.

Class gate passes for the candidate. Pin consistency passes on the unchanged symbol map. The declared-function check refuses the scratch candidate because it has no matched ledger row; there is no landed source claim to validate. No full gate is required by these bank-only changes, and none was run.
