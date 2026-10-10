# 0x002BD940: filter width and remaining position-addition residue

The target remains a partial recovery. The preferred bank is `targets/game/reverse/attempts/0x002bd940.cpp`, copied from `build/target-002bd940/12-native-mask181.cpp` under the bank's existing symbol `?bfmeGo002BD940@Rva002BD940Owner@@QAEXXZ`. It emits 354 bytes against the complete 358-byte retail extent. The probe reports 29 differing non-relocation bytes in the overlap and a four-byte missing tail. `finish_measure.measure` gives quality 0.8966. No authored source recovery or identity rename is claimed.

## New hypothesis and refutation

The saved attempt compiled the kind-of shim's 126-bit type, which occupies four words, although the actual constructor copies two six-word masks. Current landed sources `VptrZeroPrefixBlockCtors.cpp`, `BfmeT1035Use.cpp` and `Rva002622D0Collect.cpp` supplied complete visible constructor implementations to inspect. Correcting the mask layout and restoring the complete vector operations should fix the first stack-slot divergence. This hypothesis would be refuted if the measured candidate were no closer than the saved body. The saved body reproduced 320 bytes with 215 overlap differences; the corrected body improved to the measurement above.

## Boundary, receiver and call ABI

`target_disasm.log` decodes every instruction of the 358-byte body. Its only conditional branch targets the shared epilogue at +0x156, its plain return ends at +0x165, and the following sixteen bytes are padding. `checked_target.log` reports no outgoing conditional branch or tail jump. The function takes only ECX and returns no value. The complete matched caller at 0x002C12E0 loads ECX from its saved receiver at +0x7D and calls the ILT at +0x7F. `caller.disasm.log` and `caller.checked.log` retain this evidence. The thunk reaches 0x002BD940 without adjustment. The receiver's field at +8 supplies the object; the object supplies three four-byte position fields at +0x38, +0x3C and +0x40, and a four-byte float at +0xBC. The bank's owner and field names are retained.

The constructor's complete 102-byte body at 0x000C3DD0 initializes the vptr and next pointer, copies every source word at +0, +4, +8, +0xC, +0x10 and +0x14 to member +8, copies all six words of the other argument to member +0x20, and returns with stack cleanup 8. The 181-bit source constructor independently reproduces all 102 bytes modulo its vtable relocation (`filter_ctor181.probe.log`). Its in-class definition is inline and noinline, so it supplies compiler visibility without a second strong definition.

The partition wrapper at 0x009F26A0 forwards the position pointer, float bits, null region, distance mode and filter pointer to 0x009F5C00 and returns with cleanup 0x10. The complete 1995-byte inner body reads that argument order and returns the chosen object pointer in EAX with cleanup 0x14. The caller consumes EAX as a pointer. `partition_wrapper.disasm.log`, `partition_inner.disasm.log` and their checked-callee logs retain every return and branch. The random helper's complete 141-byte body returns a float in ST0 and uses four caller-cleaned four-byte arguments. The normalization helper has two complete return paths within 79 bytes, takes ECX without stack arguments, and reads and writes the same three float fields; the native helper independently matches all 79 bytes (`normalize.probe.log`). The position setter's complete 272-byte body consumes one coordinate pointer, reads its three four-byte fields and returns with cleanup 4 on both paths. The target has no indirect calls. The already-landed position setter's own virtual dispatches are retained in its complete decode and are not new method-identity claims.

## Independent mask type and virtual layout

The constructor's allocation or copied size alone does not establish the logical width. The actual filter vtable at 0x01083B70 routes slot 1 through 0x00031DF9 to the complete 20-byte helper at 0x001DCC80. That helper passes the two masks at +8 and +0x20 to the Thing predicate. Its complete 41-byte body tail-calls through 0x00019BCD to the complete 230-byte predicate at 0x000E9910. That predicate reads all six words of each mask, tests both required-clear and required-set conditions, and at +0x9A restricts the complemented final word with 0x001FFFFF. Thus the mask contains 160 plus 21 meaningful bits. The native STLport bitset representation rounds those 181 bits to six 32-bit words. This proves the 181-bit declaration independently of the donor's name or pin. The shipped table independently contains 181 names; indices 7, 10 and 11 are STRUCTURE, MONSTER and MACHINE (`metadata.log`).

The actual chain walker at 0x009F2A70 invokes slot 1 with an object pointer, checks AL and follows next at +4. The complete mask walker at 0x009F2AB0 invokes slot 2 without arguments and ANDs the EAX results. Slot 2 of the base and kind-of tables routes to 0x000C3BA0, whose complete four-byte body returns all bits set. Slot 0 routes to the 30-byte deleting destructor at 0x000C4520. Its one flag argument controls global deletion; it calls the seven-byte non-deleting cleanup at 0x000C3E50 and returns with cleanup 4. The relevant full decodes and checked-callee inventories are retained under the `filter_`, `isKindOfMulti` and `flags_test` names in the task folder.

The globally owned empty mask has 24 zero bytes. The source names the existing recorded 192-bit storage symbol and views those zero bytes as the proven 181-bit mask. It does not redefine the global. The existing constructor pin spells BitFlags<192>; the corrected BitFlags<181> constructor spelling has no pin in this revision. A future landing must bind that independently decoded constructor or correct the old prototype through the repository's procedures. This run adds no pin.

## Unwind cleanup

Retail has one state, state 0 to -1. Its cleanup at 0x00C137B0 addresses the filter at EBP-0x44 and jumps through 0x0002FEB4 to 0x000C3E50, which restores the base vptr and returns without freeing storage (`target_eh.log` and `filter_dtor.disasm.log`). The compiled candidate has the same one-state map and receiver adjustment. Its derived cleanup also emits only a base-vptr store and return. `candidate-audit.log` preserves the COFF map, cleanup relocation, base and derived destructor instructions. There are no owned element destructors or container payloads in this target.

## Measured rejected shapes

Each source below has its unedited output in the same task folder, with suffix `.probe.log`. The last column counts missing or extra bytes separately from overlap differences. The source with the complete vector operations but the old four-word masks changes the instruction shape substantially without fixing the frame. The six-word masks repair that frame and align the body through the second random call. Two arithmetic spellings retain the same remaining result; no further unchanged arithmetic/register trials were made. A separate output object and a returned aggregate enlarge the frame and worsen the result. The opaque normalization experiment emits an alternate fastcall symbol spelling and was rejected; it is not a canonical ABI declaration. Precise floating-point mode also worsens the body. Eight generated EH combinations failed to improve the corrected body.

| Trial source | Emitted bytes | Overlap differences | Size error |
|---|---:|---:|---:|
| `01-visible-ctor.cpp` | 320 | 216 | 38 |
| `02-native-vector.cpp` | 346 | 237 | 12 |
| `03-native-opaque-ctor.cpp` | 346 | 239 | 12 |
| `04-native-mask192.cpp` | 354 | 29 | 4 |
| `eh-choices-01.cpp` | 354 | 29 | 4 |
| `eh-choices-02.cpp` | 354 | 29 | 4 |
| `eh-choices-03.cpp` | 354 | 29 | 4 |
| `eh-choices-04.cpp` | 354 | 29 | 4 |
| `eh-choices-05.cpp` | 354 | 29 | 4 |
| `eh-choices-06.cpp` | 354 | 29 | 4 |
| `eh-choices-07.cpp` | 354 | 29 | 4 |
| `eh-choices-08.cpp` | 314 | 257 | 44 |
| `05-explicit-vector-add.cpp` | 354 | 29 | 4 |
| `06-reversed-vector-add.cpp` | 354 | 29 | 4 |
| `07-separate-result.cpp` | 357 | 192 | 1 |
| `08-value-result.cpp` | 381 | 198 | 23 |
| `09-opaque-normalize.cpp` | 362 | 45 | 4 |
| `10-precise-float.cpp` | 476 | 154 | 118 |
| `11-final-candidate.cpp` | 354 | 29 | 4 |
| `12-native-mask181.cpp` | 354 | 29 | 4 |
| `13-minimal-candidate.cpp` | 354 | 29 | 4 |

The remaining instruction difference starts at +0x123; the branch displacement at +0x9C changes because the later body is four bytes shorter. Retail loads the position X first and adds the delta X. At +0x139 it loads position Y, adds the still-live random-adjusted Y value and discards the extra x87 stack value. The compiler instead directly adds the position Y memory operand. The shifted setter relocation and epilogue account for later overlap differences. Reopening needs evidence for the native addition helper or lifetime/typing that produces this x87 sequence, rather than another unchanged commutation or local-order trial.

## Verification limits and retained evidence

The candidate byte gate fails on this target's measured mismatch and the unbound 181-bit constructor (`scoped-gate.log`). This failure belongs to the assigned candidate. The final CSV check and global pin consistency pass (`check_csv_final.log` and `pin-consistency.log`). File-pair name regression finds no downgrade; the CLI at this revision accepts Git revision pairs instead of the file-pair invocation in the brief, so the existing `regressions` API was also run on the actual snapshots. The class gate passes for both the retained trial and the actual bank. The fresh probe of the actual bank reproduces the reported measurement (`bank.probe.log`). The declared-unmatched source check reports the expected absence of a ledger row for a partial, which is not a landing certificate. The new and original immutable archives pass their SHA-256 checks, and the new archive's source equals the preferred bank byte for byte (`archive-integrity.log`). No shared header, policy, tooling, ledger row or baseline is changed, and no full gate is required for this evidence-only bank.

The optional `finish_measure.py --one` receipt check cannot certify reusable dependencies in this sandbox: `_case_resolve` requires ancestor directory listings even though the requested header file itself is readable. The diagnostic shortens the shown include paths. The direct `finish_measure.measure` used by `re_log.py` still makes a fresh probe and returns the measurements above (`bank-measure.json`). All trials, complete decodes, raw probes and gate output remain under `build/target-002bd940/` for collection. The minimal canonical-coordinate experiment is also retained but rejected because its fastcall bridge changes the emitted normalization symbol spelling.
