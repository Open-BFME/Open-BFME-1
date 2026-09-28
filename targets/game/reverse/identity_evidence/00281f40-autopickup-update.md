# AutoPickUpUpdate::update at RVA 0x00281F40

The old `??1AutoPickUpUpdate@@UAE@XZ` naked lift is misidentified and truncated.
The replacement is `?update@AutoPickUpUpdate@@UAE?AW4UpdateSleepTime@@XZ`,
1498 bytes, at the same RVA. Baseline: retail-1.03-unpacked.

## Independent identity evidence

- The matched AutoPickUpUpdate constructor at RVA 0x00281AB0 installs
  VA 0x010BB484 at the update-interface subobject, primary object offset 0x10.
  Its other tables are 0x010BB554 (primary), 0x010BB490 (behavior interface),
  and 0x010BB410 (AutoPickUp interface).
- Slot zero of VA 0x010BB484 is VA 0x00447591. That ILT thunk jumps to
  VA 0x00681F40. Slot one is VA 0x0044985F.
- The surviving Zero Hour `GameLogic/Module/UpdateModule.h` declares
  `UpdateModuleInterface::update()` in slot zero, returning `UpdateSleepTime`;
  `getDisabledTypesToProcess()` occupies slot one. This body returns exactly
  `UPDATE_SLEEP_NONE` (1) and `UPDATE_SLEEP_FOREVER` (0x3fffffff).
- The incoming receiver is the secondary interface: module data is read at
  ECX-0x0c, Object at ECX-8, countdown at ECX+0x14, and wake flag at ECX+0x18.
  These agree with the separately matched constructor's complete-object layout.
- The actual complete destructor is RVA 0x002818B0 (32 bytes), reached through
  ILT 0x000448A0 under `??1AutoPickUpUpdate@@MAE@XZ`. The scalar-deleting
  destructor is RVA 0x00281C50 (30 bytes), through ILT 0x00030783. Both already
  live in AutoPickUpUpdateDestructor.cpp. Neither is this gameplay body.

## Extent

The complete epilogue restores FS:[0] at RVA 0x0028250C, adds 0x8c to ESP at
0x00282513, and returns at 0x00282519. The exclusive end is 0x0028251A,
1498 bytes from the start. INT3 padding separates it from the next aligned
body. The old 1490-byte extent cut the FS restoration instruction and omitted
the rest of the epilogue. The naked lift itself was correspondingly incomplete.

## Behavior and dependencies

The body gates scanning on private status, module flags, countdown, and wake
state; runs five closest-object queries; evaluates 12-byte health/filter entries;
and dispatches special powers or a terrain point. The INI parser already in
AutoPickUpUpdate.cpp independently proves the four-byte filter handle followed
by MyHealth and TargetHealth percentages in each entry.

`callees.py 0x00281F40 1498` resolves all nine distinct direct targets.
No new callee pins are required. Filter tables and global references use existing
ledger identities. The visible mask constructor is independently byte-identical
to RVA 0x000C4B00 (57 bytes), and the one-mask filter constructor to RVA
0x00251980 (61 bytes). Keeping their copying bodies visible recovers the retail
0x80-byte local frame and unwind states 0 through 9.

The completed C++ probes exact over all 1498 bytes with 47 relocation sites.
Scoped add_match/build verification must additionally validate those references.

## Ledger transaction

add_match disallows combining identity correction with an extent correction.
Use its verified replace-existing path first to correct the extent and source,
with `object-symbol=?update@AutoPickUpUpdate@@UAE?AW4UpdateSleepTime@@XZ` naming
the actual compiled symbol. Then use its verified correct-identity path at the
now-correct extent to replace the old ledger name and record its tombstone.
The final row has only the update identity and needs no object-symbol alias.

Model: gpt-6-astra (medium), 2026-09-27.
