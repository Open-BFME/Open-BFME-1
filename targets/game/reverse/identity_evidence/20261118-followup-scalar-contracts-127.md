# Scalar alias contracts: cohort 127

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
|2021|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate_xferMethodThunk.cpp`|UnsignedByte, UnsignedInt, Bool|1|350|
|2022|`game/GameEngine/Source/GameLogic/AI/AIFearState_update.cpp`|Bool, Real, UnsignedInt|1|402|
|2023|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardReturnState_update.cpp`|Int, UnsignedInt, Bool|1|275|
|2024|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00237E50MemberRange.cpp`|Int, UnsignedInt, Real|1|281|
|2025|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdGuardAttackAggressorState_onEnter.cpp`|Bool, Int, UnsignedInt|1|354|
|2026|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawAllocateShadows.cpp`|Bool, Real, Int|1|363|
|2027|`game/GameEngine/Source/GameLogic/System/CastleBehaviorRva0036F4D0EvaNotify.cpp`|Bool, Int, UnsignedInt|1|504|
|2028|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateConditionCooldown0027BF60.cpp`|Int, UnsignedInt, Bool, Real|1|461|
|2029|`game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_update_Thunk.cpp`|Int, UnsignedInt, Bool|1|467|
|2030|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doMoveTeamTowardsNearest.cpp`|Bool, Int, Real|1|410|
|2031|`game/GameEngine/Source/GameLogic/AI/AIGuardAttackAggressorState_onEnter_Bfme.cpp`|Bool, Int, UnsignedInt|1|284|
|2032|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerRoomMessageCallback.cpp`|Int, Bool, UnsignedInt|1|825|
|2033|`game/GameEngine/Source/GameClient/EvaInit.cpp`|Int, UnsignedInt, Real|1|258|
|2034|`game/GameEngine/Source/Common/System/Rva003C2830XferMissionObjectiveStateVector.cpp`|UnsignedByte, UnsignedInt, Bool|1|326|
|2035|`game/GameEngine/Source/Common/System/RecorderPlaybackFile.cpp`|Int, UnsignedInt, Bool|1|636|
|2036|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonOnNearestEnemyBuildingClass.cpp`|Bool, Int, Real|1|448|
|2037|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonOnNearestGarrisonedBuilding.cpp`|Bool, Int, Real|1|417|
|2038|`game/GameEngine/Source/GameClient/GUI/OnlineCustomMatchGameListTooltip.cpp`|Int, Bool, UnsignedInt|1|634|
|2039|`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenCrossFadeFilterPostRender.cpp`|Int, Real, Bool|1|925|
|2040|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva004ECD10BuddyMessageNotify.cpp`|Int, Bool, UnsignedInt|1|557|
|2041|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetPlayerOwnershipOfTypeCounter.cpp`|Bool, Int, UnsignedShort|1|498|
|2042|`game/GameEngine/Source/GameLogic/Object/Object_rva001C7CF0.cpp`|Real, Bool, Int|1|295|
|2043|`game/GameEngine/Source/GameNetwork/FileTransfer_doFileTransfer.cpp`|UnsignedByte, UnsignedShort, UnsignedInt|1|814|
|2044|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineGetPlayerMaskFromAsciiString.cpp`|Bool, Int, UnsignedShort|1|635|
|2045|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerPlayerMessageCallback.cpp`|Int, Bool, UnsignedInt|1|1075|
|2046|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_doScoutLogic.cpp`|UnsignedInt, Int, Real, Bool|1|451|
|2047|`game/GameEngine/Source/Common/RTS/ObjectGetRelationshipBody.cpp`|Int, UnsignedInt, Bool|1|311|
|2048|`game/GameEngine/Source/GameLogic/AI/PathfinderClassifyMapCell.cpp`|Bool, Int, Real|1|732|
|2049|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_doRepairLogic.cpp`|Real, Int, Bool|1|404|
|2050|`game/GameEngine/Source/GameLogic/AI/AISkirmishPlayer_computeSuperweaponTarget.cpp`|Bool, Int, Real|1|639|
|2051|`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenFilterRva007D1E60PostRender.cpp`|Int, Real, Bool|1|924|
|2052|`game/GameEngine/Source/GameNetwork/Network_RelayCommandsToCommandList.cpp`|Int, UnsignedInt, UnsignedByte|1|375|
|2053|`game/GameEngine/Source/Common/Thing/ThingTemplateInitForLTA.cpp`|Int, Bool, Real|1|1334|
|2054|`game/GameEngine/Source/GameLogic/AI/PathfinderStepE05B0.cpp`|Int, UnsignedInt, Bool|1|715|
|2055|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewResetBfme.cpp`|Real, Int, Bool|1|152|
|2056|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_doAttackLogic.cpp`|UnsignedInt, Int, Real, Bool|1|501|
|2057|`game/GameEngine/Source/GameLogic/Object/FiringTrackerBFMEXfer.cpp`|Int, UnsignedByte, UnsignedInt|1|200|
|2058|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doDisplayCinematicText.cpp`|Int, Bool, Real|1|553|
|2059|`game/GameEngine/Source/GameClient/SelectionInfo_addDrawableToList.cpp`|Bool, UnsignedInt, Int|1|273|
|2060|`game/GameEngine/Source/GameLogic/Object/ExperienceTrackerAddExperiencePoints.cpp`|Int, Real, Bool|1|260|
|2061|`game/GameEngine/Source/GameLogic/AI/AITNGuardAttackAggressorState_onEnter.cpp`|Bool, Int, UnsignedInt|1|279|
|2062|`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenFilterRva007D3580PostRender.cpp`|Int, Real, Bool|1|924|
|2063|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00239AF0.cpp`|Bool, Int, UnsignedInt|1|330|
|2064|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitStandGround.cpp`|Int, UnsignedInt, Bool|1|291|
|2065|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_getStarImage_Thunk.cpp`|Int, UnsignedInt, Bool|1|208|
|2066|`game/GameEngine/Source/GameLogic/AI/AIGuardInnerStateUpdate.cpp`|Int, UnsignedInt, Real, Bool|1|293|
|2067|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewIterateDrawablesInRegionBfme.cpp`|Int, Real, Bool|1|544|
|2068|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRotateCameraOneFrameBfme.cpp`|Real, Int, Bool|1|676|
|2069|`game/GameEngine/Source/GameLogic/AI/AIPlayerGetPlayerSuperweaponValue.cpp`|Bool, Int, Real|1|502|
|2070|`game/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse_translateEvent.cpp`|UnsignedInt, Short, Int|1|520|
|2071|`game/GameEngine/Source/GameLogic/Object/Update/Rva0026C430Apply.cpp`|Bool, Int, UnsignedInt|1|180|
|2072|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdateConstructorBfme.cpp`|Real, Int, UnsignedInt, Bool|1|464|
|2073|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamStandGround.cpp`|Int, UnsignedInt, Bool|1|373|
|2074|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeHordeApproachTargetState_onEnter.cpp`|Bool, Real, Int, UnsignedInt|1|357|
|2075|`game/GameEngine/Source/GameLogic/AI/Rva0016F7C0State_condition.cpp`|Bool, Int, UnsignedInt|1|426|
|2076|`game/GameEngine/Source/GameLogic/Object/Update/StructureToppleUpdate_doToppleDelayBurstFX.cpp`|Bool, Int, Real|1|416|
|2077|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUnderConstruction.cpp`|Int, UnsignedInt, Real, Bool|1|627|
|2078|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedUseCommandButtonOnNearestKindof.cpp`|Bool, Int, Real|1|579|
|2079|`game/GameEngine/Source/GameLogic/Object/ObjectAttemptHealingFromSoleBenefactor.cpp`|Bool, Real, UnsignedInt|1|342|
|2080|`game/GameEngine/Source/GameLogic/AI/AIDeadState_onEnter.cpp`|Bool, Int, UnsignedInt|1|214|
|2081|`game/GameEngine/Source/GameLogic/Object/Update/BannerCarrierUpdate_update.cpp`|Bool, Int, UnsignedInt|1|313|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
