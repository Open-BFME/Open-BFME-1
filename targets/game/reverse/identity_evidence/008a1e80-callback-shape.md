# RVA 0x008A1E80 callback retry

The tested base is `17734e17bd45389521d9be835da83d5fe60c3056`. The ledger still owns this address as the 483-byte generated assembly row in `game/gen_asm/d_008a0830.asm`. This run preserves a partial C++ body and does not claim a conversion. The model is `gpt-6.1-sol`.

## Hypothesis and result

The saved body already incorporates the landed owner's 32-byte record stride, so the current neighbours do not supply a new fix for that earlier layout mistake. The new experiment exposes the independently decoded and already matched chain-count helper as an inline class definition with `__declspec(noinline)`. This lets MSVC see its register and side-effect behavior while retaining the real call. The hypothesis was that this visibility could recover retail's deferred EBP save and pointer reloads. A callback whose first divergence remained the EBP save would refute that explanation as a complete fix. The helper itself measures exact, but the callback still diverges there. The best candidate is closer by the repository's positional metric, and its return declaration now follows the actual indirect caller.

Raw probes, trial sources, the decoded retail instructions and the scoped gate are retained under `build/008a1e80-run/`. The finite generated local-order search retains its manifest and sources under `build/shape_search/4cfa39fd35ed4dae8dd0faaf01b0dfbf/`; `family-result.json` records that location. Probe's relocation sites do not all align with retail operands. Its positional difference count and the bank score are diagnostics, not a percentage of independently proven bytes. Normalized instruction similarity is also not a byte-match score.

## Boundary, identity and ABI evidence

The full retail decode reaches the last `ret` at target offset `+0x1E2`, followed by INT3 padding at `+0x1E3`. Every conditional branch stays within the 483-byte extent, and there is no external tail jump. All direct calls go to decoded body entries, not thunks. `target-callees.log` records the checked inventory. `retail-decode.log` contains the complete target and the helpers used here.

Startup body `0x00894800` allocates the owner, passes its configuration to `0x008A2CF0`, then registers the returned pointer with the callback addresses `0x008A1DF0` and `0x008A1E80` at decoded instructions `0x008949CB` through `0x008949DF`. The complete registration helper `0x008971F0` stores the three arguments in consecutive dwords. The complete consumer `0x008972B0` reads that storage, pushes the index and then the data pointer, calls the second callback through storage offset eight, and cleans eight bytes from the stack. It tests EAX for null and reads flags at returned-pointer offset four. Together with the target's stack reads and plain returns, this establishes a cdecl callback with a state pointer, a signed 32-bit index and a 32-bit pointer result, without receiver adjustment or hidden return storage. The name remains `Rva008A1E80`; registration does not prove an original method or class name. The retained field name `m_vptr` does not assert polymorphism. The owner constructor initializes that field as allocation storage.

`0x008A0C90` consumes ECX and one 32-bit stack argument, divides the pointer difference by twenty, computes a signed remainder and returns a slot pointer with `ret 4` on both paths. `0x008971D0` takes one cdecl pointer argument and makes a virtual call at slot `+0x14` with the unadjusted pointer in ECX. Only AL of that virtual result is consumed; the canonical unsigned-char declaration fits that evidence, but no original virtual method identity is claimed. Its two exits return the input pointer or zero in EAX. `0x008BD1B0` follows the head pointer and links at `+0x58`, returning a signed dword count. `0x008BD1D0` takes one signed stack index, follows the same links and returns a pointer or zero with `ret 4`. The declaration spellings are retained from their landed source files, and no new pin is required.

## Storage evidence

The target reads each packed slot's discriminant at zero. For discriminant zero, the odd index returns the dword at `+0x10`, while the even index returns null. For discriminant one, the odd index returns `+0x08` and the even index passes `+0x0C` to the pointer-filter helper. These are pointer-bit views in the callback result path; there is no inferred STL key or pair type.

The complete value constructor `0x008A0FF0` writes all eight fields of the actual record: it zeroes `+0x00`, `+0x04`, `+0x08`, `+0x0C`, `+0x10` and `+0x14`, writes capacity six at `+0x18`, allocates the buffer and writes its pointer at `+0x1C`. The target tests the first dword, returns the dword at `+0x04`, reads the count at `+0x14`, and reads pointer-array elements through `+0x1C`. Both target success paths shift the record index left five, and the walking cursor advances by 32. The saved body's stride agrees with these instructions. The constructor's allocation alone was not used to infer a scalar or pair payload. No constructor is implemented by this retry, and the target has no EH frame or cleanup path.

No shared header declares the retained local types in this checkout. The landed neighbouring data-offset callback, owner constructor and the four direct helper sources were read before compilation. The Zero Hour reference tree contains no `AptAnimation` source to import. Current pins and neighbouring rows resolve the old owner-layout objection but do not resolve the remaining compiler shape. This target does not construct or copy an STL value, so STL key, pair and constructor-unwind inference checks do not apply to its implementation.

## Measurements and rejected shapes

The following table is extracted from the retained raw probe output. Each probe used retail size 483 explicitly. Repeated outputs confirm repeatability in this checkout; they are not independent proof of identity.

| Raw log under `build/008a1e80-run/` | Emitted bytes | Positional non-relocation differences | First difference |
|---|---:|---:|---|
| `probe-00-original.log` | 485 | 364 | `+0x26` |
| `probe-01-visible-count-confirmed.log` | 483 | 355 | `+0x26` |
| `probe-01-visible-count.log` | 483 | 355 | `+0x26` |
| `probe-02-visible-at.log` | 485 | 364 | `+0x26` |
| `probe-03-tail-subobject.log` | 489 | 368 | `+0x26` |
| `probe-04-tail-guard.log` | 489 | 368 | `+0x26` |
| `probe-05-typed-ring.log` | 489 | 368 | `+0x26` |
| `probe-06-pointer-result-fixed.log` | 483 | 355 | `+0x26` |
| `probe-07-reload-zero-slot.log` | 483 | 355 | `+0x26` |
| `probe-08-slot-zero-label.log` | 483 | 355 | `+0x26` |
| `probe-09-null-slot-barrier.log` | 499 | 403 | `+0x26` |
| `probe-10-tail-barrier.log` | 483 | 355 | `+0x26` |
| `probe-11-inline-scan.log` | 483 | 355 | `+0x26` |
| `probe-12-scan-break.log` | 483 | 355 | `+0x26` |
| `probe-13-reuse-index-param.log` | 483 | 355 | `+0x26` |
| `probe-14-size-optimization.log` | 428 | 396 | `+0x0` |
| `probe-15-no-global-optimization.log` | 804 | 457 | `+0x0` |
| `probe-16-visible-check.log` | 483 | 355 | `+0x26` |
| `probe-17-visible-check-advance.log` | 483 | 355 | `+0x26` |
| `probe-18-null-ternary.log` | 483 | 355 | `+0x26` |
| `probe-19-slot-switch.log` | 483 | 393 | `+0x0` |
| `probe-20-flat-tail-accessor.log` | 489 | 368 | `+0x26` |
| `probe-best-final.log` | 483 | 355 | `+0x26` |
| `probe-best.log` | 483 | 355 | `+0x26` |
| `probe-family-00.log` | 483 | 355 | `+0x26` |
| `probe-family-01.log` | 483 | 355 | `+0x26` |

The bounded generator's local-definition-order alternative reproduced its baseline output. Making the packed-slot helper visible also reproduced the original bank. The verified tail subobject and reverse accessor recovered retail's final address-of-tail pattern but changed the loop cursor and increased total differences. A guard before reading the record array and typed ring pointers did not repair the first divergence. Pointer return typing agrees with the consumer but leaves emitted bytes unchanged. Reloading the known-zero slot, introducing an early null label, expressing that return as a ternary, extracting the scan into a forced-inline helper and breaking to the scan's failure return did not solve the deferred save. The null-slot barrier produces a separate early failure return but still saves EBP at `+0x26`, refuting merged failure returns as a sufficient explanation. The tail barrier does not improve the body. The index-parameter reuse, slot switch, size optimization and disabled global optimization all fail to recover retail. Exposing the exact pointer-filter and chain-advance sources gives no further improvement.

## Remaining blocker and reopening condition

The best source is `build/008a1e80-run/best.cpp`, retained as the preferred bank through `re_log.py`. It still saves EBP at `+0x26` instead of retail's `+0x16E`, folds the two initial pointer loads differently, changes early and final failure-return placement, caches the chain receiver, and differs in the final record cursor and reverse-buffer address calculation. The strict scoped byte gate fails on this target. `strict-measure.json` retains every differing offset after real call relocations are resolved, without applying the candidate's relocation masks to retail opcodes. The original body also emits two bytes beyond the retail extent. There are no unresolved call symbols. The speculative call destinations printed by the failed gate at shifted relocation sites are not valid call-site evidence and do not justify new pins. No source is left under `game/`, no ledger or symbol pin changes are made, and no full gate is required by a bank-only change.

The first pointer-return trial accidentally cast the ring-difference operands to pointers and was refused by the compiler. Its source is retained as `06-pointer-result-failed.cpp` and its raw diagnostic is `probe-06-pointer-result.log`. The corrected pointer-return source is measured separately. The file-pair form described in the assignment is unsupported by this checkout's `name_regression.py` CLI, which expects Git revisions; that failed invocation is retained as `name-regression.log`. The same module's `regressions` function reports no descriptive-name regressions for the actual old and new file contents in `strict-measure.log`.

The final bank is re-probed at its actual path in `probe-final-bank.log`, with the same instruction and relocation result as the selected source. `layout-checks.log` records passing MSVC compile-time assertions for the state, slot, block, record and chain-link declarations. `class-gate.log` records the passing shared-header check, `pin-consistency.log` records the passing pin checks, and `check-csv-final.log` records the passing CSV check after banking. The scoped failure is retained without PowerShell diagnostic formatting in `scoped-gate-raw.log`. Exactly one verdict row was appended for this run, and no new retail bytes were recovered.

Reopen with independently supported native accessor structure or a concrete compiler mechanism that accounts for the delayed EBP save and separated return paths. Another unchanged register-order rewrite does not justify a retry. An instruction path leaving the claimed extent, a different callback-storage consumer, or record accesses contradicting the offsets above would refute the boundary, ABI or layout claims respectively.
