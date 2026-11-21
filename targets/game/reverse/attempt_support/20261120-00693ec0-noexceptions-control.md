# 00693EC0: no-STL-exceptions axis is measured and inert for the caller

Root held lease16c454bc301c4acab31cea79c586176e. This worker changed no production source, header, ledger, pin, alias, claim, Git index or shared match-cache object. Only two explicit private native compilations were performed, under `build/agent-thing-bfme1-20261120/`.

Input bank SHA256: `a32b44a3dc577429ea09501d5ba24afb5e53cda08cd40735d48ccaa5f12f31ab`.

| Control | Full primary bytes | Non-relocation differences | Native unresolved |
| --- | ---: | ---: | ---: |
| Original `/O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB`, canonical StringInline | 191 | 6 | 0 |
| Same source plus `_STLP_NO_EXCEPTIONS 1` before first STL include | 191 | 6 | 0 |

The two primary COFF bodies have identical SHA256 `cc9ae2a670370a19f6dc41146de82e74579ba818e383c46d8142b172c6cb1d53` and identical11 relocation records. Both native strict resolutions report `masked=false`, `unresolved=[]`, `equal=false`. Differences remain exactly+62,+64,+6F,+72,+74,+77; there is no additional byte improvement. Retail ends `ret4` at+BC, preserving the complete191-byte extent.

The switch was active: emitted external code definitions decrease36→33. `__stl_delete`, node allocator deallocate, and the tree-node allocator deallocate disappear. `_Rb_tree::_M_create_node` and `_M_insert` change. No new definition appears. The existing separately called `insert_unique` boundary leaves the caller unchanged. This is not a valid production-only macro change: it gains no recovered bytes and changes other providers.

## ABI/provider review and limits

The existing canonical string bank uses the actual `StringBase<char>` copy constructor and releaseBuffer spellings; native strict REL32 resolution succeeds. No new alias or address pin was used. Kernel imports remain `WaitForSingleObject(handle,0xffffffff)` and `ReleaseMutex(handle)` with their original stdcall signatures.

The complete native call setup preserves:

* receiver mutex at+48 and referent active byte+41;
* by-value referent string copy, then timestamp value from+38 into the existing `Rva00691ED0Key` constructor;
* real compound-key `Rva006934C0Tree::insert_unique` at6934C0, with ECX tree receiver this+20, a hidden two-word iterator/bool result pointer and const key pointer as separate outgoing arguments;
* existing destroy(receiver,referent,1) through its current provider on the inactive branch.

The bank's two key views have the independently documented unsigned-plus-AsciiString two-word storage. `Rva00691ED0KeyCtor.cpp` actually constructs that layout; `RvaTreeInsertUnique006934C0Compound.cpp` supplies the matched compound-key insertion. They are existing opaque views, not newly proved interchangeable canonical class names. Whole-owner sizeof, a new EA method identity, alias unification and full-image provider selection are not established by this experiment. The source destination remains the EA-associated MilesAudioDevice/MilesAudioCache area, not an invented WWLib template home.

Because the sole new hypothesis is now refuted at the full caller/relocation boundary, no additional source variations, flag sweeps or old register permutations were run. The prior six-byte bank remains untouched. No ordinary production gate or runtime test is claimed for these private diagnostics.

Repro: `bfme1_693ec0_context.py`. Results: `bfme1-693ec0-context.json`, `bfme1-693ec0-context.log`, `bank-static.decode.log`, `bank-static-noexceptions.decode.log`. Both compiles were fresh; native directory-inventory drift caused the private dependency receipt cache to be refused rather than fabricated/reused.

Result: **0 completed bodies,0 new bytes.** Root should record this single bounded negative result with its eventual batch and release only its exact owned claim when appropriate.
