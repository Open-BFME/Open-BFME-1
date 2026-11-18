# 0x00131B20 Thing::isSignificantlyAboveTerrain

Previously `?bfmeCheckRW@BfmeOwnerRW@@QAEHXZ` (placeholder, BfmeConv1807.cpp).
Now `?isSignificantlyAboveTerrain@Thing@@QBE_NXZ` in
game/GameEngine/Source/Common/Thing/Thing_isSignificantlyAboveTerrain.cpp.

BFME 1 target evidence:
- ILT 0x00019FF1 -> 0x00131B20. `tools/ilt_oracle.py check` gives
  `?isSignificantlyAboveTerrain@Thing@@QBE_NXZ` CONFIRMED (exact, p_false
  6.5e-4) and both `?bfmeCheckRW@BfmeOwnerRW@@QAEHXZ` and
  `?isSignificantlyAboveTerrain@Object@@QBE_NXZ` CONTRADICTED.
- symbols.csv already pinned the Thing name at the ILT ("pristine EA
  setGoalPositionClipped call and retail AI/Drawable callers").
- Body: if `(this+0x5C & 2) == 0`, store the slot-0 virtual's float result at
  +0x54 and set bit 2, then compare `TheWritableGlobalData->+0x1AC * c` with
  +0x54 and return 0/1. name_oracle reads Thing+0x54 as
  m_cachedAltitudeAboveTerrain and +0x5C as m_cacheFlags (layout witnesses),
  and Thing::calculateHeightAboveTerrain is the protected virtual
  (?calculateHeightAboveTerrain@Thing@@MBEMXZ, 0x00132470).

Zero Hour reference: GeneralsMD Thing.cpp
`return (getHeightAboveTerrain() > -(3*3)*TheGlobalData->m_gravity);` with
getHeightAboveTerrain's cache inlined. BFME scales gravity by its own constant
at 0x01090DDC.

Link-queue row #35 (census 6c4dd9e650): W3DModelDrawTransformChange.cpp's call
was satisfied by Thing.cpp's non-retail Zero Hour copy, which is now under
#if 0.
