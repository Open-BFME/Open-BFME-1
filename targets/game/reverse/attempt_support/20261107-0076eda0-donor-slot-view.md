# 0x0076EDA0 (456 B) getBlend / animation frame ranges: EXACT

Best candidate: `build/wf/0076eda0/final.cpp`. It defines
`?getBlend@Rva0076EDA0Holder@@QAEXHPAURva0076EDA0Output@@0@Z`, and probe.py reports
`result EXACT (modulo relocation slots)` at 456/456 B with 4 relocations.
Compiler line (unchanged from the bank, same as landed sibling
`Rva0076C080AdvanceAnimation.cpp`): `/O2 /Ob2 /DNDEBUG /MD` plus the WW3D2/WWMath/WWLib/WWSaveLoad/WWDebug includes.

## Starting point
The bank `targets/game/reverse/attempts/0x0076eda0.cpp` reproduced as logged: 456 B, 10
non-relocation diffs, shape 1.000. The residue was scratch registers in the case-3 else
arm and the case-1 arm (+0xF4/+0xFE/+0x106/+0x108, +0x131/+0x133, +0x14C..+0x161). The bank
also needed an unproven `volatile` on the track's anim pointer. Without it the build was
452 B because the null-test load was CSE'd into ECX.

## What fixed it (donor structure)
Open BFME 2 at dbde7dbe has the same function:
`Code/GameEngine/Source/Common/Rva000B8F5A.cpp`, `W3DScriptedModelDraw::getPlayingAnimationFrameRanges`
(BFME 2 compiles it `/O1 /G7`). The port follows that donor's access structure:
1. The invalid index or null anim path is an early return:
   `first = {0,0}; *second = *first; return;`.
2. The null test and the switch mode go through the indexed array (`entries[i].item`,
   `entries[i].type`). Every other field goes through a per-index slot view,
   `Holder *slot = (Holder *)((char *)this + i*0x1C); slot->entries[0].field`.
   The two expressions do not CSE, so the anim pointer is reloaded before each virtual
   call with no `volatile`. The register rotation then falls out as in retail.
3. The case-3 nested else stores its tail explicitly, with no `goto common`. MSVC
   tail-merges it into the default arm the way retail does.
4. The case-3 else test is spelled `upper < lower` (BFME 1's operand order: `fld +8`,
   `fcomp +4`). The donor's `f04 > f08` puts the `fcomp` inside the direction branch.

## Trials (family / change / result)
- Store order (f): chain `a=b=0` in the tail or in case 3, and swapped store orders in
  cases 1, 3a, 3b and 5. All were worse (14-185 diffs).
- Control flow (a): the five other orders of the case labels. All stayed at 10 diffs;
  the switch normalises case order.
- Donor port (a/b/c), four combinations of mode and direction access (slot or array):
  - mode via slot: 458 B, shape 0.849.
  - mode via array, with the donor's `lower > upper`: 468 B, the `fcomp` moved.
- The same donor port with `upper < lower`: EXACT with direction via either the slot or
  the array. `final.cpp` keeps the donor's spelling, direction via the array.
- Cleaner views (c), with the null test still through `entries[i]`: `Entry *e = &entries[i]`,
  `Entry &e`, an explicit `(Entry*)((char*)this + i*0x1C + 0xD0)`, and
  `(Entry*)((char*)entries + i*sizeof)` all gave 439 B. Plain `entries[i]` everywhere
  gave 452 B. The `this + i*0x1C` holder view is load-bearing.
- Earlier sessions ruled out (from re_attempts.log): rotation_sweep singles and pairs,
  shape_search levers, permute (1142 trials), inline setters, enum mode, a frames
  accessor, a direct `Get_Num_Frames` call, float/int result locals, and `Entry&` with
  `volatile` (430 B).

## Landing notes (read-only checks; nothing landed)
- (a) `ilt_oracle.py check` says CONTRADICTED for this name, the old placeholder, and the
  donor-derived `getPlayingAnimationFrameRanges@W3DModelDraw` spellings tested
  (ILT 0x00034CDE, slot 42437). `symbols.csv` has no pin at 0x34CDE. The name
  `Rva0076EDA0Holder::getBlend` carries the address, so `tools/ilt_oracle.tier` classes it
  as a placeholder and ilt_guard exempts it. Keep this address-derived name. The BFME 2
  name is a lead only.
- (b) COMDAT and helper copies the object emits:
  - `?synchronize@Rva0076CAF0ConditionalDispatch@@QAEXXZ`: the inline guard. It uses the
    same name and body as the landed sibling `AnimationInfo0076EBE0.cpp` and has no
    ledger row. The variant named `dispatchIfStale` is also EXACT, but that name is the
    real out-of-line row at 0x0076CAF0 in `Rva0076CAF0ConditionalDispatch.cpp`. Its emitted
    copy probes EXACT against 0x0076CAF0 (19 B), but defining it inline here would duplicate
    the home TU's non-COMDAT definition. Use `synchronize`, as `final.cpp` does.
  - `??_EWeightInfoStruct@NamedPivotMapClass@@QAEPAXI@Z` comes from `hanim.h` and probes
    EXACT against its row 0x0013A460 (92 B).
  - `??1WeightInfoStruct` (from `hanim.h`) has no row.
  - `getValue` is a file-static inline.
- (c) Globals the body references:
  - VA 0x012F8064 is `?g_rva0075b2e0_value@@3IA` (data_rows, matched). dir32 also lists
    `?g_Va012F8064@@3HA`.
  - VA 0x01075334 (1.0f) is `?g_bfmeDefaultBU@@3MA` in data_rows. The TU emits
    `__real@3f800000`, which the bank's earlier constant check reported as passing.
  - VA 0x01123C58 (0.99999f, `__real@3f7fff58`) has no data row or dir32 name. It was
    verified by value in the earlier evidence note.
  - The immediate -0.00001f (0xB727C5AC) is not a relocation.
- (d) TU: put it in a new unit next to the landed siblings, for example
  `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0076EDA0FrameRanges.cpp`.
  `AnimationInfo0076EBE0.cpp` uses a different include set (no hanim.h).
  Replace the gen_asm row `?d_0076eda0@@YAXXZ` (`game/gen_asm/d_00752a20.asm`).
  Commit with the `[BFME 2 donor]` prefix and cite dbde7dbe Rva000B8F5A.cpp. The evidence
  note `targets/game/reverse/identity_evidence/0x0076eda0-animation-ranges.md` should drop
  its volatile caveat.
