# 0x00701330 W3DMouse::loadD3DCursorTextures (559 B)

The old row named this body with the truncated prefix `?loadD3DCursorTextures@W3DMouse@@`
on a naked `__emit` lift (`W3DMouseLoadD3DCursorTexturesThunk.cpp`). This note records why the
full decorated name `?loadD3DCursorTextures@W3DMouse@@AAE_NW4MouseCursor@Mouse@@@Z` is the same
identity, not a new one.

BFME 1 target evidence:
- Caller: the matched `W3DMouse::setCursor` (0x007018A0, same TU) calls ILT 0x0000D08F, which
  jumps to 0x00701330, at the point where ZH `setCursor` calls `loadD3DCursorTextures(cursor)`.
- ILT oracle: `ilt_oracle.Oracle().check(name, 0x701330)` puts the full decorated name inside the
  window of slot 9858 (CONFIRMED, p_false 7.2e-4). The `ilt_oracle.py check` CLI reports
  CONTRADICTED for this RVA because its VA/RVA heuristic subtracts 0x400000 from any
  address >= 0x401000 when the difference is itself a thunk target. It then tests slot 8511,
  which is 0x00301330.
- Body: ret 4 (one stack argument, thiscall), returns AL 0/1 (bool). It reads
  m_cursorInfo[cursor].numFrames at this+0x50+0x54*cursor and textureName at +0x30, the same
  record the matched setCursor reads. It clamps to 21 (MAX_2D_CURSOR_ANIM_FRAMES), formats
  "%s.tga" / "%s%04d.tga", stores m_currentFrames at this+0x5E88, and fills the 50x21
  cursor texture table at VA 0x012F8798 (data row ?g_w3dMouseCursorTextures). This is the ZH
  loadD3DCursorTextures control flow.

Donor source: ZH GeneralsMD W3DMouse.cpp loadD3DCursorTextures. The BFME handle types
(texture handle returned by hidden sret, surface wrapper with out-of-line destructor 0x008FC5B0)
come from already pinned callees, not from the donor.

The C++ in game/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp is byte-exact
modulo relocations (probe, 559/559 B).
