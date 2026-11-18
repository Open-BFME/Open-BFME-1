# Scalar alias contracts: cohort 138

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
|2592|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoUpdatePlayerInfo.cpp`|Int, Bool|1|167|
|2593|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupSaveLoadSetEditDescription.cpp`|Int, Bool|1|361|
|2594|`game/GameEngine/Source/Common/System/GeometryInfoSet.cpp`|Bool, Real|1|273|
|2595|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00238BC0HordeContainMemberCount.cpp`|Int, UnsignedInt|1|261|
|2596|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DSupplyDrawUpdate.cpp`|Int, Bool|1|384|
|2597|`game/GameEngine/Source/Common/Thing/ThingTemplateIsEquivalentTo.cpp`|Bool, Int|1|486|
|2598|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainAnyMemberHeldByAI.cpp`|Bool, UnsignedInt|1|76|
|2599|`game/GameEngine/Source/GameLogic/Object/Locomotor_query.cpp`|Bool, Real|1|297|
|2600|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCircular2.cpp`|Int, Bool|1|683|
|2601|`game/GameEngine/Source/GameLogic/Object/Object_bfmeSingleBoxBoundaryDistanceSquared2D.cpp`|Int, Real|1|625|
|2602|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBufferLoadMapBridges.cpp`|Real, Bool|1|360|
|2603|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfo_removeBuddy.cpp`|Int, Bool|1|150|
|2604|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PositionStartSpotControls.cpp`|Int, Bool, Real|1|427|
|2605|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0023D720HordeContainGainLevel.cpp`|Bool, UnsignedInt|1|242|
|2606|`game/GameEngine/Source/GameClient/LightPointSystemRva0039C260.cpp`|Int, UnsignedInt|1|287|
|2607|`game/GameEngine/Source/GameLogic/AI/AIRampageState_onEnter_Bfme.cpp`|Bool, UnsignedInt|1|285|
|2608|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainOnObjectCreated.cpp`|Bool, UnsignedInt|1|150|
|2609|`game/GameEngine/Source/GameNetwork/Rva005A9BD0.cpp`|Int, UnsignedInt|1|145|
|2610|`game/GameEngine/Source/GameClient/GUI/Rva0051DA30StartGameMode7.cpp`|Bool, Int|1|163|
|2611|`game/GameEngine/Source/GameLogic/AI/pathfind_tightenPath.cpp`|Int, Bool, Real|1|143|
|2612|`game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchSendRoomUtmEUI.cpp`|Int, Bool, UnsignedInt, UnsignedShort|1|190|
|2613|`game/GameEngine/Source/GameLogic/Object/Contain/Rva002459D0HordeMemberAdd.cpp`|Bool, Int|1|267|
|2614|`game/GameEngine/Source/Common/RTS/TeamPrototype_hasAnyBuildings.cpp`|Bool, UnsignedInt|1|190|
|2615|`game/GameEngine/Source/GameLogic/Object/Behavior/PassiveAreaEffectBehavior_update.cpp`|Bool, UnsignedInt|1|157|
|2616|`game/GameEngine/Source/GameClient/Drawable_drawEnthusiastic.cpp`|UnsignedInt, Real|1|511|
|2617|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContain_onContaining.cpp`|Int, Bool|1|154|
|2618|`game/GameEngine/Source/GameLogic/AI/AIGuardRetaliateReturnState_update.cpp`|Bool, UnsignedInt|1|226|
|2619|`game/GameEngine/Source/GameLogic/AI/PathfindLayerConnectsZones.cpp`|Bool, Int|1|328|
|2620|`game/GameEngine/Source/Common/System/SaveGame/addGameToAvailableList_Thunk.cpp`|UnsignedShort, Bool|1|280|
|2621|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamMoveToNearestObjectOfKindOfOwnedByPlayer.cpp`|Bool, Real|1|478|
|2622|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateBuildPath00271010.cpp`|Int, Bool|1|553|
|2623|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardReturnState_onEnter.cpp`|Int, UnsignedInt, Bool|1|230|
|2624|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamReachedWaypointsEnd.cpp`|Bool, Int|1|416|
|2625|`game/GameEngine/Source/Common/Rva00618740MoveArmyToPosition.cpp`|Bool, UnsignedInt|1|111|
|2626|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsNamedBaseUnpackableForPlayer.cpp`|Bool, UnsignedShort|1|387|
|2627|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/FoundationAIUpdateCtor.cpp`|Int, Bool|1|190|
|2628|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/updateBuddyStatus.cpp`|Int, Bool|1|580|
|2629|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doExitSpecificBuilding.cpp`|Bool, UnsignedInt|1|122|
|2630|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/populateQMColorComboBox_Thunk.cpp`|Bool, Int|1|406|
|2631|`game/GameEngine/Source/GameClient/MessageStream/Rva005AD330CommandTranslator_issueCombatDropCommand.cpp`|Bool, UnsignedInt|1|310|
|2632|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineSetPriorityThing.cpp`|Bool, Int|1|703|
|2633|`game/GameEngine/Source/GameLogic/System/GameLogicLoadPostProcess.cpp`|UnsignedInt, Int|1|469|
|2634|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenChallengeMedals_Thunk.cpp`|Bool, Int|1|320|
|2635|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamStartSequentialScript.cpp`|Bool, Int|1|286|
|2636|`game/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse_initCursorResources.cpp`|Int, Bool|1|367|
|2637|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainReleaseMember.cpp`|Bool, UnsignedInt|1|79|
|2638|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptParseLayoutBlockThunk.cpp`|UnsignedInt, Bool|1|526|
|2639|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain_getMembers.cpp`|Int, UnsignedInt|1|286|
|2640|`game/GameEngine/Source/GameLogic/AI/AIPlayerComputeCenterAndRadiusOfBase.cpp`|Int, Real|1|503|
|2641|`game/GameEngine/Source/GameClient/MessageStream/CommandTranslator_issueCombatDropCommand.cpp`|Bool, UnsignedInt|1|332|
|2642|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRva00744360.cpp`|Int, Bool, Real|1|358|
|2643|`game/GameEngine/Source/GameLogic/LargeGroupAudio/Rva003D1020AudioMapXfer.cpp`|Bool, UnsignedShort|1|500|
|2644|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00345a50.cpp`|Bool, Int|1|464|
|2645|`game/GameEngine/Source/GameNetwork/GameSpy/MainMenuUtilsConfigCallback.cpp`|Int, Bool|1|464|
|2646|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_rva001F1B90.cpp`|Bool, Real|1|260|
|2647|`game/GameEngine/Source/GameLogic/AI/AITNGuardInnerState_onEnter.cpp`|UnsignedInt, Bool|1|197|
|2648|`game/GameEngine/Source/Common/LadderPreferences_loadProfile_Bfme.cpp`|Int, Bool|1|921|
|2649|`game/Libraries/Source/WWVegas/WWLib/stlport_hashtable_uint_int_insert.cpp`|Int, UnsignedInt|1|111|
|2650|`game/GameEngine/Source/GameLogic/Object/Update/Rva00272CD0RefreshCachedFlags.cpp`|Bool, UnsignedInt|1|232|
|2651|`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/CrateCollide_isValidToExecute.cpp`|Bool, Int|1|260|
|2652|`game/GameEngine/Source/GameLogic/System/GameLogicRegisterObject.cpp`|UnsignedInt, Int|1|298|
|2653|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/CreditsMenuInit_Thunk.cpp`|Bool, Int|1|407|
|2654|`game/GameEngine/Source/GameClient/GUI/Palantir/PalantirRankAndButtons00590480.cpp`|Int, Bool|1|498|
|2655|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DFloorBufferDoXfer.cpp`|Int, Bool|1|589|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
