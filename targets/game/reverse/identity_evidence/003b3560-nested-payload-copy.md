# Exact bank at 0x003B3560

The reconstruction in `targets/game/reverse/attempts/0x003b3560.cpp` reproduces the complete retail body at 0x003B3560. It remains banked because the STLport family is paused. No function-ledger row or symbol pin was changed. The element keeps the opaque name `Rva003B3560Elem32`; this note does not claim EA's native class name or the original decorated template spelling.

The tested base is `5e74e31ef4d5102455263bc26857ef30e87a41d3`. Raw sources, measurements and validation outputs are retained in `build/worker-003b3560/`. The measured result for the final bank is in `bank-probe.log` and `strict-bank.log` there. `checked-receipts.json` identifies every independently decoded evidence extent and its raw callee report.

## New hypothesis and measured result

The saved body flattens the payload into scalar fields and spells an unrolled loop by hand. Retail instead creates separate source and destination aliases for the three dwords beginning at element offset 0x08. This suggested an embedded aggregate with implicit assignment. The hypothesis would be refuted if the aggregate view and native assignment still emitted the flat loop or failed to reproduce those alias instructions.

`trial00-saved.cpp` measures the starting bank. `trial01-nested-manual.cpp` tests a nested three-dword value in its manual loop; `trial02-nested-canonical.cpp` replaces that loop with the canonical counted copy; `trial03-coord-canonical.cpp` substitutes the shared Coord3D header. `trial04-implicit-coord.cpp` tests implicit polymorphic assignment but incorrectly includes an explicit padding array. Its extra array is semantically significant because implicit assignment copies array elements. Removing that array and using the independently witnessed member types produces exact code in `trial05-implicit-native.cpp`.

The vendor-header instantiation in `trial07-native-header.cpp` and the unsigned time members in `trial08-unsigned-times.cpp` also reproduce retail exactly. `trial06-native-manual.cpp` rejects retaining the manual unroll with the corrected layout. The native counted loop lets MSVC 7.1 generate the unroll, cursor aliases, parameter-slot spills and tail pointers itself. No register-hint or x87 spelling experiments were needed. All differing-byte counts and emitted sizes are in the unedited probe logs and `measurements.jsonl`; shorter or longer output is counted as wrong there.

## Boundary and ABI

`retail-decode.log` contains every instruction in the target. The half-open extent is [0x003B3560, 0x003B36C1). The only return is the final plain `ret`. All conditional transfers remain within this extent; there are no calls, indirect calls or tail jumps. `final-evidence-decode.log` verifies that padding follows the return. `checked-003b3560.log` confirms complete decoding and an empty direct-callee inventory.

The entry reads first, last and result from three successive stack pointer slots. It computes signed `(last - first) / 32`, copies forward, and returns the advanced result pointer in full EAX. The prologue and epilogue preserve EBX, EBP, ESI and EDI. There is no receiver adjustment, callee stack cleanup or hidden result buffer. The fourth and fifth arguments are not read by the body.

The complete caller at 0x003B4920 has two calls through ILT 0x00020F77, which independently decodes to a jump to the target. Both sites push a null distance pointer, an address for an empty iterator tag, destination start, source last and source first, in that order. Their post-call stack cleanups agree with five caller-cleaned words after accounting for the subsequent range-destroy or uninitialized-copy calls. The caller consumes EAX as the destination endpoint. The complete dispatch helper at 0x003B3DA0 passes the same five-word contract and returns EAX unchanged. Its generated `__copy_backward` pin is inconsistent with the target's forward traversal; it is not evidence for a backward algorithm. Both existing template pins are left untouched.

## Payload evidence

The complete constructor/copy helper actually reached through ILT 0x0000F9A2 is 0x003A84E0. It checks the destination for null, installs vtable VA 0x010EC764, reads and writes each dword at 0x04, 0x08, 0x0C, 0x10, 0x14 and 0x18, then reads and writes the byte at 0x1C. It never copies the vptr or tail padding. This independently refutes the earlier five-dword, byte-at-0x14 layout. The target assignment touches exactly those payload fields while preserving offset 0x00.

The complete append caller at 0x003B1A30 constructs elements through that helper and advances its finish pointer by the element stride. `ParseMoveCameraBlock` at 0x003B7650 independently creates a stack object with the same vtable and payload initialization, passes it to `INI::initFromINI` with table VA 0x010ECD18, and sends it through ILT 0x00001564 to that append caller. Allocation size and generated pin names are not used to establish the payload.

The raw field table and its parser addresses are retained in `field-table.log`. Complete decoding of `findFieldParse` at 0x00850880 verifies the table's token, callback, user-data and offset fields. Complete `initFromINI` and `initFromINIMulti` bodies verify that the callback's third argument is the object plus the table offset and that all four callback words are caller-cleaned.

| Element offset | Bank member | Independent field evidence |
|---|---|---|
| 0x00 | implicit vptr | Constructor installs VA 0x010EC764; assignment leaves it alone. |
| 0x04 | `m_a` | `DelayFromActStart` uses 0x00852D90; the complete seconds-to-milliseconds parser stores an integer result from `__ftol2`. Its existing matched source declares `UnsignedInt`. |
| 0x08, 0x0C, 0x10 | `m_triple` | `Position` uses 0x00853380; the complete parser obtains X, Y and Z and stores each as a dword float. The bank includes the canonical Coord3D header. |
| 0x14 | `m_e` | `ViewAngle` uses 0x00852B20; the complete parser stores a dword float. |
| 0x18 | `m_f` | `ScrollTime` uses the same independently decoded integer time parser as offset 0x04. |
| 0x1C | `m_flag` | `SummaryEvent` uses 0x00852E00; the complete parser stores AL. Complete `scanBool` at 0x00852550 returns true or false in AL and throws on invalid input. |
| 0x1D through 0x1F | implicit tail padding | No payload helper or target assignment reads or writes these bytes. The bank declares no padding array. |

Complete `scanReal` at 0x008526E0 returns its parsed dword float through ST0. Complete `__ftol2` at 0x009F6E38 provides the time parser's integer conversion. Their exception paths and all returns were inspected. The time fields' unsigned source declarations are retained rather than inferring signedness from a four-byte store.

## Destruction, unwind and identity limits

The complete range destroyer at 0x003A8FE0 walks elements forward and calls vtable slot zero with ECX set to the element and a zero deletion flag. Vtable VA 0x010EC764 points through ILT 0x00011AD6 to the complete scalar deleting destructor at 0x003A6FC0. It invokes the complete destructor through ILT 0x00038DAC to 0x003B7640, conditionally frees only when the flag's low bit is set, returns the receiver, and uses `ret 4`. The complete destructor only restores that vptr, so the payload has no witnessed owned resource requiring member cleanup.

`eh_info.py` rejects the reordered entry of `ParseMoveCameraBlock`. Its actual `push -1; push handler` sequence begins at 0x003B765A; decoding metadata from that sequence identifies the same handler at 0x00C1E1B8 and its sole unwind action at 0x00C1E1B0. The action adjusts ECX to the stack record and jumps through ILT 0x00038DAC to the complete destructor. `parse-camera-unwind.log`, `destruction-decode.log` and `final-evidence-decode.log` retain the map, cleanup and destination. The target itself has no EH frame or cleanup paths.

The neighbouring real sources were read directly before shaping, including the range-copy siblings at 0x003B3460, 0x003B34D0, 0x003B3720 and 0x003B37A0. The current constructor and deleting-destructor ledger names use `ApplyRandomForceNugget`, while the independently read table and parser caller describe a move-camera record. That native name is not adopted as type evidence. The Zero Hour reference search supplies no matching move-camera declaration, and `name_oracle.py` supplies no witnessed layout for the address-derived bank type. The exact template specialization is therefore a reconstruction label; the original native owner and decorated identity remain unclaimed. Neither generated backward pin nor a matching donor is treated as independent identity proof.

## Collection

The strict candidate validation calls the repository's ordinary function, boundary, string, constant, DIR32 and body checks with one in-memory candidate row. It makes no ledger change. The final strict log retains full byte equality, zero relocation slots and the full emitted extent. `check_csv-final.log` and `pin-consistency.log` retain the ledger and pin checks. The class gate and direct source-name regression comparison pass. `declared-bank.log` retains the source-claim refusal because this bank owns no ledger row; it is not reported as a passing production gate. No shared header was changed, so this bank does not require a full gate. A production landing still needs the STLport pause lifted and the ordinary source-claim and landing checks.

The required candidate symbol is `??$__copy@PBURva003B3560Elem32@@PAU1@H@_STL@@YAPAURva003B3560Elem32@@PBU1@0PAU1@ABUrandom_access_iterator_tag@0@PAH@Z`. The leaf needs no new callee pin. Reopen for collection after the header migration, then recompile the bank against the new headers and preserve the opaque element identity unless independent evidence establishes its real name.
