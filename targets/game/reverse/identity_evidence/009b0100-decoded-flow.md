# Partial reconstruction of RVA 0x009B0100

The preferred reconstruction remains a partial. It emits 1582 bytes for the independently decoded 1583-byte retail extent, with 1156 non-relocation differences. No source recovery or identity correction is claimed. The ledger remains the assembly dump. Reopening requires a source-backed hypothesis about the prologue's dimension stores, switch temporaries or pointer induction that improves the preserved compiler output.

The tested revision is `9813ae6051b579d9b4471fa1ba5cb4bb77a13c9d`. The model is `gpt-6.1-sol`. Exact measurements and source hashes are derived by `build/worker-009b0100/measure_evidence.py` into `build/worker-009b0100/measurements.json`. The best measured source is `build/worker-009b0100/19-dimension-aggregate.cpp`. The final bank uses `build/worker-009b0100/21-bank-format.cpp`, which preserves the same measured instructions with corrected indentation and the attempt tool's metadata prepended. Raw sources, probes and checks remain under `build/worker-009b0100/`; the finite store search is identified by `store-search-path.txt` there.

## New evidence and retry hypothesis

The saved reconstruction's context and control flow were checked against complete retail instructions. The setup slot now has a canonical definition in `game/GameEngine/Source/Common/Rva009AF530SetupDispatch.cpp` and a data row at VA 0x01356E68. Commit `e6a57c49b80` supplies that declaration in the current history; its date is after the saved bank's date. The current source therefore uses the existing `int * (__cdecl *)(Rva009AF530Context *, int)` declaration and casts the target's address-derived view at the call. The neighbouring plane and filter source files were read directly, including `Rva009AF200CopyPlanes.cpp`, `Rva009AF320CopyPlanes.cpp`, `BfmeLimitedEdgeFilters.cpp` and `BfmeCodecCpuDispatch.cpp`. No shared target header or proven real owner was found.

The new hypothesis was that the saved body's large mismatch includes incorrect reconstructed control flow, rather than only register allocation. Specifically, the first-row horizontal filter and both interior-loop below-neighbour filters belong inside the current-fragment guard; the first column of a middle row belongs inside the height loop; every interior column loop has a signed width bound; and the final row's right-neighbour test uses the next fragment, not the next row. The hypothesis would be refuted if the decoded transfers did not support these guards or if the corrected compiler output failed to improve upon the saved body. The decoded transfers support them, and native column indexing improved both the differing-byte count and instruction shape.

The saved body reprobes at 1474 bytes with 1296 differing bytes, first differing byte +0x4, and shape 0.803. Its recorded 0.11 score was an author estimate; the current repository distance formula measures 0.0436. The retained body measures 0.2685, first differing byte +0x4, shape 0.925, 37 structural differences and 20 unaligned relocation sites. Its first structural difference is the stack store at retail +0x28 versus the context store at the same candidate offset. The remaining mismatch spans the body, including the switch and induction variables; a one-byte length difference does not make this a near-exact body.

## Boundary and ABI

The exact extent is `[0x009B0100, 0x009B072F)`; the final instruction is the plain `ret` at 0x009B072E. `retail-target.log` contains every decoded instruction. `checked-target.log` contains the checked-callee inventory. Both return paths reach the same complete epilogue. The early zero-limit path skips the later EBX save and its pop. No conditional branch leaves the extent, and no tail jump, EH registration, unwind state, indirect virtual call or hidden return-storage argument appears.

The entry consumes seven stack words: context at entry ESP+4, table index at +8, base offset at +12, the opaque fourth argument at +16, flag-byte pointer at +20, flag stride at +24 and mask at +28. The six non-context arguments are stored respectively to context offsets +0x0C, +0x10, +0x14, +0x18, +0x1C and +0x20. Only the low mask byte participates in fragment tests, despite the full-width entry store. Context plane pointers are read at +0x78, +0x7C and +0x80; fragment-base terms at +0x84 and +0x88; dimensions at +0x90 and +0x94; and strides at +0x98 and +0x9C. Logical shifts establish the dimension bit interpretation used for chroma, while the local loop comparisons are signed. The complete target independently establishes these offsets; matching donor declarations are corroboration only.

The setup call pushes the table value and context, cleans eight bytes, and consumes EAX as a pointer. Each filter call pushes work, stride, pixel address and context, then cleans sixteen bytes. No receiver adjustment or callee-cleaned arguments occur. The scalar setup at RVA 0x009AF490 uses context+0x34 as an int buffer, clears it and writes its ramps before returning the midpoint. The SIMD setup at RVA 0x009C2930 reads the same pointer, adds 0x400, aligns it to 32 bytes and writes all six initialization words. It leaves that pointer in EAX. Its existing `initPattern` declaration returns `void`, which does not establish the ABI consumed by this target; the complete instructions and the target's EAX use do. No out-of-scope helper or pin was changed.

The complete dispatch installer at RVA 0x009B0D60 installs 0x009AF490 or 0x009C2930 in slot 0x01356E68, 0x009AF570 or 0x009C2970 in slot 0x01356E9C, and 0x009AF6A0 or 0x009C2BA0 in slot 0x01356EBC. Every one of those actual callback bodies was decoded in full and checked with the coordinator's `checked_callees.py`. All end in ordinary returns and have no outgoing tail or conditional transfers. Their raw records are `retail-helpers.log`, `retail-simd-helpers.log` and the corresponding `checked-*.log` files. The scalar filters read a signed correction table. The SIMD vertical filter also writes scratch areas at work+0x18, +0x20, +0x28 and +0x30; its complete helper does not permit a const work-buffer contract. The candidate therefore uses an opaque writable `void *` for callback work rather than claiming one common payload type for these runtime alternatives. There is no STL container or constructor cleanup in this target.

`callers.log` found no named direct caller. `raw-caller-screen.log` found no raw relative call, relative jump or absolute entry-VA reference. These are negative screening results, not a real-owner identity proof. No positive raw hit was promoted without instruction-boundary validation. The symbol retains the target address, and the real owner and original source name remain unproven. Lack of a real name is not treated as a blocker.

## Experiments and verification

Every listed trial has a complete source and unedited probe output. The saved reconstruction is `00-saved.cpp` with `probe-00.log`. The corrected flow, byte-mask spelling, member reloads, signed bounds, separate line width, column loops, per-case base addition, direct mask, initial load order, indexed pixel addresses, canonical callback declaration, case-load order, writable work, integer cursor, C-compatible declarations, C frontend, dimension aggregate and dimension array were measured independently. The finite store generator stopped at its plateau without improving the retained source. Initial local-order variants did not recover the frame schedule. Integer cursor representation and the C frontend did not improve the bytes. A local dimension aggregate improved one byte; an array produced the same compiler result. The aggregate is a compiler hypothesis, not evidence of an original declared local type. Prior volatile-dimension and register-keyword experiments were not repeated.

| Trial | Emitted bytes | Differing bytes | Shape | Preserved source |
| --- | ---: | ---: | ---: | --- |
| 00 | 1474 | 1296 | 0.803 | `build/worker-009b0100/00-saved.cpp` |
| 01 | 1581 | 1427 | 0.824 | `build/worker-009b0100/01-decoded-flow.cpp` |
| 02 | 1581 | 1427 | 0.822 | `build/worker-009b0100/02-byte-mask.cpp` |
| 03 | 1597 | 1354 | 0.857 | `build/worker-009b0100/03-reload-dimensions.cpp` |
| 04 | 1607 | 1331 | 0.864 | `build/worker-009b0100/04-signed-bounds.cpp` |
| 05 | 1639 | 1333 | 0.864 | `build/worker-009b0100/05-line-width.cpp` |
| 06 | 1642 | 1336 | 0.875 | `build/worker-009b0100/06-for-columns.cpp` |
| 07 | 1626 | 1324 | 0.857 | `build/worker-009b0100/07-case-base.cpp` |
| 08 | 1626 | 1324 | 0.859 | `build/worker-009b0100/08-native-mask.cpp` |
| 09 | 1626 | 1321 | 0.859 | `build/worker-009b0100/09-load-order.cpp` |
| 10 | 1582 | 1296 | 0.876 | `build/worker-009b0100/10-single-column-guard.cpp` |
| 11 | 1582 | 1157 | 0.925 | `build/worker-009b0100/11-native-induction.cpp` |
| 12 | 1582 | 1162 | 0.925 | `build/worker-009b0100/12-width-before-height.cpp` |
| 13 | 1582 | 1162 | 0.925 | `build/worker-009b0100/13-canonical-callback.cpp` |
| 14 | 1594 | 1358 | 0.938 | `build/worker-009b0100/14-case-loads.cpp` |
| 15 | 1582 | 1157 | 0.925 | `build/worker-009b0100/15-writable-work.cpp` |
| 15-repeat | 1582 | 1157 | 0.925 | `build/worker-009b0100/15-writable-work.cpp` |
| store-00 | 1582 | 1157 | 0.925 | `build/shape_search/e5877f9d0ec54aa4a1d776b64919a369/000-ef7920de389d.cpp` |
| store-01 | 1582 | 1157 | 0.925 | `build/shape_search/e5877f9d0ec54aa4a1d776b64919a369/001-e63a968d27b1.cpp` |
| store-02 | 1582 | 1157 | 0.925 | `build/shape_search/e5877f9d0ec54aa4a1d776b64919a369/002-8b7c3b7dff5e.cpp` |
| store-03 | 1582 | 1157 | 0.925 | `build/shape_search/e5877f9d0ec54aa4a1d776b64919a369/003-91c53a51e9c3.cpp` |
| store-04 | 1582 | 1161 | 0.925 | `build/shape_search/e5877f9d0ec54aa4a1d776b64919a369/004-ffb3593223b8.cpp` |
| 16 | 1582 | 1157 | 0.925 | `build/worker-009b0100/16-integer-cursor.cpp` |
| 17 | 1582 | 1161 | 0.925 | `build/worker-009b0100/17-c-compatible-cpp.cpp` |
| 18 | 1582 | 1161 | 0.925 | `build/worker-009b0100/18-c-frontend.cpp` |
| 19 | 1582 | 1156 | 0.925 | `build/worker-009b0100/19-dimension-aggregate.cpp` |
| 20 | 1582 | 1156 | 0.925 | `build/worker-009b0100/20-dimension-array.cpp` |
| 21 | 1582 | 1156 | 0.925 | `build/worker-009b0100/21-bank-format.cpp` |

`compare_call_traces.py` is a scratch integer-instruction interpreter, not a native execution or byte gate. It compares compiled and retail instruction streams while tracing callback arguments, returning arbitrary caller-clobbered register values and leaving context/flags unchanged. The retained aggregate body agrees in 600 cases covering several luma/chroma dimensions, flag patterns, strides and the zero-limit return. Every conditional outcome was observed except the switch's unreachable default case. This supports the reconstructed control flow in that test domain only. `call-traces-19.log` preserves the raw result. A separate old-bank probe with one explicitly recorded test has different callback arguments/order and counts (`call-traces-00-one.log`, n=1), consistent with the directly decoded guard and row-loop errors. The broader old-bank test exceeded its instruction budget; the decoded missing narrow-width guard permits a negative countdown. Its raw failure was retained, not counted as a passing test.

The actual scoped byte gate, using the repository verifier with one in-memory row and no ledger edit, fails on this target's own bytes (`byte-gate-19.log` and the final `byte-gate-banked.log`). It is not an unrelated gate blocker. `check-csv-final.log`, `pin-consistency.log`, `class-gate-banked.log` and the direct file comparison through `name_regression.regressions` in `name-regression-files.log` pass. The requested filename arguments to this revision's `name_regression.py` CLI are rejected because that CLI expects Git revisions; the raw failure is `name-regression-15.log`, and the same module's file-comparison routine was then used directly. `find_declared_unmatched.py` refuses the scratch reconstruction because it has no matched ledger row (`declared-unmatched-15.log`); it was not whitelisted or promoted into game source. The final bank was reprobed with the same complete extent in `probe-banked.log`, reproducing the retained measurements. `banking.log` and `banking-receipt.json` record the single new verdict and the compiler-measured bank score. No shared header was changed, so a full gate is not required for this bank.
