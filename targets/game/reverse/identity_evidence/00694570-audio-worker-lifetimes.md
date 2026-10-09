# Audio worker at RVA 00694570

## Result and reopening condition

This is a measured partial, not an exact recovery. The best complete source is banked as `targets/game/reverse/attempts/0x00694570.cpp`, under the existing address-derived `Rva00694570::run` name. Its explicit unsigned-long return records the zero in EAX that retail returns through its thread callback. No semantic class identity, ledger conversion, helper pin or STL identity change is claimed.

The best trial emits 315 bytes for the independently decoded 315-byte retail extent. Four non-relocation bytes differ: offsets `+0x76`, `+0x78`, `+0x7A` and `+0x7F`. These swap EAX and ECX in the sentinel and first-node loads, comparison and payload load. The byte quality is `311/315`; instruction-shape similarity is 1.000. Reopening needs a justified native declaration or access change that changes this exact register sequence, or the STLport header transition that the owner has scheduled. Named-iterator and const-list views already reproduce the same four differences.

## Retry evidence and hypothesis

At base revision `f40013bd9f458e42de838ba3083b616b3ff5edc0`, the canonical default constructor `Rva006910F0Handle::Rva006910F0Handle()` at 006910E0 is real C++ in its own translation unit. The neighboring worker method at 00694130 now has a typed hidden-return and const-reference ABI. These providers address the previous missing-default-constructor obstacle; a new shared handle or worker header is not necessary to probe this address-derived view. No saved reconstruction existed for this target.

The hypothesis was that complete handle, mutex and temporary-handle lifetimes would reproduce the exception frame and the queue loop without invented cleanup states. It would be refuted if these verified lifetimes still failed to reproduce those structural features. The experiments support the lifetime hypothesis but leave the sentinel register sequence unresolved. The constructor's queue types alone were not treated as payload evidence.

## Extent, entry and return ABI

Retail begins at 00694570 with the C++ EH registration prologue. All conditional destinations are inside the target; there are no outgoing tail jumps or indirect method calls in the main body. The stop path reaches the shared epilogue, which zeros EAX and returns at 006946AA. INT3 starts at 006946AB. The extent includes every return path.

The complete 12-byte callback at 00694700 loads its sole stack argument into ECX, calls ILT000279A8, and returns with RET4. ILT000279A8 jumps to 00694570. The landed constructor at 00694710 passes its original receiver as CreateThread's context and ILT000193F8, which jumps to 00694700, as the callback. This establishes the main body's receiver, absence of stack arguments or hidden return storage, and the callback's one-pointer stdcall ABI. The main body writes a four-byte zero result in EAX; the wrapper preserves it. Signedness cannot be distinguished from that constant, so unsigned long follows the native DWORD thread-result convention. The old void-shaped wrapper declaration does not establish a void return for the body.

The constructor stores its supplied context at receiver+48 and its stop byte at +44. The main body passes +48 to WaitForSingleObject with 500 milliseconds and releases that same handle. Its three queue headers are at +14, +18 and +1C. No field or owner name beyond existing address-derived declarations is inferred.

## Complete value construction and ownership evidence

The complete 525-byte producer at 00693B90 passes a pointer value through ILT0001F3A2 to 006925F0. At 00693D1F it stores EDI in a stack slot, which becomes ESP+3C after the constructor pops its argument. The decoded call setup at 00693D35 through 00693D40 passes that stack slot's address and supplies the selected queue receiver. It also stores the same EDI pointer in the separate returned slot at EAX. Another path in the same producer inlines the same pointer construction and list linking at 00693C81 through 00693CA2.

The complete 45-byte 006925F0 helper allocates a node, reads exactly one dword from its argument, stores it at node+8, then writes the next and previous links at node+0 and node+4 and the corresponding sentinel links. Its nullable construction branch skips only that payload store. Both paths end at RET4 at 0069261A; INT3 follows. There is no additional value field, copy-helper call or reference-count operation. The target reads node+8 as a receiver pointer, reads that receiver's count at +34, and passes the pointer to the handle constructor and file helper. Thus the queue payload is a pointer, independently of allocation size, the donor constructor's `list<int>` declaration and the unrelated ShellMenuSchemeImage template alias currently on 006925F0.

The complete handle default constructor at 006910E0 zeros one pointer and returns EAX=this. The complete pointer constructor at 006910F0 stores its sole pointer argument and conditionally invokes ILT0002857E ->006BA1D0; RET4 follows. The complete assignment at 00691140 reads one pointer from the argument, stores it in the receiver, retains the new pointer and releases the old pointer, returning EAX=this with RET4. The destructor at 00691130 tests that same pointer and tail-jumps through ILT000442B0 ->006BA220, or returns directly when null. The two reference-count helpers were decoded completely: 006BA1D0 increments receiver+34 under the owner's mutex, and 006BA220 decrements the same count, records a stamp at +38 and notifies the stored owner when the count reaches zero.

The bank calls the existing assignment declaration through the independently decoded one-pointer `Rva00691140Handle` view and keeps the constructor and destructor's existing `Rva006910F0Handle` declarations. This does not rename or repin the providers. The temporary is destroyed before queue removal. Queue removal unlinks and deallocates the node without destroying or releasing its pointer payload; the outer handle owns the retention across file processing and Sleep.

## Exception graph and mutex contract

The retail handler at 00C472E8 reaches FuncInfo00E36DC8. There are exactly three states, with predecessor transitions -1, 0 and 1. State0 destroys the persistent handle at EBP-1C through ILT000298E8 ->00691130. State1 releases the guard at EBP-14 through ILT0001E961 ->006915E0. State2 destroys the temporary handle at EBP-18 through the same handle-destructor thunk.

The compiled object's actual unwind map has those same transitions and offsets. Its handle actions bind to the canonical destructor. Its mutex action names `??1Rva006915E0@@QAE@XZ`; the emitted 25-byte destructor has the same guarded ReleaseMutex operation as retail006915E0. That production address currently has the ledger name `Rva006915E0::release`, so the destructor binding remains unresolved rather than being silently aliased. This is a binding and identity issue even if the parent bytes become exact.

Returning the raw wait status from the visible acquisition helper, then comparing it to WAIT_TIMEOUT in the main body, reproduces the initial flag promotion, mutex receiver storage, branch destinations and EH-state placement. Returning a bool from acquisition leaves the flag in memory and misses that sequence. The default guard initializes only its live flag; acquisition assigns the mutex before waiting. The imported functions' IAT identities and the repository's Windows declarations agree on four-byte HANDLE/DWORD arguments, stdcall cleanup, a DWORD wait result, BOOL release result and void Sleep result.

## Remaining bindings and validation

The diagnostic scoped verifier uses the proposed row only in memory and changes no ledger. It fails on the four instruction bytes and the unresolved `?rva00694230@Rva00694570@@QAEXPAVGen0002857E@@@Z` call. That helper's complete 654-byte body has one pointer argument, receiver fields +44/+48, three RET4 exits, no hidden result and no caller-used result. The pointer's first word is read as its filename string; further calls update the same object. Its indirect file and debug-stream calls are present only inside that separately decoded helper and are not recreated in this bank. No helper pin was added while the parent remains partial.

The existing STL node-deallocation symbol resolves in the scoped verifier. The partial needs no added STL ledger row or pin. No shared header, policy, tooling, existing source or generated assembly was edited, and no full gate is required for this bank-only change.

## Retained experiments

All raw probes and exact trial sources are under `build/worker-00694570/`. `probe-13.log` records the preferred body. `probe-15.log` and `probe-16.log` reject the named-iterator and const-list views with unchanged bytes. Earlier trials retain the constructor-owned lock, bool acquisition, flag assignment, named temporary, reversed loop guard and explicit-break variants, including their measurements. `eh-search-02.log` and its shape-search manifest retain the generated EH variants and invalid generated throw spellings; the valid flag variants made no improvement. `family-search-04.log` and its manifest retain the finite non-EH generator run, which made no improvement.

`retail-decode-final.log` contains complete target, callback, constructor, handle, reference-count, file-helper, producer and value-copy-helper decodes. `checked-target.log` and the `checked-0x*.log` files retain checked call inventories and outgoing-jump reports. `object-evidence.log` records the compiler symbols, bytes and relocations. `eh-compare.log` checks the three actual emitted states and cleanup receiver offsets, with the unresolved mutex binding explicit. `scoped-byte-gate.log` retains the strict verifier failure. The bank and final CSV check have separate raw logs retained in the same directory.
