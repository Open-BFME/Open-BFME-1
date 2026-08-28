// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?isCellOnEnd@Bridge@@QAE_NPBURegion2D@@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp

struct Region2D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
    bool isCellOnEnd(const Region2D *);
};

class BridgeCellOnEndShim
{
public:
    bool test(const Region2D *region);
};

bool Bridge::isCellOnEnd(const Region2D *region)
{
    return ((BridgeCellOnEndShim *)this)->test(region);
}
