#18 BFME1 canonical coordinate header adoptions

Base `aae40ac4728e23d2b8b4aeb3742ee899031cb719`. Adopt existing registered Coord2D/Coord3D headers, not the older
incompatible donor coord3d.h. The native compiler verifies each selected
data-only struct: float x/y at0/4 and, for Coord3D, z at8; sizes8/12, with no
methods/statics/bases/vptr. Existing BFME1 canonical contracts/headers establish
the chosen layouts. No body, field name, ABI/compiler option, shared header,
identity, ledger, pin, alias or baseline changes.

Private views: {'Coord2D': 31, 'Coord3D': 701} -> {'Coord2D': 29, 'Coord3D': 685}; removed: {'Coord2D': 2, 'Coord3D': 16}. Each source is claimed,
built normally, frozen-checked and accepted through the header lane. The only
new resolved dependency is its registered header; all old physical paths and
native dependency hashes remain exact. Complete non-debug sections, relocations,
88 external code instances and 3 named TU-local code instances
remain identical. Normal checks retain 20 existing code/EH rows with
4467 ledger-extent bytes; no new native coverage is claimed.

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
game/GameEngine/Source/GameLogic/AI/AIFollowWaypointPathState_onEnter.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 621)
  unresolved  ?TheCRCParameterCheck@@3PAXA
  unresolved  ?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@HPBDH@Z
  duplicate   ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
  selected    ?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ  (the definition the link keeps is not retail's)
  selected    ?setDesiredSpeed@AIUpdateInterface@@QAEXM@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/AIPlayerComputeSuperweaponTarget.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,434)
  unresolved  ?isSignificantlyAboveTerrain@Object@@QBE_NXZ
  duplicate   ?computeSuperweaponTarget@AIPlayer@@UAE_NPBVSpecialPowerTemplate@@PAUCoord3D@@HM@Z
  duplicate   ?getPlayerSuperweaponValue@AIPlayer@@KAHPAUCoord3D@@HM@Z
  selected    ?computeSuperweaponTarget@AIPlayer@@UAE_NPBVSpecialPowerTemplate@@PAUCoord3D@@HM@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/Common/RTS/PlayerFindClosestByObject.cpp: LINKS  LINKED 185 -> 185 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 185)
game/GameEngine/Source/GameLogic/AI/PathfinderSnapPosition.cpp: LINKS  LINKED 149 -> 149 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 149)
game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FD2E0CursorClamp.cpp: LINKS  LINKED 174 -> 174 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 174)
game/GameEngine/Source/GameLogic/System/GameLogicValidateBeaconPosition.cpp: LINKS  LINKED 157 -> 157 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 157)
game/GameEngine/Source/GameLogic/Map/TerrainLogicNewMap.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 58)
  comdat      ?rva001ADF10@TerrainLogic@@AAEXXZ  (retail: not retail's body)
  selected    ?rva001ADF10@TerrainLogic@@AAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Pathfinder/PathfinderChooseBestLocomotor.cpp: LINKS  LINKED 143 -> 143 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 143)
game/GameEngine/Source/GameLogic/System/BfmeCellRva001DE2A0.cpp: LINKS  LINKED 189 -> 189 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 189)
game/GameEngine/Source/GameLogic/AI/PathUpdateLastNode.cpp: LINKS  LINKED 108 -> 108 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 108)
game/GameEngine/Source/GameLogic/Object/Weapon_isSourceObjectWithGoalPositionWithinAttackRange.cpp: LINKS  LINKED 188 -> 188 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 188)
game/GameEngine/Source/GameLogic/AI/PathfindLayer_bfmeContainsPoint.cpp: LINKS  LINKED 119 -> 119 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 119)
game/GameEngine/Source/GameLogic/AI/PathfindTightenCallback.cpp: LINKS  LINKED 127 -> 127 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 127)
game/GameEngine/Source/Common/Rva003A2270Find.cpp: LINKS  LINKED 185 -> 185 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 185)
game/GameEngine/Source/GameClient/MapObjectWriteObjectsDataChunk.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 194)
  unresolved  ?writeDict@DataChunkOutput@@QAEXABVDict@@@Z
game/GameEngine/Source/GameLogic/System/BfmeCellGridRva001B1AD0.cpp: LINKS  LINKED 238 -> 238 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 238)
game/GameEngine/Source/GameLogic/AI/AIPickUpCrateState_computePath.cpp: LINKS  LINKED 101 -> 101 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 101)
game/GameEngine/Source/GameLogic/AI/Rva00178E30ComputePath.cpp: LINKS  LINKED 88 -> 88 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 88)
link_check: 14 of 18 link cleanly; LINKED 2,151 -> 2,151 bytes (118.7s)
```

No game run or RAM/leak/crash/FPS/multicore gain is established. Independent
projects verify concurrently; per-project source/cache/commit operations remain
sequential, BUILD_POOL14 each. No local model is used.

- [Adopt canonical Coord2D in AIFollowWaypointPathState_onEnter](b1-01-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord2D in AIPlayerComputeSuperweaponTarget](b1-02-coordinate-header-20261103-1638.md): 2 existing rows.
- [Adopt canonical Coord3D in PlayerFindClosestByObject](b1-03-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in PathfinderSnapPosition](b1-04-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva006FD2E0CursorClamp](b1-05-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in GameLogicValidateBeaconPosition](b1-06-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in TerrainLogicNewMap](b1-07-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in PathfinderChooseBestLocomotor](b1-08-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in BfmeCellRva001DE2A0](b1-09-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in PathUpdateLastNode](b1-10-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in Weapon_isSourceObjectWithGoalPositionWithinAttackRange](b1-11-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in PathfindLayer_bfmeContainsPoint](b1-12-coordinate-header-20261103-1638.md): 2 existing rows.
- [Adopt canonical Coord3D in PathfindTightenCallback](b1-13-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva003A2270Find](b1-14-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in MapObjectWriteObjectsDataChunk](b1-15-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in BfmeCellGridRva001B1AD0](b1-16-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in AIPickUpCrateState_computePath](b1-17-coordinate-header-20261103-1638.md): 1 existing rows.
- [Adopt canonical Coord3D in Rva00178E30ComputePath](b1-18-coordinate-header-20261103-1638.md): 1 existing rows.