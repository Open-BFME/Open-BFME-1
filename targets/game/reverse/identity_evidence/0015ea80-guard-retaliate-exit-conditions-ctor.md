# `GuardRetaliateExitConditions::GuardRetaliateExitConditions()` at 0x0015EA80

* **Body.** It installs vtable 0x01096518, then zeroes +4, +0x14, +0x18, +8, +0xC
  and +0x10, and returns `this`. It is 29 bytes long.
* **Whose vtable.** Slot 0 of 0x01096518 is 0x0015EAB0,
  `?shouldExit@GuardRetaliateExitConditions@@`. Only one state constructor
  installs this table on its exit-conditions member (+0x24): 0x0015F070, which
  names itself "AIGuardRetaliateAttackAggressorState". In Zero Hour that class
  holds a `GuardRetaliateExitConditions m_exitConditions`.
* **The sibling.** 0x0015BEB0 has the same 29 bytes but installs 0x01096084.
  Slot 0 of that table is `?shouldExit@ExitConditions@@` (0x0015BF80), and
  AIGuardInner/Outer/AttackAggressorState install it at +0x24. That body is
  `ExitConditions::ExitConditions()`, so this name moves off it.
* **Previous row.** `??0Rva0015EA80@@QAE@XZ` (R3ScalarFieldConstructors2.cpp)
  named no class.
