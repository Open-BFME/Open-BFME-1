# Scalar alias contracts: cohort 158

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
|3529|`game/GameEngine/Source/GameLogic/AI/Rva0020CC70RawCtor.cpp`|Int|1|76|
|3530|`game/GameEngine/Source/GameLogic/Object/Upgrade/RadarUpgradeImplementationBodyThunk.cpp`|Bool|1|67|
|3531|`game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateConstructor.cpp`|UnsignedInt|1|51|
|3532|`game/GameEngine/Source/GameLogic/Object/SpecialPower/PlayerHealSpecialPowerDoSpecialPowerAtObject.cpp`|UnsignedInt|1|16|
|3533|`game/GameEngine/Source/GameLogic/Object/ObjectRadiusShortenedDelta001E3E40.cpp`|Real|1|176|
|3534|`game/GameEngine/Source/GameNetwork/DisconnectManagerCountVotes.cpp`|Bool|1|106|
|3535|`game/GameEngine/Source/GameLogic/Rva002229E0NearestContained.cpp`|Real|1|112|
|3536|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawModuleData_buildFieldParse.cpp`|UnsignedInt|1|17|
|3537|`game/GameEngine/Source/Common/Rva00880D10CircleBoxTest.cpp`|Real|1|127|
|3538|`game/GameEngine/Source/Common/RTS/MissionStatsBFMEXfer.cpp`|UnsignedByte|1|117|
|3539|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdateOnObjectCreated.cpp`|UnsignedInt|1|51|
|3540|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorOnDelete.cpp`|Bool|1|141|
|3541|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_clearAbilityBits.cpp`|Bool|1|132|
|3542|`game/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgradeUpgradeImplementation.cpp`|UnsignedInt|1|180|
|3543|`game/GameEngine/Source/Common/Bfme5ListReset.cpp`|Bool|1|68|
|3544|`game/GameEngine/Source/Common/Gen00371090Remove.cpp`|Real|1|107|
|3545|`game/GameEngine/Source/Common/RelationshipHashInsertThunk000013E8.cpp`|Int|1|5|
|3546|`game/GameEngine/Source/GameLogic/LivingWorld/Rva003B7F90ParseArmyMoveToBlock.cpp`|Int|1|202|
|3547|`game/GameEngine/Source/GameNetwork/GameSpy/Rva000E92B0SetWideString.cpp`|Int|1|109|
|3548|`game/GameEngine/Source/GameLogic/LivingWorld/Rva00365B40.cpp`|Int|1|178|
|3549|`game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorModuleDataDestructorThunk.cpp`|UnsignedInt|1|147|
|3550|`game/GameEngine/Source/Common/Rva005A41F0Reset.cpp`|UnsignedByte|1|210|
|3551|`game/GameEngine/Source/Common/System/GameMessage_allocArg.cpp`|Int, UnsignedByte, Bool|1|83|
|3552|`game/GameEngine/Source/Common/Rva00061300NetworkCrc.cpp`|UnsignedInt|1|97|
|3553|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FD2E0CursorClamp.cpp`|Real|1|174|
|3554|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadRemoveServerFromMap.cpp`|Int|1|519|
|3555|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUI_ctor.cpp`|Int|1|61|
|3556|`game/Libraries/Source/shroudmanager/BfmeConv1574.cpp`|Real|1|131|
|3557|`game/GameEngine/Source/Common/Bfme/Gen_00417cb0_alt.cpp`|UnsignedInt|1|55|
|3558|`game/GameEngine/Source/Common/Thing/DrawableModuleConstructor.cpp`|Int|1|131|
|3559|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTruckDrawModuleData_buildFieldParse.cpp`|UnsignedInt|1|30|
|3560|`game/GameEngine/Source/Common/System/GeometryShapeCopyBackward.cpp`|Bool|1|123|
|3561|`game/GameEngine/Source/GameLogic/AI/AIPickUpCrateState_computePath.cpp`|Bool|1|101|
|3562|`game/GameEngine/Source/GameLogic/Object/Update/Rva0037AD00ParseEmotionType.cpp`|Int|1|72|
|3563|`game/GameEngine/Source/Common/SkirmishBattleHonorsFactionTotals.cpp`|Int|1|247|
|3564|`game/GameEngine/Source/GameNetwork/ConnectionManager_processGameSpyStatsAuthKey.cpp`|UnsignedInt|1|156|
|3565|`game/GameEngine/Source/Common/INI/Rva00094010Register.cpp`|Int|1|172|
|3566|`game/GameEngine/Source/Common/Thing/Thing_bfmeHasWeaponTemplateSet.cpp`|Bool|1|79|
|3567|`game/GameEngine/Source/GameLogic/LivingWorld/BfmeLwcmFindIndex.cpp`|Int, UnsignedShort|1|203|
|3568|`game/GameEngine/Source/GameLogic/LivingWorld/SplineCameraParseINIBlock.cpp`|Int|1|165|
|3569|`game/GameEngine/Source/Common/Rva005C36C0Forward.cpp`|Real|1|91|
|3570|`game/GameEngine/Source/Common/BfmeThreeHundredSeventeen.cpp`|UnsignedInt|1|45|
|3571|`game/GameEngine/Source/GameLogic/LivingWorld/Rva0020C9C0ForceAttack.cpp`|Int, Bool|1|158|
|3572|`game/GameEngine/Source/Common/BfmeConv1887.cpp`|Bool|1|86|
|3573|`game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorModuleDataCtorThunk.cpp`|UnsignedInt|1|124|
|3574|`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManagerGetHeight.cpp`|Real|1|237|
|3575|`game/GameEngine/Source/GameLogic/AI/Rva0024B7E0.cpp`|Bool|1|103|
|3576|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGainLevel.cpp`|Bool|1|69|
|3577|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSmudgeManagerReleaseResources.cpp`|Int|1|90|
|3578|`game/GameEngine/Source/GameLogic/AI/Rva0024BB60.cpp`|Int, Bool|1|90|
|3579|`game/GameEngine/Source/GameLogic/Object/Update/StealthUpdate_setWakeupIfInRange.cpp`|Real|1|137|
|3580|`game/GameEngine/Source/Common/RTS/PlayerProductionTime.cpp`|Real|1|35|
|3581|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadQRCountCallback.cpp`|Bool|1|44|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
