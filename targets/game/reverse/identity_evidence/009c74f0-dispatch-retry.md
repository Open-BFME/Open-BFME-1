# 0x009C74F0 dispatcher retry

The reconstruction remains partial. The non-naked C++ dispatcher emits the full retail extent and differs only in the order of two independent instructions in the negative-distance arm. Its frame, conditional register saves, SIMD unpack loop, direct calls and resolved table references match. The original naked bank still probes exact, but remains a lift rather than an accepted conversion. No ledger row or pin was changed.

The tested revision is `9397caea2fd93abce7a7261b8b0c71e656936e23`. The model is `gpt-6.1-sol`. Trial sources, complete decoded bodies and unedited subprocess output are retained in `build/rva009c74f0-run/` for collection.

## New hypothesis and result

The current neighboring source `Rva009C7380BinkSse.cpp` contains a C++ source-pointer normalization and four-way dispatch. `BfmeUnpack8to16Sse.cpp` supplies the exact SIMD unpack algorithm. Reading these sources suggested testing C++ dispatch with the actual unpack helper visible, rather than reproducing the entire function in naked assembly. The hypothesis would be refuted if these shapes still required unconditional ESI and EDI saves before the zero-distance return, or could not emit the unpack loop inside the caller.

The helper was inlined. EDI was saved inside the four-tap branch. Mutating the dead incoming source arguments directly, instead of retaining separate pointer locals, moved the compiler's ESI save to the retail position. Writing the unpack directly in that branch, with the dead argument slots holding its source and stride, also reproduced the stride store and loop memory operand. This refutes the earlier blanket claim that non-naked MSVC code cannot reproduce the conditional saves. The remaining mismatch concerns instruction scheduling, not the register-save mechanism.

## Boundaries and ABI

`decode_009c74f0.txt` records the complete 183-instruction body. The entry follows INT3 padding, the final return is at +0x1D0, and INT3 padding follows it. Returns occur at +0x113, +0x140, +0x16B, +0x19E and +0x1D0. Every conditional branch and direct jump stays inside the extent and reaches a decoded instruction start. There are no indirect calls, tail jumps or exception-handling registrations in the target. `checked_target.log` and `checked_009c74f0.log` retain the checked callee inventories.

The complete six direct callees were decoded, including their loop backedges and returns: 0x009C6F20, 0x009C6FC0, 0x009C7490, 0x009C72C0, 0x009C7320 and 0x009C7200. Their `decode_*.txt` and `checked_*.log` files are retained. The four one-pass filters use a seven-dword cdecl interface whose fourth slot is unused. They read byte source pixels, use packed word coefficients, and write bytes on the four-tap paths or words on the two-tap paths. The two-pass helper reads five dword arguments, uses a local temporary, and invokes the horizontal and vertical filters with their independently decoded argument order. The two-row helper reads five dword arguments and writes eight rows of packed words. All return with plain `ret`, and the target removes its outgoing arguments with the corresponding cdecl cleanup. There is no receiver adjustment or hidden return storage.

`caller_009b3b40.txt` records the complete installer. Its instruction at +0xFE stores the target's entry address into slot 0x01356B54. Raw address searches were only screening. `callers.log` validates every reported operand hit on instruction boundaries inside complete decoded bodies. The complete 768-byte caller at 0x009B5530 contains five indirect calls through that slot, at +0x19A, +0x223, +0x278, +0x2A1 and +0x2D1. Each passes seven dwords in the same order and performs cdecl cleanup. At +0x278, the cleanup also removes the two arguments still pending from an earlier call. No call consumes EAX as a result.

The first two arguments are addresses computed from the same source base and displacement terms. The third is a destination address. The fourth supplies the row stride, the fifth and sixth index coefficient records, and the seventh selects the filter family through a full dword test. The candidate retains the saved bank's `rva009c74f0` name, `p1` through `p7` names, seven-dword signature and `LunpackLoop` label. Its integer parameters preserve the existing bank's storage view of the decoded addresses; casts expose their pointer uses at the callee sites. No canonical typed declaration of this dispatcher was found. An owner or middleware identity remains unproven, so the dispatcher stays address-derived. Existing callee names are reused without treating their suffixes as independent owner evidence. No STL container or constructor-unwind claim applies.

The complete unpack helper at 0x009C7450 reads source, destination and stride dwords. It performs eight unaligned vector reads, zero-extends the low eight bytes into words, writes sixteen destination bytes per iteration, and advances the source by its stride. The target embeds that algorithm with a source stride of eight. An intrinsic version was compiled independently and produced an aligned stack frame and different loop code, supporting the limited SIMD assembly in the partial. The dispatch and arithmetic remain C++.

The existing recorded datum `g_012D8C10` supplies the table base. The four-tap table is reached by an addend of 256, with records of 64 bytes. The two-tap records occupy 32 bytes. The decoded callees read the corresponding four or two packed coefficient vectors. The candidate contains no literal image address and introduces no new pin.

## Compiler measurements

All probes explicitly used the independently reviewed retail extent of 465 bytes. Difference counts below exclude relocation slots. Missing trailing bytes are listed separately.

| Trial | Emitted bytes | Common-byte differences | Missing bytes | First difference | Raw log |
| --- | ---: | ---: | ---: | --- | --- |
| Original naked bank | 465 | 0 | 0 | Exact modulo calls | `raw_probe_saved-original.log` |
| C++ pointer locals with force-inlined unpack | 460 | 356 | 5 | +0x0B | `raw_probe_trial_inline.log` |
| Direct parameter mutation with force-inlined unpack | 458 | 198 | 7 | +0x17 | `raw_probe_trial_slots.log` |
| Direct parameter mutation with slot-based unpack | 465 | 4 | 0 | +0x17 | `raw_probe_trial_slot_loop.log` |
| Neighbor's temporary ordering | 465 | 4 | 0 | +0x17 | `raw_probe_trial_order.log` |
| Pointer-typed formal arguments | 465 | 4 | 0 | +0x17 | `raw_probe_trial_pointer.log` |
| Intrinsic unpack | 435 | 349 | 30 | +0x03 | `raw_probe_trial_intrinsic.log` |

The final candidate is `build/rva009c74f0-run/bank_candidate.cpp`, measured by `raw_probe_bank_final.log`. Its diagnostic score is 0.9914. `scoped_gate_final.log` also resolves every relocation through the repository verifier: no masking remains, there are no unresolved symbols, and the only differing offsets are +0x17 through +0x1A. Retail emits `mov ecx, edx; sub eax, edx`; the candidate emits `sub eax, edx; mov ecx, edx`.

Both scheduling follow-ups produced the same instruction result. The two unchanged-experiment limit ends that line of work. The family generator offered only a swap of the unpack source and stride assignments, which does not address the first divergence. `family_choices_raw.json` retains that choice. `family_search_raw.log` records the search tool's refusal to accept a source containing assembly; no generated alternative was compiled and no tool was changed.

## Verification and reopening

The scoped candidate gate fails byte equality at the recorded four-byte residual. Its string, constant, DIR32 and body-guard checks pass. `pin_consistency.log` passes. `class_bank.log` passes. `name_file_comparison_final.json` contains no file-level name regression after restoring the saved loop label. The name-regression CLI takes Git snapshots rather than file paths in this revision; the attempted file-path invocation is retained in `name_regression.log`, and the file comparison used its unchanged `regressions` function. `declared.log` refuses the scratch candidate because it has no matched ledger row, which is consistent with preserving a partial. A full gate is not required for this bank-only change.

Reopening requires a new source-lifetime or compiler-scheduling hypothesis with independent support that could move the source-pointer assignment ahead of the subtraction without changing the frame, calls or unpack code. Another temporary reorder or pointer-formal retry repeats a measured failure. Preserve both the original exact lift and the new non-naked alternative. The alternative is not an exact recovery and must not be landed as one.
