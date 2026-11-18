# Scalar alias contracts: cohort 164

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
|3906|`game/GameEngine/Source/GameLogic/AI/Rva0016D270ContainMerge.cpp`|Bool|1|153|
|3907|`game/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior_parseSound.cpp`|Int|1|310|
|3908|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva003248E0Condition.cpp`|Bool|1|352|
|3909|`game/GameEngine/Source/GameClient/GUI/Shell/ShellUpdate.cpp`|Int, Bool|1|351|
|3910|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_apply.cpp`|UnsignedInt|1|141|
|3911|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/FoundationAIUpdate_handle.cpp`|Bool|1|98|
|3912|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer_freeTreeBuffers.cpp`|Int|1|267|
|3913|`game/GameEngine/Source/GameNetwork/GameSpy/Rva00512890BuddyLookup.cpp`|Int|1|393|
|3914|`game/GameEngine/Source/Common/System/XferScienceElement.cpp`|Bool|1|258|
|3915|`game/GameEngine/Source/GameLogic/Object/WeaponMakeAssistanceRequest.cpp`|Real|1|267|
|3916|`game/GameEngine/Source/GameNetwork/IPEnumerationGetAddresses.cpp`|UnsignedInt|1|543|
|3917|`game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerIsPlayingLowerPriority006B2110.cpp`|Real|1|228|
|3918|`game/GameEngine/Source/GameLogic/LargeGroupAudio/Rva003D0A40MapXfer.cpp`|Bool|1|401|
|3919|`game/GameEngineDevice/Source/W3DDevice/GameClient/Gen006EF850Constructor.cpp`|UnsignedInt|1|753|
|3920|`game/Libraries/Source/WWVegas/WWLib/UnicodeStringBoolTreeFind.cpp`|Int, Bool|1|331|
|3921|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva002593F0Finish.cpp`|Real|1|512|
|3922|`game/GameEngine/Source/Common/System/Rva009A2420CollisionNodeMovementScore.cpp`|Real|1|252|
|3923|`game/GameEngine/Source/Common/StateMachine_internalSetState.cpp`|UnsignedInt|1|200|
|3924|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_d_002f5ca0.cpp`|Bool|1|130|
|3925|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackgroundRva0072DC30.cpp`|Bool, UnsignedShort|1|1044|
|3926|`game/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehavior_startPoisonedEffects.cpp`|UnsignedInt|1|175|
|3927|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00222640Dispatch.cpp`|Bool|1|187|
|3928|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_privateGuardPositionClipped.cpp`|Bool|1|242|
|3929|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapRva006CB080.cpp`|Int|1|281|
|3930|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDrawCreateEmitters.cpp`|Bool|1|436|
|3931|`game/GameEngine/Source/Common/System/ArchiveFileGetArchivedFileInfo.cpp`|UnsignedInt|1|332|
|3932|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0021D5D0OnContaining.cpp`|Bool|1|202|
|3933|`game/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdate_makeFeedbackLaser.cpp`|Bool, Int|1|270|
|3934|`game/GameEngine/Source/GameNetwork/Network_quitGame.cpp`|Int, UnsignedInt|1|37|
|3935|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitTeleportToWaypoint.cpp`|Bool|1|72|
|3936|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenOnlineChatOnBttnAccept.cpp`|Int|1|152|
|3937|`game/GameEngine/Source/GameLogic/Object/Gen001B1040ObjectTemplateXfer.cpp`|UnsignedByte|1|359|
|3938|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DFloorBuffer_rva006F9050.cpp`|Int|1|146|
|3939|`game/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelperSetModelConditionState.cpp`|UnsignedInt|1|185|
|3940|`game/GameEngine/Source/GameClient/ParticleSysBoneFXNugget_parse_Thunk.cpp`|Bool|1|401|
|3941|`game/GameEngine/Source/GameNetwork/BFMENetworkBackendDestructor.cpp`|Bool|1|216|
|3942|`game/GameEngine/Source/GameLogic/Object/Behavior/Rva00372E40.cpp`|Bool|1|280|
|3943|`game/GameEngine/Source/GameLogic/System/GameLogic_quitLocalGame.cpp`|Bool|1|221|
|3944|`game/GameEngine/Source/GameLogic/Object/Upgrade/ArmorUpgradeRemoveUpgrade.cpp`|UnsignedInt|1|213|
|3945|`game/GameEngine/Source/GameClient/EvaParseMessageFromIni.cpp`|Int|1|214|
|3946|`game/GameEngine/Source/GameClient/GUI/WindowLayoutInfoLoad.cpp`|Bool|1|234|
|3947|`game/GameEngine/Source/Common/RTS/Rva000C5EF0ActionManager.cpp`|Bool, UnsignedInt|1|119|
|3948|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00233F30RotatedOffset.cpp`|Real|1|154|
|3949|`game/GameEngine/Source/GameLogic/Object/Contain/SpawnBehaviorReclaimOrphanSpawn.cpp`|Int, Real|1|325|
|3950|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00239C90Interface.cpp`|Int, UnsignedInt|1|287|
|3951|`game/GameEngine/Source/Common/RTS/Team_bfmeSetNeedsGateOpenRaw.cpp`|Int|1|277|
|3952|`game/GameEngine/Source/GameLogic/Object/Upgrade/CostModifierUpgradeImplementation.cpp`|Bool|1|147|
|3953|`game/GameEngine/Source/Common/Rva00286C40.cpp`|Bool, UnsignedInt|1|288|
|3954|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap_updateMacroTexture.cpp`|Bool|1|276|
|3955|`game/GameEngine/Source/Common/RTS/Player_friend_applyDifficultyBonusesForObject.cpp`|Bool|1|336|
|3956|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doLocalDefeat_Thunk.cpp`|Bool|1|8|
|3957|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadNickErrorCallback.cpp`|Int|1|573|
|3958|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjClamp007A0960.cpp`|Bool, Int|1|249|
|3959|`game/GameEngine/Source/GameLogic/Object/Rva00419E40DrawablePredicate.cpp`|UnsignedInt|1|147|
|3960|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0075C8B0RenderState.cpp`|Real|1|115|
|3961|`game/GameEngine/Source/GameClient/System/ImageCollectionLoad.cpp`|Int|1|600|
|3962|`game/GameEngine/Source/GameLogic/Object/Object_bfmePostClosest.cpp`|Bool|1|254|
|3963|`game/GameEngine/Source/Common/Rva0036E650BuildListDispatch.cpp`|Int|1|433|
|3964|`game/GameEngine/Source/GameLogic/AI/INIAerialPathfindNoFlyZone.cpp`|Real|1|173|
|3965|`game/GameEngineDevice/Source/W3DDevice/GameClient/TaintBuffer_setShroudLevel.cpp`|UnsignedByte|1|735|
|3966|`game/GameEngine/Source/GameLogic/Object/Update/Rva002A7D20_getConditionalPreparationFrames.cpp`|UnsignedInt|1|105|
|3967|`game/GameEngine/Source/GameLogic/Object/Upgrade/CostModifierUpgradeRemoveUpgrade.cpp`|Bool|1|178|
|3968|`game/GameEngine/Source/GameClient/Drawable_drawBombed.cpp`|UnsignedInt|1|284|
|3969|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowHelperManagerReAcquireResources.cpp`|Bool|1|215|
|3970|`game/GameEngine/Source/Common/V3ThirdBaseCalledCopyCtor.cpp`|Int|1|125|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
