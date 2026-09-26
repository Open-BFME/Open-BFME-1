# 0x0024F280: state-gated aiMoveToObject iterate callback

Retail 0x0024F280..0x0024F2BF (64 bytes, int3-carved, `ret` with no
immediate). Now landed as `?Rva0024F280@@YAXPAVObject@@PAX@Z` in
`game/GameEngine/Source/GameLogic/AI/Rva0024F280StateGatedMoveCallback.cpp`.

## What the bytes prove

- Two `__cdecl` stack arguments: `[esp+4]` (null-checked, dereferenced at
  +0x204) and `[esp+8]` (pushed unchanged as the callee's first argument).
  No value is left in `eax` for the caller: the function returns `void`.
- `[esp+4]+0x204` is `Object::m_ai` and `m_ai+0x30` is
  `AIUpdateInterface::m_stateMachine`, the layout already witnessed by the
  matched `W3DWaypointBuffer::drawWaypoints` (0x00746A30).
- `m_stateMachine+0x1C` null-tested, else `+0x04`, else `999999`: ZH's inline
  `StateMachine::getCurrentStateID()` (`m_currentState ? m_currentState->getID()
  : INVALID_STATE_ID`, `INVALID_STATE_ID = 999999`). Written that way it
  byte-matches; written as an opaque "kind" lookup it does not (the compiler
  threads the constant, 57 of 64 bytes).
- The call is `ecx = m_ai + 0x20; push 2; push [esp+8]` to ILT 0x0001C26A,
  pinned `AICommandInterface::aiMoveToObject(Object *, CommandSourceType)` by
  the matched `QueueProductionExitUpdate::releaseLastExit` (0x002D0D10);
  `2` is `CMD_FROM_AI`.
- The only reference is the function-pointer operand in `bfmeNotifyYT`
  (0x0024F2D0), which passes it with a `void *` parameter to two container
  visits: the ZH `iterateContained(func, userData, ...)` callback shape.

## What that refutes

- `bfmeFilterYT` / `?bfmeFilterYT@@YADPAX@Z` (the caller's TU-local pin):
  declares `char __cdecl (void *)`, one argument and a `char` result. Retail
  reads two arguments and returns nothing, and nothing in it filters.
- `notifyUnlessKind` (the banked 0.9 attempt): the tested value is an AI
  state-machine state id, not a kind, and the call is a move-to-object AI
  command, not a notification.

Neither name came from a matched caller or a string; both were placeholders
chosen by earlier sessions. The callback's own name and owning TU remain
unknown, so the body keeps the address-derived `Rva0024F280`. State ids 0x38
and 0x0F are left numeric: BFME's AIStateType numbering is not witnessed.
