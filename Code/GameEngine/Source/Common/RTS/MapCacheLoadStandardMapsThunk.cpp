// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?loadStandardMaps@MapCache@@AAEXXZ: Code/GameEngine/Source/GameClient/MapUtil.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
    void loadStandardMaps();
};

class MapCacheLoadStandardMapsShim
{
public:
    void load();
};

void MapCache::loadStandardMaps()
{
    ((MapCacheLoadStandardMapsShim *)this)->load();
}
