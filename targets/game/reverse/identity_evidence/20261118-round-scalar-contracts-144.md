# Scalar alias contracts: cohort 144

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
|2972|`game/GameEngine/Source/GameLogic/AI/AIPlayerSupply.cpp`|Bool, Int, Real|2|528|
|2973|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerPrimaryIdleState_update.cpp`|Bool, Int, Real|2|831|
|2974|`game/GameEngine/Source/GameLogic/AI/AIPlayerComputeSuperweaponTarget.cpp`|Bool, Int, Real|2|1435|
|2975|`game/GameEngine/Source/GameLogic/System/BfmeCellGridDecayCells.cpp`|UnsignedInt, Real|2|63|
|2976|`game/GameEngine/Source/Common/BitFlags29Xfer.cpp`|Int, UnsignedByte|2|107|
|2977|`game/GameEngine/Source/GameClient/GUI/parseComboBoxData_Thunk.cpp`|Bool, Int|2|281|
|2978|`game/GameEngine/Source/GameLogic/AI/PathfindLayer_bfmeContainsPoint.cpp`|Bool, Int, Real|2|119|
|2979|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptAction_duplicate.cpp`|Int, Bool|2|609|
|2980|`game/GameEngine/Source/GameNetwork/BFMEDisconnectManager_voterEligibility.cpp`|Bool, Int|2|128|
|2981|`game/GameEngine/Source/GameLogic/Object/Upgrade/StealthUpgradeUpgradeImplementation.cpp`|Int, Bool|2|83|
|2982|`game/GameEngine/Source/Common/Rva003B9100Contains.cpp`|Int, UnsignedShort|2|283|
|2983|`game/GameEngine/Source/Common/Dict_getAsciiString.cpp`|Int, UnsignedInt, Bool|2|118|
|2984|`game/GameEngine/Source/GameClient/TintDrawableFXNugget_doFXObj_Thunk.cpp`|Real, UnsignedInt|2|121|
|2985|`game/GameEngine/Source/GameNetwork/NetCommandRef_dtor.cpp`|Int, UnsignedInt, UnsignedByte|2|57|
|2986|`game/GameEngine/Source/GameLogic/Object/WeaponBonusSet_parseWeaponBonusSet.cpp`|Int, Real|2|109|
|2987|`game/GameEngine/Source/Common/INI/Rva00064680ParseControlPointBlock.cpp`|Int, Real|2|171|
|2988|`game/GameEngine/Source/GameLogic/AI/PathAppendNodeCopy.cpp`|Int, Real, Bool|2|233|
|2989|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerRequestCopies.cpp`|Int, Bool, UnsignedInt, UnsignedShort|2|814|
|2990|`game/GameEngine/Source/GameClient/GUI/GameWindowManager_drawWindow_Thunk.cpp`|Int, UnsignedInt|2|208|
|2991|`game/GameEngine/Source/GameLogic/ScriptEngine/Condition_duplicate.cpp`|Int, Bool|2|597|
|2992|`game/GameEngine/Source/GameLogic/ScriptEngine/XferListAsciiString.cpp`|UnsignedByte, UnsignedShort, Bool|2|384|
|2993|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00233F30RotatedRecord.cpp`|Int, Real|2|130|
|2994|`game/GameEngine/Source/Common/System/GeometryParseActiveAndOffset.cpp`|Bool, Real|2|125|
|2995|`game/GameEngine/Source/GameClient/System/ParticleSystemManager_friend_add.cpp`|Bool, UnsignedInt|2|204|
|2996|`game/GameEngine/Source/GameNetwork/NAT_attachSlotList_BFME.cpp`|UnsignedInt, UnsignedShort|2|223|
|2997|`game/GameEngine/Source/Common/BfmeVisionSpiedMaskHandlers.cpp`|Int, UnsignedInt|2|286|
|2998|`game/GameEngine/Source/Common/System/BuildAssistant_isRemovableForConstruction.cpp`|Bool, UnsignedInt|2|180|
|2999|`game/GameEngine/Source/Common/System/GeometryParseHeightAndMajorRadius.cpp`|Bool, Real|2|146|
|3000|`game/GameEngine/Source/Common/INI/INIAudioEventInfo.cpp`|Int, Real|2|314|
|3001|`game/GameEngine/Source/GameClient/LightPulseFXNuggetEffects.cpp`|Real, UnsignedInt|2|174|
|3002|`game/GameEngine/Source/GameLogic/ScriptEngine/XferListAsciiStringCoord3D.cpp`|UnsignedByte, UnsignedShort, Bool|2|452|
|3003|`game/GameEngine/Source/GameNetwork/DisconnectManager_disconnectPlayer_Thunk.cpp`|Int, UnsignedInt|2|236|
|3004|`game/GameEngine/Source/GameClient/Drawable/Behavior/RandomSoundSelectorClientBehavior.cpp`|Real, UnsignedInt|2|241|
|3005|`game/GameEngine/Source/GameClient/Shadow_setSize.cpp`|Int, Real|2|164|
|3006|`game/GameEngine/Source/GameLogic/Object/PartitionFilterRejectBuildings.cpp`|Bool, UnsignedByte, UnsignedInt|2|292|
|3007|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewGetAxisAlignedViewRegion.cpp`|Real, Int|2|616|
|3008|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarPurchaseScience.cpp`|Int, Bool|2|161|
|3009|`game/GameEngine/Source/Common/ExperienceLevelSystemSelectNext.cpp`|Bool, Int|2|191|
|3010|`game/GameEngine/Source/GameLogic/ScriptEngine/Parameter_WriteParameter_Thunk.cpp`|Int, Real|2|193|
|3011|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doUnitStartSequentialScript_Bfme.cpp`|Bool, Int|2|235|
|3012|`game/GameEngine/Source/GameClient/GUI/FontLibraryBFMERetail_getFont.cpp`|Int, Real|2|150|
|3013|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ReplayMenuGetReplayFilenameFromListbox.cpp`|Int, Bool|2|344|
|3014|`game/GameEngine/Source/Common/Dict_releaseData.cpp`|Int, UnsignedInt, Bool|2|280|
|3015|`game/GameEngine/Source/GameLogic/Object/Update/ProneUpdate_startProneEffects.cpp`|Int, Bool|2|148|
|3016|`game/GameEngine/Source/GameNetwork/NetPacket_readRequestGameSpyStatsAuthKey.cpp`|Int, UnsignedByte|2|438|
|3017|`game/GameEngine/Source/GameClient/GUI/Shell/ShellDestructor.cpp`|Int, UnsignedInt|2|286|
|3018|`game/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateOnExitShim.cpp`|UnsignedInt, UnsignedByte|2|194|
|3019|`game/GameEngine/Source/GameLogic/Object/Contain/HordeContainTryScheduleReformation.cpp`|Bool, UnsignedInt|2|172|
|3020|`game/GameEngine/Source/GameClient/GUI/IMEManagerDestructor.cpp`|Bool, Int|2|246|
|3021|`game/GameEngine/Source/GameClient/GameClientDrawableTOCXfer.cpp`|UnsignedInt, UnsignedShort|2|493|
|3022|`game/GameEngineDevice/Source/W3DDevice/GameClient/BfmeVertexShaderLoader.cpp`|Int, Bool|2|277|
|3023|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doNamedFlash_Thunk.cpp`|Int, UnsignedInt|2|137|
|3024|`game/GameEngine/Source/Common/RTS/ScienceStoreGetPurchasableSciences.cpp`|Bool, Int|2|504|
|3025|`game/GameEngine/Source/GameLogic/AI/AIGroupSourceObjects.cpp`|Int, UnsignedInt|2|189|
|3026|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/PlayerChangedNickCallback.cpp`|Int, UnsignedInt|2|720|
|3027|`game/GameEngine/Source/GameLogic/Object/Behavior/ParkingPlaceInfoVectorInsertOverflow.cpp`|Real, Int|2|348|
|3028|`game/GameEngine/Source/GameLogic/Object/Body/ActiveBody_createParticleSystems.cpp`|Bool, Int|2|593|
|3029|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate.cpp`|Int, UnsignedInt|2|363|
|3030|`game/GameEngine/Source/GameClient/GUI/GameWindowTextAndHitTest.cpp`|Int, Bool|2|513|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
