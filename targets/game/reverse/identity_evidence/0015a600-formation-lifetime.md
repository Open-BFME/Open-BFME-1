# RVA 0015A600: formation coordinate lifetime

## Result and reopening condition

This is a partial recovery, not a landing. The retained symbol is `?apply@Rva0015A600Bucket@@QAEHPBUCoord2D@@H@Z`. Strict relocation resolution emits 308 bytes against the complete 308-byte retail body and leaves 14 differing bytes. The raw gate is `build/0015a600-retry/scoped-gate-preserved.log`; its decoded comparison is `build/0015a600-retry/strict-comparison.json`. Reopen with independently justified source or compiler evidence that explains the initial live-zero comparison, the order of the two zero stores, or the ESI/EDI assignment. Repeating the rejected initialization, pointer alias, or declaration spellings is not new evidence.

The tested revision is `20f64813a005b14e1c5326631287c2ea4bb1f878`; the model is `gpt-6.1-sol`. The ledger remains a generated assembly row. No pin, shared header, policy, or tooling change is part of this attempt.

## New hypothesis and refutation

The old saved body copies the input coordinate outside the loop and therefore accumulates a coordinate across objects. Retail's loop back edge returns to RVA 0015A621, which reloads both coordinate components from the first stack argument before the next object. Retail also finishes the y calculation before the second override call, whereas the saved body delays that calculation until after the call. The corrected lifetime and order are independently required by the decoded instructions. They would be refuted by an edge that bypasses the input reload or by a y store after the second override call; neither occurs in the complete body.

The subsequent hypothesis was that a native coordinate assignment, rather than two unrelated float stores, requires materializing the pair and thereby restores the FPU lifetime and integer copy at the tail. The GeneralsMD `Object.h` donor defines `setFormationOffset(const Coord2D&)` as aggregate assignment. That donor is an expression-shape lead, not independent BFME offset evidence. The target's writes at Object+0x31C, +0x320 and +0x324 supply the BFME offsets. Pair assignment removes the surplus FPU lifetime operations. A scalar integer replaces the bank's unused two-element spill array without volatile accesses. Chained initialization restores the retail extent. The aggregate-counter hypothesis was tested separately and rejected because it lengthened the body and displaced the frame accesses.

## Complete boundaries and ABI

The complete target has the half-open extent [0x0015A600, 0x0015A734), ending in `ret 8`. Every conditional branch remains inside that interval; there is one loop back edge, one shared epilogue and no tail jump or indirect call. The empty-count path bypasses the callee-saved pushes and returns zero in EAX. The positive-count path returns the incremented 32-bit index in EAX. The existing bank's integer return is retained; the only decoded caller does not consume that result, so a historical public return-type identity is not established.

The complete caller is RVA 0015A960, 278 bytes, including its `ret 8`. Its call at RVA 0015AA3C targets the complete five-byte ILT at RVA 0004758C, which jumps to this body. ECX is the current fixed bucket. The caller pushes a 32-bit second argument and then the address of an eight-byte coordinate local. There is no caller stack adjustment after the call, no receiver adjustment, and no hidden return storage. The next call overwrites EAX before it is read. The target reads the first argument's two floats and stores the second argument's 32 bits into the formation-ID slot. This proves the member calling convention and machine widths, not the nominal enum type of the formation ID.

All three target calls go through the complete five-byte ILT at RVA 000022BB to the complete 26-byte body at RVA 00087A80. The body starts with EAX=ECX, reads only the next pointer at +4, iterates that chain, returns the final pointer in EAX, and ends with plain `ret`. It has no stack arguments, receiver adjustment or hidden return. The matched declaration `const Overridable *Overridable::getFinalOverride() const` and its existing routed pin agree with this ABI. The call sites pass the next override, not the initial template. The direct-call audits are `callees-target.log`, `callees-caller.log`, `callees-override.log` and `callees-thunk.log` in the task's build directory. Complete disassembly and thunk bytes are retained in `decoded.log` and `audit-final.log` there.

The target and caller have no exception frame, unwind map, cleanup helper, allocation, container value constructor or ownership transfer. No STL payload or allocator type is inferred or added.

## Layout and identity

The landed neighbours at RVA 0015A560 and 0015A5B0 load the object template at +4, resolve the same override chain and read the signed integers at template+0x43C and +0x440 respectively. The landed rebuild body at RVA 0015A790 bounds each bucket to six object pointers and advances buckets by 0x1C. It independently reads Object+0x204, the AI interface's current locomotor at +0x1CC, the locomotor template at +4, and its category at +0x74. This refutes the earlier attempt's STL-vector description. The target's `fild` instructions prove signed 32-bit conversion of both template dimensions, and its two input loads and FPU accesses prove two 32-bit coordinate components. Allocation sizes and named pins are not used as value-type evidence.

The candidate includes the shared `Coord2D` and `Object` headers. It exposes the Object header's unmodelled formation storage through inline reference accessors that retain the bank's names. The `Overridable` declaration retains its proven external method and uses inline reference accessors for the observed derived-template offsets, rather than declaring those offsets as fields owned by the real base class. These accessors claim no independent retail function body. The existing `AIUpdate` label remains a partial interface layout view; it is not proof of a separate nominal class. The `AI` and `TAiData` pointer layout agrees with the target and the landed computeSize neighbour. No derived-template owner or bucket class identity is proved; the bucket keeps its address-derived name.

The first attempt to move the fields into two address-derived structs was rejected by `name_regression.regressions`; that source is only a scratch trial. The retained inline-reference form preserves the old identifiers and passes the direct source name comparison and class gate without a correction or exemption. `audit-final.log` retains that check.

## Measurements and rejected shapes

| Trial | Compiled bytes | Differing bytes | First difference |
|---|---:|---:|---|
| Original bank (`trial00-bank.log`) | 319 | 258 | +0x02 |
| `trial02-scalar.cpp` | 312 | 251 | +0x07 |
| `trial03-literal.cpp` | 312 | 251 | +0x07 |
| `trial06-pair-assignment.cpp` | 312 | 244 | +0x07 |
| `trial08-chained-init.cpp` | 308 | 14 | +0x07 |
| `trial10-reverse-chain.cpp` | 312 | 244 | +0x07 |
| `trial12-fixed-bucket.cpp` | 308 | 14 | +0x07 |
| `trial14-native-getters.cpp` | 308 | 14 | +0x07 |
| `trial17-preserve-names.cpp` | 308 | 14 | +0x07 |
| `counter-search-02.cpp` | 313 | 257 | +0x07 |

Separate scalar float stores, a `for` loop, reversed chained initialization, and initialization in a declaration do not improve the retained result. Actual six-pointer capacity, the count getter and the donor's native template/AI getters preserve the same remaining bytes. The finite counter search is retained under `build/shape_search/e381d744de3b40b0b6386744887c81f5/result.json`. The family generator supplied redundant pointer aliases, which do not explain the initial zero stores; they were not adopted. The finite search used the explicit aggregate-counter hypothesis. Its final reporting wrapper failed to serialize a path after both trials completed; the tool's result file and trial sources were already retained. Two search probe logs suffered a receipt/raw-output filename collision; corrected raw verification logs are retained separately and the collision files are preserved.

| Offset | Retail | Compiled |
|---|---|---|
| +0x07 | `cmp edx, eax` | `test edx, edx` |
| +0x0D | `mov dword ptr [esp], eax` | `mov dword ptr [esp + 4], eax` |
| +0x10 | `mov dword ptr [esp + 4], eax` | `unaligned` |
| +0x2A | `mov edi, dword ptr [ebx]` | `mov esi, dword ptr [ebx]` |
| +0x2C | `mov eax, dword ptr [edi + 4]` | `mov eax, dword ptr [esi + 4]` |
| +0x52 | `mov esi, dword ptr [eax + 0x14]` | `mov edi, dword ptr [eax + 0x14]` |
| +0x55 | `mov eax, dword ptr [edi + 4]` | `mov eax, dword ptr [esi + 4]` |
| +0x6C | `fmul dword ptr [esi + 0xa0]` | `fmul dword ptr [edi + 0xa0]` |
| +0x92 | `fmul dword ptr [esi + 0xa4]` | `fmul dword ptr [edi + 0xa4]` |
| +0x98 | `mov dword ptr [edi + 0x31c], ecx` | `mov dword ptr [esi + 0x31c], ecx` |

The strict byte differences are at +0x07, +0x08, +0x0E, +0x10, +0x11, +0x12, +0x13, +0x2B, +0x2D, +0x53, +0x56, +0x6D, +0x93, +0x99. All outgoing call displacements and DIR32 bindings resolve correctly. Baseline, string references, float constants, DIR32 addresses, CSV integrity, pin consistency, class adoption and the direct source name comparison pass. The scoped byte gate fails on this body. A full gate is not required because this is banked evidence and no shared header or landed source changes.
