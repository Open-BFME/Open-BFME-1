# 0x00238680's distance call is the matched Gen_000ED3B0::bfmeGapSq

`Rva00238680Receiver::rva00238680` (0x00238680, 146 B,
Rva00238680Receiver.cpp) called `Object::getDistanceSquared(const Object *)
const`, a symbols.csv pin on ILT 0x00043CED that no source defines (link
census: unresolved, pinned-elsewhere).

- `tools/callees.py 0x00238680 146`: `0x43ced -> 0xed3b0`.
- 0x000ED3B0 is matched as `?bfmeGapSq@Gen_000ED3B0@@QBEMPBV1@@Z`
  (Bfme5NinetyEight.cpp): const thiscall, one pointer argument, float result
  (planar distance between +0x38/+0x3C minus both +0xBC radii, clamped at 0,
  squared). The old declaration had the same ABI, so the call site's bytes
  are unchanged (1/1).
- `tools/ilt_oracle.py check '?getDistanceSquared@Object@@QBEMPBV1@@Z'
  0x000ED3B0`: CONTRADICTED (outside every window of slots
  54728:32172-32177), so the pin name is not this body's decoration.
- Matched SpecialAbilityUpdate_isWithinStartAbilityRange.cpp and
  GettingBuiltBehaviorCompletion.cpp already call this body by casting their
  objects to `Gen_000ED3B0`; this caller now does the same.

The receiver is still an Object in meaning; only the cast at the call names
the defining view class, as the other callers do.
