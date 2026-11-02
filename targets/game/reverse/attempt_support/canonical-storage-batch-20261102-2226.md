# 18 BFME1 canonical-storage adoptions

Base `849fdc602c2e4a55bfff11d796d67fad1d781677`. 18 separately claimed existing source units replace
private storage definitions with their existing registered canonical headers.
Normal gates preserve 19 native function/EH rows, 1900 ledger-extent
bytes, 51 retained external code bodies/relocation lists and
2 named TU-local code definitions. No new native rows, names,
pins, aliases, shared headers, compiler flags or baselines are authored.
No native/authored-byte or runtime improvement is claimed.

- [Adopt canonical Coord3D in SupplyTruckAIUpdate_setStoredPosition](supplytruckaiupdate_setstoredposition-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in LivingWorldRegionManager_Rva003C8300](livingworldregionmanager_rva003c8300-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Weapon_getAttackDistance](weapon_getattackdistance-coord3d-20261102-2226.md): 1 existing rows, 2 retained external definitions.
- [Adopt canonical Coord3D in BfmePositionHistoryPush](bfmepositionhistorypush-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in BfmeFacingDotProduct](bfmefacingdotproduct-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in DozerAIUpdate_getDockPoint](dozeraiupdate_getdockpoint-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in BfmeGeometryCollisionSource](bfmegeometrycollisionsource-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Weapon_isWithinAttackRange](weapon_iswithinattackrange-coord3d-20261102-2226.md): 2 existing rows, 2 retained external definitions.
- [Adopt canonical Coord3D in PathNodeGetNextOptimized](pathnodegetnextoptimized-coord3d-20261102-2226.md): 1 existing rows, 3 retained external definitions.
- [Adopt canonical Coord3D in Rva001DD2E0GeometryCheck](rva001dd2e0geometrycheck-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in EvaCheck_trigger](evacheck_trigger-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in LaserUpdate_initFromDrawables](laserupdate_initfromdrawables-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in PathfindBuildActualPathE10f0](pathfindbuildactualpathe10f0-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in WeaponTemplate_getAttackRange](weapontemplate_getattackrange-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in GeometryInfoCalcPitches](geometryinfocalcpitches-coord3d-20261102-2226.md): 1 existing rows, 7 retained external definitions.
- [Adopt canonical Coord3D in TerrainScorchFXNugget_doFXPos_Thunk](terrainscorchfxnugget_dofxpos_thunk-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Rva21E970PositionPropagation](rva21e970positionpropagation-coord3d-20261102-2226.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Coord3DVectorFillInsert](coord3dvectorfillinsert-coord3d-20261102-2226.md): 1 existing rows, 24 retained external definitions.

Each unit has its own before-object, isolated private compile, normal byte gate,
frozen-file check and owning header acceptance. Added/removed components have no
incoming retained runtime/data root; exact added-code profiles are independently
checked. Named statics are compared separately; generated EH labels belong to
the complete runtime-section (BFME1) or native parent EH (BFME2) checks.

All non-debug sections of all18 BFME1 objects preserve bytes and resolved
relocation positions. The published cached index d08539a550 (Nov2 13:45) is reused after the artifact
server refused a new download with HTTP503/account egress limit. Index SHA256
eee24b92dbc1673e69aa961c3e2464c7f67c037f6accdba45af20d369efdd4a8.
No index mutation, fresh census or full current selection is claimed.

The linking-first picker still selects AnimateWindowManager's24-byte vtable,
2,161B at d08539a550. The normal unit gate passes; the frozen checker reports
the sole table provider wrong/selected. Its named table has no native binding
for the emitted vector-deleting destructor or SubsystemInterface::draw.
The preceding batch reviewed the BFME2 donor AnimateWindowManager and its
fold-row handoff. The BFME1 source and relevant checker inputs are unchanged
since that review; this run reuses its evidence instead of repeating the scan. Different toolchain settings and unresolved BFME1 slot identities
do not support copying a BFME2 table or binding names to an assumed target.
No vtable, pin, alias or shared header is changed, and the selection review
does not count as one of the18 completed storage tasks. Controls retain the
full six relocation targets and both raw candidate addresses; alternative
RVA/VA interpretations are not promoted to native identity.
The donor59e3f8f825b698775df9e1728265fe962a5d0c02 is unchanged; its Nov1
13:06 UTC freshness check is still within72h. No unchanged broad sweep repeats.

Bounded preview, not a fresh census or complete current selection:

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
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate_setStoredPosition.cpp: LINKS  LINKED 63 -> 63 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 63)
game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldRegionManager_Rva003C8300.cpp: LINKS  LINKED 46 -> 46 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 46)
game/GameEngine/Source/GameLogic/Object/Weapon_getAttackDistance.cpp: LINKS  LINKED 95 -> 95 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 95)
game/GameEngine/Source/GameLogic/AI/BfmePositionHistoryPush.cpp: LINKS  LINKED 124 -> 124 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 124)
game/GameEngine/Source/GameLogic/AI/BfmeFacingDotProduct.cpp: LINKS  LINKED 94 -> 94 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 94)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate_getDockPoint.cpp: LINKS  LINKED 60 -> 60 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 60)
game/GameEngine/Source/GameLogic/Object/BfmeGeometryCollisionSource.cpp: LINKS  LINKED 68 -> 68 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 68)
game/GameEngine/Source/GameLogic/Object/Weapon_isWithinAttackRange.cpp: LINKS  LINKED 90 -> 90 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 90)
game/GameEngine/Source/GameLogic/AI/PathNodeGetNextOptimized.cpp: LINKS  LINKED 139 -> 139 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 139)
game/GameEngine/Source/Common/Rva001DD2E0GeometryCheck.cpp: LINKS  LINKED 55 -> 55 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 55)
game/GameEngine/Source/GameClient/EvaCheck_trigger.cpp: LINKS  LINKED 121 -> 121 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 121)
game/GameEngine/Source/GameLogic/Object/Update/LaserUpdate_initFromDrawables.cpp: LINKS  LINKED 80 -> 80 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 80)
game/GameEngine/Source/GameLogic/Pathfinder/PathfindBuildActualPathE10f0.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 181)
  unresolved  ?bfmeOptimizeDir@Path@@QAEXPBVObject@@PBUCoord3D@@H_N@Z
  selected    ??0Path@@QAE@XZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/WeaponTemplate_getAttackRange.cpp: LINKS  LINKED 89 -> 89 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 89)
game/GameEngine/Source/Common/System/GeometryInfoCalcPitches.cpp: LINKS  LINKED 158 -> 158 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 158)
game/GameEngine/Source/GameClient/TerrainScorchFXNugget_doFXPos_Thunk.cpp: LINKS  LINKED 69 -> 69 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 69)
game/GameEngine/Source/Common/Rva21E970PositionPropagation.cpp: LINKS  LINKED 57 -> 57 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 57)
game/Libraries/Source/WWVegas/WWLib/Coord3DVectorFillInsert.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 310)
  duplicate   ?_M_fill_insert@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXPAUCoord3D@@IABU3@@Z
  comdat      ?deallocate@?$allocator@UCoord3D@@@_STL@@QAEXPAUCoord3D@@I@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ??$uninitialized_fill_n@PAUCoord3D@@IU1@@_STL@@YAPAUCoord3D@@PAU1@IABU1@@Z  (retail: unproven and differs from the kept copy)
  comdat      ?_M_clear@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEXXZ  (first: differs from the first copy in link order (no retail address))
  comdat      ?_M_insert_overflow@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEXPAUCoord3D@@ABU3@ABU__false_type@2@I_N@Z  (retail: not retail's body)
  comdat      ?_M_fill_insert@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXPAUCoord3D@@IABU3@@Z  (retail: not retail's body)
  selected    ?_M_fill_insert@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXPAUCoord3D@@IABU3@@Z  (the definition the link keeps is not retail's)
  selected    ?_M_insert_overflow@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEXPAUCoord3D@@ABU3@ABU__false_type@2@I_N@Z  (the definition the link keeps is not retail's)
link_check: 16 of 18 link cleanly; LINKED 1,408 -> 1,408 bytes (218.9s)
```

## Parallel and sequential execution

The two independent repositories use separate source trees, object caches,
ledgers and claim namespaces; their working processes can run concurrently.
BUILD_POOL=14 per repository, aggregate28 build workers on28 logical CPUs.
Within one repository, source installation, normal verification, queue/log
writes, staging and commits are serialized. Private compilations are safe to
parallelize only with distinct objects and stable shared inputs; they do not
authorize simultaneous shared-cache or ledger writes. Dependent canonical-header
changes precede consumers and require their own wider gate. Publications follow
each repository's native workflow and account clock. No local inference or GPU
job is needed. No serial-vs-parallel speedup benchmark is claimed.

Full engine link, gameplay and RAM/leak/crash/FPS gains remain unproven.
