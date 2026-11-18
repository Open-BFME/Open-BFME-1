# Scalar alias contracts: cohort 154

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
|3270|`game/GameEngine/Source/GameClient/System/Image_getStatus.cpp`|UnsignedInt|1|4|
|3271|`game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/Gen_01307178ReAcquireResourcesThunk.cpp`|Bool|1|5|
|3272|`game/GameEngine/Source/Common/BfmeCopyBackward28.cpp`|UnsignedInt|1|79|
|3273|`game/GameEngine/Source/Common/Rva006FCBD0ClampForward.cpp`|Real|1|50|
|3274|`game/GameEngine/Source/Common/Rva007AE610Array.cpp`|UnsignedInt|1|15|
|3275|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AnimalAIUpdateRva00116950Slot4.cpp`|Bool|1|3|
|3276|`game/GameEngine/Source/Common/Rva005BDBC0IsZero2D.cpp`|Real|1|49|
|3277|`game/GameEngine/Source/GameLogic/AI/Rva00183BF0StateBool.cpp`|Bool|1|3|
|3278|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DBuffDrawObscuredVirtual.cpp`|Bool|1|3|
|3279|`game/GameEngine/Source/Common/Rva003D4DA0Getter.cpp`|Int|1|4|
|3280|`game/GameEngine/Source/GameClient/ViewSetViewFilterPosBfme.cpp`|Bool|1|3|
|3281|`game/GameEngine/Source/GameLogic/Object/LocomotorPreferredHeight.cpp`|Real|1|4|
|3282|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_setChooseVictimAlwaysUsesNormal.cpp`|Bool|1|13|
|3283|`game/GameEngine/Source/Common/Rva0043A610ByteFieldGetter.cpp`|UnsignedByte|1|4|
|3284|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyGameSlot_getFavoriteSide.cpp`|Int|1|4|
|3285|`game/GameEngine/Source/Common/Rva0036CD30OptionalFloat.cpp`|Real|1|19|
|3286|`game/GameEngine/Source/GameLogic/Object/SpecialPower/CashHackUpgradesVectorInsertOverflow.cpp`|Int|1|305|
|3287|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyGameSlot_getLosses.cpp`|Int|1|4|
|3288|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDebugDisplaySetFontHeight.cpp`|Int|1|10|
|3289|`game/GameEngineDevice/Source/W3DDevice/GameClient/ScreenMotionBlurFilterShutdown.cpp`|Int|1|6|
|3290|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDrawSetFullyObscured.cpp`|Bool|1|3|
|3291|`game/GameEngine/Source/GameClient/System/ParticleSystemIsSaveable.cpp`|Bool|1|7|
|3292|`game/GameEngine/Source/GameClient/System/ParticleSystemIsDestroyed.cpp`|Bool|1|7|
|3293|`game/GameEngine/Source/Common/Rva004781A0Get.cpp`|Int|1|31|
|3294|`game/GameEngine/Source/GameClient/System/ParticleSystemGetStartFrame.cpp`|UnsignedInt|1|7|
|3295|`game/GameEngine/Source/Common/Rva0036CD50GuardedRatio.cpp`|Real|1|36|
|3296|`game/GameEngine/Source/Common/System/Radar_queueTerrainRefresh.cpp`|UnsignedInt|1|15|
|3297|`game/GameEngine/Source/GameLogic/Object/BfmeThingEFEClampIndex.cpp`|Real|1|47|
|3298|`game/GameEngine/Source/GameClient/W3DViewGetAngleBfme.cpp`|Real|1|4|
|3299|`game/GameEngine/Source/GameClient/System/ParticleSystemGetParticleCount.cpp`|UnsignedInt|1|7|
|3300|`game/GameEngine/Source/Common/Bfme5CeilCellExtent.cpp`|Real|1|41|
|3301|`game/GameEngine/Source/Common/Rva007AE3E0Pair.cpp`|UnsignedInt|1|21|
|3302|`game/GameEngine/Source/GameLogic/Object/Locomotor_rva001BD790.cpp`|Real|1|24|
|3303|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DParticleSystemManagerQueueParticleRender.cpp`|Bool|1|8|
|3304|`game/GameEngine/Source/GameClient/System/ParticleSystemIsSystemForever.cpp`|Bool|1|7|
|3305|`game/GameEngine/Source/GameLogic/Object/Contain/HealContainIsHealContain.cpp`|Bool|1|3|
|3306|`game/GameEngine/Source/GameClient/GUI/GameWindowStatusThunk.cpp`|UnsignedInt|1|19|
|3307|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineCreateNamedMapRevealILT.cpp`|Real|1|5|
|3308|`game/GameEngine/Source/Common/Bfme/Rva006E7B20Vector3Setter.cpp`|Int|1|33|
|3309|`game/GameEngine/Source/Common/Rva0005CBD0BufferGrow.cpp`|UnsignedInt|1|37|
|3310|`game/GameEngine/Source/GameClient/System/ParticleSystemSetSystemLifetime.cpp`|UnsignedInt|1|13|
|3311|`game/GameEngine/Source/Common/Rva007AE5E0RefPtr.cpp`|UnsignedInt|1|39|
|3312|`game/GameEngine/Source/GameLogic/AI/PathfindMovementProfileIndex.cpp`|Bool|1|33|
|3313|`game/GameEngine/Source/GameClient/System/ParticleSystemManagerSetOnScreenParticleCount.cpp`|Int|1|13|
|3314|`game/GameEngine/Source/Common/SmallGaps/Rva0090FE40ExtractReset.cpp`|Real|1|61|
|3315|`game/GameEngine/Source/GameNetwork/Rva006911A0HandleBridgeWorker.cpp`|UnsignedByte|1|56|
|3316|`game/GameEngine/Source/GameLogic/AI/Rva000F9250.cpp`|Bool|1|10|
|3317|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw_setAnimationLoopDuration.cpp`|Real|1|63|
|3318|`game/GameEngine/Source/GameLogic/AI/PathScaledCount.cpp`|Real|1|79|
|3319|`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierValueRange_findValue.cpp`|Bool|1|46|
|3320|`game/GameEngine/Source/GameClient/W3DViewGetPitchBfme.cpp`|Real|1|4|
|3321|`game/GameEngine/Source/GameClient/System/ParticleSystemManagerGetParticleCount.cpp`|UnsignedInt|1|7|
|3322|`game/GameEngine/Source/Common/Bezier/Rva000059EDBezierSegmentThunk.cpp`|Real|1|5|
|3323|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DParticleSystemManagerGetOnScreenParticleCount.cpp`|Int|1|7|
|3324|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewGetFXPitchBfme.cpp`|Real|1|4|
|3325|`game/GameEngine/Source/Common/Rva002BC210Call.cpp`|Bool|1|17|
|3326|`game/GameEngine/Source/GameNetwork/DisconnectManager_hasPingSuccessRatioAtLeast.cpp`|Real|1|46|
|3327|`game/GameEngine/Source/Common/BfmeConv595.cpp`|Bool|1|43|
|3328|`game/GameEngine/Source/Common/BfmeConv1675.cpp`|Real|1|68|
|3329|`game/GameEngine/Source/Common/SkirmishBattleHonorsTotals.cpp`|Int|1|247|
|3330|`game/GameEngine/Source/GameClient/W3DViewIsMouseLockedBfme.cpp`|Bool|1|7|
|3331|`game/GameEngine/Source/Common/BfmeSetupAPB.cpp`|UnsignedInt|1|80|
|3332|`game/GameEngine/Source/GameClient/Terrain/TerrainRoadTypeSetRepairedToFXStringILT.cpp`|Int|1|5|
|3333|`game/GameEngine/Source/Common/BitFlags181TestSetAndClear.cpp`|Bool|1|230|
|3334|`game/GameEngine/Source/GameLogic/Object/ObjectClearStatusType.cpp`|Bool|1|71|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
