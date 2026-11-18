# Scalar alias contracts: cohort 141

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
|2785|`game/GameEngine/Source/GameLogic/Object/WeaponTemplate_shouldProjectileCollideWith.cpp`|Bool, Int|1|428|
|2786|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeployStyleAIUpdate_aiDoCommand_BFME.cpp`|Bool, Int|1|403|
|2787|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferAddTreeType.cpp`|Int, Real, UnsignedByte|1|661|
|2788|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate_setDockCrippledMethodThunk.cpp`|Int, Bool|1|142|
|2789|`game/GameEngine/Source/GameLogic/AI/Rva001752A0.cpp`|Bool, Real|1|943|
|2790|`game/GameEngine/Source/GameLogic/Object/ObjectSetOrRestoreTeam.cpp`|Bool, Int|1|581|
|2791|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva003273A0SpecialPowerAction.cpp`|Bool, Int|1|201|
|2792|`game/GameEngine/Source/GameLogic/Object/ObjectSetDisabledUntil.cpp`|Bool, UnsignedInt|1|509|
|2793|`game/GameEngine/Source/GameLogic/Object/ObjectGetAbleToAttackSpecificObjectBFME.cpp`|Int, UnsignedInt, Bool|1|331|
|2794|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewInitHeightForMapBfme.cpp`|Real, Bool|1|230|
|2795|`game/GameEngine/Source/GameLogic/AI/Rva00173B90State_onEnter.cpp`|Bool, UnsignedInt|1|178|
|2796|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContain_isSpecificRiderFreeToExit_Thunk.cpp`|Int, Bool|1|126|
|2797|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGiveTeamUpgrade.cpp`|Bool, Int, UnsignedInt|1|195|
|2798|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamFollowSkirmishApproachPath.cpp`|Bool, Int|1|498|
|2799|`game/GameEngine/Source/GameLogic/AI/AIPlayerIsSupplySourceAttacked.cpp`|Bool, UnsignedInt|1|428|
|2800|`game/GameEngine/Source/GameLogic/AI/PathOptimize.cpp`|Int, Bool|1|669|
|2801|`game/GameEngine/Source/GameClient/GUI/SkirmishScreenStateRefreshGameSlot.cpp`|Bool, Int|1|683|
|2802|`game/GameEngine/Source/GameLogic/Object/Upgrade/ObjectCreationUpgradeUpdate.cpp`|Real, UnsignedInt|1|552|
|2803|`game/GameEngine/Source/GameClient/MessageStream/CommandTranslator_issueFireWeaponCommand.cpp`|Bool, UnsignedInt|1|685|
|2804|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadJoinRoomCallback.cpp`|Int, UnsignedInt, Bool|1|626|
|2805|`game/GameEngine/Source/GameLogic/Object/Behavior/RunOffMapBehaviorRva00205440.cpp`|Bool, Real|1|354|
|2806|`game/GameEngine/Source/GameNetwork/LANDisplayGameList.cpp`|Int, Bool, UnsignedShort|1|710|
|2807|`game/GameEngine/Source/GameLogic/AI/AIAttackFollowWaypointPathState_update_Bfme.cpp`|Bool, UnsignedInt|1|342|
|2808|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferAddTreeType.cpp`|Int, Real, UnsignedByte|1|694|
|2809|`game/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelperUpdate.cpp`|UnsignedInt, Real|1|552|
|2810|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContainIsValidContainerFor.cpp`|Bool, Int|1|285|
|2811|`game/GameEngine/Source/GameLogic/ScriptEngine/Condition_ParseConditionDataChunk_Thunk.cpp`|Int, Bool|1|800|
|2812|`game/GameEngine/Source/GameLogic/Object/Contain/CaveContainOnRemoving.cpp`|Bool, UnsignedInt|1|170|
|2813|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptCreateWindow.cpp`|Int, UnsignedInt|1|320|
|2814|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/HordeAIUpdate_update.cpp`|Bool, UnsignedInt|1|212|
|2815|`game/GameEngine/Source/GameClient/MessageStream/SelectionXlatCanSelectDrawable.cpp`|Bool, UnsignedInt|1|370|
|2816|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTransferTeamToPlayer_Rva003028B0.cpp`|Bool, UnsignedInt|1|303|
|2817|`game/GameEngine/Source/GameClient/GUI/Rva0046A870CreateMainWindow.cpp`|UnsignedInt, UnsignedShort|1|448|
|2818|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_addValidObjectsToGarrisonPoints.cpp`|Int, Bool|1|489|
|2819|`game/GameEngine/Source/GameClient/GUI/ControlBar/ArmySummaryHelpText.cpp`|Int, Bool|1|755|
|2820|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva002F7820.cpp`|Bool, UnsignedShort|1|529|
|2821|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainIsValidContainerFor.cpp`|Bool, Int|1|492|
|2822|`game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_computePath_Bfme.cpp`|Bool, Real|1|384|
|2823|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeployStyleAIUpdate_setMyState_BFME.cpp`|Bool, Int, UnsignedInt|1|964|
|2824|`game/GameEngine/Source/GameClient/GUI/BfmeAptScreenSkirmishRva0057BE50.cpp`|Int, UnsignedInt|1|1000|
|2825|`game/GameEngine/Source/GameLogic/Object/Contain/AODHordeContainUpdateFormationMembers.cpp`|Real, UnsignedInt|1|1540|
|2826|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_isPowerCurrentlyInUse.cpp`|Bool, UnsignedInt|1|150|
|2827|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/SkirmishScreenStateRefreshPlayerTypeCombo.cpp`|Bool, Int|1|911|
|2828|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_joinTeam.cpp`|Bool, Int, UnsignedInt|1|296|
|2829|`game/GameEngine/Source/GameNetwork/GameSpy/Chat_addChat.cpp`|Bool, Int|1|955|
|2830|`game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineRegisterScriptFunctions.cpp`|Int, Bool|1|1162|
|2831|`game/GameEngine/Source/GameLogic/AI/AIPlayerOnStructureProduced.cpp`|Bool, Int|1|613|
|2832|`game/GameEngine/Source/GameNetwork/GameSpy/PeerDefsGameSpyInfoReset.cpp`|Bool, Int|1|389|
|2833|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/MemberReleaseMovement00242C90.cpp`|Bool, UnsignedInt|1|791|
|2834|`game/GameEngine/Source/GameLogic/Object/Update/DetachableRiderUpdate_update.cpp`|UnsignedInt, Int|1|720|
|2835|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRva00742920.cpp`|Int, Real|1|726|
|2836|`game/GameEngine/Source/GameClient/InGameUIRva00446550.cpp`|Bool, Int|1|756|
|2837|`game/GameEngine/Source/Common/Gen006091B0FlagBroadcast.cpp`|Bool, UnsignedInt|1|226|
|2838|`game/GameEngine/Source/Common/U4Sink0060D3B0_push.cpp`|Bool, Int, UnsignedInt|1|451|
|2839|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/PopulateInGameDiplomacyPopup.cpp`|Int, Bool|1|1203|
|2840|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule_initiateIntentToDoSpecialPower.cpp`|Bool, UnsignedInt|1|488|
|2841|`game/GameEngine/Source/GameLogic/Object/Collide/SquishCollide.cpp`|Real, Bool|1|1138|
|2842|`game/GameEngine/Source/GameLogic/AI/AIPlayerBuildUpgrade.cpp`|Bool, Int|1|1089|
|2843|`game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapRva0074ACB0Load.cpp`|Int, Bool|1|1511|
|2844|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineHome.cpp`|Int, Real|1|2787|
|2845|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawAttachableSubModels.cpp`|Int, UnsignedInt|1|863|
|2846|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardMachine_lookForInnerTarget.cpp`|Bool, Real|1|1106|
|2847|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0023B7A0HordeContainView.cpp`|Bool, UnsignedInt|1|465|
|2848|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionParseAction.cpp`|Int, Bool|1|2545|
|2849|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doForceObjectSelection_Thunk.cpp`|Bool, Int, Real|1|481|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
