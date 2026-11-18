# Scalar alias contracts: cohort 132

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
|2279|`game/GameEngine/Source/GameClient/EvaCheckVec_resize.cpp`|Int, Real|1|41|
|2280|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread_stopHostingAlready.cpp`|Int, Bool|1|96|
|2281|`game/GameEngine/Source/GameLogic/Object/Object_bfmeGetMultiLogicalBonePosition.cpp`|Bool, Int|1|174|
|2282|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00227B60ContainDispatch.cpp`|Bool, UnsignedInt, Int|1|103|
|2283|`game/GameEngine/Source/GameLogic/Pathfinder/PathfindBuildActualPathE10f0.cpp`|Int, Bool|1|181|
|2284|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva0071CF40.cpp`|Int, Real|1|178|
|2285|`game/GameEngine/Source/GameLogic/Object/ApplyRandomForceNugget_ctor_Thunk.cpp`|Real, Bool|1|32|
|2286|`game/GameEngine/Source/GameLogic/AI/Rva003DAD60Adjust.cpp`|Int, Bool|1|170|
|2287|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_setAbilityBits.cpp`|Int, Bool, UnsignedInt|1|135|
|2288|`game/GameEngine/Source/GameLogic/Object/Update/AttributeHandleStandInDestructor.cpp`|Int, UnsignedInt|1|76|
|2289|`game/GameEngine/Source/Common/ExperienceLevelSystemExperienceForNextLevel.cpp`|Bool, Int, Real|1|201|
|2290|`game/GameEngine/Source/GameLogic/Object/Behavior/Gen003711C0StatusReset.cpp`|Int, Bool|1|161|
|2291|`game/GameEngine/Source/Common/RTS/PlayerCountObjects.cpp`|Int, UnsignedInt|1|149|
|2292|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva00550500StartPings.cpp`|Int, Bool|1|394|
|2293|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterRenderObjRebuild.cpp`|Bool, Int|1|178|
|2294|`game/GameEngine/Source/GameClient/GUI/Shell/ShellMenuSchemeDestructor.cpp`|Int, UnsignedShort|1|238|
|2295|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderChooseBestLocomotor.cpp`|Int, Real|1|143|
|2296|`game/GameEngine/Source/GameLogic/Object/Weapon_isSourceObjectWithGoalPositionWithinAttackRange.cpp`|Real, Bool|1|188|
|2297|`game/GameEngine/Source/Common/INI/Rva0006AF00FunctionCurveParseKey.cpp`|Real, Int|1|248|
|2298|`game/Libraries/Source/xfer/Gen009D8CA0ReadAt.cpp`|Int, Bool|1|183|
|2299|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva0026C8C0SetStatus.cpp`|Int, Bool|1|94|
|2300|`game/Libraries/Source/WWVegas/WW3D2/BoxDynamicVBAccessCtor.cpp`|UnsignedInt, UnsignedShort|1|82|
|2301|`game/GameEngine/Source/Common/Rva0015AAC0ComputeSize.cpp`|Int, Real|1|114|
|2302|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva0071C9C0.cpp`|Int, Real|1|397|
|2303|`game/GameEngine/Source/Common/INI/Rva000BD900ParseFCurveOrReal.cpp`|Int, Real|1|180|
|2304|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorRva0036F2D0RecordLookup.cpp`|Real, Int|1|403|
|2305|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineSetPriorityDefault.cpp`|Bool, Int|1|170|
|2306|`game/GameEngine/Source/Common/Bezier/BezierSegmentGetSegmentPoints.cpp`|Int, Bool|1|249|
|2307|`game/GameEngine/Source/GameLogic/Pathfinder/PathfindCell_costSoFar.cpp`|UnsignedInt, UnsignedShort|1|190|
|2308|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/Pinger_startThreads.cpp`|Int, Bool|1|234|
|2309|`game/GameEngine/Source/Common/Rva001FE670AffordCheck.cpp`|Real, UnsignedInt|1|71|
|2310|`game/GameEngine/Source/GameClient/GUI/ParseIconObjectBlock.cpp`|Int, Real|1|209|
|2311|`game/GameEngine/Source/Common/System/GeometryInfoDefaultConstructor.cpp`|Bool, Real|1|111|
|2312|`game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerGetFileLengthMS.cpp`|Bool, Real|1|214|
|2313|`game/GameEngine/Source/GameLogic/ScriptEngine/Rva002EDF70TacticalAngle.cpp`|Real, Int|1|115|
|2314|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_setMaxHealth.cpp`|Bool, Real|1|129|
|2315|`game/GameEngine/Source/GameLogic/AI/Rva003DAC80Adjust.cpp`|Int, Bool|1|170|
|2316|`game/GameEngine/Source/GameLogic/Object/Contain/Rva002274A0ParsePassengerBone.cpp`|Bool, UnsignedInt, Int|1|425|
|2317|`game/GameEngine/Source/GameLogic/AI/AIGroup_groupDoSpecialPower.cpp`|Bool, UnsignedInt|1|135|
|2318|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoRemoveFromSavedIgnoreListThunk.cpp`|Int, Bool|1|118|
|2319|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewSetZoomBfme.cpp`|Bool, Real|1|185|
|2320|`game/GameEngine/Source/GameNetwork/GameInfo_getSlotNum_Thunk.cpp`|Int, Bool|1|301|
|2321|`game/GameEngine/Source/GameNetwork/GameInfo_IsSlotLocalAlly_Rva000A3170.cpp`|Bool, Int|1|61|
|2322|`game/GameEngine/Source/GameLogic/Object/WeaponParseMinMaxDuration.cpp`|Int, Real|1|234|
|2323|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDebugDisplayDrawText.cpp`|Int, Char|1|220|
|2324|`game/GameEngine/Source/GameClient/ParticleSystemFXNugget_dtor_Thunk.cpp`|Real, Bool|1|127|
|2325|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorPrepareOwnedObjectForUnpack.cpp`|Int, Bool|1|131|
|2326|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/MonsterDockUpdateOnExitReached.cpp`|UnsignedInt, Bool, Int|1|174|
|2327|`game/GameEngine/Source/GameLogic/Object/Damage/EvacuateDamage_onDamage.cpp`|Int, Real|1|155|
|2328|`game/GameEngine/Source/GameLogic/Object/Object_setSingleModelCondition.cpp`|Int, UnsignedInt|1|71|
|2329|`game/Libraries/Source/EA/Apt/AptString/Rva8CD130StringFind0089FF80.cpp`|UnsignedShort, Int|1|319|
|2330|`game/GameEngine/Source/GameLogic/AI/AIGroup_add.cpp`|UnsignedInt, Bool|1|150|
|2331|`game/GameEngine/Source/GameLogic/Object/Behavior/AutoAbilityBehavior_bfmeCanAutoFire.cpp`|UnsignedInt, Bool|1|125|
|2332|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenuStartPings.cpp`|Int, Bool|1|394|
|2333|`game/GameEngine/Source/GameLogic/Map/TerrainLogicNewMap.cpp`|Bool, Real|1|58|
|2334|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doResumeSupplyTruckingForIdleUnits.cpp`|Bool, Int|1|137|
|2335|`game/GameEngine/Source/GameNetwork/GameSpy/promoted__amIHost_GameSpyStagingRoom_UBE_NXZ_00638350.cpp`|Int, Bool|1|109|
|2336|`game/GameEngine/Source/GameNetwork/NAT_constructor_BFME.cpp`|UnsignedInt, UnsignedShort|1|154|
|2337|`game/GameEngine/Source/GameClient/FXNuggetConstructor.cpp`|UnsignedInt, Bool|1|225|
|2338|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowAllocateShadowVolume.cpp`|Bool, Int|1|211|
|2339|`game/GameEngine/Source/GameLogic/Object/Update/ProductionUpdateRva0029DA90.cpp`|Bool, UnsignedInt|1|158|
|2340|`game/GameEngine/Source/GameLogic/AI/AIGroup_setWeaponLockForGroup.cpp`|Int, Bool|1|163|
|2341|`game/GameEngine/Source/GameClient/GUI/GameWindowTransitions_findGroup.cpp`|Int, UnsignedShort|1|307|
|2342|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedEmoticon.cpp`|Real, Int|1|66|
|2343|`game/GameEngine/Source/GameLogic/Object/Contain/OpenContainGetPassengerBoneName.cpp`|Bool, UnsignedInt|1|115|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
