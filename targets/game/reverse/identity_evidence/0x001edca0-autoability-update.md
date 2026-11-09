# 0x001EDCA0: AutoAbilityBehavior::update, and its filter constructor at 0x001ED510

## 0x001EDCA0 (1944 bytes)

Old row: `?dup_001edca0@@YAXXZ`, a naked lift in `AutoAbilityBehaviorModuleDataDestructorThunk.cpp` carrying the object symbol `??1AutoAbilityBehaviorModuleData@@UAE@XZ`.
New row: `?update@AutoAbilityBehavior@@UAE?AW4UpdateSleepTime@@XZ` in `AutoAbilityBehaviorUpdate.cpp`.

BFME 1 target evidence:
- The matched AutoAbilityBehavior constructor at 0x001ED8A0 stores vtable 0x010A1AF4 at `this+0x10` (+0x5A: `mov dword ptr [esi+0x10], 0x10a1af4`).
- Slot 0 of that table holds 0x00410A2D, an ILT thunk whose `jmp` lands on 0x001EDCA0. The table is the update-interface vtable, and slot 0 of Zero Hour's `UpdateModuleInterface` is `update()`.
- `tools/ilt_oracle.py check` returns CONFIRMED (p_false 3.9e-4) for `?update@AutoAbilityBehavior@@UAE?AW4UpdateSleepTime@@XZ` and CONTRADICTED for `??1AutoAbilityBehaviorModuleData@@UAE@XZ` at this address.
- The body returns the sleep values 6, a computed delay (default 50) and 0x3FFFFFFF, and it dispatches command buttons. A ModuleData destructor does neither.

The extent is unchanged from the old row: 1944 bytes.

## 0x001ED510 (46 bytes)

Old row: `?set@Rva001ED510@@QAEAAV1@HHDH@Z` in `Rva001ED510Set.cpp`.
New row: `??0PartitionFilterValidCommandButtonTarget@@QAE@PAVObject@@PBVCommandButton@@_NW4CommandSourceType@@@Z` in `AutoAbilityBehaviorUpdate.cpp`.

BFME 1 target evidence:
- The body stores `??_7PartitionFilterValidCommandButtonTarget@@6B@` (0x010A1A5C) at +0, zeroes `m_next`, and stores four arguments at +0x08, +0x0C, +0x10 (a byte) and +0x14. That is the layout of Zero Hour's class: source, commandButton, match, commandSource.
- `tools/ilt_oracle.py check` returns CONFIRMED (p_false 3.9e-4) for the constructor name and CONTRADICTED for the old placeholder.
- symbols.csv already pins the constructor name at this body's ILT, 0x0003A5AD.
- 0x001EDCA0 calls it through that ILT. 0x001EDCA0 matches only when this constructor's body is visible in its TU: declaring it out of line gives 1948 bytes and 1199 diffs.
- The body sits at 0x001ED510, next to the other AutoAbilityBehavior bodies (0x001ED890, 0x001ED8A0, 0x001EDC00, 0x001EDCA0). That is consistent with retail emitting this header-inline constructor from the same TU.

Carried from Zero Hour (`GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h`): the class name, member names and the constructor's parameter order. The extent is unchanged: 46 bytes.

## Callee pin added with this landing

`??0PartitionFilterPlayerAffiliation@@QAE@PBVPlayer@@I_N@Z` at ILT 0x00034BB7, which jumps to 0x00160CE0.
- That body (ledger `?set@Rva00160CE0@@QAEAAV1@HHD@Z`) stores `??_7PartitionFilterPlayerAffiliation@@6B@` and three arguments in Zero Hour's member order.
- ilt_oracle CONFIRMS Zero Hour's exact decoration at 0x00160CE0.
- It contradicts the eleven other spellings tried, which combine `PAVPlayer` / `PBVPlayer`, `H` / `I` / an enum for the affiliation, and `H` / `_N` for the flag.

## Partition filter vtable at 0x010956B0

update() builds a temporary partition filter whose vtable is at VA 0x010956B0. `dir32_addresses.csv` records that table as `??_7BfmeObjEQT@@6B@`, so the class in the landed source is `BfmeObjEQT`. The banked attempt called it `ObjectFilter010956B0`; that was an attempt-local address label with no ledger record, not a different identity. The same address also carries a recorded `??_7DistLODPrototypeClass@@6B@` name, which conflicts with this use as a partition filter and is not relied on here.
