# Used-dtor COMDAT suppression is blocked: MSVC emits a dangling import

Inspected BFME 1 at origin/master 2026-11-12 (muse-spark-1.3). No source edit
retained. Two link-queue dtors were attempted and both reverted for the same
root cause; a third queue entry was verified stale-fixed.

## The rule (new, proven this session)

`__declspec(dllimport) __forceinline` on a destructor definition suppresses
the COMDAT **only when the TU never ODR-uses the destructor**. When the TU
uses it — even when every use inlines, with zero call relocs — MSVC 7.1 still
emits a dangling `__imp_<dtor>` undefined symbol-table entry. Scratch variants
V1/V3/V4/V6/V7/V8 of Rva00895D30ManagerSubmit.cpp (private objects under
build/diag-t4/, since deleted) prove the trigger is use, not body shape:
empty body, `delete`-free body and accessor-free body all still emit it, while
`__forceinline` alone still emits the COMDAT.

A dangling `__imp_` of a game-local name cannot pass link_check: excused()
covers an `__imp_` name only when retail imports that function
(tools/link_census.py:2167), and a game dtor is never a retail import. So the
suppression trades the COMDAT loser for an unresolved blocker on the same
file. Both edits below were reverted after their scoped gates passed.

The precedents that DO work are unused dtors: LivingWorldEntryUpdate and
Rva00895B20Dependencies (commit titles say "unused"); their fresh objects
were verified to carry neither the COMDAT nor the import.

## T4: ??1RefHandle008958D0 (queue #11, 846 B) — blocked, reverted

Follow-up (same session): the current link order keeps cleanup.obj's
retail 35 B copy first, so the link itself is already correct; the entry is
hygiene against three wrong 32 B function-pointer-view emitters (submit,
ManagerFind, CreateHandle). Suppression was attempted in all three:
- submit: dllimport poisons the TU (inline destructions ODR-use the dtor;
  dangling __imp_; scoped gate passes but link_check would flag unresolved).
- ManagerFind (in-class body): dllimport breaks the pinned $L458 funclet
  ($L458 not in object; row loses its anchor) — the dtor is used.
- CreateHandle (out-of-line __forceinline body): dllimport on an out-of-line
  definition is C2264; deleting the body breaks rva00895A00 (the dtor is
  called, previously via matching routes; removal reroutes to a local 0xC57CD6).
All three reverted; parents re-verified pristine. The wrong copies can only go
once their TUs stop needing the body, which their parents forbid.

Emitters today: submit 32 B wrong (function-pointer view: `dec` + indirect
`call [TheBfmeFree]`) plus three retail-identical 35 B copies (fixup,
release-unref, cleanup; body matches retail at 0x00784A70, relocs to
decrement + bfmeDropA). Suppression direction is right — the kept copy would
then be retail's — but the dtor is used (three inline destruction sites in
bfmeSubmitEVA, parent still byte-matches either way) so dllimport poisons the
TU. No source change retained; the wrong 32 B copy still stands.
re_log: ??1RefHandle008958D0 @ 0x00784A70 blocked,
blocker=toolchain/msvc-dllimport-used-dtor.

## T5: ??1BfmeSharedString (queue #13, 636 B) — stale, reverted

The identical suppression was tried 2026-11-01 and reverted for the same
unresolvable import (attempt_support/link14-bfmeshardstring-dtor-20261101.md);
this session reproduced the dangling `__imp_` in both find TUs with clean
scoped gates and reverted again. Meanwhile the entry itself is stale: commit
5a70c54bbd (2026-11-11, after the census) already bound both find bodies to
call releaseBuffer directly, both parents still match, the remaining 5 B
stubs are referenced by nothing tree-wide (full build/match scan: zero
referrers), and StringBase.obj defines the target. No ledger, pin or source
change needed; the refresh should clear it.

## T1: DynamicVectorClass<VertexMaterialClass*> vtable (queue #17) — still blocked

Verified at current HEAD: matinfo.obj and MeshLoadContextLifecycle.obj emit
byte-identical copies (digest b91e8deb677b, six VertexMaterial-named slots);
the two queued consumer TUs only reference it. The kept copy cannot become
retail's until the six slot rows are identity-corrected (cascade in
0113c614-vmc-vector-mislabel-cascade-20261105.md, superseding the earlier
slot-4/5 proposals). No source edit; consumer spelling already correct.

## T6: ??_7Rva006092D0State@@6B@ (queue #20) — still blocked

Both emitters are wrong (constructor 4 B, destructor 116 B of 28 zeros + one
reloc; retail's 29 slots are all live methods). None of the 12 distinct slot
targets has a functions.csv row, symbols.csv pin or data row, so neither a
class-view completion nor a data-row provider can verify today. Prerequisite:
land the 12 slot bodies first.
