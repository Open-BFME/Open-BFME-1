# 0x00180320 constructs AIFaceState, not AIIdleState

* **Its vtable is AIFaceState's.** The body installs 0x0109AD20. That table's name
  slot (0x00180390) returns "AIFaceState". Its update slot, slot 6, is
  `?update@AIFaceState@@` at 0x00189660, which reads +0x28 and +0x2C.
  AIIdleState's table is 0x010985B0: its name slot (0x00172140) returns
  "AIIdleState", slot 6 is `?update@AIIdleState@@` (0x00188090), and slot 7
  returns true.
* **AIStateMachine agrees.** `??0AIStateMachine` (0x00185A20) is Zero Hour's
  `defineState` list. It builds state 0 (AI_IDLE) as `new(0x28)` on 0x010985B0,
  with shouldLookForTargets 1. It builds states 0x24, 0x25 and 0x3B as `new(0x30)`
  on 0x0109AD20 with +0x28 = 1, 0 and 2. Those are Zero Hour's face-object and
  face-position states, `newInstance(AIFaceState)(this, true/false)`, plus one
  BFME addition. AIStateMachineConstructor.cpp already resolves ??_7AIIdleState to
  0x010985B0 and ??_7AIFaceState to 0x0109AD20.
* **Body.** It takes two arguments (`ret 8`). It builds the "AIIdleState" State
  base with AIIdleState's LOOK_FOR_TARGETS stores (+0x24 = 0xFFFF, +0x26 = 1,
  +0x27 = 0), then stores +0x28 = arg 2 as a dword and +0x2C = 0.
* **Why the name is opaque.** Zero Hour's second parameter is a `Bool`. Here it is
  a dword with three values, and its type cannot be read from the bytes.
* AIIdleState's own constructor is 0x001720D0 (see 001720d0-ai-idle-state-ctor.md).
