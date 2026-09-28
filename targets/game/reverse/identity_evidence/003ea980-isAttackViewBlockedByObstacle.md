# 0x003EA980 -- ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z

The lift name is confirmed, not assumed. Nothing is renamed.

## Chain of evidence

1. **ILT thunk 0x00023042 is a bare jump to this body.**

   `python3 tools/dis_retail.py 0x00023042 5`

   ```
   ; ?j_00023042@@YAXXZ rva=0x00023042 size=5
   +0000 e9 39 79 3c 00           jmp     0x7ea980
   ```

   0x7EA980 - 0x400000 = 0x003EA980, the 501-byte body in question. A 5-byte
   ILT thunk with no argument shuffling is a thiscall member thunk, so the
   target is the real body of a member function -- not a static helper, not a
   jump stub.

2. **Two matched sibling bodies in the same class declare and call this exact
   four-argument signature.** `functions.csv` rows 61112 and 61114, both
   `matched` against clean C++ in
   `game/GameEngine/Source/GameLogic/AI/PathfinderAttackViewForwarders.cpp`:

   - 0x003EE730 `?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@0@Z`, 52 B
   - 0x003EE780 `?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@PBUCoord3D@@@Z`, 24 B

   Both bodies end in a call whose argument list is
   `(const Object *source, const Coord3D &sourcePosition, const Object *target, const Coord3D &targetPosition)`
   -- a 16-byte `ret 0x10`, which is the `this` pointer plus three pointers and
   two references, and the exact parameter shape this body reads from
   `[esp+0x34]`, `[esp+0x38]`, `[esp+0x3c]`, `[esp+0x40]` at +0x001e onward.
   A matched caller naming the symbol is the strongest evidence available, and
   there are two.

3. **Named retail callers exist and agree.** `python3 tools/callees.py`-style
   xref inventory gives 12 call sites, all through ILT thunks, including
   `?updateInternal@AIAttackApproachTargetState@@AAE?AW4StateRet...` in
   `AIStates.cpp` (x2) and `?Rva0016AEE0WeaponRangePosition@@YA_NPAVState@@PAX@Z`.
   The attack-state machine is the only thing in the game that asks "can this
   attacker see that target", which is what the name says.

4. **The EA label chain agrees.** `Pathfinder::IsAttackViewBlockedByObstacle`,
   EA source file `GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp`.
   BFME2's rename of some members does not touch this one.

5. **The body shape matches the name.** Return type `bool` (`xor al,al` on the
   two false exits, `mov al,1` on the two true exits), four arguments
   (`ret 0x10`), non-static (`mov ecx, ...` from the incoming stack slot), and
   no vtable slot. Nothing in the body contradicts arity, return type or
   dispatch.

## What the body does (why the BFME body is not the Zero Hour body)

`game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp` carries a source-level
`Bool Pathfinder::isAttackViewBlockedByObstacle(...)` under the same name, but
it is the **Zero Hour twin**, and it cannot be this body:

- `AIData::m_attackUsesLineOfSight` is read at `+0x67` in retail 0x003EA980;
  AIPathfind.cpp's `AI.h` layout puts it at `+0x6b` (probe evidence line
  `+000e`). Moving it would move every sibling body already matched under that
  header.
- ZH tests the attacker's kind through `Thing::isKindOf(KINDOF_ATTACK_NEEDS_LINE_OF_SIGHT)`.
  BFME instead walks the final template override and tests
  `m_kindOfFlags & 0x04000000` at `+0x00CC`.
- BFME takes the weapon from `AssistedTargetingObjectShim::find(0)`; ZH uses
  `Object::getCurrentWeapon()`.
- BFME has the two `TerrainLogic::getLayerForDestination` queries and the bare
  `fcomp` elevation comparison that decides whether a bridge answers for the
  ground under it. ZH has neither.
- Probe on AIPathfind.cpp: **261 bytes vs 501 retail, 194 non-reloc diffs**,
  shape 0.480. Not a spelling difference; a different function.

So the real body is a separate TU with the BFME layouts spelled privately.
Every offset it reads is witnessed elsewhere in the tree:

| offset | meaning | witness |
|---|---|---|
| +0x04 | `Object::m_template` | AIWanderState_update_Bfme.cpp:90 |
| +0x04 | `BfmeThingTemplate::m_nextOverride` | AIWanderState_update_Bfme.cpp:90 |
| +0xCC | `BfmeThingTemplate::m_kindOfFlags` | AIWanderState_update_Bfme.cpp:96 |
| +0x67 | `AIData::m_attackUsesLineOfSight` | retail 0x003EA980 itself |
| seven fields | `ObstacleCellStruct` | PathfindObstacleCallbackDebb0.cpp:114 |
| +0x38 | `Object` cached position | PathfinderAttackViewForwarders.cpp (4 bodies) |

## Landing

- Source: `game/GameEngine/Source/GameLogic/AI/PathfinderIsAttackViewBlockedByObstacle.cpp`
- Probe result: `EXACT (modulo relocation slots)`, 501/501 bytes, 16 relocations
- All 16 relocation slots accounted for: 9 distinct retail call targets
  (1+1+1+1+1+4+2+1+1 calls) plus `?TheAI` x1 and `?TheTerrainLogic` x2.
- The naked `__emit` lift
  `game/GameEngine/Source/GameLogic/Pathfinder/Pathfinder_isAttackViewBlockedByObstacle_Thunk.cpp`
  held this body and nothing else, so it is deleted with the landing.
