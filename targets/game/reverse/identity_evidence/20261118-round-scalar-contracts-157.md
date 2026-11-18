# Scalar alias contracts: cohort 157

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
|3464|`game/GameEngine/Source/GameLogic/LivingWorld/ParseForceBattle.cpp`|Int|1|157|
|3465|`game/GameEngine/Source/GameLogic/Object/Update/WeaponModeSpecialPowerUpdateModuleDataBaseCtorThunk.cpp`|Int|1|156|
|3466|`game/GameEngine/Source/Common/BfmeConv1570.cpp`|Real|1|44|
|3467|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_d_002ef310.cpp`|Byte|1|44|
|3468|`game/GameEngine/Source/GameLogic/LivingWorld/ParseMergeArmyBlock.cpp`|Int|1|157|
|3469|`game/GameEngine/Source/Common/Thing/Rva00140070CollectModuleAssets.cpp`|Int|1|235|
|3470|`game/GameEngine/Source/Common/Rva00880C30BoxPair.cpp`|Real|1|221|
|3471|`game/GameEngine/Source/GameLogic/LivingWorld/ParseArmyMoveToBlock.cpp`|Int|1|157|
|3472|`game/GameEngine/Source/Common/System/GeometryInfoCalcPitches.cpp`|Real|1|159|
|3473|`game/GameEngine/Source/GameLogic/AI/PathfindLayerDestructor.cpp`|Int|1|64|
|3474|`game/GameEngine/Source/GameLogic/Object/Update/BfmeAttributeNamedEntryFind.cpp`|Int, UnsignedShort|1|153|
|3475|`game/GameEngineDevice/Source/VideoDevice/Bink/Rva00434A90.cpp`|Bool|1|194|
|3476|`game/GameEngine/Source/GameLogic/AI/PathfindLayerResetFull.cpp`|Int|1|64|
|3477|`game/GameEngine/Source/GameLogic/LivingWorld/ParseAnimObjectUpdate.cpp`|Int|1|158|
|3478|`game/GameEngine/Source/GameLogic/LivingWorld/ParseEyeTowerPointData.cpp`|Int|1|157|
|3479|`game/GameEngine/Source/GameLogic/Object/SpecialPower/ScavengerSpecialPowerDoSpecialPower.cpp`|UnsignedInt|1|44|
|3480|`game/GameEngine/Source/GameLogic/AI/PathfinderAdjustLOSPoints.cpp`|Int|1|100|
|3481|`game/GameEngine/Source/Common/Rva003C8340NotifyHilight.cpp`|Bool|1|262|
|3482|`game/GameEngine/Source/GameLogic/LivingWorld/Rva003B88F0ParseAnimObjectUpdate.cpp`|Int|1|154|
|3483|`game/GameEngine/Source/GameClient/GUI/ControlBar/WOLQuickMatchMenuShutdownComplete.cpp`|Bool|1|90|
|3484|`game/GameEngine/Source/GameLogic/LivingWorld/ParseEnableRegion.cpp`|Int|1|162|
|3485|`game/GameEngine/Source/GameLogic/Object/Object_rva001C1EA0EnragedState.cpp`|Bool|1|155|
|3486|`game/GameEngine/Source/Common/INI/Rva002DC6D0ParseFilterPercentEntry.cpp`|Real|1|174|
|3487|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006F6F40FloorElement.cpp`|Real|1|376|
|3488|`game/GameEngine/Source/GameLogic/LivingWorld/Rva003BAA70ParseArmyMoveToBlock.cpp`|Int|1|157|
|3489|`game/GameEngine/Source/GameLogic/Object/Update/UpdateModule_getWakeFrame.cpp`|UnsignedInt|1|24|
|3490|`game/GameEngine/Source/GameLogic/Object/Weapon_getPercentReadyToFire.cpp`|UnsignedInt|1|152|
|3491|`game/GameEngine/Source/Common/Thing/ThingTemplate_bfmeGetAudioEventInfo57.cpp`|Int|1|56|
|3492|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0075C690CountSharedEdges.cpp`|UnsignedShort|1|125|
|3493|`game/GameEngine/Source/GameLogic/Object/Object_maskObject.cpp`|Bool|1|79|
|3494|`game/GameEngine/Source/Common/System/GeometryShapeCopyConstructor.cpp`|Bool|1|73|
|3495|`game/GameEngine/Source/Common/Bfme/S4Made0090F650Constructor.cpp`|Real|1|48|
|3496|`game/GameEngine/Source/Common/Rva006DF110Coordinate.cpp`|Real|1|167|
|3497|`game/GameEngine/Source/GameLogic/AI/Rva003D5B00CellPredicate.cpp`|Int|1|75|
|3498|`game/GameEngine/Source/GameLogic/AI/AISkirmishPlayerGetMyEnemyPlayerIndexThunk.cpp`|Int|1|63|
|3499|`game/Libraries/Source/WWVegas/WWLib/RvaHashResize00927DE0.cpp`|UnsignedInt|1|289|
|3500|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/OptionPreferences_ctor.cpp`|Int, UnsignedInt, Bool|1|92|
|3501|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_getClosestSlave.cpp`|Bool, Real|1|182|
|3502|`game/GameEngine/Source/GameClient/GUI/ControlBar/CommandSetAssign.cpp`|Int|1|64|
|3503|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainParseRanksThatStopAdvance.cpp`|Int|1|99|
|3504|`game/GameEngine/Source/GameLogic/LivingWorld/ParseMoveCameraBlock.cpp`|Int|1|161|
|3505|`game/GameEngine/Source/Common/Thing/ModuleInfoClearAi.cpp`|Bool|1|97|
|3506|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineGetCurrentPlayer.cpp`|Bool|1|110|
|3507|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_shutdownComplete.cpp`|Bool|1|93|
|3508|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/SplineEffectParseGeometryName.cpp`|Int|1|135|
|3509|`game/Libraries/Source/WWVegas/WW3D2/Animatable3DObjClass_Single_Anim_Progress.cpp`|Real|1|51|
|3510|`game/GameEngine/Source/GameClient/Eva_setShouldPlay.cpp`|Bool|1|146|
|3511|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterface_bfmeClearModelConditions.cpp`|Int|1|110|
|3512|`game/GameEngine/Source/Common/S3CrateChanceRoll.cpp`|Real|1|57|
|3513|`game/GameEngine/Source/GameLogic/Object/Upgrade/RadarUpgradeOnCapture.cpp`|Bool|1|97|
|3514|`game/GameEngine/Source/Common/U2FeslBoundedStringCopy.cpp`|UnsignedInt|1|98|
|3515|`game/GameEngine/Source/GameLogic/AI/PathAdvanceCachedPoint.cpp`|Real|1|102|
|3516|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual_getTerrainTile.cpp`|Real|1|126|
|3517|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateMusicHasCompleted_Bfme.cpp`|Bool|1|114|
|3518|`game/GameEngine/Source/Common/Rva0049C2E0Method.cpp`|Int, UnsignedInt|1|127|
|3519|`game/GameEngine/Source/GameLogic/Object/SpecialPower/DevastateSpecialPowerDoSpecialPowerAtObject.cpp`|UnsignedInt|1|16|
|3520|`game/GameEngine/Source/Common/RTS/Player_getScienceAvailabilityTypeFromString.cpp`|Int|1|134|
|3521|`game/GameEngine/Source/GameLogic/LivingWorld/ParseWorldTextBlock.cpp`|Int|1|174|
|3522|`game/GameEngine/Source/GameLogic/AI/Rva00178AE0State_onEnter.cpp`|Bool|1|66|
|3523|`game/GameEngine/Source/GameLogic/Object/Object_updateSupplyStatus.cpp`|UnsignedInt|1|152|
|3524|`game/GameEngine/Source/Common/Rva0006AB90FunctionCurveFinish.cpp`|Int|1|159|
|3525|`game/GameEngine/Source/GameLogic/Object/Update/StructureCollapseOnDie.cpp`|Bool|1|82|
|3526|`game/GameEngine/Source/Common/Bfme/Rva0005C110SurfaceDestructor.cpp`|Int|1|134|
|3527|`game/GameEngine/Source/GameLogic/Pathfinder/pathfinder_layer.cpp`|Bool, Int|1|110|
|3528|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyGroupRoomPairDestructor.cpp`|Int|1|77|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
