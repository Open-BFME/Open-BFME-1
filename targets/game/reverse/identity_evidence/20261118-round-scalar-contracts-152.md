# Scalar alias contracts: cohort 152

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
|3239|`game/GameEngine/Source/Common/T3SmallLeafBodies.cpp`|Int, UnsignedInt, Real|8|217|
|3240|`game/GameEngineDevice/Source/W3DDevice/GameClient/Water/WaterPolygon.cpp`|Int, Char, Bool|8|724|
|3241|`game/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdateClientUpdate.cpp`|Bool, Int, UnsignedInt, Real|8|963|
|3242|`game/Libraries/Source/Compression/CompressionManager_decompressData.cpp`|Int, UnsignedByte, Bool|8|1058|
|3243|`game/GameEngine/Source/GameLogic/AI/AISkirmishPlayer.cpp`|Int, Bool|8|40|
|3244|`game/GameEngine/Source/GameClient/EvaReset.cpp`|Bool, Int|8|336|
|3245|`game/GameEngine/Source/Common/Open2Twins002.cpp`|Int, Bool|8|535|
|3246|`game/GameEngine/Source/GameLogic/AI/AIGroupBroadcastOrders.cpp`|Int, Bool|8|518|
|3247|`game/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva00648220PeerThreadStaleServerLookup.cpp`|Int, Bool, UnsignedInt, UnsignedShort|9|1273|
|3248|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsTriggerAreas.cpp`|Int, UnsignedInt, Bool, Real|9|1237|
|3249|`game/GameEngine/Source/GameLogic/AI/AICommandInterfaceAttackCommands.cpp`|Int, UnsignedInt, Real, Bool|9|1936|
|3250|`game/GameEngine/Source/Common/Gen_000cd680.cpp`|Int, Short|9|141|
|3251|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditionsPlayerMask.cpp`|Bool, UnsignedInt|9|1697|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
