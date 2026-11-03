# 8 BFME1 include-inventory repairs

Base `b6053e9b8b2490bdcf691bdab4730a6cb8d9dac8`. Each source independently removes only its redundant whole-checkout
`/I.` search root and anchors existing includes relative to the source. The
before/after compiler dependency sets resolve to the same physical paths and
hashes, normalizing Windows case and relative path aliases. No source body,
optimization or ABI switch, shared header, native name, pin, alias, ledger,
hatch or baseline changes. Every source has its own before-object, native
normal/frozen gate, external code/relocation comparison, named static comparison,
and complete non-debug-section comparison including data, EH and linker directives.

Preserved: 65 existing native function/EH rows, 16844 ledger-extent bytes,
596 retained external code instances and 24 named TU-local code
instances. No native coverage, runtime improvement or linked-byte gain is claimed.

- [Repair include inventory in StealthUpdate_allowedToStealthAt002ACD90](b1-01-include-inventory-20261103-1454.md): 2 rows, 18 external code instances.
- [Repair include inventory in Rva21C710Prepare](b1-02-include-inventory-20261103-1454.md): 2 rows, 24 external code instances.
- [Repair include inventory in W3DViewRva00743CE0](b1-03-include-inventory-20261103-1454.md): 2 rows, 4 external code instances.
- [Repair include inventory in BfmeAptScreenSaveLoadConstructor](b1-04-include-inventory-20261103-1454.md): 1 rows, 64 external code instances.
- [Repair include inventory in RoadShaderPixelShader_init](b1-05-include-inventory-20261103-1454.md): 2 rows, 31 external code instances.
- [Repair include inventory in Rva001D48A0Xfer](b1-06-include-inventory-20261103-1454.md): 2 rows, 110 external code instances.
- [Repair include inventory in MainMenuUtils](b1-07-include-inventory-20261103-1454.md): 11 rows, 132 external code instances.
- [Repair include inventory in TurretAI](b1-08-include-inventory-20261103-1454.md): 43 rows, 213 external code instances.

## Selection and scope

The native link pickers were reviewed before choosing this bounded compiler-input
maintenance batch. Repeated unchanged failed body trials are not work credit.

BFME1's current native dry-run picks RefHandle008958D0's destructor COMDAT losers
in ManagerFind/CreateHandle/Dependencies, 846B at index d08539a550. Existing native
records already establish the exact 35B owner at 00784A70 and explain why its
inline-drop copies differ from the kept helper-calling form. The recorded
inline-depth/optimization/source-order trials are not repeated. The pinned donor
is `59e3f8f825b698775df9e1728265fe962a5d0c02`; its relevant source was compared with
current BFME2 `ae346c89bf5570faa12923552858c400788b9c4c`. The key destructor body is
unchanged; current changes import canonical string/allocator declarations and
do not resolve the BFME1 COMDAT/codegen prerequisite. The BFME1 24B object and
free callback differ from BFME2's 28B allocator-owned object. No donor body,
ABI, vtable, alias or address is copied. This review is not a completed repair.
The previous run successfully fetched the native artifact; this run reuses the dated Nov2 13:45 d08539a550 index, not a fresh census.

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
game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_allowedToStealthAt002ACD90.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 748)
  unresolved  ?allow@Rva0025ED50RootFilter@@UAE_NPAVObject@@@Z
  unresolved  ?getClosestObject@PartitionManager@@QAEPAVObject@@PBUCoord3D@@MW4DistanceCalculationType@@PAVPartitionFilter@@@Z
  unresolved  ?getPlayerMask@PartitionFilter@@UAEHXZ
  comdat      ?allowedToStealthAt002ACD90@StealthUpdate@@QBE_NPBUCoord3D@@0@Z  (retail: not retail's body)
  selected    ??0PartitionFilterAcceptByKindOf@@QAE@ABV?$BitFlags@$0MA@@@0@Z  (the definition the link keeps is not retail's)
  selected    ??_7PartitionFilter@@6B@  (the definition the link keeps is not retail's)
  selected    ?allowedToStealthAt002ACD90@StealthUpdate@@QBE_NPBUCoord3D@@0@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Contain/Rva21C710Prepare.cpp: LINKS  LINKED 485 -> 485 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 485)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRva00743CE0.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 950)
  unresolved  ?TheTerrainLogic@@3PAVRva003FD060TerrainLogic@@A
  unresolved  ?g_Va012F9DE4@@3UCoord3D@@A
  unresolved  ?g_Va012F9DF0@@3UCoord3D@@A
  unresolved  ?g_bfmeDefaultEG@@3MB
game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenSaveLoadConstructor.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,707)
  unresolved  ??1FunctorWrapperHead@@UAE@XZ
  unresolved  ?Gen0056C3F0@@YAHHH@Z
  unresolved  ?g_Slot012BF440@@3UBigObfSlot@@A
  unresolved  ?g_saveLoadRegistrations012B7E60@@3PAPBDA
  duplicate   ??0Obf0056D5E0@@QAE@PAH0@Z
  duplicate   ??0Rva0056C9F0FunctorWrapper@@QAE@ABUFunctorBinding@@@Z
  duplicate   ??0Rva0056CA40FunctorWrapper@@QAE@ABUFunctorBinding@@@Z
  duplicate   ?Rva0056DE40@@YAHHH@Z
  comdat      ??_7Rva0056C9F0FunctorWrapper@@6B@  (retail: unproven and differs from the kept copy)
  comdat      ??_7Rva0056CA40FunctorWrapper@@6B@  (retail: unproven and differs from the kept copy)
  comdat      ??_7BfmeAptScreenSaveLoad@@6BBfmeAptScreenSaveLoadSecondary@@@  (retail: not retail's body)
  selected    ??_7BfmeAptScreenSaveLoad@@6BBfmeAptScreenSaveLoadSecondary@@@  (the definition the link keeps is not retail's)
game/GameEngineDevice/Source/W3DDevice/GameClient/RoadShaderPixelShader_init.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 4,110)
  unresolved  ?D3DDevice@DX8Wrapper@@2PAUIDirect3DDevice8@@A
  unresolved  ?Free_String@StringClass@@QAEXXZ
  unresolved  ?Get_String@StringClass@@QAEXH_N@Z
  unresolved  ?Pixel_Shader_Constants@DX8Wrapper@@2PAVVector4@@A
  unresolved  ?Release_Ref@BFMETextureRelease@@QAEXXZ
  unresolved  ?SnapshotActivated@WW3D@@2_NA
  unresolved  ?TextureStageStates@DX8Wrapper@@2PAY0CA@IA
  unresolved  ?g_bfmeAltFE@@3PAHA
  unresolved  ?g_bfmeCh1035@@3DA
  unresolved  ?g_bfmeDefaultFE@@3PAHA
  unresolved  ?g_bfmeFlagsFE@@3PAHA
  unresolved  ?g_bfmePointersFE@@3PAPAHA
  unresolved  ?m_EmptyString@StringClass@@2PADA
  unresolved  ?matrix_changes@DX8Wrapper@@2IA
  unresolved  ?texture_stage_state_changes@DX8Wrapper@@2IA
  duplicate   ?getShroudTexture@W3DShroud@@QAE?AVTextureHandle@@XZ
  duplicate   ?init@RoadShaderPixelShader@@EAEHXZ
  comdat      ??1TextureHandle@@QAE@XZ  (first: differs from the first copy in link order (no retail address))
  selected    ?init@RoadShaderPixelShader@@EAEHXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Rva001D48A0Xfer.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 3,980)
  unresolved  ?TheAI@@3PAXA
  unresolved  ?TheGameLogic@@3PAXA
  unresolved  ?TheTerrainLogic@@3PAXA
  unresolved  ?g_guardTargetTypeThrowInfo@@3HA
  unresolved  ?g_theNameKeyGenerator@@3PAVNameKeyGenerator@@A
  unresolved  ?rva001D48A0Transfer@DamageInfoInput@@UAEXPAVXfer@@@Z
  unresolved  ?rva001D48A0Transfer@DamageInfoOutput@@UAEXPAVXfer@@@Z
  unresolved  _bfmeFormatText
  comdat      ??_7DamageInfoInput@@6B@  (retail: unproven and differs from the kept copy)
  comdat      ??_7DamageInfoOutput@@6B@  (retail: unproven and differs from the kept copy)
  comdat      ??$_Construct@URva001D28F0Element@@U1@@_STL@@YAXPAURva001D28F0Element@@ABU1@@Z  (retail: unproven and differs from the kept copy)
  comdat      ??1?$pair@HVAsciiString@@@_STL@@QAE@XZ  (first: differs from the first copy in link order (no retail address))
game/GameEngine/Source/GameNetwork/GameSpy/MainMenuUtils.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 2,350)
  unresolved  ??0BfmeErasedValue_00627200@@QAE@ABV0@@Z
  unresolved  ?MessageBoxCancel@@YAPAVGameWindow@@VUnicodeString@@0P6AXXZ@Z
  unresolved  ?deallocate@BfmeStartNodeAllocAccess@@SAXPAXI@Z
  unresolved  ?downloadNextQueuedFile@BfmeStartDownloadManager@@QAEJXZ
  unresolved  ?ghttpGet@@YA?AW4GHTTPBool@@PBDW41@P6A?AW41@HW4GHTTPResult@@PADHPAX@Z4@Z
  unresolved  ?ghttpGetHeaders@@YAPADH@Z
  unresolved  ?ghttpHead@@YA?AW4GHTTPBool@@PBDW41@P6A?AW41@HW4GHTTPResult@@PADHPAX@Z4@Z
  unresolved  ?ghttpSetProxy@@YAXPBD@Z
  unresolved  ?queueFileForDownload@BfmeStartDownloadManager@@QAEXVBfmeStartAsciiString@@00000_N@Z
  duplicate   ?trim@AsciiString@@QAEXXZ
  comdat      ?reverseFind@AsciiString@@QBEPBDD@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?nextToken@AsciiString@@QAE_NPAV1@PBD@Z  (retail: not retail's body)
  comdat      ?concat@AsciiString@@QAEXABV1@@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?trim@AsciiString@@QAEXXZ  (retail: not retail's body)
  comdat      ?compare@AsciiString@@QBEHABV1@@Z  (retail: unproven and differs from the kept copy)
  comdat      ??8@YA_NABVAsciiString@@0@Z  (retail: unproven and differs from the kept copy)
  comdat      ??0QueuedDownload@@QAE@ABV0@@Z  (retail: not retail's body)
  comdat      ??$_Construct@VQueuedDownload@@V1@@_STL@@YAXPAVQueuedDownload@@ABV1@@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?_M_create_node@?$list@VQueuedDownload@@V?$allocator@VQueuedDownload@@@_STL@@@_STL@@IAEPAU?$_List_node@VQueuedDownload@@@2@ABVQueuedDownload@@@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ??1?$list@VQueuedDownload@@V?$allocator@VQueuedDownload@@@_STL@@@_STL@@QAE@XZ  (first: differs from the first copy in link order (no retail address))
  selected    ??0QueuedDownload@@QAE@ABV0@@Z  (the definition the link keeps is not retail's)
  selected    ??8@YA_NABVAsciiString@@0@Z  (the definition the link keeps is not retail's)
  selected    ?clear@?$_List_base@VQueuedDownload@@V?$allocator@VQueuedDownload@@@_STL@@@_STL@@QAEXXZ  (the definition the link keeps is not retail's)
  selected    ?isEmpty@AsciiString@@QBE_NXZ  (the definition the link keeps is not retail's)
  selected    ?nextToken@AsciiString@@QAE_NPAV1@PBD@Z  (the definition the link keeps is not retail's)
  selected    ?releaseBuffer@UnicodeString@@IAEXXZ  (the definition the link keeps is not retail's)
  selected    ?trim@AsciiString@@QAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/AI/TurretAI.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 2,330)
  unresolved  __imp_?deallocate@__new_alloc@_STL@@SAXPAXI@Z
  duplicate   ??0AIAttackFireWeaponState@@QAE@PAVStateMachine@@PAVNotifyWeaponFiredInterface@@@Z
  duplicate   ??0TurretAIAimTurretState@@QAE@PAVTurretStateMachine@@@Z
  duplicate   ??0TurretAIHoldTurretState@@QAE@PAVTurretStateMachine@@@Z
  duplicate   ??0TurretAIIdleScanState@@QAE@PAVTurretStateMachine@@@Z
  duplicate   ??0TurretAIIdleState@@QAE@PAVTurretStateMachine@@@Z
  duplicate   ??0TurretAIRecenterTurretState@@QAE@PAVTurretStateMachine@@@Z
  duplicate   ??0TurretState@@IAE@PAVTurretStateMachine@@VAsciiString@@@Z
  duplicate   ?loadPostProcess@TurretAIRecenterTurretState@@MAEXXZ
  duplicate   ?onEnter@TurretAIIdleState@@UAE?AW4StateReturnType@@XZ
  duplicate   ?setTurretTargetObject@TurretAI@@QAEXPAVObject@@_N@Z
  duplicate   ?startRotOrPitchSound@TurretAI@@AAEXXZ
  comdat      ??_7TurretStateMachine@@6B@  (retail: not retail's body)
  comdat      ?startRotOrPitchSound@TurretAI@@AAEXXZ  (retail: not retail's body)
  comdat      ?stopRotOrPitchSound@TurretAI@@AAEXXZ  (retail: not retail's body)
  comdat      ?onEnter@TurretAIIdleState@@UAE?AW4StateReturnType@@XZ  (retail: not retail's body)
  comdat      ??1TurretAI@@MAE@XZ  (retail: not retail's body)
  comdat      ??_7TurretAI@@6BSnapshot@@@  (retail: not retail's body)
  comdat      ?setTurretTargetObject@TurretAI@@QAEXPAVObject@@_N@Z  (retail: not retail's body)
  comdat      ??1State@@MAE@XZ  (first: differs from the first copy in link order (no retail address))
  comdat      ??_7AIAttackFireWeaponState@@6B@  (retail: not retail's body)
  comdat      ??_7TurretState@@6B@  (retail: not retail's body)
  comdat      ??_7TurretAIIdleState@@6B@  (retail: not retail's body)
  comdat      ??_7TurretAIIdleScanState@@6B@  (retail: not retail's body)
  comdat      ??_7TurretAIRecenterTurretState@@6B@  (retail: not retail's body)
  selected    ??0TurretState@@IAE@PAVTurretStateMachine@@VAsciiString@@@Z  (the definition the link keeps is not retail's)
  selected    ??1TurretAI@@MAE@XZ  (the definition the link keeps is not retail's)
  selected    ??_7AIAttackFireWeaponState@@6B@  (the definition the link keeps is not retail's)
  selected    ??_7TurretAI@@6BSnapshot@@@  (the definition the link keeps is not retail's)
  selected    ??_7TurretAIIdleScanState@@6B@  (the definition the link keeps is not retail's)
  selected    ??_7TurretAIIdleState@@6B@  (the definition the link keeps is not retail's)
  selected    ??_7TurretAIRecenterTurretState@@6B@  (the definition the link keeps is not retail's)
  selected    ??_7TurretState@@6B@  (the definition the link keeps is not retail's)
  selected    ??_7TurretStateMachine@@6B@  (the definition the link keeps is not retail's)
  selected    ?findMemoryPool@MemoryPoolFactory@@QAEPAVMemoryPool@@PBD@Z  (the definition the link keeps is not retail's)
  selected    ?freeBlock@MemoryPool@@QAEXPAX@Z  (the definition the link keeps is not retail's)
  selected    ?getNextMoodTarget@AIUpdateInterface@@QAEPAVObject@@_N0@Z  (the definition the link keeps is not retail's)
  selected    ?onEnter@AIAttackFireWeaponState@@UAE?AW4StateReturnType@@XZ  (the definition the link keeps is not retail's)
  selected    ?onEnter@TurretAIIdleState@@UAE?AW4StateReturnType@@XZ  (the definition the link keeps is not retail's)
  selected    ?onExit@AIAttackFireWeaponState@@UAEXW4StateExitType@@@Z  (the definition the link keeps is not retail's)
  selected    ?resetToDefaultState@StateMachine@@UAE?AW4StateReturnType@@XZ  (the definition the link keeps is not retail's)
  selected    ?setGoalObject@StateMachine@@QAEXPBVObject@@@Z  (the definition the link keeps is not retail's)
  selected    ?setState@StateMachine@@UAE?AW4StateReturnType@@I@Z  (the definition the link keeps is not retail's)
  selected    ?setTurretTargetObject@TurretAI@@QAEXPAVObject@@_N@Z  (the definition the link keeps is not retail's)
  selected    ?startRotOrPitchSound@TurretAI@@AAEXXZ  (the definition the link keeps is not retail's)
  selected    ?stopRotOrPitchSound@TurretAI@@AAEXXZ  (the definition the link keeps is not retail's)
  selected    ?update@AIAttackFireWeaponState@@UAE?AW4StateReturnType@@XZ  (the definition the link keeps is not retail's)
link_check: 1 of 8 link cleanly; LINKED 485 -> 485 bytes (119.1s)
```

## Execution and proof limits

The repositories use independent claims, source trees, ledgers and object caches,
so native work ran concurrently between projects. Within each repository, edits,
native cache writes, log writes and commits were sequential. BUILD_POOL=14 each,
up to28 build workers on28 logical CPUs. No local model was required. No measured
serial/parallel speedup is claimed. The already-corrected diagnostic controls are reused; project gates remain unchanged.

This batch repairs compiler include inventories. It does not establish RAM/leak,
crash, FPS or multicore improvements. Full engine linking/gameplay remain unproven.
