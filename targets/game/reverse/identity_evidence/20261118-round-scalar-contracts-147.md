# Scalar alias contracts: cohort 147

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
|3122|`game/GameEngine/Source/GameLogic/LargeGroupAudio/LargeGroupAudioKeyMapRva003D47A0Load.cpp`|Bool, UnsignedByte|3|396|
|3123|`game/GameEngine/Source/GameClient/System/CampaignManagerConstructorAndVtable.cpp`|Bool, Int|3|159|
|3124|`game/GameEngine/Source/Common/Glo012F1028Sub_bfmeNotify.cpp`|Int, UnsignedInt|3|468|
|3125|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawImage.cpp`|Int, Real|3|460|
|3126|`game/GameEngine/Source/GameClient/Rva0040EE90OwnerUpdate.cpp`|Int, Real|3|515|
|3127|`game/GameEngine/Source/GameClient/MapCacheLoad.cpp`|Int, UnsignedShort|3|577|
|3128|`game/GameEngine/Source/GameClient/GUI/parseInputCallback_Thunk.cpp`|Int, Bool|3|390|
|3129|`game/GameEngineDevice/Source/W3DDevice/GameClient/TerrainTracksRenderObjClassSystem.cpp`|Int, Bool|3|320|
|3130|`game/GameEngine/Source/GameLogic/AI/AIWaypointPathStates.cpp`|UnsignedByte, UnsignedInt|3|269|
|3131|`game/GameEngine/Source/GameClient/GUI/BfmeAptScreenObjectivesProvide.cpp`|Bool, Int|3|521|
|3132|`game/GameEngine/Source/GameLogic/AI/AIHarvestApproachSiteState_onEnter.cpp`|Bool, Real|3|469|
|3133|`game/GameEngine/Source/GameLogic/System/GameLogicAwakenUpdate.cpp`|UnsignedInt, Int|3|613|
|3134|`game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap_stream_ctor.cpp`|Int, Bool|3|406|
|3135|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsAudio.cpp`|Bool, Int|3|735|
|3136|`game/GameEngine/Source/Common/RTS/ResourceGatheringManager_findBestSupplyWarehouse.cpp`|Bool, Real|3|987|
|3137|`game/GameEngine/Source/GameLogic/Object/ObjectSpecialPowers.cpp`|Bool, UnsignedInt|3|211|
|3138|`game/GameEngine/Source/GameClient/GameClientDestructor00431380.cpp`|UnsignedInt, UnsignedShort, Int|3|1109|
|3139|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsBuildBase.cpp`|Bool, Int|3|764|
|3140|`game/GameEngine/Source/GameClient/GUI/BfmeAptScreenInGameChatSelectedFriends.cpp`|Bool, Int|3|1729|
|3141|`game/GameEngine/Source/Common/INI/INIAudioSettings.cpp`|Real, Int|3|663|
|3142|`game/GameEngine/Source/GameLogic/AI/TurretAIOwnerAndMachine.cpp`|Bool, UnsignedInt|3|586|
|3143|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/TransportAIUpdatePrivateAttackObject.cpp`|Bool, Int|3|531|
|3144|`game/GameEngine/Source/GameClient/GUI/BfmeAptScreenInGameChatSend.cpp`|Bool, Int|3|1505|
|3145|`game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerRva006AF840.cpp`|Bool, Int|3|1389|
|3146|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineSequentialScripts.cpp`|Bool, Int|3|2120|
|3147|`game/GameEngine/Source/Common/ExperienceLevelSystemSort.cpp`|Bool, UnsignedInt, UnsignedShort, Int, Real|4|535|
|3148|`game/GameEngine/Source/GameNetwork/NetPacket_isRoomForFrameFamily.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|4|484|
|3149|`game/GameEngine/Source/Common/ExperienceLevelSystemMapOperator.cpp`|Int, Bool, UnsignedInt, Real|4|368|
|3150|`game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadarDrawEvents.cpp`|Int, Bool, Real, UnsignedInt|4|822|
|3151|`game/GameEngine/Source/GameClient/GameClientXfer00432010.cpp`|Int, Bool, Real, UnsignedShort|4|1437|
|3152|`game/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior_playerScan.cpp`|Bool, Int, UnsignedInt, Real|4|1529|
|3153|`game/GameEngine/Source/GameLogic/ScriptEngine/XferListUnsignedShort.cpp`|UnsignedByte, UnsignedShort, Bool|4|346|
|3154|`game/GameEngine/Source/GameLogic/Object/ExperienceTrackerProgression.cpp`|Int, Real, Bool|4|332|
|3155|`game/GameEngine/Source/GameLogic/AI/AI_getAdjustedVisionRangeForObject.cpp`|Int, UnsignedInt, Real|4|342|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
