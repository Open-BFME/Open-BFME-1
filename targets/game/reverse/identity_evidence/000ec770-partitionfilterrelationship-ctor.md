# 0x000EC770 is PartitionFilterRelationship::PartitionFilterRelationship(const Object*, Int, Bool)

Retail body: 39 bytes, `thiscall`, `ret 0xC` (three stack arguments), returns
`this` in EAX. It stores argument 1 at +0x8, writes 0 at +0x4, installs the
vtable literal 0x01085DC0 at +0x0, stores argument 2 at +0xC and the low byte
of argument 3 at +0x10.

- 0x01085DC0 is `??_7PartitionFilterRelationship@@6B@` in
  `targets/game/reverse/dir32_addresses.csv`, so the object being constructed
  is a `PartitionFilterRelationship`.
- +0x4 = 0 is `PartitionFilter::m_next`, the base-class link every matched
  filter TU declares (`ScriptConditionsTeamSighted_Rva00328020.cpp`,
  `ObjectCountNearbyEnemies.cpp`).
- Zero Hour declares `PartitionFilterRelationship(const Object *obj, Int
  flags)` with members `m_obj`, `m_flags`; BFME adds a trailing Bool at +0x10.
  A vtable install plus base-link zeroing plus member stores that returns
  `this` is a constructor, not a `set` method.
- Callers reach it through ILT 0x0000F4B1 to build full-expression filter
  temporaries; the blocked verdict on DumbProjectileBehavior::update
  (0x001F0960) names this call site.

The previous row name `?set@Rva000EC770@@QAEAAV1@HHD@Z` (in
`Rva000EC770Set.cpp`, a raw-vtable-literal placeholder TU) described the byte
shape, not an identity. That TU owned only this row and is deleted with this
landing. Compiled from real C++ (base + derived classes, inlined base
constructor) the body is byte-exact at `/O2`.
