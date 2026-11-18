# Scalar alias contracts: cohort 128

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
|2082|`game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdateUpdateBfme.cpp`|UnsignedInt, Int, Bool|1|347|
|2083|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doFireSpecialPowerOnNearestObjectTypeByPlayer.cpp`|Bool, Int, Real|1|382|
|2084|`game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollide_executeCrateBehavior.cpp`|Int, UnsignedInt, Real, Bool|1|381|
|2085|`game/GameEngine/Source/GameLogic/World/ParseObjectDataChunk_Thunk.cpp`|Bool, Int, Real|1|605|
|2086|`game/GameEngine/Source/GameClient/InGameUIRva00442FD0.cpp`|Int, Bool, Real|1|380|
|2087|`game/GameEngine/Source/GameClient/GUI/IMEManagerInit.cpp`|Bool, Int, UnsignedInt|1|581|
|2088|`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewCameraModFinalTimeMultiplierBfme.cpp`|Real, Int, Bool|1|261|
|2089|`game/GameEngine/Source/GameLogic/AI/AIAttackMeleeEngageState_onEnter.cpp`|Bool, Int, UnsignedInt|1|641|
|2090|`game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_doSetRefToNearestTeamOfTypeOwnedByPlayer.cpp`|Bool, Int, Real|1|369|
|2091|`game/GameEngine/Source/GameClient/InGameUI_canSelectedObjectsEffectivelyUseWeapon_Thunk.cpp`|Int, UnsignedInt, Bool|1|269|

Native origins: `game/GameEngine/Include/Precompiled/PreRTS.h` and
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h`.
The current BFME2 reference is reviewed as a lead only; its addresses and
build configuration are not imported. Local manifests retain hashes and
actual compiler arguments for every control, candidate and witness.
