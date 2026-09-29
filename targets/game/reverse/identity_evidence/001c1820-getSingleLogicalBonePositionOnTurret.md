# 0x001C1820 identity: Object::getSingleLogicalBonePositionOnTurret

`?getSingleLogicalBonePositionOnTurret@Object@@QBE_NW4WhichTurretType@@PBDPAUCoord3D@@PAVMatrix3D@@@Z`
is the correct name for the 1008-byte body at RVA 0x001C1820. The lift file
`game/GameEngine/Source/GameLogic/Object/ObjectGetSingleLogicalBonePositionOnTurretThunk.cpp`
carried the name already; these are the independent checks behind it.

## Matched caller names the symbol

`python3 tools/callers_of.py 0x001C1820` prints exactly one retail caller:

    0x00603fe0 ?initLaser@LaserUpdate@@QAEXPBVObject@@PBUCoord3D@@1H@Z

That row is `matched` in `targets/game/reverse/functions.csv` from real source
(`game/GameEngine/Source/GameLogic/Object/Update/LaserUpdate_initLaser.cpp`,
776 B) and its own notes record the identity chain from pinned ILT 0x00024FC3.
A matched caller that spells the symbol is the strongest evidence available and
it agrees with the lift name, so no address-derived name is needed.

A second retail call site (OpenContain, `getObject()->getSingleLogicalBonePositionOnTurret(TURRET_MAIN, ...)`)
exists in the same upstream source, but its owning body is still a naked
`__emit` lift, so it carries no independent weight.

## Arity and body agreement

* `targets/game/reverse/lift_arity.csv` records 4 stack args for this lift,
  matching `WhichTurretType, const char*, Coord3D*, Matrix3D*`.
* The body's tail is `ret 16` (`c2 10 00`), retail-correct for four `Real`-sized
  4-byte stack arguments popped by the callee.
* `tools/inferred_protos.csv` reads the body as `__thiscall, 4 stack slot(s),
  returns a value [eax read at 1/2 sites]`; the `Bool` return is produced by
  `xor al,al` / `mov al,1` on the two exits.

## Zero Hour twin

`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h:568`
declares the method with the identical signature, and the GeneralsMD source body
at `.../Source/GameLogic/Object/Object.cpp:6033` is the source the readable TU
compiles. `ea_evidence.csv:5001` records the same file
(`GameEngine/Source/GameLogic/Object/Object.cpp`, `zh`).

## Callee identity: nothing unresolved

`python3 tools/callees.py 0x001C1820 1008` lists four distinct call targets and
`--unpinned-only` reports 0 unnamed. Each is a 5-byte ILT thunk with a pinned,
matched body:

| thunk RVA | target | ledger name | pin |
|---|---|---|---|
| 0x00002243 | 0x00132530 (468 B, matched) | `?convertBonePosToWorldPos@Thing@@QBEXPBUCoord3D@@PBVMatrix3D@@PAU2@PAV3@@Z` | `?convertBonePosToWorldPos@Object@@...` -> 0x00002243, `pin_consistency`: consistent |
| 0x0000460B | 0x0026EAF0 (61 B, matched) | `?getTurretRotAndPitch@AIUpdateInterface@@QBE_NW4WhichTurretType@@PAM1@Z` | resolved by matched row |
| 0x00009601 | 0x0041B9C0 (196 B, matched) | `?getProjectileLaunchOffset@Drawable@@QBE_NW4WeaponSlotType@@HPAVMatrix3D@@W4WhichTurretType@@PAUCoord3D@@3@Z` | resolved by matched row |
| 0x0002319B | 0x00413850 (175 B, matched) | `?getPristineBonePositions@Drawable@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@HH@Z` | `?getPristineBonePositions@BFMEDrawableBoneQuery@@...` -> 0x0002319B, `pin_consistency`: consistent |

A full `./build.sh` scoped to the readable TU linked and byte-compiled all 196
functions in it: 195 pass, this one fails on 8 bytes. No unresolved or unpinned
callee is reported at any stage, so the "typed callee names without pins" theory
that motivated the callee-identity assignment is disproved. See
`re_attempts.log` for the 2026-09-29 blocked verdict.

The remaining 8 bytes are the x87 operand schedule in the second
`turnAdjustment.Translate(...)` row 0 (`+01a7`), blocker family `float`.
