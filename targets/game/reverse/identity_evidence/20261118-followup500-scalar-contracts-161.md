# Scalar alias contracts: cohort 161

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
|3712|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva00609940CursorTarget.cpp`|Real|1|135|
|3713|`game/GameEngine/Source/GameLogic/AI/AIGuardRetaliateState_xfer.cpp`|UnsignedByte|1|204|
|3714|`game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_update.cpp`|Bool|1|96|
|3715|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferDoLighting.cpp`|UnsignedInt|1|470|
|3716|`game/GameEngine/Source/GameLogic/Pathfinder/pathfinder_zonemanager.cpp`|Bool|1|293|
|3717|`game/Libraries/Source/WWVegas/WW3D2/SetMeshModelFlag.cpp`|Int|1|160|
|3718|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SurrenderQuitMenu.cpp`|Bool|1|116|
|3719|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_handle.cpp`|Bool|1|135|
|3720|`game/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetState_update_Bfme.cpp`|Bool|1|161|
|3721|`game/GameEngine/Source/GameLogic/Object/Object_rva001E2560.cpp`|Real|1|170|
|3722|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackgroundIsEdgeAligned.cpp`|Bool|1|305|
|3723|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate_chooseGoodLocomotorFromCurrentSet.cpp`|Int, UnsignedInt, Bool|1|137|
|3724|`game/GameEngine/Source/GameLogic/LivingWorld/ParseFlashRegionsEvent.cpp`|Int|1|145|
|3725|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior_getCanAnySlavesAttackSpecificTarget.cpp`|Bool|1|197|
|3726|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_d_002f4ab0.cpp`|Bool|1|141|
|3727|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doPlayerRepairStructure.cpp`|Bool|1|94|
|3728|`game/GameEngine/Source/GameLogic/AI/AITNGuard_findBestTunnel_Bfme.cpp`|Real|1|134|
|3729|`game/GameEngine/Source/GameLogic/AI/Rva0016D9C0State_xfer.cpp`|UnsignedByte|1|204|
|3730|`game/GameEngine/Source/GameLogic/LivingWorld/Rva003B82D0ParseArmyMoveToBlock.cpp`|Int|1|183|
|3731|`game/GameEngine/Source/Common/System/SaveGame/GameState_findNextSaveFilename.cpp`|Int|1|281|
|3732|`game/GameEngine/Source/GameClient/GUI/WindowLayoutInfoAssignmentThunk.cpp`|UnsignedInt|1|115|
|3733|`game/GameEngine/Source/Common/Rva0075C9F0Dispatch.cpp`|Real|1|101|
|3734|`game/GameEngine/Source/GameLogic/AI/AIAttackState_loadPostProcess.cpp`|Bool|1|154|
|3735|`game/GameEngine/Source/GameLogic/System/Rva0038AD90ObjectIndicators.cpp`|Bool|1|92|
|3736|`game/GameEngine/Source/GameLogic/Object/SpecialPower/ProductionSpeedBonusDoSpecialPower.cpp`|UnsignedInt|1|144|
|3737|`game/GameEngine/Source/Common/Rva0037F190ExperienceLevelSystem.cpp`|Bool|1|115|
|3738|`game/GameEngine/Source/GameLogic/Object/Upgrade/Rva002D9610.cpp`|UnsignedInt|1|157|
|3739|`game/GameEngine/Source/GameLogic/AI/Rva001703C0AIStateMachine_update.cpp`|UnsignedInt|1|118|
|3740|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002BC5D0StateAction.cpp`|Int|1|114|
|3741|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0023A100HordeMemberWalk.cpp`|Bool, Int, UnsignedInt|1|167|
|3742|`game/GameEngine/Source/GameClient/Drawable_setIndicatorColor.cpp`|UnsignedInt|1|143|
|3743|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_putObjectAtBestGarrisonPoint.cpp`|Int, Bool|1|123|
|3744|`game/GameEngine/Source/GameLogic/AI/AIFindClosestRepulsor.cpp`|Bool|1|154|
|3745|`game/GameEngine/Source/Common/Rva00778000ParseTimeOfDay.cpp`|Int|1|348|
|3746|`game/GameEngine/Source/GameLogic/Object/Contain/Rva0023A270HordeContain.cpp`|Bool, UnsignedInt|1|210|
|3747|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterTracksRenderSystemInit.cpp`|UnsignedInt|1|157|
|3748|`game/GameEngine/Source/GameClient/DrawableColorFlash.cpp`|UnsignedInt|1|124|
|3749|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetWarehouseValue_Thunk.cpp`|Int|1|162|
|3750|`game/GameEngine/Source/GameClient/GUI/Rva0051D590ShellMusic.cpp`|Bool|1|198|
|3751|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva0025D6E0FreezingRainApply.cpp`|Real|1|149|
|3752|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/GUICallbacks/W3DCommandBarTopDraw.cpp`|Int|1|67|
|3753|`game/GameEngine/Source/Common/RTS/Rva000C50C0DockPredicate.cpp`|Bool|1|102|
|3754|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_doPop.cpp`|Bool|1|115|
|3755|`game/GameEngine/Source/GameLogic/AI/Rva003D60E0RadialOffset.cpp`|Int, Bool, Real|1|152|
|3756|`game/GameEngine/Source/GameLogic/Object/Update/BannerCarrierUpdateRawCtor.cpp`|Int|1|76|
|3757|`game/GameEngine/Source/GameLogic/AI/ZoneBlockEffectiveZone.cpp`|Bool|1|275|
|3758|`game/GameEngine/Source/Common/System/SaveGame/GameStateAutoSave.cpp`|Bool|1|155|
|3759|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGuardInTunnelNetwork.cpp`|Bool|1|114|
|3760|`game/GameEngine/Source/Common/System/DataChunkOutputDestructor.cpp`|Int|1|297|
|3761|`game/GameEngine/Source/Common/WatchdogReport.cpp`|UnsignedInt|1|107|
|3762|`game/GameEngine/Source/GameClient/GUI/WindowLayoutInfoDestructorThunk.cpp`|UnsignedInt|1|129|
|3763|`game/GameEngine/Source/Common/UserPreferences_write_Thunk.cpp`|Int, Bool|1|162|
|3764|`game/GameEngine/Source/Common/V3ByteBaseCopyCtor.cpp`|Int|1|50|
|3765|`game/GameEngine/Source/Common/Rva007751A0ParseS4.cpp`|Int|1|253|
|3766|`game/GameEngine/Source/GameLogic/Object/LocomotorGetMaxTurnRateObject.cpp`|Real|1|133|
|3767|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackgroundAllocateThunk.cpp`|Int|1|83|
|3768|`game/GameEngine/Source/GameLogic/Object/Update/BfmeSecondPlainMemberSet.cpp`|UnsignedInt|1|298|
|3769|`game/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgradeRemoveUpgrade.cpp`|Bool|1|85|
|3770|`game/GameEngine/Source/GameLogic/Map/TerrainLogicGetWaypointByID.cpp`|UnsignedInt|1|116|
|3771|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00259CD0BoundsCentreApply.cpp`|Real|1|149|
|3772|`game/GameEngine/Source/Common/Rva007E35E0StringStateInitialize.cpp`|Bool|1|314|
|3773|`game/GameEngine/Source/Common/RTS/PlayerListUnidentified000DF510.cpp`|Int|1|107|
|3774|`game/GameEngine/Source/Common/System/SaveGame/GameStateMap_extractAndSaveMap.cpp`|UnsignedInt|1|315|
|3775|`game/GameEngine/Source/GameLogic/AI/AIDockState_xfer.cpp`|UnsignedByte|1|218|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
