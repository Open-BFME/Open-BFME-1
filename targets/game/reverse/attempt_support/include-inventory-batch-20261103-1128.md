# 18 BFME1 include-inventory repairs

Base `e14c32bc812e72944777566303abbc555c13278a`. Each source independently removes only its redundant whole-checkout
`/I.` search root and anchors existing includes relative to the source. The
before/after compiler dependency sets resolve to the same physical paths and
hashes, normalizing Windows case and relative path aliases. No source body,
optimization or ABI switch, shared header, native name, pin, alias, ledger,
hatch or baseline changes. Every source has its own before-object, native
normal/frozen gate, external code/relocation comparison, named static comparison,
and complete non-debug-section comparison including data, EH and linker directives.

Preserved: 23 existing native function/EH rows, 7442 ledger-extent bytes,
257 retained external code instances and 7 named TU-local code
instances. No native coverage, runtime improvement or linked-byte gain is claimed.

- [Repair include inventory in Rva00694130AudioWorker](b1-01-include-inventory-20261103-1128.md): 3 rows, 5 external code instances.
- [Repair include inventory in EmotionTrackerUpdateNearbyFilter](b1-02-include-inventory-20261103-1128.md): 1 rows, 6 external code instances.
- [Repair include inventory in Rva002C4EA0RepairContained](b1-03-include-inventory-20261103-1128.md): 1 rows, 11 external code instances.
- [Repair include inventory in Rva009412F0GetCharData](b1-04-include-inventory-20261103-1128.md): 1 rows, 4 external code instances.
- [Repair include inventory in Rva002C4CC0](b1-05-include-inventory-20261103-1128.md): 1 rows, 3 external code instances.
- [Repair include inventory in Rva004B2260](b1-06-include-inventory-20261103-1128.md): 2 rows, 3 external code instances.
- [Repair include inventory in Rva00372E40](b1-07-include-inventory-20261103-1128.md): 1 rows, 21 external code instances.
- [Repair include inventory in Rva007E4D40MovieInit](b1-08-include-inventory-20261103-1128.md): 1 rows, 7 external code instances.
- [Repair include inventory in DozerAIUpdateFindGoodBuildOrRepairPosition](b1-09-include-inventory-20261103-1128.md): 1 rows, 11 external code instances.
- [Repair include inventory in Rva00363050LivingWorldEntryUpdate](b1-10-include-inventory-20261103-1128.md): 1 rows, 11 external code instances.
- [Repair include inventory in Rva0040F160](b1-11-include-inventory-20261103-1128.md): 1 rows, 2 external code instances.
- [Repair include inventory in parseInputCallback_Thunk](b1-12-include-inventory-20261103-1128.md): 3 rows, 10 external code instances.
- [Repair include inventory in GlobalLanguageInitBfme](b1-13-include-inventory-20261103-1128.md): 1 rows, 29 external code instances.
- [Repair include inventory in Rva0065B350XKResponse](b1-14-include-inventory-20261103-1128.md): 1 rows, 63 external code instances.
- [Repair include inventory in AptPalantirHeroSelectorRva00592130](b1-15-include-inventory-20261103-1128.md): 1 rows, 31 external code instances.
- [Repair include inventory in BufferedStreamAttach006B5900](b1-16-include-inventory-20261103-1128.md): 1 rows, 10 external code instances.
- [Repair include inventory in Rva0015A960FormationProcess](b1-17-include-inventory-20261103-1128.md): 1 rows, 6 external code instances.
- [Repair include inventory in W3DViewRva00744360](b1-18-include-inventory-20261103-1128.md): 1 rows, 24 external code instances.

## Selection and scope

The native link pickers were reviewed before choosing this bounded compiler-input
maintenance batch. Repeated unchanged failed body trials are not work credit.

BFME1's current native dry-run picks RefHandle008958D0's destructor COMDAT losers
in ManagerFind/CreateHandle/Dependencies, 846B at index d08539a550. Existing native
records already establish the exact 35B owner at 00784A70 and explain why its
inline-drop copies differ from the kept helper-calling form. The recorded
inline-depth/optimization/source-order trials are not repeated. The pinned donor
is `59e3f8f825b698775df9e1728265fe962a5d0c02`; its relevant source was compared with
current BFME2 `af2bef90c6786c7cd2deffa60594a0bcdda519ae`. The key destructor body is
unchanged; current changes import canonical string/allocator declarations and
do not resolve the BFME1 COMDAT/codegen prerequisite. The BFME1 24B object and
free callback differ from BFME2's 28B allocator-owned object. No donor body,
ABI, vtable, alias or address is copied. This review is not a completed repair.
The previous AnimateWindowManager target has changed upstream; no credit for
that other contributor's work is taken here. The native artifact fetch now
succeeds and still supplies the dated Nov2 13:45 d08539a550 index, not a fresh census.

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
game/GameEngineDevice/Source/MilesAudioDevice/Rva00694130AudioWorker.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 236)
  comdat      ?rva00693B90@Rva00694710AudioWorker@@QAE?AVRva006910F0Handle@@ABVAsciiString@@H@Z  (retail: not retail's body)
  selected    ?rva00693B90@Rva00694710AudioWorker@@QAE?AVRva006910F0Handle@@ABVAsciiString@@H@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdateNearbyFilter.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 208)
  unresolved  ??1Rva0028F2A0Base@@UAE@XZ
  unresolved  ?TheShroudManager@@3PAVPartitionManager@@A
  unresolved  ?allow@Rva010BE170@@UAE_NPAVObject@@@Z
  unresolved  ?lookup@Rva002EEDA0ShroudManager@@QAEHPBUCoord3D@@HI@Z
  unresolved  ?playerMask@Rva0028F2A0Base@@UAEHXZ
  unresolved  ?playerMask@Rva010BE170@@UAEHXZ
game/GameEngine/Source/Common/Rva002C4EA0RepairContained.cpp: LINKS  LINKED 239 -> 239 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 239)
game/Libraries/Source/WWVegas/WW3D2/Rva009412F0GetCharData.cpp: LINKS  LINKED 260 -> 260 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 260)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002C4CC0.cpp: LINKS  LINKED 383 -> 383 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 383)
game/GameEngine/Source/GameClient/GUI/Rva004B2260.cpp: LINKS  LINKED 109 -> 109 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 109)
game/GameEngine/Source/GameLogic/Object/Behavior/Rva00372E40.cpp: LINKS  LINKED 279 -> 279 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 279)
game/GameEngine/Source/Common/Rva007E4D40MovieInit.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 666)
  unresolved  ?TheBfmeObject_00C70BC0@@3VGen_00C70BC0Target@@A
  unresolved  ?g_Va01307438@@3PAIA
  unresolved  ?g_Va01307838@@3PAHA
  unresolved  ?g_Va01307C38@@3PAHA
  unresolved  ?g_Va01308038@@3PAHA
  unresolved  ?g_Va01308438@@3PAHA
  unresolved  ?g_Va01308838@@3PAIA
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateFindGoodBuildOrRepairPosition.cpp: LINKS  LINKED 445 -> 445 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 445)
game/GameEngine/Source/Common/Rva00363050LivingWorldEntryUpdate.cpp: LINKS  LINKED 307 -> 307 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 307)
game/GameEngine/Source/GameClient/Rva0040F160.cpp: LINKS  LINKED 200 -> 200 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 200)
game/GameEngine/Source/GameClient/GUI/parseInputCallback_Thunk.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 390)
  unresolved  ?TheBfmeObject_00C700B0@@3VGen_00C700B0Target@@A
  unresolved  ?TheParsedCallbackResult@@3PAXA
  unresolved  ?g_Va012F2554@@3PAXA
  unresolved  ?g_Va012F2558@@3PAXA
  unresolved  ?unidentified_00025CD4@WindowLookupShim@@QAEPAXHH@Z
game/GameEngine/Source/GameClient/GlobalLanguageInitBfme.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 973)
  unresolved  ?g_Va012B53A8@@3PBDB
  unresolved  ?loadFile@INI@@QAEXVAsciiString@@W4INILoadType@@PAVXfer@@@Z
game/GameEngine/Source/GameNetwork/Rva0065B350XKResponse.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 1,534)
  duplicate   ?trim@AsciiString@@QAEXXZ
  comdat      ?nextToken@AsciiString@@QAE_NPAV1@PBD@Z  (retail: not retail's body)
  comdat      ?toLower@AsciiString@@QAEXXZ  (retail: not retail's body)
  comdat      ?trim@AsciiString@@QAEXXZ  (retail: not retail's body)
  comdat      ?getCharAt@AsciiString@@QBEDH@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ??$find@PAX@?$_Rb_tree@PAXU?$pair@QAXPAX@_STL@@U?$_Select1st@U?$pair@QAXPAX@_STL@@@2@U?$less@PAX@2@V?$allocator@U?$pair@QAXPAX@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@QAXPAX@_STL@@U?$_Nonconst_traits@U?$pair@QAXPAX@_STL@@@2@@1@ABQAX@Z  (retail: not retail's body)
  selected    ??$find@PAX@?$_Rb_tree@PAXU?$pair@QAXPAX@_STL@@U?$_Select1st@U?$pair@QAXPAX@_STL@@@2@U?$less@PAX@2@V?$allocator@U?$pair@QAXPAX@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@QAXPAX@_STL@@U?$_Nonconst_traits@U?$pair@QAXPAX@_STL@@@2@@1@ABQAX@Z  (the definition the link keeps is not retail's)
  selected    ?isEmpty@AsciiString@@QBE_NXZ  (the definition the link keeps is not retail's)
  selected    ?nextToken@AsciiString@@QAE_NPAV1@PBD@Z  (the definition the link keeps is not retail's)
  selected    ?toLower@AsciiString@@QAEXXZ  (the definition the link keeps is not retail's)
  selected    ?trim@AsciiString@@QAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameClient/GUI/Palantir/AptPalantirHeroSelectorRva00592130.cpp: LINKS  LINKED 265 -> 265 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 265)
game/GameEngineDevice/Source/MilesAudioDevice/BufferedStreamAttach006B5900.cpp: LINKS  LINKED 303 -> 303 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 303)
game/GameEngine/Source/Common/Rva0015A960FormationProcess.cpp: LINKS  LINKED 278 -> 278 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 278)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRva00744360.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-02 13:45 at d08539a550; file's own bytes 357)
  unresolved  ?castRay@RTS3DScene@@QAE_NAAVRayCollisionTestClass@@_NH@Z
  comdat      ?getObject@Drawable@@QAEPAVObject@@XZ  (first: differs from the first copy in link order (no retail address))
  comdat      ??0RayCollisionTestClass@@QAE@ABVLineSegClass@@PAUCastResultStruct@@H_N2@Z  (retail: not retail's body)
link_check: 11 of 18 link cleanly; LINKED 3,068 -> 3,068 bytes (131.2s)
```

## Execution and proof limits

The repositories use independent claims, source trees, ledgers and object caches,
so native work ran concurrently between projects. Within each repository, edits,
native cache writes, log writes and commits were sequential. BUILD_POOL=14 each,
up to28 build workers on28 logical CPUs. No local model was required. No measured
serial/parallel speedup is claimed. The diagnostic first pass corrected its own
cross-project command assumption and Windows path-alias comparison; project
gates were never weakened and original sources were restored before the corrected run.

This batch repairs compiler include inventories. It does not establish RAM/leak,
crash, FPS or multicore improvements. Full engine linking/gameplay remain unproven.
