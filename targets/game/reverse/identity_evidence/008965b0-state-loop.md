# RVA 0x008965B0 state loop

The complete target is a no-argument `__thiscall` method with an address-derived owner. The existing pin `?Rva008965B0@Rva00893030Manager@@QAEXXZ` is retained. The body is not an exact recovery. No original method spelling or GameSpy identity is asserted.

## Retry hypothesis

The previous attempts stopped at method identity and supplied no saved body or measured compiler experiment. The current ledger has a manager pin from the caller at RVA 0x00896710, landed reference-object destruction at 0x00895260, and object-table fixups at 0x008A12C0. These supply an address-derived receiver and concrete field and lifetime evidence. The new hypothesis is a repeated traversal of the manager's linked list, with one copied reference handle per node and a second local handle in the successful state-3 arm. It is refuted by incompatible caller stack cleanup, different helper parameter ownership, or an unwind map that destroys different objects. These checks support the hypothesis, but the tested C++ shapes do not reproduce the target's instruction stream.

## Boundary and ABI evidence

The target starts at RVA 0x008965B0 and ends with an ordinary `ret` at RVA 0x0089670F. Every direct conditional branch and direct jump stays inside this extent. Its back edges reach the state test at +0x50, the next-node acquisition at +0x34, or the outer traversal at +0x23. There are no outgoing tail jumps. The next recorded body starts immediately after the return. Raw disassembly and the complete-decode callee inventory are retained in `build/target-008965B0/dis-target.log` and `callees-target.log`.

The complete caller at 0x00896710 loads ECX from VA 0x013377D4 before its call at +0x31, passes no stack arguments, and performs no argument cleanup afterward. The target saves ECX as its owner and reads the list head at owner+0. The existing landed `Rva00893030ManagerCopyOut.cpp` and `Rva00893030ManagerFind.cpp` use the same address-derived owner and two-word `{object,next}` node. The full caller decode and checked inventory are `dis-caller.log` and `callees-caller.log`. A receiver adjustment, hidden return pointer, or additional consumed stack argument in another complete caller would refute this signature.

The manager check at 0x00895B20 consumes the copied pointer at its first stack argument, returns `ret 4`, and returns the byte value zero or one in AL. Its complete body reads the referenced object's +0x10 pointer, then the pointed object's +0x28 count and +0x2C entries. It releases the consumed reference at its common exit. The target tests AL. This supports `bool Rva00895B20(Rva00893030Ref)`, not a pointer argument borrowed without cleanup. Its unwind state zero also destroys the incoming argument. The raw evidence is `dis-895b20.log`, `callees-895b20.log`, and `eh-895b20.log`.

The notification at 0x00896470 reads one stack pointer, releases it on its common exit, and ends with a plain `ret`. It does not consume incoming ECX as a receiver. The target removes four argument bytes after the call. This supports `void __cdecl Rva00896470(Rva00893030Ref)`. Its unwind action also destroys the incoming handle. The evidence is `dis-896470.log`, `callees-896470.log`, and `eh-896470.log`.

The landed fixup body at 0x008A12C0 is a `__thiscall` function ending with `ret 8` at +0x17A. The target passes the +0x14 buffer first, then the +0x10 base pointer, and adjusts ECX to base+8. Its first declared argument is unused by the fixup body; its second is used for the indirect callback. All decoded paths reach the common return. The six-entry owned jump table starts at +0x180 and dispatches the record-kind cases within this body. The complete donor source was read directly. A noinline copy was also compiled beside the caller in trial 18 and did not improve the caller. The raw evidence is `dis-fixups.log`, `callees-8a12c0.log`, and `probe-18.log`.

## Object and callback ownership

Each list node contains a reference pointer at +0 and its next node at +4. The target's copied handle stores only that pointer and increments the payload's first dword. It reads the payload's pooled-string pointer at +4, state at +8, object pointer at +0x10, and buffer at +0x14. The complete landed destructor at 0x00895260 independently reads those fields and the argument at +0x0C. Its common string cleanup decrements a word refcount; states 3, 4, and 5 dispatch the object cleanup at object+8 and free the buffer. The sized object deallocator receives the object pointer and 0x18. These observations support the existing `BfmeDropObjectA` view without inferring a value type from allocation size. Evidence: `dis-dtor.log` and `callees-dtor.log`.

The landed installer at 0x00789440+0x46 writes VA 0x00B892F0 into callback slot VA 0x01337848. This is decoded instruction evidence, not a raw pointer search. The complete 0x007892F0 callback consumes a character pointer followed by a copied reference handle. It forwards another acquired handle to the already-landed `Rva00893030` dispatcher, then decrements and releases its incoming handle before a plain return. The target passes the pooled string's character address at data+8 and the acquired handle, then removes eight bytes. This supports the cast to `void (__cdecl *)(const char *, Rva00893030Ref)` while preserving the canonical global's existing generic declaration. Evidence: `dis-registration.log`, `dis-callback.log`, and `callees-callback.log`. The callback's nested virtual file operation is unrelated to the target's ABI and is not reconstructed here.

## Exception cleanup blocker

The target's handler is RVA 0x00C57290, with FuncInfo at 0x00E46740. State 0 unwinds to -1 through the one-pointer handle at EBP-0x18. State 1 unwinds to 0 through the additional handle at EBP-0x14. Both actions tail-jump through ILT RVA 0x000463AD to the complete cleanup body at 0x00784A70. That cleanup calls the complete decrement helper at 0x00894D90 and then the complete `bfmeDropA` body at 0x00895320 when the count reaches zero. The increment and decrement helpers manipulate only the first dword through a pointer and return the updated value. The drop helper calls the existing object destructor and sized deallocator. Evidence: `eh-target.log`, `dis-cleanup.log`, `callees-cleanup.log`, `dis-increment.log`, `dis-decrement.log`, and `dis-drop.log`.

The tested handle declarations have the required two lifetimes, but their emitted standalone destructor differs from the shared retail cleanup. Giving the actual increment, decrement, and drop definitions to the TU emits a 38-byte destructor with inlined decrement and object destruction rather than retail's 35-byte helper-call body. Reordering those definitions does not change this result. `coff-07.log` and `coff-12.log` retain the emitted instructions and relocation targets. Matching only the main method would therefore leave cleanup emission unresolved. No destructor pin was added to conceal this difference.

## Compiler experiments

All target probes explicitly used the independently decoded retail size and preserved complete output. Sources and logs are under `build/target-008965B0/`; generated search trials and per-trial raw probes are under the `build/shape_search/` directories named below. These are diagnostic masked comparisons, not acceptance receipts. In particular, relocation-site drift prevents treating the first candidate's score as an aligned semantic comparison.

| Trial | Hypothesis | Emitted bytes | Non-relocation differences | First difference |
|---|---|---:|---:|---:|
| 01 | Five-state switch and scoped second handle | 352 | 207 | +0x30 |
| 02 | Explicit comparison chain | 338 | 270 | +0x17 |
| 03 | Three switch cases plus default state tests | 325 | 249 | +0x17 |
| 04 | Cached state in the comparison chain | 338 | 270 | +0x17 |
| 05 | Size optimization | 236 | 196 | +0x00 |
| 06 | Handle dereference accessor | 338 | 271 | +0x17 |
| 07 | Actual refcount and drop definitions visible | 338 | 270 | +0x17 |
| 08 | Enum state representation | 338 | 270 | +0x17 |
| 09 | Comparison chain with explicit done flag | 338 | 270 | +0x17 |
| 10 | Void pointer view of the object field | 338 | 270 | +0x17 |
| 11 | Volatile state with one cached read | 338 | 270 | +0x17 |
| 12 | Helper definitions after handle declaration | 338 | 270 | +0x17 |
| 13 | Inline state getter and setter | 338 | 270 | +0x17 |
| 14 | Separate final-state exits | 338 | 270 | +0x17 |
| 15 | Forced inline handle operations with size optimization | 263 | 218 | +0x00 |
| 16 | One-pointer iterator object | 338 | 270 | +0x17 |
| 17 | Separate conditionals and continue edges | 338 | 270 | +0x17 |
| 18 | Complete landed fixup helper visible | 338 | 270 | +0x17 |
| 19 | Unsigned refcount pointer representation | 338 | 270 | +0x17 |
| 20 | Canonical raw-pointer node and acquiring pointer constructor | 352 | 207 | +0x30 |
| 21 | Canonical raw-pointer node in the comparison chain | 338 | 270 | +0x17 |

The required EH generator produced eight measured trials under `build/shape_search/85aa047de02e4199b0adeb8be745ceb9/`. EH mode and exception specifications gave either the original switch shape or a shorter, worse frame. The non-EH generator's store-order and loop-header combinations gave four unchanged switch results under `build/shape_search/b7174b0ee1e045219627f20ace1b2d05/`. The bounded processor-option search under `build/shape_search/0d1f507612f34e9ca33c2a754cf8a2e0/` left the comparison-chain shape unchanged for G5 and G6; G7 emitted a larger, worse body.

The preferred candidate is trial 20. It preserves the canonical `BfmeDropObjectA *` node field from the landed manager-copy source, and its acquiring pointer constructor reproduces the same best instruction stream as trial 01. The earlier wrapper-valued node view is retained only as a rejected type trial. The preferred candidate emits a jump table after +0x53, while retail uses a comparison chain, and its return occurs before the table rather than at the retail endpoint. Trial 21 supplies the closer control-flow form but loses the hoisted state-four constant and the spilled node pointer, changes the frame, and moves the state-four store below argument preparation. Neither source is a recovery. Reopening is justified by native declaration or helper-visibility evidence that changes branch lowering and constant materialization, together with a cleanup declaration that reproduces the independently decoded shared unwind action. Repeating the rejected field, loop, or EH spellings without such evidence is not justified.

## Verification status

The scoped `add_match.py` byte gates for trial 01 and the final bank both failed and automatically restored the ledger and replacement tombstone. `build/target-008965B0/scoped-gate.log` and `scoped-gate-bank.log` retain the complete raw output. The final bank reproduces the preferred trial's measured result in `probe-bank.log`. In addition to the measured instruction mismatch, the source's typed declarations for the manager check and notification have no pins. Their full-body ABI evidence is given above, but no pin was added for a nonmatching attempt. The declaration checker correctly rejects the unlanded scratch source because it owns no matched ledger row. The class check reports the address-derived member without a shared-header conflict, and the bank's class gate passes. The file-path invocation suggested for `name_regression.py` fails because this checkout's CLI takes Git revisions. Its `regressions` text API reports no name regressions, and the saved body equals trial 20 byte for byte after its two metadata lines; the raw result is `name-preservation.log`. CSV and pin-consistency checks pass; their final raw logs are `check_csv-final.log` and `pin-consistency.log`. These passing inventory checks do not qualify the candidate as a recovery. No shared header, tool, STL row, symbol pin, or baseline was changed.
