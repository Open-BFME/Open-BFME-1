# Scalar alias contracts: cohort 121

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
|1652|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromLeft_reverseAnimateWindow.cpp`|UnsignedInt, Int, Real, Bool|1|262|
|1653|`game/GameEngine/Source/GameNetwork/LANAPIReset.cpp`|Int, UnsignedInt, UnsignedByte, Bool|1|191|
|1654|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateQueryRallyOverride.cpp`|Bool, Int, Real, UnsignedInt|1|429|
|1655|`game/GameEngine/Source/Common/ExperienceLevelListAssignment.cpp`|Bool, UnsignedInt, Int, Real|1|127|
|1656|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromBottom_reverseAnimateWindow.cpp`|UnsignedInt, Int, Real, Bool|1|263|
|1657|`game/GameEngine/Source/Common/System/RadarObjectXfer.cpp`|UnsignedByte, UnsignedInt, Int, Bool|1|170|
|1658|`game/GameEngine/Source/Common/ExperienceLevelListMerge.cpp`|Bool, UnsignedInt, Int, Real|1|167|
|1659|`game/GameEngine/Source/GameLogic/AI/GroundCellsStructCellCallback.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|284|
|1660|`game/GameEngine/Source/Common/Rva001A78B0RecordXfer.cpp`|Bool, Int, UnsignedInt, Short|1|329|
|1661|`game/GameEngine/Source/Common/RTS/TeamRelationMap_xfer.cpp`|Bool, UnsignedInt, UnsignedShort, UnsignedByte|1|269|
|1662|`game/GameEngine/Source/GameClient/System/Anim2DNaturalDrawing.cpp`|Int, Real, UnsignedByte, UnsignedShort|1|199|
|1663|`game/GameEngine/Source/GameNetwork/LANAPISetLocalIP.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|199|
|1664|`game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap_ParseSizeOnly_Thunk.cpp`|Int, Bool, UnsignedShort, UnsignedByte|1|526|
|1665|`game/GameEngine/Source/GameNetwork/NATSendMangledPortNumberToTarget.cpp`|UnsignedShort, UnsignedInt, Int, Bool|1|388|
|1666|`game/GameEngine/Source/GameClient/System/Rva005BA9E0Anim2DWorldDraw.cpp`|Int, Real, UnsignedByte, UnsignedShort|1|187|
|1667|`game/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelperXfer.cpp`|UnsignedByte, UnsignedInt, Int, Bool|1|290|
|1668|`game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapParseHeightMapData.cpp`|Int, Bool, UnsignedShort, UnsignedByte|1|504|
|1669|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_gainOneBox.cpp`|Bool, Int, UnsignedInt, Real|1|286|
|1670|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowManagerRva007B3E70.cpp`|Int, Real, Char, Bool|1|460|
|1671|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsHasCommandPointsToBuildTeam.cpp`|Bool, Int, Real, UnsignedShort|1|364|
|1672|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva0032A550.cpp`|Int, Real, UnsignedShort, Bool|1|348|
|1673|`game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapGetExtraAlphaUVData.cpp`|Int, Short, Bool, UnsignedByte|1|423|
|1674|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer_clearAllTrees.cpp`|Int, Real, UnsignedInt, UnsignedByte|1|278|
|1675|`game/GameEngine/Source/GameLogic/ScriptEngine/AttackPriorityInfoXfer.cpp`|UnsignedByte, UnsignedShort, Int, Bool|1|375|
|1676|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsAnyUnitsUsingBloodthirsty.cpp`|Bool, Int, UnsignedByte, UnsignedShort|1|186|
|1677|`game/GameEngine/Source/GameLogic/System/VictorySystemNewMap.cpp`|Int, UnsignedInt, Real, Bool|1|747|
|1678|`game/GameEngine/Source/GameClient/InGameUI_addFloatingText.cpp`|UnsignedByte, UnsignedInt, Int, Real|1|302|
|1679|`game/GameEngine/Source/GameLogic/Object/Weapon_setClipPercentFull.cpp`|Int, UnsignedInt, Real, Bool|1|288|
|1680|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva0071D5E0.cpp`|Int, Bool, Real, UnsignedInt|1|809|
|1681|`game/GameEngine/Source/GameNetwork/LANAPIRequestGameLeave.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|341|
|1682|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContain/Rva00245010RecordBuild.cpp`|Int, UnsignedInt, Real, Bool|1|828|
|1683|`game/GameEngine/Source/GameLogic/Object/Update/BfmeTargetXIUseXI.cpp`|Bool, Int, UnsignedInt, Real|1|427|
|1684|`game/GameEngine/Source/GameLogic/Object/Body/Rva0020F240DoDamageFX.cpp`|Bool, Int, UnsignedInt, Real|1|185|
|1685|`game/GameEngine/Source/Common/System/XferMapAsciiStringReal.cpp`|UnsignedByte, UnsignedInt, Bool, Real|1|414|
|1686|`game/GameEngine/Source/GameClient/InGameUI_updateFloatingText.cpp`|Int, UnsignedInt, UnsignedByte, Real|1|314|
|1687|`game/GameEngine/Source/GameLogic/Map/WaypointXfer.cpp`|UnsignedByte, UnsignedInt, Int, Bool, Real|1|648|
|1688|`game/GameEngine/Source/GameLogic/Object/Behavior/SiegeDockingBehaviorXfer.cpp`|UnsignedByte, UnsignedInt, Int, Bool|1|393|
|1689|`game/GameEngine/Source/GameLogic/Object/WeaponEffects/LuaEventNugget.cpp`|Int, UnsignedInt, Real, Bool|1|428|
|1690|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva00734270.cpp`|Int, Bool, Real, UnsignedInt|1|953|
|1691|`game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DTerrainLogicLoadMap.cpp`|Bool, Int, Real, UnsignedShort|1|607|
|1692|`game/GameEngine/Source/GameLogic/Map/TerrainLogic_loadMap_Thunk.cpp`|Int, Bool, UnsignedInt, UnsignedShort|1|381|
|1693|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamFlash_Thunk.cpp`|Bool, Int, Real, UnsignedInt|1|282|
|1694|`game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateXfer.cpp`|Int, UnsignedInt, UnsignedShort, Bool|1|435|
|1695|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva0032C680.cpp`|Bool, Int, UnsignedInt, UnsignedByte|1|286|
|1696|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_SkirmishFireSpecialPowerAtMostCost.cpp`|Bool, Int, Real, UnsignedShort|1|265|
|1697|`game/GameEngine/Source/GameLogic/Object/Update/ModelConditionSpecialAbilityUpdate_triggerAbilityEffect.cpp`|Bool, Real, Int, UnsignedInt|1|390|
|1698|`game/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehaviorOnDie.cpp`|Bool, Int, Real, UnsignedInt|1|353|
|1699|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003F1690.cpp`|Int, UnsignedInt, Bool, Real|1|337|
|1700|`game/GameEngine/Source/GameClient/InGameUI_popupMessage_Thunk.cpp`|Bool, Int, UnsignedInt, Real|1|474|
|1701|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardInnerState_update.cpp`|Int, UnsignedInt, Real, Bool|1|175|
|1702|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardIdleState.cpp`|Int, UnsignedInt, Bool, Real|1|290|
|1703|`game/GameEngine/Source/GameLogic/Map/FindPositionAround001AF610.cpp`|Bool, Real, Int, UnsignedInt|1|1139|
|1704|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehaviorConstructor.cpp`|UnsignedInt, Int, Real, Bool|1|297|
|1705|`game/GameEngine/Source/Common/ExperienceLevelConstructor.cpp`|Bool, UnsignedInt, Int, Real|1|267|
|1706|`game/Libraries/Source/file/StreamingArchiveFile.cpp`|Int, Bool, Char, Real|1|263|
|1707|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva003EA570.cpp`|Int, UnsignedInt, Bool, Real|1|775|
|1708|`game/GameEngine/Source/GameLogic/AI/AIPanicState_onEnter_Thunk.cpp`|Bool, Int, Real, UnsignedInt|1|353|
|1709|`game/GameEngine/Source/GameLogic/Object/Update/Rva00257DB0PartitionScan.cpp`|Bool, Int, Real, UnsignedInt|1|817|
|1710|`game/GameEngine/Source/GameLogic/Object/Behavior/ClearanceTestingSlowDeathBehavior.cpp`|Bool, Real, Int, UnsignedInt|1|675|
|1711|`game/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva001FF1C0.cpp`|Int, UnsignedInt, Real, Bool|1|321|
|1712|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_update.cpp`|Bool, Real, Int, UnsignedInt|1|579|
|1713|`game/GameEngine/Source/GameLogic/AI/Rva001695B0AdjustBuildList.cpp`|Bool, Int, Real, UnsignedInt|1|828|
|1714|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamMoveToNearestObjectOfTypeOwnedByPlayer.cpp`|Bool, Int, UnsignedShort, Real|1|519|
|1715|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanLobbyMenuPlayerTooltip.cpp`|Int, Real, UnsignedInt, UnsignedShort, Bool|1|145|
|1716|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_updateSpecialPowerShortcut.cpp`|Int, UnsignedInt, Real, Bool|1|684|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
