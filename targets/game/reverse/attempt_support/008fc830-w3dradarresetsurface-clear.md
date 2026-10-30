# 0x008FC830 W3DRadarResetSurface::clear(UnsignedInt), 508 B (session a1/502, 2026-10-30)

Link queue #14 blocker `?clear@W3DRadarResetSurface@@QAEXI@Z` (unlocks
Rva006C3500W3DRadarShroudCopy.cpp). Retail row is still the gen dump
`?d_008fc830@@YAXXZ`; the body belongs in
`game/Libraries/Source/WWVegas/WW3D2/SurfaceClass_DrawPixel.cpp` (it owns the
static `Rva008FC4F0_PixelSize`, `Get_Description` callers and
`Rva008FCA30_Surface_Byte_Size`, the next body).

Donor: Open-BFME-2 20a0cb6173 `Code/Libraries/Source/WWVegas/WW3D2/SurfaceByteSize.cpp`
`W3DRadarResetSurface::clear(bool)` (BFME 2 0x00116780, /O2 /Ob2 /G7 /arch:SSE).
BFME 1 target facts: one COM pointer at +0, LockRect/UnlockRect slots
0x34/0x38, inline DX8 error stream (TheBfmeAwakenDebug), low byte of the
argument selects 0/0xFF fill, DXT1-5 branch writes FF FE FF FF 55 55 55 55
blocks. Callers spell the argument UnsignedInt.

Best candidate (banked as attempts/008FC830.cpp, whole TU): donor body with
- `unsigned height;` set to `desc.Height >> 2` in the DXT branch and
  `desc.Height` in an `else` (donor's `desc.Height >>= 2` stores back; retail keeps it in ecx),
- countdown row loops `for (unsigned y = height; y > 0; --y)`,
- white branch keeps its own UnlockRect + return (a `goto` to a shared unlock wrecked regalloc).

probe --shape = 1.000: the only residue is retail `80 ca ff  or dl,0xff`
vs ours `81 ca ff 00 00 00  or edx,0xff` (+3 B, everything after shifts).

Ruled out (TU flags /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc, G6 default):
- every `unsigned char` spelling of the opaque byte (`(uchar)(fill|255)`, `c|=0xff`,
  chained stores, `c = 0xff; ... c = 0x55` reuse, signed char, -1): VC7.1 folds to
  `mov byte [esp+x],0xff` immediates, 0.966;
- `short`/`int`/`unsigned` opaque, `fill |= 0xff` on the unsigned fill, `&= 0xff`: `or edx,0xff`;
- `unsigned char fill` (any spelling, incl. if-assign, ~0, -1): fill becomes
  `test/sete/dec` and the frame moves, 0.90;
- `unsigned short fill`: 0.86; opaque hoisted above `if (white)` or to function scope: 0.98;
- /G7 gives `or dl,0xff` but `sub [mem],1` loop counters and loop alignment padding; /G5, /Os, /O1 worse.
Next ideas: a narrow LOCAL whose address is taken (shape_levers line on narrow locals),
or a byte-struct member assignment that keeps the value in dl.
