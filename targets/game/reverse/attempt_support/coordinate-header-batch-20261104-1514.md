# Twenty further BFME1 coordinate reconciliations

Base `e61f5c5f6366db32602abd70b3b1e7795539ac80`. Replace20 data-only private Coord3D declarations with the
existing registered BFME1 header. Native CodeView proves every struct/12B,
float x/y/z at0/4/8, no bases/vptr/methods/statics. Private view inventory:
{'Coord2D': 29, 'Coord3D': 591} -> {'Coord2D': 29, 'Coord3D': 571}. All24 existing rows (5859 ledger-extent bytes),
149 external definitions, local code and complete ordered nondebug section
data/relocations are unchanged. Only the canonical header is added to each
resolved dependency set; every prior path/hash is retained. No header, ledger,
pin, alias, baseline or compiler option changes. These are source tasks, not
new authored coverage or generated-code recoveries.

Linking was reviewed first. The current picker still serves aiMoveToPosition
wrong_selected/1826 estimated census bytes. OneRing and MovementOrders source
match the previous published package; the reviewed donor SlavedUpdateRepair
SHA256 remains a5a18492070ef9b1afae5f0d419afab7fa206c0b80580f76d5afa5bcbe8c5f8a.
The reference pin/checkout is still f6d845ecd439374ef476ce04c992a2b848eb2c99;
its successful13:39 UTC freshness check is within72h. Reuse the tracked
donor-refresh-20261104-1410.md and aimove-provider-20261104-0356.md evidence;
no redundant donor scan or exhausted body variation is repeated. The visible
inline-helper/provider/scheduling prerequisite remains, with no donor layout
or compiler profile imported. Current full provider closure is not proved.

Dated scoped prediction, not a new census or full-image link:
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
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate_chooseGoodLocomotorFromCurrentSet.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 132)
  unresolved  ?m@T_000382c1@@QAEXXZ
  duplicate   ?chooseGoodLocomotorFromCurrentSet@AIUpdateInterface@@IAEXXZ
  selected    ?chooseGoodLocomotorFromCurrentSet@AIUpdateInterface@@IAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Pathfinder/PathfindE1fe0.cpp: LINKS  LINKED 270 -> 270 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 270)
game/GameEngine/Source/GameLogic/Object/Die/DieMuxDataIsDieApplicable.cpp: LINKS  LINKED 241 -> 241 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 241)
game/GameEngine/Source/GameLogic/Map/BridgeIsPointOnBridge.cpp: LINKS  LINKED 344 -> 344 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 344)
game/GameEngine/Source/GameLogic/Object/Contain/Rva0023D850HordeSnapToMember.cpp: LINKS  LINKED 147 -> 147 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 147)
game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawSetHidden.cpp: LINKS  LINKED 132 -> 132 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 132)
game/GameEngine/Source/GameLogic/Object/Locomotor_rva001BB0D0.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 890)
  unresolved  ?bfmeFinish1282@BfmeA1282@@QAEXPAVBfmeQ1282@@PBUCoord3D@@MM@Z
  comdat      ?clearModelConditionState@Object@@QAEXH@Z  (retail: not retail's body)
  selected    ?clearModelConditionState@Object@@QAEXH@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/AIGuard_getGuardScanPos.cpp: LINKS  LINKED 278 -> 278 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 278)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BCE00StateAction.cpp: LINKS  LINKED 168 -> 168 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 168)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRva00744360.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 357)
  unresolved  ?castRay@RTS3DScene@@QAE_NAAVRayCollisionTestClass@@_NH@Z
  comdat      ?getObject@Drawable@@QAEPAVObject@@XZ  (first: differs from the first copy in link order (no retail address))
  comdat      ??0RayCollisionTestClass@@QAE@ABVLineSegClass@@PAUCastResultStruct@@H_N2@Z  (retail: not retail's body)
game/GameEngine/Source/GameLogic/AI/Rva0015EBE0GuardContainQuery.cpp: LINKS  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 0)
game/GameEngine/Source/GameLogic/Object/ObjectPreFireCurrentWeapon.cpp: LINKS  LINKED 215 -> 215 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 215)
game/GameEngine/Source/GameLogic/AI/PathfinderSetDebugPath.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 190)
  selected    ??0Path@@QAE@XZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/ScriptEngine/LuaObjectBindings002E6650.cpp: LINKS  LINKED 310 -> 310 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 310)
game/GameEngine/Source/Common/Rva006DF420ProbeOffsets.cpp: LINKS  LINKED 237 -> 237 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 237)
game/GameEngine/Source/Common/U4Blend00609600.cpp: LINKS  LINKED 298 -> 298 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 298)
game/GameEngine/Source/GameClient/FXListDoFXPosPublic.cpp: LINKS  LINKED 133 -> 133 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 133)
game/GameEngine/Source/GameClient/SoundFXNugget_doFXObj_Thunk.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 265)
  comdat      ?doFXObj@SoundFXNugget@@UBEXPBVObject@@0@Z  (retail: not retail's body)
  comdat      ?doFXPos@SoundFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z  (retail: not retail's body)
  selected    ?doFXObj@SoundFXNugget@@UBEXPBVObject@@0@Z  (the definition the link keeps is not retail's)
  selected    ?doFXPos@SoundFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorUpdateThunk.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 719)
  duplicate   ?update@BridgeBehavior@@UAE?AW4UpdateSleepTime@@XZ
  selected    ?isEmpty@AsciiString@@QBE_NXZ  (the definition the link keeps is not retail's)
  selected    ?update@BridgeBehavior@@UAE?AW4UpdateSleepTime@@XZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/ScriptEngine/XferListAsciiStringCoord3D.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 435)
  selected    ?_M_allocate@?$__node_alloc@$00$0A@@_STL@@CAPAXI@Z  (the definition the link keeps is not retail's)
link_check: 13 of 20 link cleanly; LINKED 2,773 -> 2,773 bytes (236.1s)
```

Both projects verify independently in parallel, with sequential per-project
mutations and BUILD_POOL14 each. No local model. No gameplay, RAM/leak/crash,
64-bit/FPS/multicore result is established.

- [Adopt canonical Coord3D in AIUpdate_chooseGoodLocomotorFromCurrentSet](b1-01-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in PathfindE1fe0](b1-02-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in DieMuxDataIsDieApplicable](b1-03-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in BridgeIsPointOnBridge](b1-04-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in Rva0023D850HordeSnapToMember](b1-05-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in W3DModelDrawSetHidden](b1-06-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in Locomotor_rva001BB0D0](b1-07-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in AIGuard_getGuardScanPos](b1-08-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in Rva002BCE00StateAction](b1-09-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in W3DViewRva00744360](b1-10-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in Rva0015EBE0GuardContainQuery](b1-11-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in ObjectPreFireCurrentWeapon](b1-12-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in PathfinderSetDebugPath](b1-13-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in LuaObjectBindings002E6650](b1-14-coordinate-header-20261104-1514.md): 2 retained rows.

- [Adopt canonical Coord3D in Rva006DF420ProbeOffsets](b1-15-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in U4Blend00609600](b1-16-coordinate-header-20261104-1514.md): 2 retained rows.

- [Adopt canonical Coord3D in FXListDoFXPosPublic](b1-17-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in SoundFXNugget_doFXObj_Thunk](b1-18-coordinate-header-20261104-1514.md): 2 retained rows.

- [Adopt canonical Coord3D in BridgeBehaviorUpdateThunk](b1-19-coordinate-header-20261104-1514.md): 1 retained rows.

- [Adopt canonical Coord3D in XferListAsciiStringCoord3D](b1-20-coordinate-header-20261104-1514.md): 2 retained rows.
