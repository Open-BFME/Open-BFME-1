# 0x002C1150 constructs a subclass of AIPickUpCrateState, not the class itself

* **Its vtable is not AIPickUpCrateState's.** The body installs 0x010C7D30.
  AIPickUpCrateState's table is 0x010960D0: its slot 0 is
  `??_GAIPickUpCrateState` (0x0015CDD0), slot 4 is
  `?onEnter@AIPickUpCrateState@@` (0x0016C0A0), and slot 6 is
  `?update@AIPickUpCrateState@@` (0x00178E10, Zero Hour's AIStates.cpp code).
  AIStateMachine (state 0x27), AIAttackMoveStateMachine and
  AIAttackThenIdleStateMachine all inline `newInstance(AIPickUpCrateState)` on
  0x010960D0.
* **What 0x010C7D30 is.** It shares slots 1-3 and 7-17 with 0x010960D0. That
  includes the name slot 0x0015CDC0, which returns "AIPickUpCrateState".
  It has its own deleting destructor at slot 0 (0x002C11A0) and its own slots 4,
  5 and 6 (0x002BC050, 0x002BC0A0 and 0x002BC090). Nothing else installs it.
* **Body.** It makes the same base call with the same "AIAttackPickUpCrateState"
  name and the same `+0x50 = 0` as AIPickUpCrateState's constructor, 0x0015CD70.
  It stores that member *before* its vtable, the order of a derived class after
  its base constructor was inlined. 0x0015CD70 installs its vtable first.
* **Placement.** It sits among the GiantBird states: 0x002C11E0 is
  GiantBirdGuardAttackAggressorState's constructor, and 0x002C1260 builds a
  GiantBird state machine. The class name is not recovered, so it keeps the
  address.
