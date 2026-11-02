# 18 BFME1 canonical-storage adoptions

Base `87527fbcc708f67a8bd14d1996f8fed40aa08808`. 18 separately claimed existing source units replace
private storage definitions with their existing registered canonical headers.
Normal gates preserve 19 native function/EH rows, 1100 ledger-extent
bytes, 58 retained external code bodies/relocation lists and
0 named TU-local code definitions. No new native rows, names,
pins, aliases, shared headers, compiler flags or baselines are authored.
No native/authored-byte or runtime improvement is claimed.

- [Adopt canonical Coord3D in bfmeUnitAngle](bfmeunitangle-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in BfmeConv2094](bfmeconv2094-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Gen0060C510TargetAttachParticleSystem](gen0060c510targetattachparticlesystem-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Coord3DPairConstruct](coord3dpairconstruct-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Coord3DListInsert](coord3dlistinsert-coord3d-20261102-1632.md): 1 existing rows, 18 retained external definitions.
- [Adopt canonical Coord3D in Object_bfmeBoundaryDistanceSquared2D](object_bfmeboundarydistancesquared2d-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in QueueProductionExitUpdateSetRallyPoint](queueproductionexitupdatesetrallypoint-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in PartitionManagerShroudStatusForPlayer](partitionmanagershroudstatusforplayer-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in PathAppendNodeILT](pathappendnodeilt-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Rva001B49E0SetPosition](rva001b49e0setposition-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Rva00106F20Radar](rva00106f20radar-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in DynamicDecalFXNugget_doFXObj_Thunk](dynamicdecalfxnugget_dofxobj_thunk-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in LivingWorldManagerGetHeight](livingworldmanagergetheight-coord3d-20261102-1632.md): 1 existing rows, 20 retained external definitions.
- [Adopt canonical Coord3D in Rva0002E15EAsciiStringCoordTreeCopyThunk](rva0002e15easciistringcoordtreecopythunk-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in Rva001A3390TriggerCount](rva001a3390triggercount-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.
- [Adopt canonical Coord3D in ParticleSystemSetPosition](particlesystemsetposition-coord3d-20261102-1632.md): 1 existing rows, 4 retained external definitions.
- [Adopt canonical Coord3D in WeaponFireForwarders](weaponfireforwarders-coord3d-20261102-1632.md): 2 existing rows, 2 retained external definitions.
- [Adopt canonical Coord3D in WorkerAIUpdate_setStoredPosition](workeraiupdate_setstoredposition-coord3d-20261102-1632.md): 1 existing rows, 1 retained external definitions.

Each unit has its own before-object, isolated private compile, normal byte gate,
frozen-file check and owning header acceptance. Added/removed components have no
incoming retained runtime/data root; exact added-code profiles are independently
checked. Named statics are compared separately; generated EH labels belong to
the complete runtime-section (BFME1) or native parent EH (BFME2) checks.

All non-debug sections of all18 BFME1 objects preserve bytes and resolved
relocation positions. Paired original/current snapshots against d08539a550
also preserve their per-unit blocker results for every indexed unit. A census
comparison is not an adoption before/after result or full current selection.

The new linking-first picker selects AnimateWindowManager's24-byte vtable,
2,161B at d08539a550. The normal unit gate passes; the frozen checker reports
the sole table provider wrong/selected. Its named table has no native binding
for the emitted vector-deleting destructor or SubsystemInterface::draw.
The BFME2 donor AnimateWindowManager and its prior fold-row handoff were
reviewed. Different toolchain settings and unresolved BFME1 slot identities
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
game/GameEngine/Source/Common/bfmeUnitAngle.cpp: LINKS  LINKED 108 -> 108 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 108)
game/GameEngine/Source/Common/BfmeConv2094.cpp: LINKS  LINKED 65 -> 65 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 65)
game/GameEngine/Source/GameClient/Gen0060C510TargetAttachParticleSystem.cpp: LINKS  LINKED 43 -> 43 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 43)
game/GameEngine/Source/GameClient/Coord3DPairConstruct.cpp: LINKS  LINKED 5 -> 5 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 5)
game/GameEngine/Source/Common/Coord3DListInsert.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 75)
  comdat      ?_M_create_node@?$list@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@IAEPAU?$_List_node@UCoord3D@@@2@ABUCoord3D@@@Z  (retail: not retail's body)
  selected    ??$_M_insert_dispatch@U?$_List_iterator@UCoord3D@@U?$_Const_traits@UCoord3D@@@_STL@@@_STL@@@?$list@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXU?$_List_iterator@UCoord3D@@U?$_Nonconst_traits@UCoord3D@@@_STL@@@1@U?$_List_iterator@UCoord3D@@U?$_Const_traits@UCoord3D@@@_STL@@@1@1ABU__false_type@1@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Object_bfmeBoundaryDistanceSquared2D.cpp: LINKS  LINKED 21 -> 21 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 21)
game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateSetRallyPoint.cpp: LINKS  LINKED 81 -> 81 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 81)
game/GameEngine/Source/GameLogic/Object/PartitionManagerShroudStatusForPlayer.cpp: LINKS  LINKED 8 -> 8 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 8)
game/GameEngine/Source/GameLogic/AI/PathAppendNodeILT.cpp: LINKS  LINKED 5 -> 5 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 5)
game/GameEngine/Source/Common/Rva001B49E0SetPosition.cpp: LINKS  LINKED 44 -> 44 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 44)
game/GameEngine/Source/Common/System/Rva00106F20Radar.cpp: LINKS  LINKED 119 -> 119 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 119)
game/GameEngine/Source/GameClient/DynamicDecalFXNugget_doFXObj_Thunk.cpp: LINKS  LINKED 30 -> 30 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 30)
game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManagerGetHeight.cpp: LINKS  LINKED 237 -> 237 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 237)
game/GameEngine/Source/Common/Rva0002E15EAsciiStringCoordTreeCopyThunk.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 5)
  unresolved  ?copy@AsciiCoordTreeCopyShim@_STL@@QAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@2@PAU32@0@Z
game/GameEngine/Source/GameLogic/Rva001A3390TriggerCount.cpp: LINKS  LINKED 73 -> 73 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 73)
game/GameEngine/Source/GameClient/System/ParticleSystemSetPosition.cpp: LINKS  LINKED 39 -> 39 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 39)
game/GameEngine/Source/GameLogic/Object/WeaponFireForwarders.cpp: LINKS  LINKED 78 -> 78 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 78)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_setStoredPosition.cpp: LINKS  LINKED 63 -> 63 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 63)
link_check: 16 of 18 link cleanly; LINKED 1,019 -> 1,019 bytes (117.3s)
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
