# Scalar alias contracts: cohort 156

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
|3399|`game/GameEngine/Source/Common/BfmeConv1946.cpp`|Bool|1|161|
|3400|`game/GameEngine/Source/Common/RTS/Money_xfer.cpp`|UnsignedInt|1|48|
|3401|`game/GameEngine/Source/GameLogic/ScriptEngine/CurDrawableGetCurrentTargetHeight.cpp`|Real|1|84|
|3402|`game/GameEngine/Source/GameLogic/Object/ObjectStatusOfContained.cpp`|Bool|1|78|
|3403|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BC470StateAction.cpp`|Int|1|83|
|3404|`game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006CC000_TerrainBit.cpp`|Bool|1|117|
|3405|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapRenderObjClass_releaseRefs_rva006D6FD0.cpp`|Int|1|134|
|3406|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapGetClipHeight.cpp`|UnsignedShort|1|84|
|3407|`game/GameEngine/Source/GameLogic/AI/AIGuard_getStdGuardRange.cpp`|Real|1|59|
|3408|`game/GameEngine/Source/GameLogic/Object/Update/Rva0037AD60ParseEmotionAIType.cpp`|Int|1|72|
|3409|`game/GameEngine/Source/Common/BitFlags304ModelConditionCtor3.cpp`|Int|1|117|
|3410|`game/GameEngine/Source/Common/Rva00063A40_parse.cpp`|Int|1|150|
|3411|`game/GameEngine/Source/GameClient/GUI/Rva0048B0E0TransitionGuard.cpp`|Bool|1|94|
|3412|`game/GameEngine/Source/GameClient/GUI/WindowLayoutInfoConstructor.cpp`|UnsignedInt|1|196|
|3413|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0073C700Configure.cpp`|Real|1|148|
|3414|`game/GameEngine/Source/Common/BfmeConv1572.cpp`|Real|1|44|
|3415|`game/GameEngine/Source/Common/INI/Rva000BD260ParseIndexListVector.cpp`|Int|1|107|
|3416|`game/GameEngine/Source/GameLogic/System/GameLogic_friend_createObject.cpp`|UnsignedInt|1|115|
|3417|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorUpgradeImplementation.cpp`|Bool|1|8|
|3418|`game/GameEngine/Source/Common/S3MaskedTableTest.cpp`|UnsignedShort|1|40|
|3419|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DFloorBuffer_releaseResources.cpp`|Int|1|139|
|3420|`game/GameEngine/Source/Common/BitFlags304ModelConditionCtor4.cpp`|Int|1|141|
|3421|`game/GameEngine/Source/Common/Rva0015A5B0Sum.cpp`|Int|1|57|
|3422|`game/GameEngine/Source/GameLogic/Object/WeaponEffects/Made001E5AF0Constructor.cpp`|Int|1|97|
|3423|`game/GameEngine/Source/Common/Rva001DD2E0GeometryCheck.cpp`|Real|1|55|
|3424|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIUpdateInterfaceGetCurrentStateID.cpp`|UnsignedInt|1|20|
|3425|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva00144500BitFlagsParseFromINI.cpp`|Bool|1|73|
|3426|`game/GameEngine/Source/Common/S3PlaneFrontTest.cpp`|Real|1|50|
|3427|`game/GameEngine/Source/Common/INI/INIGetNextToken.cpp`|Int|1|86|
|3428|`game/GameEngine/Source/Common/SmallGaps/Rva004F1210Deallocate.cpp`|UnsignedInt|1|50|
|3429|`game/GameEngine/Source/GameLogic/Pathfinder/PathfindLayerRememberEndpoint.cpp`|Int|1|78|
|3430|`game/GameEngine/Source/GameLogic/Object/Contain/S4ModuleData00116D80Constructor.cpp`|Real|1|28|
|3431|`game/GameEngine/Source/GameNetwork/GameInfo_assign.cpp`|Int|1|159|
|3432|`game/GameEngine/Source/Common/Thing/ModuleInfoClearCopiedFromDefaultEntries.cpp`|Bool|1|101|
|3433|`game/GameEngine/Source/GameLogic/Object/Update/UpdateModule_bfmeFinishWithDeposit.cpp`|UnsignedInt|1|88|
|3434|`game/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelperFramesUntilNext.cpp`|UnsignedInt|1|91|
|3435|`game/GameEngine/Source/GameLogic/AI/PathfinderWorldLinePredicate.cpp`|Bool|1|76|
|3436|`game/Libraries/Source/WWVegas/WWLib/RvaHashFind00927800.cpp`|UnsignedInt|1|70|
|3437|`game/GameEngine/Source/GameLogic/AI/PathfindApplyBlockZoneRaw.cpp`|Int|1|55|
|3438|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderGroundCellPredicate.cpp`|Bool|1|96|
|3439|`game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006C6E20_TerrainBitPlaneQuery.cpp`|Bool|1|117|
|3440|`game/GameEngine/Source/GameLogic/Object/Update/OCLUpdate_getRemainingFrames.cpp`|UnsignedInt|1|13|
|3441|`game/GameEngine/Source/GameLogic/System/GameLogicAddTOCEntry.cpp`|UnsignedShort|1|168|
|3442|`game/GameEngine/Source/Common/Rva00473930AllocProxyCtor.cpp`|UnsignedInt, Bool|1|35|
|3443|`game/GameEngine/Source/Common/Rva00095230NodeDeallocate.cpp`|UnsignedInt|1|47|
|3444|`game/GameEngine/Source/Common/Rva0040E990KeyboardFlagged.cpp`|Bool|1|63|
|3445|`game/GameEngine/Source/GameClient/GUI/Shell/Rva0057F0B0ShellHide.cpp`|Bool|1|57|
|3446|`game/GameEngine/Source/GameLogic/Object/Update/BroadcastStealthUpdateModuleData_buildFieldParse.cpp`|UnsignedInt|1|35|
|3447|`game/GameEngine/Source/GameNetwork/Rva0061EE90CountNonClosed.cpp`|Int|1|220|
|3448|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_canAnySlavesAttack.cpp`|Bool|1|124|
|3449|`game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006C6EC0_TerrainBitPlaneQuery.cpp`|Bool|1|117|
|3450|`game/GameEngine/Source/GameClient/CursorParticleSystemFXNuggetConstructor.cpp`|Real|1|171|
|3451|`game/GameEngine/Source/GameLogic/AI/PathNodeGetNextOptimized.cpp`|Real|1|139|
|3452|`game/GameEngine/Source/GameLogic/Object/Upgrade/UpgradeMux_resetUpgrade.cpp`|Bool|1|122|
|3453|`game/GameEngine/Source/Common/Rva00880D90SphereOverlap.cpp`|Real|1|61|
|3454|`game/GameEngine/Source/Common/Rva00338F90DebugPause.cpp`|UnsignedByte|1|66|
|3455|`game/GameEngine/Source/GameLogic/Object/BfmeGeometryCollisionSource.cpp`|Real|1|68|
|3456|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/ControlBar_buildTooltipLayout.cpp`|Int|1|26|
|3457|`game/GameEngine/Source/Common/Rva0060D480CampaignGate.cpp`|Bool|1|46|
|3458|`game/GameEngine/Source/GameLogic/AI/PathfinderGetCellTwin.cpp`|Bool|1|65|
|3459|`game/GameEngine/Source/GameLogic/AI/Squad_isOnSquad.cpp`|Bool|1|38|
|3460|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00259160FilteredModelCondition.cpp`|Int|1|86|
|3461|`game/GameEngine/Source/GameLogic/System/GameLogic_isInLivingWorldCampaign.cpp`|Int|1|91|
|3462|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowGeometryCtorThunk.cpp`|Int|1|131|
|3463|`game/GameEngine/Source/Common/BfmeConv2113.cpp`|Int|1|52|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
