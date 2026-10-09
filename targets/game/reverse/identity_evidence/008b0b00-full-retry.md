# Complete callback at 0x008B0B00

This retry tests the complete 483-byte function at revision `1744eb8181af82b07e22687cd5d2993dbbbb8316`, using model `gpt-6.1-sol`. It does not land a recovery or change a ledger row or symbol pin. The saved reconstruction retains the earlier bank's `aptBuild008B0B32` name. That opaque inherited identifier does not claim that the continuation is an entry point.

## Hypothesis and refutation

The complete-function assignment removes the earlier boundary restriction. The current C++ owners of the payload constructor, result constructor, string setter and intrusive allocator supply independently inspectable declarations and layouts. The new hypothesis was that the actual inherited allocator and visible string assignment would improve the containing-body reconstruction. Failure to improve the restored saved body, or disagreement with the native unwind cleanup, would refute it. The allocator experiment improved the containing-body measurement, but the byte gate still fails.

## Boundary and caller evidence

`build/apt-full-retry/retail_b00.txt` retains the native body and following padding. The branch at +0x1C enters +0x32 after exception registration. Returns occur at +0x31 and +0x1E2; both restore `fs:[0]` and discard the same sixteen-byte registration frame. `checked_008b0b00.txt` accepts all 483 bytes and reports no outgoing direct branch. The 433-byte row at 0x008B0B32 remains an interior continuation.

The absolute-pointer screening hit at 0x008B285B belongs to `push 0x00CB0B00` at 0x008B285A. Its constructor call reaches the complete 31-byte body at 0x00899FC0, which stores its dword argument at object +0x20 and installs vtable 0x01136128. These results are retained in `xrefs_b00_verified.txt`, `caller_008b0ee0.txt`, `retail_callback_holder.txt` and `vtable_callback.txt`. The containing lookup has 6734 bytes of code, two bytes of padding, three jump tables and a byte index map. `checked_lookup_code.txt` checks the complete code; `lookup_tables.json` validates every direct and switch destination against decoded instruction starts and accounts for its complete 7162-byte extent. A linear decode through switch data is not a code certificate.

The actual native invocation is independently decoded throughout the complete 2353-byte body at 0x008CF740 in `indirect_008cf740.txt`. `checked_callback_caller.txt` accepts it without outgoing direct branches. The body checks the callable's six-bit type against 9, pushes the count from its third stack argument and the owner from its first stack argument, calls `[ebp+0x20]` at 0x008CF793, and removes eight bytes. It stores EAX as a value pointer and reads the returned flags at +4. This proves a cdecl callback taking an owner pointer and a dword count, returning a pointer in EAX. The target's signed count comparison supplies signedness. There is no hidden return storage or callback receiver adjustment. The invoker's later virtual reference-count calls are separate. No original method identity is inferred.

## Layout, helpers and cleanup

The neighboring landed `Rva008B09A0ApplyRecord.cpp` and `Rva008B02A0RelativeRect.cpp`, and the actual constructor sources at 0x008AD100, 0x008B0170 and 0x008B0120, were inspected. The complete payload constructor reads thirteen dword arguments and stores the string at +0 and scalar fields at +4, +8, +0xC, +0x10, +0x14, +0x18 and +0x1C. Both exits use `ret 0x34`. The first and ninth arguments are dereferenced as value pointers. The saved body keeps the existing thirteen-int declaration and raw second-argument representation. Allocation size does not establish the original scalar parameter types.

The result constructor calls the base at 0x00899F00, adjusts its member receiver by +0x20, invokes the complete record copy and assignment bodies, returns its receiver in EAX and uses `ret 4`. Their complete field reads and writes are retained in `retail_helpers.txt`, with one checked-callee file per helper. The assignment visits the string and every scalar field, with sentinel tests for +0x14, +0x18 and +0x1C. The independent base constructor installs a value vptr. The retained result view is polymorphic with its member at +0x20. The complete neighboring callback's x87 accesses independently support float types for record-relative +4 and context +0x60; `neighbor_record.txt` and `checked_neighbor_record.txt` retain that evidence. No container payload is deduced from allocation size.

`eh_b00.txt`, `eh_payload.txt` and `eh_result_ctor.txt` retain the native unwind maps. The target has four states with predecessor -1. State 0 deletes the ordinary payload allocation. State 1 passes the result and size 0x40 to the complete headered deallocator at 0x008AB870. States 2 and 3 destroy separate four-byte strings through the complete destructor at 0x00891B80. `eh_b00_object.json` confirms the candidate's four states and predecessor values. The candidate cleanup instructions in `b00_11_polymorphic.object.txt` have the same argument widths, local offsets and destructor targets. The sized-delete symbol `??3Rva008B0170@@SAXPAXI@Z` remains unpinned, and its original declaring owner is unresolved. An artificial inheritance from the address-named deallocator was rejected and is absent from the retained body. Scalar delete, headered delete, intrusive linking and string destruction were decoded to their full returns. Indirect allocation and pool release use cdecl function pointers with caller cleanup.

The value-to-string helper at 0x008985C0 fails its recorded 1866-byte linear extent check at 0x00898CFD because the suffix is switch data. `checked_008985c0.txt` retains that failure, while `checked_008985c0_code.txt` checks the complete 1740-byte executable extent through both `ret 4` paths. `value_string_tables.json` validates its 84-byte pointer table and 42-byte index map, including every dispatch destination and every outgoing direct branch. These separately account for all 1866 bytes. The required full-extent linear tool check remains failing and needs review together with these code and data certificates.

## Compiler experiments

Every trial source, full raw probe and decoded object remains under `build/apt-full-retry/`. Positional relocation masking is diagnostic and does not establish resolved byte equality. The restored saved body, header-pointer adjustment, integer adjustment and artificial deallocator inheritance produced the same first allocator mismatch. Forced inline string assignment removed the incorrect out-of-line assignment call. The inspected noinline linker body and CPU switch did not resolve the first mismatch. Reusing the actual value base and the neighboring allocator's separate raw and adjusted pointer locals removed that structural mismatch. An extra range accessor, a signed bounds accessor, polymorphic layout and raw scalar views did not improve that result. Separate record and cursor locals worsened it.

The EH generator's new valid choices produced no improvement. Its initial mixed stdout/stderr JSON failure and corrected search remain in `eh_search.txt` and `eh_new_search.txt`. Its invalid local-declaration choice and previously exhausted switches were excluded. The non-EH generator offered only the final-store interchange, which did not improve the result. Its raw receipt is in `family_search.txt`. All generated sources and result receipts remain under the `build/shape_search/` paths printed by those logs.

The retained body is trial 11. The first mismatch is a register operand at +0xB3. Structural differences begin at +0xE1, including a missing receiver move, the sentinel comparison form, pool-release scheduling and the final scalar store. Reopening requires new evidence for the native accessor and string lifetime interfaces, review of the auxiliary helper's mixed code/data certificate, and the sized-delete binding. Repeating the tested header arithmetic, accessor layering, scalar views or switches is unsupported.

## Preserved result and gates

The body is preserved with the repository attempt tools under `targets/game/reverse/attempts/0x008b0b00.cpp`, with immutable full-extent source evidence under `attempt_history/0x008b0b00/`. The bank tool still measures the unchanged ledger's 50-byte prefix, so its automatically measured header score is zero. The separately probed complete extent and its diagnostic quality are recorded in the measurement table and verdict. The zero header does not describe a full-extent automatic measurement.

`check_csv_final.txt` and `pin_consistency_final.txt` pass. `gate_b00_bank.txt` is the failing full-extent scoped byte gate using the actual saved bank and an in-memory diagnostic row. `class_b00_bank.txt` passes. The requested file-path invocation of `name_regression.py` fails in `names_best.txt`, because this revision's CLI takes Git revisions. The module's source comparison in `audit_banks.txt` reports no descriptive-name regression and verifies the immutable archive digests. `probe_b00_bank.txt` reproduces the retained trial's complete-extent measurement. `declared_best.txt` correctly refuses an unmatched trial source, so it is banked rather than installed under `game/`. The gate's nonsensical callee addresses come from relocation sites shifted by the unmatched instruction layout; they are not new target identities. No shared header, policy, tooling, baseline, generated assembly source or STL symbol changed. No full gate is required for this evidence-only result.

## Measured trials

These measurements are generated from the retained raw full-extent probes. The quality metric penalizes positional masked differences and missing bytes; it does not prove resolved byte equality.

| Raw probe under `build/apt-full-retry/` | Emitted bytes | Retail bytes | Positional differences | First byte difference | Diagnostic quality |
| --- | ---: | ---: | ---: | --- | ---: |
| `b00_00_saved.probe.txt` | 460 | 483 | 250 | +0x96 | 0.3872 |
| `b00_01_header.probe.txt` | 460 | 483 | 250 | +0x96 | 0.3872 |
| `b00_02_integer.probe.txt` | 460 | 483 | 250 | +0x96 | 0.3872 |
| `b00_03_delete.probe.txt` | 460 | 483 | 250 | +0x96 | 0.3872 |
| `b00_04_assignment.probe.txt` | 482 | 483 | 269 | +0x96 | 0.4389 |
| `b00_05_linkvisible.probe.txt` | 479 | 483 | 282 | +0x96 | 0.3996 |
| `b00_06_g6.probe.txt` | 482 | 483 | 269 | +0x96 | 0.4389 |
| `b00_07_nativebase.probe.txt` | 480 | 483 | 211 | +0xB3 | 0.5507 |
| `b00_08_recordlocal.probe.txt` | 482 | 483 | 364 | +0x33 | 0.2422 |
| `b00_09_rangelayer.probe.txt` | 480 | 483 | 211 | +0xB3 | 0.5507 |
| `b00_10_cursorlocal.probe.txt` | 498 | 483 | 370 | +0x32 | 0.1718 |
| `b00_11_polymorphic.probe.txt` | 480 | 483 | 211 | +0xB3 | 0.5507 |
| `b00_12_scalarbits.probe.txt` | 480 | 483 | 211 | +0xB3 | 0.5507 |
| `b00_13_bounds.probe.txt` | 480 | 483 | 211 | +0xB3 | 0.5507 |

The target preservation receipt records 1447.7 elapsed seconds from the UTC start timestamp. The record and raw banker output are in `build/apt-full-retry/verdict_008b0b00.json` and `bank_008b0b00.txt`.
