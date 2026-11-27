# Generic compiler-vftable COFF sizing — private verifier candidate

**Scoped result: sicher.** The real normal add_data_match refusal was a size-proof false reject: the native compiler emits the complete52B table, but sizeof cannot name a compiler-created `??_7` symbol. This package changes only sizing; no table/class identity, slot-name or target-address policy is inferred from the symbol spelling.

## Frozen two-file patch

Apply `vftable-coff-sizing.patch` only to `tools/data_rows.py` and existing `tools/tests/test_data_rows.py`. Current production files are untouched. `git apply --check` passed against the captured baseline. Root should use a separate **[BFME2donor] Verifier-Change** commit before retrying the actual data frontdoor.

Provenance: local pinned BFME2 donor **1e864b34e05f68568db539537b6959d94d104f57**, `tools/data_rows.py`, `_vftable_size`. The source-owned table52/13 proof is in the previous Node13 lifetime manifest401c1c05c30a107eb74366987bd7d8ac6196b216206691f398df9079dc397a15. No donor Weak105, Resolver, address-ownership, static-data or import exception was copied.

## Exact sizing rule and limits

The new private helper recognizes external, data-typed compiler `??_7...@6B...@` names at offset0. It requires a READ + INITIALIZED_DATA + COMDAT section that has no WRITE, EXECUTE, CODE or BSS flags; nonempty size divisible by4 and an actual raw payload exactly that long. It rejects any other section-local symbol except the exact STATIC/data/offset0 section-symbol metadata. Every word must have exactly one aligned DIR32 relocation to an existing COFF symbol; no extra, duplicate, overlapping, absent, fractional or out-of-bounds pointer field is accepted. Real RTTI/COL prefixes put the table at nonzero offset and are refused; another named COL or alias is refused as well. Ordinary unrelocated alignment padding cannot inflate this size.

There is **no null/zero-addend assumption**. Tests accept independently correct positive and negative addends, and still refuse a wrong retail pointer. The unmodified verify_row checks all initializer bytes and every pointer/addend against real ledger addresses. The unchanged Weak105/TU-local policy remains refusing. No name/source/52-byte whitelist, size override, null-based table scan, raw array, fake extern, resolver mapping or compiler flag was introduced.

This is a section-shape size proof; it is not a full malformed-COFF validator, original class/type proof or full program link proof. The helper consumes the native parser's COMDAT flag; the actual normal-object section aux selection ANY2 is independently captured in the native receipt. Non-vftable sizing, COMMON handling, arithmetic/protected probes, scalar agreement and allocation bounds retain their previous logic. verify_row, Resolver and all other previous top-level functions/classes are text-identical, as recorded in UNCHANGED-GUARD-AND-DONOR-PROVENANCE.json.

## Tests and real-object evidence

29 new Python regression cases: **unmodified baseline25passed/4failed; candidate29/29passed**. They construct complete COFF fixtures using the existing section/aux/relocation emitter and run the actual native data verification logic, never a mock compiler that reports a requested size. Additional direct malformed-payload inputs exercise missing/truncated data, unknown relocation referents and a function-typed supposed table. The fixture-only image/COFF checks are distinct from actual native source admission.

The combined relevant Python scope is **86passed/2failed/1skip,0deselected**. Both failures were rerun against the captured unmodified production tool and are identical: existing test_data_rows_probe_includes fixtures provide a fake build with subprocess.run but no watch_compiler, while the prior real implementation already requires watch_compiler. No unrelated tool/test/skip was changed to hide them. The skip is pytest's existing empty `test_audit_red_team_escapes[NOTSET]` fixture. Seven old tests that really launch C++/PP were explicitly outside this task's zero-compiler permission and are listed by node name in the receipt. A first two-failure replay selected pytest's parent-directory-prefixed node IDs incorrectly and collected0 tests; that path-setup log/receipt is retained separately, followed by the corrected complete two-failure replay.

ACTUAL-NORMAL-COFF-SIZING-PROOF.json reads the **actual current normally built proper ScriptEngine object**, verifies native compile_is_current=True, snapshots its bytes privately and records the actual external data symbol, full52B raw section, thirteen DIR32 entries, section symbols and actual COMDAT ANY2. The baseline size API reproduces `cannot be named from its TU`; the candidate proves52 without calling the supplied forbidden compiler/probe. No data row or private resolver was created; retail/table semantics remain the previously independent proof and Root's upcoming real data verification.

## Root steps

1. Review and normally commit the two-file tooling patch separately, with donor provenance and Verifier-Change metadata.
2. Repeat the original ordinary add_data_match command from `R/bfme1/node13-real-vtable-native.log`. The symbol, source, original RVA CE75C0 and requested52 are unchanged. Let the existing complete byte/target/integrity gate decide; no --no-verify route exists or is proposed.
3. Run the planned actual96/33-source/header/data/EH gates before coherent family publication. Their new data admission is not claimed by this private patch or fixture suite.

No C++ or PP invocations, production source/header/CSV/baseline/pin/Git/claim changes occurred. FINAL-GUARD.json checks all frozen production inputs; Root's separately authorized re_attempts false-reject append is explicitly exempt and its observed hash preserved. All artifacts are private and hash-closed by MANIFEST.json. Suggested tracked review material: patch, this HDF, concise test/real-object/provenance receipts and the manifest; raw generated object and full logs can remain in diagnostics.
