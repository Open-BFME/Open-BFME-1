# 0x001827C0 AIAttackApproachTargetState::updateInternal (1398 B): EXACT

Symbol: `?updateInternal@AIAttackApproachTargetState@@AAE?AW4StateReturnType@@XZ`.
Bank `targets/game/reverse/attempts/0x001827c0.cpp` (0.9957) reproduced at 1398 B, 52 relocs,
6 non-reloc diffs in the direction copy at +0x100..+0x112.

Best candidate: `build/wf/001827c0/final.cpp` (landing-shaped). The minimal diagnostic form is
`best.cpp`. Both are EXACT at 1398 B under `// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath`.
They are also EXACT with the AIStates.cpp sibling switches `/DNDEBUG /DWIN32 /MD /EHsc` (`best_eh.cpp`).

## Root cause (measured)

Retail copies the facing vector as `edx=[eax]; ecx=[eax+4]; st x; edx=[eax+8]; st y; ecx=esi; st z`.
This is VC7.1's two-register block copy, with the load of y scheduled above the store of x.
- Every natural copy (copy-init, assignment, copy ctor, memcpy, POD block copy) emits the same
  registers in sequential order: load/store, load/store. Earlier logs reported "retail copy
  regs but ESI/EDI flip". The flip is a separate effect, and those copies were sequential as well.
- Diagnostic x4 calls `Scale` on `target` instead of `direction`. The copy then interleaves
  (1 diff). So the hoist is blocked only because `direction`'s address escapes as `this` of the
  opaque out-of-line `Coord3D::Scale`.
- **Lever:** make the inline body of `Coord3D::Scale` visible in the TU:
  `inline Coord3D &Coord3D::Scale(float s){x*=s;y*=s;z*=s;return *this;}`.
  VC7.1 still calls it here; it is not inlined. The copy then interleaves exactly as in retail.
  The out-of-line definition (y1), `inline` (y2) and noinline (y3) are all EXACT. The emitted
  COMDAT is retail-identical to the ledger row `?Scale@Coord3D@@QAEAAV1@M@Z` 0x0014FFD0
  ("inline header member emitted as pick-any COMDAT"; AIFearState_onEnter.cpp defines it the
  same way).
- Second lever (ESI/EDI, source vs victim): in the natural-copy form, the range-check delta must
  read the source position through a named local:
  `const Coord3D *sourcePos=source->getPosition(); delta.x-=sourcePos->x; ...`.
  Applying it to the first delta, the second delta, both, or as a reference all fix the
  allocation. Without it the natural-copy form is 50 diffs (z1).
- With both levers, the bank's `Pathfinder *const pf` / `const Coord3D &pos` receiver hack in
  the no-victim branch is unnecessary (y4 EXACT without it).

## Trials (all on the natural direction copy unless noted)

| family | change | result |
|---|---|---|
| copy form | copy-init / assign / copy-ctor / named facing ptr | 64 (ESI/EDI flip, sequential copy) |
| copy form | memcpy, W3 dword struct, F3 float struct block copy | 64; with sourcePos 14 (sequential) |
| lifetime | victimPos local (early) | 1402 B / 1025 |
| lifetime | victimPos local (before viewBlocked) | 64 |
| lifetime | sourcePos local in either or both deltas (pointer or ref) | 14 (regs fixed, copy sequential) |
| lifetime | inline `delta.Sub()` | 1384 B |
| order | melee/inRange decl swap | 75 / 25 |
| misc | code decl, deltaci, dist, height local, inRange!=0, viewBlocked split, rva5c ctor, pf2 | unchanged 64 / 14 |
| misc | moved field-wise subtract | 1404 B |
| misc | target += spelled field-wise | 70 / 20 |
| flags | flag_sweep (O1/O2/Ox x Ob0-2 x G5/G6/G7/GB x Oy-) on bank and sourcePos form | best stays 6 / 14 |
| callee visibility | **inline Coord3D::Scale body visible** + sourcePos | **EXACT** |

## Landing notes (read-only checks done)

(a) `tools/ilt_oracle.py check` reports CONFIRMED, p_false=8.48e-04 (exact). Use the existing name.

(b) The TU emits these helper COMDATs, each probed against its own ledger row, and all are
retail-identical:
- `?Scale@Coord3D@@QAEAAV1@M@Z` at 0x0014FFD0 (33 B): EXACT.
- `??0Coord3D@@QAE@ABV0@@Z` at 0x0005BC20 (25 B): EXACT.
- `??1Coord3D@@QAE@XZ` at 0x0005BC40 (1 B): EXACT.
- `??YCoord3D@@QAEAAV0@ABUCoord3DBase@@@Z` at 0x00148730 (33 B): EXACT.
- `?getPosition@Object@@QBEPBVCoord3D@@XZ` and `?pathfinder@AI@@QAEPAVPathfinder@@XZ` have no
  ledger rows. They are inline accessors and are inlined at every use.

Call binding in final.cpp:
- These calls use existing names:
  - Ledger rows with ILT columns: Scale (0xE1C4), Sub (0x179EF), length (0x2FE0F), lengthSqr
    (0x20662), and `?update@AIInternalMoveToState@@UAE` (0x488F6). For `update` the
    declaration was made virtual in vtable slot +0x18 so that it mangles UAE.
  - symbols.csv pins: getGoalObject (0xE570), isGoalObjectDestroyed (0x432C), getCurrentWeapon
    (0x31A7F), getControllingPlayer (0x20824), bfmeMeleeHordeTargetInvalid (0x2056D),
    bfmeGetNonnegativePreferredLocomotorHeight (0x47C8), and `_bfmeRetailCritterDesyncLog`
    (0x3A17A).
- The typed pins for Coord3D-parameter callees are keyed `struct` (`PBUCoord3D`). This TU's
  WWMath `class Coord3D` mangles them as `PBVCoord3D`. Those calls therefore go through their
  ledger ILT names (`?j_XXXXXXXX@@YAXXZ`) with the `CALL` member-pointer macro, the same as the
  bank and the AIAttackApproachTargetState_onEnter.cpp / computePath_Bfme.cpp siblings:
  - 0x4AB4C setCurrentVictim
  - 0x40246 getUnitDirectionVector2D
  - 0x3A4E5 isGoalPosWithinAttackRange
  - 0x2E85C / 0x2E951 isWithinAttackRange
  - 0x23042 isAttackViewBlockedByObstacle (x2)
  - 0x18EB2 isQuickPathAvailable
  - 0x2FAEA getCurrentStateID
  - 0x296A9 getTeamTargetObject
  - 0x32B46 Pathfinder approach check

  The candidate stays EXACT with this binding. No new pins are needed.
- The Coord3D class-key conflict (WWMath `class` versus canonical/contract `struct`) blocks
  the typed spellings. Lib/Coord3D.h has no Scale member, and the lever needs Scale's body
  visible as a Coord3D member.

(c) Globals, by recorded name:
- `?TheAI@@3PAVAI@@A` at 0x012EF214 (dir32).
- `?TheGameLogic@@3PAVGameLogic@@A` at 0x012F0898 (dir32 and data_rows).
- `?TheCRCParameterCheck@@3PAVCRCParameterCheck@@A` at 0x012ED4FC.
- `__real@40800000` at 0x01075340, `__real@00000000` at 0x01075350 and `__real@42c80000` at
  0x0107FAC4 (dir32).
- Two string literals ("%i AIAttackApproachTargetState success [3]" at 0x0109B078 and
  "masiwar called by AIAttackApproachTargetState::updateInternal [2]" at 0x0109B028) have no
  dir32 row. Check whether the gate requires one.

(d) Home TU: the row currently points at the naked MASM lift in
`game/GameEngine/Source/GameLogic/AI/AIStates.cpp` (line ~2605). That TU builds against ZH
headers (`struct Coord3D` without Scale), and the sibling AIAttackApproachTargetState_*.cpp
files use Lib/Coord3D.h. Recommended: a new
`game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetState_updateInternal.cpp`
(WWMath coord3d.h + inline Scale, the same pattern as AIFearState_onEnter.cpp). Land it with
`add_match --replace-existing` and delete the naked function from AIStates.cpp.

Donor: BFME 2 2bac16a65 `Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp`
`AIAttackApproachTargetState::updateInternal` confirmed the control flow and the
`ApproachCoord` copy/Scale idea. Its inlined Scale shrinks the BFME 1 body (prior log), so BFME 1
needs the visible but not-inlined member instead.
