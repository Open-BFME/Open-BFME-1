# 18 BFME1 include-inventory repairs

Base `9dff51acaa037c7ef85f8be83db17d2649fadf0c`. Each source independently removes only its redundant whole-checkout
`/I.` search root and anchors existing includes relative to the source. The
before/after compiler dependency sets resolve to the same physical paths and
hashes, normalizing Windows case and relative path aliases. No source body,
optimization or ABI switch, shared header, native name, pin, alias, ledger,
hatch or baseline changes. Every source has its own before-object, native
normal/frozen gate, external code/relocation comparison, named static comparison,
and complete non-debug-section comparison including data, EH and linker directives.

Preserved: 36 existing native function/EH rows, 12698 ledger-extent bytes,
434 retained external code instances and 20 named TU-local code
instances. No native coverage, runtime improvement or linked-byte gain is claimed.

- [Repair include inventory in Rva00380EE0ExperienceAdvance](b1-01-include-inventory-20261103-1212.md): 1 rows, 11 external code instances.
- [Repair include inventory in Rva003D86E0Scanner](b1-02-include-inventory-20261103-1212.md): 1 rows, 4 external code instances.
- [Repair include inventory in Rva0065B350MapLookupResponse](b1-03-include-inventory-20261103-1212.md): 5 rows, 56 external code instances.
- [Repair include inventory in Rva0015A600FormationOffsets](b1-04-include-inventory-20261103-1212.md): 1 rows, 10 external code instances.
- [Repair include inventory in WindowVideoManagerCtor](b1-05-include-inventory-20261103-1212.md): 11 rows, 101 external code instances.
- [Repair include inventory in Rva0023D230RepresentativeMember](b1-06-include-inventory-20261103-1212.md): 1 rows, 32 external code instances.
- [Repair include inventory in MilesAudioCacheReadAudioFile00694230](b1-07-include-inventory-20261103-1212.md): 1 rows, 40 external code instances.
- [Repair include inventory in ClickReactionBehaviorRva001F7B10](b1-08-include-inventory-20261103-1212.md): 1 rows, 2 external code instances.
- [Repair include inventory in BfmeTailA1044004B0850](b1-09-include-inventory-20261103-1212.md): 1 rows, 1 external code instances.
- [Repair include inventory in WaterShader007A6460](b1-10-include-inventory-20261103-1212.md): 1 rows, 11 external code instances.
- [Repair include inventory in WaterShader007A6AA0](b1-11-include-inventory-20261103-1212.md): 1 rows, 14 external code instances.
- [Repair include inventory in GiantBirdGuardIdleState](b1-12-include-inventory-20261103-1212.md): 1 rows, 12 external code instances.
- [Repair include inventory in PathfinderIterateCellsAlongLineRva003E3650](b1-13-include-inventory-20261103-1212.md): 1 rows, 20 external code instances.
- [Repair include inventory in Rva001FD970Update](b1-14-include-inventory-20261103-1212.md): 1 rows, 15 external code instances.
- [Repair include inventory in AODHordeContainUpdateFormationMembers](b1-15-include-inventory-20261103-1212.md): 1 rows, 73 external code instances.
- [Repair include inventory in AIGuardIdleStateDestructor](b1-16-include-inventory-20261103-1212.md): 2 rows, 13 external code instances.
- [Repair include inventory in Rva00585CF0HandleUpdate](b1-17-include-inventory-20261103-1212.md): 4 rows, 13 external code instances.
- [Repair include inventory in SiegeDeploySpecialPowerUpdate](b1-18-include-inventory-20261103-1212.md): 1 rows, 6 external code instances.

## Selection and scope

The native link pickers were reviewed before choosing this bounded compiler-input
maintenance batch. Repeated unchanged failed body trials are not work credit.

BFME1's current native dry-run picks RefHandle008958D0's destructor COMDAT losers
in ManagerFind/CreateHandle/Dependencies, 846B at index d08539a550. Existing native
records already establish the exact 35B owner at 00784A70 and explain why its
inline-drop copies differ from the kept helper-calling form. The recorded
inline-depth/optimization/source-order trials are not repeated. The pinned donor
is `59e3f8f825b698775df9e1728265fe962a5d0c02`; its relevant source was compared with
current BFME2 `4c68335a247a7bb4b0e03ebb87b8bc8378eb0231`. The key destructor body is
unchanged; current changes import canonical string/allocator declarations and
do not resolve the BFME1 COMDAT/codegen prerequisite. The BFME1 24B object and
free callback differ from BFME2's 28B allocator-owned object. No donor body,
ABI, vtable, alias or address is copied. This review is not a completed repair.
The previous AnimateWindowManager target has changed upstream; no credit for
that other contributor's work is taken here. The previous run successfully fetched the native artifact; this run reuses the dated Nov2 13:45 d08539a550 index, not a fresh census.

Bounded dated preview (UNKNOWN/INCONCLUSIVE stays unverified):

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
game/GameEngine/Source/Common/Rva00380EE0ExperienceAdvance.cpp: LINKS  LINKED 283 -> 283 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 283)
game/GameEngine/Source/GameLogic/AI/Rva003D86E0Scanner.cpp: LINKS  LINKED 477 -> 477 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 477)
game/GameEngine/Source/GameNetwork/Rva0065B350MapLookupResponse.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 944)
  duplicate   ?trim@AsciiString@@QAEXXZ
  comdat      ?trim@AsciiString@@QAEXXZ  (retail: not retail's body)
  comdat      ??$find@PAX@?$_Rb_tree@PAXU?$pair@QAXPAX@_STL@@U?$_Select1st@U?$pair@QAXPAX@_STL@@@2@U?$less@PAX@2@V?$allocator@U?$pair@QAXPAX@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@QAXPAX@_STL@@U?$_Nonconst_traits@U?$pair@QAXPAX@_STL@@@2@@1@ABQAX@Z  (retail: not retail's body)
  selected    ??$find@PAX@?$_Rb_tree@PAXU?$pair@QAXPAX@_STL@@U?$_Select1st@U?$pair@QAXPAX@_STL@@@2@U?$less@PAX@2@V?$allocator@U?$pair@QAXPAX@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@QAXPAX@_STL@@U?$_Nonconst_traits@U?$pair@QAXPAX@_STL@@@2@@1@ABQAX@Z  (the definition the link keeps is not retail's)
  selected    ?trim@AsciiString@@QAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/Common/Rva0015A600FormationOffsets.cpp: LINKS  LINKED 307 -> 307 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 307)
game/GameEngine/Source/GameClient/GUI/WindowVideoManagerCtor.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 588)
  unresolved  ?TheVideoPlayer@@3PAVVideoPlayer@@A
  duplicate   ?playMovie@WindowVideoManager@@QAEXPAVGameWindow@@VAsciiString@@W4WindowVideoPlayType@@@Z
  comdat      ?deallocate@?$allocator@PAX@_STL@@QAEXPAPAXI@Z  (retail: not retail's body)
  comdat      ?allocate@?$allocator@PAX@_STL@@QAEPAPAXIPBX@Z  (retail: not retail's body)
  comdat      ??1?$_Vector_base@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ?clear@?$hashtable@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAEXXZ  (retail: not retail's body)
  comdat      ??1?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ?_M_insert_overflow@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@IAEXPAPAXABQAXABU__true_type@2@I_N@Z  (retail: not retail's body)
  comdat      ??$_M_allocate_and_copy@PAPAX@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@IAEPAPAXIPAPAX0@Z  (retail: not retail's body)
  comdat      ??1?$hashtable@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ??E?$_Ht_iterator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@U?$_Nonconst_traits@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAEAAU01@XZ  (retail: not retail's body)
  comdat      ?reserve@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEXI@Z  (retail: not retail's body)
  comdat      ??E?$_Ht_iterator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@U?$_Nonconst_traits@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAE?AU01@H@Z  (retail: not retail's body)
  comdat      ??_7WindowVideoManager@@6B@  (retail: not retail's body)
  selected    ??1?$hashtable@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ??1WindowVideoManager@@UAE@XZ  (the definition the link keeps is not retail's)
  selected    ??E?$_Ht_iterator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@U?$_Nonconst_traits@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAE?AU01@H@Z  (the definition the link keeps is not retail's)
  selected    ??E?$_Ht_iterator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@U?$_Nonconst_traits@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAEAAU01@XZ  (the definition the link keeps is not retail's)
  selected    ??_7WindowVideoManager@@6B@  (the definition the link keeps is not retail's)
  selected    ?update@WindowVideoManager@@UAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva0023D230RepresentativeMember.cpp: LINKS  LINKED 409 -> 409 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 409)
game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCacheReadAudioFile00694230.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 651)
  unresolved  ?DebugGlobal00409E20@@3PAVDebugView00409E20@@A
  comdat      ?compare@AsciiString@@QBEHABV1@@Z  (retail: unproven and differs from the kept copy)
  comdat      ??$_Construct@VAsciiString@@V1@@_STL@@YAXPAVAsciiString@@ABV1@@Z  (retail: not retail's body)
  comdat      ?_M_create_node@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less@VAsciiString@@@3@V?$allocator@VAsciiString@@@3@@_STL@@IAEPAU?$_Rb_tree_node@VAsciiString@@@2@ABVAsciiString@@@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?_M_insert@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less@VAsciiString@@@3@V?$allocator@VAsciiString@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABVAsciiString@@0@Z  (retail: not retail's body)
  selected    ??$_Construct@VAsciiString@@V1@@_STL@@YAXPAVAsciiString@@ABV1@@Z  (the definition the link keeps is not retail's)
  selected    ?Rva00693FB0@Gen0002857EOwner@@QAEXXZ  (the definition the link keeps is not retail's)
  selected    ?_M_insert@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less@VAsciiString@@@3@V?$allocator@VAsciiString@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABVAsciiString@@0@Z  (the definition the link keeps is not retail's)
  selected    ?insert_unique@?$_Rb_tree@VAsciiString@@V1@U?$_Identity@VAsciiString@@@_STL@@U?$less@VAsciiString@@@3@V?$allocator@VAsciiString@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@_STL@@_N@2@ABVAsciiString@@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Behavior/ClickReactionBehaviorRva001F7B10.cpp: LINKS  LINKED 339 -> 339 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 339)
game/GameEngine/Source/GameClient/GUI/BfmeTailA1044004B0850.cpp: LINKS  LINKED 355 -> 355 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 355)
game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterShader007A6460.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,262)
  unresolved  ?BaseHeightMapScorchSetShader@@YAXABVShaderClass@@@Z
  unresolved  ?D3DDevice@DX8Wrapper@@2PAUIDirect3DDevice8@@A
  unresolved  ?Pixel_Shader_Constants@DX8Wrapper@@2PAVVector4@@A
  unresolved  ?SnapshotActivated@WW3D@@2_NA
  unresolved  ?TextureStageStates@DX8Wrapper@@2PAY0CA@IA
  unresolved  ?matrix_changes@DX8Wrapper@@2IA
  unresolved  ?render_state@DX8Wrapper@@2URenderStateStruct@@A
  unresolved  ?render_state_changed@DX8Wrapper@@2IA
  unresolved  ?texture_stage_state_changes@DX8Wrapper@@2IA
  duplicate   ?Set_DX8_Texture_Stage_State@DX8Wrapper@@SAXIKI@Z
  comdat      ?Set_DX8_Texture_Stage_State@DX8Wrapper@@SAXIKI@Z  (retail: not retail's body)
  comdat      ?Set_Material@DX8Wrapper@@SAXPBVVertexMaterialClass@@@Z  (retail: unproven and differs from the kept copy)
game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterShader007A6AA0.cpp: LINKS  LINKED 1,553 -> 1,553 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,553)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardIdleState.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 290)
  duplicate   ?getEstimateTeamPosition_000EDCD0@Team@@QBEXPAUCoord3D@@@Z
  selected    ?lookForInnerTarget@GiantBirdGuardMachine@@QAE_NXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003E3650.cpp: LINKS  LINKED 538 -> 538 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 538)
game/GameEngine/Source/Common/Rva001FD970Update.cpp: LINKS  LINKED 1,340 -> 1,340 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,340)
game/GameEngine/Source/GameLogic/Object/Contain/AODHordeContainUpdateFormationMembers.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,539)
  unresolved  ?bfmeBlocksFormationRefresh@AIUpdateInterface@@QAE_NXZ
  duplicate   ?sub@Coord3D@@QAEXPBUCoord3DBase@@@Z
  comdat      ??DCoord3D@@QBEMABUCoord3DBase@@@Z  (retail: not retail's body)
game/GameEngine/Source/GameLogic/AI/AIGuardIdleStateDestructor.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 295)
  duplicate   ?getEstimateTeamPosition_000EDCD0@Team@@QBEXPAUCoord3D@@@Z
  selected    ?lookForInnerTarget@AIGuardMachine@@QAE_NXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/Common/Rva00585CF0HandleUpdate.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 699)
  unresolved  ?rva0046B2A0@Rva00579160Manager@@QAEIABVAsciiString@@@Z
  unresolved  ?rva0060D4C0@BfmeGameCW@@QAEXPAX@Z
game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeploySpecialPowerUpdate.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 703)
  selected    ?aiMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z  (the definition the link keeps is not retail's)
link_check: 9 of 18 link cleanly; LINKED 5,601 -> 5,601 bytes (213.2s)
```

## Execution and proof limits

The repositories use independent claims, source trees, ledgers and object caches,
so native work ran concurrently between projects. Within each repository, edits,
native cache writes, log writes and commits were sequential. BUILD_POOL=14 each,
up to28 build workers on28 logical CPUs. No local model was required. No measured
serial/parallel speedup is claimed. The already-corrected diagnostic controls are reused; project gates remain unchanged.

This batch repairs compiler include inventories. It does not establish RAM/leak,
crash, FPS or multicore improvements. Full engine linking/gameplay remain unproven.
