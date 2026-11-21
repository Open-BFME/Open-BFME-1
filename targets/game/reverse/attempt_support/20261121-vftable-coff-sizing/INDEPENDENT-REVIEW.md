# Independent review: compiler-vftable COFF sizing

Verdict: no concrete blocking finding in the reviewed two-file patch. This is a bounded sizing/guard review, not a class-identity, selected-provider or runtime proof.

## Immutable input fence

Author package: `W:/OpenBFME/diagnostics/continue-20261120-body-recovery-1656/agents/transport/vftable-coff-sizing-tooling-20261121`.

- MANIFEST.json:73c1a5c84f68aa37530cd631261f1106b08d3c65063c09e29271cb85a0ffa38e
- vftable-coff-sizing.patch:1846a196957df76e5e74258bf374ff085b87260ae26ccfc354c21a46850dc1a2 (author's frozen patch reference)
- tools/data_rows.py:b2fa197dc19d5bc4b69253e65f6065dc482dfd560024a961fcf687e118b0939c
- tools/tests/test_data_rows.py:a27a39f2b3586ecc8091320bbfd5cfcd8a708f9bbe90fc20aaa47c5ce756e45c
- Unmodified production tool at review:64a9eb329abd32d08e3973ef1d3acbfe32cc497a2f890ce0beb6cd5ea5792240
- Unmodified production test at review:5bc3f6025d9c601ece6f8758bec3eda7e942defd9b586079c50bb36ac676bbf7

Private tool/test and author manifest hashes were independently checked. Read the complete private-vs-live diff, tests and frozen HDF; directly read the pinned BFME2 helper at1e864b34e05f68568db539537b6959d94d104f57. No donor weak-default, Resolver or local-static sizing route was ported.

## Exact change boundary

Independent AST/source-segment comparison finds only one existing top-level function changed: symbol_size. Only _vftable_size is added. Every other existing top-level function/class, including verify_row and Resolver, remains text-identical; the module-doc change describes the new sizing rule. Non-vftable sizeof, scalar agreement, COMMON, allocation bounds and missing-source behavior are retained.

The helper requires external data type0/value0, a complete positive four-byte-multiple READ/INIT_DATA/COMDAT section, no WRITE/EXECUTE/CODE/BSS, raw payload exactly equal to section extent, no competing symbol except exact section-symbol metadata, and exactly one existing-target DIR32 relocation at every word. Nonzero vftable offsets/prefixes, arbitrary dot aliases and extra named COL symbols refuse. It proves a whole dedicated section rather than a52-byte slice or a name/address whitelist. Nonzero addends remain subject to the unchanged byte and pointer-target verifier.

## Independent compiler-free probes

Executed23 negative in-memory helper cases: nonzero offset; function-typed or local table; extra alias/COL/foreign-dot symbols; each four forbidden flags; each three missing required flags; truncated/missing/empty/fractional raw payload; absent/duplicate/overlapping/past-end slot; DIR32NB; unknown target index. Every case returned no size proof.

A dedicated eight-byte table shape passed. Independently hash-checked the author's existing normal-object private snapshot `actual-normal-source.obj` as4fe5ee8613c6eb3fcd912fcae6a5e9d94eef0fa87d4d7f7bc7294e3fd943b2f3 and parsed it with the unchanged native COFF parser. The candidate size API proves exactly52 for its actual table while a forbidden sizeof/probe callback is never invoked. source=None still gives no proof. This is26 bounded pure size/availability controls, zero compiler/preprocessor calls; it is not a data-row admission or a fresh proof of current selected object/provider.

Weak105 refusal remains the unchanged verify_row check requiring each pointer target's storage EXTERNAL2. Read the new regression that exercises it; no weak policy or resolver exception is introduced. I did not rerun that full verifier fixture or the author's full suite. Reported29/29 new cases and86pass/2baseline-identical failures/1existing skip remain author results; seven real CPP/PP tests were explicitly outside the zero-compiler scope, not silently passed.

## Remaining limits and Root boundary

This helper is not a full malformed-COFF/architecture/COMDAT-aux validator; the actual normal object's ANY2 auxiliary selection is separate evidence. A compiler-style name is not original class identity, slot semantics or an owning-source proof. No conclusion about an EA name follows from ??_7. Normal integrity, source currency, table bytes, every pointer/addend, existing strong/weak/local policy and selected-provider checks remain mandatory.

Root must integrate as a separately normally checked verifier change, then retry the original unmodified add_data_match frontdoor for the52-byte table. All96 code rows, the existing three data rows, header/EH consumers and actual selected providers/link proof remain required before coherent source publication. No override, source emitter, mapping, alias, pin, baseline or claim change is recommended. Zero task/body/byte/runtime credit.

Reviewer made no production/Main/Git/claim/source/header/object/shared-cache edits and launched zero CPP/PP. Only this private review HDF and its manifest were written. PC remains on.
