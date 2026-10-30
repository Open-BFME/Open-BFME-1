# 0x01097144 PartitionFilterSamePlayer vtable gate-debt (body_guard_baseline 129-132)

Banked **blocked** 2026-10-30. This is a multi-TU, shared-header, ledger
re-attribution repair, not a single-body reconstruction. The four debt lines are
all DIR32 references to the one vtable at VA 01097144, spelled under five
different class names by seven TUs. Clearing them requires converging every
referencing TU on the one real name, landing a keystone deleting-dtor row, and
replacing the recorded dir32 name. That is a large, entangled change that
violates "keep each change small, verified and easy to rebase," so it is banked
with the full verified mechanics below.

## The four debt lines (targets/game/reverse/body_guard_baseline.csv)

- 129 `dir32,0x01097144,??_7PartitionFilterSamePlayer@@6B@` (the real name)
- 130 `dir32,0x01097144,??_7PlayerFilter0028AE90@@6B@` (clone)
- 131 `dir32,0x01097144,??_7PlayerFilter002A1780@@6B@` (clone)
- 132 `dir32,0x01097144,??_7PlayerFilter0041E9E0@@6B@` (clone)

Each reads: "retail 0x01097144 is already recorded as
`??_7Rva0016A9F0FunctorValueWrapper@@6B@`; reference that name, not a new one."
The recorded name (dir32_addresses.csv:3291) is the functor-bind placeholder.

## Verified identity: 0x01097144 is the PartitionFilterSamePlayer vtable

Raw retail walk (build/partfilter_probe/verify_vtable.py, functor_raw.py): the
table is exactly 3 code slots + 1 null dword (0x01097150), 0x10-pitched like its
neighbours; the next table starts at 0x01097154.

- slot0 (0x01097144) = 0x00412F8F  ILT ?j_00012f8f -> body 0x0016E510 (30 B
  scalar deleting destructor)
- slot1 (0x01097148) = 0x00430C6F  ILT ?j_00030c6f -> body 0x001DC8B0 (28 B,
  the real `allow`, `sete`-style bool epilogue; misnamed row 31144)
- slot2 (0x0109714C) = 0x0043A9E0  ILT ?j_0003a9e0 -> body 0x001DC890 (14 B,
  the real `getPlayerMask` override; misnamed row 57791)
- slot3 (0x01097150) = 0 (terminator)

Two virtuals + deleting destructor = `PartitionFilterSamePlayer`
(`allow`, `getPlayerMask`). The functor-bind family's single virtual
(`functorValueWrapperAnchor`) is documented absent-from-retail/synthetic, so a
real 28 B slot1 body cannot be the anchor: the vtable is SamePlayer's, not a
functor-bind wrapper's. `code_references(0x01097144)` is True (ctor 0x0016A9F0
stores it as imm32).

## The ctor at 0x0016A9F0 is misattributed to the functor-bind family

The 25 B ctor at RVA 0x0016A9F0 stores the vtable 0x01097144 (verified: the
`mov [eax],<imm32>` operand is 0x01097144). The ledger rows it under the
functor-bind family as `??0Rva0016A9F0FunctorValueWrapper@@QAE@PAX@Z`
(functions.csv:4247, source game/GameEngine/Source/Common/
FunctorBindValueWrapperCtors.cpp). That class is the 6th member of a 6-way
byte-identical 25 B ctor family (0x00149FC0/0x00149FF0/0x0014A580/0x0014A5E0/
0x0016A9F0/0x0026FA60). The 25 B body is byte-identical whether the argument is
`void*` or `const Player*` (it is a plain dword store at +0x08), so the family
match is a byte coincidence: 0x0016A9F0 is in fact the PartitionFilterSamePlayer
ctor, and the family's 6th "member" is a misidentified SamePlayer. (The other
five functor-bind vtables are 0x01095714/24/34/44 and 0x010B9340, each also
3-slot; 0x01097144 is the odd one out = SamePlayer.)

## The seven TUs / five names referencing 0x01097144

- `PartitionFilterSamePlayer` (real): game/GameEngine/Source/GameLogic/Object/
  PartitionManager.cpp (key-function TU; defines `allow` at :5057,
  present-unmatched).
- `Rva0016A9F0FunctorValueWrapper` (placeholder): game/GameEngine/Source/Common/
  FunctorBindValueWrapperCtors.cpp (ctor at 0x0016A9F0).
- `PlayerFilter0028AE90` (clone): VeterancyCrateCollideExecute.cpp:77 and
  CommandButtonHuntUpdateScanClosestTarget.cpp:192 (used :554).
- `PlayerFilter002A1780` (clone): Rva002A1780NearestObject.cpp:60 (used :114)
  and VictorySystemNotifyCell.cpp:32 (used :121).
- `PlayerFilter0041E9E0` (clone): DrawableTiming0041E9E0.cpp:53 (used :153).

Every one of these TUs instantiates the SamePlayer class under a private
placeholder name; each ctor emits a DIR32 to 0x01097144 under its own name.
The clone private re-declarations (e.g. VictorySystemNotifyCell.cpp:22-41)
redeclare the base `PartitionFilter` with the correct shape (inline ctor
m_next=0, inline virtual dtor, `virtual bool allow(Object*)=0`,
`virtual Int getPlayerMask()`, `PartitionFilter *m_next`) and the derived with
`Player* m_08` at +0x08 ??? i.e. the same class, different member names. Note the
clone base ctor param is `Player*` (non-const) vs the shim's `const Player*`:
the real ctor param mangling (`PBVPlayer` vs `PAVPlayer`) is unresolved.

## Shared header is also wrong

inputs/reference/shims/partitiondataoutofline/GameLogic/PartitionManager.h:
the base `PartitionFilter` (603-610) has the wrong shape (no m_next, no virtual
dtor, no getPlayerMask), while `PartitionFilterSamePlayer` (646-656,
`const Player *m_player`) is correct. The clones privately re-declare the
correct base. A shared-header fix therefore costs a full gate and must reconcile
every dependent body.

## Clearing mechanics (Path 2 only; Path 1 ruled out)

`unrecorded_dir32_problem` (tools/build.py:3636) for (sym, 0x01097144):
- 3646 `others = at[0x01097144] - {sym}`; 3650 fires unless `others` is empty
  (i.e. the dir32 record holds ONLY sym at that address) or a data row places
  sym there.
- Path 1 (data row) is dead for a vtable: `data_rows.compiled_size` cannot
  `sizeof` a compiler-generated `??_7` symbol, so `verify_row`'s size proof
  fails.
- With the record holding only the real name, 3680 calls
  `dir32_record_guard.function_owner_problem` (vtable branch, :255-280):
  needs `code_references` True (yes), a matched non-generated
  `??_G/??_E<Class>` deleting-dtor row (`dtors`) that is in
  `vtable_slot_targets` (`reached` = {0x0016E510, 0x001DC8B0, 0x001DC890}),
  and no foreign class's dtor in `reached`.

So the fix is:
1. Land the keystone deleting-dtor as a matched, non-generated row
   `??_GPartitionFilterSamePlayer@@UAEPAXI@Z` @ 0x0016E510 (30 B), replacing
   the gen row `??_GGen_dtor_0016e510@@UAEPAXI@Z` (functions.csv:11416,
   game/gen_small/dtors_001.cpp:284-285). The 30 B body is
   push esi / mov esi,ecx / call ILT->7B ??1 reseat / test byte[esp+8],1 / je /
   push esi / call ILT->0x00881EB0 (operator delete) / add esp,4 / mov eax,esi /
   pop esi / ret 4; both calls reloc-masked. `??_G` + first letter U (public
   user dtor) is the MSVC 7.1 mangling (probed in build/partfilter_probe/
   probe_access.cpp). The `??_G` body is emitted by instantiation alone (no
   `delete` needed); the vtable COMDAT is emitted only in a TU that
   instantiates the class (key-function TU = PartitionManager.cpp, which
   defines `allow`). Family precedent: every sibling filter's deleting dtor
   lives in its own `<Class>DeletingDestructor.cpp` (functions.csv:12532-12539).
   TU attribution of the keystone is non-trivial (the vtable and `??_G` are
   both emitted in the key-function TU, whose `allow` is still present-unmatched).
2. Converge all seven TUs on the real name: rename the clone private
   re-declarations (and the functor-bind 6th member) to
   `PartitionFilterSamePlayer`, or point them at the corrected shared shim.
   This also re-homes the ctor row 4247 (0x0016A9F0) from the functor-bind
   family to `??0PartitionFilterSamePlayer@@QAE@PBVPlayer@@@Z` (or
   `PAVPlayer` once the const-ness is resolved) ??? one identity per body, so the
   family drops from 6 to 5 members.
3. Replace dir32_addresses.csv:3291
   (`??_7Rva0016A9F0FunctorValueWrapper@@6B@,0x01097144`) with
   `??_7PartitionFilterSamePlayer@@6B@,0x01097144` via
   `tools/dir32_record.py` (sole writer; `retire` requires the old bare
   identifier absent from game/+shims/ ??? `Rva0016A9F0FunctorValueWrapper` is
   spelled in FunctorBindValueWrapperCtors.cpp, so that spelling must move in
   the same change). Spell the real vtable name in a comment of the repairing
   TU so `repair_queue.locate_source` (git grep -F) finds it.
4. `repair_queue.pass_test` each line via an in-process driver (the names carry
   `?`/`@` and must not cross PowerShell args); on pass, delete the baseline
   lines, commit fix + baseline deletion with a `Verifier-Change:` trailer,
   push with the submodule workaround, `progress.py`.

## Ruled out / do not touch

- Path 1 data row for the vtable (size unprovable; no `??_E` ledger home).
- The 78 B Relationship mask row (functions.csv:58227,
  `?getPlayerMask@PartitionFilterRelationship@@QAEHXZ` @0x001DC910) and the
  contested slot1/slot2 body rows (31144, 57791) beyond the keystone
  conversion.
- The 32 B ctor at 0x0016AA20 (`??0Rva0016AA20VptrZeroObject`, row 4248)
  belongs to a different class (vtable 0x01097154) ??? do not conflate.

## Probes (untracked, build/partfilter_probe/)

probe.cpp + run_probe.py/dump_all.py/dump_vtable.py/dump_vtable2.py (shape/
ctor/vtable: 3 slots, ctor 25 B byte-identical to retail 0x0016A9F0, vtable
symbol `??_7PartitionFilterSamePlayer@@6B@`); probe_mangle.cpp + run_mangle.py
(U=virtual / Q=non-virtual); probe_access.cpp + run_access.py (U/M/E access
letters, `??_E` slot target); verify_vtable.py (raw slot walk); functor_family.py
+ functor_raw.py (the 6 ctor vtables, all 3-slot; 0x01097144 is the SamePlayer
one).
