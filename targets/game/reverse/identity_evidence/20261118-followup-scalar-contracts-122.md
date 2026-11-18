# Scalar alias contracts: cohort 122

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
|1717|`game/GameEngine/Source/GameLogic/Object/Update/FlammableUpdateOnDamage.cpp`|Bool, Int, Real, UnsignedInt|1|346|
|1718|`game/GameEngine/Source/GameClient/System/ParticleSystem_generateParticleInfo_BFME.cpp`|Bool, Real, Int, UnsignedInt|1|844|
|1719|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjLoadSetting.cpp`|Int, UnsignedInt, Char, Real|1|565|
|1720|`game/GameEngine/Source/GameClient/DrawableVeterancyIcons.cpp`|Int, UnsignedInt, Real, Bool|1|627|
|1721|`game/GameEngine/Source/GameLogic/AI/Rva0015F420GuardRetaliateAttackEnter.cpp`|Int, UnsignedInt, Real, Bool|1|527|
|1722|`game/GameEngine/Source/GameLogic/AI/AIGuardOuterState_onEnter_Bfme.cpp`|Int, UnsignedInt, Bool, Real|1|476|
|1723|`game/GameEngine/Source/GameLogic/AI/AIIdleState_update.cpp`|Bool, UnsignedShort, UnsignedInt, Real|1|404|
|1724|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapIsClearLineOfSight.cpp`|Int, Real, Bool, UnsignedShort|1|1082|
|1725|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardInnerState_onEnter.cpp`|Int, UnsignedInt, Real, Bool|1|411|
|1726|`game/GameEngine/Source/GameNetwork/LANAPIOnHasMap_Bfme.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|709|
|1727|`game/GameEngine/Source/Common/System/BuildAssistant_clearRemovableForConstruction.cpp`|Bool, Real, Int, UnsignedInt|1|438|
|1728|`game/GameEngine/Source/GameLogic/Map/Rva001A7A90AddShrub.cpp`|Bool, Int, UnsignedInt, UnsignedShort, Real|1|311|
|1729|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUI_drawMoveHints.cpp`|Real, Int, UnsignedInt, Bool|1|650|
|1730|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptParseScreenRectThunk.cpp`|Int, Bool, UnsignedInt, Real|1|453|
|1731|`game/GameEngine/Source/Common/System/SaveGame/BfmeGameStateSaveListPopulate.cpp`|Bool, UnsignedShort, UnsignedInt, Int|1|798|
|1732|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsSkirmishSupplies.cpp`|Bool, Int, UnsignedInt, Real|1|835|
|1733|`game/GameEngine/Source/GameClient/InGameUICreateMoveHint.cpp`|Real, Bool, UnsignedInt, Int|1|283|
|1734|`game/GameEngine/Source/GameLogic/AI/Rva00174A20State_update.cpp`|Int, UnsignedInt, UnsignedByte, Bool, Real|1|536|
|1735|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva001FF360.cpp`|Int, UnsignedInt, Real, Bool|1|479|
|1736|`game/GameEngine/Source/Common/System/BuildAssistantAddBibs.cpp`|Bool, Real, Int, UnsignedInt|1|452|
|1737|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitGarrisonNearestBuilding_Thunk.cpp`|Bool, Int, UnsignedInt, Real|1|451|
|1738|`game/GameEngine/Source/GameLogic/AI/Rva003F82C0Pathfinder.cpp`|Int, Bool, Real, UnsignedInt|1|1044|
|1739|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/InsertPlayerInListbox00530550.cpp`|Int, UnsignedInt, Real, Bool|1|479|
|1740|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowManagerRva007B4940.cpp`|Int, Real, Char, Bool|1|718|
|1741|`game/GameEngine/Source/GameLogic/Object/Update/AutoDepositUpdate_update.cpp`|Bool, Int, UnsignedInt, Real|1|649|
|1742|`game/GameEngine/Source/GameLogic/AI/AIGuardInnerState_onEnter_Bfme.cpp`|Int, UnsignedInt, Real, Bool|1|439|
|1743|`game/GameEngine/Source/Common/BfmeUpdateSkirmishBattleHonors.cpp`|Int, UnsignedInt, Real, Bool|1|1932|
|1744|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva00326DA0.cpp`|Bool, Int, UnsignedInt, UnsignedByte, UnsignedShort|1|332|
|1745|`game/GameEngine/Source/GameLogic/AI/AICommandParmsStorageXfer.cpp`|Int, UnsignedInt, Real, Bool|1|805|
|1746|`game/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior_ctor_Thunk.cpp`|Bool, Real, Int, UnsignedInt|1|395|
|1747|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUIDraw.cpp`|Real, Int, UnsignedInt, Bool|1|163|
|1748|`game/GameEngine/Source/GameLogic/Object/PartitionData_updateCellsTouched.cpp`|Int, Bool, Real, UnsignedInt|1|959|
|1749|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_moveToNewRepairSpot.cpp`|UnsignedInt, Int, Real, Bool|1|267|
|1750|`game/GameEngine/Source/GameLogic/Object/Update/SpecialEnemySenseUpdateUpdate.cpp`|Int, Bool, Real, UnsignedInt|1|549|
|1751|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainExitObjectInAHurry.cpp`|Int, UnsignedInt, Real, Bool|1|1040|
|1752|`game/GameEngine/Source/GameLogic/Object/Update/SpecialDisguiseUpdateTriggerAbilityEffect.cpp`|Bool, Int, UnsignedInt, Real|1|433|
|1753|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsEvaluatePlayerHasNumUnitsLoadedWithObject.cpp`|Bool, Int, UnsignedInt, UnsignedByte, UnsignedShort|1|455|
|1754|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainExitObjectViaDoor.cpp`|Int, UnsignedInt, Real, Bool|1|1039|
|1755|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva00270DF0RebuildPath.cpp`|Int, UnsignedInt, Bool, Real|1|424|
|1756|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_setRepairState.cpp`|Bool, Real, Int, UnsignedInt|1|704|
|1757|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyStagingRoomLaunchGame.cpp`|Bool, Int, UnsignedInt, UnsignedShort|1|945|
|1758|`game/GameEngine/Source/Common/System/SaveGame/GameStatePopulateSaveGameListboxBFME.cpp`|Bool, UnsignedShort, UnsignedInt, Int|1|1286|
|1759|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeploySpecialPowerInitiate.cpp`|Bool, Int, UnsignedInt, Real|1|650|
|1760|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsTeamSighted_Rva00328020.cpp`|Bool, Int, Real, UnsignedShort|1|738|
|1761|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva001FECD0.cpp`|Int, UnsignedInt, Real, Bool|1|718|
|1762|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva0032ABC0.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|820|
|1763|`game/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp`|Bool, Int, UnsignedInt, Real|1|654|
|1764|`game/GameEngine/Source/GameClient/EvaConstructor.cpp`|Int, UnsignedInt, Bool, Real|1|379|
|1765|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva00326F40.cpp`|Bool, Int, UnsignedInt, UnsignedByte, UnsignedShort|1|640|
|1766|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva00326C00.cpp`|Bool, Int, UnsignedInt, UnsignedByte, UnsignedShort|1|332|
|1767|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_continuePreparation.cpp`|Bool, Int, Real, UnsignedInt|1|681|
|1768|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_onRemoving.cpp`|Int, UnsignedInt, Bool, Real|1|383|
|1769|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva005307B0ChatPlayerTooltip.cpp`|Int, UnsignedInt, Real, Bool|1|2136|
|1770|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeEngageState_updateInternal.cpp`|Bool, Real, Int, UnsignedInt|1|1314|
|1771|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorComputeAggregateStates.cpp`|Bool, Int, Real, UnsignedInt|1|750|
|1772|`game/GameEngine/Source/GameLogic/Object/Update/CivilianSpawnUpdate.cpp`|Bool, Real, Int, UnsignedInt|1|1025|
|1773|`game/GameEngine/Source/GameClient/System/ParticleSystemUpdate.cpp`|Bool, Int, UnsignedInt, Real|1|1744|
|1774|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_setCorrectDamageState.cpp`|Real, Int, Bool, UnsignedInt|1|1574|
|1775|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva0053AF50StagingPlayerTooltip.cpp`|Int, Bool, Real, UnsignedInt|1|2060|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
