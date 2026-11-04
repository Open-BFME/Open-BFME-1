#18 BFME1 canonical coordinate header adoptions

Base `eb147825e10bda16ec648c86be5f7b794fe7791b`. Adopt the existing registered Coord3D header, not the older
incompatible donor coord3d.h. The native compiler verifies each selected
data-only struct: float x/y/z at0/4/8; size12, with no
methods/statics/bases/vptr. Existing BFME1 canonical contracts/headers establish
the chosen layouts. No body, field name, ABI/compiler option, shared header,
identity, ledger, pin, alias or baseline changes.

Private views: {'Coord2D': 29, 'Coord3D': 667} -> {'Coord2D': 29, 'Coord3D': 649}; removed: {'Coord3D': 18}. Each source is claimed,
built normally, frozen-checked and accepted through the header lane. The only
new resolved dependency is its registered header; all old physical paths and
native dependency hashes remain exact. Complete non-debug sections, relocations,
87 external code instances and 6 named TU-local code instances
remain identical. Normal checks retain 20 existing code/EH rows with
3565 ledger-extent bytes; no new native coverage is claimed.

The linking picker was reviewed first. The official aafdf413e9 index was
fetched successfully. Its additional wrong OneRing provider was investigated
in isolated compiler experiments; the unchanged production caller remains
verified. The new tracked aimove-provider-20261104-0356.md handoff records
the tested boundaries and remaining terrain-vptr scheduling/owner prerequisite.
That investigation is not counted as a completed source task.
The aiMoveToPosition family retains its recorded shared-shim/private ABI prerequisites. Current
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
game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdate_getNaturalRallyPoint.cpp: LINKS  LINKED 492 -> 492 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 492)
game/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdateXfer.cpp: LINKS  LINKED 138 -> 138 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 138)
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsDoTeamRadarCreateEventThunk.cpp: LINKS  LINKED 95 -> 95 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 95)
game/GameEngine/Source/GameLogic/AI/AIMoveAndTightenState_onEnter_Thunk.cpp: LINKS  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 0)
game/GameEngine/Source/GameLogic/Object/Rva001C0010GeometryPosition.cpp: LINKS  LINKED 287 -> 287 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 287)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowWaypointPathStateOnExit.cpp: LINKS  LINKED 172 -> 172 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 172)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceWaypointGoalPathSize.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 77)
  duplicate   ?getAIStateType@AIUpdateInterface@@QBE?AW4AIStateType@@XZ
game/GameEngine/Source/Common/System/GeometryParseActiveAndOffset.cpp: LINKS  LINKED 125 -> 125 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 125)
game/GameEngine/Source/GameLogic/AI/AIMoveToPositionAndEnterState_onEnter.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 146)
  selected    ?setDesiredSpeed@AIUpdateInterface@@QAEXM@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/PathfinderIsCheckForAdjust003F2B60.cpp: LINKS  LINKED 355 -> 355 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 355)
game/GameEngine/Source/GameLogic/AI/AITNGuard_findBestTunnel_Bfme.cpp: LINKS  LINKED 134 -> 134 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 134)
game/GameEngine/Source/GameLogic/Object/Weapon_rva001F01D0.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 82)
  selected    ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doRevealMapAtWaypoint.cpp: LINKS  LINKED 99 -> 99 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 99)
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsTeamDistanceRva00325970.cpp: LINKS  LINKED 466 -> 466 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 466)
game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FD180MouseWorldToScreen.cpp: LINKS  LINKED 277 -> 277 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 277)
game/GameEngine/Source/GameLogic/AI/Rva00170460AIStateMachine_clear.cpp: LINKS  LINKED 90 -> 90 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 90)
game/GameEngine/Source/GameLogic/ScriptEngine/Rva002FEE90SiegeDockSearch.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 446)
  unresolved  ?getPlayerMask@PartitionFilter@@UAEHXZ
  comdat      ?apply@Rva002FEE90ScriptActions@@QAEXABVAsciiString@@PAURva002FEE90Parameter@@1@Z  (retail: not retail's body)
  selected    ??0PartitionFilterAcceptByKindOf@@QAE@ABV?$BitFlags@$0MA@@@0@Z  (the definition the link keeps is not retail's)
  selected    ??_7PartitionFilter@@6B@  (the definition the link keeps is not retail's)
  selected    ?apply@Rva002FEE90ScriptActions@@QAEXABVAsciiString@@PAURva002FEE90Parameter@@1@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameClient/MessageStream/GUICommandTranslator_doPlaceBeacon.cpp: LINKS  LINKED 70 -> 70 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 70)
link_check: 14 of 18 link cleanly; LINKED 2,800 -> 2,800 bytes (120.8s)
```

No game run or RAM/leak/crash/FPS/multicore gain is established. Independent
projects verify concurrently; per-project source/cache/commit operations remain
sequential, BUILD_POOL14 each. No local model is used.

- [Adopt canonical Coord3D in DefaultProductionExitUpdate_getNaturalRallyPoint](b1-01-coordinate-header-20261104-0356.md): 2 existing rows.
- [Adopt canonical Coord3D in RubbleRiseUpdateXfer](b1-02-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in ScriptActionsDoTeamRadarCreateEventThunk](b1-03-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in AIMoveAndTightenState_onEnter_Thunk](b1-04-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva001C0010GeometryPosition](b1-05-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in GiantBirdFollowWaypointPathStateOnExit](b1-06-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in AIUpdateInterfaceWaypointGoalPathSize](b1-07-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in GeometryParseActiveAndOffset](b1-08-coordinate-header-20261104-0356.md): 2 existing rows.
- [Adopt canonical Coord3D in AIMoveToPositionAndEnterState_onEnter](b1-09-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in PathfinderIsCheckForAdjust003F2B60](b1-10-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in AITNGuard_findBestTunnel_Bfme](b1-11-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in Weapon_rva001F01D0](b1-12-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in ScriptActions_doRevealMapAtWaypoint](b1-13-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in ScriptConditionsTeamDistanceRva00325970](b1-14-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva006FD180MouseWorldToScreen](b1-15-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva00170460AIStateMachine_clear](b1-16-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva002FEE90SiegeDockSearch](b1-17-coordinate-header-20261104-0356.md): 1 existing rows.
- [Adopt canonical Coord3D in GUICommandTranslator_doPlaceBeacon](b1-18-coordinate-header-20261104-0356.md): 1 existing rows.