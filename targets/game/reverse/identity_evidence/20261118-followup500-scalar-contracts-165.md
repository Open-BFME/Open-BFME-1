# Scalar alias contracts: cohort 165

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
|3971|`game/GameEngine/Source/GameLogic/AI/TeamInQueue_disbandMethodThunk.cpp`|Bool|1|180|
|3972|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayRva006E9940.cpp`|Int|1|183|
|3973|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DGameWindowDrawText.cpp`|Bool|1|237|
|3974|`game/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior_update_BFME.cpp`|UnsignedInt|1|331|
|3975|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorOnDie.cpp`|Bool|1|298|
|3976|`game/GameEngine/Source/GameLogic/Map/BridgeGetBridgeHeight.cpp`|Real|1|664|
|3977|`game/GameEngine/Source/GameClient/MessageStream/WindowXlat.cpp`|Int|1|176|
|3978|`game/GameEngine/Source/GameLogic/Object/Rva001C6E00.cpp`|Bool, UnsignedInt|1|214|
|3979|`game/GameEngine/Source/GameClient/INIPredefinedEvaEvent.cpp`|Int|1|342|
|3980|`game/GameEngine/Source/GameLogic/AI/PathfinderStepE0370.cpp`|Int|1|458|
|3981|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doCameraMotionBlurJump.cpp`|Bool, Real|1|165|
|3982|`game/Libraries/Source/WWVegas/WW3D2/promoted__Reset_HAnimComboClass_QAEXXZ_00974DC0.cpp`|Int|1|95|
|3983|`game/Libraries/Source/WWVegas/WW3D2/WW3D_Begin_Render_Bfme.cpp`|UnsignedInt|1|318|
|3984|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterTracksRenderSystemReAcquireResources.cpp`|UnsignedShort|1|335|
|3985|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00249250HordeGarrisonHook.cpp`|UnsignedInt|1|142|
|3986|`game/GameEngine/Source/GameLogic/Object/Upgrade/ArmorUpgradeUpgradeImplementation.cpp`|UnsignedInt|1|199|
|3987|`game/GameEngine/Source/GameLogic/Object/SpecialPower/PlayerUpgradeSpecialPowerDoSpecialPower.cpp`|UnsignedInt|1|209|
|3988|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLQuickMatchMenuShutdown_Clean.cpp`|Bool|1|147|
|3989|`game/GameEngine/Source/GameLogic/Object/Helper/ObjectSMCHelperUpdate.cpp`|UnsignedInt|1|138|
|3990|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva0032C990.cpp`|Bool|1|291|
|3991|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptGuiFX.cpp`|UnsignedInt|1|382|
|3992|`game/GameEngine/Source/GameLogic/AI/Rva0017BF00State_onExit.cpp`|Bool|1|89|
|3993|`game/GameEngine/Source/Common/OSDisplayWarningBox_Thunk.cpp`|UnsignedInt|1|509|
|3994|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContain.cpp`|Bool|1|219|
|3995|`game/GameEngine/Source/GameLogic/Object/Contain/HordeGarrisonContainCtor.cpp`|UnsignedInt|1|175|
|3996|`game/GameEngine/Source/GameLogic/Object/Upgrade/CostModifierUpgradeOnCapture.cpp`|Bool|1|309|
|3997|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainGetObjectGarrisonPointIndex.cpp`|Int|1|481|
|3998|`game/GameEngine/Source/Common/Rva0019FD00Fill.cpp`|Bool|1|425|
|3999|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorCtorThunk.cpp`|UnsignedInt|1|376|
|4000|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjInitBumpMap.cpp`|Int|1|747|
|4001|`game/GameEngine/Source/GameLogic/Object/WeaponDamageFieldNuggetRva002DAEC0.cpp`|UnsignedInt|1|392|
|4002|`game/GameEngine/Source/GameLogic/AI/PathfinderIterateCellsAlongLineRva003E3650.cpp`|Int|1|538|
|4003|`game/GameEngine/Source/GameClient/GUI/SoloMordorFade_LoadGame.cpp`|Bool|1|126|
|4004|`game/GameEngine/Source/Common/Rva0049BA80.cpp`|Int|1|292|
|4005|`game/Libraries/Source/WWVegas/WWLib/stlport_hashtable_int_int_insert.cpp`|Int|1|111|
|4006|`game/Libraries/Source/WWVegas/WWLib/stlport_hashtable_int_ptr_insert.cpp`|Int|1|111|
|4007|`game/GameEngine/Source/GameLogic/Object/Update/Rva0039FF30FilterSetMasks.cpp`|UnsignedInt|1|549|
|4008|`game/GameEngine/Source/GameLogic/Object/ObjectFriendBindToDrawable.cpp`|UnsignedInt|1|411|
|4009|`game/GameEngine/Source/GameClient/STLHashMapP36InsertUniqueNoresize.cpp`|Int|1|146|
|4010|`game/GameEngine/Source/GameLogic/Object/Update/BloodthirstyUpdateSacrificeHorde.cpp`|Bool|1|346|
|4011|`game/GameEngine/Source/Common/Rva001FCA90Selector.cpp`|Bool|1|151|
|4012|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_TeamTeleportToWaypoint_Rva002F7280.cpp`|Bool|1|152|
|4013|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doPlayerForceEmotion.cpp`|Bool|1|260|
|4014|`game/GameEngine/Source/GameLogic/Object/ObjectDoCommandButtonAtObject.cpp`|Bool|1|524|
|4015|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_rva001F1CE0.cpp`|Bool|1|296|
|4016|`game/GameEngine/Source/GameLogic/Object/Behavior/GateOpenAndCloseBehaviorCtor.cpp`|UnsignedInt|1|197|
|4017|`game/GameEngine/Source/GameClient/GUI/INIFontDefaultSettings.cpp`|Real|1|480|
|4018|`game/GameEngine/Source/Common/RTS/Player_resetSciences.cpp`|Int|1|250|
|4019|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva00351040ScriptAssetList.cpp`|Int|1|386|
|4020|`game/GameEngine/Source/Common/Thing/ThingFactory_newObject.cpp`|UnsignedInt|1|278|
|4021|`game/GameEngine/Source/GameLogic/Object/ObjectOnDestroy.cpp`|Bool|1|194|
|4022|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowGeometryManager_Load_Geom_Thunk.cpp`|Bool|1|342|
|4023|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0023A380HordeContain.cpp`|UnsignedInt|1|369|
|4024|`game/GameEngine/Source/GameClient/GUI/AptMapPreviewConstructor.cpp`|UnsignedShort|1|257|
|4025|`game/GameEngine/Source/Common/Rva00388820FindWaypointByName.cpp`|Bool, Int|1|245|
|4026|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenInGameChatFriendPanel.cpp`|Bool, Int|1|219|
|4027|`game/GameEngine/Source/GameLogic/Object/Update/OCLUpdateUpdate.cpp`|UnsignedInt|1|239|
|4028|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawSetPauseAnimation.cpp`|Bool|1|119|
|4029|`game/GameEngine/Source/GameLogic/Object/Update/AutoPickUpUpdate.cpp`|Real|1|585|
|4030|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowUpdateOptimalExtrusionPadding.cpp`|Real|1|760|
|4031|`game/GameEngine/Source/GameNetwork/ConnectionManagerProcessDisconnectChat.cpp`|Int|1|255|
|4032|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGuard.cpp`|Bool, Int, Real|1|160|
|4033|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BC670StateAction.cpp`|Int|1|83|
|4034|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdAttackState_update.cpp`|Int|1|199|
|4035|`game/GameEngine/Source/Common/RTS/Rva000EDB30TeamIsIdle.cpp`|Bool|1|97|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
