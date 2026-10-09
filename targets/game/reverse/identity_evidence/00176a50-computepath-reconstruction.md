# AIAttackMeleeApproachState::computePath reconstruction

## Result and next experiment

The complete candidate is banked as a partial for RVA 0x00176A50 at revision 59a7d205747039f201c47a160ed94987c1003971. Its 1041 emitted bytes differ from the 1041 retail bytes at 26 non-relocation positions. The relocation-masked diagnostic score is 0.975024015; it is not strict byte acceptance. No function ledger row or symbol pin was changed. The scoped strict byte gate fails on these operands and the unresolved `?Rva000B6CA0Length@@YIMPBUCoord3D@@@Z` copy. See `build/00176a50/scoped-gate.txt`.

Reopening needs a concrete lifetime or alias experiment that preserves the native horde copy's load ordering while reusing the initial coordinate's stack slot. The compiler listing allocates the main direction at -36 and the inlined helper direction at -24; retail uses the same slot for both branches. An actual canonical Coord3D member declaration that emits the verified length helper with its real symbol would also remove the unresolved local-copy dependency. Blind register changes do not address this evidence.

## Retry hypothesis and refutation

Earlier identity blockers are addressed by the existing constructor and vtable evidence, independently checked here. The landed neighboring AIAttackMeleeEngageState computePath source supplies the authentic isSamePosition helper, compact receiver views, compile flags and an inlined coordinate-copy helper. The hypothesis was that these declarations, together with complete decoding of the uncertain module lookup and output helper, would permit a measured complete body. A differing receiver adjustment, return cleanup, output field or outbound branch would refute the relevant contract. Measurements establish a complete near match, while they refute the stronger hypothesis that copying the neighbor's inlined helper suffices for exact allocation.

## Identity and boundary

Constructor RVA 0x0017F7F0 passes the AIAttackMeleeApproachState literal to the base constructor and installs vtable VA 0x0109A6C0. Slot 17 at VA 0x0109A704 contains ILT VA 0x004179EA, whose decoded jump reaches RVA 0x00176A50. The base class table's corresponding slot reaches the already matched AIInternalMoveToState::computePath at RVA 0x001725B0. Existing notes are `targets/game/reverse/identity_evidence/00176a50-meleeapproach-computepath.md` and `targets/game/reverse/identity_evidence/00176a50-aiattackmeleeapproachstate-computepath.md`. Fresh raw data is retained in `build/00176a50/identity-bytes.json` and `constructor-disasm.txt`.

The complete target ends with plain RET at +0x410, followed by INT3 at +0x411. It returns the boolean in AL, receives this in ECX, has no explicit argument and no hidden return pointer. All six return paths and every conditional and unconditional branch were inspected. The audit decodes all target bytes and finds each outgoing jump destination at an instruction within the extent. It also checks all 23 direct callee extents; none has an outbound branch. `build/00176a50/boundary-audit.txt`, `target-disasm.txt` and `checked-target.txt` retain the evidence. The audit alone does not prove identity or nested indirect-call targets.

## EH and ownership

The target is a method with an EH registration frame, not a constructor. Its one unwind state surrounds initialization of the static SiegeDeploySpecialPower key. FuncInfo at VA 0x011F4264 points to the unwind map at VA 0x011F425C, whose cleanup is VA 0x01005BD0. The complete cleanup clears bit zero in the static guard at VA 0x012EF304 and returns. No target member destructor, array ownership or dynamically allocated coordinate is implied. Raw FuncInfo and map words are in `boundary-audit.txt`; full cleanup instructions are in `target-unwind.txt`.

The called output helper at RVA 0x001F9180 constructs and destroys 16 stack coordinates with stride 12. Its coordinate output is independently proved by reads and writes of all three 32-bit components. Its internal record array has stride eight and the selected first field is a bone index; its second payload field has not been established by a value constructor. No STL value type is inferred and no STL row or pin is proposed. Cleanup implementation and the complete record type would need further evidence before recovering that separate helper.

## Receiver fields and scalar types

The target reads machine+0x10 as the owner pointer, owner+0x204 as the AI update pointer and owner+0x38 as x/y/z position floats. AI update+0x140 is the path pointer, +0x31E is a byte waiting flag and +0x326 is the blocked flag. State+0x24 is the three-float goal, +0x4C is the adjustment byte, +0x4D is the waiting byte, +0x50 is an unsigned frame timestamp and +0x54 is the previous victim coordinate. Integer-only fields without independently established names retain offset names.

The complete direction getter at RVA 0x00132140 lazily writes x/y/z at receiver+0x48/+0x4C/+0x50 and returns the address of +0x48; it does not return a temporary or hidden structure. The complete length helper reads x/y/z at offsets 0/4/8, squares and sums them, and returns a float in ST0 without writing the coordinate. The target zeros the initial direction's z. Its distance branch fails when length is below the sum of AI data floats +0x90 and +0x94; the full x87 compare and status-bit branch refute the initial opposite comparison. No scalar type is deduced from allocation size.

## Direct callee contracts

Every listed callee has full decoded instructions and a checked_callees inventory in `build/00176a50/callee-<rva>.txt` and `checked-<rva>.txt`. The inventory's names are screening information; the stack cleanup, receiver and result observations below come from instructions and the complete target call sites. Calls use no receiver adjustment in this target. Floats occupy one stack slot; pointer arguments occupy one stack slot. Reference-returning coordinate operators return their receiver in EAX.

| Callee RVA | Complete extent | Contract used by this target |
| --- | ---: | --- |
| 0x00065C80 | 215 | Cdecl diagnostic with receiver argument and format string; caller removes arguments. |
| 0x000A1490 | 16 | ECX state machine, no arguments, Object pointer in EAX, plain RET. |
| 0x0016AA70 | 69 | TU-private isSamePosition: EDX our position, ECX previous position, EAX current position, AL bool, plain RET. |
| 0x001BE230 | 47 | ECX Object, optional output slot pointer, EAX weapon, RET 4. |
| 0x001CC790 | 113 | ECX source Object, victim pointer then crush enum, AL bool, RET 8. |
| 0x0027BD90 | 362 | ECX AI update, coordinate pointer then byte bool in stack slot, RET 8; result unused. |
| 0x000B6CA0 | 33 | ECX coordinate, no arguments, ST0 float, plain RET. |
| 0x000A2CF0 | 64 | ECX Thing, one kind enum, AL bool, RET 4. |
| 0x00175820 | 158 | Cdecl source then victim pointers, AL bool, caller removes eight bytes. |
| 0x00132140 | 64 | ECX Object, no arguments, EAX pointer to the three cached direction floats, plain RET. |
| 0x0014FFD0 | 33 | ECX coordinate, float scale, receiver reference in EAX, RET 4. |
| 0x000EC6F0 | 33 | ECX coordinate, coordinate reference, receiver reference in EAX, RET 4. |
| 0x001BEC20 | 22 | ECX Object, no arguments, layer dword in EAX, plain RET. |
| 0x0008FFC0 | 299 | ECX name-key generator, string pointer, key dword in EAX, RET 4. |
| 0x001BEE60 | 63 | ECX Object, key dword, module pointer in EAX, RET 4. |
| 0x001F8AB0 | 155 | Cdecl Object pointer, module pointer in EAX, caller removes four bytes. |
| 0x00266340 | 12 | ECX opaque module, no arguments, AL from module+0x38 equals three, plain RET. |
| 0x001F9180 | 342 | ECX opaque module, optional coordinate output pointer, AL bool, RET 4. |
| 0x0016A240 | 33 | ECX coordinate, coordinate reference, receiver reference in EAX, RET 4. |
| 0x000FB930 | 79 | ECX coordinate, no arguments, normalizes all three components, plain RET. |
| 0x003D8BC0 | 96 | ECX pathfinder, coordinate pointer then byte bool in stack slot, AL bool, RET 8. |
| 0x00148730 | 33 | ECX coordinate, coordinate reference, receiver reference in EAX, RET 4. |
| 0x002705D0 | 783 | ECX AI update, coordinate pointer then byte bool in stack slot, AL bool on all three returns, RET 8. |

RVA 0x001F8AB0 does not implement the current generated row's WorkerAIUpdate getModuleNameKey contract. It scans the Object's module pointer array at +0x1F0 and compares a virtual name-key result with the initialized DynamicPortalBehaviour key. The virtual call at +0x62 receives the module in ECX, takes no arguments and yields the compared dword in EAX. Its dynamic slot owner remains unproven; the candidate retains an address-derived call contract and adds no guessed pin. RVA 0x001F9180 likewise stays opaque despite a misleading existing pin. Unknown identities are not used as semantic type evidence.

The copied isSamePosition body independently probes EXACT at 69 bytes (`probe-sameposition.txt`). The ECX length copy independently probes EXACT at 33 bytes (`probe-length-026.txt`), but this does not establish its new symbol as a second retail identity. The static fastcall spelling generated EAX instead of the required ECX and was rejected (`probe-length-023-correct.txt`). The final copy is inline so it does not introduce a second strong out-of-line owner. It needs canonical binding before a strict landing.

## Measurements and rejected hypotheses

Every trial source and unedited probe output is retained under `build/00176a50/`; experiment receipts and objects are under `build/experiments/`. EH and finite direction-store trials also retain their shape_search manifests under `build/shape_search/`. The EH generator's EHsc toggle produced the same body; its result manifest is `build/shape_search/f16fcd043de344b48860f022750be0e7/result.json`. No additional EH state is needed.

The shared failure exit in trial 013 removed the incorrect early-return block shape and first reached the native extent. Caching AI data before coordinate construction and evaluating the initial setter's scalar inputs before subtraction improved trial 020. The inlined helper's own local restored native horde copy ordering in trial 025, at the cost of a second coordinate stack slot. Trial 026 preserves that best shape while fixing the copied helper's ECX ABI. The instruction sequence matches retail after registers and constants are normalized, but the byte gate still fails.

Native WWMath Coord3D declarations with copy operators, GameLogic getter visibility, direct reuse of the outer direction, an explicit intermediate copy, a value-return copy helper, placement copy construction and scalar setter reuse were rejected by their measured outputs. In particular placement copy construction emits 1071 bytes with 421 differences (trial 029), and scalar setter reuse emits 1041 bytes with 41 differences and one relocation-position disagreement (trial 030). Neither replaces the bank.

| Trial | Emitted bytes | Non-relocation differences | First difference | Raw probe |
| --- | ---: | ---: | ---: | --- |
| 002 | 1027 | 677 | 31 | `build/00176a50/probe-002.txt` |
| 003 | 1063 | 689 | 31 | `build/00176a50/probe-003.txt` |
| 004 | 1063 | 689 | 31 | `build/00176a50/probe-004.txt` |
| 005 | 1060 | 702 | 149 | `build/00176a50/probe-005.txt` |
| 006 | 1060 | 702 | 149 | `build/00176a50/probe-006.txt` |
| 007 | 1044 | 689 | 149 | `build/00176a50/probe-007.txt` |
| 008 | 1044 | 689 | 149 | `build/00176a50/probe-008.txt` |
| 009 | 992 | 701 | 28 | `build/00176a50/probe-009.txt` |
| 010 | 1060 | 701 | 149 | `build/00176a50/probe-010.txt` |
| 011 | 1060 | 701 | 149 | `build/00176a50/probe-011.txt` |
| 012 | 1060 | 702 | 149 | `build/00176a50/probe-012.txt` |
| 013 | 1041 | 76 | 175 | `build/00176a50/probe-013.txt` |
| 014 | 1041 | 108 | 175 | `build/00176a50/probe-014.txt` |
| 015 | 1041 | 106 | 175 | `build/00176a50/probe-015.txt` |
| 016 | 1041 | 76 | 175 | `build/00176a50/probe-016.txt` |
| 017 | 1043 | 658 | 31 | `build/00176a50/probe-017.txt` |
| 018 | 1043 | 658 | 31 | `build/00176a50/probe-018.txt` |
| 019 | 1041 | 72 | 175 | `build/00176a50/probe-019.txt` |
| 020 | 1041 | 43 | 175 | `build/00176a50/probe-020.txt` |
| 021 | 1055 | 508 | 175 | `build/00176a50/probe-021.txt` |
| 022 | 1041 | 43 | 175 | `build/00176a50/probe-022.txt` |
| 023 | 1039 | 490 | 175 | `build/00176a50/probe-023.txt` |
| 024 | 1041 | 43 | 175 | `build/00176a50/probe-024.txt` |
| 025 | 1041 | 26 | 28 | `build/00176a50/probe-025.txt` |
| 026 | 1041 | 26 | 28 | `build/00176a50/probe-026.txt` |
| 027 | 1041 | 43 | 175 | `build/00176a50/probe-027.txt` |
| 028 | 1041 | 26 | 28 | `build/00176a50/probe-028.txt` |
| 029 | 1071 | 421 | 175 | `build/00176a50/probe-029.txt` |
| 030 | 1041 | 41 | 175 | `build/00176a50/probe-030.txt` |

The best probe is `build/00176a50/probe-026.txt`; `probe-028.txt` repeats it with a compiler listing. In that listing (`candidate.cod`) the extra slot explains the prologue, EH-state and epilogue displacement differences. Timestamp allocation at +0xAE/+0xB2, y subtraction at +0x1A5 and the commutative x87 sum at +0x1B5/+0x1BB remain distinct operand differences. Exact non-relocation byte offsets are computed in `best-measurement.json` and are +0x1C, +0x60, +0x6A, +0x79, +0x83, +0xAF, +0xB3, +0x152, +0x15C, +0x175, +0x17F, +0x1A6, +0x1A7, +0x1B7, +0x1BD, +0x20B, +0x219, +0x21D, +0x224, +0x23F, +0x291, +0x29B, +0x2DC, +0x2EE, +0x3FC, +0x40F.

## Checks and limits

The bank re-probes with the same 1041-byte extent and 26 differing non-relocation bytes (`build/00176a50/probe-bank.txt`). CSV validation passes (`build/00176a50/check-csv-final.txt`), pin consistency passes (`pin-consistency.txt`), and the source class gate passes (`class-gate.txt`). The strict scoped gate fails for the candidate and the saved bank (`scoped-gate.txt` and `scoped-gate-bank.txt`). The declared-unmatched check fails because this unlanded scratch source owns zero ledger rows (`declared-unmatched.txt`); no whitelist or baseline was changed. There is no exact recovery, no full gate and no commit. The bank is preparation for another experiment, not matched progress. Existing generated sources, all shared headers, symbols.csv and functions.csv remain untouched.
