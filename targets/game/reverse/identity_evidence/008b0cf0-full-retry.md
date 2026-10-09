# Complete callback at 0x008B0CF0

This retry tests the complete 482-byte function at revision `1744eb8181af82b07e22687cd5d2993dbbbb8316`, using model `gpt-6.1-sol`. It changes no production source, symbol pin or function ledger row. The inherited `d_008b0d21` function name and all descriptive names from the saved enclosing-body reconstruction remain intact. The name is an opaque identifier, not an independent entry claim for the continuation.

## Hypothesis and refutation

The earlier boundary blocker is addressed by the complete-function assignment. The payload and result constructors, string setter, intrusive allocator and neighboring record callbacks now have inspectable C++ owners. The hypothesis was that the actual value base, inherited allocation method and canonical constructor declaration would improve the saved full-body reconstruction. No improvement at the complete extent, or disagreement between the reconstructed ownership and native cleanup, would refute it. The inherited allocator improves the measured result; the accessor experiments do not resolve the remaining bytes.

## Complete boundary and ABI

`build/apt-full-retry/retail_cf0.txt` decodes the function and following padding. Its branch at +0x1B enters +0x31 with the exception frame still registered. The early return is at +0x30. The final return is at +0x1E1 after restoring `fs:[0]` and discarding sixteen frame bytes. `checked_008b0cf0.txt` accepts all 482 bytes without outgoing direct branches. The ledger's 433-byte row at 0x008B0D21 is an interior continuation.

The pointer hit at 0x008B27EA belongs to the decoded `push 0x00CB0CF0` at 0x008B27E9 in the lookup function. Its constructor call reaches the complete 31-byte body at 0x00899FC0, which stores the callback at object +0x20 and installs vtable 0x01136128. `xrefs_cf0_verified.txt`, `caller_008b0ee0.txt`, `retail_callback_holder.txt` and `vtable_callback.txt` retain this evidence. `checked_lookup_code.txt` accepts the lookup's complete 6734-byte code extent. `lookup_tables.json` separately validates all direct branches, three jump tables and the index map, accounting for the full ledger extent including switch data.

The complete generic native invocation at 0x008CF740 is retained in `indirect_008cf740.txt` and accepted by `checked_callback_caller.txt`. It checks callable type 9, pushes its third argument as the count and its first argument as the owner, calls the object's function pointer at +0x20, and removes eight bytes. It stores EAX as a returned value pointer and subsequently reads flags at +4. Together with this target's signed comparison against 2, this proves a cdecl owner-pointer and signed-dword-count callback returning a pointer in EAX. No hidden return storage or receiver adjustment is present. Virtual reference-count calls in the invoker are separate from the callback invocation. The original method identity remains unknown and is not a blocker to using its existing opaque name.

## Fields, constructors and cleanup

The complete payload constructor at 0x008AD100 reads thirteen dword arguments, dereferences the first and ninth as value pointers, and stores a string and seven scalar fields through +0x1C. Both exits use `ret 0x34`. The saved float-second-argument declaration names an unbound constructor. The retained candidate uses the existing thirteen-int declaration from the inspected constructor source, preserving its raw second-argument representation. This is a dword ABI view, not proof that all original scalar parameter types were integers.

The result constructor at 0x008B0170 calls the value base constructor at 0x00899F00 and adjusts its member receiver by +0x20 for record copy and assignment. Those complete helpers visit the string and all scalar fields, including conditional copies at +0x14, +0x18 and +0x1C. Their raw decode is in `retail_helpers.txt`, with separate complete checked-callee receipts. The retained candidate includes the witnessed polymorphic base, the record's constructor and assignment declarations, and its member at +0x20.

The neighboring complete 339-byte callback at 0x008B09A0 independently executes `fld [record+0x24]` and `fst [context+0x60]`. It then writes the single-precision 1.0 representation to context +0x60 when required. `neighbor_record.txt` and `checked_neighbor_record.txt` retain the complete decode and inventory. This supports float types for record-relative +4 and context +0x60. The retained candidate uses those float declarations rather than inferring their type from object allocation size. The bytes do not change under this correction.

`eh_cf0.txt` retains four native unwind states, each with predecessor -1. State 0 frees the ordinary payload allocation. State 1 passes the result and size 0x40 to the complete sized headered deallocator at 0x008AB870. States 2 and 3 destroy the two four-byte string temporaries through the complete 22-byte EAStringC destructor at 0x00891B80. `eh_cf0_object.json` confirms the candidate's four predecessor -1 states, and `cf0_13_nativefloat.object.txt` retains all cleanup instructions and relocations. Sizes, receiver offsets and stack cleanup agree; `??3Rva008B0170@@SAXPAXI@Z` is still unpinned, and its original declaring owner remains unproven. No new pin was invented. The pool-release and allocation callbacks have cdecl function-pointer contracts with caller cleanup. The retained pool view keeps the saved bank's existing symbol and its witnessed +4 release slot.

The required 1866-byte linear inventory for the value-to-string helper at 0x008985C0 fails on its inline switch data. The complete 1740-byte code inventory passes. `value_string_tables.json` validates the remaining 84-byte pointer table and 42-byte index map, all destinations and every outgoing direct branch. These separate certificates account for the complete extent and both `ret 4` paths. `checked_008985c0.txt` preserves the failing full-extent tool output; it needs review alongside `checked_008985c0_code.txt` and the table certificate.

## Experiments and reopening

Every trial has an unchanged source, full raw probe and decoded object under `build/apt-full-retry/`. The initial saved full-body reconstruction was reproduced at the complete extent. Correcting its unbound float constructor declaration does not change the masked bytes. Moving allocation into the independently proven value base and retaining the neighboring allocator's raw and adjusted pointer locals removes the first structural allocator mismatch. Value, reference and mutable cursor getters do not improve the result. Value and reference array accessors worsen string-release scheduling. A two-slot pool view does not change the code and adds an unrecorded global spelling, so it is rejected. Canonical record declarations, a polymorphic base and the independently supported float fields preserve the best result. Index-local order does not remove the remaining differences.

The EH generator's checked setter choice and the non-EH generator's final-store interchange do not improve the full-body result. The generated sources and unmodified result receipts remain at the `build/shape_search/` paths named in `cf0_eh_search.txt` and `cf0_family_search.txt`. No register or x87 experiment is repeated after its unchanged stopping point.

The retained body is trial 13. The first difference is a register operand at +0xB2. Structural differences begin at +0xE0: a missing cursor receiver move, a register sentinel comparison instead of a memory comparison, and the associated index reload order. The candidate is three bytes short. Reopening requires a newly evidenced native accessor interface or callee-visibility contract that predicts these operations, plus the sized-delete binding and review of the mixed code/data helper certificate. Repeating the tested getter forms, pool view, local order or compiler switches is unsupported.

## Preservation and validation

The candidate is saved by the repository attempt tools under `targets/game/reverse/attempts/0x008b0cf0.cpp`, with immutable complete-extent source evidence under `attempt_history/0x008b0cf0/`. The automatic banker still measures the unchanged 49-byte prefix ledger row and therefore records a zero header score. The separately measured complete extent and diagnostic quality are recorded in the table and verdict. Missing emitted bytes remain mismatches, and positional relocation masking is not resolved equality.

`gate_cf0_bank.txt` retains the failing complete-extent byte gate using the actual saved bank and an in-memory diagnostic row. `class_cf0_bank.txt` passes, and `audit_banks.txt` reports no source-level descriptive-name regression and verifies the immutable archive digests. `probe_cf0_bank.txt` reproduces the retained trial's complete-extent measurement. `check_csv_final.txt` and `pin_consistency_final.txt` pass. The gate's nonsensical callee addresses result from applying relocation sites to the unmatched instruction layout; they are not new target identities. No shared header, policy, tooling, baseline, generated assembly source or STL symbol changes, so no full gate is required. The saved body remains a partial and contributes no recovered bytes.

## Measured trials

These measurements are generated from the retained raw full-extent probes. The quality metric penalizes positional masked differences and missing bytes; it does not prove resolved byte equality.

| Raw probe under `build/apt-full-retry/` | Emitted bytes | Retail bytes | Positional differences | First byte difference | Diagnostic quality |
| --- | ---: | ---: | ---: | --- | ---: |
| `cf0_00_saved.probe.txt` | 481 | 482 | 271 | +0x95 | 0.4336 |
| `cf0_01_decl.probe.txt` | 481 | 482 | 271 | +0x95 | 0.4336 |
| `cf0_02_nativealloc.probe.txt` | 479 | 482 | 212 | +0xB2 | 0.5477 |
| `cf0_03_getter.probe.txt` | 478 | 482 | 218 | +0xB2 | 0.5311 |
| `cf0_04_refgetter.probe.txt` | 479 | 482 | 212 | +0xB2 | 0.5477 |
| `cf0_05_mutgetter.probe.txt` | 478 | 482 | 218 | +0xB2 | 0.5311 |
| `cf0_06_polymorphic.probe.txt` | 479 | 482 | 212 | +0xB2 | 0.5477 |
| `cf0_07_poolpair.probe.txt` | 479 | 482 | 212 | +0xB2 | 0.5477 |
| `cf0_08_refsubscript.probe.txt` | 478 | 482 | 218 | +0xB2 | 0.5311 |
| `cf0_09_valuesubscript.probe.txt` | 478 | 482 | 218 | +0xB2 | 0.5311 |
| `cf0_10_recorddecl.probe.txt` | 479 | 482 | 212 | +0xB2 | 0.5477 |
| `cf0_11_indexfirst.probe.txt` | 479 | 482 | 213 | +0xB2 | 0.5456 |
| `cf0_12_indexafter.probe.txt` | 479 | 482 | 212 | +0xB2 | 0.5477 |
| `cf0_13_nativefloat.probe.txt` | 479 | 482 | 212 | +0xB2 | 0.5477 |

The target preservation receipt records 1497.2 elapsed seconds from the UTC start timestamp. The record and raw banker output are in `build/apt-full-retry/verdict_008b0cf0.json` and `bank_008b0cf0.txt`.
