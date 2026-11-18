# Scalar alias contracts: cohort 150

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
|3207|`game/GameEngine/Source/GameLogic/Object/Contain/ContestableContain.cpp`|Bool, UnsignedInt|5|735|
|3208|`game/GameEngine/Source/GameLogic/Object/ObjectTeamAndPlayer.cpp`|Bool, UnsignedInt|5|306|
|3209|`game/GameEngine/Source/GameLogic/Object/ObjectUpgrades.cpp`|Bool, UnsignedInt|5|558|
|3210|`game/Libraries/Source/WWVegas/WW3D2/DX8Wrapper_DrawPrimitives.cpp`|UnsignedShort, UnsignedInt|5|1950|
|3211|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_appendMessage.cpp`|Int, Bool|5|2682|
|3212|`game/GameEngine/Source/GameNetwork/NetPacket_isRoomForDisconnectFamily.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|6|754|
|3213|`game/GameEngine/Source/GameNetwork/NetPacket_addRequestPlayerLeaveFamily.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|6|1874|
|3214|`game/GameEngine/Source/Common/Audio/AudioSettingsCtorThunk.cpp`|Real, Int, UnsignedInt, Bool|6|777|
|3215|`game/GameEngine/Source/GameNetwork/NetPacket_commandSizes.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte|6|386|
|3216|`game/GameEngine/Source/GameNetwork/LANAPILocalAddress.cpp`|Int, UnsignedInt, UnsignedShort, Bool|6|879|
|3217|`game/GameEngine/Source/GameLogic/Object/ObjectContainQueries.cpp`|Int, Bool, Real|6|324|
|3218|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDrawDestructor.cpp`|UnsignedInt, Bool, Real|6|172|
|3219|`game/GameEngine/Source/GameLogic/Object/ObjectDamageAndWeapons.cpp`|Int, Bool, UnsignedInt|6|436|
|3220|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsCamera.cpp`|Int, Bool, Real|6|1078|
|3221|`game/GameEngine/Source/Common/System/DataChunkOutput.cpp`|Int, UnsignedShort|6|617|
|3222|`game/GameEngine/Source/Common/RTS/TeamFactoryCreate.cpp`|UnsignedByte, UnsignedInt|6|601|
|3223|`game/GameEngine/Source/Common/Open2BitFlagsParse.cpp`|Int, Bool|6|996|
|3224|`game/GameEngine/Source/GameLogic/Object/ObjectGeometry.cpp`|Bool, Real|6|467|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
