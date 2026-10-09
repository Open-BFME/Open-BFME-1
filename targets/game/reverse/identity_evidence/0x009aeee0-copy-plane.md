# Copy-plane retry at 0x009AEEE0

The tested base revision is `8c0324f884629de45a838529af467c6cb668331e`. The implementation keeps `copyPlane009AEEE0`, `Rva009AF200Context`, the bank's member names and opaque callback names. The matched caller at `0x009AF200` calls this exact body three times, with the established context, source offset, destination offset and plane selector declaration. No original codec owner or vendor function name is claimed.

## Boundary and ABI evidence

The target occupies `[0x009AEEE0, 0x009AF0C8)`. Its single `ret` is at `+0x1E7`, followed by `int3` padding. Every conditional branch and loop backedge targets a decoded instruction within that interval. There are two indirect calls and no direct calls, outgoing tail jumps, exception states or cleanup helpers. Complete decodes and checked-callee outputs are retained under `build/copy-plane-009aeee0/`; `boundary-audit.json` records instruction coverage, branch alignment and return locations for the target and every body used as ABI evidence.

The complete matched caller pushes context, x, y and plane in cdecl order at call sites `+0xF6`, `+0x100` and `+0x10A`, then removes the accumulated argument bytes. It supplies selectors zero, one and two. The target reads four dword stack arguments and returns with plain `ret`; it neither adjusts a receiver nor accepts hidden result storage. The existing signed offset and selector declaration is retained because raw dword loads alone do not distinguish signed and unsigned source types.

The target reads signed mode at context `+0x00`, byte-buffer pointers at `+0x78`, `+0x7C` and `+0x80`, opaque fragment offsets at `+0x84` and `+0x88`, unsigned dimensions at `+0x90` and `+0x94`, and strides at `+0x98` and `+0x9C`. Unsigned shifts and comparisons support the dimension widths. The matched neighboring driver and plane copier were read in full; they confirm the buffer pointers, dimension and stride offsets. The two previously named opaque offset members retain their bank names and dword representation. No shared header registers this context view, and the class gate accepts it.

The target selects two ordinary function addresses for the final callback. They are executable functions, rather than vtables: `0x009AD750` is selected for mode at least two and the landed `Rva009ACC80Filter` at `0x009ACC80` otherwise. The calls at target `+0x15E` and `+0x1D9` push context, source byte pointer, destination byte pointer, unsigned stride, unsigned fragment width, fragment index and limit-table pointer, then remove the argument bytes. Complete final-callback decodes end at ordinary returns; they index a dword table through the seventh argument, read index arrays through context `+0x24`, and update signed variance dwords through context `+0x28`. There is no hidden result, receiver adjustment or virtual dispatch. The landed callback's canonical context declaration is used with an explicit function-pointer cast between the two address-derived context views.

The complete CPU installer at `0x009B0D60` stores generic callbacks `0x009ACF90` and `0x009ADD80`, MMX callbacks `0x009B6D80` and `0x009B8130`, or SSE callbacks `0x009BEBB0` and `0x009BFA40` into the two runtime slots read by the target. Every installed body was decoded through its actual return and passed checked-callee inventory. All use the same stack argument positions and cdecl return convention; some ignore the seventh slot. Runtime calls carry the same seven dwords for every tier. No pin was added or changed.

The bounding/filter helper reached by the matched neighboring copier was decoded through `0x009ADD7A`, including its return. Its ledger extent ends inside the final stack restoration, so the ABI check used the complete extent instead. This note does not change that unrelated row or claim a recovery of that helper. There is no STL value type, ownership inference, constructor unwind path or vtable-owner inference in this attempt.

## New hypothesis and measurement

The new landed callback provides a canonical final-callback declaration. More substantially, complete target decoding refutes the saved bank's fixed middle-row callback pointers: target `+0x148` through `+0x151` advances both live buffer pointers by eight strides on every iteration, and its final callback receives the advanced pointers. The saved bank initializes callback pointers once outside the loop and leaves the final pointers at the original position. The landed adjacent plane copier independently uses cumulative advancement. A decode showing fixed pointers or a final call receiving the original pointers would refute this correction.

The corrected source advances both pointers cumulatively, recomputes the tail copy delta, uses the canonical landed final callback and the recorded `const void *` declaration of the low-mode limit-table global, and assigns the fragment offset in the selected plane branch. The row and dimension records are source-local compiler-shape hypotheses; they claim no codec member layout or original aggregate type. The better bank remains a complete, nonmatching reconstruction.

The authoritative measurement inventory is `build/copy-plane-009aeee0/measurements.json`; the table below is generated from raw probe output. These diagnostic differences use the probe's relocation mask and do not establish correctness. In particular, the retained candidate still has misaligned relocation operands, and the ordinary candidate byte gate fails.

| Raw probe log | Compiled bytes | Non-relocation differences | First difference |
|---|---:|---:|---:|
| `00-saved-probe.log` | 468 | 399 | `+0x6` |
| `01-advance-probe.log` | 472 | 410 | `+0x2` |
| `02-canonical-probe.log` | 472 | 410 | `+0x2` |
| `03-aggregate-probe.log` | 472 | 409 | `+0x2` |
| `04-pointer-before-table-probe.log` | 488 | 383 | `+0x2` |
| `05-scoped-probe.log` | 488 | 383 | `+0x2` |
| `06-plane-switch-probe.log` | 504 | 384 | `+0x2` |
| `07-unsigned-table-range-probe.log` | 504 | 384 | `+0x2` |
| `08-switch-subtract-probe.log` | 504 | 384 | `+0x2` |
| `09-row-aggregate-probe.log` | 488 | 382 | `+0x3` |
| `10-table-switch-probe.log` | 504 | 376 | `+0x2` |
| `11-delta-inner-probe.log` | 489 | 412 | `+0x2` |
| `12-split-offset-probe.log` | 488 | 336 | `+0x2` |
| `13-copy-cursors-probe.log` | 489 | 385 | `+0x2` |
| `14-delta-guard-probe.log` | 488 | 393 | `+0x2` |
| `15-guard-row-aggregate-probe.log` | 488 | 392 | `+0x2` |
| `16-unsigned-index-probe.log` | 488 | 336 | `+0x2` |
| `17-signed-fragment-fields-probe.log` | 488 | 336 | `+0x2` |
| `18-plane-dimensions-first-probe.log` | 488 | 358 | `+0x2` |
| `19-split-offset-row-record-probe.log` | 488 | 332 | `+0x2` |
| `20-increment-each-iteration-probe.log` | 488 | 336 | `+0x2` |
| `21-positive-bytes-probe.log` | 488 | 336 | `+0x2` |
| `22-inline-row-copy-probe.log` | 370 | 310 | `+0x2` |
| `23-inline-enabled-probe.log` | 516 | 408 | `+0x2` |
| `24-pointer-pair-probe.log` | 488 | 333 | `+0x2` |
| `25-best-listing-probe.log` | 488 | 332 | `+0x2` |
| `26-split-if-dispatch-probe.log` | 472 | 405 | `+0x2` |
| `27-dimensions-record-probe.log` | 488 | 330 | `+0xB` |
| `28-row-width-record-probe.log` | 488 | 332 | `+0x2` |
| `29-reuse-plane-count-probe.log` | 488 | 332 | `+0x2` |
| `30-clean-best-probe.log` | 488 | 330 | `+0xB` |
| `final-bank-probe.log` | 488 | 330 | `+0xB` |

Every trial source and unedited raw probe output is retained in the task folder. The bounded generator's original choices, trial sources and result manifest are retained in `build/shape_search/e16a55a3e11d4ca99081b7dfe1b50c89/`. Its register-order alternatives and scalar frame alternative did not change the output. Signed fragment fields, unsigned local index, nested scope, direct cursor copies, inner and guarded delta lifetimes, inlined row-copy helper, pointer pair, dimension-first dispatch, dead-plane countdown and row-width record alternatives were measured and rejected when they failed to improve the complete candidate. The initial inline-helper experiment retained two calls under `/Ob0`; enabling inlining produced a worse complete body. No assembly, volatile workaround, baseline expansion or guessed pin was used.

## Remaining blocker and reopening condition

The candidate's frame size now agrees, but mode and zero scratch registers are exchanged, height is hoisted into EBP before plane dispatch, the source and delta share the dead x argument slot, and final callback and row locals occupy different frame slots. These lifetime differences propagate through callback setup and both copy loops. Reopening is justified by a native donor or independently supported local representation that explains the unhoisted height, persistent source register and witnessed row/delta homes. Another unconstrained register-order sweep has no supporting evidence.

The ordinary candidate scoped byte check failed. The unchanged dump row passed its scoped byte, literal, constant, DIR32 and body guards. Pin consistency and class checks passed. Direct `name_regression.regressions` comparison of the old bank and candidate found no descriptive-to-placeholder substitutions; the CLI expects revision arguments in this checkout, so its file-path invocation was rejected before the direct API check. The declaration guard rejects the scratch candidate as a source with no ledger row, which is expected for a bank. No source was installed in `game/`, no ledger row or pin was changed, and no full gate is required by the bank-only change. The initial `build.cmd` entry point could not locate a Python installation via its `py -3` launcher; the required scoped gate completed through the same existing `tools/build.py` entry point using the available Python executable.
