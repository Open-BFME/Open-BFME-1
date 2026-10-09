# RVA 0x0016F150: callee contract and partial reconstruction

The target remains unconverted. The complete C++ candidate compiles but does not byte-match retail. Its original class and method identity remain unknown, so the reconstruction uses `Rva0016F150::method`. No ledger row or pin is changed.

## Retry hypothesis and result

The earlier records stop at an integer-return `lineClear` versus a retail `test al,al`, a missing named ILT pin, and an unpinned step constant. The new hypothesis was that the existing integer declaration can be retained while the caller explicitly examines its low byte, the existing address-only thunk can carry a decoded member-pointer ABI, and the step can be a verified float literal. The hypothesis would be refuted if the complete callee returned non-boolean integer values, the thunk adjusted the receiver or stack, or the compiler could not emit the observed low-byte test and argument setup. Complete decoding establishes a zero-or-one EAX return and an unadjusted jump thunk. The measured candidate emits the low-byte test and the five arguments. The remaining failure is compiler shape, not the previously alleged missing callee contract.

The inspected revision is `4b91c8621e9e1195de1a556cdb352500c02d364f`. The baseline is the repository's retail 1.03 unpacked executable. The 352-byte target digest from the retained search receipt is `b1f5d360f8acce2de1a0dc59a23835044172b4bbfced3da3b46bd67af093d9c7`.

## Boundary and ABI evidence

`build/rva0016f150/retail-decode.log` retains every target instruction and following padding. The entry reserves a 0x1C-byte frame. Returns occur at offsets +0x1E, +0xCB, +0x13D and +0x15D, each with `ret 0x0C`. The last return ends at +0x160 and INT3 padding begins there. Every conditional branch stays inside that extent; there is no tail jump, indirect call or exception handler. `checked-target.log` inventories the complete extent independently of ledger naming.

`caller-decode.log` retains the complete 1107-byte caller at RVA 0x00182F70 and its padding. Its aligned calls at +0x2DC and +0x33C target ILT 0x0002255C, whose entire jump is retained in `abi-decode.log`. Both sites push the third object pointer, the source object, and the mutable destination coordinate, in that order. The first site supplies the state in ECX; the second omits a receiver setup. The target never reads its incoming ECX or its third argument, consumes three stack slots, and returns zero or one in AL without hidden return storage. A member declaration with an unused opaque receiver preserves this physical contract; a stdcall experiment is indistinguishable in the emitted body. Neither observation identifies the original source-level owner or the unused third parameter's declaration.

The target itself proves a pointer read at source+0x204, float position reads at source+0x38 and +0x3C, a dword read at the first pointer+0x1B8, and a pathfinder pointer read at TheAI+0x0C. These accesses agree with the neighbouring landed `Rva0016EE00.cpp`; the names of the unknown fields remain offsets. `name_oracle.py` supplies no BFME witness for Object+0x204 or AIUpdateInterface+0x1B8, so the bank does not give either field an invented member name. The canonical `Lib/Coord3D.h` provides the three-float layout. Its local address-derived vector view adds arithmetic and bit-copy helpers without changing the canonical declaration. There is no container or owning member, and no constructor unwind or element-destructor claim.

The full ILT 0x0003A391 jumps to RVA 0x001BEC20. The complete 22-byte accessor reads a byte at ECX+0x3A8 and an integer at ECX+0x314, returns an integer in EAX, preserves ECX and has a plain return. The existing `Object::getLayer() const` pin is consistent. The bank uses that existing declaration rather than introducing a new alias.

The full ILT 0x000432A2 jumps to RVA 0x003EE970 without adjusting the receiver. That complete 102-byte body reads its source object, integer query value, four-byte layer and two coordinate pointers from five stack slots; it forwards the object/value to the payload constructor, converts both endpoints and passes the layer to the walker. `neg eax; sbb eax,eax; inc eax` produces zero or one, and `ret 0x14` cleans up all five arguments. Both target endpoint arguments are the same local coordinate pointer. The bank retains the canonical integer return through an address-only thunk and explicitly narrows its test to the low byte. No bool-return retyping or new pin is required.

`payload-decode.log` and `checked-payload.log` retain the complete 232-byte payload constructor at 0x003E5A50. Its return-this path cleans up three arguments and reaches padding; its writes extend through +0x50. It has no unwind map or destructor cleanup. It is not used to infer an STL value type. `abi-decode.log` and `checked-ftol2.log` retain the complete 117-byte CRT conversion helper: it consumes ST(0), preserves the deeper x87 values and returns EDX:EAX; this caller uses EAX. Every helper branch was inspected through its return.

The decoded constant data are retained in `retail-decode.log`: RVA 0x00C977E4 is float bits `BD4CCCCD` (-0.05f), 0x00C75334 is 1.0f, 0x00C75350 is 0.0f, and 0x00C75C74 is 10.0f. Literal constants produce ordinary compiler constant relocations. No data pin is added.

## Measured experiments

All trial sources, unedited probe logs, object receipts and byte-offset lists remain under `build/rva0016f150/` and the probe's `build/experiments/` directories. Each trial has its own source and log. The table uses the repository finish metric, which penalizes size error twice. Probe counts are relocation-masked diagnostic counts; some relocation positions do not align, so none is an acceptance result.

| Trial | Compiled bytes | Probe differing bytes | First difference | Finish metric |
|---|---:|---:|---|---:|
| trial-001 | 356 | 284 | +0x3 | 0.1705 |
| trial-002 | 380 | 272 | +0x21 | 0.0682 |
| trial-003 | 365 | 240 | +0x21 | 0.2443 |
| trial-004 | 365 | 240 | +0x21 | 0.2443 |
| trial-005 | 365 | 208 | +0x21 | 0.3352 |
| trial-006 | 365 | 208 | +0x21 | 0.3352 |
| trial-007 | 365 | 163 | +0x21 | 0.4631 |
| trial-008 | 365 | 208 | +0x21 | 0.3352 |
| trial-009 | 365 | 277 | +0x21 | 0.1392 |
| trial-010 | 365 | 163 | +0x21 | 0.4631 |
| trial-011 | 341 | 286 | +0x3 | 0.1250 |
| trial-012 | 365 | 163 | +0x21 | 0.4631 |
| trial-014 | 346 | 268 | +0x22 | 0.2045 |
| trial-015 | 365 | 163 | +0x21 | 0.4631 |
| trial-016 | 427 | 254 | +0x0 | 0.0000 |
| trial-017 | 365 | 163 | +0x21 | 0.4631 |
| trial-019 | 365 | 163 | +0x21 | 0.4631 |
| trial-020 | 349 | 264 | +0x21 | 0.2330 |
| trial-021 | 252 | 220 | +0x0 | 0.0000 |
| trial-022 | 365 | 163 | +0x21 | 0.4631 |
| trial-023 | 365 | 163 | +0x21 | 0.4631 |

Trial 013 preserves a failed shell argument replacement and its compile error; trial 018 preserves a successfully compiled stdcall body requested under the wrong mangled name. Trial 019 measures that body under the actual compiler symbol. Neither failed request is a byte-match measurement.

The first complete experiment used the neighbouring WWMath class declaration. Trials 002 and 003 adopted the canonical coordinate struct and explicit float initialization. Trial 004 tested explicit bit copies. Trials 005 and 006 tested the two decoded x87 sum lifetimes; trial 007 retained the canonical coordinate base with member arithmetic and reproduces the x87 instruction sequence from +0x49 through +0xBC. Trials 008 through 011 tested copy return structure and the neighbouring class version; none beats the preferred shape. Trial 012 establishes the existing Object declaration and four-byte layer type. Trial 014 removes the cached receiver and moves its load after the layer query, which disagrees with retail. Trial 015 uses the directly declared canonical line-clear method and keeps the same diagnostic shape.

Trial 016 exposes the authentic complete lineClear definition. `probe-visible-lineclear.log` measures that helper at its existing 102-byte extent as exact modulo relocation slots; it is not a new recovery or a strict helper gate result. The caller inlines it and grows. Trial 017 prevents that inlining, keeps the helper visible, and returns to the preferred caller shape without improving it. Trials 019 through 021 test the callee-cleanup spelling, explicit coordinate differences and size optimization, with no improvement. Trial 022 removes the private AI layout in favour of the existing opaque global declaration and an offset read. Trial 023 tests a shared success label and keeps the same result.

The generated constant-return family has a retained three-trial search at `build/shape_search/c63a59fd142d4fad9b7568f721a4c817/result.json`; it reaches a plateau with identical outputs. That family changes no register or x87 shape. Other generated families found no applicable edits in the initial source. No assembly, naked function, baseline expansion or speculative pin is used.

## Preferred body and reopening condition

The preferred body is `targets/game/reverse/attempts/0x0016f150.cpp`, reproduced from `build/rva0016f150/bank-ready.cpp`. It compiles to 365 bytes against retail's 352. The final diagnostic probe has 163 differing bytes in the common extent and a 13-byte size excess; the padded masked comparison has 176 differences and its exact offsets are in the final measurement JSON. The repository finish metric is 0.4631. The first difference is +0x21. Register-normalized instruction similarity is a separate diagnostic and is not the bank's score.

Retail keeps the destination in EDI, the count in EBX and the query value in EBP, spilling the pathfinder receiver into the destination argument's dead home. The candidate leaves the destination in its argument home, uses EDI for the count and retains the pathfinder in EBX. This changes the initial load/copy schedule, receiver spill/reload, loop alignment and final copy. The target's +0x21..+0x48 copy schedule, +0x6B..+0x71 register operands and +0xCE onward receiver/loop/copy sequence remain the codegen-order blocker. The main x87 arithmetic sequence is reproduced in the preferred shape.

Reopening needs independently supported native coordinate-copy or receiver-lifetime context that changes this allocation, or a compiler experiment that demonstrably improves those exact regions. Repeating return-width retyping, the exhausted copy forms, the visible non-inlined lineClear body, the shared success label or the constant-return generator is not a new hypothesis. The real owner identity remains unproven and address-derived; that is not itself a byte-recovery blocker.

The scoped strict byte gate fails on this candidate's code differences, with raw output in `gate-final.log`. Its relocation diagnostics are displaced because the instruction layouts differ and are not evidence for new callee pins. `check-csv-final.log`, `pin-consistency-final.log` and `class-gate-final.log` pass. There is no landing, source change under game/, shared-header change or required full gate. The coordinator must collect the bank and evidence as a partial, not as verified recovered bytes.
