# 0x006C6350: LineSegClass::operator= (BaseHeightMap's COMDAT), not PristineBoneInfo

Retail evidence (`inputs/baselines/bfme1/retail-1.03-unpacked`, RVA = VA - 0x400000):

- `0x006C6350` and `0x006098D0` are byte-identical 85-byte bodies: copy
  thirteen dwords (0x34 bytes) from `[esp+4]` to `ecx`, return `this`, `ret 4`.
  Retail was linked without identical-COMDAT folding, so each body has one
  identity, and one COMDAT name has one body in the image.
- `0x006C6350` is reached only through ILT `0x00044AA8`, and the only caller of
  either is `?Cast_Ray@BaseHeightMapRenderObjClass@@UAE_NAAVRayCollisionTestClass@@@Z`
  (`0x006CDF90`, `call 0x00044AA8` at +0x19B). That call takes `ecx = &lineseg`
  (a local `LineSegClass`) and pushes `&raytest.Ray` (raytest+0x0C); it is the
  Zero Hour statement `lineseg=raytest.Ray;` (BaseHeightMap.cpp Cast_Ray). The
  body sits inside BaseHeightMap.obj's code range (0x006C5B40..0x006D0590),
  where the compiler placed the COMDAT that TU instantiated.
- Recompiling the Zero Hour Cast_Ray against `game/Libraries/Source/WWVegas/WWMath/lineseg.h`
  (`game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap_Cast_Ray.cpp`)
  reproduces all 2839 bytes of 0x006CDF90; its only unresolved relocation was this
  call, emitted as `??4LineSegClass@@QAEAAV0@ABV0@@Z`, which the ledger placed at
  `0x006098D0` instead of `0x006C6350`.
- `0x006098D0` (ILT `0x000014FB`) has no direct caller and no caller through its
  ILT; it already carries a second name, `??4_ArcInfoStruct@VehicleCurveClass@@QAEAAU01@ABU01@@Z`
  (one_identity.py lists it among addresses with two real names). The
  `LineSegClass` claim there is the over-claim; the 52-byte `_ArcInfoStruct`
  claim stays.
- `??4PristineBoneInfo@@QAEAAU0@ABU0@@Z` at `0x006C6350` had no caller evidence:
  nothing in W3DModelDraw reaches 0x006C6350, and its only caller is the terrain
  ray cast above, which has no PristineBoneInfo.

Correction: `??4LineSegClass@@QAEAAV0@ABV0@@Z` moves from `0x006098D0` to
`0x006C6350` (source BaseHeightMap.cpp, which already forces this COMDAT for
Cast_Ray), retiring `??4PristineBoneInfo@@QAEAAU0@ABU0@@Z` at `0x006C6350`.
