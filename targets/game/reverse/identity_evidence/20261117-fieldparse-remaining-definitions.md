# Final four local FieldParse definitions

Tasks578-581 remove the remaining complete game-source descriptor definitions
discovered in the current tree after the28-source foundation and two explicit
consumer fixes. These four translation units use the same canonical standalone
Common/FieldParse.h. No function, provider, alias, datum or pin is added or removed.

## Evidence and bounded change

BFME1 matched128B lookup00850880 reads token+0, callback+4, userData+8 and
offset+12 in16B strides; the matched728B dispatcher00851910 invokes the
callback with four pointer words. Existing local INI shims supply the same
definition and inline set method. Read-only BFME2 reference0630f0ef47d0a818bb2e97583b43cfb1ecd35491
was consulted for context; no donor body, address or ABI is adopted.

The former full INI header context failed compilation in three consumers.
The new standalone descriptor supplies only the needed descriptor contract;
those are new include-context hypotheses, with complete before/after proofs.
The W3D model-condition parser was absent from the old source inventory and
was discovered by a fresh current-tree definition sweep.

Retain the original unsigned/int offset bit width, constant values and runtime
operations. The canonical offset spelling is int32; the physical four slots
remain4B each. No calling declaration or table target is remapped. The Q4
callbacks retain their original two-argument source declarations and their
existing table casts: no arity or semantic identity is inferred for them.

## Verification

Each source passes a fresh private control/candidate compile, complete ordinary
runtime inventory identity including raw directives, weak/alias equality, and
a real-header include trace. All other original complete CodeView contracts
are identical. Canonical descriptor role reconciliation is explicit.
Native providers and consumers pass117/117 rows across7 sources
with116 DIR32 references. The three parser-provider units are included.
No shared header changes in this cohort. Normal publication and a separate
full current-source link census establish different properties; this cleanup
does not claim new function bytes, crash/leak/RAM fixes,64-bit,FPS or game start.

| Task | Consumer | Retained rows | Retained bytes |
|---|---|---|---|
|578|`game/GameEngine/Source/GameClient/GUI/GameWindowTransitionsHandler.cpp`|4|981|
|579|`game/GameEngine/Source/GameLogic/LivingWorld/INILivingWorldAnimObject.cpp`|10|609|
|580|`game/GameEngine/Source/Common/Q4IniMultiFieldParse.cpp`|11|1056|
|581|`game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/Rva0077C390Parse.cpp`|1|588|
