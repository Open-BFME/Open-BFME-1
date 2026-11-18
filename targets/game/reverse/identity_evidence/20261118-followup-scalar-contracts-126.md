# Scalar alias contracts: cohort 126

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
|1960|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishPositionAdditionalImages.cpp`|Int, Bool, Real|1|659|
|1961|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/MessageBox.cpp`|UnsignedInt, Int, Bool|1|680|
|1962|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsNamedEnteredArea.cpp`|Int, UnsignedInt, Bool|1|107|
|1963|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00239950HordeContain.cpp`|Bool, Real, UnsignedInt|1|324|
|1964|`game/GameEngine/Source/GameLogic/AI/AIGuardOuterState_update_Bfme.cpp`|Bool, UnsignedInt, Real|1|360|
|1965|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_KillHordeMembers.cpp`|Int, UnsignedInt, Bool, Real|1|301|
|1966|`game/GameEngine/Source/GameLogic/AI/PathfinderClassifyFence.cpp`|Real, Int, Bool|1|690|
|1967|`game/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate_doDamageLine.cpp`|Real, Bool, Int|1|479|
|1968|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BAA40FoundationLookup.cpp`|Bool, Real, Int|1|353|
|1969|`game/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBoxAddEntryText_Thunk.cpp`|Bool, Int, UnsignedInt|1|357|
|1970|`game/GameEngine/Source/GameLogic/Object/ObjectRva001CD6B0DamageStateConditions.cpp`|Int, UnsignedInt, Bool|1|585|
|1971|`game/GameEngine/Source/GameLogic/System/GameLogic_prepareNewGame_Thunk.cpp`|Bool, Int, UnsignedInt|1|234|
|1972|`game/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior_effectLogic.cpp`|Bool, UnsignedInt, Real|1|243|
|1973|`game/GameEngine/Source/Common/RTS/ActionManager_canRepairObject_Thunk.cpp`|Bool, Int, UnsignedByte|1|316|
|1974|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModLookTowardBfme.cpp`|Real, Int, Bool|1|497|
|1975|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DCommandBarGridDraw.cpp`|Int, UnsignedInt, Real|1|634|
|1976|`game/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem_loadBigFilesFromDirectory.cpp`|Char, Int, Bool|1|459|
|1977|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_isWithinAbilityAbortRange.cpp`|Real, Int, Bool|1|372|
|1978|`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/ShroudCrateCollide_executeCrateBehavior.cpp`|Bool, Int, UnsignedInt|1|160|
|1979|`game/GameEngine/Source/GameLogic/Object/Update/LargeGroupAudioUpdate_update.cpp`|Bool, Int, UnsignedInt|1|274|
|1980|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetPlayersNearestUnitOfTypeToReference.cpp`|Bool, Int, Real|1|344|
|1981|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorInitiateUnpack.cpp`|Bool, Int, UnsignedInt|1|288|
|1982|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerUnitCondition.cpp`|Bool, UnsignedInt, Int|1|944|
|1983|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUI_drawSelectionRegion.cpp`|Int, UnsignedInt, Real|1|340|
|1984|`game/GameEngine/Source/GameLogic/ScriptEngine/SequentialScript_xfer.cpp`|UnsignedByte, UnsignedInt, Int|1|277|
|1985|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule_onSpecialPowerCreationMethodThunk.cpp`|UnsignedInt, Int, Bool|1|304|
|1986|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorUpdate.cpp`|Bool, Int, UnsignedInt|1|492|
|1987|`game/GameEngine/Source/GameLogic/Object/ExperienceTrackerSetExperienceAndLevel.cpp`|Int, Real, Bool|1|137|
|1988|`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/HealCrateCollide_executeCrateBehavior.cpp`|Bool, Int, UnsignedInt|1|152|
|1989|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlayInsertChat.cpp`|Int, Bool, UnsignedInt|1|596|
|1990|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyStagingRoom_CopyCtor.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|395|
|1991|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap_getHeightMapHeight.cpp`|Real, Int, UnsignedShort|1|957|
|1992|`game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar_taintCell_rva006C2710.cpp`|Int, Real, UnsignedByte|1|626|
|1993|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewResetCameraBfme.cpp`|Real, Int, Bool|1|434|
|1994|`game/GameEngine/Source/GameLogic/Object/ObjectCanCrushOrSquish.cpp`|UnsignedByte, UnsignedInt, Bool|1|223|
|1995|`game/GameEngine/Source/GameLogic/Object/WeaponSpawnAndFadeNuggetRva002DE9B0.cpp`|UnsignedInt, Real, Bool|1|325|
|1996|`game/GameEngine/Source/GameLogic/Object/WeaponEffects/MetaImpactNugget.cpp`|Int, UnsignedInt, Real, Bool|1|326|
|1997|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainPips.cpp`|Bool, Int, UnsignedInt|1|190|
|1998|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCircular3.cpp`|Int, Bool, Real|1|991|
|1999|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00243C40HordeMemberCommand.cpp`|Bool, Int, UnsignedInt|1|211|
|2000|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_showShellMap.cpp`|Bool, Int, UnsignedInt|1|289|
|2001|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetupWaypointPathBfme.cpp`|Real, Int, Bool|1|599|
|2002|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeSquishState_computePath.cpp`|Bool, Real, UnsignedInt|1|475|
|2003|`game/GameEngine/Source/GameLogic/Object/Rva001CD300Object.cpp`|Bool, UnsignedInt, Int|1|225|
|2004|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsEvaluateNamedSelected.cpp`|Bool, Int, UnsignedInt|1|211|
|2005|`game/GameEngine/Source/Common/Rva004B0D40.cpp`|Int, UnsignedInt, Real|1|979|
|2006|`game/GameEngine/Source/GameLogic/Object/ObjectRva001CEE10.cpp`|Bool, Int, UnsignedInt|1|336|
|2007|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamMoveToNearestObjectOfType.cpp`|Bool, Int, Real|1|280|
|2008|`game/GameEngine/Source/GameLogic/Object/WeaponSet_updateWeaponSet.cpp`|Int, Bool, UnsignedInt|1|379|
|2009|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate_followWaypointPath.cpp`|Bool, Int, Real|1|435|
|2010|`game/GameEngineDevice/Source/MilesAudioDevice/Rva0069A2E0Refresh.cpp`|Real, Bool, Int|1|775|
|2011|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002C87B0WorkerXfer.cpp`|UnsignedByte, UnsignedInt, Bool|1|499|
|2012|`game/GameEngine/Source/GameClient/MessageStream/CommandTranslator_issueMoveToLocationCommand.cpp`|Bool, Int, UnsignedInt|1|312|
|2013|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_FireSpecialPowerOnNearestObjectType_Rva002F9C60.cpp`|Bool, Int, Real|1|249|
|2014|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamSetModelCondition.cpp`|Int, Bool, UnsignedInt|1|103|
|2015|`game/GameEngine/Source/Common/System/XferScienceVector.cpp`|UnsignedByte, UnsignedInt, Bool|1|294|
|2016|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_internalChangeHealth.cpp`|Real, Bool, Int|1|592|
|2017|`game/GameEngine/Source/GameLogic/Object/Object_rva001CBC20DefectionComplete.cpp`|UnsignedInt, Bool, Int|1|257|
|2018|`game/GameEngine/Source/GameLogic/AI/PathOptimizeGround.cpp`|Int, Real, Bool|1|590|
|2019|`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/MoneyCrateCollide_executeCrateBehavior.cpp`|Bool, Int, UnsignedInt|1|278|
|2020|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva002FA7C0ScriptAction.cpp`|Bool, Int, Real|1|386|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
