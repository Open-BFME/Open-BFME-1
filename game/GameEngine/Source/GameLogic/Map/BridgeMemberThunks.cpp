// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z: game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// readable body of ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z: game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
//
// The two 5-byte incremental-link thunks retail links in front of Bridge's
// public query members. Each forwards to the implementation the linker placed
// elsewhere, which is why each has its own shim class: the shim's member is the
// symbol that carries the real address, and the thunk is what callers reach.
//
// They were three files declaring `class Bridge` three times, one member each.
// One class here declares all three, so the interface a caller sees is stated
// once instead of once per thunk.

struct Coord3D;
struct Region2D;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
    float getBridgeHeight(const Coord3D *, Coord3D *);
    bool isPointOnBridge(const Coord3D *);
};

// The body behind this thunk is ?getBridgeHeight@Bridge@@QAEMPBVCoord3D@@PAV2@@Z
// (class-keyed Coord3D, ilt_oracle CONFIRMED for slot 8601) in BridgeGetBridgeHeight.cpp.
extern "C" void __identifier("?getBridgeHeight@Bridge@@QAEMPBVCoord3D@@PAV2@@Z")(void);

class BridgePointOnBridgeShim
{
public:
    bool test(const Coord3D *point);
};

// ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z
float Bridge::getBridgeHeight(const Coord3D *pos, Coord3D *normal)
{
    typedef float (Bridge::*Body)(const Coord3D *, Coord3D *);
    union { void (*raw)(void); Body body; } target;
    target.raw = __identifier("?getBridgeHeight@Bridge@@QAEMPBVCoord3D@@PAV2@@Z");
    return (this->*target.body)(pos, normal);
}

// ?isPointOnBridge@Bridge@@QAE_NPBUCoord3D@@@Z
bool Bridge::isPointOnBridge(const Coord3D *point)
{
    return ((BridgePointOnBridgeShim *)this)->test(point);
}
