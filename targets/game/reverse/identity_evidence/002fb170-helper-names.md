# 0x002FB170 doTeamUseCommandButtonOnNearestEnemy: TU-local helper names

The banked attempt (targets/game/reverse/attempts/0x002fb170.cpp) described the filter object the body
constructs inline with invented labels: a helper `construct`, and members `m_vptr` / `m_next` for the first two
words of a 24-byte value it copies. The landed source names them from what the bytes show instead:

* The object is a PartitionFilter subclass whose constructor (reached at 0x000C3DD0) copies two 24-byte
  values: KINDOFMASK_NONE and the caller's exclusion mask. It is therefore a kind-of filter, most likely Zero
  Hour's PartitionFilterAcceptByKindOf(mustBeSet, mustBeClear), but no caller or vtable proves the class, so it
  keeps the address-derived name Rva000C3DD0VptrZeroBlockObject.
* The 24-byte value is a flag mask (BitFlags-sized), not an object with a vtable or a linked list, so its words
  are m_dword00 / m_dword04 ..., not m_vptr / m_next. The old labels asserted a layout the body contradicts.

No retail identity is claimed or removed by these renames; they only drop unproven local labels.
