# 18 BFME1 include-inventory repairs

Base `e04322a14ea1c21264a54b80bc1f98cd2a2a89a8`. Each source independently removes only its redundant whole-checkout
`/I.` search root and anchors existing includes relative to the source. The
before/after compiler dependency sets resolve to the same physical paths and
hashes, normalizing Windows case and relative path aliases. No source body,
optimization or ABI switch, shared header, native name, pin, alias, ledger,
hatch or baseline changes. Every source has its own before-object, native
normal/frozen gate, external code/relocation comparison, named static comparison,
and complete non-debug-section comparison including data, EH and linker directives.

Preserved: 22 existing native function/EH rows, 11241 ledger-extent bytes,
465 retained external code instances and 11 named TU-local code
instances. No native coverage, runtime improvement or linked-byte gain is claimed.

- [Repair include inventory in ClickReactionBehaviorRva001F7CC0](b1-01-include-inventory-20261103-1239.md): 1 rows, 16 external code instances.
- [Repair include inventory in Rva00896540RefHolderForward](b1-02-include-inventory-20261103-1239.md): 1 rows, 5 external code instances.
- [Repair include inventory in Rva0073B7A0](b1-03-include-inventory-20261103-1239.md): 1 rows, 3 external code instances.
- [Repair include inventory in Rva000AF660Owner](b1-04-include-inventory-20261103-1239.md): 1 rows, 13 external code instances.
- [Repair include inventory in Rva0058D770Rank](b1-05-include-inventory-20261103-1239.md): 1 rows, 5 external code instances.
- [Repair include inventory in Rva00896470RefHolderSubmit](b1-06-include-inventory-20261103-1239.md): 1 rows, 7 external code instances.
- [Repair include inventory in Rva004B2330](b1-07-include-inventory-20261103-1239.md): 1 rows, 6 external code instances.
- [Repair include inventory in Rva00463E30AptWindowShow](b1-08-include-inventory-20261103-1239.md): 1 rows, 29 external code instances.
- [Repair include inventory in Rva004B24F0](b1-09-include-inventory-20261103-1239.md): 2 rows, 10 external code instances.
- [Repair include inventory in Rva00462D40DisableComponents](b1-10-include-inventory-20261103-1239.md): 3 rows, 33 external code instances.
- [Repair include inventory in Rva005C9FC0ParticleManagerXfer](b1-11-include-inventory-20261103-1239.md): 1 rows, 32 external code instances.
- [Repair include inventory in Rva00463850AptWindowCreate](b1-12-include-inventory-20261103-1239.md): 1 rows, 88 external code instances.
- [Repair include inventory in PersistentStorageDataCallback](b1-13-include-inventory-20261103-1239.md): 2 rows, 82 external code instances.
- [Repair include inventory in W3DWaterDraw](b1-14-include-inventory-20261103-1239.md): 1 rows, 13 external code instances.
- [Repair include inventory in AttributeModifierAuraUpdate](b1-15-include-inventory-20261103-1239.md): 1 rows, 76 external code instances.
- [Repair include inventory in Rva007E5080Vp6PlayerOpen](b1-16-include-inventory-20261103-1239.md): 1 rows, 12 external code instances.
- [Repair include inventory in BuildAssistantAddBibs](b1-17-include-inventory-20261103-1239.md): 1 rows, 33 external code instances.
- [Repair include inventory in W3DViewRva00743F80](b1-18-include-inventory-20261103-1239.md): 1 rows, 2 external code instances.

## Selection and scope

The native link pickers were reviewed before choosing this bounded compiler-input
maintenance batch. Repeated unchanged failed body trials are not work credit.

BFME1's current native dry-run picks RefHandle008958D0's destructor COMDAT losers
in ManagerFind/CreateHandle/Dependencies, 846B at index d08539a550. Existing native
records already establish the exact 35B owner at 00784A70 and explain why its
inline-drop copies differ from the kept helper-calling form. The recorded
inline-depth/optimization/source-order trials are not repeated. The pinned donor
is `59e3f8f825b698775df9e1728265fe962a5d0c02`; its relevant source was compared with
current BFME2 `f13dcc93a2910bb6bdbcb067805ea75747038fd1`. The key destructor body is
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
game/GameEngine/Source/GameLogic/Object/Behavior/ClickReactionBehaviorRva001F7CC0.cpp: LINKS  LINKED 208 -> 208 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 208)
game/GameEngine/Source/Common/Rva00896540RefHolderForward.cpp: LINKS  LINKED 111 -> 111 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 111)
game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0073B7A0.cpp: LINKS  LINKED 178 -> 178 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 178)
game/GameEngine/Source/Common/Rva000AF660Owner.cpp: LINKS  LINKED 274 -> 274 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 274)
game/GameEngine/Source/Common/Rva0058D770Rank.cpp: LINKS  LINKED 90 -> 90 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 90)
game/GameEngine/Source/Common/Rva00896470RefHolderSubmit.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 142)
  unresolved  ?g_bfmeTracker4310@@3PAVBfmeTracker4310@@A
  unresolved  ?g_rva013377F0@@3PAVGen_uw_00893e70@@A
game/GameEngine/Source/GameClient/GUI/Rva004B2330.cpp: LINKS  LINKED 252 -> 252 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 252)
game/GameEngine/Source/GameClient/GUI/Rva00463E30AptWindowShow.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 466)
  unresolved  ?TheBfmeObject_00C70090@@3VGen_00C70090Target@@A
  comdat      ??8@YA_NABVAsciiString@@0@Z  (retail: unproven and differs from the kept copy)
  comdat      ??R?$equal_to@VAsciiString@@@_STL@@QBE_NABVAsciiString@@0@Z  (retail: not retail's body)
  comdat      ?set@AsciiString@@QAEXPBD@Z  (retail: not retail's body)
  comdat      ??$_M_find@VAsciiString@@@?$hashtable@URva00460B30Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva00460B30ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva00460B30Value@@@7@@_STL@@ABEPAU?$_Hashtable_node@URva00460B30Value@@@1@ABVAsciiString@@@Z  (retail: not retail's body)
  selected    ??8@YA_NABVAsciiString@@0@Z  (the definition the link keeps is not retail's)
  selected    ?isEmpty@AsciiString@@QBE_NXZ  (the definition the link keeps is not retail's)
  selected    ?set@AsciiString@@QAEXPBD@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameClient/GUI/Rva004B24F0.cpp: LINKS  LINKED 178 -> 178 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 178)
game/GameEngine/Source/GameClient/GUI/Rva00462D40DisableComponents.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 351)
  duplicate   ??1BFMERetailAsciiString@@QAE@XZ
  comdat      ??0BFMERetailAsciiString@@QAE@ABV0@@Z  (retail: not retail's body)
  comdat      ??$for_each@U?$_Ht_iterator@URva0045F0A0Input@@U?$_Nonconst_traits@URva0045F0A0Input@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva0045F0A0ExtractKey@@U?$equal_to@VAsciiString@@@3@V?$allocator@URva0045F0A0Input@@@3@@_STL@@VRva0045F0A0@@@_STL@@YA?AVRva0045F0A0@@U?$_Ht_iterator@URva0045F0A0Input@@U?$_Nonconst_traits@URva0045F0A0Input@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva0045F0A0ExtractKey@@U?$equal_to@VAsciiString@@@3@V?$allocator@URva0045F0A0Input@@@3@@0@0V1@@Z  (retail: not retail's body)
  selected    ??0BFMERetailAsciiString@@QAE@ABV0@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameClient/System/Rva005C9FC0ParticleManagerXfer.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 748)
  unresolved  ?createParticleSystem@ParticleSystemManager@FXParticleSystem@@QAE?AVParticleSystemHandle@@PBVParticleSystemTemplate@2@_N@Z
  comdat      ??8@YA_NABVAsciiString@@0@Z  (retail: unproven and differs from the kept copy)
  comdat      ??R?$equal_to@VAsciiString@@@_STL@@QBE_NABVAsciiString@@0@Z  (retail: not retail's body)
  comdat      ??$_M_find@VAsciiString@@@?$hashtable@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@U?$equal_to@VAsciiString@@@2@V?$allocator@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@@_STL@@ABEPAU?$_Hashtable_node@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@1@ABVAsciiString@@@Z  (retail: not retail's body)
  selected    ??8@YA_NABVAsciiString@@0@Z  (the definition the link keeps is not retail's)
  selected    ?isEmpty@AsciiString@@QBE_NXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameClient/GUI/Rva00463850AptWindowCreate.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 669)
  unresolved  ?TheBfmeObject_00C70080@@3VGen_00C70080Target@@A
  unresolved  ?g_Va012F198C@@3PAXA
  comdat      ?toLower@AsciiString@@QAEXXZ  (retail: not retail's body)
  comdat      ?compare@AsciiString@@QBEHABV1@@Z  (retail: unproven and differs from the kept copy)
  comdat      ??8@YA_NABVAsciiString@@0@Z  (retail: unproven and differs from the kept copy)
  comdat      ??R?$equal_to@VAsciiString@@@rts@@QBE_NABVAsciiString@@0@Z  (retail: unproven and differs from the kept copy)
  comdat      ?allocate@?$allocator@PAX@_STL@@QAEPAPAXIPBX@Z  (retail: not retail's body)
  comdat      ?deallocate@?$allocator@PAX@_STL@@QAEXPAPAXI@Z  (retail: not retail's body)
  comdat      ??0?$_Vector_base@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@IABV?$allocator@PAX@1@@Z  (retail: not retail's body)
  comdat      ??1?$_Vector_base@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ??$_M_find@VAsciiString@@@?$hashtable@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@2@@_STL@@ABEPAU?$_Hashtable_node@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@1@ABVAsciiString@@@Z  (retail: not retail's body)
  comdat      ??1?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAE@XZ  (retail: not retail's body)
  comdat      ?resize@?$hashtable@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@2@@_STL@@QAEXI@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?_M_insert@?$hashtable@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@2@@_STL@@QAEAAU?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@2@ABU32@@Z  (retail: not retail's body)
  comdat      ??A?$hash_map@VAsciiString@@VRva0045EF90Object@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@4@V?$allocator@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@_STL@@@_STL@@QAEAAVRva0045EF90Object@@ABVAsciiString@@@Z  (retail: not retail's body)
  selected    ??$_M_find@VAsciiString@@@?$hashtable@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@2@@_STL@@ABEPAU?$_Hashtable_node@U?$pair@$$CBVAsciiString@@VRva0045EF90Object@@@_STL@@@1@ABVAsciiString@@@Z  (the definition the link keeps is not retail's)
  selected    ??8@YA_NABVAsciiString@@0@Z  (the definition the link keeps is not retail's)
  selected    ?toLower@AsciiString@@QAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageDataCallback.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,841)
  comdat      ?_M_erase@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@M@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@M@_STL@@@2@@Z  (retail: not retail's body)
  selected    ?_M_erase@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@M@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@M@_STL@@@3@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBW4NameKeyType@@M@_STL@@@2@@Z  (the definition the link keeps is not retail's)
  selected    ?parsePlayerKVPairs@GameSpyPSMessageQueueInterface@@SA?AVPSPlayerStats@@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z  (the definition the link keeps is not retail's)
game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWaterDraw.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 2,257)
  unresolved  ?D3DDevice@DX8Wrapper@@2PAUIDirect3DDevice8@@A
  unresolved  ?Pixel_Shader_Constants@DX8Wrapper@@2PAVVector4@@A
  unresolved  ?ShaderDirty@ShaderClass@@2_NA
  unresolved  ?SnapshotActivated@WW3D@@2_NA
  unresolved  ?TextureStageStates@DX8Wrapper@@2PAY0CA@IA
  unresolved  ?bfmeTwoRB@@YAXHH@Z
  unresolved  ?matrix_changes@DX8Wrapper@@2IA
  unresolved  ?render_state@DX8Wrapper@@2URenderStateStruct@@A
  unresolved  ?render_state_changed@DX8Wrapper@@2IA
  unresolved  ?texture_stage_state_changes@DX8Wrapper@@2IA
  comdat      ?Set_Material@DX8Wrapper@@SAXPBVVertexMaterialClass@@@Z  (retail: unproven and differs from the kept copy)
  comdat      ?Set_Shader@DX8Wrapper@@SAXABVShaderClass@@@Z  (retail: unproven and differs from the kept copy)
game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierAuraUpdate.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,471)
  unresolved  ?allow@Rva0025ED50ObjectFilter@@UAE_NPAVObject@@@Z
  unresolved  ?allow@Rva0025ED50RootFilter@@UAE_NPAVObject@@@Z
  unresolved  ?allow@Rva0025F2D0KindOfAnyFilter@@UAE_NPAVObject@@@Z
  unresolved  ?allow@Rva00265150RJFilter@@UAE_NPAVObject@@@Z
  unresolved  ?getPlayerMask@PartitionFilter@@UAEHXZ
  unresolved  ?getPlayerMask@PartitionFilterRelationship@@UAEHXZ
  unresolved  ?isAnyKindOf@Thing@@QBE_NABUKindOfMask@@@Z
  unresolved  ?iterate@PartitionManager@@QAE?AURva0025ED50WideResult@@PBUCoord3D@@MW4IterOrderType@@PAVPartitionFilter@@_N@Z
  unresolved  ?queryAt00880E60@BfmeTaintManager@@QAEHPBUCoord3D@@@Z
  comdat      ??_7PartitionFilterRelationship@@6B@  (retail: unproven and differs from the kept copy)
  selected    ??_7PartitionFilter@@6B@  (the definition the link keeps is not retail's)
  selected    ??_7PartitionFilterRelationship@@6B@  (the definition the link keeps is not retail's)
  selected    ?isEmpty@AsciiString@@QBE_NXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/Common/Rva007E5080Vp6PlayerOpen.cpp: LINKS  LINKED 733 -> 733 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 733)
game/GameEngine/Source/Common/System/BuildAssistantAddBibs.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 451)
  duplicate   ?addBibs@BuildAssistant@@UAEXPBUCoord3D@@PBVThingTemplate@@@Z
  duplicate   ?isRemovableForConstruction@BuildAssistant@@IAE_NPAVObject@@@Z
  comdat      ?friend_calcVisionRange@ThingTemplate@@QBEMXZ  (retail: not retail's body)
  comdat      ?getTemplate@Thing@@QBEPBVThingTemplate@@XZ  (retail: not retail's body)
  comdat      ??_7PartitionFilter@@6B@  (retail: unproven and differs from the kept copy)
  comdat      ??_7PartitionFilterAcceptByKindOf@@6B@  (retail: unproven and differs from the kept copy)
  comdat      ?isRemovableForConstruction@BuildAssistant@@IAE_NPAVObject@@@Z  (retail: not retail's body)
  comdat      ??0?$BitFlags@$0MA@@@QAE@W4BogusInitType@0@H@Z  (retail: not retail's body)
  comdat      ??1BfmeWideResult@@QAE@XZ  (retail: unproven and differs from the kept copy)
  selected    ??0PartitionFilterAcceptByKindOf@@QAE@ABV?$BitFlags@$0MA@@@0@Z  (the definition the link keeps is not retail's)
  selected    ??_7PartitionFilter@@6B@  (the definition the link keeps is not retail's)
  selected    ?addBibs@BuildAssistant@@UAEXPBUCoord3D@@PBVThingTemplate@@@Z  (the definition the link keeps is not retail's)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRva00743F80.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 789)
  unresolved  ?BfmeCameraGlobal12F9DBC@@3MA
  unresolved  ?g_Va012BB1D8@@3MA
  unresolved  ?g_Va012BB1DC@@3MA
  unresolved  ?g_Va012BB1E0@@3MA
  unresolved  ?g_Va012BB1E4@@3MA
  unresolved  ?g_Va012BB1E8@@3MA
  unresolved  ?g_Va012BB1F8@@3MA
  unresolved  ?g_Va012BB1FC@@3MA
  unresolved  ?g_Va012BB200@@3MA
  unresolved  ?g_Va012BB204@@3MA
  unresolved  ?g_Va012BB218@@3_NA
  unresolved  ?g_Va012F9DDC@@3MA
  unresolved  ?g_Va012F9DE0@@3MA
  unresolved  ?g_Va012F9E28@@3PAURva012F9E28Fields@@A
  unresolved  ?g_bfmeFlagEC@@3_NA
link_check: 8 of 18 link cleanly; LINKED 2,024 -> 2,024 bytes (256.1s)
```

## Execution and proof limits

The repositories use independent claims, source trees, ledgers and object caches,
so native work ran concurrently between projects. Within each repository, edits,
native cache writes, log writes and commits were sequential. BUILD_POOL=14 each,
up to28 build workers on28 logical CPUs. No local model was required. No measured
serial/parallel speedup is claimed. The already-corrected diagnostic controls are reused; project gates remain unchanged.

This batch repairs compiler include inventories. It does not establish RAM/leak,
crash, FPS or multicore improvements. Full engine linking/gameplay remain unproven.
