# Shared enum contracts, cohort 107

Each task replaces one private per-unit enum with its existing BFME1 definition.
Values used by the translation unit, primitive underlying type and four-byte
size are preserved. Extra or conflicting private enumerators are permitted only
when absent from masked active code outside their declaration; every such entry
is retained in the diagnostic proof and listed below. No active identifier is
renamed, no pin, alias or provider is rebound. This is source consistency, not
new authored function bytes or a demonstrated full-image/runtime improvement.

NameKeyType follows the native namekeygenerator shim; ObjectID/DrawableID the
native Common/game_type.h; UpdateSleepTime the native UpdateModule.h. Original
EA license and constants are retained. CommandSourceType uses the unchanged
native command_source_type.h: PLAYER/SCRIPT/AI have independent BFME1 evidence;
DOZER/default-switch retain documented Zero Hour provenance, not new target proof.

Read-only BFME2 donor0630f0ef47d0a818bb2e97583b43cfb1ecd35491 was reviewed:
NameKeyGeneratorLifetime.cpp carries the same NameKey constants; the BFME2
NameKeyGenerator.h and UpdateModule.h use forwards and distinct class contracts.
No donor address, layout or body is imported. Existing BFME1 source contracts
and independent matched native providers take precedence.

Every ordinary whole-object inventory is identical: code, data, relocations,
definitions, raw directives, weak externals and aliases. Paired private Z7
CodeView records prove primitive enum ABI, every member value, every other
original enum and all original complete class contracts. Real include tracing
and a fresh actual-header probe confirm the normal object uses this contract.
Debug probes themselves must reproduce ordinary runtime after normalizing only
section ordinals displaced by debug sections. Native byte, relocation and body
gates pass; shared headers also require the normal full dependency hook.
Scope excludes crash/leak/RAM,64-bit,multicore,FPS and game-start claims.

|Task|Enum|Consumer|Rows|Retained bytes|Unused private enumerators replaced|
|---|---|---|---:|---:|---|
|1079|ObjectID|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateExitObjectViaDoor.cpp`|4|1219|`{}`|
|1080|UpdateSleepTime|`game/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior_playerScan.cpp`|4|1529|`{}`|
|1081|NameKeyType|`game/GameEngine/Source/GameClient/MessageStream/CommandXlatVoice.cpp`|4|11631|`{"NAMEKEY_NONE": 0}`|
