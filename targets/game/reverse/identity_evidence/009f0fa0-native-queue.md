# 0x009F0FA0 reconstruction retry

The retained body is a partial reconstruction, not an exact recovery. It keeps the address-derived `Q1Receiver0134FAAC::m009F0FA0(Rva009EF0D0Element *)` identity. The tested base is `b57be48c295c3d8041151f86e5eafc2eabeb2197`; the model is `gpt-6.1-sol`. Sources, unedited probe outputs, compiler objects and decoded retail instructions are retained under `build/009f0fa0-retry/` in the originating checkout.

## New hypothesis and result

The current ledger supplies the canonical `AssetManagerImpl::AddRequiredAssets` declaration for 0x009EFBF0, replacing the saved body's stale `AssetRegistry::Queue_Keys_009EFBF0` declaration. The neighbouring authored sources use native member queue expressions and provide the touched receiver offsets. The first hypothesis was that the canonical declaration and the sibling's STL exception setting would improve the saved body. An unchanged compiler output would refute it. The canonical declaration leaves the byte shape unchanged, and disabling STL exceptions also leaves the target shape unchanged. Both were measured.

The successful hypothesis was that a reference local bound to `m_deques78[queue]` changes whole-function liveness and common-subexpression selection. Removing that reference and using the native member expression at each access eliminates the early EBX/EBP exchange and the saved queue spill. The alternative using a queue pointer does not. This result is measured in `08-native-queue-probe.txt`, not inferred from a donor's comments. A `for` loop over the extra keys restores the retail loop's receiver spill and reload. Materialising the last index as a signed local gives the closest measured body, although its index arithmetic still differs from retail.

## Boundary and caller ABI

`retail-target-corrected.txt` contains the complete 1198-byte instruction decode. Every direct conditional and unconditional branch stays inside that code extent; the only indirect jump is the seven-case switch at +0x32D. The single return is `ret 4` at RVA 0x009F144B. Two padding bytes follow at 0x009F144E. The owned table occupies 0x009F1450 through 0x009F146B and targets 0x009F130C, 0x009F1323, 0x009F1344, 0x009F13EB, 0x009F12D4, 0x009F12E3 and 0x009F12FA. All are decoded instruction starts inside the body. Four `int3` bytes then separate the next function at 0x009F1470. The ledger's 1228-byte extent includes the code, padding and table. Probe's linear decoding warning at the table endpoint treats table data as instructions and does not establish a boundary defect.

The decoded caller 0x009EB8A0 loads ECX from global VA 0x0134FAAC, pushes its original receiver and calls the target at 0x009EB8BE. The target preserves incoming ECX as the receiver and reads its single argument as an object with a vptr at +0, flags at +4, a key at +8 and an optional key-array pointer at +0xC. This supports the existing opaque thiscall signature and `ret 4`; the EA screening label `AssetManagerImpl::LoadAsset` is not used to rename the owner. See also `009eb8a0-registry-callee.md`.

The original `retail-target.txt` predates a correction to the scratch decoder's outgoing-jump address display. Use `retail-target-corrected.txt`; the underlying instruction bytes were unchanged.

## Values, helper routes and ownership

`helpers.txt`, `deeper-helpers.txt` and `final-helpers.txt` contain complete decoded bodies for the value and ABI helpers. The corresponding `checked-*.txt` files retain the checked call inventories. The push helper is exactly 101 code bytes; the earlier `helpers.txt` display includes its following padding, and `final-helpers.txt` has the exact extent.

| Actual route | Independent decoded observation |
|---|---|
| 0x009EC290, 71 bytes | Both returns pop eight bytes. ECX supplies the tree; the stack supplies hidden iterator storage and a key reference. Nodes compare an unsigned dword at +0x10. This lookup alone does not identify the value type. |
| 0x000065AA to 0x001408C0 to 0x00030413 to 0x0013FA60 | The forwarder copies the returned iterator dword and bool byte into hidden result storage. The insert-unique body reads one key dword and forwards to 0x00048478. Both return paths pop eight bytes. |
| 0x00048478 to 0x0013F760, 179 bytes | Both allocation paths read exactly one dword from the actual value reference and write exactly one dword at node +0x10. Other writes are node links at +4, +8 and +0xC. There is no second payload read or write. The return uses hidden iterator storage and pops twenty bytes, covering that storage and four explicit arguments. This is the value-construction evidence, not the allocation size. |
| 0x0002FB80 to 0x00143B20, 65 bytes | The local wrapper constructor establishes its tree header and count, writes zero at wrapper +0xC and one byte at +0x10, returns the receiver in EAX and pops no arguments. It does not initialise a value payload. |
| 0x00015D7A to 0x00140950 to 0x00015BE5 to 0x00134AA0 | The tree destructor and complete erase helper free the header and nodes. Erase visits the right subtree recursively and the left subtree iteratively, frees nodes and performs no payload destructor call or pointee deletion. Both erase exits pop one node argument. |
| 0x009EF060 to 0x009ED4A0 | The subscript helper copies all four iterator fields, advances by a signed dword argument and returns the element address in EAX with `ret 4`. The advance helper handles both same-block and cross-block paths, including negative offsets, with four-byte element stride. |
| 0x009EF0D0, 101 bytes | The actual push helper reads one dword from the supplied reference, retains it across allocation, and writes one dword to the element slot. It updates the finish iterator and returns with `ret 4`. The fully decoded 0x009EFBF0 caller passes the object pointer that it has just dereferenced for its flags. This establishes the deque's pointer payload independently of an `int` donor or a named pin. |
| 0x009ED8A0, 69 bytes | Both pop paths remove one four-byte slot; the cross-block path frees the old block and updates the finish iterator. There is no element destructor or pointee deletion, no stack argument and no observed return value. |

The key's complete construction has one unsigned four-byte representation and no additional payload field. The target also reads one four-byte key per extra-key array slot. The source retains the established opaque `Rva001408C0Target *` ABI spelling for compatibility with its canonical callees. Whether those key bits denote a pointer or an integer handle, and the nominal key owner's identity, remain unproven. No semantic key type is newly claimed.

## Exception cleanup and indirect calls

`eh-target.txt` maps all three states. State 0 has predecessor -1 and destroys the local wrapper at `[ebp-0x20]` through 0x0000E746, 0x00141CC0, 0x00015D7A and 0x00140950. State 1 has predecessor 0 and releases the lock pointer at `[ebp+4]` through 0x009ECAC0. State 2 has predecessor -1 and releases the final lock pointer at `[ebp-0x28]` through the same helper. The decoded release helper reads the pointer at receiver +0, passes it to `LeaveCriticalSection` and returns without stack arguments. `final-object.txt` retains the compiled map, which has those same predecessor states and receiver offsets. Its local wrapper destructor and lock destructor use the corresponding tree and import release operations. The first direct lock deliberately has no automatic cleanup in this reconstruction because the retail early return retains it.

Each element virtual call in the target sets ECX to the element without a receiver adjustment. Slot +0 returns a narrow-string pointer consumed by byte access and `_strnicmp`; slot +0x10 receives the local wrapper address; slot +0x38 supplies a dword accumulated at receiver +0x20. Other element results are unused. The debug calls use the global debug receiver at slots +0x60 and +0x6C, then pass the returned stream receiver through two +0x38 string calls and a +0x4C completion call. Runtime virtual implementation identities and unused return widths are not established by this body. The declarations are partial ABI views inherited from the bank; an exact recovery would still need that indirect-call review.

## Measurements and rejected shapes

All counts below come from probes with the retail extent explicitly set to 1228 bytes. Missing suffix bytes count against the diagnostic score. Masked scores are not strict relocation acceptance. The final body was recompiled repeatedly and reproduced the same mismatch count.

| Trial | Object bytes | Differing bytes | Missing bytes | Raw output |
|---|---:|---:|---:|---|
| Original saved body | 1204 | 687 | 24 | `00-original-probe.txt` |
| Canonical callee declaration | 1204 | 687 | 24 | `01-canonical-probe.txt` |
| Explicit initial lock local | 1204 | 676 | 24 | `03-local-lock-probe.txt` |
| Native queue member expressions | 1216 | 360 | 12 | `08-native-queue-probe.txt` |
| Key `for` loop | 1228 | 362 | 0 | `10-key-for-probe.txt` |
| Signed last-index local, retained | 1228 | 145 | 0 | `final-probe.txt` |

The finite EH and non-EH searches retain their generated choices and raw receipts in `02-eh-search.txt`, `non-eh-search.txt` and the two `build/shape_search/` directories named in those receipts. `/EHsc-` is worse than the explicit-lock candidate; `_STLP_NO_EXCEPTIONS` does not improve the target. A lock accessor, queue pointer, narrowed queue-reference scope, named destination reference, unsigned last index, signed size before subtraction, const last reference and inline copy helper do not improve the retained result. Their trial sources and unedited outputs remain in the same scratch folder. No unchanged register hypothesis is a reason to reopen this bank.

## Remaining blockers and reopening condition

The first remaining raw byte difference is +0x204, a branch displacement. The first remaining computation difference is +0x2A1 in the last-element size calculation. Retail keeps the node-count decrement before shifting; the retained source folds that subtraction and the final index decrement into `lea ...-0x21`. Scratch registers and the receiver reload around the copy and pop also differ. The key loop, EH state stores and final enqueue match their retail instruction offsets in the retained result. `final-object.txt` records every remaining masked difference offset. Twelve object relocation sites do not align with retail operands, so the byte diagnostic cannot validate those references.

The strict scoped gate in `final-scoped-gate.txt` fails on the mismatching body and these two unresolved symbols: `??A?$_Deque_iterator@PAVRva009EF0D0Element@@U?$_Nonconst_traits@PAVRva009EF0D0Element@@@_STL@@@_STL@@QBEAAPAVRva009EF0D0Element@@H@Z` at 0x009EF060 and `?pop_back@?$deque@PAVRva009EF0D0Element@@V?$allocator@PAVRva009EF0D0Element@@@_STL@@@_STL@@QAEXXZ` at 0x009ED8A0. The assignment pauses adding or changing STL names, so neither pin nor ledger identity was changed. The existing generated `int` helper identities are not proof of the caller's payload type.

Reopening is justified by the STLport header transition, an independently justified index-expression or helper-visibility change that reproduces the decoded arithmetic, or new evidence for the indirect-call declarations. The owner and method may stay opaque. A clean exact-byte result would still require independent relocation and indirect-call acceptance. No function was landed by this retry.
