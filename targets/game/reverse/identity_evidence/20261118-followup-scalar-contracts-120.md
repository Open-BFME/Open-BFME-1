# Scalar alias contracts: cohort 120

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
|1592|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_xfer.cpp`|UnsignedByte, UnsignedShort, UnsignedInt, Int, Bool, Real|1|403|
|1593|`game/GameEngine/Source/GameNetwork/Network_processDestroyPlayerCommand.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|232|
|1594|`game/GameEngine/Source/GameLogic/AI/TeamInQueueXfer.cpp`|UnsignedByte, UnsignedShort, UnsignedInt, Int, Bool|1|420|
|1595|`game/GameEngine/Source/Common/ExperienceLevelSystemFindLevel.cpp`|Bool, UnsignedInt, UnsignedShort, Int, Real|1|315|
|1596|`game/GameEngine/Source/GameClient/System/Anim2DConstructor.cpp`|UnsignedByte, UnsignedShort, UnsignedInt, Bool, Int|1|297|
|1597|`game/GameEngine/Source/GameLogic/System/Rva00375A00Xfer.cpp`|Int, Real, UnsignedInt, UnsignedByte, Bool|1|873|
|1598|`game/GameEngine/Source/GameClient/DrawableSetStealthLook.cpp`|UnsignedByte, UnsignedInt, Int, Real, Bool|1|416|
|1599|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjUpdate.cpp`|Real, Int, UnsignedInt, UnsignedByte, Bool|1|1342|
|1600|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsSkirmishSpecialPowerIsReady.cpp`|Bool, Int, UnsignedInt, UnsignedByte, UnsignedShort|1|478|
|1601|`game/GameEngine/Source/GameLogic/Pathfinder/pathfinder_path.cpp`|UnsignedByte, UnsignedInt, Int, Bool, Real|1|946|
|1602|`game/GameEngine/Source/GameLogic/Object/SpecialPower/TaintSpecialPowerAfter.cpp`|Int, UnsignedInt, UnsignedByte, Bool, Real|1|1109|
|1603|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsEvaluateUnitHasToggledWeapon.cpp`|Bool, Int, UnsignedInt, UnsignedByte, UnsignedShort|1|358|
|1604|`game/GameEngine/Source/GameLogic/Object/VictorySystemXfer.cpp`|Bool, Int, UnsignedInt, Real, UnsignedByte|1|926|
|1605|`game/GameEngine/Source/GameNetwork/LANAPI_handleInActive.cpp`|Int, UnsignedByte, UnsignedInt, UnsignedShort, Bool|1|323|
|1606|`game/GameEngine/Source/GameNetwork/LANAPIOnAccept.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|205|
|1607|`game/GameEngine/Source/GameLogic/Map/TerrainLogic_xferTerrainState.cpp`|UnsignedByte, Bool, Int, UnsignedInt, Real|1|1515|
|1608|`game/GameEngine/Source/GameLogic/Pathfinder/PathfindPrependCells.cpp`|Int, UnsignedInt, UnsignedShort, Real, Bool|1|987|
|1609|`game/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetState_updateInternal.cpp`|Int, Bool, Real, UnsignedByte, UnsignedInt|1|522|
|1610|`game/GameEngine/Source/GameNetwork/LANAPIOnChat.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|653|
|1611|`game/GameEngine/Source/GameLogic/AI/AIMoveToState_update_Bfme.cpp`|Bool, Real, Int, UnsignedByte, UnsignedInt|1|522|
|1612|`game/GameEngine/Source/GameNetwork/SinglePlayerSkirmishGameInfo_xfer.cpp`|UnsignedByte, UnsignedShort, UnsignedInt, Int, Bool|1|901|
|1613|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/MpGameSetupRva00527930.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|1516|
|1614|`game/GameEngine/Source/GameNetwork/LANAPI_OnPlayerLeave.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|638|
|1615|`game/GameEngine/Source/GameLogic/AI/Gen00168910BfmeAccept.cpp`|UnsignedByte, UnsignedShort, UnsignedInt, Int, Bool|1|1037|
|1616|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerGogoGadgetTextEntry.cpp`|Int, UnsignedInt, UnsignedShort, Short, Bool|1|738|
|1617|`game/GameEngine/Source/GameNetwork/LANAPIRequestHasMap.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|809|
|1618|`game/GameEngine/Source/GameNetwork/LANAPIBfmeSerializedGameInfo.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|480|
|1619|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderFindSafePathBfme.cpp`|Int, UnsignedInt, UnsignedShort, Bool, Real|1|750|
|1620|`game/GameEngine/Source/GameClient/Drawable/Behavior/AnimationSoundClientBehaviorUpdateAnimationSounds.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Real, Bool|1|903|
|1621|`game/GameEngine/Source/GameLogic/Map/TerrainLogicPlaceTree001AD080.cpp`|UnsignedShort, UnsignedInt, Int, Bool, Real|1|594|
|1622|`game/GameEngine/Source/Common/System/Rva00101820BuildObjectNow.cpp`|Real, Int, UnsignedInt, UnsignedByte, Bool|1|626|
|1623|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferXfer.cpp`|Int, Real, Bool, UnsignedShort, UnsignedInt|1|1966|
|1624|`game/GameEngine/Source/GameNetwork/LANAPIHandleJoinAcceptRva0068CF00.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|818|
|1625|`game/GameEngine/Source/GameNetwork/LANAPIRequestGameCreateThunk.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|722|
|1626|`game/GameEngine/Source/GameClient/Drawable_drawConstructPercent.cpp`|UnsignedByte, UnsignedInt, Int, Real, Bool|1|688|
|1627|`game/GameEngine/Source/GameNetwork/LANAPIOnGameStart.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|1041|
|1628|`game/GameEngine/Source/Common/RTS/ActionManagerCanEnterObject.cpp`|Bool, Int, UnsignedInt, UnsignedByte, Real|1|849|
|1629|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanGameOptionsMenu_StartPressed.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|2229|
|1630|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayRva006EB500.cpp`|Int, UnsignedInt, Bool, Real, UnsignedByte|1|1215|
|1631|`game/GameEngine/Source/GameLogic/AI/AIGuardShouldExit.cpp`|Int, UnsignedInt, Real, Bool|1|135|
|1632|`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapEvaluateVisibleCliff.cpp`|Int, Real, Bool, UnsignedShort|1|352|
|1633|`game/GameEngine/Source/GameNetwork/NetPacket_isAckRepeat.cpp`|Int, Bool, UnsignedInt, UnsignedShort, UnsignedByte|1|82|
|1634|`game/GameEngine/Source/GameNetwork/Network_init.cpp`|Int, UnsignedInt, UnsignedByte, Bool|1|185|
|1635|`game/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior_pulseHealObject.cpp`|Int, UnsignedInt, Real, Bool|1|121|
|1636|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006FD180MouseWorldToScreen.cpp`|Int, UnsignedInt, Real, Bool|1|277|
|1637|`game/GameEngine/Source/Common/RTS/Player_addSkillPointsForKill.cpp`|Bool, Int, Real, UnsignedByte|1|131|
|1638|`game/GameEngine/Source/Common/ExperienceLevelListCopyConstructor.cpp`|Bool, UnsignedInt, Int, Real|1|114|
|1639|`game/GameEngine/Source/GameLogic/AI/GuardRetaliateExitConditions_shouldExit.cpp`|Int, UnsignedInt, Real, Bool|1|194|
|1640|`game/GameEngine/Source/GameLogic/Object/Behavior/BezierProjectileBehavior_rva001EFB20.cpp`|Bool, Int, UnsignedInt, Real|1|356|
|1641|`game/GameEngine/Source/GameNetwork/NetPacket_fillRequestPlayerLeave.cpp`|Int, UnsignedByte, UnsignedShort, UnsignedInt|1|66|
|1642|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromTop_updateAnimateWindow.cpp`|UnsignedInt, Int, Real, Bool|1|237|
|1643|`game/GameEngine/Source/GameClient/System/Anim2DRealCoordinateDrawing.cpp`|Int, Real, UnsignedByte, UnsignedShort|1|167|
|1644|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromLeft_updateAnimateWindow_Thunk.cpp`|UnsignedInt, Int, Real, Bool|1|230|
|1645|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doRevealMapAtWaypoint.cpp`|Bool, Real, UnsignedShort, UnsignedInt|1|101|
|1646|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromRightFast_reverseAnimateWindow.cpp`|UnsignedInt, Int, Real, Bool|1|260|
|1647|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva00326490Condition.cpp`|Bool, Int, UnsignedInt, UnsignedShort|1|364|
|1648|`game/GameEngine/Source/GameLogic/Object/Update/LaserUpdate_xfer.cpp`|Bool, UnsignedByte, UnsignedInt, Real|1|240|
|1649|`game/GameEngine/Source/GameLogic/AI/Rva003F8070Pathfinder.cpp`|Int, Bool, Real, UnsignedInt|1|464|
|1650|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromRightFast_updateAnimateWindow.cpp`|UnsignedInt, Int, Real, Bool|1|230|
|1651|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerHasKilledTypeUnits.cpp`|Bool, Int, UnsignedInt, UnsignedShort|1|261|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
