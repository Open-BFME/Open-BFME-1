# Shared enum contracts, cohort 105

Native reusable dependency receipts remain unavailable for `game/GameEngine/Source/GameLogic/Object/Die/CrushDieOnDie.cpp`. Each instead has a fresh actual-source private ordinary compile with strict whole-runtime equality, plus its actual type/include proof and successful normal byte build. This supports source-contract preservation only; no current-provider or LINKED preview is claimed.

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
|852|ObjectID|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate_xferMethodThunk.cpp`|1|350|`{"INVALID_OBJECT_ID": 0}`|
|853|ObjectID|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule_aboutToDoSpecialPower.cpp`|1|379|`{}`|
|854|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Object_rva001CBC20DefectionComplete.cpp`|1|257|`{"INVALID_NAME_KEY": 0, "NAME_KEY_MAX": 2147483647, "NAME_KEY_MIN": -2147483648}`|
|855|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupReplayInit_Thunk.cpp`|1|386|`{}`|
|856|ObjectID|`game/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior_doPhaseStuff_Thunk.cpp`|1|504|`{"INVALID_OBJECT_ID": 0}`|
|857|NameKeyType|`game/GameEngine/Source/GameClient/GUI/Rva0059E320MainMenuMediumInit.cpp`|1|293|`{}`|
|858|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_ctor_Thunk.cpp`|1|252|`{}`|
|859|ObjectID|`game/GameEngine/Source/GameLogic/Object/Behavior/Rva00200DF0OnDie.cpp`|1|525|`{"INVALID_OBJECT_ID": 0}`|
|860|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/grabWindowPointers.cpp`|1|714|`{}`|
|861|ObjectID|`game/GameEngine/Source/GameLogic/AI/TeamInQueueXfer.cpp`|1|420|`{"BFME_OBJECT_ID_INVALID": 0}`|
|862|NameKeyType|`game/GameEngine/Source/GameLogic/System/CastleBehaviorRva0036F4D0EvaNotify.cpp`|1|504|`{}`|
|863|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_update_Thunk.cpp`|1|467|`{}`|
|864|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehaviorConstructor.cpp`|1|297|`{}`|
|865|ObjectID|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorCtorThunk.cpp`|1|661|`{}`|
|866|ObjectID|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doPlaySoundEffectAtTeam.cpp`|1|242|`{}`|
|867|NameKeyType|`game/GameEngine/Source/GameClient/MapCacheAddMap.cpp`|1|1394|`{"Rva004570F0Key": 0}`|
|868|ObjectID|`game/GameEngine/Source/GameLogic/System/Rva00375A00Xfer.cpp`|1|873|`{"INVALID_OBJECT_ID": 0}`|
|869|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/GiveUpgradeUpdateUpdate.cpp`|1|278|`{}`|
|870|NameKeyType|`game/GameEngine/Source/GameLogic/System/EmotionNugget.cpp`|1|543|`{"InvalidKey": -1}`|
|871|NameKeyType|`game/GameEngine/Source/Common/RTS/PlayerConstructor.cpp`|1|898|`{}`|
|872|NameKeyType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineGetPlayerMaskFromAsciiString.cpp`|1|635|`{}`|
|873|NameKeyType|`game/GameEngine/Source/Common/RTS/UnitRevivalTracker.cpp`|1|350|`{"Rva000FA1B0InvalidNameKey": 0}`|
|874|DrawableID|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualAddFactionBibDrawable.cpp`|1|780|`{"DRAWABLE_ID_ZERO": 0}`|
|875|ObjectID|`game/GameEngine/Source/GameLogic/Object/FiringTrackerBFMEXfer.cpp`|1|200|`{"INVALID_OBJECT_ID": 0}`|
|876|ObjectID|`game/GameEngine/Source/GameLogic/Object/Update/Rva00257DB0PartitionScan.cpp`|1|817|`{}`|
|877|NameKeyType|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_getStarImage_Thunk.cpp`|1|208|`{}`|
|878|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/PhysicsBehaviorUpdate.cpp`|1|862|`{}`|
|879|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/MemberSelection00244680.cpp`|1|624|`{}`|
|880|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdateUpdate.cpp`|1|464|`{}`|
|881|NameKeyType|`game/GameEngine/Source/Common/ExperienceLevelSystemRva0037F280.cpp`|1|459|`{}`|
|882|ObjectID|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRotateCameraOneFrameBfme.cpp`|1|676|`{"FORCE_OBJECTID_TO_LONG_SIZE": 2147483647}`|
|883|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/RainOfFireUpdate.cpp`|1|789|`{}`|
|884|ObjectID|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdateConstructorBfme.cpp`|1|464|`{"FORCE_OBJECTID_TO_LONG_SIZE": 2147483647}`|
|885|NameKeyType|`game/GameEngine/Source/GameClient/InGameUISelectDrawable.cpp`|1|350|`{}`|
|886|ObjectID|`game/GameEngine/Source/GameLogic/Object/ObjectAttemptHealingFromSoleBenefactor.cpp`|1|342|`{}`|
|887|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateWaypointPath.cpp`|1|398|`{}`|
|888|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGameSystem.cpp`|1|764|`{}`|
|889|NameKeyType|`game/GameEngine/Source/GameClient/InGameUI_playCameoMovie.cpp`|1|273|`{}`|
|890|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/BannerCarrierUpdate_update.cpp`|1|313|`{}`|
|891|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/BfmeConv2025.cpp`|1|190|`{"CMD_TP_2": 2}`|
|892|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdateUpdateBfme.cpp`|1|347|`{}`|
|893|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/hideWindows.cpp`|1|1186|`{}`|
|894|ObjectID|`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollide_executeCrateBehavior.cpp`|1|381|`{}`|
|895|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehaviorUpdate.cpp`|1|570|`{}`|
|896|ObjectID|`game/GameEngine/Source/GameLogic/Object/Object_notifyRva001C8830.cpp`|1|336|`{"OBJECT_ID_INVALID": 0}`|
|897|NameKeyType|`game/GameEngine/Source/GameLogic/World/ParseObjectDataChunk_Thunk.cpp`|1|605|`{}`|
|898|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate_doPushOutDocking_Bfme.cpp`|1|446|`{}`|
|899|ObjectID|`game/GameEngine/Source/GameLogic/Map/Bridge.cpp`|1|317|`{}`|
|900|ObjectID|`game/GameEngine/Source/GameLogic/Object/WeaponTemplate_shouldProjectileCollideWith.cpp`|1|428|`{"INVALID_OBJECT_ID": 0}`|
|901|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/FoundationAIUpdate.cpp`|1|657|`{}`|
|902|DrawableID|`game/GameEngine/Source/GameLogic/Map/Rva001A7A90AddShrub.cpp`|1|311|`{}`|
|903|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContainUpdate.cpp`|1|365|`{"UPDATE_SLEEP_NONE": 0}`|
|904|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehaviorUpdate.cpp`|1|1067|`{}`|
|905|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupJoinGameInit.cpp`|1|510|`{}`|
|906|ObjectID|`game/GameEngine/Source/GameLogic/AI/Rva00173B90State_onEnter.cpp`|1|178|`{"INVALID_OBJECT_ID": 0}`|
|907|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Upgrade/ObjectCreationUpgradeUpdate.cpp`|1|552|`{"NAME_KEY_NONE": 0}`|
|908|ObjectID|`game/GameEngine/Source/GameClient/SuperweaponInfoCtor.cpp`|1|236|`{"OBJECTID_NONE": 0}`|
|909|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/Behavior/RunOffMapBehaviorRva00205440.cpp`|1|354|`{}`|
|910|ObjectID|`game/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorOnHealing.cpp`|1|388|`{}`|
|911|CommandSourceType|`game/GameEngine/Source/GameLogic/AI/AITNGuardMachineLookForInnerTarget.cpp`|1|437|`{}`|
|912|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/FloatUpdateUpdate.cpp`|1|683|`{}`|
|913|ObjectID|`game/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelperUpdate.cpp`|1|552|`{}`|
|914|NameKeyType|`game/GameEngine/Source/GameLogic/ScriptEngine/Condition_ParseConditionDataChunk_Thunk.cpp`|1|800|`{}`|
|915|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/StateTransition002A32D0.cpp`|1|463|`{}`|
|916|NameKeyType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamHuntWithCommandButton.cpp`|1|895|`{}`|
|917|CommandSourceType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitGarrisonNearestBuilding_Thunk.cpp`|1|451|`{}`|
|918|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/HordeAIUpdate_update.cpp`|1|212|`{}`|
|919|ObjectID|`game/GameEngine/Source/GameLogic/AI/AIMoveAwayFromRepulsorsState_onEnter_Thunk.cpp`|1|197|`{"INVALID_OBJECT_ID": 0}`|
|920|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/AutoDepositUpdate_update.cpp`|1|649|`{}`|
|921|NameKeyType|`game/GameEngine/Source/GameClient/InGameUISiegeDockSelection.cpp`|1|541|`{}`|
|922|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupHostGameInit.cpp`|1|1253|`{}`|
|923|ObjectID|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_addValidObjectsToGarrisonPoints.cpp`|1|489|`{}`|
|924|CommandSourceType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_TeamRepairNearest_Rva00303670.cpp`|1|534|`{}`|
|925|ObjectID|`game/GameEngine/Source/GameLogic/AI/AICommandParmsStorageXfer.cpp`|1|805|`{}`|
|926|ObjectID|`game/GameEngine/Source/GameLogic/Object/ObjectAttemptDamageHook.cpp`|1|825|`{}`|
|927|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/UpdateNumPlayersOnline.cpp`|1|1421|`{}`|
|928|ObjectID|`game/GameEngine/Source/GameLogic/Object/Object_rva001CC250.cpp`|1|831|`{}`|
|929|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior_ctor_Thunk.cpp`|1|395|`{}`|
|930|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/setObserverWindows.cpp`|1|1251|`{}`|
|931|ObjectID|`game/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehaviorOnDamage.cpp`|1|514|`{}`|
|932|ObjectID|`game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_computePath_Bfme.cpp`|1|384|`{}`|
|933|ObjectID|`game/GameEngine/Source/GameClient/InGameUIDoXfer.cpp`|1|1453|`{"OBJECTID_NONE": 0}`|
|934|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_markAsDetected.cpp`|1|594|`{"NAMEKEY_NONE": 0}`|
|935|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenInit.cpp`|1|1422|`{}`|
|936|CommandSourceType|`game/GameEngine/Source/GameLogic/AI/AIMoveToState_update_Bfme.cpp`|1|522|`{}`|
|937|NameKeyType|`game/GameEngine/Source/GameLogic/ScriptEngine/VictoryConditionsUpdate.cpp`|1|986|`{}`|
|938|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/SpecialEnemySenseUpdateUpdate.cpp`|1|549|`{}`|
|939|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WanderAIUpdate002C7780.cpp`|1|564|`{}`|
|940|ObjectID|`game/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdateTriggerAbilityEffect.cpp`|1|433|`{"INVALID_OBJECT_ID": 0}`|
|941|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Update/ToggleMountedSpecialAbilityUpdateTriggerAbilityEffect.cpp`|1|406|`{}`|
|942|NameKeyType|`game/GameEngine/Source/GameLogic/AI/AIPlayerFindSupplyCenter.cpp`|1|886|`{}`|
|943|ObjectID|`game/GameEngine/Source/Common/System/BuildAssistant_sellObject.cpp`|1|344|`{}`|
|944|NameKeyType|`game/GameEngine/Source/GameLogic/AI/Rva0014CA60WeaponTargetPredicate.cpp`|1|712|`{}`|
|945|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/WeaponSetGetAbleToAttackSpecificObject.cpp`|1|999|`{}`|
|946|NameKeyType|`game/GameEngine/Source/GameLogic/AI/AIPlayerOnStructureProduced.cpp`|1|613|`{}`|
|947|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Contain/SiegeExit0024AE60.cpp`|1|1070|`{"Key0024AE60Invalid": 0}`|
|948|CommandSourceType|`game/GameEngine/Source/GameClient/InGameUICanSelectedObjectsDoAction.cpp`|1|976|`{}`|
|949|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeploySpecialPowerInitiate.cpp`|1|650|`{}`|
|950|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/populateSideInfo.cpp`|1|1714|`{}`|
|951|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/DetachableRiderUpdate_update.cpp`|1|720|`{}`|
|952|ObjectID|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva001FECD0.cpp`|1|718|`{}`|
|953|DrawableID|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectDoXfer.cpp`|1|840|`{"FORCE_DRAWABLEID_LONG": 2147483647}`|
|954|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp`|1|654|`{}`|
|955|ObjectID|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_onVeterancyLevelChanged.cpp`|1|520|`{}`|
|956|ObjectID|`game/GameEngine/Source/GameLogic/Object/Die/CrushDieOnDie.cpp`|1|486|`{}`|
|957|ObjectID|`game/GameEngine/Source/GameLogic/Object/FiringTrackerShotFired001B3510.cpp`|1|805|`{}`|
|958|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeploySpecialPowerUpdate.cpp`|1|704|`{}`|
|959|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPowerRva00265ED0.cpp`|1|659|`{}`|
|960|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/PopulateInGameDiplomacyPopup.cpp`|1|1203|`{}`|
|961|CommandSourceType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGarrisonNearestBuilding.cpp`|1|536|`{}`|
|962|DrawableID|`game/GameEngine/Source/GameClient/Drawable/Behavior/AnimationSoundClientBehaviorUpdateAnimationSounds.cpp`|1|903|`{}`|
|963|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Update/ToppleUpdateApplyTopplingForce.cpp`|1|832|`{}`|
|964|CommandSourceType|`game/GameEngine/Source/GameLogic/AI/AIPlayerOnUnitProduced.cpp`|1|595|`{}`|
|965|NameKeyType|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptCreateGadget.cpp`|1|1959|`{}`|
|966|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnUpdate.cpp`|1|1025|`{}`|
|967|NameKeyType|`game/GameEngine/Source/GameLogic/Object/Update/FlameStep00294410.cpp`|1|1163|`{"KEY_NONE": 0}`|
|968|DrawableID|`game/GameEngine/Source/GameLogic/Map/TerrainLogicPlaceTree001AD080.cpp`|1|594|`{}`|
|969|NameKeyType|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewBuildCameraTransformBfme.cpp`|1|1322|`{}`|
|970|NameKeyType|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionParseAction.cpp`|1|2545|`{}`|
|971|ObjectID|`game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateStartMoveSound.cpp`|1|566|`{}`|
|972|CommandSourceType|`game/GameEngine/Source/GameLogic/AI/AIGroupScatter.cpp`|1|525|`{}`|
|973|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdSwoopStateOnEnter.cpp`|1|1057|`{}`|
|974|CommandSourceType|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_onExit.cpp`|1|814|`{}`|
