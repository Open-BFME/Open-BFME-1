# Scalar alias contracts: cohort 146

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
|3084|`game/GameEngine/Source/GameNetwork/ConnectionManager_processAck.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte|3|235|
|3085|`game/GameEngine/Source/GameNetwork/NetPacket_ackCommands.cpp`|Bool, UnsignedShort, UnsignedByte, UnsignedInt|3|135|
|3086|`game/GameEngine/Source/Common/Rva00382210ExperienceLevelSystem.cpp`|Bool, UnsignedInt, UnsignedShort, Int, Real|3|508|
|3087|`game/GameEngine/Source/Common/System/RAMFile.cpp`|Int, Bool, Char, Real|3|796|
|3088|`game/GameEngine/Source/GameLogic/Object/ObjectHeightAndLayer.cpp`|Int, Bool, Real, UnsignedInt|3|227|
|3089|`game/GameEngine/Source/GameLogic/AI/AISkirmishPlayerAcquireEnemy.cpp`|Bool, Int, UnsignedInt, Real|3|729|
|3090|`game/GameEngine/Source/Common/RTS/PlayerObjectWalk.cpp`|Int, UnsignedInt, Bool, Real|3|310|
|3091|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsMovies.cpp`|Bool, Int, UnsignedInt, Real|3|313|
|3092|`game/GameEngine/Source/Common/RTS/TunnelTracker_getContainCount.cpp`|Int, UnsignedInt, Real, Bool|3|299|
|3093|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorUnpackCost.cpp`|Bool, Int, Real, UnsignedInt|3|574|
|3094|`game/GameEngine/Source/GameLogic/AI/AIPlayerSelectTeamToBuild.cpp`|Bool, Int, UnsignedInt, Real|3|1051|
|3095|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsUseCommandButtonOnNearestThing.cpp`|Bool, Int, Real, UnsignedInt|3|862|
|3096|`game/GameEngine/Source/GameLogic/AI/AerialPathfinder_separationPush.cpp`|Bool, Real, Int, UnsignedInt|3|1613|
|3097|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferConstructor.cpp`|Int, Real, Bool|3|479|
|3098|`game/GameEngine/Source/GameLogic/Map/PolygonTrigger_pointInTrigger.cpp`|Bool, Int, Real|3|833|
|3099|`game/GameEngine/Source/GameClient/System/ParticleSystem_createParticle_Bfme.cpp`|Bool, Int, UnsignedInt|3|380|
|3100|`game/GameEngine/Source/GameClient/System/Campaign_newMission.cpp`|Int, UnsignedInt, UnsignedShort, Bool|3|441|
|3101|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromBottomTimed_initReverseAnimateWindow_Thunk.cpp`|UnsignedInt, Int, Real|3|229|
|3102|`game/GameEngine/Source/GameLogic/ScriptEngine/victory_conditions_create.cpp`|Int, UnsignedInt, Bool|3|254|
|3103|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeContainParseRankInfo.cpp`|Int, Real, Bool|3|728|
|3104|`game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorCtorThunk.cpp`|Int, UnsignedInt, Bool|3|427|
|3105|`game/GameEngine/Source/GameNetwork/NetPacket_readGameMessage.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|3|458|
|3106|`game/GameEngine/Source/GameLogic/AI/PathfinderPickBridge.cpp`|Real, Bool, Int|3|1672|
|3107|`game/GameEngine/Source/GameClient/GUI/Rva00435270ApplyLayout.cpp`|Int, Real, Bool|3|630|
|3108|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsTeamCompare.cpp`|Bool, Real, UnsignedShort|3|494|
|3109|`game/GameEngine/Source/GameLogic/AI/AIFollowPathAsTeamState_onEnter.cpp`|Bool, Real, Int|3|756|
|3110|`game/GameEngine/Source/GameLogic/Object/ObjectCommandButtons.cpp`|Bool, Int, UnsignedInt|3|315|
|3111|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowInitAnimate.cpp`|UnsignedInt, Int, Real|3|724|
|3112|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsCompare.cpp`|Bool, Int, Real|3|572|
|3113|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlayRequestBuddyAdd.cpp`|Bool, Int, UnsignedInt|3|907|
|3114|`game/GameEngine/Source/GameClient/DrawableRegionRenderA.cpp`|UnsignedInt, Int, Real|3|1434|
|3115|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsCommandButton.cpp`|Bool, Int, UnsignedInt|3|560|
|3116|`game/GameEngine/Source/Common/RTS/PlayerBfmeLinkedObjLink.cpp`|Bool, Int, UnsignedInt|3|1775|
|3117|`game/GameEngine/Source/GameLogic/System/GameLogicPopulateGameReport.cpp`|Int, Bool, UnsignedByte|3|2064|
|3118|`game/GameEngine/Source/GameClient/GUI/Gadget/GadgetComboBoxInput.cpp`|Int, Short, Bool, UnsignedInt|3|3225|
|3119|`game/GameEngine/Source/Common/BitFlags11Xfer.cpp`|Int, UnsignedByte|3|187|
|3120|`game/GameEngine/Source/GameLogic/Map/TerrainLogicCountTrees.cpp`|Real, Int|3|139|
|3121|`game/GameEngine/Source/Common/Thing/Thing_isKindOf.cpp`|Int, UnsignedInt, Bool|3|125|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
