# Native served SpawnUnit ModuleData DIR32 debt, read-only

**Sicher:** the current native ownership predicate already accepts this exact
name/address. **Sicher:** ordinary `repair_queue.py pass-test` cannot currently
locate its compiler-generated owner. No source/data/baseline/tool/Git/claim was
changed; no compiler was invoked. This is **0 new bodies / 0 C++ bytes**.

## Exact served item and coordinates

Input: `R/bfme1/next-default-after-reference-refresh.json`, default selection
53371, `dir32` gate debt. The displayed `target_rva=0x0108E890` is really a VA.
The original PE image base is `0x00400000`; real RVA is **`0x00C8E890`**, in
`.rdata`. Do not claim RVA0108E890.

Name: `??_7SpawnUnitBehaviorModuleData@@6B@`. The exact selected baseline line is:

```
dir32,0x0108E890,??_7SpawnUnitBehaviorModuleData@@6B@,"nothing in the ledger owns 0x0108E890. Give the datum a data row first (tools/add_data_match.py), or use an address name (g_Va<VA>)"
```

The old one-minute blocked attempt said no source spells this symbol. The class
is now reconstructed, but its compiler-generated decorated vtable name is still
not literally written by source. The basename/class token alone is not the
native locator's lookup key.

## Reproduced native result, without compilation

`WRITER-READONLY.json` records calls against current unmodified tools:

* `build.unrecorded_dir32_problem(name, VA,
  build.dir32_identities(build.read_dir32_addresses()),
  build.load_symbol_map())` -> **None**.
* `dir32_record_guard.function_owner_problem` with native function rows and the
  same current recorded/data starts -> **None**.
* `repair_queue.locate_source(name)` -> **None**.
* `data_rows.cpp_name(name)` -> None; `compiled_size(source,name)` returns
  `cannot be named from its TU` before creating a probe or invoking a compiler.

The live ownership finding is therefore stale. This does not establish that a
whole-source gate has passed after removing the baseline, nor that the emitted
table reproduces the full original virtual interface.

## Original identity, boundary, and runtime roles

The complete original ctor00125CE0/114B stores VA0108E890 in `[esi]` at
RVA00125D04 (immediate operand at00125D06). A focused full `.text` search finds
only that dword occurrence. Original registry0012C2E0 independently binds the
literal `SpawnUnitBehavior` to factory ILT0003F611 ->00125D70 -> this ctor;
the adjacent Oathbreakers registration reaches a different factory001246F0.
This corroborates tracked `identity_evidence/00125ce0-spawnunit-module-data-ctor.md`.

Slot0 is VA0042A78E ->00126ED0/30B, the existing authored
`??_GSpawnUnitBehaviorModuleData@@UAEPAXI@Z`. Its body calls ILT00024703 toward
complete destructor00126F00/80B, conditionally calls real operator delete881EB0,
returns the receiver, and removes one dword. The complete dtor destroys strings
at+C/+8 and restores Snapshot-family table01073744. Prior B1 commit
c09ad9adea516558deb7bfa6b4cec633688b1763 used the local name BfmeBaseVUQ for
that restored table; it did not reconstruct this class's live interface.

The bounded original table has **17 entries / 68B**. This is not inferred merely
from adjacent code pointers:

* native `code_references` is true at0108E890 and next start0108E8E8, false at
  every inner word0108E894..0108E8D0 and throughout the following20B;
* 20 zero bytes separate the table's final entry at0108E8D0 from that next start;
* all16 inherited slots1..16 equal both independently witnessed live ModuleData
  table010896B8 and simple data table010BD278 (ctor0028BBF0), exactly;
* the existing original inventory independently partitions C8E890+68 and
  C8E8D4+20 pad, before C8E8E8+68. This supports, but does not alone establish,
  the boundary.

Slots0..16 reach these **body RVAs**, in order:

```
126ED0 113AB0 113AC0 113AD0 1139F0 113A00 113A10 113A20 113EC0
113A30 113A40 113A50 113A60 113A70 113A80 113A90 113AA0
```

The first four roles are deleting dtor / no-op / `ModuleData` literal getter /
ret4 transfer-shaped empty method. Slots4..7 return false, slot8 is a33B
helper with ret8, slots9..15 return zero, slot16 returns true. The actual source
names/types/constness of all unknown inherited APIs are not proven. In
particular, the current opaque BfmeConv735.cpp name for113EC0 is not evidence for
its original class/signature. No uniform bool/pointer declarations are proposed.

Constructor/factory/read-only consumer establish object storage at least0x20,
tag field boundary+4, strings UnitName+8/UnitCommand+C, and SpawnOnce+1C. The
factory allocates0x20 and invokes the independently named field-parser callback.
Neither B2 float declarations nor arbitrary names for+10/+14/+18 are imported.

## Current emitter and whole-source scopes

Native index: commit42237e2367, date2026-11-21 10:53. The sole current table
definer is the existing SpawnUnitBehaviorModuleDataConstructor object. Its
42be7409c5deec24611adb6e7d9261f0edb52f98309b901a6ee8e3e26bec6318 hash exactly
matches that index's inventory. Its table allocation is only4B, with one DIR32
to weak `??_ESpawnUnitBehaviorModuleData`, defaulting to the authored `??_G`.
Constructor and destructor sources share the one-slot BfmeBaseVUQ view; the
destructor class is novtable. Factories and Update have additional local storage
views. A correct slot0 identity does not make their full class models canonical.

`SCOPE.json` lists four related existing sources and all eight existing rows in
them. A future full class reconciliation must include the emitter, real dtor,
factory and consumer, plus selected copies/providers and EH graph. That is a
separate prerequisite, overlapping the already recorded Foundation ModuleData
17-vs8-vs31 blocker. No new shared-header change is justified here.

## Donor review and rejected adaptations

Reviewed B1's official local B2 donor1e864b34e05f68568db539537b6959d94d104f57,
not the separate active B2 workspace. Canonical Common/ModuleData.h and the
5c4cc57fb722c20f255ed66f8e7586ba1ab21029 FamilyUpgradeModuleDataDtors repair
reconcile SpawnUnit's base onto an evidenced31-slot B2 live interface. Commit
d40475ae7b3828e7aa9d26a290d9d75a6043b7f6 documents the same short-table cause
for UpgradeDie and audits all changed provider copies and consumers. The
vtable-bridge-uncovered-survey-20261115 also explicitly records the Spawn
constructor's address-named extern as a remaining repair lead. These support
the diagnosis/method, not a B1 31-slot transplant.

Do not copy the B2 ctor's address-named manual vptr, non-retail inline anchor,
private flags, FamVtableEmissionTag emitters, folded identities or ICF aliases.
Current B1 native live17-slot contract differs from ZH8 and B2 31.

## Ordinary admission / pass-test plan and actual blockers

There is **no actionable new C++ body** and no reason to add a second datum merely
to erase an ownership finding the native predicate already accepts. The current
ordinary pass-test cannot start its real build because the compiler-name owner
locator returns None. Treat this as a narrowly evidenced tool locator limit;
any generic tool correction requires Root's separate scope/normal verification.
No baseline line was deleted here and no source-name comment/alias/marker was
added to force the locator.

For completeness the proposed ordinary data writer, if a fully admissible real
compiler table ever exists, is:

```
python3 tools/add_data_match.py '??_7SpawnUnitBehaviorModuleData@@6B@' 0x0108E890 --va game/GameEngine/Source/GameLogic/Object/Behavior/SpawnUnitBehaviorModuleDataConstructor.cpp --size 68 --model MODEL --evidence EVIDENCE
```

It is **not currently runnable to acceptance**: source emits4B, sizeof grammar
cannot name `??_7`, and current data-row relocation code requires EXTERNAL2 while
the actual table referent is weak105. `--size4` does not resolve either writer
contract, and would prove at most that first datum, never the whole class.
No generated pointer array, replacement global, address-name or pin is proposed.

After a legitimate ordinary locator resolution, Root must execute the exact
served `python3 tools/repair_queue.py pass-test '<baseline line above>'`, which
removes just that line, runs the real owner source gate and restores it on
failure. There is no source override option in its current CLI. The first normal
source test is constructor.cpp (2 existing rows/144B); class reconciliation, if
separately pursued, needs all four files/eight rows/810 retained bytes, genuine
compiler table/data ownership and providers/consumers/whole-object linking.

## Evidence limits

Current original table roles and stale native ownership finding are proven by
the frozen current receipts. Full API signatures, native data admission, a fresh
whole-source gate, regenerated census, final linked image and runtime are not
claimed. No credit, claims, commits, publication or shutdown were performed.
