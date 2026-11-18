# Scalar alias contracts: cohort 155

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
|3335|`game/GameEngine/Source/Common/Rva000D2FB0BitSetCtor.cpp`|Int|1|48|
|3336|`game/GameEngine/Source/GameClient/Terrain/TerrainRoadTypeSetDamageToFXStringILT.cpp`|Int|1|5|
|3337|`game/GameEngine/Source/Common/Bfme/Rva001B40F0Formula.cpp`|Real|1|63|
|3338|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainParseRankSets.cpp`|Int|1|90|
|3339|`game/GameEngine/Source/GameLogic/Object/Object_isCurWeaponLocked.cpp`|Bool|1|17|
|3340|`game/GameEngine/Source/GameLogic/Object/Weapon_getClipReloadTime.cpp`|UnsignedInt|1|93|
|3341|`game/GameEngine/Source/GameLogic/ScriptEngine/VictoryGameLogicShim.cpp`|Int|1|35|
|3342|`game/GameEngine/Source/GameLogic/AI/Rva002491F0.cpp`|Int, Bool|1|75|
|3343|`game/GameEngine/Source/GameLogic/Object/SpecialPower/PlayerHealSpecialPowerDoSpecialPower.cpp`|UnsignedInt|1|3|
|3344|`game/GameEngine/Source/Common/MultiplayerColorMapOperator.cpp`|Int|1|188|
|3345|`game/GameEngine/Source/GameLogic/AI/PathfindZoneManager_markZonesDirty.cpp`|Bool|1|6|
|3346|`game/GameEngine/Source/Common/BitFlags192TestForAny.cpp`|Bool|1|109|
|3347|`game/GameEngine/Source/GameLogic/Object/Behavior/DeathStatusFlags_parse.cpp`|Bool|1|178|
|3348|`game/GameEngine/Source/GameLogic/System/GameLogic_isInMultiplayerGame.cpp`|Bool|1|63|
|3349|`game/GameEngine/Source/Common/BitFlags192TestForAll.cpp`|Bool|1|144|
|3350|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006BE410TerrainQueryForwarder.cpp`|Bool|1|11|
|3351|`game/GameEngine/Source/Common/BfmeConv636.cpp`|Real|1|53|
|3352|`game/GameEngine/Source/Common/BitFlags192TestSetAndClear.cpp`|Bool|1|230|
|3353|`game/GameEngine/Source/GameLogic/Object/Object_bfmeBoundaryDistanceSquared2D.cpp`|Real|1|21|
|3354|`game/GameEngine/Source/Common/Rva00256AB0ListNonEmpty.cpp`|Int|1|32|
|3355|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer_stampShroudVisible.cpp`|Int|1|59|
|3356|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LANPreferencesCtorThunk.cpp`|Bool|1|92|
|3357|`game/GameEngine/Source/GameClient/EvaCheck_resetFromInfo.cpp`|Real|1|54|
|3358|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/IMECandidateWindowInput.cpp`|UnsignedInt|1|6|
|3359|`game/GameEngine/Source/GameLogic/Pathfinder/ZoneBlockSetWaypoint.cpp`|Bool|1|87|
|3360|`game/GameEngine/Source/Common/System/DataChunkInputReset.cpp`|Int|1|52|
|3361|`game/GameEngine/Source/GameLogic/System/assignRandomStillImage.cpp`|Int|1|108|
|3362|`game/GameEngine/Source/Common/Rva00473900AllocProxyCtor.cpp`|UnsignedInt, Bool|1|35|
|3363|`game/GameEngine/Source/GameNetwork/BFMEConnectionManager_voteForPlayerDisconnect.cpp`|Int|1|26|
|3364|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Rva00752F40Handle.cpp`|Int|1|93|
|3365|`game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006C6F60_TerrainBit.cpp`|Bool|1|117|
|3366|`game/GameEngine/Source/GameLogic/Rva002D7890.cpp`|Real|1|59|
|3367|`game/GameEngine/Source/GameNetwork/readAsciiFieldFromBuffer.cpp`|UnsignedByte|1|111|
|3368|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BC4E0StateAction.cpp`|Int|1|75|
|3369|`game/GameEngine/Source/GameLogic/AI/PathfindCellInfoPoolReset.cpp`|Int|1|93|
|3370|`game/GameEngine/Source/Common/System/Rva003C2E60XferMissionObjectiveStates.cpp`|Bool|1|91|
|3371|`game/GameEngine/Source/Common/Bfme/Q1Forwardee0000871A_handle.cpp`|Int|1|37|
|3372|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/BfmeConv1679.cpp`|Real|1|118|
|3373|`game/GameEngine/Source/Common/Bfme/Glo012F7048Type_test.cpp`|Bool|1|12|
|3374|`game/GameEngine/Source/GameLogic/AI/PathfindCellLayersCompatible.cpp`|Bool|1|80|
|3375|`game/GameEngine/Source/GameLogic/Object/AnimSetVectorInsertThunk0000DB2F.cpp`|Int|1|5|
|3376|`game/GameEngine/Source/GameLogic/Object/Weapon_getAttackDistance.cpp`|Real|1|95|
|3377|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DWaypointBufferDestructor.cpp`|Int|1|117|
|3378|`game/GameEngine/Source/GameLogic/AI/PathfindZoneWaypoint.cpp`|Bool|1|97|
|3379|`game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006CB500_BitPlaneTest.cpp`|Bool|1|83|
|3380|`game/GameEngine/Source/GameNetwork/Connection_clearCommandsExceptFrom.cpp`|Int|1|77|
|3381|`game/Libraries/Source/WWVegas/WWLib/RvaHashIndex00928620.cpp`|UnsignedInt|1|76|
|3382|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayStringDrawDefault.cpp`|Int|1|22|
|3383|`game/GameEngine/Source/Common/INI/Rva002D4AA0ParsePercentVectorEntry.cpp`|Real|1|74|
|3384|`game/GameEngine/Source/GameLogic/Object/Update/Gen003A0410Constructor.cpp`|UnsignedInt|1|115|
|3385|`game/GameEngine/Source/Common/S4Elem007746E0Constructor.cpp`|Int|1|117|
|3386|`game/GameEngine/Source/GameLogic/AI/PathfindCell_isObstaclePresent.cpp`|Bool|1|46|
|3387|`game/GameEngine/Source/GameLogic/Object/Update/Rva002B7F40_clearModelCondition.cpp`|UnsignedInt|1|48|
|3388|`game/GameEngine/Source/GameLogic/LivingWorld/BfmeLivingWorldManagerIsCampaignVictorious.cpp`|Bool|1|9|
|3389|`game/GameEngine/Source/Common/BfmeConv630.cpp`|Bool|1|50|
|3390|`game/GameEngine/Source/Common/Rva00092D70ToggleCloudMapOption.cpp`|Bool|1|154|
|3391|`game/GameEngine/Source/Common/Rva003E62B0PathQueryCtor.cpp`|Int|1|64|
|3392|`game/GameEngine/Source/Common/Rva0015A560MaxOverride.cpp`|Int|1|63|
|3393|`game/GameEngine/Source/Common/BfmeConv1717.cpp`|Real|1|64|
|3394|`game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_00730e20_StructForward.cpp`|Real|1|48|
|3395|`game/GameEngine/Source/Common/Rva005C6370ListInsert.cpp`|Real|1|75|
|3396|`game/GameEngine/Source/GameLogic/System/CrateCreationEntryListInsert.cpp`|Real|1|75|
|3397|`game/GameEngine/Source/Common/Thing/ThingTemplateRemoveModuleInfo.cpp`|Bool|1|101|
|3398|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdFollowWaypointPathStateOnEnter.cpp`|UnsignedInt|1|78|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
