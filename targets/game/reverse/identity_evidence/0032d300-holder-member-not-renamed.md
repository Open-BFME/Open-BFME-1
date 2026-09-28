# 0x0032D300 skirmish-supplies condition: `m_object -> m_value` is not a rename

name_regression paired the bank `targets/game/reverse/attempts/0x0032d300.cpp`
with the landed `ScriptConditionsSkirmishSupplies.cpp` and reported the
+0x00 member `m_object -> m_value`. The two names belong to different
classes that do not correspond:

- Bank: `MemoryPoolObjectHolder::m_object`. This was the Zero Hour holder
  around a `SimpleObjectIterator *`. Even as that class the name was not
  the witnessed one: Zero Hour's `GameMemory.h:785` spells the member
  `m_mpo`, and `name_oracle.py --class MemoryPoolObjectHolder --offset 0`
  has no BFME witness, only that ZH hint.
- Landed: `BfmeWideResult::m_value`, the refcounted range-query result
  that BFME's partition query at 0x009F2960 returns by value (payload:
  vector of 8-byte entries, cursor +0x0C, references +0x10). The retail
  body releases that payload by decrementing +0x10. It does not call a
  MemoryPoolObject `deleteInstance`, so the ZH holder does not describe
  this body. `name_oracle.py --class BfmeWideResult --offset 0` has no
  witness. The other landed users of the same ABI
  (`ObjectCountNearbyEnemies.cpp`, `DelayedLuaEventUpdate.cpp`,
  `ObjectBroadcastEventTo*.cpp`) call the member `value`, and
  `m_value` is the same opaque spelling.

The holder class was replaced by the correct ABI, not renamed, so no
evidenced name was lost.
