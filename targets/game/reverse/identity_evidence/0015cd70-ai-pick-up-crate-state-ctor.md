# `AIPickUpCrateState::AIPickUpCrateState(StateMachine*)` at 0x0015CD70

* **Its vtable is AIPickUpCrateState's.** The body installs 0x010960D0. Slot 0 of
  that table reaches `??_GAIPickUpCrateState@@MAEPAXI@Z` (0x0015CDD0, through ILT
  0x00044599). Slot 2, the name slot 0x0015CDC0, returns "AIPickUpCrateState".
  Slot 4 is `?onEnter@AIPickUpCrateState@@` (0x0016C0A0), and slot 6 is
  `?update@AIPickUpCrateState@@` (0x00178E10), compiled from Zero Hour's
  AIStates.cpp.
* **Body.** It calls the AIInternalMoveToState base (0x0014F280) with the name
  "AIAttackPickUpCrateState", installs its vtable, and sets `m_delayCounter`
  (+0x50) to 0, with `ret 4`. AIStateMachine (state 0x27) inlines this exact
  sequence. So do AIAttackMoveStateMachine and AIAttackThenIdleStateMachine,
  whose Zero Hour source is `newInstance(AIPickUpCrateState)(this)`.
* **Previous rows.** `??0Rva0015CD70State@@QAE@PAX@Z`
  (StateSelfNamingCtorsWithFields.cpp) named no class. The AIPickUpCrateState
  name sat on 0x002C1150, which installs its own table 0x010C7D30 and is a
  subclass (see 002c1150-pickup-crate-subclass-ctor.md).
