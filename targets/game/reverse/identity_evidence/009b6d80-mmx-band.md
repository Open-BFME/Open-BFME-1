# RVA 0x009B6D80 MMX band-filter attempt

This is a partial reconstruction, not a landing. The tested base is `0b64ac4a425605880e8542e7416e59b07754064e`. The preferred body is `targets/game/reverse/attempts/0x009b6d80.cpp`; it defines `?Rva009B6D80@@YAXPAURva009B6D80Context@@PBEPAEHIIPBI@Z`. Its owner remains unknown. No function row or symbol pin is changed.

The new hypothesis was that compiler-generated loop control around the packed MMX kernels could reproduce retail, following the existing `BfmeBlurRowsMmx.cpp` and codec filter siblings. Inspection of `BfmeConv9C2620.cpp` supplied a specific new lever: `/Z7` with aligned locals and an EBP-using assembly island emits retail's return-address-copy prologue. The hypothesis would be refuted by a complete measured candidate that could not improve on the prior evidence. There was no prior saved body. The first measured candidate was five thousand bytes long; `/Z7`, local initialization order and ascending variance sums established the exact prefix through `+0x093E` outside relocation operands. The remaining first divergence is scalar CSE at `+0x093F`, rather than the previously untested handwritten-MMX blocker alone.

Boundary evidence is `build/rva009b6d80/retail.asm`, `retail.bin` and `structure.json`. The full 5028 bytes decode into 1456 instructions, including 1150 instructions with MMX operands. The sole return is `+0x13A3`; preceding and following padding separate this body from its neighbours. Every conditional branch and unconditional jump has an instruction-aligned destination inside the extent. There are no calls or tail jumps. `checked_callees.log` confirms the complete extent has no direct callees. No EH registration or cleanup path exists in the decoded body.

Identity and ABI evidence comes from the complete installer at RVA `0x009B0D60` and the complete indirect caller at RVA `0x009AEEE0`, retained in `installer.asm` and `slotref_009aeee0.asm`. The installer instruction at RVA `0x009B0EE9` assigns this target to slot VA `0x01356E88` in the MMX tier. The caller selects that slot at `+0x27`, saves it at `[esp+0x20]`, and calls that saved value at `+0x15E` after seven pushes. The arguments, in callee order, are context (ESI), source (EBP), destination (EBX), stride (EDI), count (EDX), start index (ECX), and a strength-table pointer (EAX). Its `add esp,0x1C` establishes caller cleanup, and it does not consume EAX as a result. No receiver adjustment or hidden return storage is present. The target reads those seven stack slots through EBX at offsets `+8` through `+0x20`. `checked_dispatch_caller.log` and `checked_installer.log` retain the helper's complete decoded-call inventory. The earlier inspection of `0x009AF0D0` concerns slot `0x01356EB4`, so it is not target ABI evidence.

The context view is address-derived. The target reads a pointer at context `+0x24`, loads a complete dword key from that array, then loads a dword strength with that key. At context `+0x28` it reads the metric-array pointer and adds eight zero-extended variance words to each affected dword. Those accesses establish the array element widths; allocation sizes and donor names are not used as type evidence. Stride, count and start are passed as 32-bit quantities. Unsigned loop comparisons are explicit. Stride's original signed declaration is not recoverable from these operations; signed and unsigned 32-bit trial declarations emitted identical instructions. The pointer and integer declarations describe this decoded ABI without claiming a proprietary class identity. No shared header declares `Rva009B6D80Context`, and the name oracle reports no witnessed layout for it.

The packed constants at VAs `0x012D86C0` and `0x012D86D0` contain four 16-bit threes and four 16-bit fours. They are local constant arrays in the candidate, with six relocations instead of literal image addresses. The first MMX island saves EBP before using it as an image pointer and restores it before scalar metric updates. Both filter islands and the copy island have balanced explicit saves and restores. The complete intrinsic alternative is `trial21.cpp`, with raw output `probe21.log`; it emitted 7283 bytes and a different prologue. It does not establish that every conceivable intrinsic spelling is impossible. The assembly-island candidate uses the repository's existing MMX-kernel approach while leaving thresholds, pointer advances, loop control and metric accumulation in C++.

The final named-local candidate `trial23.cpp` emits 5023 bytes against 5028 retail bytes. There are 98 positional non-relocation differences, beginning at `+0x93F`, plus 5 missing bytes. The repository's `finish_measure` formula gives 0.9785. This is a diagnostic bank score, not semantic or byte-match acceptance. `probe23.log`, `compiled23.asm`, `relocs23.json` and `remaining_differences.json` retain the raw result and every differing offset. The remaining regions are the scalar rewind at `+0x093F`, the second loop's register selection, and its metric/update/return tail. The scoped byte gate failed on this candidate; `scoped_gate.log` retains its complete output. The baseline check passed within that gate. `class_gate.log` records the scoped declaration check. The optional native comparison was not executed because the bundled linker failed with `LNK2023` for `msobj71.dll`; see `native_compile.log`. No native-equivalence result is claimed.

All trial sources and raw probe outputs remain in `build/rva009b6d80/`. The stock non-EH choice generator was run and its choices retained in `choices09.json`. `shape_search09.log` records the tool's refusal to search a source containing existing assembly islands. It was not bypassed. The following trials describe the tested alternatives; their measurements are read from the retained JSON receipts.

| Trial | Hypothesis or observation | Compiled bytes | Positional differences | First difference |
|---|---|---:|---:|---|
| 03 | A frame-pointer pragma leaves the original prologue unchanged | 5007 | 4567 | `+0x3` |
| 04 | The landed sibling /Z7 recipe restores the aligned prologue | 5023 | 230 | `+0x33` |
| 05 | Initialize the index before the destination local | 5023 | 226 | `+0x266` |
| 06 | Reordering variance declarations does not change their slots | 5023 | 226 | `+0x266` |
| 07 | An aggregate variance record changes scalar CSE and worsens the body | 5016 | 4535 | `+0x3A` |
| 08 | Aligned qword variance declarations do not change the result | 5023 | 226 | `+0x266` |
| 09 | Ascending variance sums restore the buffer slots and scalar loads | 5023 | 186 | `+0x93F` |
| 10 | Separate scalar rewind statements are combined again | 5023 | 186 | `+0x93F` |
| 11 | Separate pointer rewind statements are combined again | 5023 | 186 | `+0x93F` |
| 12 | A signed count cast does not prevent factoring | 5023 | 186 | `+0x93F` |
| 13 | A barrier between rewind terms does not prevent factoring | 5023 | 186 | `+0x93F` |
| 14 | A separate second-loop index changes the first loop adversely | 5045 | 4516 | `+0x26` |
| 15 | /G6 leaves the body unchanged | 5023 | 186 | `+0x93F` |
| 16 | /Og- changes the entire scalar body and frame | 5335 | 4398 | `+0x18` |
| 17 | A stride shift changes arithmetic but worsens the prefix | 5023 | 228 | `+0x1D` |
| 18 | A count shift changes arithmetic without resolving the transition | 5023 | 185 | `+0x93F` |
| 21 | Complete intrinsic kernels have substantial compiler drift | 7283 | 4678 | `+0x0` |
| 22 | A barrier before sample loads restores threshold-store placement | 5023 | 98 | `+0x93F` |
| 23 | Use named locals in the copy island; bytes equal trial 22 | 5023 | 98 | `+0x93F` |
| 24 | A shared strength local leaves the result unchanged | 5023 | 98 | `+0x93F` |
| 25 | The arithmetic helper remains a call under /Ob0 and is rejected | 5023 | 2511 | `+0x26` |
| 26 | Unsigned stride declaration has the same machine ABI and bytes | 5023 | 98 | `+0x93F` |
| 27 | Long casts do not prevent rewind factoring | 5023 | 98 | `+0x93F` |
| 28 | Resetting the index before decrementing the end does not improve bytes | 5023 | 98 | `+0x93F` |

Trials 01 and 02 retain their complete sources and probe logs. Trial 01 established the initial compiler experiment; `/Oy-` in trial 02 did not change its result. Trials 19 and 20 are preserved syntax-failure intermediates of the intrinsic translation, followed by the complete successful compile in trial 21. No verdict was recorded for an intermediate trial.

Reopening is justified by a specific MSVC source-shape or compiler recipe that preserves separate stride/count rewind terms while retaining the current exact prefix, or by independently recovered native codec source. Repeating the rejected reset spellings, changing only variance declaration order, or retranscribing the same MMX islands does not address the measured residue. The body is banked under the several-failed-shapes stopping criterion. No unrelated gate failure is hidden, and no baseline, shared tooling, policy, header, STL symbol or pin has been changed.

Final bank verification is retained in build/rva009b6d80/probe_bank.log and final_validation.json. The saved bank emits exactly the same 5023 bytes as trial 23. check_csv_final.log and class_gate_bank.log record passing checks. A scripted check independently confirms that all branch destinations are decoded instruction starts and all 5028 retail bytes were decoded.
