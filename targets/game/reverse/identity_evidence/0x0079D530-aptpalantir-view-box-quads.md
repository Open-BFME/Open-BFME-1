# 0x0079D530: AptPalantir method (radar view-box inset quads), name unproven

Retail body 0x0079D530..0x0079D8F0 (961 bytes).

## Owning class: AptPalantir

- Its only caller is 0x0079DEE0. That function copies `this` into ebp at entry
  (`mov ebp, ecx`) and later does `mov ecx, ebp; call 0x0040CA45`. ILT
  0x0000CA45 is `jmp 0x0079D530`, so `this` reaches this body unadjusted.
- 0x0079DEE0 sits in slot 10 (+0x28) of vtable 0x01127A48, reached through ILT
  0x000392D4. The matched AptPalantir constructor (0x0079D9F0) installs that
  vtable: its immediate operand 0x01127A48 is at 0x0079DA26. The matched
  callback `aptPalantirRenderRadarViewBox` (0x00563C40) calls slot 10 of
  `TheAptPalantir`, so 0x0079DEE0 is `AptPalantir::renderRadarViewBox`.
- This body reads +0x51C (the RadarViewBoxEdge `Image *` that the constructor
  looks up) and writes the three `Coord2D[4]` arrays at +0x524, +0x544 and
  +0x564. Those are the members witnessed by the matched AptPalantir
  constructor and destructor. It reads Image+0x24, which is `m_imageSize.x`
  according to name_oracle's layout witness.

## Method name: not proven

The first bank called this `QuadrilateralInset0079D530::update`. Nothing
supports `update`. On the real class that name would also collide with
AptPalantir's inherited `SubsystemInterface::update` virtual. This body is a
non-virtual helper that `renderRadarViewBox` calls directly, not a vtable
slot. No string, caller symbol or Zero Hour twin names it, so it keeps the
address token: `AptPalantir::rva0079D530`, following the precedent
`AptPalantir::rva00594740`.
