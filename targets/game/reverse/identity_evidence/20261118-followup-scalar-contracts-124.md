# Scalar alias contracts: cohort 124

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
|1833|`game/GameEngine/Source/GameLogic/Object/Update/ProneUpdate_goProne.cpp`|Int, Real, Bool|1|76|
|1834|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva00734790.cpp`|Int, UnsignedInt, Real|1|218|
|1835|`game/GameEngine/Source/GameClient/MapObjectWriteObjectsDataChunk.cpp`|Int, Real, Bool|1|194|
|1836|`game/GameEngine/Source/GameClient/MapCacheClearUnseenMaps.cpp`|Bool, Int, UnsignedShort|1|290|
|1837|`game/GameEngineDevice/Source/W3DDevice/GameClient/TBuffXfer.cpp`|UnsignedByte, UnsignedInt, Bool|1|165|
|1838|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineAdjustToppleDirection.cpp`|Int, UnsignedShort, Real, Bool|1|198|
|1839|`game/GameEngine/Source/Common/System/SaveGame/GameStateMap_clearScratchPadMaps.cpp`|Bool, Char, Int|1|419|
|1840|`game/GameEngine/Source/GameClient/GUI/WindowManagerRva00467F20.cpp`|Bool, Int, UnsignedInt|1|293|
|1841|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferUpdateSway.cpp`|Int, Short, Real|1|397|
|1842|`game/GameEngine/Source/Common/Rva00380790ExperienceLevelApply.cpp`|Bool, Int, Real|1|107|
|1843|`game/GameEngine/Source/GameLogic/System/BfmeCellEvaluateVictory.cpp`|Int, UnsignedInt, Real|1|1729|
|1844|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/MonsterDockUpdateOnApproachReached.cpp`|UnsignedInt, Bool, Int|1|216|
|1845|`game/GameEngine/Source/GameLogic/Object/Update/ToppleUpdate_onCollide.cpp`|Bool, Real, UnsignedByte, UnsignedInt|1|161|
|1846|`game/GameEngine/Source/GameLogic/Object/ObjectRva001CF8F0.cpp`|Bool, Int, UnsignedInt|1|114|
|1847|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleDoSpecialPowerAtLocation.cpp`|UnsignedInt, Int, Bool|1|80|
|1848|`game/GameEngineDevice/Source/W3DDevice/GameClient/Rva00747E80WriteNamedCameras.cpp`|Int, Real, Bool|1|287|
|1849|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModuleDoSpecialPower.cpp`|UnsignedInt, Int, Bool|1|76|
|1850|`game/GameEngine/Source/GameLogic/Object/Contain/RiderChangeContainIsValidContainerFor.cpp`|Bool, Int, UnsignedShort|1|156|
|1851|`game/GameEngine/Source/Common/GlobalDataSetTimeOfDay.cpp`|Real, Int, Bool|1|298|
|1852|`game/GameEngine/Source/GameLogic/Object/Update/RadarUpdate_extendRadar.cpp`|UnsignedInt, Real, Bool|1|79|
|1853|`game/GameEngine/Source/GameLogic/Object/Update/Rva00267D00.cpp`|Bool, Int, Real|1|102|
|1854|`game/GameEngine/Source/GameLogic/Object/Behavior/PassiveAreaEffectBehavior_rva00201fd0.cpp`|UnsignedInt, Real, Bool|1|114|
|1855|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModFinalPitchBfme.cpp`|Real, Int, Bool|1|171|
|1856|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineSetPriorityKind.cpp`|Bool, Int, UnsignedInt|1|259|
|1857|`game/GameEngine/Source/Common/xferTree.cpp`|UnsignedByte, UnsignedInt, Bool|1|314|
|1858|`game/GameEngine/Source/GameNetwork/Transport_init_AsciiString.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|127|
|1859|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsTeamDistanceRva00325970.cpp`|Bool, Real, Int|1|468|
|1860|`game/GameEngine/Source/GameLogic/Object/Rva001C9380Object.cpp`|Bool, Int, Real|1|215|
|1861|`game/GameEngine/Source/GameLogic/AI/PathfindCellCallbackDeda0.cpp`|Int, UnsignedInt, Bool|1|104|
|1862|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar_Rva0049E5A0ToggleMode.cpp`|Int, Bool, UnsignedInt|1|201|
|1863|`game/GameEngine/Source/GameLogic/System/VictorySystemNotifyCell.cpp`|Int, Bool, UnsignedInt|1|292|
|1864|`game/GameEngine/Source/Common/RTS/PlayerGetRva0058B590Value.cpp`|UnsignedInt, Int, Real|1|236|
|1865|`game/GameEngine/Source/GameNetwork/Network_isPlayerConnected.cpp`|Int, UnsignedInt, Bool|1|47|
|1866|`game/GameEngine/Source/Common/RTS/PartitionManagerRevealVariant008F77E0.cpp`|Real, Int, UnsignedInt|1|171|
|1867|`game/GameEngine/Source/Common/System/Rva00107140RadarEventLoc.cpp`|Int, UnsignedInt, Real|1|203|
|1868|`game/GameEngine/Source/GameLogic/Object/Update/MobMemberSlavedUpdate_stopSlavedEffects.cpp`|UnsignedInt, Bool, Int|1|70|
|1869|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_didUnitExist.cpp`|Int, UnsignedShort, Bool|1|165|
|1870|`game/GameEngine/Source/GameLogic/AI/AIAttackStateOnExitClean.cpp`|Bool, UnsignedInt, Int|1|328|
|1871|`game/GameEngine/Source/GameLogic/Object/BfmeMeleeHordeTargetInvalid.cpp`|Real, Int, Bool|1|158|
|1872|`game/GameEngine/Source/GameClient/GUI/ProcessAnimateWindowSlideFromLeft_initAnimateWindow.cpp`|UnsignedInt, Int, Real|1|235|
|1873|`game/GameEngineDevice/Source/W3DDevice/GameClient/HeightMapLineMaxHeight_006C6910.cpp`|Int, Real, UnsignedShort|1|735|
|1874|`game/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior_xfer.cpp`|UnsignedByte, UnsignedShort, UnsignedInt|1|262|
|1875|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_shouldRetaliate.cpp`|Bool, Int, UnsignedInt|1|154|
|1876|`game/GameEngine/Source/Common/RTS/Player_addSkillPoints.cpp`|Int, Real, Bool|1|295|
|1877|`game/GameEngine/Source/GameLogic/Object/Object_rva001C7530.cpp`|Real, Bool, UnsignedInt|1|161|
|1878|`game/GameEngine/Source/Common/System/UpgradeCenterCanAffordUpgrade.cpp`|Bool, Int, UnsignedInt|1|86|
|1879|`game/GameEngine/Source/GameLogic/AI/PathfinderRva003E4190.cpp`|Int, Real, Bool|1|328|
|1880|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdateOnExitReached.cpp`|UnsignedInt, Int, Bool|1|283|
|1881|`game/GameEngine/Source/Common/Rva00380EE0ExperienceAdvance.cpp`|Bool, Int, Real|1|284|
|1882|`game/GameEngine/Source/GameLogic/AI/LinePassableStruct_linePassableCallback.cpp`|Int, UnsignedInt, Bool|1|203|
|1883|`game/GameEngine/Source/GameClient/GUI/Shell/Shell_findScreenByFilename.cpp`|Int, UnsignedShort, Bool|1|265|
|1884|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_doGuardLogic.cpp`|UnsignedInt, Int, Real, Bool|1|204|
|1885|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva003F5E20.cpp`|Real, Int, Bool|1|345|
|1886|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeLighting_006F7DA0.cpp`|Real, Int, UnsignedInt|1|610|
|1887|`game/GameEngine/Source/Common/System/RecorderCopyReplayFile.cpp`|Int, UnsignedInt, Bool|1|927|
|1888|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/Rva002C3FE0HeightClearance.cpp`|Bool, Int, Real|1|332|
|1889|`game/GameEngine/Source/GameLogic/AI/AICowerState_update.cpp`|Bool, Int, UnsignedInt|1|334|
|1890|`game/GameEngineDevice/Source/Win32Device/Common/Win32LocalFileSystemOpenFileWide.cpp`|Int, Char, Bool|1|571|
|1891|`game/GameEngine/Source/GameLogic/Pathfinder/PathfinderValidMovementPosition.cpp`|Int, UnsignedInt, Bool, Real|1|226|
|1892|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRotateCameraTowardPositionBfme.cpp`|Real, Int, Bool|1|336|
|1893|`game/GameEngine/Source/GameClient/FXListDoFXPosPublic.cpp`|Bool, Int, Real|1|133|
|1894|`game/GameEngine/Source/GameLogic/Object/ObjectOnContainedBy.cpp`|UnsignedInt, Int, Bool|1|184|
|1895|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferUpdateSway.cpp`|Int, UnsignedInt, Short, Real|1|397|
|1896|`game/GameEngine/Source/Common/System/Recorder_updateRecord.cpp`|Int, UnsignedByte, Bool|1|335|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
