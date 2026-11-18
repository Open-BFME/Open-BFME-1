# Scalar alias contracts: cohort 163

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
|3841|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate_findGoodBuildOrRepairPositionAndTarget.cpp`|UnsignedInt|1|291|
|3842|`game/GameEngine/Source/GameClient/MessageStream/MetaMap_getMetaMapRecThunk.cpp`|Int|1|111|
|3843|`game/GameEngine/Source/GameNetwork/NetworkUtilResolveIP.cpp`|UnsignedInt|1|203|
|3844|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006F8F00Owner_updateBuffers.cpp`|Int, UnsignedShort|1|264|
|3845|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D7440.cpp`|Int, Bool|1|433|
|3846|`game/GameEngine/Source/GameLogic/Object/ObjectBuildObjectInfo.cpp`|UnsignedInt|1|194|
|3847|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainUpdate.cpp`|UnsignedInt|1|122|
|3848|`game/GameEngine/Source/Common/Bfme/GenOwner_ready.cpp`|Bool|1|77|
|3849|`game/GameEngine/Source/Common/NameKeyGenerator_keyToName.cpp`|Int, UnsignedInt, Bool|1|119|
|3850|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate_xfer.cpp`|UnsignedInt|1|273|
|3851|`game/GameEngine/Source/Common/ExperienceLevelSystemDestructor.cpp`|Bool|1|340|
|3852|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewWorldToScreenBfme.cpp`|Int|1|180|
|3853|`game/GameEngine/Source/GameNetwork/GenerateGameOptionsString.cpp`|Int, Bool|1|117|
|3854|`game/GameEngine/Source/GameLogic/Object/Update/Rva0029C380BuildableStatus.cpp`|Int, Bool|1|111|
|3855|`game/GameEngine/Source/Common/Rva0015A790RebuildBuckets.cpp`|Int|1|364|
|3856|`game/Libraries/Source/WWVegas/WWLib/UnicodeStringBoolTreeLowerBoundThunk.cpp`|Int, Bool|1|247|
|3857|`game/GameEngine/Source/Common/StateMachineCtorThunk.cpp`|Bool|1|180|
|3858|`game/GameEngine/Source/GameLogic/Object/SpecialPower/DevastateSpecialPowerDoSpecialPower.cpp`|UnsignedInt|1|75|
|3859|`game/GameEngine/Source/GameLogic/Pathfinder/PathfindCellXfer.cpp`|Int|1|479|
|3860|`game/GameEngine/Source/GameClient/GUI/ControlBar/Rva0058DA50SelectAllHeroes.cpp`|Bool|1|287|
|3861|`game/GameEngine/Source/Common/Rva006ABC60Xfer.cpp`|Bool|1|258|
|3862|`game/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDamagedBehaviorXfer.cpp`|Bool|1|435|
|3863|`game/GameEngine/Source/GameLogic/Object/Contain/Rva002371C0HordeContain.cpp`|UnsignedInt|1|195|
|3864|`game/GameEngine/Source/GameLogic/Object/Update/Rva0039DAC0AttributeNames.cpp`|Int|1|274|
|3865|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewShakeBfme.cpp`|Real|1|272|
|3866|`game/GameEngine/Source/Common/Audio/AudioManagerIsValidAudioEvent.cpp`|Bool|1|189|
|3867|`game/GameEngine/Source/GameLogic/AI/AIFollowPathAsTeamState_computePath_Bfme.cpp`|Bool|1|266|
|3868|`game/GameEngine/Source/GameLogic/AI/AIMoveOntoWallState_xfer.cpp`|UnsignedByte|1|210|
|3869|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamAssimilateWithFirstWalkOnArmy.cpp`|Bool|1|133|
|3870|`game/GameEngine/Source/Common/System/SaveGame/GameStateFindBlockInfoByToken.cpp`|UnsignedShort|1|271|
|3871|`game/GameEngine/Source/GameLogic/Object/Update/Emotion_xfer.cpp`|UnsignedInt|1|460|
|3872|`game/GameEngine/Source/Common/RTS/Rva000EDED0TeamUpgradeScan.cpp`|Bool|1|132|
|3873|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate_setCashValue.cpp`|Int|1|81|
|3874|`game/GameEngine/Source/GameClient/MapMetaData_assign.cpp`|UnsignedShort|1|229|
|3875|`game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateGetAdjustsDestination.cpp`|Bool|1|203|
|3876|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0023D850HordeSnapToMember.cpp`|Real|1|147|
|3877|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DCommandBarBackgroundDraw.cpp`|Int|1|279|
|3878|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DCommandBarForegroundDraw.cpp`|Int|1|279|
|3879|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetPlayerKillsOfKindOfToCounter.cpp`|Bool|1|284|
|3880|`game/GameEngine/Source/GameLogic/Map/SidesListValidateAllyEnemyList.cpp`|Bool|1|413|
|3881|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0021AC30ContestableContainOverride.cpp`|Bool|1|178|
|3882|`game/GameEngine/Source/Common/Rva003A1120CopyCtor.cpp`|Int|1|375|
|3883|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainGetClosestRider.cpp`|Real|1|145|
|3884|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishPreferencesUserNameSerialize.cpp`|Bool|1|276|
|3885|`game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerFindLowestPrioritySound.cpp`|Real|1|258|
|3886|`game/GameEngine/Source/GameLogic/AI/Rva0016F4F0.cpp`|Bool|1|243|
|3887|`game/GameEngine/Source/GameClient/GUI/GameWindowWinSetInstanceData.cpp`|Int|1|158|
|3888|`game/GameEngine/Source/Common/Rva0060EE80Manager.cpp`|Bool|1|315|
|3889|`game/GameEngine/Source/GameClient/MessageStream/GUICommandTranslator_doPlaceBeacon.cpp`|Bool|1|70|
|3890|`game/GameEngine/Source/Common/BfmeOwnVUMXfer.cpp`|UnsignedByte|1|428|
|3891|`game/GameEngine/Source/GameLogic/Object/Behavior/Rva0036FF70ModuleQuery.cpp`|Int|1|524|
|3892|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayRva006ECF80.cpp`|Bool|1|74|
|3893|`game/GameEngine/Source/GameLogic/Object/Die/crushLocationCheck_Thunk.cpp`|Real|1|387|
|3894|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineGetPlayerMaskFromParameter.cpp`|Bool|1|215|
|3895|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawModuleData_parseEmbedPortal.cpp`|Int|1|272|
|3896|`game/GameEngine/Source/GameLogic/Object/Locomotor_maintainCurrentPositionWings.cpp`|Bool, Real|1|338|
|3897|`game/GameEngine/Source/GameLogic/Object/Object_setEffectivelyDead.cpp`|Bool|1|337|
|3898|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00236E10HordeApplyToMembers.cpp`|Int, UnsignedInt|1|253|
|3899|`game/GameEngine/Source/GameLogic/Object/Die/FXListDieOnDie.cpp`|Real|1|143|
|3900|`game/GameEngine/Source/GameLogic/Object/ObjectBfmeApplyABG.cpp`|Int|1|159|
|3901|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDrawDoDrawModule.cpp`|Real, Bool|1|401|
|3902|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdatePathPriority.cpp`|Bool|1|435|
|3903|`game/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdate_onObjectCreated.cpp`|Bool|1|181|
|3904|`game/GameEngine/Source/Common/Thing/ThingFactory_reset.cpp`|Bool|1|167|
|3905|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00268340IniParseAnim.cpp`|Int|1|111|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
