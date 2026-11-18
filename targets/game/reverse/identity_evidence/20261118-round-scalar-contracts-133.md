# Scalar alias contracts: cohort 133

One task replaces one consumer file's grouped private primitive typedefs
with the existing EA/BFME1 contract. Individual typedefs are not counted as
separate tasks. Only exact primitive spellings already present in both the
native BFME1 Precompiled/PreRTS.h and the EA BaseType.h qualify. Char remains
char, unsigned types remain unsigned, and no 64-bit/platform modernization is
inferred. Original provider headers are preserved. The narrow shared header
contains only the nine original scalar typedefs, without macros or runtime code.

Actual original source filenames compile into explicit private ordinary and Z7
controls before any edit. After adoption the normal build passes. Its complete
ordinary runtime inventory equals the actual pre-edit object: code, data,
definitions, relocations, raw directives, weak references and aliases. A fresh
actual-source ordinary object also equals the normal build object. All original
complete class contracts and all original enums remain identical in actual
Z7 records. Real-header traces and opened-input hashes are retained.

Additional private functions bind pointers to each adopted alias and return its
sizeof. Complete witness symbol names and bodies must remain identical, proving
primitive type identity and size even for aliases that contribute no runtime
instructions. A negative control changes unused Int from int to unsigned int:
ordinary runtime remains identical, but the exact primitive witness rejects it.
Witness code exists only in explicit diagnostic outputs. It is not game source,
retail identity evidence or authored-byte progress. CPP files included by other
CPPs are excluded unless all parent/namespace contexts are independently proven.

This source consistency work adds no newly reconstructed function bytes and
makes no crash, RAM/leak, FPS, multicore or runtime-start claim. No verifier,
baseline, pin, EH label or alias is weakened or manually altered. Linking is
separate; absent dependency receipts remain UNKNOWN for provider freshness.

|Task|Consumer|Grouped aliases|Rows|Retained row bytes|
|---|---|---|---:|---:|
|2344|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_appendSequentialScript.cpp`|Bool, Int|1|230|
|2345|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainMarkAllPassengersDetected.cpp`|Bool, UnsignedInt|1|177|
|2346|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainGetNaturalRallyPoint.cpp`|Int, Bool|1|201|
|2347|`game/GameEngine/Source/GameLogic/System/GameLogicValidateBeaconPosition.cpp`|Bool, Real|1|160|
|2348|`game/GameEngine/Source/GameLogic/Object/Update/Rva00267930FloatUpdate.cpp`|Bool, Int|1|171|
|2349|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva00733000.cpp`|Int, Real|1|397|
|2350|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_reset.cpp`|Bool, Int|1|120|
|2351|`game/GameEngine/Source/Common/System/SaveGame/GameStateIterateSaveFiles.cpp`|Bool, Char, Int|1|346|
|2352|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00238740Lookup.cpp`|Int, UnsignedShort|1|232|
|2353|`game/GameEngine/Source/GameLogic/System/BfmeCellRva001DE2A0.cpp`|Int, Real|1|189|
|2354|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ReplayMenuUpdate.cpp`|Bool, Int|1|277|
|2355|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva00324210PlayerCondition.cpp`|Bool, Int|1|172|
|2356|`game/GameEngine/Source/Common/INI/AudioEventInfoParseVolumeSliderMultiplier.cpp`|Int, Real|1|254|
|2357|`game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCache.cpp`|UnsignedInt, UnsignedByte|1|115|
|2358|`game/GameEngine/Source/GameLogic/AI/PathHasMissingWaypoint.cpp`|Bool, UnsignedInt|1|59|
|2359|`game/GameEngine/Source/GameLogic/Object/Contain/ContainModuleInterfaceGetStatus.cpp`|Bool, Int|1|98|
|2360|`game/GameEngine/Source/Common/RTS/TunnelTracker_ctor.cpp`|Int, UnsignedInt, Bool|1|140|
|2361|`game/GameEngine/Source/GameNetwork/DisconnectManager_getVotesNeededToKick.cpp`|Int, Bool|1|81|
|2362|`game/GameEngine/Source/GameNetwork/DisconnectManager_populateDisconnectScreen_Thunk.cpp`|Int, UnsignedInt|1|189|
|2363|`game/GameEngine/Source/GameLogic/Map/TerrainLogic_findClosestEdgePoint.cpp`|Real, Int|1|253|
|2364|`game/GameEngine/Source/Common/System/GeometryInfoConstructor.cpp`|Bool, Real|1|170|
|2365|`game/GameEngine/Source/GameLogic/Object/Damage/ReflectDamage_onDamage.cpp`|Int, Real|1|148|
|2366|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRemoveTreesForConstruction.cpp`|Real, Bool|1|302|
|2367|`game/GameEngine/Source/GameLogic/Object/Create/PreorderCreate_onBuildComplete.cpp`|Int, Bool|1|85|
|2368|`game/GameEngine/Source/GameClient/GlobalLanguage_parseFontDesc.cpp`|Int, Bool|1|136|
|2369|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContainOnCapture.cpp`|Int, Bool|1|99|
|2370|`game/GameEngine/Source/GameClient/GlobalLanguage_adjustFontSize.cpp`|Int, Real|1|56|
|2371|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdAttackStateOnExit.cpp`|Int, UnsignedInt|1|138|
|2372|`game/GameEngine/Source/Common/SearchStringMatches.cpp`|Bool, Int|1|419|
|2373|`game/GameEngine/Source/GameClient/GUI/FullFadeTransition_init_Thunk.cpp`|Int, Real|1|95|
|2374|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsUnitGuardForFramecount.cpp`|Bool, Int|1|133|
|2375|`game/GameEngine/Source/GameLogic/AI/PathfinderSnapPosition.cpp`|Int, Bool, Real|1|151|
|2376|`game/GameEngine/Source/GameLogic/Object/Behavior/SupplyWarehouseCripplingBehavior_update.cpp`|UnsignedInt, Real|1|100|
|2377|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineAppendDebugMessage.cpp`|Bool, Int|1|197|
|2378|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamIdleForFramecount.cpp`|Bool, Int|1|148|
|2379|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewLerpCameraOneFrame.cpp`|Real, Int|1|140|
|2380|`game/GameEngine/Source/GameLogic/AI/PathComputeFlightDistToGoal.cpp`|Bool, Real|1|244|
|2381|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva0032A490ObjectDistanceFilter.cpp`|Real, Int|1|144|
|2382|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewZoomCameraOneFrame.cpp`|Real, Bool|1|156|
|2383|`game/GameEngine/Source/GameClient/GUI/Rva0051DD10StartBattleSchool.cpp`|Bool, Int|1|181|
|2384|`game/GameEngine/Source/GameClient/Rva00743BF0NamedEntryStart.cpp`|Bool, Int|1|180|
|2385|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitSetModelConditionForDuration.cpp`|Bool, Int, Real|1|284|
|2386|`game/GameEngine/Source/Common/INI/Rva00369C30ParseAttributeValue.cpp`|Int, Real|1|144|
|2387|`game/GameEngine/Source/GameLogic/LivingWorld/DelayedWorldTextEventModule.cpp`|Bool, Int|1|165|
|2388|`game/GameEngine/Source/GameLogic/Object/AttackNugget_ctor_Thunk.cpp`|Real, Int|1|90|
|2389|`game/GameEngine/Source/GameLogic/AI/PathfinderSetDebugPath.cpp`|Int, Real, Bool|1|190|
|2390|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doDisplayCounter_Thunk.cpp`|Int, Bool|1|235|
|2391|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetZoomToDefaultBfme.cpp`|Real, Bool|1|228|
|2392|`game/GameEngine/Source/GameLogic/Object/PartitionData_doRectFill.cpp`|Real, Int|1|415|
|2393|`game/GameEngine/Source/Common/Thing/ModuleInfoClearModuleDataWithTag.cpp`|Bool, Int|1|227|
|2394|`game/GameEngine/Source/GameClient/GUI/Rva00386910.cpp`|Bool, Int|1|216|
|2395|`game/GameEngine/Source/GameLogic/Object/Update/Rva0039D770Xfer.cpp`|UnsignedShort, Bool|1|253|
|2396|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoAddText.cpp`|Bool, Int|1|245|
|2397|`game/GameEngineDevice/Source/VideoDevice/Bink/SubtitleEntryAlignment.cpp`|Int, Real|1|202|
|2398|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00266590Apply.cpp`|Bool, UnsignedInt|1|171|
|2399|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraUpdateOneFrame.cpp`|Real, Bool|1|156|
|2400|`game/GameEngine/Source/GameLogic/Object/Weapon_bfmeComputeStatus.cpp`|Bool, UnsignedInt|1|208|
|2401|`game/GameEngine/Source/Common/Rva001FE6D0PlayerCharge.cpp`|Real, UnsignedInt|1|86|
|2402|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva00740440CameraPathAngles.cpp`|Real, Bool|1|347|
|2403|`game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_doFXListAtBone.cpp`|Bool, Int|1|135|
|2404|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraUpdateAlternateOneFrame.cpp`|Real, Bool|1|156|
|2405|`game/Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass_PendingSurfaceStruct_dtor.cpp`|Int, Bool|1|59|
|2406|`game/GameEngine/Source/GameClient/System/FXParticleSystem/ParticleModuleState005FC800Slot1.cpp`|UnsignedInt, Real|1|105|
|2407|`game/GameEngine/Source/GameClient/GUI/IMEManagerConstructor.cpp`|Bool, Int|1|164|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
