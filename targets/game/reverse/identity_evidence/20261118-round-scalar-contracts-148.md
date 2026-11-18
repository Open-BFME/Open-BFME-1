# Scalar alias contracts: cohort 148

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
|3156|`game/GameEngine/Source/GameClient/SuperweaponInfo.cpp`|Int, Real, Bool|4|395|
|3157|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/IMECandidateMainDraw_Thunk.cpp`|Int, UnsignedInt, Real|4|272|
|3158|`game/GameEngine/Source/Common/System/BuildAssistant_buildTiledLocations.cpp`|Bool, Real, Int, UnsignedInt|4|638|
|3159|`game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DGameWindow.cpp`|Int, Real, Bool|4|2838|
|3160|`game/GameEngine/Source/GameClient/Rva00443910OwnerDirect.cpp`|Int, UnsignedInt, Real|4|1329|
|3161|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsNamedUnit.cpp`|Bool, Int, Real|4|893|
|3162|`game/GameEngine/Source/Common/System/GeometryInfoCollidesWith.cpp`|Bool, Real, Int|4|1779|
|3163|`game/GameEngine/Source/GameLogic/ScriptEngine/TeamCommandQuery002FBC90.cpp`|Bool, Int, Real|4|3157|
|3164|`game/GameEngine/Source/GameNetwork/GameInfoParseOptions.cpp`|Int, Bool, UnsignedInt|4|5721|
|3165|`game/GameEngine/Source/GameClient/GUI/LoadScreenInit.cpp`|Int, Bool, UnsignedInt|4|5910|
|3166|`game/GameEngine/Source/Common/RelationshipHashInsert.cpp`|Int, UnsignedInt|4|784|
|3167|`game/GameEngine/Source/GameLogic/Object/Body/ImmortalBodyConstructor.cpp`|Bool, Real|4|169|
|3168|`game/GameEngine/Source/Common/Rva005C3510FloatAccessors.cpp`|Real, Int|4|84|
|3169|`game/GameEngine/Source/GameLogic/ScriptEngine/XferListInt.cpp`|UnsignedByte, UnsignedShort, Bool|4|344|
|3170|`game/GameEngine/Source/GameClient/GUI/DisconnectMenu/DisconnectMenu.cpp`|Int, Bool|4|244|
|3171|`game/GameEngine/Source/Common/RTS/PlayerHasAny.cpp`|Int, UnsignedInt, Bool|4|312|
|3172|`game/GameEngine/Source/Common/BitFlagsParseFromINI.cpp`|Int, Bool|4|478|
|3173|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBufferDestructor.cpp`|Int, UnsignedInt|4|624|
|3174|`game/GameEngine/Source/Common/RTS/PlayerObjectCounts.cpp`|Int, UnsignedInt|4|338|
|3175|`game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldCampaign.cpp`|Int, UnsignedInt|4|413|
|3176|`game/GameEngine/Source/GameLogic/AI/AIGroupMembership.cpp`|Int, UnsignedInt, Real, Bool|4|272|
|3177|`game/GameEngine/Source/GameNetwork/PopulateColorComboBox.cpp`|Bool, Int|4|1259|
|3178|`game/GameEngine/Source/GameLogic/AI/PathfindCheckDestination.cpp`|Int, Bool|4|517|
|3179|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsExperience.cpp`|Bool, Int|4|259|
|3180|`game/GameEngine/Source/Common/setUnignoreText_Thunk.cpp`|Int, Bool|4|350|
|3181|`game/GameEngine/Source/GameClient/GUI/WindowFieldParsersBfme.cpp`|Int, Bool|4|517|
|3182|`game/Libraries/Source/WWVegas/WWLib/INI_fieldParsers.cpp`|Int, Real|4|625|
|3183|`game/GameEngine/Source/Common/BfmeOneHundredOne.cpp`|Int, UnsignedShort|4|750|
|3184|`game/GameEngine/Source/GameClient/GUI/WinInstanceDataDisplayStrings.cpp`|Int, UnsignedInt, Bool|4|850|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
