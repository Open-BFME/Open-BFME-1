// ??0Bridge@@QAE@PAVObject@@@Z
// partial score=0.20 date=2026-09-10
// Bridge::Bridge(Object *bridgeObj), retail 0x001A9CE0 size 1412.
//
// Identity is not in doubt: pinned via ILT 0x00047C0D, which the landed
// Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp:1744 caller
// (TerrainLogic::addLandmarkBridgeToLogic) already calls through a forward
// declaration (BfmeBridgeNode::BfmeBridgeNode(Object*), comment
// "retail ILT 0x00047c0d"). reverse/symbols.csv already carries the pin.
//
// A readable draft already lives in the same TU as this constructor's
// natural home, Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// lines 344-454 (Bridge::Bridge(Object *bridgeObj), tagged
// "??0Bridge@@ present-unmatched"). It compiles against the file's real
// #include chain and produces 1528 B against retail's 1412 B, 1206
// non-relocation bytes differing, first divergence at +0x23 -- i.e. almost
// immediately, not a late near-miss. Do not re-type it; open that file.
//
// Bridge's exact 0x90-byte layout is already PROVEN, not guessed: the
// landed, matched Code/GameEngine/Source/GameLogic/Map/BridgeIsPointOnBridge.cpp
// (BridgePointOnBridgeShim) gives it field-for-field --
//   +0x00 vptr (void*)              +0x28 fromLeft (Coord3D)
//   +0x04 m_next (void*)            +0x34 fromRight (Coord3D)
//   +0x08 m_templateName (void*)    +0x40 toLeft (Coord3D)
//   +0x0C from (Coord3D)            +0x4C toRight (Coord3D)
//   +0x18 to (Coord3D)              +0x58 bridgeIndex/curDamageState/
//   +0x24 bridgeWidth (float)             bridgeObjectID/towerObjectID[4]/
//                                          damageStateChanged (0x20 span)
//   +0x78 m_bounds (Region2D, 16B)  +0x88 m_layer (int)   +0x8C m_extra
//
// The divergence is the vtable install. Retail's ctor writes
// `mov dword ptr [esi], 0x109c354` early (VA 0x0109C354); tools/vtable_lookup.py
// 0x0109C354 shows one slot -> 0x0040db43 (a j_ thunk) and names the two
// other retail sites that install the same constant: the sibling ctor
// Bridge(BridgeInfo&,Dict*,AsciiString) at 0x001A98A0 (already landed, but
// only as a naked __emit lift -- Bridge_ctor_Thunk.cpp -- so it is not a
// real-C++ precedent either) and a generated destructor stub at 0x001A7350
// (Gen_dtor_001a7350.cpp, 101B, still ungenerated real C++). No file in
// this tree yet WRITES that vtable pointer as real C++, and no
// reverse/symbols.csv pin exists for VA 0x0109C354. The landed
// BridgePointOnBridgeShim sidesteps this entirely by modelling the slot as
// a plain, never-assigned `void *m_vptr` data member -- it only READS the
// object, so it never had to solve the install. This ctor cannot dodge it:
// landing requires either (a) a real virtual base whose compiler-synthesised
// vtable happens to byte-match 0x0109C354's single-slot shape, or (b) an
// extern data symbol pinned/patched to that VA whose address the ctor
// stores explicitly. Neither is done here.
//
// Ruled out: compiling the ctor against the file's real TerrainLogic.h
// class (public MemoryPoolObject with `virtual ~MemoryPoolObject(){}` from
// reference/shims/sweep/Common/GameMemory.h) does NOT reproduce the retail
// vtable-install instruction at the same program point; the compiled
// prologue takes a different shape (an extra `push edi` / different
// register zeroing order) from the very first divergent byte, so the
// mismatch is not merely the DIR32 payload value.
//
// Untouched downstream: even with the vtable solved, the tower-creation
// loop (BRIDGE_TOWERS is live in this BFME body, unlike the GeneralsMD
// reference where it is #if 0'd out) calls Object::getTemplate,
// Object::getPosition, Object::getOrientation, GeometryInfo::getMajorRadius/
// getMinorRadius, ThingTemplate::getTowerObjectName and
// Bridge::createTower (itself only a naked lift at
// Code/GameEngine/Source/GameLogic/Bridge_createTower_Thunk.cpp) -- none of
// these were found matched or pinned in reverse/functions.csv /
// reverse/symbols.csv, so even a byte-correct shim would still fail the
// unresolved-call gate on first build. t=25min model=Claude Sonnet 5
