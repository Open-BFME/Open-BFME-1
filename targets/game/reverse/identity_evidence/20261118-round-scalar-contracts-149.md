# Scalar alias contracts: cohort 149

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
|3185|`game/GameEngine/Source/GameLogic/Object/ObjectModelConditions.cpp`|Int, Bool, UnsignedInt|4|337|
|3186|`game/GameEngine/Source/GameLogic/AI/Rva003F5340RingSearch.cpp`|Bool, Int|4|2603|
|3187|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPowerAndUpgradeFromUnit.cpp`|Int, Bool|4|560|
|3188|`game/GameEngine/Source/GameClient/GUI/GameWindowTransitionsHandler.cpp`|Bool, Int|4|981|
|3189|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsTeamMovement.cpp`|Bool, Int|4|1064|
|3190|`game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAttackMoveToStateOnEnter.cpp`|Int, Bool|4|659|
|3191|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsTeamMembers.cpp`|Bool, Int, Real, UnsignedInt, UnsignedShort|5|993|
|3192|`game/GameEngine/Source/GameNetwork/NetPacket_init.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte|5|498|
|3193|`game/GameEngine/Source/Common/ExperienceLevelCopyConstructor.cpp`|Bool, UnsignedInt, Int, Real|5|1009|
|3194|`game/GameEngine/Source/GameClient/GUI/AptPalantirRva00594740.cpp`|Int, UnsignedInt, Bool, Real|5|1698|
|3195|`game/GameEngine/Source/GameLogic/AI/PathfindZoneBlockQueries.cpp`|Int, UnsignedInt, Bool|5|527|
|3196|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayLetterBox.cpp`|Bool, UnsignedInt, Int|5|812|
|3197|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/ControlBarPopupDescription.cpp`|Bool, Int, UnsignedInt|5|1109|
|3198|`game/GameEngine/Source/Common/IntUnsignedMapCopy.cpp`|Int, UnsignedInt|5|447|
|3199|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/GameSpyPeerMessageQueueConstructor.cpp`|Bool, Int|5|298|
|3200|`game/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdateModuleDataCtorThunk.cpp`|Int, Bool|5|317|
|3201|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyGameSlot_setPingString.cpp`|Int, Bool|5|473|
|3202|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/UpdateDiplomacyBriefingUnicodeText.cpp`|Int, Bool|5|461|
|3203|`game/GameEngine/Source/GameClient/GUI/ControlBar/CommandSetLifetime.cpp`|Int, Bool|5|522|
|3204|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedUnitProperties.cpp`|Bool, Int, Real|5|350|
|3205|`game/GameEngine/Source/Common/RTS/ScoreKeeperScoring.cpp`|Int, UnsignedInt|5|738|
|3206|`game/GameEngine/Source/GameLogic/Object/Contain/Rva00237BD0HordeMemberWalks.cpp`|Int, UnsignedInt|5|892|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
