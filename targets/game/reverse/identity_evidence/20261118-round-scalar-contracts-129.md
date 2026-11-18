# Scalar alias contracts: cohort 129

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
|2092|`game/GameEngine/Source/GameClient/MessageStream/GUICommandTranslator_doAttackMoveCommand.cpp`|Bool, Int, UnsignedInt|1|170|
|2093|`game/GameEngine/Source/GameLogic/Object/Contain/Rva002377A0HordeContain.cpp`|Bool, UnsignedInt, Int|1|336|
|2094|`game/GameEngine/Source/GameNetwork/NetPacket_addCommand.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|408|
|2095|`game/GameEngine/Source/GameLogic/Object/SpecialPower/GrabPassengerSpecialPowerDoSpecialPowerAtObject.cpp`|UnsignedInt, Int, Bool|1|383|
|2096|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva002F9FF0.cpp`|Bool, Int, Real|1|588|
|2097|`game/GameEngine/Source/GameClient/DrawableGetHealthBoxPosition.cpp`|UnsignedByte, UnsignedInt, Bool|1|212|
|2098|`game/GameEngine/Source/GameClient/MessageStream/Rva005ACD40AttackCommand.cpp`|Bool, Int, UnsignedInt|1|456|
|2099|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawModuleDataParseConditionState.cpp`|Int, UnsignedInt, Bool|1|748|
|2100|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineCheckConditionsForTeamNames.cpp`|Bool, Int, UnsignedInt|1|783|
|2101|`game/GameEngine/Source/GameLogic/Object/Object_getWorldspaceBestContactPoint.cpp`|Bool, Int, UnsignedInt|1|609|
|2102|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PlayerLeftCallback.cpp`|Int, Bool, UnsignedInt, UnsignedShort|1|559|
|2103|`game/GameEngine/Source/GameLogic/Object/Update/ProductionUpdate_queueUpgrade.cpp`|Int, UnsignedInt, Bool|1|307|
|2104|`game/GameEngine/Source/GameLogic/Object/ObjectRva001CFF30.cpp`|Bool, Int, UnsignedInt|1|532|
|2105|`game/GameEngine/Source/GameClient/GUI/Gadget/GadgetListboxCreateScrollbar.cpp`|Int, UnsignedInt, Bool|1|879|
|2106|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00266EB0SiegeDeployBaseTransition.cpp`|Int, Bool, UnsignedInt|1|684|
|2107|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMergeTeamIntoTeam.cpp`|Bool, Int, UnsignedInt|1|457|
|2108|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateVirtual.cpp`|Int, UnsignedInt, Bool|1|684|
|2109|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva003F5C70.cpp`|Int, Bool, Real|1|335|
|2110|`game/GameEngine/Source/GameClient/Drawable_setCaptionText.cpp`|UnsignedByte, Int, Real|1|381|
|2111|`game/GameEngine/Source/GameLogic/AI/PathfinderProcessHierarchicalCell.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|711|
|2112|`game/GameEngine/Source/GameLogic/AI/AIMeleeReAcquireState_update.cpp`|Bool, UnsignedInt, Int|1|553|
|2113|`game/GameEngine/Source/GameLogic/System/ArmySummaryPlayerArmySync.cpp`|Int, Real, Bool|1|498|
|2114|`game/GameEngine/Source/Common/RTS/PlayerBecomingLocal.cpp`|Bool, Int, UnsignedInt, Real|1|748|
|2115|`game/GameEngine/Source/GameClient/InGameUISiegeDockSelection.cpp`|Int, UnsignedInt, Bool|1|541|
|2116|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineNewMap.cpp`|Bool, Int, UnsignedInt|1|1059|
|2117|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehavior_update.cpp`|Bool, UnsignedInt, Real|1|470|
|2118|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferXfer.cpp`|Int, Real, Bool|1|814|
|2119|`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenBWFilterSet.cpp`|Int, Real, Bool|1|1206|
|2120|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_TeamRepairNearest_Rva00303670.cpp`|Bool, Int, Real|1|534|
|2121|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowUpdate.cpp`|Real, Int, Bool|1|758|
|2122|`game/GameEngine/Source/GameLogic/AI/PathfinderBfmeCheckAttackViewAltHelper.cpp`|Int, Bool, Real|1|678|
|2123|`game/GameEngine/Source/GameClient/InGameUI_setRadiusCursor_Thunk.cpp`|Real, Int, Bool|1|531|
|2124|`game/GameEngine/Source/GameLogic/Pathfinder/BfmeAttackQueryCanAttackTarget.cpp`|Int, Bool, Real|1|771|
|2125|`game/GameEngine/Source/GameLogic/Object/Object_rva001CC250.cpp`|Real, Bool, Int|1|831|
|2126|`game/GameEngine/Source/GameLogic/Object/Rva001E7C30WeaponTemplateComputeScatter.cpp`|Real, Int, Bool|1|592|
|2127|`game/GameEngine/Source/GameClient/DrawableHealthBar.cpp`|Bool, UnsignedInt, Real|1|511|
|2128|`game/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetState_stateReturn_Bfme.cpp`|Int, Bool, Real|1|897|
|2129|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DRenderObjectSnapshotXfer.cpp`|UnsignedByte, Int, Bool|1|665|
|2130|`game/GameEngine/Source/GameLogic/Object/Contain/CaveContainRecalcApparentControllingPlayer.cpp`|Bool, Int, UnsignedInt|1|227|
|2131|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSkirmishCommandButtonOnMostValuable_Thunk.cpp`|Bool, Int, Real|1|795|
|2132|`game/GameEngine/Source/Common/GameLODManagerInit.cpp`|Bool, Int, Real|1|1074|
|2133|`game/GameEngine/Source/GameLogic/Object/Object_rva001CEAD0_onVeterancyLevelChanged.cpp`|Bool, Int, UnsignedInt|1|664|
|2134|`game/GameEngine/Source/GameLogic/Object/ObjectQueryRva001CF9F0.cpp`|Bool, UnsignedInt, Int|1|725|
|2135|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamUseCommandButtonOnNearestEnemy.cpp`|Bool, Int, Real|1|713|
|2136|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlaySystem.cpp`|Int, UnsignedInt, Bool|1|784|
|2137|`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenFilterRva007D85C0PostRender.cpp`|Int, Real, Bool|1|1777|
|2138|`game/GameEngine/Source/GameLogic/AI/AIPlayerFindSupplyCenter.cpp`|Bool, Int, Real|1|886|
|2139|`game/GameEngine/Source/GameLogic/Object/Update/ToggleMountedSpecialAbilityUpdateTriggerAbilityEffect.cpp`|Bool, Int, UnsignedInt|1|406|
|2140|`game/GameEngine/Source/GameLogic/AI/Rva0014CA60WeaponTargetPredicate.cpp`|Bool, Int, Real|1|712|
|2141|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderIsAttackViewBlockedByObstacle.cpp`|Int, Real, Bool|1|501|
|2142|`game/GameEngine/Source/GameLogic/Object/WeaponSetGetAbleToAttackSpecificObject.cpp`|Int, UnsignedInt, Bool|1|999|
|2143|`game/GameEngine/Source/GameNetwork/LANAPIHandleRequestLocationsThunk.cpp`|UnsignedInt, UnsignedShort, Bool|1|600|
|2144|`game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs_TearDownGameSpy.cpp`|Int, UnsignedInt, Bool|1|607|
|2145|`game/GameEngine/Source/GameLogic/Pathfinder/AIPathfind_classifyCells.cpp`|Int, Real, Bool|1|1405|
|2146|`game/GameEngine/Source/GameLogic/AI/Rva003F8820Pathfinder.cpp`|Int, Bool, Real|1|1391|
|2147|`game/GameEngine/Source/GameLogic/Object/Update/ProductionUpdateXfer.cpp`|UnsignedByte, UnsignedInt, UnsignedShort|1|1107|
|2148|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva00775470ProjectileLaunchOffset.cpp`|Bool, Int, Real|1|599|
|2149|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectDoXfer.cpp`|UnsignedByte, UnsignedInt, Real|1|840|
|2150|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdateExitObjectViaDoor.cpp`|Real, Int, Bool|1|565|
|2151|`game/GameEngine/Source/GameLogic/AI/AIAttackFireWeaponState_onEnter.cpp`|Bool, Int, UnsignedInt|1|586|
|2152|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DStatusCircleRenderBFME.cpp`|Int, Real, Bool|1|2243|
|2153|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_projectileFireAtObjectOrPosition.cpp`|Real, Bool, Int|1|846|
|2154|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PositionStartSpotsBFME.cpp`|Int, UnsignedInt, Bool|1|1069|
|2155|`game/GameEngine/Source/GameClient/Drawable_drawIconUI_BFME.cpp`|Int, Real, Bool|1|480|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
