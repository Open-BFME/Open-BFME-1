# Position update at RVA 0x003CCB70

The retained C++ candidate defines `?updatePosition@Rva003CC890@@QAEXXZ`. At revision `dbfea2ff0cfbd7707f89cdc5cea96c69a4446798`, it emits 400 bytes against the complete 400-byte retail body and differs in six non-relocation bytes. This is a partial reconstruction. The ledger still names the assembly dump. The owning class keeps the established address-derived name `Rva003CC890`.

## Retry hypothesis and refutation

The current ledger still has only a dump at helper RVA 0x003CC940, and `symbols.csv` has only the untyped `b_003cc940` spelling. No newly landed typed helper resolves the prior contract blocker. This run tests a complete typed reconstruction under the coordinator's permission to establish an address-derived helper contract independently. Decoding the entire helper and both callers must establish its receiver, argument storage, output fields and stack cleanup before relying on compiler results. A different receiver adjustment, output width, stack cleanup or outgoing branch outside the claimed extent would refute that contract. The recorded 362-byte earlier reconstruction has no retrievable saved source at this address, so its score cannot be reproduced or compared directly.

The first complete experiment uses the canonical `game/Libraries/Include/Lib/Coord3D.h`, the landed release owner's field offsets, the matched audio methods' declarations and a typed helper declaration. Its x87 scaling sequence differs from retail. A `double` scale is then tested because retail keeps the quotient in x87 storage and its subsequent multiplies consume the live operands differently from the float-scale candidate. The observation that refutes this lever is an unchanged or worse instruction sequence. Trial 05 removes the structural differences and reaches the complete retail size. This establishes a useful compiler shape; it does not establish the historical local variable's source spelling independently.

## Complete boundaries and calls

Retail spans `[0x003CCB70, 0x003CCD00)`. The null-event branch at offset 0x0B reaches the shared epilogue at 0x18B. All conditional branches and ordinary jumps stay inside the extent, including the clamp branch and the common position-update tail. The final `ret` is at offset 0x18F. Following bytes are `int3` padding. There is no exception frame, constructor, container or tail jump in this target.

The direct caller at RVA 0x003D1A60 has been decoded across its complete 1465-byte extent. Its instruction at offset 0x592 calls ILT RVA 0x00026EBD, which jumps to 0x003CCB70. Immediately before that call, it loads the element pointer into ECX. There are no stack arguments, receiver adjustments or reads of the call's return value. This agrees with the target's unadjusted ECX receiver and plain `ret`.

The first target call at offset 0x17 reaches ILT RVA 0x0004327F, which jumps to helper RVA 0x003CC940. The helper spans `[0x003CC940, 0x003CCAF5)`. Every conditional branch is internal. Its single return at offset 0x1B2 is `ret 4`, followed by padding. It uses the incoming ECX owner, reads the two leading coordinate fields, the data pointer at +0x08 and all eight nullable pointers at +0x10 through +0x2C. Every nonnull pointee contributes a signed integer from +0x30 through `fild`. It computes two float coordinates, obtains terrain height through an indirect call and writes exactly three float fields at output offsets 0, 4 and 8. EAX holds the output address at return. Both decoded callers supply 12 bytes of coordinate storage on the stack and consume those fields; neither consumes EAX.

The physical helper ABI is therefore an unadjusted thiscall receiver with one stack slot pointing to three float fields, callee cleanup of four bytes and EAX equal to that storage address. The bytes do not independently distinguish an explicit output argument from a hidden struct-return argument. Trial 07 models `Coord3D position()` and reproduces the same caller shape and six differences as the explicit output declaration. The bank retains the explicit output declaration from the best measured source. It would require the typed symbol `?position@Rva003CC890@@QAEXPAUCoord3D@@@Z` to resolve to RVA 0x003CC940 during landing. No pin is added in this partial submission.

The other direct calls reach `AudioEventRTS::resolveOwnerPosition` through ILT 0x00029AE1 to RVA 0x000B4020, and `AudioEventRTS::setPosition` through ILT 0x00001E88 to RVA 0x000B2210. Their complete decoded extents are 367 and 51 bytes. The resolver writes the boolean byte and the three coordinate fields, and every return cleans eight bytes. Its six-entry jump table stays within the decoded body. The setter reads one coordinate pointer, writes three fields at AudioEventRTS +0x34, +0x38 and +0x3C on the permitted owner-type paths, and cleans four bytes on its shared return. In the target, each receiver is the owned pointer at owner +0x0C plus four bytes. The independently matched declarations and decoded stores agree with an embedded AudioEventRTS at that offset.

The final indirect call uses the canonical `TheAudio` global at image VA 0x012ED668 and primary vtable slot +0xB4. The slot at vtable VA 0x0111C0C0 contains VA 0x00440039. Its five-byte thunk jumps to RVA 0x006A2800, whose full 155-byte body takes a handle followed by a coordinate pointer and ends in `ret 8`. The target pushes the coordinate pointer before the handle, and reads that handle at owned object +0x10. The callee forwards its second argument to the same AudioEventRTS position setter. This checks the indirect call separately from the direct call inventory.

## Names and declarations

The landed `Rva003CC890AudioRelease.cpp` establishes the owned event at +0x0C, the eight node pointers at +0x10 through +0x2C and the flag at +0x34. The landed `Y1EightSlotRefCounts.cpp` independently uses that slot block and calls the release method on the same receiver. The target and its parent use those offsets consistently. This supports the existing address-derived owner, not an EA class name. There is no LargeGroupAudio twin in the Zero Hour reference tree. The native coordinate arithmetic methods in `GeneralsMD/Code/Libraries/Include/Lib/BaseType.h` were read directly before testing their source form.

The candidate's audio class declarations cover only the methods, receiver offsets and handle field needed by this body. The canonical Coord3D header is included. `name_oracle.py` has no witnessed layout for Rva003CC890. No STL row, shared header, generated source, baseline or symbol pin is changed.

## Measurements and rejected shapes

These are the unedited probe reports' sizes and non-relocation difference counts. Size differences are additional failures; instruction-normalized similarity is not byte equality.

| Trial | Hypothesis | Emitted size | Probe differences |
|---|---|---:|---:|
| 01 | Complete typed baseline with float scale | 398 | 87 |
| 02 | Explicit scalar copy into the fallback position | 408 | 356 |
| 03 | Native coordinate copy, subtract, scale and add methods | 412 | 201 |
| 04 | Native methods with direct component subtraction | 398 | 87 |
| 05 | Double scale with the original aggregate copies | 400 | 6 |
| 06 | Explicit scalar copy in the clamp result | 410 | 356 |
| 07 | Hidden Coord3D return storage for the helper | 400 | 6 |
| Copy search | Intrinsic memcpy for both target copies | 400 | 6 |

Trial 05's six differing byte offsets are 0x0040, 0x0044, 0x0050, 0x0058, 0x00F7 and 0x0101. Retail retains X in EDI and Z in EDX; the reconstruction retains X in EDX and Z in EDI. The scalar-copy and memcpy experiments do not improve this residue. They meet the coordinator's two non-improving register-experiment limit after the precision lever improved the body. A verified native copy declaration or authentic surrounding source that changes these lifetimes would justify reopening it. Repeating unchanged register or float-scale spellings would not.

Raw probes and complete decoded bodies are retained under `build/ccb70/`. Trial 05 is `build/ccb70/trial05.cpp`, and its complete raw probe is `build/ccb70/probe05.log`. Exact byte offsets, relocation names, object path, following padding and audio vtable entry are in `build/ccb70/measurement.log`. The bounded copy search retains both source snapshots and its result in `build/shape_search/ef2a8c7c30d845218964572b9f9dc710/`. The target, helper, caller, resolver, setter and audio-slot extents each have a raw `checked-*.log` from the coordinator's `checked_callees.py` helper, plus complete disassemblies.

The scoped candidate gate in `build/ccb70/scoped-gate.log` fails on this body's differences and the unresolved typed helper symbol. It uses the repository's `build.verify_functions` with a supplied candidate row and does not mutate the ledger. The class gate and CSV check pass. `find_declared_unmatched.py --fail` rejects the scratch candidate because it owns no ledger row, as expected for this partial; no waiver is added. No exact recovery or full gate is claimed.
