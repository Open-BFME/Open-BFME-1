# 0x0089FDA0 UTF-8 append reconstruction

## Result and reopening condition

This is a banked partial, not a source recovery. The complete candidate remains under `targets/game/reverse/attempts/0x0089fda0.cpp`; the ledger still owns the generated assembly. The tested base is `65ae283316f92f8c96d66d4f1f7e5830931898bf`, and the model is `gpt-6.1-sol`. The remaining blocker is register allocation and pointer lifetime, beginning at the prologue. Reopen with a source representation that explains the early parameter load and preserves the old-size register through the first intrinsic copy. Repeating the recorded scalar, inline-helper or scope variants without that explanation is not justified.

The prior bank omits the zero-reserve arm, places the terminator before the old-text copy, and copies from the header address. Decoding the actual stack displacements disproves that last choice: `+0x117..+0x11C` forms and saves `oldData + 8`; the allocation argument remains on the stack until `+0x16C`, so the source reload at `+0x158` reads that saved payload pointer. The replacement models these operations and the repeated handle loads.

## New hypothesis and refutation

The previous identity deferrals are addressed by the existing address-derived pin and the landed caller `Rva008A9E20CodepointStringValue.cpp`. The register deferral is tested with the current `EAStringCMid.cpp` donor, decoded independently instead of copied from an earlier verdict. The hypothesis was that the missing zero-reserve branch, field reloads through the receiver, and independent lifetimes of the old header and old payload explain the short reconstruction. It would be refuted if those shapes still omitted retail's branches or made no measured improvement over the original bank. The complete shapes reproduce the branches, and the retained candidate improves measured quality, but they do not reproduce the early source load or the complete register schedule.

## Boundary, ABI and ownership evidence

`build/target-0089fda0/target-decode.log` decodes the entire extent. `checked-target.log` reports no direct calls or outgoing branches. All conditional branches stay in the body; there are no tail jumps or exception records in its instructions. The single `ret 8` ends at RVA `0x0089FF72`, followed by fourteen `INT3` bytes before the next landed body. The early no-copy paths join the epilogue after the conditional `EBP` restoration; the nonzero-copy path saves and restores `EBP` inside that region.

The complete caller and donor are retained in `caller-and-changebuffer.log`, with separate checked-callee logs. In caller `0x008A9E20`, `+0x71` pushes the codepoint limit, `+0x73` pushes the byte pointer, `+0x74` supplies the local string handle in `ECX`, and `+0x80` calls the assigned body directly. There is no receiver adjustment or hidden result argument. The target reads the pointer from the first stack slot and tests the second as a signed count; it returns the original receiver in 32-bit `EAX` and removes both stack words. The original overload identity remains unknown, so the bank keeps `EAStringC::rva0089FDA0` and its existing decorated signature. The class spelling is inherited from landed declarations and the original bank; this run does not establish an original EA method name.

The target and complete `ChangeBuffer` helper agree on a handle at receiver offset zero and an eight-byte header. They read the reference count at header `+0`, length at `+2`, capacity at `+4`, and write zero to the bank's hash field at `+6`, all as words. Payload reads and writes start at `+8`. The raw empty block has reference word `0x0101`, zero length and capacity, and a zero payload; `0x012D5298` is data, not an installed vtable. No STL key or payload inference applies.

The indirect allocation at target `+0x134` receives one 32-bit size and returns the new header pointer. The caller removes its argument at `+0x16C`. The indirect release at `+0x19E` receives the saved old header after its word reference count becomes zero; its argument is removed at `+0x1A5`. These are cdecl callback contracts for pool slots zero and four, not independently identified callback implementations. No new pin is needed or added. The target has no constructor unwind cleanup; the caller's string ownership is visible in its complete body and the proposed method preserves that handle contract.

`decode-helper.log` and `checked-decode-helper.log` retain the complete `0x0089DF20` helper used to test the decoder expression. Every return path writes the codepoint through its output pointer and returns the next byte address. No EAString donor was found in the Zero Hour reference tree. No canonical EAStringC header is registered at this base. The adjacent landed UTF-8 slice, suffix, search and normalization files were read directly.

## Measurements and rejected shapes

The table is generated from the unedited `trial-*.probe.log` files using the repository's `finish_measure.parse` quality rule. It penalizes the emitted-size error twice and masks object relocation fields. It is diagnostic ranking; the relocation sites drift in the partial and do not certify their identities. Trial 13 is retained because it measures best; trials 14 and 21 produce the same instructions. `candidate-final.probe.log` verifies that formatting and the evidence marker preserve the same measurement. Direct object comparison confirms exact decoder bytes in the retained candidate over `+0x20..+0xB0`.

| Trial | Emitted bytes | Non-relocation differences | Measured quality |
|---|---:|---:|---:|
| trial-00 | 404 | 277 | 0.1395 |
| trial-01 | 466 | 433 | 0.0708 |
| trial-02 | 466 | 433 | 0.0708 |
| trial-03 | 475 | 440 | 0.0172 |
| trial-04 | 472 | 440 | 0.0300 |
| trial-05 | 472 | 440 | 0.0300 |
| trial-06 | 489 | 415 | 0.0107 |
| trial-07 | 475 | 440 | 0.0172 |
| trial-08 | 472 | 440 | 0.0300 |
| trial-09 | 471 | 290 | 0.3562 |
| trial-10 | 478 | 293 | 0.3197 |
| trial-11 | 467 | 289 | 0.3755 |
| trial-12 | 467 | 289 | 0.3755 |
| trial-13 | 464 | 284 | 0.3820 |
| trial-14 | 464 | 284 | 0.3820 |
| trial-15 | 472 | 440 | 0.0300 |
| trial-16 | 478 | 293 | 0.3197 |
| trial-17 | 467 | 293 | 0.3670 |
| trial-18 | 481 | 439 | 0.0000 |
| trial-19 | 467 | 293 | 0.3670 |
| trial-20 | 467 | 293 | 0.3670 |
| trial-21 | 464 | 284 | 0.3820 |

Trial 00 is the original bank. Trial 01 restores the zero-reserve branch, payload copy and receiver reloads. Trial 02 qualifies decoder pointee reads and is byte-neutral. Trials 03, 07, 17, 19 and 20 split the bounded append or decoder into inline helpers, including reference and pointer returns, without improving the preferred shape. Trial 04 removes the early count return, trial 05 inlines the complete native ChangeBuffer donor, and trial 06 scopes the decoder locals; none improves the retained candidate. Trial 08 folds the complete decoded codepoint helper into the loop and is byte-neutral against trial 04.

Trial 09 uses a top-level volatile pointer parameter without changing the mangled ABI. Trials 10 and 11 preserve payload and header pointer slots. Trial 12 removes the parameter qualifier, and trial 13 uses a one-element saved-header array while keeping the payload pointer slot. Trial 14 changes the counted-loop form and is byte-neutral. Trial 15 replaces the payload pointer slot with an array and regresses. Trial 16 restores the parameter qualifier and regresses. Trial 18 moves the byte-scan pointer into the inner scope and regresses. Trial 21 spells the byte distance as unsigned address subtraction and is byte-neutral. The finite generated loop and copy search also plateaus; its immutable trials and manifest are under `build/shape_search/76393c65d314417baceaf52524443949/`.

## Verification limits

The standard scoped byte verifier fails this candidate; raw output is in `build/target-0089fda0/scoped-byte-gate-final.log`. CSV validation, pin consistency and the class gate pass, with raw logs beside it. File-to-file descriptive-name retention passes through `name_regression.regressions`; the current command-line tool expects Git revisions rather than source paths. `find_declared_unmatched.py --fail` reports the candidate's zero matched rows, so it cannot be committed as a landed game source. No whitelist, baseline, shared header, policy or tooling is changed. The ledger and symbols file remain unchanged, and no full gate is required for the bank and evidence-only change.
