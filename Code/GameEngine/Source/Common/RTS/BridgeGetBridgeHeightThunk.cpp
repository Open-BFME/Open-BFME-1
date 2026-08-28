// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?getBridgeHeight@Bridge@@QAEMPBUCoord3D@@PAU2@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp

struct Coord3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
    float getBridgeHeight(const Coord3D *, Coord3D *);
};

class BridgeGetBridgeHeightShim
{
public:
    float compute(const Coord3D *pos, Coord3D *normal);
};

float Bridge::getBridgeHeight(const Coord3D *pos, Coord3D *normal)
{
    return ((BridgeGetBridgeHeightShim *)this)->compute(pos, normal);
}
