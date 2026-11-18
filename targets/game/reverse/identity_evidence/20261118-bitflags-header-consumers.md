# Seventeen BitFlags consumer reconciliations

Tasks584-600 replace data-bearing per-unit BitFlags views with one explicit,
standalone Common/BitFlags/BitFlags.h. Its unique path does not shadow the
vendor Common/BitFlags.h. No caller field, actual template argument, pin, alias,
provider ownership or runtime definition is rebound. No new authored function
bytes, full-image gain, crash/leak/RAM,64-bit,multicore,FPS or runtime claim.

## Evidence and provenance

EA GeneralsMD Common/BitFlags.h supplies the existing wrapper operations and
declarations. The local header uses primitive int/bool spellings, the original
int template-argument convention, and narrow bitset/string prerequisites.
Existing native I/O providers retain their own bodies; buildDescription stays
a declaration instead of importing a concrete AsciiString implementation. The
original debug assertion is retained under its existing NDEBUG condition.

Independent BFME1 matched providers include BitFlags304TestForAll (ten copied
words and the exact304-bit top-word sanitization),192TestSetAndClear,86Xfer,
304 constructor variants and192UpgradeCtor. The combined native gate includes
those actual providers. The native class_contract template query supplies zero
views and is recorded as a tool limitation, not accepted as an ABI proof.

The compiler provides complete paired BitFlags<N> and nested _STL::bitset<N>
CodeView records. Both retain one m_bits at+0, the same instantiation and total
size4*ceil(N/32), no bases or virtual state. A zero field-width returned by the
generic parser is not treated as an extent: the complete nested record supplies
and independently verifies it. Every other original complete class contract is
unchanged. Existing320 arguments are retained as source contracts; no new
retail320-bit semantic identity is claimed. Added static/member declarations
emit no new definition or storage in these consumers.

Read-only BFME2 revision0630f0ef47d0a818bb2e97583b43cfb1ecd35491 was reviewed:
ObjectFilter.h has int-argument BitFlags forwards and distinct218-bit usage;
Common/BitFlags304GetSingleBitFromName.cpp and116TestSetAndClear.cpp provide
related wrapper context. Their counts,addresses and bodies are not imported.

## Verification

Every complete ordinary before/after runtime inventory is identical, including
raw directives,definitions,code,data,relocations,weak externals and aliases.
Real include tracing proves the new BFME1 header is used. The actual Z7 type
probe has the same runtime inventory as the ordinary object after normalizing
only section ordinals shifted by inserted .debug sections. Deliberate code,
data and relocation-target mutations are all rejected by that comparison.
The one missing debug-include context uses the normal compiler search roots,
recorded explicitly with actual include tracing; no substitute header is used.
Native provider/consumer gate:28/28 functions across23 sources,
78 DIR32 references,zero baseline findings. Current pinned configurations
are verified; broad debug-build or full-image parity is not inferred. The
required normal shared-header commit/push gate remains authoritative.

|Task|Consumer|Retained rows|Retained bytes|
|---|---|---:|---:|
|584|`game/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdateModuleDataConstructor.cpp`|1|164|
|585|`game/GameEngine/Source/GameClient/FXNuggetConstructor.cpp`|1|225|
|586|`game/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdateModuleDataCtorThunk.cpp`|1|250|
|587|`game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain_addValidObjectsToGarrisonPoints.cpp`|1|489|
|588|`game/GameEngine/Source/GameLogic/Object/SpecialPower/TaintSpecialPowerAfter.cpp`|1|1109|
|589|`game/GameEngine/Source/GameLogic/AI/Rva002491F0.cpp`|1|75|
|590|`game/GameEngine/Source/GameLogic/Object/Update/ToppleUpdateApplyTopplingForce.cpp`|1|832|
|591|`game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdateQueryRallyOverride.cpp`|1|429|
|592|`game/GameEngine/Source/GameLogic/Object/Update/BfmeTargetXIUseXI.cpp`|1|427|
|593|`game/GameEngine/Source/GameLogic/AI/AIAttackSquadStateChooseVictim.cpp`|1|949|
|594|`game/GameEngine/Source/GameLogic/Object/ObjectClearModelConditionFlags.cpp`|1|64|
|595|`game/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehaviorCreateSpawn.cpp`|2|785|
|596|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_createSpecialObject.cpp`|1|232|
|597|`game/GameEngine/Source/GameLogic/Object/Upgrade/BaseUpgradeUpgradeImplementation.cpp`|2|600|
|598|`game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_endPreparation.cpp`|1|225|
|599|`game/GameEngine/Source/GameLogic/AI/Rva0024BB60.cpp`|1|90|
|600|`game/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetState_onEnter_Bfme.cpp`|1|523|
