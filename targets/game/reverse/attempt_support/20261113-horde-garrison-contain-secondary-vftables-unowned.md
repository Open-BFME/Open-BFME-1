# HordeGarrisonContain ctor: nine secondary vftables no ledger identity can own

Attempt 2026-11-13, session model qwen38-27b-ninfer. No source, record, pin or
ledger line was edited: the item is a gate-debt repair, and every ownership route
the gate accepts refuses it. Recorded so the next agent starts from ruled-out
routes instead of re-scanning.

## The debt

`targets/game/reverse/body_guard_baseline.csv` lines 116-124 hold nine keyed
`dir32` lines, all for one translation unit:

    game/GameEngine/Source/GameLogic/Object/Contain/HordeGarrisonContainCtor.cpp

Keys (VA, name): 0x010AFAC4 `$06`, 0x010AFAD4 `$05`, 0x010AFB10 `$04`,
0x010AFB20 `$03`, 0x010AFB24 `$02`, 0x010AFB40 `$01`, 0x010AFCE8 `WideSecondaryBase`,
0x010AFCF8 `?dup` (its slot0 is `?j_0001b8c4` -> FUN_0061f920), 0x010AFDC0 primary.
The served item was 0x010AFB24 / `??_7HordeGarrisonContain@@6B?$OpenContainSecondaryBase@$02@@@`.

## Facts measured on this checkout (origin/master at record time)

* Scoped gate WITH the hatch lines: `Source claims OK`, `Functions: OK 1/1 matched`
  (`??0HordeGarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z`),
  `DIR32 addresses: OK (9 reference(s) checked against 17236 recorded symbols)`,
  `Body guard: OK (1 row(s); 0 baselined findings)`.
* Scoped gate with the 0x010AFB24 line deleted (the queue pass-test semantics:
  `tools/repair_queue.py pass-test` deletes the line, runs `tools/build.py SOURCE`,
  puts it back on failure): `DIR32 addresses: FAIL 1 reference(s)`,
  `??0HordeGarrisonContain@@QAE@PAVThing@@PBVModuleData@@@Z +0x57:
  ??_7HordeGarrisonContain@@6B?$OpenContainSecondaryBase@$02@@@: nothing in the
  ledger owns 0x010AFB24 ...`. So the debt is LIVE, not stale, and the hatch is
  what keeps the gate green.
* The gate names the OFFENDING ROW, which is why `repair_queue.py locate_source`
  fails for this item: it looks the vtable NAME up in the ledger (no matched row
  carries a compiler-mangled vtable name) and `git grep -l -F -- <name> game/` is
  empty. The row whose gate fails is the matched ctor row above, 0x00248F90/175 B,
  in that TU. The pass test is drivable by hand through `./build.cmd <source>`;
  hand-running it is what produced the FAIL above. Baseline restored to HEAD
  (byte-identical, 348 dir32 lines, clean `git diff`).
* COFF facts (`build._object_layout` on `game_^...^horde^garrison^contain^ctor.obj`):
  the nine secondary vtables are EXTERNAL section symbols (`storage=2`) in sections
  11-19, `.rdata`, `raw_size=4`, one DIR32 relocation each, bytes `00000000`
  (filled from the reloc). Each is a one-slot table.
* Retail slot0 of each debt VA is a matched `gen-thunk` ILT row: 0x010AFAC4 ->
  `?j_000431df` -> 0x0021B800; 0x010AFAD4 -> `?j_000122e7` -> 0x00248B20;
  0x010AFB10 -> `?j_0001ae10` -> 0x00248BD0; 0x010AFB20 -> `?j_000097b9` ->
  0x00249820; 0x010AFB24 -> `?j_00028678` -> 0x002217E0; 0x010AFB40 ->
  `?j_00019533` -> 0x0021B830; 0x010AFCF8 -> `?j_0000a6c3` -> 0x00119EC0;
  0x010AFDC0 -> `?j_00006528` -> 0x00249110 = the matched
  `??_GHordeGarrisonContain@@UAEPAXI@Z` (30 B). So each secondary table reaches a
  matched deleting destructor exactly like the primary table does.
* `dir32_addresses.csv` records NO name at any of the nine VAs (only
  `??_7HordeGarrisonContainModuleData@@6B@` at 0x010B0788 for this class family).

## Routes ruled out (each refusal is the gate's, not a judgment)

1. `tools/add_data_match.py '<name>' 0x010AFB24 --va --size 4 <ctor TU> ...`:
   `add_data_match: no size is proven for <name>: <name> cannot be named from its
   TU`. `tools/data_rows.py:compiled_size` proves size through a probe TU that
   `#include`s the source and spells the symbol; a compiler-generated vtable has
   no C++ spelling, so no data row can ever carry these names. Same shape as the
   2026-11-06/11 rows that needed a vftable emitter.
2. `tools/dir32_record.py record`: needs `build/dir32_addresses.csv`, which only a
   full gate writes, and even fed by a proposal it re-checks every candidate through
   `build.unrecorded_dir32_problem`, whose only vtable branch is
   `dir32_record_guard.function_owner_problem`. That requires `VTABLE_RE`
   `^??_7(.+)@@6B@$` (a PRIMARY table); a secondary name falls through to the
   function branch and returns `nothing in the ledger owns ...`. Refused.
3. `tools/dir32_record.py retire OLD --for NEW`: needs OLD recorded; none of the
   nine is recorded. No operator-correction route either:
   `tools/dir32_record_guard.py:730` refuses
   `{name} is not a primary vtable ??_7C@@6B@; only those have a correction route`.
4. Respell-to-recorded-name, the pattern every closed dir32 debt line since 2026-11-05
   used (`rg` of 60 commits touching `body_guard_baseline.csv`): impossible here,
   because no recorded name exists at any of the nine addresses (fact above).
   Renaming the ctor TU's base classes cannot help: retail's addresses are fixed, and
   the emitted names are already derived-qualified for `HordeGarrisonContain`.
5. Moving the keys to the other hatch, `dir32_unowned_known.txt`: written only by
   `tools/gate_baseline.py --record-unowned` from a full gate's `build/dir32_unowned.txt`,
   and `validate_file` requires the staged copy to be a subset of HEAD's, so adding
   lines is refused. Also a full gate does not report them while the keyed lines are
   present (`tools/build.py:3858` skips pairs already in `unowned_dir32_baseline()`).
6. Inline asm / literal vptr stores to dodge the relocation: refused by the verdict
   rule (MASM/`__emit` lifts are not conversions) and would leave `gen_asm` shape in
   `game/`.

## Why the siblings are not blocked

`??_7AODHordeContain@@6B?$OpenContainSecondaryBase@$0N@@@`, the GarrisonContain and
ContestableContain pairs at 0x010AE6D8/0x010AB2F8 etc. ARE recorded, at
`targets/game/reverse/dir32_addresses.csv` lines 903-912, 1569-1571 etc. Those were
added by 99e2be2a35 (2026-09-27, "build: check every commit's masked addresses
against the recorded ones"), the bulk seeding that predates the ownership rule.
`git log` over the 60 most recent commits touching that file shows no post-rule
commit ever added a secondary-vftable name: the rule landed and this ctor TU
landed after it, so its nine tables got a keyed baseline line instead of a record.

## Lever gap (recorded, not implemented: gate files are sole-writer-gated)

`tools/dir32_record_guard.py:function_owner_problem` proves a PRIMARY table from
retail slots reaching a matched non-generated `??_G`/`??_E` dtor of the same class,
and `build.py:3709` accepts that as ownership. The nine tables here satisfy exactly
that evidence (slot0 -> ILT thunk -> matched `??_G` / dtor of `HordeGarrisonContain`)
but `SECONDARY_VTABLE_RE` excludes them from the proof and from the correction route.
If the primary-table proof were extended to secondary tables of the same class, all
nine would be provable and the debt lines would close by `dir32_record.py record`
plus deleting lines 116-124. Changing that rule is a gate-machinery decision for a
human maintainer, not something this session may edit.

## Inputs at record time

`check_csv: OK (functions.csv 173475 rows, symbols.csv 91334 rows, data_rows.csv 1859
rows)` at the rebase base; `dir32_record_guard: OK (record moves in 9b03111301..d1c221c3d8
all corrected)`; `DIR32 pins: OK (3437 pins agree with dir32_addresses.csv)`;
`link_check.py --census-only` census `aafdf413e9` unchanged. Ctor TU cl line:
`// cl: /DNDEBUG /MD /EHsc`. Donor freshness: last verified BFME 2 donor inputs
`76f0baefa` (see `build/bfme2-last-check.txt` note6); untouched here.

## Related records

`re_attempts.log` rows 61234/61235 recorded the same ownership gap for the
MobMemberSlavedUpdate vftable family (`blocker=identity/dir32-record-ownership`);
row 60919 records the missing vftable emitter. Cluster: `blocker=identity/dir32-record-ownership`.
