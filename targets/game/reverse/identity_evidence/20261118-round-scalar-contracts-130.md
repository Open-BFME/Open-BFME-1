# Scalar alias contracts: cohort 130

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
|2156|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_onVeterancyLevelChanged.cpp`|Int, Bool, Real|1|520|
|2157|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateIdle.cpp`|Bool, Int, UnsignedInt|1|296|
|2158|`game/GameEngine/Source/GameClient/GUI/OnlineStateUpdateCreateGame0053E390.cpp`|Bool, UnsignedInt, UnsignedShort|1|992|
|2159|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_populateSpecialPowerShortcut.cpp`|Int, UnsignedInt, Bool|1|624|
|2160|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003E5E40.cpp`|Int, Bool, Real|1|460|
|2161|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SiegeDeployHordeSpecialPowerRva00265ED0.cpp`|Int, Bool, Real, UnsignedInt|1|659|
|2162|`game/GameEngine/Source/GameNetwork/LANGameInfoParseGameOptionsString.cpp`|Int, Bool, UnsignedInt|1|954|
|2163|`game/GameEngine/Source/GameLogic/System/GameLogicInit.cpp`|Real, Bool, Int|1|1017|
|2164|`game/GameEngine/Source/GameLogic/AI/AIPlayerQueueDozer.cpp`|Bool, Int, UnsignedInt|1|490|
|2165|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainOnRemoving.cpp`|Bool, Int, UnsignedInt|1|415|
|2166|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doTeamGarrisonNearestBuilding.cpp`|Bool, Real, Int, UnsignedInt|1|536|
|2167|`game/GameEngine/Source/GameLogic/Object/Update/ProductionUpdate_queueCreateUnit.cpp`|Int, UnsignedInt, Bool|1|603|
|2168|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003DF250.cpp`|Int, Bool, Real|1|648|
|2169|`game/GameEngine/Source/GameLogic/Object/Weapon_computeApproachTarget.cpp`|Real, Int, Bool|1|1042|
|2170|`game/GameEngine/Source/Common/Rva0078E570DrawBorder.cpp`|Int, Real, Bool|1|572|
|2171|`game/GameEngine/Source/GameLogic/AI/AIPlayerOnUnitProduced.cpp`|Bool, Real, Int, UnsignedInt|1|595|
|2172|`game/GameEngine/Source/GameLogic/Object/Update/ToppleUpdateApplyTopplingForce.cpp`|Real, Int, UnsignedInt|1|832|
|2173|`game/GameEngine/Source/GameLogic/AI/PathfinderAdjustToPossibleDestination.cpp`|Int, Bool, Real|1|1108|
|2174|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewBuildCameraTransformBfme.cpp`|Real, Int, Bool|1|1322|
|2175|`game/GameEngine/Source/GameLogic/AI/AIFollowWaypointPathState_onEnter.cpp`|Bool, UnsignedInt, Real|1|622|
|2176|`game/GameEngine/Source/GameLogic/AI/PathfinderAdjustDestination003F6090.cpp`|Int, Bool, Real|1|1142|
|2177|`game/GameEngine/Source/GameLogic/Object/Update/StealthUpdateChangeVisualDisguise.cpp`|Bool, UnsignedInt, Int|1|1085|
|2178|`game/GameEngine/Source/GameLogic/AI/AISkirmishPlayerRecruitSpecificAITeam.cpp`|Bool, Int, Real|1|1130|
|2179|`game/GameEngine/Source/GameLogic/AI/AIPlayerQueueUnits.cpp`|Bool, Int, UnsignedInt, Real|1|805|
|2180|`game/GameEngine/Source/GameLogic/AI/AIPlayerCheckQueuedTeams.cpp`|Bool, Int, UnsignedInt|1|697|
|2181|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineLoginUpdate.cpp`|Int, UnsignedInt, Bool|1|1969|
|2182|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Rva004C0560.cpp`|Int, UnsignedInt, Bool|1|1459|
|2183|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeployStyleAIUpdate_update_BFME.cpp`|Bool, Int, UnsignedInt|1|1124|
|2184|`game/GameEngine/Source/GameClient/InGameUIDestructorThunk.cpp`|Int, UnsignedInt, Bool, UnsignedByte|1|936|
|2185|`game/GameEngine/Source/GameLogic/Object/Contain/TransportContainOnRemoving.cpp`|Int, UnsignedInt, Bool|1|987|
|2186|`game/GameEngine/Source/GameLogic/AI/AIFollowPathAsTeamState_update.cpp`|Bool, Real, UnsignedInt|1|1517|
|2187|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupPlayerInfo_responses.cpp`|Int, Bool, Real|1|2116|
|2188|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSmudgeManagerRender.cpp`|Int, UnsignedInt, Real|1|2829|
|2189|`game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateUpdate00172E70.cpp`|Bool, UnsignedInt, Real|1|1166|
|2190|`game/GameEngine/Source/Common/RTS/MoneyDepositILT.cpp`|UnsignedInt, Bool|1|5|
|2191|`game/GameEngine/Source/Common/System/StreamingArchiveFileNextLine.cpp`|Char, Int|1|3|
|2192|`game/GameEngine/Source/Common/Rva0081D520Owner.cpp`|Int, Real|1|82|
|2193|`game/GameEngine/Source/Common/Rva001ED9A0MaskIntersection.cpp`|UnsignedInt, Bool|1|189|
|2194|`game/GameEngine/Source/Common/ModelConditionFlagsOperatorNotEqual.cpp`|Bool, UnsignedInt|1|62|
|2195|`game/GameEngine/Source/GameNetwork/ConnectionManager_initTransport.cpp`|UnsignedInt, UnsignedShort|1|158|
|2196|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer_resetMatchingRow.cpp`|Int, Real|1|94|
|2197|`game/GameEngine/Source/GameLogic/Object/WeaponBonusSet_bfmeApplyBonuses.cpp`|UnsignedInt, Real|1|133|
|2198|`game/GameEngine/Source/Common/BfmeConv1408.cpp`|Bool, UnsignedInt|1|206|
|2199|`game/GameEngine/Source/Common/Rva0028BDF0RecordCopy.cpp`|UnsignedInt, UnsignedByte|1|87|
|2200|`game/GameEngine/Source/Common/RTS/PlayerListGetPlayersMask.cpp`|Int, UnsignedInt|1|56|
|2201|`game/GameEngine/Source/GameLogic/Object/Update/Gen00256970SetStatus.cpp`|Int, Bool|1|42|
|2202|`game/GameEngine/Source/GameClient/LanguageFilter_readWord.cpp`|Bool, UnsignedShort|1|160|
|2203|`game/GameEngine/Source/GameLogic/Object/Update/Gen002569B0SetStatus.cpp`|Int, Bool|1|41|
|2204|`game/GameEngine/Source/GameLogic/Object/Update/Gen00256E20SetStatus.cpp`|Int, Bool|1|46|
|2205|`game/GameEngine/Source/Common/RTS/BfmeAcademyPointRecorder_recordPointsEarned.cpp`|Int, Bool|1|36|
|2206|`game/GameEngine/Source/GameLogic/Object/Update/BfmeReleaseAttributeHandle.cpp`|Int, UnsignedInt|1|72|
|2207|`game/GameEngine/Source/GameNetwork/Network_slotIsLocalOrLive.cpp`|Int, Bool|1|17|
|2208|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate_onDockReached.cpp`|Int, Bool|1|122|
|2209|`game/GameEngine/Source/GameLogic/Object/Update/Gen002993C0SetStatus.cpp`|Int, Bool|1|49|
|2210|`game/GameEngine/Source/GameClient/System/ParticleSystemManagerRemoveOldestParticles.cpp`|Int, UnsignedInt|1|95|
|2211|`game/GameEngine/Source/GameLogic/Rva001A3390TriggerCount.cpp`|Int, Real, Bool|1|73|
|2212|`game/GameEngine/Source/GameLogic/Object/SpecialPower/Rva00266EF0ClearStatusBit63.cpp`|Int, Bool|1|62|
|2213|`game/GameEngine/Source/Common/Bfme5SeventySevenWorldAt.cpp`|Real, Int|1|135|
|2214|`game/GameEngine/Source/GameClient/TintDrawableFXNuggetConstructor.cpp`|Real, UnsignedInt|1|80|
|2215|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarRva004A0B20.cpp`|Bool, Int|1|81|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
