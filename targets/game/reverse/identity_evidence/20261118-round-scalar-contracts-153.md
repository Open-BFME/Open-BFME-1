# Scalar alias contracts: cohort 153

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
|3252|`game/GameEngine/Source/Common/GlobalDataConstructor.cpp`|Real, Int, UnsignedInt, UnsignedByte, UnsignedShort, Bool|10|4821|
|3253|`game/GameEngine/Source/GameNetwork/LANGameInfoBodies.cpp`|Int, UnsignedInt, UnsignedShort, UnsignedByte, Bool|10|817|
|3254|`game/GameEngine/Source/Common/System/DataChunkInput.cpp`|Int, UnsignedInt, UnsignedShort, Bool|10|1640|
|3255|`game/GameEngine/Source/Common/Recorder.cpp`|Int, UnsignedInt, UnsignedByte|10|911|
|3256|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsNamedTeam.cpp`|Bool, Int, Real|10|702|
|3257|`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenGrabMultiPlayerInfo.cpp`|Int, Bool|10|956|
|3258|`game/GameEngine/Source/GameLogic/Map/TerrainLogicRva001A8170BeaconPathPoint.cpp`|Bool, Real|10|1396|
|3259|`game/GameEngine/Source/Common/MultiPlayMultParseCallbacks.cpp`|Int, Real|10|1763|
|3260|`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarContextUI.cpp`|Int, UnsignedInt, Real, Bool|11|1990|
|3261|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionsCounters.cpp`|Bool, Int, UnsignedInt|11|1322|
|3262|`game/GameEngine/Source/GameClient/InGameUIBodies.cpp`|Int, UnsignedInt, Bool|11|1905|
|3263|`game/GameEngine/Source/Common/Rva0039D020False.cpp`|Bool|1|3|
|3264|`game/GameEngine/Source/Common/Rva0045C060NoOp.cpp`|Int|1|3|
|3265|`game/GameEngine/Source/GameClient/Terrain/TerrainRoadTypeGetRoadWidth.cpp`|Real|1|4|
|3266|`game/GameEngine/Source/Common/Rva00260980False.cpp`|Bool|1|3|
|3267|`game/GameEngine/Source/Common/Rva0068DB60Field04.cpp`|UnsignedInt|1|4|
|3268|`game/GameEngine/Source/Common/Rva006E7140RealGetter.cpp`|Real|1|4|
|3269|`game/GameEngine/Source/GameLogic/Object/Rva001BE7A0ObjectStatus.cpp`|Bool|1|36|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
