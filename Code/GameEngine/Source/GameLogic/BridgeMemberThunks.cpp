// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?isCellOnEnd@Bridge@@QAE_NPBURegion2D@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
//
// The three 5-byte incremental-link thunks retail links in front of Bridge's
// public query members. Each forwards to the implementation the linker placed
// elsewhere, which is why each has its own shim class: the shim's member is the
// symbol that carries the real address, and the thunk is what callers reach.
//
// They were three files declaring `class Bridge` three times, one member each.
// One class here declares all three, so the interface a caller sees is stated
// once instead of once per thunk.

struct Coord3D;
struct Region2D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
    float getBridgeHeight(const Coord3D *, Coord3D *);
    bool isCellOnEnd(const Region2D *);
    bool isPointOnBridge(const Coord3D *);
};

class BridgeGetBridgeHeightShim
{
public:
    float compute(const Coord3D *pos, Coord3D *normal);
};

class BridgeCellOnEndShim
{
public:
    bool test(const Region2D *region);
};

class BridgePointOnBridgeShim
{
public:
    bool test(const Coord3D *point);
};

// ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z
float Bridge::getBridgeHeight(const Coord3D *pos, Coord3D *normal)
{
    return ((BridgeGetBridgeHeightShim *)this)->compute(pos, normal);
}

// ?isCellOnEnd@Bridge@@QAE_NPBURegion2D@@@Z
bool Bridge::isCellOnEnd(const Region2D *region)
{
    return ((BridgeCellOnEndShim *)this)->test(region);
}

// ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z
bool Bridge::isPointOnBridge(const Coord3D *point)
{
    return ((BridgePointOnBridgeShim *)this)->test(point);
}
