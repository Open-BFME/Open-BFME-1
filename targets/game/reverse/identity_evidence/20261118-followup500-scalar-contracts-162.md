# Scalar alias contracts: cohort 162

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
|3776|`game/GameEngine/Source/GameLogic/Object/ObjectPreFireCurrentWeapon.cpp`|UnsignedInt|1|215|
|3777|`game/GameEngine/Source/Common/ExperienceLevelSystemGainLevel.cpp`|Bool|1|139|
|3778|`game/GameEngine/Source/GameClient/GUI/CameraMarkerListReplace.cpp`|Int|1|185|
|3779|`game/Libraries/Source/WWVegas/WW3D2/BoxDynamicVBAccessClassDestructor.cpp`|UnsignedShort|1|79|
|3780|`game/GameEngine/Source/Common/System/DataChunkOutputCloseDataChunkThunk.cpp`|Int|1|118|
|3781|`game/GameEngine/Source/GameLogic/AI/AIMoveToPositionAndEnterState_onEnter.cpp`|UnsignedByte|1|146|
|3782|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003D7010.cpp`|Int, Bool|1|449|
|3783|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00345910.cpp`|Bool|1|249|
|3784|`game/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdateBuildFieldParse.cpp`|Int, UnsignedInt|1|36|
|3785|`game/GameEngine/Source/GameLogic/Object/Contain/HordeTransportContainIsValidContainerFor.cpp`|Bool|1|112|
|3786|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/ModelConditionInfo_addPublicBone.cpp`|Int, Bool|1|161|
|3787|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerStateMachineSupplyPredicate.cpp`|Bool|1|73|
|3788|`game/GameEngine/Source/Common/Rva0007F560FactoryLookup.cpp`|Int|1|188|
|3789|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineMADStruct.cpp`|Int|1|478|
|3790|`game/GameEngine/Source/Common/SmallGaps/Rva002EF110ScriptPlayers.cpp`|Int|1|137|
|3791|`game/GameEngine/Source/GameLogic/AI/AIAttackFireWeaponState_onExit.cpp`|Bool|1|161|
|3792|`game/GameEngine/Source/Common/Bfme/Gen_00418A60.cpp`|UnsignedInt|1|122|
|3793|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_rva0075BBA0.cpp`|Int|1|154|
|3794|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva0033CA50CollectScriptAssets.cpp`|Int|1|200|
|3795|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_updateSubObjectsFromShroud.cpp`|Bool|1|244|
|3796|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContainParseBoneSpecificConditionState.cpp`|UnsignedInt|1|172|
|3797|`game/GameEngine/Source/GameLogic/AI/Rva0016CF40State_xfer.cpp`|UnsignedByte|1|218|
|3798|`game/GameEngine/Source/Common/Rva00588E60DrawImageAt.cpp`|Real|1|120|
|3799|`game/GameEngine/Source/GameLogic/AI/wantToSquishTarget_Thunk.cpp`|Bool|1|174|
|3800|`game/GameEngine/Source/Common/Rva0016D5F0PathTest.cpp`|Bool|1|202|
|3801|`game/GameEngine/Source/GameLogic/Object/Update/TemporarilyDefectUpdate_bfmeTransferDefection.cpp`|UnsignedInt|1|114|
|3802|`game/GameEngine/Source/GameLogic/Map/TerrainLogicP48ClearNear.cpp`|Real|1|176|
|3803|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContainIniParseAnim.cpp`|Int|1|111|
|3804|`game/GameEngine/Source/GameLogic/Map/TerrainLogicGetLayerForDestinationObject.cpp`|Real|1|245|
|3805|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DView_createNamedCamera_rva00741C00.cpp`|Real|1|195|
|3806|`game/GameEngine/Source/Common/Rva001FD6B0StateUpdate.cpp`|Bool|1|163|
|3807|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorOnDelete.cpp`|UnsignedInt|1|76|
|3808|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowManagerReAcquireThunk.cpp`|Bool|1|70|
|3809|`game/GameEngine/Source/GameLogic/Object/Update/WallUpgradeUpdate_update.cpp`|UnsignedInt|1|175|
|3810|`game/GameEngine/Source/GameLogic/AI/AIExitStateOnExit.cpp`|Int|1|54|
|3811|`game/GameEngine/Source/GameLogic/Map/Waypoint_method001ABBB0.cpp`|Bool|1|168|
|3812|`game/Libraries/Source/WWVegas/WWLib/RvaTreeBoundsAsciiStringNoCase.cpp`|Int, Bool|1|166|
|3813|`game/GameEngine/Source/GameClient/Rva006A9800.cpp`|Int|1|216|
|3814|`game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseToken.cpp`|Int, Bool|1|155|
|3815|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doDisableInput_BFME.cpp`|Bool|1|99|
|3816|`game/GameEngine/Source/GameLogic/AI/Rva00249310Check.cpp`|Bool|1|108|
|3817|`game/GameEngine/Source/Common/BfmeConv1965.cpp`|Bool|1|100|
|3818|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceIsIdle.cpp`|Bool|1|78|
|3819|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00244F00RecordBuild.cpp`|Int|1|210|
|3820|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankDrawCreateEmitters.cpp`|Bool|1|310|
|3821|`game/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate_update.cpp`|UnsignedInt|1|115|
|3822|`game/GameEngine/Source/Common/Rva0024D520Method.cpp`|Real|1|160|
|3823|`game/GameEngine/Source/Common/System/BfmeRefPackDecode.cpp`|UnsignedByte|1|423|
|3824|`game/GameEngine/Source/Common/SkirmishBattleHonors_getFavoriteSideName.cpp`|Int, Bool|1|330|
|3825|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainFinishUpdate.cpp`|Bool|1|195|
|3826|`game/GameEngine/Source/Common/Thing/ThingTemplateHashResize.cpp`|Int, Bool|1|418|
|3827|`game/GameEngine/Source/GameLogic/Object/Update/BfmeInternAttributeEntry.cpp`|UnsignedInt|1|211|
|3828|`game/GameEngine/Source/GameLogic/Object/BfmeThingEFECtor.cpp`|Real|1|157|
|3829|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BD630StateTransition.cpp`|Int|1|151|
|3830|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedBaseUnpack.cpp`|Bool, Int|1|272|
|3831|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateFollowPathAppend.cpp`|Bool|1|545|
|3832|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva002ED960_SpeechPlaySingleArg.cpp`|Bool|1|132|
|3833|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamForceEmotion.cpp`|Bool|1|121|
|3834|`game/GameEngine/Source/GameLogic/Object/Update/Rva002C4FD0.cpp`|Real, Bool|1|378|
|3835|`game/GameEngine/Source/Common/System/MemoryPoolDestructor.cpp`|Int|1|115|
|3836|`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManagerRva00615B10.cpp`|Bool|1|210|
|3837|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate_retrieveMembers.cpp`|Int, Bool|1|202|
|3838|`game/Libraries/Source/WWVegas/WWLib/TreeLowerBound00093230.cpp`|Int, Bool|1|137|
|3839|`game/GameEngine/Source/Common/GameLODManagerGetAudioLODIndex.cpp`|Int|1|242|
|3840|`game/GameEngine/Source/Common/System/ArchivedFileInfoMapOperator.cpp`|UnsignedInt|1|236|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
