# 0x001F0960 BezierProjectileBehavior::update: filter and result type names

The banked attempt for 0x001F0960 used invented names for the three
partition-query temporaries and the owning result (ProjectileObjectFilter,
ProjectileOwnerFilter, BfmeWideResult), built with raw vtable stores.

Retail builds the query exactly as the matched
`game/GameEngine/Source/GameLogic/Object/Body/Rva002113A0NearbyObjects.cpp`
(0x002113A0) does:

- The filter at `[esp+0x40]` gets vtable 0x01085DD0 and stores the owning
  Object. The retail image and the matched TUs name that vtable
  `??_7Rva0025ED50ObjectFilter@@6B@`.
- The filter at `[esp+0x18]` gets vtable 0x01083B80, named
  `??_7Rva0025ED50RootFilter@@6B@`.
- The third filter is built by the out-of-line constructor at 0x000EC770,
  now matched as `??0PartitionFilterRelationship@@QAE@PBVObject@@H_N@Z`
  (commit 35d1750f02).
- `PartitionManager::iterate` at 0x009F2960 returns the same 4-byte owning
  result that the matched TUs model as `Rva0025ED50WideResult`. It is released
  through 0x000C5FC0.

The rewrite reuses those matched class names instead of inventing new ones.
The `__declspec` pairing that the name-regression checker reports is a false
match: that token was an attribute on the old fake constructors, not a type.
