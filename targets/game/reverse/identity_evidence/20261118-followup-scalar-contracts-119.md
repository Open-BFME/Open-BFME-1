# Scalar alias contracts: cohort 119

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
|1582|`game/GameEngine/Source/GameNetwork/NetGameCommandMsg_constructGameMessage.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool, Real|1|467|
|1583|`game/GameEngine/Source/GameClient/GUI/GameWindowManagerMouseEvent.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Real, Bool|1|1569|
|1584|`game/GameEngine/Source/GameNetwork/NetPacket_isRoomForGameSpyStatsAuthKeyMessage.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|250|
|1585|`game/GameEngine/Source/GameLogic/System/BfmeCellGridXfer.cpp`|Bool, Int, UnsignedInt, Real, UnsignedByte|1|530|
|1586|`game/GameEngine/Source/Common/RTS/ScoreKeeperXfer.cpp`|Int, Bool, UnsignedByte, UnsignedShort, UnsignedInt|1|517|
|1587|`game/GameEngine/Source/GameNetwork/LANAPIConstructor.cpp`|UnsignedInt, UnsignedShort, UnsignedByte, Int, Bool|1|242|
|1588|`game/GameEngine/Source/GameNetwork/LANAPIRequestEnableMPSetupUI.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|1|166|
|1589|`game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapRva0074B480.cpp`|Int, UnsignedInt, UnsignedByte, Real, Bool|1|1179|
|1590|`game/GameEngine/Source/Common/RTS/TeamFactory_xfer.cpp`|Bool, Int, UnsignedInt, UnsignedShort, UnsignedByte|1|351|
|1591|`game/GameEngine/Source/Common/RTS/TunnelTracker_xfer.cpp`|UnsignedByte, UnsignedInt, Int, UnsignedShort, Bool|1|248|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
