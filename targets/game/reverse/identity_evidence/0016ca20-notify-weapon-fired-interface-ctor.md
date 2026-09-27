# `NotifyWeaponFiredInterface::NotifyWeaponFiredInterface()` at 0x0016CA20

* **Body.** `mov eax,ecx / mov dword ptr [eax],0x010976E0 / ret`: a no-argument
  constructor whose only work is installing vtable 0x010976E0.
* **Whose vtable.** 0x010976E0 holds five slots, all `_purecall`, which is Zero
  Hour's NotifyWeaponFiredInterface (five pure virtuals, no destructor). The two
  classes that derive from it install it on their interface subobject before
  overwriting it with their own: `AIAttackState::AIAttackState` (0x0017C910) at
  `[esi+0x24]` right after the State base, then 0x0109A0B0; `TurretAI::TurretAI`
  (0x0018DED0) at `[esi+4]`, then 0x0109BBDC.
* **Only candidate.** No other retail body of constructor shape stores 0x010976E0.
* **Previous rows.** `??0Rva0016CA20@@QAE@XZ` (TinyVfptrCtors.cpp) named no class.
  The name used to sit on 0x00061D90, where retail stores a literal zero
  (`mov dword ptr [eax],0`), not a vtable. The DIR32 mask hid that difference.
