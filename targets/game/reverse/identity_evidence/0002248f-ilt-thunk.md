# ILT thunk 0x0002248F is not the W3DRadar::buildTerrainTexture body

The 5-byte row at 0x0002248F was named `?buildTerrainTexture@W3DRadar@@IAEXPAVTerrainLogic@@@Z`
and forwarded, through a TU-local `W3DRadarBuildTerrainTextureShim::build` pin, to 0x006C39D0.
Retail at 0x0002248F is one instruction:

    +0000 e9 3c 15 6a 00    jmp 0x006C39D0

(`python3 tools/dis_retail.py 2248F 5`). It lies in the incremental-link table and has no body
of its own. The body is 0x006C39D0 (1772 B), now matched from clean C++ under the real name:

- the matched `?refreshTerrain@W3DRadar@@UAEXPAVTerrainLogic@@@Z` (0x006C4280) calls it through
  this thunk, as Zero Hour's and Generals' `W3DRadar::refreshTerrain` call
  `buildTerrainTexture( terrain )`;
- the body is the original Generals `W3DRadar::buildTerrainTexture` sampling loop (integer z,
  `getGroundHeight` per water sample, bridge template colour, `DrawPixel` of
  `GameMakeColor(r*255, g*255, b*255, 255)`), preceded by BFME's `<map>_art.tga` check.

The thunk keeps its bytes as the address-claimed ILT thunk `?j_0002248f@@YAXXZ`, jumping to the
address pin `?b_006c39d0@@YAXXZ` (0x006C39D0), and the real name moves to the body.
