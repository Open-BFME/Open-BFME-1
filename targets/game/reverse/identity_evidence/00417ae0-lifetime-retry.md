# Partial recovery at 0x00417AE0

The preferred bank is `targets/game/reverse/attempts/0x00417ae0.cpp`. It is a complete C++ attempt under the existing address-derived identity `Rva00417AE0::run(int)`. It is not a verified source recovery. The ledger remains on its generated dump. Reopen this attempt when an independently supported declaration or compiler lifetime rule explains the remaining late EBX save; repeating register spellings is not justified.

## Evidence and ABI

This retry examined revision `91d7b17f67449f1ff3e8a2f90d197e7057a08bcb`. The matched Object caller at 0x001CD6B0 loads its Drawable pointer from +0x80 and passes one 32-bit damage selector through the ILT to 0x00417AE0. The target has a complete 366-byte extent ending in `ret 4`. Its three guards read +0x140, +0x141 and +0x143; its slots are at +0x144 and +0x148. The matched ambient emitter at 0x00417710 and assignment at 0x00087750 resolve the earlier slot-layout and reference-ownership blockers. The method's original name remains unknown, and the zero-offset base class in the bank is an ABI view rather than a claim about source inheritance.

Complete decoded listings and checked-callee reports are retained in `build/rva00417ae0/retail-*.log` and `checked-*.log`. They cover the target, caller, both selectors, assignment, copy constructor, destructor, singleton, singleton value constructor, pointer setter, lookup and final-override helper. `decode-evidence.log` identifies the reference executable and records instruction coverage, branch destinations and return paths for the complete extents. The shorter initial screenings named `retail-b3fa0-check.log` and `retail-87a80-check.log` are not complete-function evidence.

The actual selector targets are 0x00417430 and 0x004175F0. Both receive a hidden output pointer followed by the 32-bit selector and return that output address in EAX, with `ret 8`. The caller retains its unadjusted receiver. The copy helper at 0x000B97D0 copies the pointer at holder +0, increments its pointee's signed counter at +4 and returns the receiver with `ret 4`. The assignment helper increments the incoming pointee, releases the old pointee and copies the pointer. Release decrements the same counter and invokes virtual slot zero with argument 1 when the counter is nonpositive. No allocation-size or named-pin inference establishes these fields.

The event view has filename +4, information reference +8, handle +0xC, kill handle +0x10 and event name +0x14. A dynamic slot embeds this event at +4, placing its information reference at +0xC and handle at +0x10. The matched emitter independently constructs those slots and uses these fields. The target compares the first desired pointer to the first slot pointer, then emits when the second pointers differ OR the first comparison changed. This condition follows the decoded JNE and JE destinations, rather than the older incorrect equality-and hypothesis.

`eh-target.log` and `eh-compiled-best.log` retain the retail and compiled unwind maps. Both have state predecessors -1, 0, 1 and 2 and cleanup receiver adjustments -0x14, +4, -0x10 and -0x18. Every cleanup reaches the holder destructor; its complete decoded release path is retained. The compiled metadata inspection uses synthetic COFF section addresses and makes no claim that those addresses belong to retail.

The singleton donor in `Rva0041ABE0ReplaceResource.cpp` was read directly. Its private result convention and constructor fields were independently decoded. The visible singleton and assignment compile exactly under probe masking, but both are already recovered elsewhere. The two visible selector reconstructions are not exact standalone recoveries. They are included only to reproduce compiler visibility in this bank, and their opaque call-view names have not been pinned.

## Experiments

The new hypothesis was that decoded holder ownership and visible callee bodies would let the compiler stop treating result storage as escaping. It would be refuted if the measured target did not improve on the saved body. The measurements support an improvement, but do not establish byte equality.

| Source or family | Compiled extent | Non-relocation differences | Result |
| --- | ---: | ---: | --- |
| Saved body, trial00 | 386 | 271 | Reproduced the earlier mismatch. |
| Visible assignment, trial09 | 366 | 229 | Correct extent; local frame still short. |
| Visible second selector, trial15 | 370 | 180 | Local frame becomes retail-sized. |
| Both visible selectors, trial18 | 366 | 163 | Best measured shape. |
| Typed emitter declaration, trial21 and best | 366 | 163 | Same best shape with the decoded argument widths. |

All trial sources and unedited probe output remain under `build/rva00417ae0/`. The EH generator and finite shape search did not improve trial00; their raw choices and results are retained, including `build/shape_search/c7eb28db05564553a968ab2ad8b50003/result.json`. The non-EH family generator found no applicable choices. Explicit output construction, native/default construction, direct and cached-pointer release, outer flag scopes, a nontrivial copy constructor, comparison wrapper and two bool aggregate spellings were measured. Direct/cached release changed the extent without solving allocation. Canonical return types, separate reference types, const payloads/getters, early returns, and visibility of the matched emitter and lookup were also measured and did not improve the best result.

The first remaining divergence is +0x45. Retail saves EBX before calling the first selector; the compiler saves it near +0xC1. Until that save, compiled stack displacements are four bytes lower. The decrement import is cached in EBP instead of ESI, EBX is restored early, and the last two cleanups use ESI instead of EDI. Probe reports four relocation-layout drifts and four structural differences, despite a normalized instruction match of 0.984. This is a register allocation and save-scheduling blocker, not a missing complete body.

## Verification status

The bank was compiled and gated again at its saved path, with identical target output. Raw results are in `build/rva00417ae0/`: `probe-banked.log`, `gate-banked.log`, `check_csv-banked.log`, `pin-consistency.log`, `class-gate-banked.log` and `name-regression-banked.log`. `verification-receipt.json` retains the commands, exit codes and body hash. CSV validation, pin consistency, class gate and the source comparison API for name regression pass. The name-regression CLI in this revision expects Git revisions rather than two source paths; its unsuccessful requested invocation is retained separately in `name-regression.log`.

The strict scoped byte gate fails. It reports byte differences and three unresolved opaque call views for the two selectors and emitter. Their retail targets and stack contracts are decoded, but no speculative pins were added to make this nonmatching bank pass. `find_declared_unmatched.py --fail` also reports the three present-but-unmatched definitions and lack of a matched bank row; `declared-unmatched-banked.log` retains that result. A full gate is not required for a bank-only change with no game source, shared declaration or pin edits. No source recovery or additional matched bytes are claimed.
