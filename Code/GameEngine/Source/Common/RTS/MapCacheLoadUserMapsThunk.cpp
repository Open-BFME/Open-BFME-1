// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib
// readable body of ?loadUserMaps@MapCache@@AAE_NXZ: Code/GameEngine/Source/GameClient/MapUtil.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
    bool loadUserMaps();
};

class MapCacheLoadUserMapsShim
{
public:
    bool load();
};

bool MapCache::loadUserMaps()
{
    return ((MapCacheLoadUserMapsShim *)this)->load();
}
