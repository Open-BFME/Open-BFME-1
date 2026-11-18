# Scalar alias contracts: cohort 151

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
|3225|`game/GameEngine/Source/Common/RTS/TeamMemberQueries.cpp`|Bool, Real|6|1106|
|3226|`game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorOnHealing.cpp`|Real, UnsignedInt|6|1429|
|3227|`game/Libraries/Source/Compression/LZHCompress/NoxCompress.cpp`|Int, UnsignedInt, UnsignedByte, Bool|7|1193|
|3228|`game/GameEngine/Source/GameLogic/System/BfmeCellGrid.cpp`|Int, UnsignedInt, Real|7|1027|
|3229|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva007739F0ModelVariant.cpp`|Bool, Int, UnsignedInt|7|1718|
|3230|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerMessageBox.cpp`|Int, Bool, UnsignedInt, UnsignedShort|7|1741|
|3231|`game/GameEngine/Source/GameLogic/Map/TerrainLogicNameLookups.cpp`|Bool, Int, Real|7|1873|
|3232|`game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoAddGroupRoomThunk.cpp`|Bool, Int|7|1420|
|3233|`game/GameEngine/Source/Common/BitFlagsParseToken.cpp`|Int, Bool|7|2925|
|3234|`game/GameEngine/Source/Common/RTS/TeamTriggerAreaTests.cpp`|Bool, Int, UnsignedInt|7|1757|
|3235|`game/GameEngine/Source/Common/RTS/TeamPrototypeInstanceWalks.cpp`|UnsignedInt, UnsignedShort, UnsignedByte, Bool, Int, Real|8|905|
|3236|`game/GameEngine/Source/GameNetwork/NetPacketCommandBodies.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|8|3068|
|3237|`game/GameEngine/Source/Common/SmallIniParseCallbacks.cpp`|Int, UnsignedInt, Real, Bool|8|336|
|3238|`game/GameEngine/Source/GameNetwork/LANAPISendPath.cpp`|Int, Bool, UnsignedInt, UnsignedByte|8|1340|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
