# BFME1 verified source batch

Base `77a8439ee4bde1c902f2059f5d77ff4ed307c4b7`. 20 source tasks; 25 retained code/EH rows,
4960 summed ledger-extent bytes and 116 external code definitions.
These are existing matches, not new authored coverage.

Replace 20 independently compiled data-only coordinate views with
their existing BFME1 header. Native CodeView proves the struct/field layout;
complete ordered runtime sections, external/local code and relocations remain
identical. Every prior resolved header path/hash remains; only the canonical
header is added. Native private-view counts: {'Coord2D': 29, 'Coord3D': 611} -> {'Coord2D': 29, 'Coord3D': 591}.
The verified BFME2 reference refresh is recorded separately in
donor-refresh-20261104-1410.md. No donor header or compiler setting is imported.

Linking was reviewed first. W3DMouse's served BFME2 blocker is already fixed
upstream, so no credit is taken for it. BFME1's movement-provider prerequisite
remains documented with the refreshed donor. Native scoped dated prediction:

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
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_internalCancelTask.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 82)
  selected    ?aiMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/Common/Glo012F1028Type_Rva003BDA10.cpp: LINKS  LINKED 181 -> 181 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 181)
game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_doFXListAtBone.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 135)
  unresolved  ?convertBonePosToWorldPos@Object@@QBEXPBUCoord3D@@PBVMatrix3D@@PAU2@PAV3@@Z
  duplicate   ?doFXListAtBone@BoneFXUpdate@@IAEXPBVFXList@@PBUCoord3D@@@Z
  selected    ?doFXListAtBone@BoneFXUpdate@@IAEXPBVFXList@@PBUCoord3D@@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/Weapon_isClearGoalFiringLineOfSightTerrain_Object.cpp: LINKS  LINKED 197 -> 197 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 197)
game/GameEngine/Source/GameLogic/ScriptEngine/Condition_setConditionType_Thunk.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 259)
  duplicate   ?setConditionType@Condition@@QAEXW4ConditionType@1@@Z
  selected    ??0Parameter@@QAE@W4ParameterType@0@H@Z  (the definition the link keeps is not retail's)
  selected    ?setConditionType@Condition@@QAEXW4ConditionType@1@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameLogic/Object/WeaponStore_createAndFireTempWeapon.cpp: LINKS  LINKED 302 -> 302 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 302)
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveCameraTo.cpp: LINKS  LINKED 184 -> 184 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 184)
game/GameEngine/Source/Common/BfmeConv2090.cpp: LINKS  LINKED 212 -> 212 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 212)
game/GameEngine/Source/GameLogic/Object/Update/Rva00267D00.cpp: LINKS  LINKED 102 -> 102 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 102)
game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitGuardPosition.cpp: LINKS  LINKED 111 -> 111 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 111)
game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00767DB0Fx.cpp: LINKS  LINKED 292 -> 292 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 292)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModFinalZoomBfme.cpp: LINKS  LINKED 321 -> 321 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 321)
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewShakeBfme.cpp: LINKS  LINKED 272 -> 272 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 272)
game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdSwoopStateOnExit.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 176)
  unresolved  ?updateGoal@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@HPBDH@Z
  selected    ?removeGoal@Pathfinder@@QAEXPAVObject@@@Z  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameClient/MapCacheAddMap.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 1,391)
  unresolved  ?Rva012F158C@@3HA
  unresolved  ?Rva012F1590@@3HA
  unresolved  ?TheBfmeObject_00C6FFF0@@3VGen_00C6FFF0Target@@A
  unresolved  ?TheBfmeObject_00C70010@@3VGen_00C70010Target@@A
  unresolved  ?TheBfmeObject_00C70020@@3VGen_00C70020Target@@A
  unresolved  ?g_Va012A79A0@@3VStaticNameKey@@A
  unresolved  ?g_Va012A79A8@@3VStaticNameKey@@A
  unresolved  ?g_Va012A79E8@@3VStaticNameKey@@A
  unresolved  ?resetMap@@YAXXZ
  duplicate   ?addMap@MapCache@@AAE_NVAsciiString@@0PAUFileInfo@@_N@Z
  comdat      ?toLower@AsciiString@@QAEXXZ  (retail: not retail's body)
  comdat      ?concat@AsciiString@@QAEXPBD@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?concat@AsciiString@@QAEXD@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?reverseFind@AsciiString@@QBEPBDD@Z  (first: differs from the first copy in link order (no retail address))
  selected    ??0MapMetaData@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ??1MapMetaData@@QAE@XZ  (the definition the link keeps is not retail's)
  selected    ??4MapMetaData@@QAEAAV0@ABV0@@Z  (the definition the link keeps is not retail's)
  selected    ?addMap@MapCache@@AAE_NVAsciiString@@0PAUFileInfo@@_N@Z  (the definition the link keeps is not retail's)
  selected    ?calcCRC@@YAIVAsciiString@@0@Z  (the definition the link keeps is not retail's)
  selected    ?isEmpty@AsciiString@@QBE_NXZ  (the definition the link keeps is not retail's)
  selected    ?toLower@AsciiString@@QAEXXZ  (the definition the link keeps is not retail's)
game/GameEngine/Source/GameClient/System/FXParticleSystem/TerrainCollisionSlot1.cpp: LINKS  LINKED 174 -> 174 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 174)
game/GameEngine/Source/GameLogic/AI/AIStateMachineDestructor.cpp: LINKS  LINKED 107 -> 107 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 107)
game/GameEngine/Source/GameLogic/AI/Rva00174730State_update.cpp: LINKS  LINKED 158 -> 158 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 158)
game/GameEngine/Source/GameLogic/Object/Body/PorcupineFormationBodyModuleApply.cpp: LINKS  LINKED 142 -> 142 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 142)
game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva0025D6E0FreezingRainApply.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-11-03 13:29 at aafdf413e9; file's own bytes 148)
  unresolved  ?bfmeRunCOF@BfmeThingCOF@@QAEXPAX000@Z
  unresolved  ?bfmeStopAZC@BfmeModeAZC@@QAEXH@Z
  unresolved  ?g_bfmeModeAZC@@3PAUBfmeModeAZC@@A
link_check: 14 of 20 link cleanly; LINKED 2,755 -> 2,755 bytes (132.9s)
```

This is not a fresh census or a full-image link. No game run, memory/leak/crash,
64-bit, FPS or multicore improvement is demonstrated. Independent projects
can verify concurrently; per-repository edits, cache writes and publication
remain sequential. BUILD_POOL14 each, no local model.

- [Adopt canonical Coord3D in WorkerAIUpdate_internalCancelTask](b1-01-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in Glo012F1028Type_Rva003BDA10](b1-02-coordinate-header-20261104-1410.md): 2 retained rows.

- [Adopt canonical Coord3D in BoneFXUpdate_doFXListAtBone](b1-03-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in Weapon_isClearGoalFiringLineOfSightTerrain_Object](b1-04-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in Condition_setConditionType_Thunk](b1-05-coordinate-header-20261104-1410.md): 2 retained rows.

- [Adopt canonical Coord3D in WeaponStore_createAndFireTempWeapon](b1-06-coordinate-header-20261104-1410.md): 3 retained rows.

- [Adopt canonical Coord3D in ScriptActions_doMoveCameraTo](b1-07-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in BfmeConv2090](b1-08-coordinate-header-20261104-1410.md): 2 retained rows.

- [Adopt canonical Coord3D in Rva00267D00](b1-09-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in ScriptActions_doUnitGuardPosition](b1-10-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in Rva00767DB0Fx](b1-11-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in W3DViewCameraModFinalZoomBfme](b1-12-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in W3DViewShakeBfme](b1-13-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in AIGiantBirdSwoopStateOnExit](b1-14-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in MapCacheAddMap](b1-15-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in TerrainCollisionSlot1](b1-16-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in AIStateMachineDestructor](b1-17-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in Rva00174730State_update](b1-18-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in PorcupineFormationBodyModuleApply](b1-19-coordinate-header-20261104-1410.md): 1 retained rows.

- [Adopt canonical Coord3D in Rva0025D6E0FreezingRainApply](b1-20-coordinate-header-20261104-1410.md): 1 retained rows.


Additional current selected-provider review: native linking still serves
aiMoveToPosition, wrong_selected/1826 estimated bytes in five files at
aafdf413e9. The fresh donor linking packet names SlavedUpdateRepair.cpp.
Its current /GX profile keeps an explicit noinline visible method body over
a C0 struct command block and direct coordinate-buffer free; that visibility
supports the documented escape-analysis need. It does not supply a measured
replacement for BFME1's 180-byte extra copy or reconcile the219-byte owner,
different DamageInfo/layout and local STL allocator context. The donor's
recent commits2600bf0767 and6783b36cf8 adopt MiscAudio and PathNode; they do
not remove this movement body. No same-name/provider-clean result is treated
as target ABI proof and no unchanged exhausted body variant is rerun.
Reviewed source SHA256: a5a18492070ef9b1afae5f0d419afab7fa206c0b80580f76d5afa5bcbe8c5f8a.
