// Retail 0x0002248F is the five-byte incremental-link thunk `jmp 0x006C39D0`
// for W3DRadar::buildTerrainTexture; the body itself is matched at 0x006C39D0
// (game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar_buildTerrainTexture.cpp).
// The matched W3DRadar::refreshTerrain (0x006C4280) calls through this thunk.
// Claimed by address, as the ILT convention says; see
// targets/game/reverse/identity_evidence/0002248f-ilt-thunk.md.
// Under /O2 a tail call with no arguments is exactly `E9 rel32`.

void b_006c39d0();

void j_0002248f() { b_006c39d0(); }
