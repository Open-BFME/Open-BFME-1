# Recharge provider: preserve the existing reload-time getter independently

Queue60 claim F17DE657; dependent existing getter claim000CD590. The214-byte
SpecialPowerModule::startPowerRecharge at00268BA0 already has its independent
identity/swap evidence and exact provider in SpecialPowerModule_startPowerRecharge.cpp.
SpecialPowerModule.cpp still supplied a wrong Zero Hour definition without
BFME's owner attribute multiplier. Remove only this obsolete definition.

Previous removal was restored when it stopped emitting the sole ledger-owner
copy of SpecialPowerTemplate::getReloadTime. A second existing retail copy
already exists in Player_resetOrStartSpecialPowerReadyFrame.cpp, where the
native ready-frame timer calculation uses it. Its existing header-derived
body is27 bytes at000CD590 and calls the same override walker through
ILT00048C61. Claim and repoint this unchanged getter with add_match.py
--replace-existing; the tool independently verifies the new provider2/2.
No new body, class, layout, name, pin, compiler flag or header is introduced.

Normal combined gate verifies15/15 rows across the existing Player provider,
old module and exact recharge provider;15 DIR32 references,1 literal and2
float constants pass. COFF confirms: old module only references recharge,
split provider defines recharge and references getReloadTime, Player provider
defines getReloadTime. Both shared-header users still use the established
local Zero Hour SpecialPower header and their original flags; no donor include
path is part of either build.

Source removal renumbers5 existing cleanup labels. eh_state_pins.py --fix
reconciles the one independently anchored getModuleNameKey cleanup. Four
other pre-existing parent bodies are unanchored; the tool leaves those
ledger rows unchanged, and the normal gate verifies their current byte bodies
through its existing renumbered-label handling. This repair does not claim
new unwind-state identity evidence for those4 rows or weaken a check.

Donor reviewed a9286edec5374324e40c1f5dd29c3a8ab5582283:
Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp
and Code/GameEngine/Include/Common/SpecialPower.h. Their reference getter/
recharge relationship is a lead; BFME1's attribute scaling and27-byte getter
remain target facts. The reviewed paths have no delta through the externally
advanced tracked donorf6d845ecd439374ef476ce04c992a2b848eb2c99. No donor
code/addresses/layouts/flags or cached compile trial is imported or changed.

Before census-only link_check: wrong selected/duplicate recharge provider.
After current-object preview: selection unknown against stale Oct19 census;
no newly recovered or linked bytes are claimed. Related recharge near-twin
at0026AE00 has its separate already-correct address-derived identity and
provider; it is not changed by this base-provider repair.
