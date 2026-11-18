# Shared enum contracts, cohort 103

Each task replaces one private per-unit enum with its existing BFME1 definition.
Values used by the translation unit, primitive underlying type and four-byte
size are preserved. Extra or conflicting private enumerators are permitted only
when absent from masked active code outside their declaration; every such entry
is retained in the diagnostic proof and listed below. No active identifier is
renamed, no pin, alias or provider is rebound. This is source consistency, not
new authored function bytes or a demonstrated full-image/runtime improvement.

NameKeyType follows the native namekeygenerator shim; ObjectID/DrawableID the
native Common/game_type.h; UpdateSleepTime the native UpdateModule.h. Original
EA license and constants are retained. CommandSourceType uses the unchanged
native command_source_type.h: PLAYER/SCRIPT/AI have independent BFME1 evidence;
DOZER/default-switch retain documented Zero Hour provenance, not new target proof.

Read-only BFME2 donor0630f0ef47d0a818bb2e97583b43cfb1ecd35491 was reviewed:
NameKeyGeneratorLifetime.cpp carries the same NameKey constants; the BFME2
NameKeyGenerator.h and UpdateModule.h use forwards and distinct class contracts.
No donor address, layout or body is imported. Existing BFME1 source contracts
and independent matched native providers take precedence.

Every ordinary whole-object inventory is identical: code, data, relocations,
definitions, raw directives, weak externals and aliases. Paired private Z7
CodeView records prove primitive enum ABI, every member value, every other
original enum and all original complete class contracts. Real include tracing
and a fresh actual-header probe confirm the normal object uses this contract.
Debug probes themselves must reproduce ordinary runtime after normalizing only
section ordinals displaced by debug sections. Native byte, relocation and body
gates pass; shared headers also require the normal full dependency hook.
Scope excludes crash/leak/RAM,64-bit,multicore,FPS and game-start claims.

|Task|Enum|Consumer|Rows|Retained bytes|Unused private enumerators replaced|
|---|---|---|---:|---:|---|
|601|ObjectID|`game/GameEngine/Source/Common/Rva002E0970Remove.cpp`|1|16|`{}`|
|602|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Contain/Rva002308E0StaticNameKey.cpp`|1|104|`{}`|
|603|NameKeyType|`game/GameEngine/Source/Common/SmallGaps/Rva002A0A40StaticNameKey.cpp`|1|104|`{}`|
|604|ObjectID|`game/GameEngine/Source/GameLogic/Object/Rva001DDBE0AddObjectID.cpp`|1|62|`{"INVALID_OBJECT_ID": 0}`|
|605|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Helper/ObjectRecoveryHelper_update.cpp`|1|20|`{}`|
|606|NameKeyType|`game/GameEngine/Source/Common/RTS/ScienceStoreInternalName.cpp`|1|62|`{}`|
|607|ObjectID|`game/GameEngine/Source/GameLogic/AI/Rva0018B8B0Apply.cpp`|1|74|`{"INVALID_OBJECT_ID": 0}`|
|608|NameKeyType|`game/GameEngine/Source/Common/BfmeConv1955.cpp`|1|149|`{}`|
|609|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleMemberBehaviorFind.cpp`|1|108|`{}`|
|610|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/WargBehavior_update.cpp`|1|43|`{}`|
|611|NameKeyType|`game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineScanEventKeys.cpp`|1|58|`{}`|
|612|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateUpdate.cpp`|1|41|`{}`|
|613|NameKeyType|`game/GameEngine/Source/GameLogic/Object/WeaponStore_findWeaponTemplate_Thunk.cpp`|1|183|`{"INVALID_NAME_KEY": 0}`|
|614|NameKeyType|`game/GameEngine/Source/Common/Bfme5DictStringPresence.cpp`|1|92|`{}`|
|615|ObjectID|`game/GameEngine/Source/Common/Audio/BfmeTheEmptyAudioEventGlobal.cpp`|1|29|`{}`|
|616|ObjectID|`game/GameEngine/Source/Common/BfmeObjectIdSwapRemove.cpp`|1|68|`{"INVALID_OBJECT_ID": 0}`|
|617|DrawableID|`game/GameEngine/Source/GameClient/BfmeDrawableEventManagerForwardDrawableEvent.cpp`|1|60|`{}`|
|618|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Helper/ObjectRecoveryHelper_getModuleNameKey.cpp`|1|104|`{}`|
|619|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/UpdateModule_bfmeFinishWithDeposit.cpp`|1|88|`{}`|
|620|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Update/WallUpgradeUpdateFind.cpp`|1|108|`{}`|
|621|NameKeyType|`game/GameEngine/Source/Common/System/DataChunkOutput_writeNameKey_Thunk.cpp`|1|134|`{"NameKeyType_dummy": 0}`|
|622|ObjectID|`game/GameEngine/Source/GameLogic/AI/AIGroup_getAllIDs.cpp`|1|136|`{"INVALID_OBJECT_ID": 0}`|
|623|NameKeyType|`game/GameEngine/Source/Common/System/Rva0010A950UpgradeLookup.cpp`|1|36|`{}`|
|624|NameKeyType|`game/GameEngine/Source/Common/Rva005674A0Assign.cpp`|1|59|`{}`|
|625|UpdateSleepTime|`game/GameEngine/Source/Common/Rva002CF610Flags.cpp`|1|86|`{"UPDATE_SLEEP_PLACEHOLDER": 0}`|
|626|ObjectID|`game/GameEngine/Source/GameLogic/System/EmotionSystemObjectIDAdd.cpp`|1|95|`{"INVALID_OBJECT_ID": 0}`|
|627|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehavior_update.cpp`|1|48|`{"UPDATE_SLEEP_NONE": 0}`|
|628|UpdateSleepTime|`game/GameEngine/Source/Common/Rva00202DF0BackStepSeed.cpp`|1|70|`{}`|
|629|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/EnragedBehaviorCtorThunk.cpp`|1|134|`{}`|
|630|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/ClickReactionBehaviorCtorThunk.cpp`|1|151|`{}`|
|631|NameKeyType|`game/GameEngine/Source/Common/RTS/Handicap_readFromDict_Thunk.cpp`|1|368|`{}`|
|632|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/UpdateModule_getWakeFrame.cpp`|1|24|`{}`|
|633|DrawableID|`game/GameEngine/Source/GameLogic/Object/Update/LaserUpdate_initFromDrawables.cpp`|1|80|`{}`|
|634|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDamagedBehaviorUpgradeImplementation.cpp`|1|15|`{}`|
|635|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/ReplenishUnitsBehaviorUpgradeImplementation.cpp`|1|15|`{}`|
|636|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/BroadcastStealthUpdateUpgradeImplementation.cpp`|1|15|`{}`|
|637|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/ShareExperienceBehaviorCtorThunk.cpp`|1|148|`{"UPDATE_SLEEP_DUMMY": 0}`|
|638|NameKeyType|`game/GameEngine/Source/Common/Thing/ModuleFactory_rva00127e80.cpp`|1|95|`{}`|
|639|NameKeyType|`game/GameEngine/Source/GameClient/Drawable_findClientUpdateModule.cpp`|1|55|`{}`|
|640|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierAuraUpdateUpgradeImplementation.cpp`|1|15|`{}`|
|641|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/RadiusDecalUpdate_update.cpp`|1|50|`{}`|
|642|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/OneRingPenaltyUpdateCtorThunk.cpp`|1|157|`{}`|
|643|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/DetachableRiderUpdateCtorModuleFactoryBody.cpp`|1|140|`{}`|
|644|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/BuildingBehaviorCtorThunk.cpp`|1|138|`{}`|
|645|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Update/Rva002323B0UpdateFind.cpp`|1|110|`{}`|
|646|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/SpecialEnemySenseUpdateCtorThunk.cpp`|1|131|`{}`|
|647|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/BloodthirstyUpdateCtor.cpp`|1|154|`{}`|
|648|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/DualWeaponBehaviorCtorThunk.cpp`|1|137|`{}`|
|649|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/HitReactionBehaviorCtorThunk.cpp`|1|137|`{}`|
|650|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Update/Rva0026C260StealthCheck.cpp`|1|151|`{"NAMEKEY_FORCE_LONG": 2147483647}`|
|651|NameKeyType|`game/GameEngineDevice/Source/W3DDevice/GameClient/MapObject_verifyValidTeamMethodThunk.cpp`|1|157|`{}`|
|652|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/BunkerBusterBehaviorCtorThunk.cpp`|1|154|`{}`|
|653|NameKeyType|`game/GameEngineDevice/Source/W3DDevice/GameClient/BfmeObjEME_bfmeGetEME.cpp`|1|200|`{}`|
|654|ObjectID|`game/GameEngine/Source/Common/VectorObjectIDResizeThunk.cpp`|1|76|`{}`|
|655|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/PassiveAreaEffectBehaviorCtorThunk.cpp`|1|211|`{}`|
|656|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/StickyBombUpdateCtorThunk.cpp`|1|154|`{"UPDATE_SLEEP_DUMMY": 0}`|
|657|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/CheckpointUpdateCtorThunk.cpp`|1|154|`{"UPDATE_SLEEP_DUMMY": 0}`|
|658|NameKeyType|`game/GameEngine/Source/Common/Gen00371090Remove.cpp`|1|107|`{}`|
|659|NameKeyType|`game/GameEngine/Source/GameClient/GUI/parseDrawCallback_Thunk.cpp`|1|130|`{}`|
|660|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/WallUpgradeUpdateCtorThunk.cpp`|1|169|`{"UPDATE_SLEEP_DUMMY": 0}`|
|661|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/OverchargeBehaviorCtorThunk.cpp`|1|154|`{"UPDATE_SLEEP_DUMMY": 0}`|
|662|DrawableID|`game/GameEngine/Source/GameClient/BfmeDrawableEventForwarder.cpp`|1|59|`{}`|
|663|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/SpecialPower/DeflectSpecialPowerUpdate.cpp`|1|139|`{}`|
|664|ObjectID|`game/GameEngine/Source/Common/BfmeConv1703.cpp`|1|55|`{}`|
|665|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/RespawnUpdateCtorModuleFactory.cpp`|1|168|`{}`|
|666|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/TemporarilyDefectUpdateCtorThunk.cpp`|1|146|`{"UPDATE_SLEEP_DUMMY": 0}`|
|667|CommandSourceType|`game/GameEngine/Source/Common/Bfme5GuardedTargetSink.cpp`|1|63|`{}`|
|668|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Behavior/SetMemberPayload0036F1B0.cpp`|1|228|`{}`|
|669|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/SmartBombTargetHomingUpdateCtorThunk.cpp`|1|154|`{}`|
|670|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/SlaveWatcherBehaviorConstructor.cpp`|1|134|`{}`|
|671|ObjectID|`game/GameEngine/Source/GameLogic/System/GameLogic_bfmeSwapObjectIDs.cpp`|1|135|`{"INVALID_OBJECT_ID": 0}`|
|672|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Upgrade/AudioLoopUpgradeCtorModuleFactory.cpp`|1|193|`{}`|
|673|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/LeafletDropBehaviorCtorThunk.cpp`|1|154|`{"UPDATE_SLEEP_DUMMY": 0}`|
|674|ObjectID|`game/GameEngine/Source/GameLogic/AI/Rva0018BB10LiveObjects.cpp`|1|282|`{"FORCE_OBJECTID_32": 2147483647}`|
|675|NameKeyType|`game/GameEngine/Source/Common/Rva0037F050ExperienceQuery.cpp`|1|121|`{}`|
|676|NameKeyType|`game/GameEngine/Source/Common/INI/NamedIndexListParser00377AF0.cpp`|1|441|`{"InvalidKey": -1}`|
|677|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Behavior/Rva00128780GateBehaviorResolver.cpp`|1|176|`{}`|
|678|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Behavior/Gen00374800ModuleCheck.cpp`|1|166|`{}`|
|679|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehaviorCtorModuleFactory.cpp`|1|164|`{"UPDATE_SLEEP_DUMMY": 0}`|
|680|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlayRCMenuInit.cpp`|1|649|`{}`|
|681|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorCtorModuleFactory.cpp`|1|182|`{}`|
|682|ObjectID|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdateModuleDataCtorThunk.cpp`|1|123|`{"INVALID_OBJECT_ID": 0}`|
|683|ObjectID|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdateXfer.cpp`|1|119|`{}`|
|684|ObjectID|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateModuleDataCtorThunk.cpp`|1|141|`{"INVALID_OBJECT_ID": 0}`|
|685|NameKeyType|`game/GameEngine/Source/Common/Rva001B70E0Lookup.cpp`|1|92|`{}`|
|686|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/HordeAIUpdateCtorThunk.cpp`|1|141|`{}`|
|687|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehaviorConstructor.cpp`|1|154|`{}`|
|688|DrawableID|`game/GameEngine/Source/GameLogic/ScriptEngine/CurDrawablePlaySound.cpp`|1|211|`{}`|
|689|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/HordeUpdateCtorThunk.cpp`|1|154|`{"UPDATE_SLEEP_DUMMY": 0}`|
|690|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/Gen00296F90Handle.cpp`|1|131|`{}`|
|691|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdateCtorThunk.cpp`|1|175|`{}`|
|692|UpdateSleepTime|`game/GameEngine/Source/GameLogic/ScriptEngine/DelayedLuaEventUpdateConstructor.cpp`|1|161|`{"UPDATE_SLEEP_DUMMY": 0}`|
|693|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdateResetFromModuleData.cpp`|1|70|`{"UPDATE_SLEEP_DUMMY": 0}`|
|694|ObjectID|`game/GameEngine/Source/GameLogic/ScriptEngine/SolutionVecCopyConstructor.cpp`|1|82|`{}`|
|695|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/RubbleRiseUpdateOnDie.cpp`|1|65|`{}`|
|696|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehaviorConstructor.cpp`|1|134|`{}`|
|697|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/DestroyEnvironmentUpdate_update.cpp`|1|155|`{}`|
|698|NameKeyType|`game/GameEngine/Source/Common/RTS/PlayerTemplate_parseProductionVeterancyLevel_Thunk.cpp`|1|170|`{"NAME_KEY_INVALID": 0}`|
|699|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContain.cpp`|1|120|`{}`|
|700|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdateConstructor.cpp`|1|134|`{}`|
|701|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdateConstructor.cpp`|1|160|`{}`|
|702|NameKeyType|`game/GameEngine/Source/Common/RTS/PlayerFindSkirmishSide.cpp`|1|331|`{}`|
|703|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/PhysicsBehaviorRva0029B120.cpp`|1|137|`{}`|
|704|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehaviorConstructor.cpp`|1|155|`{}`|
|705|ObjectID|`game/GameEngine/Source/GameClient/GUI/Gadget/doAudioFeedback_Thunk.cpp`|1|153|`{"OBJECT_ID_UNUSED": 0}`|
|706|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Object_bfmeTransferReplacementState.cpp`|1|211|`{"INVALID_NAME_KEY": 0}`|
|707|ObjectID|`game/GameEngine/Source/GameLogic/AI/Squad_xfer.cpp`|1|274|`{}`|
|708|NameKeyType|`game/GameEngine/Source/GameLogic/ScriptEngine/ObjectSpy.cpp`|1|250|`{}`|
|709|ObjectID|`game/GameEngine/Source/Common/RTS/TunnelTrackerOnTunnelDestroyed.cpp`|1|191|`{"INVALID_OBJECT_ID": 0}`|
|710|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/WeaponModeSpecialPowerUpdateCtorThunk.cpp`|1|125|`{}`|
|711|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContainUpdate.cpp`|1|54|`{}`|
|712|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdate_ctor.cpp`|1|160|`{}`|
|713|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/SupplyWarehouseCripplingBehavior_update.cpp`|1|100|`{}`|
|714|NameKeyType|`game/GameEngine/Source/Common/System/UpgradeCenter_newUpgrade_Thunk.cpp`|1|246|`{}`|
|715|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdateConstructor.cpp`|1|252|`{}`|
|716|NameKeyType|`game/GameEngine/Source/Common/System/RecorderInitControls_Thunk.cpp`|1|150|`{}`|
|717|NameKeyType|`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManagerLookupByName.cpp`|1|95|`{}`|
|718|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/PhysicsBehaviorRva0029A7D0.cpp`|1|133|`{"UPDATE_SLEEP_NONE": 0}`|
|719|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/LargeGroupBonusUpdateCtorThunk.cpp`|1|191|`{"UPDATE_SLEEP_DUMMY": 0}`|
|720|NameKeyType|`game/GameEngine/Source/GameLogic/Map/SidesList_isPlayerDefaultTeam_Thunk.cpp`|1|380|`{"NameKeyTypeUnknown": 0}`|

Four narrow headers reuse existing native enum definitions and their EA licenses.
The eight broader provider-header edits were withdrawn after an ambiguous EH
pin refusal; their original HEAD compiler contexts are retained. See
../attempt_support/20261118-shared-enum-provider-context.md. No pin, baseline
or verifier was altered. The successful scope requires a fresh consumer/provider
build, actual-header proofs and the normal native shared-header gate.

The native declaration finder also required removing a stale present-unmatched
comment on the already-matched PoisonedBehaviorCtorModuleFactory constructor.
This comment correction changes no body, row or identity; fresh proofs follow.
