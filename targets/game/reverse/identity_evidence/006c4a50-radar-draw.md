# RVA006C4A50: BFME radar draw

Retail1.03 unpacked: entry6C4A50, RET14 at6C501B, extent1486. Independently read
vtableVA0111D7B4 slot7 -> VA0042B6F7 E9 -> VA00AC4A50. Matched W3DRadar
constructor6C1D70/destructor6C1780 install this table. ZH W3DRadar::draw provides
the border/aspect algorithm and operation order. BFME adds a packed-color fifth
argument, clipping, a fourth image, and native value-surface cleanup. The new
method remains address-qualified because the published four-argument ABI differs.

Source includes canonical Player/Radar headers, retaining canonical global
pointer types. Physical BFME layout and virtual calls use address-qualified
views. Fifth argument is passed to packed-color multiplier6C0890, all image
calls, both renderObjectList calls, and events/view-box calls; it is not Bool
or float. Four image offsets1474,149C,1484,1490; last uses original rectangle.

## Four scoped callee-view pins

These retain the existing physical callees, without claiming new body identities.
- fill@Rva006C4A50Display ->4336F0 via ILT13FA2. Four float coordinates plus
  packed color. Independently decoded60-byte callee forwards five words between
  begin/end virtuals; RET14 at433729.
- line@Rva006C4A50Display ->479E00 via ILT4A35E. Five floats including width1.0
  plus packed color. Decoded65-byte callee forwards six words between begin/end;
  RET18 at479E3E. Existing definitions use int/pointer spellings. Member-pointer
  casts to those bindings emitted60 extra bytes; direct float-stack views retain
  the actual call contract and reproduce retail exactly.
- renderObjectList@Rva006C4A50Owner ->6C43F0 via ILT272A5. Parent passes list,
  address of +1488 texture holder, and packed color twice. Existing1296-byte
  MASM body ends6C48FD RET0C. Old Bool spelling would truncate packed color.
- drawEvents@Rva006C4A50Owner ->6C3170 via ILT3F887. Parent passes five words
  x,y,width,height,color. Existing729-byte dump ends6C3446 RET14 despite old
  four-argument decorated label. Separate helper body identity is unchanged.

Other calls reuse Player::hasRadar, Radar::findDrawPositions, Rva006C0890,
W3DRadarResetTexture::getSurfaceLevel, W3DRadarResetSurface::clear/destructor,
Rva006C0C00W3DRadar::reconstructViewBox, Rva006C0FA0W3DRadar::method.

Surface return is one nontrivial word: clear at6C4DEC; destructor at6C4DFD before
list rendering. FuncInfoE39BC8 has state0 -> -1; actionC4A000 LEA ECX,[EBP-28]
then JMP8FC5B0. Native full-expression lifetime retained; no surrogate cleanup.

Probe including canonical headers:1486/1486 exact outside41 relocation slots.
Landing additionally requires strict relocation/reference verification.
