# Scalar alias contracts: cohort 136

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
|2537|`game/GameEngine/Source/Common/Rva000F9CF0Xfer.cpp`|UnsignedByte, UnsignedInt|1|438|
|2538|`game/GameEngine/Source/Common/System/GeometryInfoRva0087E190.cpp`|Bool, Real|1|469|
|2539|`game/GameEngine/Source/Common/System/SaveGame/GameStateMap_embedInUseMap.cpp`|UnsignedInt, Int|1|343|
|2540|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedSetRepulsor.cpp`|Int, Bool|1|67|
|2541|`game/GameEngine/Source/GameLogic/ScriptEngine/ControlBar_showSpecialPowerShortcutMethodThunk.cpp`|Int, Bool|1|14|
|2542|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme_find.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|245|
|2543|`game/GameEngine/Source/Common/StateMachine_updateStateMachineTwin.cpp`|UnsignedInt, Int, Bool|1|124|
|2544|`game/GameEngineDevice/Source/W3DDevice/GameClient/TerrainTracksBfmeReAcquire.cpp`|Int, UnsignedShort|1|328|
|2545|`game/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldRegionManager_Rva003C8D50.cpp`|Bool, UnsignedByte|1|334|
|2546|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdFollowThruStateOnExit.cpp`|Int, UnsignedInt|1|210|
|2547|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_redeployOccupants.cpp`|Int, Bool|1|159|
|2548|`game/GameEngine/Source/GameClient/GUI/ControlBar/Rva004A41D0UpgradeSinkCallback.cpp`|Bool, UnsignedInt|1|78|
|2549|`game/GameEngine/Source/GameLogic/AI/PathfindCell_setTypeAsObstacle.cpp`|Int, Bool|1|233|
|2550|`game/GameEngine/Source/GameLogic/AI/AIMoveToPositionAndDieState_onEnter.cpp`|Int, UnsignedInt, UnsignedByte, Real, Bool|1|134|
|2551|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawRva007633A0.cpp`|Bool, Real|1|303|
|2552|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior.cpp`|Int, Bool|1|244|
|2553|`game/GameEngine/Source/GameLogic/System/VictorySystemRva001DFC10.cpp`|Int, Real|1|262|
|2554|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate_giveFinalOrders.cpp`|Int, Bool|1|270|
|2555|`game/GameEngine/Source/GameClient/SubtitleEntryConstructor.cpp`|UnsignedInt, Int|1|318|
|2556|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorCostForDamage.cpp`|Int, Real|1|86|
|2557|`game/GameEngine/Source/GameLogic/Object/Weapon_getRemainingAmmo.cpp`|UnsignedInt, Bool|1|111|
|2558|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetCommandPointsToBuildTeamToCounter.cpp`|Bool, Int|1|165|
|2559|`game/GameEngine/Source/Common/RTS/ActionManagerCanGarrison.cpp`|Bool, Int|1|247|
|2560|`game/GameEngine/Source/GameClient/FXListDoFXObjThunk.cpp`|Bool, Int|1|166|
|2561|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DPushButtonCenteredScaledImage00794040.cpp`|Int, Real|1|170|
|2562|`game/GameEngine/Source/GameClient/MessageStream/CommandXlatRva005A9C90.cpp`|Int, Bool|1|159|
|2563|`game/GameEngine/Source/Common/RTS/Team_countObjectsByThingTemplate.cpp`|Int, Bool|1|193|
|2564|`game/GameEngine/Source/GameNetwork/GameSpy/LanLobbyGamesTooltip.cpp`|Int, Bool|1|402|
|2565|`game/GameEngine/Source/GameLogic/Object/Object_rva001CE530.cpp`|Bool, UnsignedInt|1|213|
|2566|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawSetTerrainDecal.cpp`|Bool, Real|1|294|
|2567|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00236CA0HordeContain.cpp`|UnsignedInt, Bool|1|292|
|2568|`game/GameEngine/Source/GameLogic/Object/WeaponSet_getModelConditionForWeaponSlot.cpp`|Int, UnsignedInt|1|244|
|2569|`game/GameEngine/Source/Common/Rva004942C0Owner.cpp`|Int, Real|1|146|
|2570|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeWaitPathState_update.cpp`|Bool, UnsignedInt|1|358|
|2571|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonAbilityOnNamed_Thunk.cpp`|Bool, Int|1|166|
|2572|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_onContaining.cpp`|Int, Bool|1|179|
|2573|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewUpdateCameraMovementsBfme.cpp`|Int, Bool|1|293|
|2574|`game/GameEngine/Source/GameClient/GUI/Rva00435270SetRange.cpp`|Int, Real|1|378|
|2575|`game/GameEngine/Source/GameClient/GUI/Map_Roll_LoadGame.cpp`|Bool, Real|1|121|
|2576|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_initLaser.cpp`|Bool, Int|1|368|
|2577|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawXfer.cpp`|UnsignedInt, Int, Bool|1|312|
|2578|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdateFindGoodBuildOrRepairPosition.cpp`|Real, Bool|1|445|
|2579|`game/GameEngine/Source/GameLogic/AI/AISkirmishPlayer_startTraining.cpp`|Int, Bool|1|313|
|2580|`game/GameEngine/Source/Common/RTS/PlayerAddRadar.cpp`|Int, Bool|1|215|
|2581|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorIsPlayerAllowedToPackOrUnpack.cpp`|Bool, Int|1|198|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
