# 0x0079D3A0: AptPalantir vtable slot 11, not W3DGameWindowManager::init

BFME 1 target evidence (retail-1.03-unpacked):

- Vtable 0x01127A48 slot 11 (+0x2C) holds ILT 0x00445F39, which jumps to
  0x0079D3A0. The only functions carrying that vtable constant are the matched
  `??1AptPalantir@@UAE@XZ` (0x0079D1D0) and `??0AptPalantir@@QAE@XZ`
  (0x0079D9F0), so the body is an AptPalantir virtual
  (`tools/vtable_lookup.py 0x01127A48`).
- The body calls ILT 0x00004002 -> 0x00592B80, the matched
  `Rva00597FC0Client::bfmeReset00592B80`, on the same object (AptPalantir's
  base in AptPalantirConstructor.cpp), then zero-fills the three four-element
  Coord2D arrays at +0x524/+0x544/+0x564 that the constructor TU lays out.
- The banked `W3DGameWindowManager::init` name (score 0.35) came from the Zero
  Hour shape of three coordinate-array clears; the vtable ownership and base
  call refute it (re_attempts.log, refuted verdict, model=luna).

The semantic method name is not proven, so the row keeps the address-derived
`AptPalantir::rva0079d3a0`, matching its sibling `rva0079dc00`.
