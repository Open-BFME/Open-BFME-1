# Animation interval outputs at RVA 0x0076EDA0

The retained body is a partial reconstruction. At revision `e0ae9c1bcfeefc6356aa8d88d298057374cfdb6a`, the compiler emits the retail extent with ten differing register-operand bytes. No source recovery or ledger change is claimed. The preferred bank is `targets/game/reverse/attempts/0x0076eda0.cpp`; the exact measured precursor is `build/76eda0/11-retail-constant.cpp`. The actual model is gpt-6.1-sol.

## Retry hypothesis and evidence

The landed siblings `Rva0076EB50Method.cpp`, `AnimationInfo0076EBE0.cpp` and `Rva0076C080AdvanceAnimation.cpp` supply the inline stamp guard and the three tracks. The retry hypothesis was that the old bank's main blockers were incomplete control flow and a hidden inline guard, rather than an unavailable semantic owner. It would be refuted by a complete, correctly typed switch failing to reproduce the guard and improving neither instruction structure nor measured bytes. The new body reproduces that guard and all control-flow structure; the remaining bytes are register operands.

The previous preferred source was measured directly, rather than assigned its author score. Its x87 cases were incomplete: case 3 omitted the dword test at track offset +0x14, case 5 subtracted a constant from the wrong output, and the common tail overwrote case-specific results. Its invalid path also omitted the copy between output pairs. It declares the same output type for both arguments; this part is now supported by the caller.

## Boundary and ABI

The target starts at 0x0076EDA0 and ends after `ret 12` at 0x0076EF65. INT3 padding starts at 0x0076EF68. All conditional branches and internal jumps remain inside this extent. Each return restores EBX, ESI and EDI and removes three stack dwords. ECX is the receiver; the first argument is a signed index with a subsequent unsigned upper bound of three. Both other arguments are pointers to two four-byte floats. There is no hidden return object and no exception frame.

The independently decoded caller begins at 0x006059F0. Its complete body ends with `ret` at 0x00605D76, followed by INT3 padding. The ledger's 896-byte caller extent omits the last seven bytes, so the acceptance decode used 903 bytes; the caller row was left unchanged because it is outside this assignment. At 0x00605B33 the caller forms the second output at its current ESP+0x50, pushes it, forms the first output at the adjusted ESP+0x4C, then pushes the index in ESI. It sets ECX to the interface in EBP and calls slot +0x34 at 0x00605B6B. After the target's cleanup, the caller reads two contiguous eight-byte pairs starting at ESP+0x48 and compares both members as floats. It does not read EAX as a return value. This validates argument order, widths, cleanup and output representation independently of the bank.

The primary W3DModelDraw vtable at 0x01123D38 has slot +0x98 routing through ILT 0x00030F30 to 0x00751DA0. The complete eleven-byte helper returns receiver+0x0C for a non-null receiver and zero otherwise. The caller obtains its secondary interface through this slot. The secondary table at 0x01123C68 has slot +0x34 routing through ILT 0x00034CDE to the target. The destructor installs that secondary table at primary+0x0C. This establishes the receiver adjustment and family, but not the original name of this BFME-specific method. The bank's existing `Rva0076EDA0Holder::getBlend` name is retained.

## Layout and callees

The secondary view has the stamp at +0x90 and three tracks at +0xD0 with stride 0x1C. Relative track fields read here are: pointer +0x00; float `lower` +0x04; float `upper` +0x08; mode dword `type` +0x10; tested dword +0x14; enabled byte +0x18. The intervening +0x0C field and trailing +0x19 byte are not read by this target and are represented as storage. The bank preserves its existing descriptive member names; they are not claims about the original source names.

The direct call at target +0x17 reaches ILT 0x00024F5F and then the landed `Rva0076C080::advanceAnimation` at 0x0076C080. It receives primary=this-0x0C with no stack arguments. That helper's instruction region is 2107 bytes; its ledger extent also includes a switch table. Linear decoding the entire ledger extent as instructions fails on that table. The checked inventory therefore uses the complete code region and separately follows its outgoing tail at 0x0076C854 through ILT 0x000363AE to the complete 181-byte body at 0x00762900. The helper's stack is restored before the tail jump, and the tail ends in an argument-free return.

The virtual calls at target +0x88, +0x108, +0x133 and +0x160 use slot +0x10 with the track pointer in ECX and no stack arguments. Their full EAX result is stored as a dword and converted with FILD, establishing a signed 32-bit integer return. Independently, the complete HRawAnimClass and HCompressedAnimClass constructors install their primary vtables, whose slot +0x10 points to the four-byte `mov eax,[ecx+0x40]; ret` Get_Num_Frames accessors at 0x00959A30 and 0x0095B850. The neighbour's name, frame-count and duration calls agree with this HAnim interface. The candidate includes the canonical `hanim.h` and keeps `Rva0076EDA0Item` as a typedef instead of duplicating the class.

The global stamp uses the existing recorded name `g_rva0075b2e0_value`. Float operands were read back from retail: the unit constant is 1.0f; the constant at image VA 0x01123C58 is the float represented by bytes 58 FF 7F 3F, written as 0.99999f. Earlier trial sources used the incorrect 1.00001f, which the probe masks but the constant verifier rejects. They remain preserved as rejected experiments. The negative control is retained in `build/76eda0/wrong-literal-negative-control.log`. The immediate value 0xB727C5AC is -0.00001f. No new pin, STL row or header was added.

## Compiler experiments

| Trial source under build/76eda0 | Emitted bytes | Non-relocation differences | Raw probe |
|---|---:|---:|---|
| 00-saved.cpp | 410 | 372 | build/76eda0/00-saved.probe.log |
| 01-complete.cpp | 463 | 331 | build/76eda0/01-complete.probe.log |
| 02-tail.cpp | 466 | 325 | build/76eda0/02-tail.probe.log |
| 03-predicate.cpp | 480 | 367 | build/76eda0/03-predicate.probe.log |
| 04-ordered.cpp | 452 | 343 | build/76eda0/04-ordered.probe.log |
| 05-accessor.cpp | 452 | 343 | build/76eda0/05-accessor.probe.log |
| 06-reference.cpp | 452 | 343 | build/76eda0/06-reference.probe.log |
| 07-slice-view.cpp | 461 | 375 | build/76eda0/07-slice-view.probe.log |
| 08-volatile-item.cpp | 456 | 37 | build/76eda0/08-volatile-item.probe.log |
| 09-common-label.cpp | 456 | 10 | build/76eda0/09-common-label.probe.log |
| 10-canonical-calls.cpp | 456 | 10 | build/76eda0/10-canonical-calls.probe.log |
| 11-retail-constant.cpp | 456 | 10 | build/76eda0/11-retail-constant.probe.log |

The complete switch and native array accesses fix the prologue and stamp load order. Sharing the lower/output tail through a label fixes block placement. The ordered `<` comparison, rather than float equality, lets MSVC reuse the same FCOMP status for the two comparisons. An item-pointer volatile qualifier prevents the null-test value from being cached through the mode dispatch and restores a missing pointer reload; this is a compiler-shape device, not independently proven original volatility.

The accessor and reference null guards both reproduced the same pointer-CSE result. A padded slice view worsened it. A direct canonical virtual call reproduced the wrapper's code. For the final register residue, the documented receiver-local toggle was tested with a finite two-trial shape_search and stopped at its plateau. A float local at the first divergent load also emitted identical bytes. Neither repeated register experiment improved the body; no additional register or x87 iteration is justified without a new hypothesis.

The exact remaining byte offsets, measured after strict relocation resolution, are +0x0F5, +0x0FF, +0x107, +0x109, +0x132, +0x134, +0x14D, +0x157, +0x15F, +0x161. They affect the first-value load/store and the virtual-table scratch registers in the case-3 and case-1 paths. All other bytes, including resolved calls and constants, agree. The authoritative raw differences and byte values are in `build/76eda0/measurement.json`.

## Verification and reopening

`build/76eda0/bank-final.probe.log` and `build/76eda0/bank-final-gate.log` contain the unedited measurements of the final preferred bank, after removing its duplicate generated symbol comment. The scoped verifier uses an in-memory candidate row. The byte check fails on this body; string references, both float constants and recorded DIR32 names pass. `build/76eda0/pin-consistency.log`, `build/76eda0/check_csv-final.log` and `build/76eda0/class-gate-bank.log` pass. The declared-unmatched scan correctly refuses the unlanded scratch source because it owns zero ledger rows; no whitelist or baseline was changed. A file comparison using the current name_regression implementation finds no descriptive-to-placeholder substitutions; this checkout's CLI takes Git revisions, so its literal old-file/new-file invocation was unavailable. The comparison receipt is `build/76eda0/name-regression-file-check.json`.

The animation-step switch subtracts one from its mode, compares the unsigned result with five, and dispatches through the six dwords at RVA 0x0076C8BC. Every entry is an instruction start inside the decoded helper; the range guard's default target is inside it too. `build/76eda0/advance-switch.json` retains all resolved entries. No table entry or conditional branch adds an unreviewed outgoing path.

Complete decode and checked-callee records are under `build/76eda0/`, including target, caller, animation constructors, frame getters, the interface adjustor, the animation-step code and its tail. Original probes, every trial source and the shape-search manifest are retained there and under the search's generated build directory. No long-running job remains.

Reopen with an evidence-backed scratch-allocation lever that can change the listed operands while preserving the existing instruction stream, output alias behavior and canonical HAnim ABI. The current volatile qualifier remains an unproven original-source property. The original method name remains unknown and is not itself a blocker. The bank is useful evidence, not an exact source recovery.
