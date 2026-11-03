#18 BFME1 data-only Coord2D header adoptions

Base `42098e3dc6d67087d53c103c13dee150495c8e8a`. Native header ordering inventories49 private Coord2D views.
Choose18 unqueued, data-only struct views with the existing x/y field spellings.
The compiler proves size8, float fields at0/4, no bases/vptr/methods/statics;
the existing BFME1 canonical contract and registered header agree. Native
census now reports31 private views. Nontrivial constructors/return-copy cases
and previously queued failures are deliberately not retried as this pattern.

Each source adopts the same existing header at a source-relative path, without
body/field/ABI/flag/name/row/pin/shared-header or baseline changes. The only
added resolved dependency is that header; every old physical path and native
dependency digest stays unchanged. The header's separate artifact SHA256 is
recorded too. Native normal/frozen/header-acceptance checks pass for 25
existing native/EH rows (10072 ledger-extent bytes). All 211 external
code instances and relocations, 9 named local code instances and every
non-debug section including data, EH and directives remain exact.

The first private diagnostic compared native MD5 dependency hashes with
artifact SHA256 hashes and therefore rejected already passing native results.
Those source edits were restored before the corrected, successful checks.
One private CodeView probe initially missed a normal-build retry include path;
it was rerun with exactly the directories in that source's native receipt.
Neither issue changed a project verifier, source compiler/ABI option or gate.

The primary native linking pick remains RefHandle008958D0's destructor loser,
846B in3 files. Prior blocker/owner trials and relevant BFME2 donor class were
reviewed; that class is unchanged at the pinned59e3f8f825b6 and current donor
revision. The differing24B/28B layouts and allocator callbacks are not copied.
No unchanged failed recovery is repeated or credited. This batch reduces18
private class copies, with no new native coverage, runtime, RAM/crash/FPS gain.

Bounded dated preview (not a new census or full-image link):

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
game/GameEngine/Source/Common/Rva00463BA0WindowBounds.cpp: LINKS  LINKED 111 -> 111 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 111)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCalcDeltaScrollThunk.cpp: LINKS  LINKED 157 -> 157 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 157)
game/GameEngine/Source/GameLogic/AI/Rva003D60E0RadialOffset.cpp: LINKS  LINKED 152 -> 152 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 152)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceCalculateMaxBlockedSpeed.cpp: LINKS  LINKED 289 -> 289 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 289)
game/GameEngine/Source/GameLogic/Object/Contain/HordeContainParseBannerCarrierPosition.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 326)
  unresolved  __imp_?allocate@?$__node_alloc@$00$0A@@_STL@@SAPAXI@Z
  unresolved  __imp_?deallocate@?$__node_alloc@$00$0A@@_STL@@SAXPAXI@Z
  comdat      ?deallocate@?$allocator@UGen_t_0023daa0_p4pod@@@_STL@@QAEXPAUGen_t_0023daa0_p4pod@@I@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?_M_insert_overflow@?$vector@UGen_t_0023daa0_p4pod@@V?$allocator@UGen_t_0023daa0_p4pod@@@_STL@@@_STL@@IAEXPAUGen_t_0023daa0_p4pod@@ABU3@ABU__false_type@2@I_N@Z  (retail: not retail's body)
  comdat      ?parseBannerCarrierPosition@@YAXPAVINI@@PAX1PBX@Z  (retail: not retail's body)
  selected    ?_M_insert_overflow@?$vector@UGen_t_0023daa0_p4pod@@V?$allocator@UGen_t_0023daa0_p4pod@@@_STL@@@_STL@@IAEXPAUGen_t_0023daa0_p4pod@@ABU3@ABU__false_type@2@I_N@Z  (the definition the link keeps is not retail's)
  selected    ?parseBannerCarrierPosition@@YAXPAVINI@@PAX1PBX@Z  (the definition the link keeps is not retail's)
  selected    ?set@AsciiString@@QAEXPBD@Z  (the definition the link keeps is not retail's)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DBoxFilterDraw.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 570)
  unresolved  ?ScreenMaterial@@3PAVVertexMaterialClass@@A
  unresolved  ?TheBoxTextureDirtyMask@@3IA
  unresolved  ?TheDX8Caps@@3PAVDX8CapsLike@@A
  unresolved  ?TheScorchShader@@3VShaderClass@@A
  unresolved  ?bfmeDrawFilterUV@@YAXHHPAUCoord2D@@@Z
game/GameEngine/Source/Common/Rva00588E60DrawImageAt.cpp: LINKS  LINKED 120 -> 120 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 120)
game/GameEngine/Source/GameLogic/AI/AIGroup_getMinMaxAndCenter_Thunk.cpp: LINKS  LINKED 326 -> 326 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 326)
game/GameEngine/Source/GameLogic/Map/Bridge_isCellOnSide_Thunk.cpp: LINKS  LINKED 504 -> 504 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 504)
game/GameEngine/Source/GameLogic/AI/AIPlayerComputeCenterAndRadiusOfBase.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 503)
  duplicate   ?computeCenterAndRadiusOfBase@AIPlayer@@IAEXPAUCoord3D@@PAM@Z
  selected    ?computeCenterAndRadiusOfBase@AIPlayer@@IAEXPAUCoord3D@@PAM@Z  (the definition the link keeps is not retail's)
  selected    ?getTemplateName@BuildListInfo@@QBE?AVAsciiString@@XZ  (the definition the link keeps is not retail's)
  selected    ?isEmpty@AsciiString@@QBE_NXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva00245010RecordBuild.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 828)
  comdat      ??$_Construct@UBfmeRva44E60Record@@U1@@_STL@@YAXPAUBfmeRva44E60Record@@ABU1@@Z  (retail: not retail's body)
  comdat      ??$_Construct@VRva00244A80Element@@V1@@_STL@@YAXPAVRva00244A80Element@@ABV1@@Z  (retail: not retail's body)
  selected    ??$_Construct@UBfmeRva44E60Record@@U1@@_STL@@YAXPAUBfmeRva44E60Record@@ABU1@@Z  (the definition the link keeps is not retail's)
  selected    ??$_Construct@VRva00244A80Element@@V1@@_STL@@YAXPAVRva00244A80Element@@ABV1@@Z  (the definition the link keeps is not retail's)
  selected    ?push_back@?$list@HV?$allocator@H@_STL@@@_STL@@QAEXABH@Z  (the definition the link keeps is not retail's)
  alias_unknown ??0Rva00244A80Element@@QAE@ABV0@@Z=?j_000128dc@@YAXXZ  (the call resolves only through an /alternatename alias nothing can judge: alias: no pin or row)
game/GameEngine/Source/GameClient/DrawableVeterancyIcons.cpp: LINKS  LINKED 627 -> 627 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 627)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdateWaypointPath.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 398)
  duplicate   ?prependNode@Path@@QAEXPBUCoord3D@@W4PathfindLayerEnum@@@Z
  duplicate   ?setPathFromWaypoint@AIUpdateInterface@@QAEXPBVWaypoint@@PBUCoord2D@@@Z
  selected    ??0Path@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ?setPathFromWaypoint@AIUpdateInterface@@QAEXPBVWaypoint@@PBUCoord2D@@@Z  (the definition the link keeps is not retail's)
game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenFilterRva007D1E60PostRender.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 924)
  unresolved  ?BaseHeightMapScorchSetShader@@YAXABVShaderClass@@@Z
  unresolved  ?bfmeEndRenderToTexture@@YAPAXXZ
  unresolved  ?g_bfmeScaleB3@@3MA
  unresolved  ?g_rva007A2330Flag@@3DA
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp: LINKS  LINKED 942 -> 942 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 942)
game/GameEngine/Source/GameLogic/AI/Rva003F82C0Pathfinder.cpp: LINKS  LINKED 1,044 -> 1,044 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,044)
game/GameEngine/Source/GameLogic/AI/Rva001695B0AdjustBuildList.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 827)
  selected    ?getFirstObject@GameLogic@@QAEPAVObject@@XZ  (the definition the link keeps is not retail's)
  selected    ?getTemplateName@BuildListInfo@@QBE?AVAsciiString@@XZ  (the definition the link keeps is not retail's)
  selected    ?setLocation@BuildListInfo@@QAEXUCoord3D@@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/Rva003F8820Pathfinder.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,385)
  unresolved  ?g_rva012B4C0C@@3PAHA
  unresolved  ?g_rva012B4C34@@3PAHA
link_check: 10 of 18 link cleanly; LINKED 4,272 -> 4,272 bytes (174.2s)
```

Independent repositories ran concurrently; source edits, native object caches
and commits within each repository were sequential. BUILD_POOL14 each permits
28 build workers on28 logical CPUs. No local model was needed.

- [Adopt canonical Coord2D in Rva00463BA0WindowBounds](b1-01-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in W3DViewCalcDeltaScrollThunk](b1-02-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in Rva003D60E0RadialOffset](b1-03-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in AIUpdateInterfaceCalculateMaxBlockedSpeed](b1-04-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in HordeContainParseBannerCarrierPosition](b1-05-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in W3DBoxFilterDraw](b1-06-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in Rva00588E60DrawImageAt](b1-07-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in AIGroup_getMinMaxAndCenter_Thunk](b1-08-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in Bridge_isCellOnSide_Thunk](b1-09-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in AIPlayerComputeCenterAndRadiusOfBase](b1-10-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in Rva00245010RecordBuild](b1-11-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in DrawableVeterancyIcons](b1-12-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in AIUpdateWaypointPath](b1-13-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in ScreenFilterRva007D1E60PostRender](b1-14-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in ScriptEngine](b1-15-coord2d-header-20261103-1526.md): 8 existing rows.
- [Adopt canonical Coord2D in Rva003F82C0Pathfinder](b1-16-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in Rva001695B0AdjustBuildList](b1-17-coord2d-header-20261103-1526.md): 1 existing rows.
- [Adopt canonical Coord2D in Rva003F8820Pathfinder](b1-18-coord2d-header-20261103-1526.md): 1 existing rows.