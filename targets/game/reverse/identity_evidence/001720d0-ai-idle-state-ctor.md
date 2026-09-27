# `AIIdleState::AIIdleState(StateMachine*, AIIdleTargetingType)` at 0x001720D0

* **Its vtable is AIIdleState's.** The body installs 0x010985B0. That table's name
  slot (0x00172140) returns "AIIdleState". Slot 6 is `?update@AIIdleState@@` at
  0x00188090, and slot 7 (0x00172130) returns true, Zero Hour's `isIdle()`.
* **Body.** It is Zero Hour's AIIdleState constructor (AIStates.cpp) as written:
  `State(machine, "AIIdleState")`, `m_shouldLookForTargets = (arg ==
  LOOK_FOR_TARGETS)` (`sete`), `m_inited = FALSE`, `m_initialSleepOffset = -1`.
  It takes two arguments and the object is 0x28 bytes.
* **Callers agree.** AIStateMachine's state 0 (AI_IDLE) inlines it with
  LOOK_FOR_TARGETS. AIAttackMoveStateMachine and AIAttackThenIdleStateMachine
  inline it with DO_NOT_LOOK_FOR_TARGETS; both are
  `newInstance(AIIdleState)(this, DO_NOT_LOOK_FOR_TARGETS)` in Zero Hour.
  AIAttackSwoopThenIdleStateMachine (0x002BF480) calls this body through ILT
  0x000241A4 with (this, 1) for its state 0.
* **Placement.** It sits just before AIIdleState's other bodies: 0x00172130
  (isIdle), 0x00172140 (name), 0x00172150 (deleting destructor) and 0x00172180
  (`?doInitIdleState@AIIdleState@@`).
* **Previous rows.** `??0Rva001720D0AIIdleLikeState@@QAE@PAXH@Z` held this body
  under an address-derived name, because the AIIdleState name sat on 0x00180320.
  That body is AIFaceState's (see 00180320-face-state-ctor.md).
