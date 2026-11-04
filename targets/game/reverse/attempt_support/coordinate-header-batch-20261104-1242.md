# Twenty further BFME1 canonical coordinate adoptions

Base `7dc725a773984003b76bf5d45a457f34eb79afd0`. Replace20 data-only Coord3D definitions with the already
registered BFME1 Coord3D header. Native CodeView proves each12-byte struct,
float x/y/z at0/4/8, no methods/statics/bases/vptr. No incompatible older
coord3d.h view or donor layout is imported. No body, field spelling, ABI option,
shared header, identity, ledger, pin, alias, queue or baseline change.

Private views in the checked tree: {'Coord2D': 29, 'Coord3D': 631} -> {'Coord2D': 29, 'Coord3D': 611}. Every source is claimed,
built normally, frozen-checked and accepted through the header lane. Complete
non-debug sections/relocations, 126 external code instances and1
named TU-local code instances remain identical. The only new dependency is
the registered header; every old physical path and native digest is retained.
The23 existing code/EH rows cover4712 ledger-extent bytes; none is new
authored coverage. HTTP/1.1 is used for coordination and publication. Every admitted source has
its own recorded native claim lease before editing.

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
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
game/GameEngine/Source/GameLogic/Object/Contain/OpenContainGetNaturalRallyPoint.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 201)
  duplicate   ?getNaturalRallyPoint@OpenContain@@UBE_NAAUCoord3D@@_N@Z
  comdat      ??1AsciiString@@QAE@XZ  (retail: not retail's body)
  comdat      ?concat@AsciiString@@QAEXPBDH@Z  (retail: not retail's body)
  comdat      ?getNaturalRallyPoint@OpenContain@@UBE_NAAUCoord3D@@_N@Z  (retail: not retail's body)
  selected    ?concat@AsciiString@@QAEXPBDH@Z  (the definition the link keeps is not retail's)
  selected    ?getNaturalRallyPoint@OpenContain@@UBE_NAAUCoord3D@@_N@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/ScriptEngine/Condition_duplicate.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 597)
  comdat      ??_7Condition@@6B@  (retail: unproven and differs from the kept copy)
  comdat      ??4Parameter@@QAEAAV0@ABV0@@Z  (retail: not retail's body)
  selected    ??4Parameter@@QAEAAV0@ABV0@@Z  (the definition the link keeps is not retail's)
  selected    ?setConditionType@Condition@@QAEXW4ConditionType@1@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/ScriptEngine/Parameter_WriteParameter_Thunk.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 162)
  duplicate   ?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z
  selected    ?WriteParameter@Parameter@@QAEXAAVDataChunkOutput@@@Z  (the definition the link keeps is not retail's)
  selected    ?set@AsciiString@@QAEXPBDH@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameClient/ParticleSystemFXNuggetConstructor.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 346)
  duplicate   ??0ParticleSystemFXNugget@@QAE@XZ
  comdat      ?clear@AsciiString@@QAEXXZ  (retail: not retail's body)
  selected    ??0FXNugget@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ??0ParticleSystemFXNugget@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ??_7ParticleSystemFXNugget@@6B@  (the definition the link keeps is not retail's)
  selected    ?clear@AsciiString@@QAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorBodyState.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 537)
  duplicate   ?onBodyDamageStateChange@BridgeBehavior@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z
  selected    ?onBodyDamageStateChange@BridgeBehavior@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z  (the definition the link keeps is not retail's)
  selected    ?resolveFX@BridgeBehavior@@IAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowPathState_update.cpp: LINKS  LINKED 260 -> 260 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 260)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetZoomToDefaultBfme.cpp: LINKS  LINKED 228 -> 228 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 228)
game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PositionStartSpotControls.cpp: LINKS  LINKED 426 -> 426 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 426)
game/GameEngine/Source/GameLogic/AI/AIMoveAndDeleteState_onEnter_Thunk.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 0)
  duplicate   ?onEnter@AIMoveAndDeleteState@@UAE?AW4StateReturnType@@XZ
  comdat      ?onEnter@AIMoveAndDeleteState@@UAE?AW4StateReturnType@@XZ  (retail: not retail's body)
  selected    ?onEnter@AIMoveAndDeleteState@@UAE?AW4StateReturnType@@XZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/Rva001703C0AIStateMachine_update.cpp: LINKS  LINKED 118 -> 118 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 118)
game/GameEngine/Source/GameLogic/AI/pathfind_tightenPath.cpp: LINKS  LINKED 142 -> 142 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 142)
game/GameEngine/Source/GameLogic/Map/TerrainLogicGetHighestLayer.cpp: LINKS  LINKED 165 -> 165 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 165)
game/GameEngine/Source/GameClient/MapMetaData_dtor.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 183)
  unresolved  ??1Rva00078460Elem@@QAE@XZ
  unresolved  ?releaseBuffer@BFMERetailAsciiString@@QAEXXZ
  unresolved  __imp_?deallocate@?$__node_alloc@$00$0A@@_STL@@SAXPAXI@Z
  duplicate   ??1?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@QAE@XZ
  duplicate   ??1BFMERetailAsciiString@@QAE@XZ
  duplicate   ??1MapMetaData@@QAE@XZ
  comdat      ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@_STL@@@_STL@@QAEXPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@2@I@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ??1?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ?clear@?$_List_base@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXXZ  (retail: not retail's body)
  comdat      ??1?$_Rb_tree_base@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@2@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ??1?$_List_base@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ?_M_erase@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@3@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@2@@Z  (retail: not retail's body)
  comdat      ??1?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@3@@_STL@@QAE@XZ  (retail: not retail's body)
  selected    ??1MapMetaData@@QAE@XZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/LivingWorld/Rva0020CA90Attack.cpp: LINKS  LINKED 158 -> 158 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 158)
game/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehaviorOnObjectCreated.cpp: LINKS  LINKED 131 -> 131 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 131)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdFollowThruStateOnExit.cpp: LINKS  LINKED 210 -> 210 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 210)
game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDrawReactToTransformChange.cpp: LINKS  LINKED 283 -> 283 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 283)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewWorldToScreenBfme.cpp: LINKS  LINKED 180 -> 180 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 180)
game/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleModuleState005FC800Slot1.cpp: LINKS  LINKED 105 -> 105 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 105)
game/GameEngine/Source/GameLogic/AI/AIGroupCenter.cpp: LINKS  LINKED 222 -> 222 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 222)
link_check: 13 of 20 link cleanly; LINKED 2,628 -> 2,628 bytes (164.3s)
```

No game run or RAM/leak/crash/FPS/multicore gain is established. The independent
projects verify concurrently; per-repository sources/cache/commits are handled
sequentially, BUILD_POOL14 each. No local model is used.

- [Adopt canonical Coord3D in OpenContainGetNaturalRallyPoint](b1-01-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in Condition_duplicate](b1-02-coordinate-header-20261104-1242.md): 2 retained rows.
- [Adopt canonical Coord3D in Parameter_WriteParameter_Thunk](b1-03-coordinate-header-20261104-1242.md): 2 retained rows.
- [Adopt canonical Coord3D in ParticleSystemFXNuggetConstructor](b1-04-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in BridgeBehaviorBodyState](b1-05-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in GiantBirdFollowPathState_update](b1-06-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in W3DViewSetZoomToDefaultBfme](b1-07-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in PositionStartSpotControls](b1-08-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in AIMoveAndDeleteState_onEnter_Thunk](b1-09-coordinate-header-20261104-1242.md): 2 retained rows.
- [Adopt canonical Coord3D in Rva001703C0AIStateMachine_update](b1-10-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in pathfind_tightenPath](b1-11-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in TerrainLogicGetHighestLayer](b1-12-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in MapMetaData_dtor](b1-13-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in Rva0020CA90Attack](b1-14-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in BridgeScaffoldBehaviorOnObjectCreated](b1-15-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in AIGiantBirdFollowThruStateOnExit](b1-16-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in W3DLightDrawReactToTransformChange](b1-17-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in W3DViewWorldToScreenBfme](b1-18-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in ParticleModuleState005FC800Slot1](b1-19-coordinate-header-20261104-1242.md): 1 retained rows.
- [Adopt canonical Coord3D in AIGroupCenter](b1-20-coordinate-header-20261104-1242.md): 1 retained rows.