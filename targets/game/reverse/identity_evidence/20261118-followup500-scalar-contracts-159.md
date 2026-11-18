# Scalar alias contracts: cohort 159

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
|3582|`game/GameEngine/Source/GameLogic/Object/ObjectRva001CABE0.cpp`|Bool, UnsignedInt|1|376|
|3583|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva002985D0ClearAbilityBits.cpp`|Bool|1|132|
|3584|`game/GameEngine/Source/Common/Rva0037F050ExperienceQuery.cpp`|Int|1|121|
|3585|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BC540StateAction.cpp`|Int|1|114|
|3586|`game/GameEngine/Source/GameLogic/System/LivingWorld/Glo012F1024Type_enterSelected.cpp`|Int|1|157|
|3587|`game/GameEngine/Source/Common/Rva007692D0LookupCoord.cpp`|Bool|1|118|
|3588|`game/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgradeRemoveUpgrade.cpp`|UnsignedInt|1|180|
|3589|`game/GameEngine/Source/GameLogic/Object/Object_bfmeIsGiantBird.cpp`|Bool|1|25|
|3590|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplaySetTimeOfDayLightScale.cpp`|Int|1|372|
|3591|`game/GameEngine/Source/GameLogic/AI/Rva0017ADC0State_onExit.cpp`|UnsignedInt|1|63|
|3592|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/OptionPreferences_getCampaignDifficulty.cpp`|Int|1|114|
|3593|`game/Libraries/Source/shroudmanager/Rva008F9810BestCellPoint.cpp`|Real|1|259|
|3594|`game/GameEngine/Source/GameLogic/Object/Locomotor_rva001B5B40.cpp`|Real|1|144|
|3595|`game/GameEngine/Source/GameLogic/Object/Collide/AODCrushCollideModuleDataConstructor.cpp`|Int|1|126|
|3596|`game/GameEngine/Source/GameLogic/LivingWorld/BfmeLwcmFindByKey.cpp`|Int, UnsignedShort|1|216|
|3597|`game/GameEngine/Source/GameLogic/AI/PathUpdateLastNode.cpp`|Bool, Real|1|109|
|3598|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva002E55C0LuaFile.cpp`|Int|1|156|
|3599|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupPlayerInfoLookupRankImage.cpp`|Int|1|434|
|3600|`game/GameEngine/Source/GameNetwork/GameInfo_allSameTeam.cpp`|Bool|1|174|
|3601|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BC400StateAction.cpp`|Int|1|89|
|3602|`game/GameEngine/Source/GameLogic/Object/Update/BloodthirstyUpdateModuleDataConstructor.cpp`|Int|1|119|
|3603|`game/GameEngine/Source/GameLogic/Object/Upgrade/UpgradeMux_wouldUpgrade.cpp`|Bool, UnsignedInt|1|180|
|3604|`game/GameEngine/Source/Common/GameLODManagerGetStaticGameLODIndex.cpp`|Int|1|206|
|3605|`game/GameEngineDevice/Source/W3DDevice/Common/System/Gen006C1A20ImageState.cpp`|UnsignedInt|1|182|
|3606|`game/GameEngine/Source/GameClient/GUI/ControlBar/CommandButtonRva0049B9B0.cpp`|UnsignedInt|1|160|
|3607|`game/GameEngine/Source/GameClient/GUI/ControlBar/CommandSet_parseCommandButton.cpp`|Int|1|207|
|3608|`game/GameEngine/Source/GameLogic/AI/Rva003D5B70CellPredicate.cpp`|Int|1|94|
|3609|`game/GameEngine/Source/Common/UpgradePairTreeWide.cpp`|Int|1|185|
|3610|`game/GameEngine/Source/GameNetwork/GameSpy/PeerDefsGroupRoomMapOperator.cpp`|Int|1|215|
|3611|`game/GameEngine/Source/GameLogic/Object/SpecialPower/OCLSpecialPowerDoSpecialPowerAtObject.cpp`|UnsignedInt|1|40|
|3612|`game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseTokenEvents.cpp`|Int|1|246|
|3613|`game/GameEngine/Source/GameLogic/Object/SpecialPower/TaintSpecialPowerDoSpecialPowerAtLocation.cpp`|UnsignedInt|1|73|
|3614|`game/GameEngine/Source/Common/Rva0006AB90FunctionCurveAddKey.cpp`|Int|1|275|
|3615|`game/GameEngine/Source/GameClient/System/ParticleIsInvisible.cpp`|Bool|1|107|
|3616|`game/GameEngine/Source/GameLogic/AI/PathfindZoneCollapse.cpp`|Int|1|178|
|3617|`game/GameEngine/Source/Common/UpgradePairTree.cpp`|Int, Real|1|185|
|3618|`game/GameEngine/Source/Common/RTS/Player_applyBattlePlanBonusesForPlayerObjects_Thunk.cpp`|UnsignedInt|1|289|
|3619|`game/GameEngine/Source/Common/Rva003C1050NormalizeUpgradeMask.cpp`|UnsignedInt|1|250|
|3620|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdateXfer.cpp`|Real|1|119|
|3621|`game/GameEngine/Source/GameLogic/Object/WeaponEffects/Made001E6170Constructor.cpp`|Int|1|86|
|3622|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006DED60RoadBuffer_rva006DEB70.cpp`|Int|1|181|
|3623|`game/GameEngine/Source/Common/System/SaveGame/GameStateRva001127F0LoadByFilename.cpp`|Bool, Int|1|254|
|3624|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseTooltip.cpp`|Bool|1|121|
|3625|`game/GameEngine/Source/Common/BfmeConv1964.cpp`|Bool|1|100|
|3626|`game/GameEngine/Source/GameLogic/LivingWorld/Rva0020CA90Attack.cpp`|Int, Bool|1|158|
|3627|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadTrackStatsForPlayer.cpp`|Int|1|252|
|3628|`game/GameEngine/Source/Common/CommandLine_parseMod.cpp`|Int|1|478|
|3629|`game/GameEngineDevice/Source/W3DDevice/GameClient/BFMERetailWorldHeightMapBlendTileData.cpp`|UnsignedShort|1|91|
|3630|`game/GameEngine/Source/GameClient/GameClientAddTOCEntry.cpp`|UnsignedShort|1|168|
|3631|`game/GameEngine/Source/GameLogic/ScriptEngine/BfmeScriptCondAreaGate.cpp`|Bool|1|77|
|3632|`game/GameEngine/Source/Common/RTS/PlayerListXfer.cpp`|UnsignedByte|1|134|
|3633|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doHideCounter.cpp`|Int|1|178|
|3634|`game/GameEngine/Source/Common/Thing/Rva001417F0ModuleInfoClear.cpp`|Bool|1|97|
|3635|`game/GameEngine/Source/Common/Thing/ObjectModuleConstructor.cpp`|Int|1|131|
|3636|`game/GameEngine/Source/Common/Thing/ThingTemplate_calcCostToBuild.cpp`|Real|1|131|
|3637|`game/GameEngine/Source/Common/Bfme5MakeAndAppend.cpp`|Bool|1|108|
|3638|`game/GameEngine/Source/Common/Thing/BFMEThingFactory_newDrawable.cpp`|Int|1|38|
|3639|`game/Libraries/Source/WWVegas/WWLib/RvaHashResizeAsciiString006136C0.cpp`|Int, Bool|1|418|
|3640|`game/GameEngine/Source/GameLogic/AI/PathfinderBuildHierarchicalPath.cpp`|Bool|1|275|
|3641|`game/GameEngine/Source/GameLogic/ScriptEngine/AttackPriorityInfoGetPriority.cpp`|Int|1|82|
|3642|`game/GameEngine/Source/GameLogic/AI/Rva00178E30ComputePath.cpp`|Bool|1|88|
|3643|`game/GameEngine/Source/Common/Rva001C2E50Xfer.cpp`|UnsignedByte|1|223|
|3644|`game/GameEngine/Source/GameLogic/AI/AIGroupConstructor.cpp`|UnsignedInt|1|197|
|3645|`game/GameEngine/Source/GameLogic/AI/Rva0018D4F0TurretStateUpdate.cpp`|UnsignedInt|1|104|
|3646|`game/GameEngine/Source/Common/S3CachedThresholdTest.cpp`|Real|1|68|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
