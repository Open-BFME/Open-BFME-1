#18 BFME1 canonical coordinate header adoptions

Base `983dbf9d397be4d14cab999cc7d8cc1ac03ffa7c`. Adopt the existing registered Coord3D header, not the older
incompatible donor coord3d.h. The native compiler verifies each selected
data-only struct: float x/y/z at0/4/8; size12, with no
methods/statics/bases/vptr. Existing BFME1 canonical contracts/headers establish
the chosen layouts. No body, field name, ABI/compiler option, shared header,
identity, ledger, pin, alias or baseline changes.

Private views: {'Coord2D': 29, 'Coord3D': 685} -> {'Coord2D': 29, 'Coord3D': 667}; removed: {'Coord3D': 18}. Each source is claimed,
built normally, frozen-checked and accepted through the header lane. The only
new resolved dependency is its registered header; all old physical paths and
native dependency hashes remain exact. Complete non-debug sections, relocations,
70 external code instances and 3 named TU-local code instances
remain identical. Normal checks retain 20 existing code/EH rows with
3420 ledger-extent bytes; no new native coverage is claimed.

The linking picker was reviewed first. The aiMoveToPosition loser already has
recorded shared-shim/private AICommandParms destructor prerequisites. Current
ScriptActions has the earlier BFME layout repair. Reviewed BFME2 reference
AICommandInterface header/slot evidence does not prove the BFME1 private ABI.
The previous RefHandle donor review is also reused only after its current
source hash is rechecked unchanged; the reference check remains within72h.
No unchanged broad donor scan or failed reconstruction is repeated. This batch
uses BFME1's own contracts, with no donor source port or build-input change.

Current picker, based on dated census evidence:
```text
link queue #4 (census aafdf413e9; files linked at census aafdf413e9 dropped): ?aiMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z
  wrong_selected; unlocked 1,826 B in 5 file(s) at the census
  fix: the link keeps a non-retail definition: fix or remove the wrong emitter ahead of retail's copy
  files: 5 open: game/GameEngine/Source/GameLogic/Object/Contain/TunnelContain.cpp game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeploySpecialPowerUpdate.cpp game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_internalCancelTask.cpp game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_doRepairLogic.cpp game/GameEngine/Source/GameLogic/Object/Update/WoundArrowUpdateUpdate.cpp
  (2 family stlport, 1 family strings skipped)
```

Scoped census-only prediction, not a new census or complete link:
```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_getClosestSlave.cpp: LINKS  LINKED 182 -> 182 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 182)
game/GameEngine/Source/GameLogic/Object/Update/ToppleUpdate_onCollide.cpp: LINKS  LINKED 161 -> 161 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 161)
game/GameEngine/Source/GameLogic/AI/PathfindAdjustDeab0.cpp: LINKS  LINKED 200 -> 200 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 200)
game/GameEngine/Source/GameLogic/Object/Contain/OpenContainGetClosestRider.cpp: LINKS  LINKED 145 -> 145 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 145)
game/GameEngine/Source/GameLogic/AI/Rva00178BC0ComputePath.cpp: LINKS  LINKED 88 -> 88 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 88)
game/GameEngine/Source/GameLogic/AI/Rva00178D90ComputePath.cpp: LINKS  LINKED 88 -> 88 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 88)
game/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdate_animateGridDecals_Thunk.cpp: LINKS  LINKED 259 -> 259 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 259)
game/GameEngine/Source/GameClient/ParticleSystemFXNugget_dtor_Thunk.cpp: LINKS  LINKED 127 -> 127 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 127)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DView_createNamedCamera_rva00741C00.cpp: LINKS  LINKED 195 -> 195 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 195)
game/GameEngine/Source/Common/BfmeConvD820.cpp: LINKS  LINKED 100 -> 100 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 100)
game/GameEngine/Source/GameLogic/AI/BfmeHostEZ_bfmeConsiderEZ.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 167)
  unresolved  ?worldLineNoHit@Pathfinder@@QAE_NPBUCoord3D@@0@Z
  selected    ?slowDoesPathExist@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@1W4ObjectID@@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/PathComputeFlightDistToGoal.cpp: LINKS  LINKED 244 -> 244 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 244)
game/GameEngine/Source/Common/GlobalDataSetTimeOfDay.cpp: LINKS  LINKED 298 -> 298 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 298)
game/GameEngine/Source/GameLogic/AI/AIMoveOntoWallState_onEnter.cpp: LINKS  LINKED 154 -> 154 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 154)
game/GameEngine/Source/GameLogic/AI/Rva0017EC10WeaponStatus.cpp: LINKS  LINKED 120 -> 120 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 120)
game/GameEngine/Source/GameLogic/AI/PathfinderCheckForTargetBfme.cpp: LINKS  LINKED 170 -> 170 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 170)
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptAction_duplicate.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 609)
  duplicate   ?duplicate@ScriptAction@@QBEPAV1@XZ
  comdat      ??_7ScriptAction@@6B@  (retail: unproven and differs from the kept copy)
  comdat      ??4Parameter@@QAEAAV0@ABV0@@Z  (retail: not retail's body)
  selected    ??4Parameter@@QAEAAV0@ABV0@@Z  (the definition the link keeps is not retail's)
  selected    ?duplicate@ScriptAction@@QBEPAV1@XZ  (the definition the link keeps is not retail's)
  selected    ?setActionType@ScriptAction@@QAEXW4ScriptActionType@1@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/Rva00173900AIMoveToStateSA_update.cpp: LINKS  LINKED 111 -> 111 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 111)
link_check: 16 of 18 link cleanly; LINKED 2,642 -> 2,642 bytes (221.1s)
```

No game run or RAM/leak/crash/FPS/multicore gain is established. Independent
projects verify concurrently; per-project source/cache/commit operations remain
sequential, BUILD_POOL14 each. No local model is used.

- [Adopt canonical Coord3D in SpawnBehavior_getClosestSlave](b1-01-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in ToppleUpdate_onCollide](b1-02-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in PathfindAdjustDeab0](b1-03-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in OpenContainGetClosestRider](b1-04-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva00178BC0ComputePath](b1-05-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva00178D90ComputePath](b1-06-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in DynamicShroudClearingRangeUpdate_animateGridDecals_Thunk](b1-07-coordinate-header-20261104-0110.md): 2 existing rows.
- [Adopt canonical Coord3D in ParticleSystemFXNugget_dtor_Thunk](b1-08-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in W3DView_createNamedCamera_rva00741C00](b1-09-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in BfmeConvD820](b1-10-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in BfmeHostEZ_bfmeConsiderEZ](b1-11-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in PathComputeFlightDistToGoal](b1-12-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in GlobalDataSetTimeOfDay](b1-13-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in AIMoveOntoWallState_onEnter](b1-14-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva0017EC10WeaponStatus](b1-15-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in PathfinderCheckForTargetBfme](b1-16-coordinate-header-20261104-0110.md): 1 existing rows.
- [Adopt canonical Coord3D in ScriptAction_duplicate](b1-17-coordinate-header-20261104-0110.md): 2 existing rows.
- [Adopt canonical Coord3D in Rva00173900AIMoveToStateSA_update](b1-18-coordinate-header-20261104-0110.md): 1 existing rows.