# 0x002440E0: declaration and helper-contract retry

## Result

No source recovery landed. The preferred body at `targets/game/reverse/attempts/0x002440e0.cpp` remains byte-for-byte unchanged. New declaration, native-value-constructor and helper-visibility experiments did not improve its measured shape. The scoped byte gate fails on unresolved calls and unequal instructions. There are no ledger, symbol-pin or shared-header edits.

The tested revision is `cbcb79d0784092768988547a74ad9640d84a4b42`. The model is `gpt-6.1-sol`. Raw trial sources, compiler/probe output and decoded instructions are retained in `build/2440e0-retry/`; `measurements.json` is generated from the unedited probe logs. `build/verdict.txt` records the running verdict.

## New evidence and refutable hypotheses

The landed neighbours `MemberGoalRefresh00243EA0.cpp`, `Rva00244080.cpp` and `MemberSelection00244680.cpp` confirm the adjusted receiver, member-list access and several callee routes. The current `PathfinderRva003E49F0.cpp` supplies a complete implementation of helper `0x003E4680`. The current `Rva002459D0HordeMemberAdd.cpp` and `Rva00245010RecordBuild.cpp` lead to the actual map value and vector record constructors. These additions address earlier missing helper and field contracts. They do not supply the target's missing compiler lifetime or stack-slot arrangement.

The new hypothesis was that authentic declaration or helper visibility could reproduce the receiver/argument allocation and the two-step primary-map adjustment. Its refutation condition was an unchanged or worse measured target body after introducing that evidence. An inline primary accessor, the canonical Object fields, a C++ secondary-base downcast and authentic Pathfinder helper visibility all leave the baseline target shape unchanged. The Pathfinder visibility trial's helper itself is masked-byte exact, but that establishes neither a new recovery nor the target's relocation correctness. The parent-resolver visibility trial leaves the target unchanged; its separately measured helper still differs, so it is weaker evidence and is not claimed exact.

A second hypothesis was that calls through the existing typed ILT routes or the canonical `BfmeMemberIndexMap::find` declaration would correct the bank's unresolved route declarations and improve layout. Each complete candidate was probed. These variants increase the frame and/or mismatch count. The isolated typed-map trial also worsens the shape. Explicit record constructors derived from the complete constructor/copy helpers leave the target unchanged. Generic register renaming, prior literal-line tail merging, local rotations and exhausted finite families were not repeated as a search campaign.

## Boundary and ABI evidence

`002440e0.asm` decodes the complete target. Its sole return is `ret 4` at `+0x478`; the extent ends immediately after that instruction. Every decoded branch destination lies inside the extent on an instruction boundary. Both the early-null and loop-completion paths restore the frame through that epilogue. There is no outgoing tail jump or exception-registration frame. The argument is used as an Object-compatible pointer and the receiver as an adjusted subobject pointer. The original C++ owner remains unproven.

Every direct callee used below was fully decoded and checked with `checked_callees.py`. `control-flow.json` lists the extents, every return and outgoing branch result; the corresponding `*-checked.log` files retain the tool's raw output. All listed extents decode completely with internal instruction-aligned branches and no outgoing tail jumps. These checks support the analysed boundaries and do not independently establish semantic names.

| Retail route | Complete helper | Observed contract |
|---|---|---|
| `0x0000FAA6` | `0x001CB020` | Object-compatible receiver; one stack slot consumed with `ret 4`; low byte of the flag is tested; EAX returns an object pointer or null. |
| `0x0001F000` | `0x002230A0` | Map receiver; hidden iterator storage followed by a key pointer in source argument order; `ret 8`; writes one node pointer and returns the storage address in EAX. |
| `0x0003251F` | `0x000A2CF0` | Thing-compatible receiver and one kind slot; `ret 4`; caller consumes AL. |
| `0x00027AB6` | `0x003E4680` | Pathfinder receiver; object pointer, coordinate pointer and ObjectID output buffer; `ret 0xC`; EAX is the count. The helper uses coordinate x/y and appends DWORD object IDs with a bounded output count. |
| `0x00031A7F` | `0x001BE230` | Object receiver; optional WeaponSlotType output pointer, passed null here; `ret 4`; EAX returns Weapon pointer. The bank's int declaration preserves width but not this canonical pointer type. |
| `0x0002E85C` | `0x001E8930` | Weapon receiver; source pointer, target pointer and one extra DWORD forwarded to the inner range helper; `ret 0xC`; false path defines AL. |
| `0x0002EDCF` | `0x001535A0` | AICommandInterface receiver at AI subobject `+0x20`; target pointer, integer and source slot; both returns use `ret 0xC`; result is unused. |
| `0x0000E4A8` | `0x001CBDC0` | Object-compatible receiver and low-byte flag; `ret 4`; target ignores result. Complete body is not evidence for a deleting destructor. |
| `0x000016A4` | `0x000C4D40` | Status index slot; `ret 4`; reads the status-word array and returns normalized zero/one EAX; this caller tests AL. |
| `0x000263F0` | `0x00238D10` | Seven stack arguments; every return uses `ret 0x1C` and defines AL. See the argument analysis below. |
| `0x0003A391` | `0x001BEC20` | Object receiver, no stack arguments, layer result in EAX. |
| `0x000294E2` | `0x003E9720` | Pathfinder receiver; object, coordinate, layer, file and line slots; both returns use `ret 0x14`; target ignores result. |

At target `+0x370`, the call to `0x00238D10` receives member, output Coord3D, target, target Coord3D, recent flag slot, delay pointer and kind flag slot. The complete callee reads the object/coordinate arguments, writes all three output coordinate components and the DWORD delay, and uses the low byte of the last flag. It does not read the incoming receiver or the fifth argument. The caller still adjusts ECX by `-0xE4`; retaining a member-call ABI avoids inventing a free-function contract. Nothing in this analysis supplies a semantic owner name.

The target's virtual calls were examined separately: receiver slots `+0x110` and `+0x94` each receive one object pointer; AI slot `+0x184` has no explicit argument and produces AL; containment slot `+0x68` has no explicit argument and returns a pointer; the returned object's slot `+0x48` receives zero, a coordinate pointer and zero, and returns an object-compatible pointer. Complete dynamic implementations were not identified, so the original types of both zero slots and the callee's stack cleanup remain ABI/type blockers. Width and push order are known; int versus float or another four-byte type is not established by the literal zero. Installed-table screening found no target route and does not prove nonvirtual identity.

## Container evidence from actual helpers

The complete member-add caller `0x002459D0` indexes the root map at `+0x120` using member ID at `+0x74` and stores an integer vector index into the returned node payload. Its actual indexing helper `0x00226FA0` uses signed comparisons against node key `+0x10`, builds a key/zero-payload temporary and returns node `+0x14`. Its hinted insertion route reaches `0x00224AD0`, then `_M_insert` at `0x00223D20`. Both allocating arms of that complete helper call `0x00030788`, whose thunk reaches the complete `0x00222520` constructor. That constructor reads exactly source DWORDs `+0` and `+4` and writes exactly destination DWORDs `+0` and `+4`, with a null-destination return path. This field evidence establishes the two-DWORD value; the signed key comparison, signed index use and explicit index write establish the proposed map use. Allocation width and the donor's template name were not used as proof of the payload.

The member-add vector routes reach constructor `0x00233C60` and copy helper `0x00234780`. The complete constructor zeros DWORDs `+0`, `+4`, `+8`, `+0xC`, `+0x14` and `+0x18`, and writes one to BYTE `+0x10`. The complete copy helper reads and writes those same six DWORDs and the byte, returning immediately for a null destination. Neither accesses padding `+0x11..+0x13`. The target independently addresses the coordinate at `+4`, uses the byte at `+0x10`, and uses unsigned frame/delay arithmetic at `+0x14` and `+0x18`. Its final assignment copies the complete record including padding. The byte's original bool versus char spelling is not proven; both spellings were measured. The explicit native-constructor candidate adds no ownership or cleanup hypothesis, and this target has no constructor unwind states to analyse.

## Measurements

The following values are parsed from preserved raw target probe output. The score is the prior bank's conservative ranking formula, `1 - (positional_differences + 2 * abs(ours - retail)) / retail`. It is not a verified fraction of recovered bytes: relocation operands drift, so positional masking can hide different retail operands. The raw logs and disassemblies remain the evidence. Each trial is a single compiler measurement (n=1); several distinct declaration hypotheses independently produce the same baseline instruction/relocation result.

| Trial and corresponding `.log` | Compiled bytes | Positional differences | First difference | Ranking score |
|---|---:|---:|---|---:|
| baseline | 1135 | 839 | 0x4 | 0.247602 |
| canonical-index-map | 1141 | 997 | 0x2 | 0.120314 |
| canonical-index-nontrivial-routes | 1166 | 1002 | 0x2 | 0.093287 |
| canonical-index-nontrivial | 1141 | 997 | 0x2 | 0.120314 |
| canonical-index-typed-routes | 1166 | 1002 | 0x2 | 0.093287 |
| canonical-object | 1135 | 839 | 0x4 | 0.247602 |
| position-accessor | 1135 | 839 | 0x4 | 0.247602 |
| primary-accessor | 1135 | 839 | 0x4 | 0.247602 |
| record-byte | 1135 | 839 | 0x4 | 0.247602 |
| record-native-constructors | 1135 | 839 | 0x4 | 0.247602 |
| secondary-downcast | 1135 | 839 | 0x4 | 0.247602 |
| typed-ilt-force-inline | 1164 | 1000 | 0x2 | 0.098518 |
| typed-ilt-preserve-tail-fixed | 1164 | 1002 | 0x2 | 0.096774 |
| typed-ilt-routes | 1164 | 1000 | 0x2 | 0.098518 |
| typed-map-only | 1139 | 983 | 0x2 | 0.129032 |
| visible-parent | 1135 | 839 | 0x4 | 0.247602 |
| visible-pathfinder-authentic | 1135 | 839 | 0x4 | 0.247602 |
| visible-pathfinder-native-precompiled | 1135 | 839 | 0x4 | 0.247602 |

The native Precompiled-floor variant is rejected as authentic helper evidence because its floor implementation differs from the donor. Two initial compilation failures and the initial wrong helper mangling are preserved but are not counted as target measurements. The parent helper trial differs at its recorded register-allocation offsets. The authentic Pathfinder helper trial is masked exact; it did not improve the target.

## Gates and reopening condition

`check-csv-final.log` and `pin-consistency-final.log` pass. `scoped-bank-gate.log` fails the candidate's normal byte/relocation verifier: the bank's linker alias directives leave eleven callees unresolved in that verifier, and its native tree-find spelling resolves to a different existing route. That pin observation alone does not prove a bad pin because operand positions already drift. No pin was invented or changed. The typed-route experiments above address routing without modifying the paused STL family and still fail byte equality.

No full gate was required or run because there is no landed body, changed shared header, shim or source row. There is no exact target recovery and no accepted new identity. The descriptive bank names are retained. Reopen when independent native declarations or source context establishes the missing caller lifetimes and reproduces the first prologue divergence, or when the STLport header transition provides the correct native map-call lowering. A new semantic name or another generic register shuffle does not resolve these blockers.
