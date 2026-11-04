# Eighteen further BFME1 canonical coordinate adoptions

Base `7194ec5b9030eb6ab706c30281eabd491f91b244`. Replace18 data-only Coord3D definitions with the already
registered BFME1 Coord3D header. Native CodeView proves each12-byte struct,
float x/y/z at0/4/8, no methods/statics/bases/vptr. No incompatible older
coord3d.h view or donor layout is imported. No body, field spelling, ABI option,
shared header, identity, ledger, pin, alias, queue or baseline change.

Private views in the checked tree: {'Coord2D': 29, 'Coord3D': 649} -> {'Coord2D': 29, 'Coord3D': 631}. Every source is claimed,
built normally, frozen-checked and accepted through the header lane. Complete
non-debug sections/relocations, 106 external code instances and2
named TU-local code instances remain identical. The only new dependency is
the registered header; every old physical path and native digest is retained.
The21 existing code/EH rows cover4921 ledger-extent bytes; none is new
authored coverage. Two initial transport claim refusals were retried using
HTTP/1.1 before editing those sources; both later acquired proper leases and
passed all checks. The early refusals remain diagnostic history only.

Linking was reviewed first. The aafdf413e9 index and prior tracked
aimove-provider-20261104-0356.md handoff are reused: the OneRing source is
hash/byte unchanged, and the same ScriptActions/owner and vptr-scheduling
prerequisites remain. No unchanged failed body trial is repeated. The BFME2
reference check is still within72h; reviewed RefHandle donor source is
hash-equal. Native target layout proof comes from BFME1's own contract and
compiler, not from a donor name or target-incompatible command ABI.

Current native picker:
```text
link queue #4 (census aafdf413e9; files linked at census aafdf413e9 dropped): ?aiMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z
  wrong_selected; unlocked 1,826 B in 5 file(s) at the census
  fix: the link keeps a non-retail definition: fix or remove the wrong emitter ahead of retail's copy
  files: 5 open: game/GameEngine/Source/GameLogic/Object/Contain/TunnelContain.cpp game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeploySpecialPowerUpdate.cpp game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_internalCancelTask.cpp game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_doRepairLogic.cpp game/GameEngine/Source/GameLogic/Object/Update/WoundArrowUpdateUpdate.cpp
  (2 family stlport, 1 family strings skipped)
```

Scoped dated prediction, not a new census or full-image link:
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
game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorResolveFX.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 719)
  duplicate   ?resolveFX@BridgeBehavior@@IAEXXZ
  selected    ?getDamageToOCLString@TerrainRoadType@@QAE?AVAsciiString@@W4BodyDamageType@@H@Z  (the definition the link keeps is not retail's)
  selected    ?getDamageToSoundString@TerrainRoadType@@QAE?AVAsciiString@@W4BodyDamageType@@@Z  (the definition the link keeps is not retail's)
  selected    ?getRepairedToSoundString@TerrainRoadType@@QAE?AVAsciiString@@W4BodyDamageType@@@Z  (the definition the link keeps is not retail's)
  selected    ?resolveFX@BridgeBehavior@@IAEXXZ  (the definition the link keeps is not retail's)
  selected    ?setEventName@AudioEventRTS@@QAEXVAsciiString@@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorFindClosestOrphan.cpp: LINKS  LINKED 120 -> 120 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 120)
game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_putObjectAtBestGarrisonPoint.cpp: LINKS  LINKED 123 -> 123 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 123)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowPathStateOnExit.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 185)
  unresolved  ?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@HPBDH@Z
  selected    ?onExit@AIFollowPathState@@UAEXW4StateExitType@@@Z  (the definition the link keeps is not retail's)
  selected    ?removeGoal@Pathfinder@@QAEXPAVObject@@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_startFacing.cpp: LINKS  LINKED 154 -> 154 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 154)
game/GameEngine/Source/Common/Rva000E5B30.cpp: LINKS  LINKED 201 -> 201 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 201)
game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva0023BE60NearbyObjectsCheck.cpp: LINKS  LINKED 189 -> 189 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 189)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdAttackStateOnExit.cpp: LINKS  LINKED 138 -> 138 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 138)
game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateXfer.cpp: LINKS  LINKED 134 -> 134 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 134)
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamIdleForFramecount.cpp: LINKS  LINKED 147 -> 147 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 147)
game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006F7150ShroudBounds.cpp: LINKS  LINKED 398 -> 398 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 398)
game/GameEngineDevice/Source/W3DDevice/GameClient/Rva00740440CameraPathAngles.cpp: LINKS  LINKED 347 -> 347 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 347)
game/GameEngine/Source/GameLogic/AI/PathfinderBuildHierarchicalPath.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 275)
  comdat      ?_M_insert_overflow@?$vector@URva003DDF00Element@@V?$allocator@URva003DDF00Element@@@_STL@@@_STL@@IAEXPAURva003DDF00Element@@ABU3@ABU__false_type@2@I_N@Z  (retail: unproven and differs from the kept copy)
  selected    ??0Path@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z  (the definition the link keeps is not retail's)
  selected    ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/Rva00173990State_onEnter.cpp: LINKS  LINKED 101 -> 101 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 101)
game/GameEngine/Source/GameLogic/Object/Update/FireWeaponUpdate.cpp: LINKS  LINKED 131 -> 131 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 131)
game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_isWithinStartAbilityRange.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 696)
  unresolved  ?bfmeDoYR@BfmeSubYR@@QAEDPAX000H@Z
  unresolved  ?bfmeRunEQT@BfmeObjEQT@@QAEDPAX@Z
  comdat      ??1BfmeObjEQT@@UAE@XZ  (first: differs from the first copy in link order (no retail address))
  comdat      ??_GBfmeObjEQT@@UAEPAXI@Z  (first: differs from the first copy in link order (no retail address))
game/GameEngine/Source/GameLogic/AI/AICommandInterfaceFaceCommands.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 625)
  comdat      ?deallocate@?$allocator@UCoord3D@@@_STL@@QAEXPAUCoord3D@@I@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ??1?$_Vector_base@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAE@XZ  (first: differs from the first copy in link order (no retail address))
  selected    ??1?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ??1AICommandParms@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_validateRallyPoint.cpp: LINKS  LINKED 232 -> 232 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 232)
link_check: 13 of 18 link cleanly; LINKED 2,415 -> 2,415 bytes (116.4s)
```

No game run or RAM/leak/crash/FPS/multicore gain is established. The independent
projects verify concurrently; per-repository sources/cache/commits are handled
sequentially, BUILD_POOL14 each. No local model is used.

- [Adopt canonical Coord3D in BridgeBehaviorResolveFX](b1-01-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in SpawnBehaviorFindClosestOrphan](b1-02-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in GarrisonContain_putObjectAtBestGarrisonPoint](b1-03-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in GiantBirdFollowPathStateOnExit](b1-04-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in SpecialAbilityUpdate_startFacing](b1-05-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in Rva000E5B30](b1-06-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in Rva0023BE60NearbyObjectsCheck](b1-07-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in AIGiantBirdAttackStateOnExit](b1-08-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in SlavedUpdateXfer](b1-09-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in ScriptActions_doTeamIdleForFramecount](b1-10-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in Rva006F7150ShroudBounds](b1-11-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in Rva00740440CameraPathAngles](b1-12-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in PathfinderBuildHierarchicalPath](b1-13-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in Rva00173990State_onEnter](b1-14-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in FireWeaponUpdate](b1-15-coordinate-header-20261104-1105.md): 2 retained rows.
- [Adopt canonical Coord3D in SpecialAbilityUpdate_isWithinStartAbilityRange](b1-16-coordinate-header-20261104-1105.md): 1 retained rows.
- [Adopt canonical Coord3D in AICommandInterfaceFaceCommands](b1-17-coordinate-header-20261104-1105.md): 3 retained rows.
- [Adopt canonical Coord3D in GarrisonContain_validateRallyPoint](b1-18-coordinate-header-20261104-1105.md): 1 retained rows.