# 0x008941A0: native return handle and owned pair

## Result and reopening condition

This is a measured partial, not a source recovery. The best body is banked as `targets/game/reverse/attempts/0x008941a0.cpp` under the existing name `Rva00894120Vector::find008941A0`. No function row or symbol pin changed. The original owner and original iterator type remain unknown. The iterator class in the bank is a compiler-shape hypothesis with an address-derived name.

| Candidate | Compiled bytes | Retail bytes | Non-relocation differences | First difference | Relocation-layout drift | Measured quality |
| --- | ---: | ---: | ---: | --- | ---: | ---: |
| Original saved body, `build/rva008941a0-20261009/baseline.cpp` | 390 | 429 | 325 | +0x02 | 10 sites | 0.0606 |
| Best new body, `build/rva008941a0-20261009/iterator-state.cpp` | 429 | 429 | 142 | +0x1D | 1 site | 0.6690 |

Quality uses `tools/finish_measure.py`'s byte-distance formula. Normalized instruction similarity is not that quality and does not establish byte equality. Raw measurements are `baseline-probe.log`, `iterator-state-probe.log` and the repeat `best-listing-probe.log` in `build/rva008941a0-20261009/`.

Reopen when there is a concrete source hypothesis that caches the scaled count while reloading the item base on the scan latch, or that places the returned handle in the parameter home without changing its lifetime. The current loop caches the item base and reloads the count. Insertion argument scheduling also differs. These differences remain after the structural experiments listed below. The scoped candidate gate additionally requires an independently justified pin for `?rva00895950@Rva00893030Manager@@QAE?AVRefHandle008958D0@@PAVBfmeStrVKI@@@Z`; this run deliberately adds no pin to an inexact candidate.

## Retry hypothesis and independent evidence

The saved body treated the manager result as a plain pointer and released the original input parameter. It already emitted a direct call, contrary to an earlier attempt record describing an indirect call. The new hypothesis is a native nontrivial handle returned through hidden storage, followed by destruction of that returned handle. The input remains a caller-owned string wrapper. This hypothesis would be refuted by a complete callee returning a raw pointer without hidden storage, or by a caller relinquishing the input string at the target call.

The landed `Rva00893030ManagerFind.cpp` at 0x008958D0 supplies a checked one-pointer `RefHandle008958D0` declaration and a string-wrapper argument. The actual target call is to 0x00895950, whose complete body calls that search, accepts object kind 4 or 5 at object offset 8, increments the returned object's DWORD reference count and stores a pointer or null through the first stack argument. Its epilogue returns the storage pointer in EAX and uses `ret 8`. Thus ECX is the manager, the first stack argument is hidden return storage and the second is the string-wrapper pointer. This resolves the earlier `callee/00895950-ABI` blocker without using a matching donor as type proof.

At target offset +0x75, ESI preserves the input wrapper. The call's hidden output address is the input parameter's former home. After the call, `[EAX]` supplies the boolean test, while the output home supplies the object released through 0x00894D90 and 0x00895320. The input wrapper is used again for pair construction. The bank reproduces this ownership, but the compiler puts the returned handle in a local slot instead of the parameter home.

The complete caller at 0x00894380 constructs a local string wrapper through 0x0089E680, pushes its address at 0x00894487 and calls the target at 0x0089448C. It later releases that string independently. The target has ECX receiver, one four-byte stack argument, no used return value and `ret 4` on both exits. No receiver adjustment occurs at this call. This supports the bank's retained method ABI; the method's existing `void *` argument spelling is kept to preserve its name.

## Boundaries, fields and ownership

`boundary-audit-final.log` validates full instruction coverage, all internal direct branch destinations and every return for the target and supporting extents. The target ends after its second `ret 4` at 0x0089434D, followed by padding. Both return paths and all conditional branches remain inside the extent. The caller has 711 bytes of code, one padding byte and a four-entry switch table in its 728-byte ledger extent. Its indirect dispatch table points to decoded instruction boundaries at 0x00894430, 0x00894430, 0x0089444C and 0x008944AF. Treating the table bytes as instructions was an initial screening error; the final audit separates them.

The target's scan and both construction paths establish count at receiver offset 0, an unused four-byte slot at offset 4 and the item pointer at offset 8. Each item contains a pointer at offset 0 and a four-byte state at offset 4, with stride 8. The scan compares string lengths, then pointer equality, then all string bytes. An existing state 2 becomes 3. A newly inserted item receives state 3 when the manager lookup succeeds and state 1 otherwise. The bank uses an unsigned state representation; the instructions prove its width and observed values, not an original enum name or signedness.

The complete actual forward-copy helper at 0x008926D0 and backward-copy helper at 0x00892730 read and write both item fields with stride 8. The assignment helper at 0x008924B0 reads the source's first field, increments its WORD reference count, decrements and possibly frees the destination's former first field, then copies both fields. The target independently constructs both fields and increments the same WORD count. Consequently this is an owned string pointer plus a four-byte state, not a scalar inferred from allocation size. The full range insertion helper at 0x00893F10 calls those value-copy helpers. Its direct recursive calls and three `ret 12` exits are decoded in `type-decode.log` and `boundary-audit-final.log`.

The complete caller string constructor at 0x0089E680 distinguishes the shared empty string from an allocated string, writes WORD reference count at offset 0, WORD length at offset 2, capacity at offset 4 and a zero WORD at offset 6, then copies the characters and terminator at offset 8. This independently supports the target's string-length and character offsets. The exact meaning of the zero WORD is not claimed.

The global allocation pair uses the existing `g_rva01337A30AllocPair` declaration and DIR32 name at 0x01337A30. The cleanup pushes the string pointer, calls the pair's function pointer at offset 4 and removes four stack bytes, supporting the cdecl free callback declaration. This is an indirect function-pointer call, not a virtual method. No new global address literal or symbol pin is introduced.

## Exception cleanup

The target's FuncInfo at RVA 0x00E46370 has two unwind states. State 0 goes to cleanup 0x00C56EE0 with the item at EBP minus 0x1C; state 1 goes to cleanup 0x00C56EE8 with the item at EBP minus 0x14. Each cleanup tail-jumps to the complete 22-byte destructor at 0x00892890. That destructor owns only the first field, decrements its WORD reference count and frees it through the allocation pair when zero. It does not destroy the state field or the container. The bank's assembly listing emits the same two pair offsets and state transitions. Its standalone item destructor probes exactly modulo its one relocation, recorded in `pair-cleanup-probe.log`; this is supporting shape evidence and is not a new claim on the already-owned destructor address.

The manager callee's FuncInfo at 0x00E46550 has an output-handle cleanup guarded by a constructed-return flag and a separate local-handle cleanup. The complete cleanup funclets at 0x00C570B8 and 0x00C570B0 reach ILT 0x000463AD, which resolves to the complete null-guarded handle destructor at 0x00784A70. That destructor calls the DWORD decrement helper and drops the object only on zero. The target inlines this same destruction sequence. Its pair reference count is a WORD; its returned object's reference count is a DWORD. The proposed declarations keep these lifetimes separate.

## Rejected compiler experiments

The first complete native-handle rewrite compiled to 427 bytes with 338 differences. Following the landed insertion adapter's source reduced that to 336 differences. Reordering the range-local setup reached 327 differences without fixing the frame or ownership-slot scheduling. Explicit parameter-slot reuse regressed to 475 bytes with 350 differences. A typed string comparison operator regressed, as did disabling global optimization and selecting size optimization.

An iterator scan compiled to 429 bytes with 165 differences. Sharing the insertion pointer locals between the two owning-pair scopes produced the best result in the table. Explicit count caching, iterator copy construction, compound iterator increment and begin/end accessor spellings did not change that result. A byte-count iterator regressed to 428 bytes with 329 differences. These unchanged spellings do not justify another retry by themselves.

The visible complete range-insertion donor did not improve the caller; its own reconstruction still differed by four bytes at recursive argument setup. A visible complete native-return manager callee also left the caller unchanged and did not independently match its own retail body. Neither helper is claimed as recovered. Mechanical `eh_levers.py`, `shape_family_levers.py` and finite scan choices were run and retained with raw outputs; no generated choice improved the best body. No unchanged register-only or x87 search should be reopened without new evidence.

## Verification and raw evidence

All experiment sources, compiler outputs, disassemblies and receipts remain under `build/rva008941a0-20261009/`; `measurements.jsonl` indexes the target probes. Each trial was checked against `build/STOP_WORKER` before starting. `target-callees.log`, `helper-callees.log`, the `*-checked.log` records, `type-decode.log`, `extra-abi-decode.log`, `caller-string-ctor-decode.log`, `target-eh.log` and `find-eh.log` preserve the actual decoded evidence. The generated assembly listing is `best-unwind.cod`.

`check-csv-final.log` and `pin-consistency-final.log` pass. `name-regression-direct.log` records no regressions through the repository's text-comparison API; the command-line tool accepts Git revisions, so the requested file-to-file CLI form was unavailable. `class-gate.log` passes for the candidate. `declared-unmatched.log` fails because this partial has no matched source row; that failure is expected and remains unresolved.

`scoped-baseline-gate-python.log` passes the existing generated target row only. `candidate-byte-gate.log` runs the repository's strict scoped verifier with an in-memory candidate row and fails on byte inequality plus the unpinned native-return manager symbol. The generated row remains untouched. `build.cmd` could not find its Python launcher in this sandbox, so the baseline check used its Python build entry point directly. No full gate is required for this bank-only change. No exact recovery, original class identity or linkable candidate is claimed.
