# Scalar alias contracts: cohort 166

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
|4036|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdate_canAcceptNewRepair.cpp`|Bool|1|132|
|4037|`game/Libraries/Source/WWVegas/WWLib/stlport_hashtable_uint_ptr_insert.cpp`|Int, UnsignedInt|1|111|
|4038|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_endPreparation.cpp`|UnsignedInt, Bool|1|225|
|4039|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorRva00370340.cpp`|Bool|1|794|
|4040|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate_doPullInDocking_Bfme.cpp`|Real|1|308|
|4041|`game/GameEngine/Source/GameLogic/Object/ObjectDoCommandButtonAtPosition.cpp`|Bool|1|464|
|4042|`game/GameEngine/Source/GameLogic/AI/AI_parseSideInfo.cpp`|Int|1|299|
|4043|`game/GameEngine/Source/GameLogic/Object/Weapon_preFireWeapon.cpp`|UnsignedInt|1|403|
|4044|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/GameSpyLoginPreferencesWriteThunk.cpp`|Bool|1|927|
|4045|`game/GameEngineDevice/Source/W3DDevice/GameClient/RTS2DScene_Ctor_Thunk.cpp`|Bool|1|209|
|4046|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenLeave.cpp`|Bool|1|359|
|4047|`game/GameEngine/Source/GameNetwork/LANAPIOnGameCreate.cpp`|Int, UnsignedInt|1|243|
|4048|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/UpdateBestLadderRanks004DBBF0.cpp`|Int|1|525|
|4049|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doFireSpecialPowerOnTeam.cpp`|Bool, Real|1|109|
|4050|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_createSpecialObject.cpp`|UnsignedInt|1|232|
|4051|`game/GameEngine/Source/GameLogic/AI/PathfinderXferE38F0.cpp`|Int|1|439|
|4052|`game/GameEngine/Source/GameLogic/Object/Object_rva001CD420_propagateContainModelCondition.cpp`|Bool, Int|1|225|
|4053|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIGiantBirdFollowThruStateUpdate.cpp`|UnsignedInt|1|347|
|4054|`game/GameEngine/Source/GameClient/DrawableRefreshAmbientSound.cpp`|UnsignedInt|1|396|
|4055|`game/GameEngine/Source/GameClient/GUI/ControlBar/Rva004BC8A0.cpp`|Bool|1|175|
|4056|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSmudge_copyRect.cpp`|Int|1|326|
|4057|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0077C390Parse.cpp`|Int|1|588|
|4058|`game/GameEngine/Source/GameClient/EffectFactory0040A260Create.cpp`|Int|1|337|
|4059|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineEvaluateConditions.cpp`|Bool|1|372|
|4060|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayCaptureScreen.cpp`|UnsignedInt|1|501|
|4061|`game/GameEngine/Source/Common/Rva0051D1E0Shutdown.cpp`|Bool|1|149|
|4062|`game/GameEngine/Source/Common/Rva001CCFC0OwnerApplyMask.cpp`|Bool, Int|1|332|
|4063|`game/GameEngine/Source/GameLogic/Object/Upgrade/GarrisonUpgradeRemoveUpgrade.cpp`|Bool, UnsignedInt|1|142|
|4064|`game/GameEngine/Source/Common/Rva0039B2B0Xfer.cpp`|UnsignedByte|1|134|
|4065|`game/GameEngine/Source/GameLogic/Object/Locomotor_rva001BB0D0.cpp`|Real|1|890|
|4066|`game/GameEngine/Source/GameLogic/Object/SpecialPower/SplitHordeSpecialPowerDoSpecialPower.cpp`|UnsignedInt|1|170|
|4067|`game/GameEngine/Source/GameLogic/Object/Object_notifyRva001C89E0.cpp`|UnsignedInt|1|123|
|4068|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayTransition006E8310.cpp`|Real|1|555|
|4069|`game/GameEngine/Source/GameLogic/AI/AIHarvestPrepareSiteState_update.cpp`|UnsignedInt|1|272|
|4070|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadQRPlayerKeyCallback.cpp`|Bool|1|612|
|4071|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarConstructor.cpp`|UnsignedInt|1|787|
|4072|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupReplayInit_Thunk.cpp`|Bool|1|386|
|4073|`game/GameEngine/Source/GameLogic/AI/Rva0016AEE0WeaponRangePosition.cpp`|Bool|1|109|
|4074|`game/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate_endRepair.cpp`|Bool|1|76|
|4075|`game/GameEngine/Source/GameClient/LanguageFilter_InsertUnique_0044D960.cpp`|Bool|1|446|
|4076|`game/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorRva00371B00.cpp`|Bool|1|419|
|4077|`game/GameEngine/Source/GameLogic/Object/Locomotor_maintainCurrentPosition.cpp`|Bool, Real|1|616|
|4078|`game/GameEngine/Source/GameLogic/Rva0037FE30_record.cpp`|Bool|1|260|
|4079|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/grabWindowPointers.cpp`|Int|1|714|
|4080|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsRva0032C7F0.cpp`|Bool|1|324|
|4081|`game/GameEngine/Source/Common/RTS/Team_notifyTeamOfObjectDeath.cpp`|Bool, Int|1|279|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
