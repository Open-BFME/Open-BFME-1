# Scalar alias contracts: cohort 160

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
|3647|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doHideCountdownTimer.cpp`|Int|1|178|
|3648|`game/GameEngine/Source/Common/RTS/Rva000EDF80TeamMemberScan.cpp`|Bool|1|90|
|3649|`game/GameEngine/Source/Common/ExperienceLevelSystemUpdate.cpp`|Bool|1|180|
|3650|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainParseSplitResult.cpp`|Int|1|365|
|3651|`game/GameEngine/Source/GameNetwork/GameSpyOverlay_close.cpp`|Int, UnsignedInt, Bool|1|90|
|3652|`game/GameEngine/Source/GameClient/Rva00427130VectorResize.cpp`|UnsignedInt|1|98|
|3653|`game/GameEngineDevice/Source/W3DDevice/GameClient/CameraPath_endpointSetup_rva0073C640.cpp`|Real|1|142|
|3654|`game/GameEngine/Source/Common/INI/INISlopeLimits.cpp`|Real|1|126|
|3655|`game/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdateResetFromModuleData.cpp`|UnsignedInt|1|70|
|3656|`game/GameEngine/Source/Common/Rva00612430DgeFind.cpp`|Int|1|232|
|3657|`game/GameEngine/Source/GameLogic/System/BuildableStatusHashResize.cpp`|Int, Bool|1|418|
|3658|`game/GameEngine/Source/GameLogic/AI/Rva00260E80GroupApply.cpp`|Int|1|123|
|3659|`game/GameEngine/Source/GameLogic/AI/PathfindLayerXfer.cpp`|Int|1|267|
|3660|`game/GameEngine/Source/GameLogic/AI/Rva00174520AICowerState_onEnter.cpp`|Bool, UnsignedInt|1|113|
|3661|`game/GameEngine/Source/GameClient/LanguageFilter_unHaxor.cpp`|Int, Bool|1|574|
|3662|`game/GameEngine/Source/GameClient/EvaEventFXNugget_doFXObj_Thunk.cpp`|Bool|1|139|
|3663|`game/GameEngine/Source/Common/Rva0060D3E0CursorDisable.cpp`|Bool|1|34|
|3664|`game/GameEngine/Source/GameNetwork/DownloadManagerDownloadNextQueuedFile.cpp`|Bool|1|340|
|3665|`game/GameEngine/Source/Common/Containers/Rva003A1080Setup.cpp`|Real|1|119|
|3666|`game/GameEngine/Source/GameClient/GUI/GameWindowTransitionsHandlerCollectGroups.cpp`|Bool|1|132|
|3667|`game/GameEngine/Source/GameClient/MapMetaData_dtor.cpp`|UnsignedShort|1|183|
|3668|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetHeightAboveGroundBfme.cpp`|Real|1|218|
|3669|`game/GameEngine/Source/Common/RTS/ScoreKeeperReset.cpp`|Int|1|470|
|3670|`game/GameEngine/Source/GameClient/WaterTransparencySettingAssign.cpp`|Int|1|113|
|3671|`game/GameEngine/Source/GameLogic/Object/Behavior/Rva0022DA50NameCountParser.cpp`|Int|1|223|
|3672|`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManagerFindArmyIcon.cpp`|Int, UnsignedInt|1|225|
|3673|`game/GameEngine/Source/GameLogic/LivingWorld/ParseLivingWorldCampaignAct.cpp`|Int|1|286|
|3674|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishPreferencesUserNameRemove.cpp`|Bool|1|164|
|3675|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap_loadRoadsAndBridges.cpp`|Bool|1|67|
|3676|`game/GameEngine/Source/GameClient/FXList_bfmeIsBlocked.cpp`|UnsignedInt|1|188|
|3677|`game/GameEngine/Source/GameLogic/Object/LocomotorRva001B5A30.cpp`|Real|1|148|
|3678|`game/GameEngine/Source/Common/System/SaveGame/GameState_findHighFileNumber.cpp`|Int|1|318|
|3679|`game/GameEngine/Source/GameLogic/Object/Body/PorcupineFormationBodyModuleApply.cpp`|Real|1|142|
|3680|`game/GameEngine/Source/Common/Watchdog_Thread_Function.cpp`|UnsignedInt|1|278|
|3681|`game/GameEngine/Source/Common/RTS/PlayerFindSkirmishSide.cpp`|Bool|1|331|
|3682|`game/GameEngine/Source/Common/INI/INI_parseMetaMapDefinition_Thunk.cpp`|Int|1|143|
|3683|`game/GameEngineDevice/Source/Win32Device/Common/Win32LocalFileSystem_openFile.cpp`|Int|1|22|
|3684|`game/GameEngine/Source/GameClient/Gen_005e9a20.cpp`|Int|1|57|
|3685|`game/GameEngine/Source/GameClient/GUI/Gadget/doAudioFeedback_Thunk.cpp`|Bool|1|153|
|3686|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainModuleData_parseInitialRoster_Thunk.cpp`|Int|1|104|
|3687|`game/GameEngine/Source/GameLogic/Object/Behavior/Rva002098B0ParsePhaseWeaponList.cpp`|Int|1|167|
|3688|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowManagerInit.cpp`|Bool|1|93|
|3689|`game/GameEngine/Source/GameLogic/Object/SpecialPower/BfmeSpecialPowerAllowanceStore_allows.cpp`|Int|1|61|
|3690|`game/GameEngine/Source/GameLogic/Object/Object_bfmeTransferReplacementState.cpp`|UnsignedInt|1|211|
|3691|`game/GameEngine/Source/GameLogic/Object/SpecialPower/BfmeSpecialPowerAllowanceStore_bfmeIndexOf.cpp`|Int|1|195|
|3692|`game/GameEngine/Source/GameLogic/AI/Rva00178BC0ComputePath.cpp`|Bool|1|88|
|3693|`game/GameEngine/Source/GameLogic/AI/Rva00178D90ComputePath.cpp`|Bool|1|88|
|3694|`game/GameEngine/Source/Common/Thing/ThingFactoryDestructorThunk.cpp`|UnsignedShort|1|92|
|3695|`game/GameEngine/Source/GameLogic/AI/AerialPathfinder_addNoFlyZone.cpp`|Int, Real, Bool|1|75|
|3696|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva00237D70RandomMember.cpp`|UnsignedInt|1|170|
|3697|`game/GameEngine/Source/GameLogic/Object/Rva002D9F30SetCondition.cpp`|UnsignedInt|1|70|
|3698|`game/GameEngine/Source/GameLogic/Object/SpecialPower/StopSpecialPowerDoSpecialPower.cpp`|UnsignedInt|1|35|
|3699|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BBC40FlagPredicate.cpp`|UnsignedInt|1|135|
|3700|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer_freeTreeBuffers.cpp`|Int|1|267|
|3701|`game/GameEngine/Source/GameLogic/Object/Upgrade/ObjectCreationUpgradeRva002D6FE0.cpp`|Bool, UnsignedInt|1|210|
|3702|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorIsPendingObjectUnavailable.cpp`|Bool|1|77|
|3703|`game/GameEngine/Source/GameClient/Rva006FEA60FadeInGameMovie.cpp`|Int|1|132|
|3704|`game/GameEngine/Source/GameClient/System/FXParticleSystem/TerrainCollisionSlot1.cpp`|Real|1|175|
|3705|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ReplayMenuShutdown.cpp`|Bool|1|75|
|3706|`game/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContainUpdate.cpp`|UnsignedInt|1|54|
|3707|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateModule_iniParseAnimAndDuration.cpp`|Int|1|267|
|3708|`game/GameEngine/Source/GameClient/GUI/Rva004776E0ParseStyledName.cpp`|Int|1|512|
|3709|`game/GameEngine/Source/GameClient/GUI/AptPalantirOnButtonAlert.cpp`|Bool|1|244|
|3710|`game/GameEngine/Source/GameLogic/Object/Upgrade/UpgradeMux_Rva002D70F0.cpp`|Bool, UnsignedInt|1|173|
|3711|`game/GameEngine/Source/GameLogic/LivingWorld/SplineEffectParseINIBlock.cpp`|Int|1|214|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
