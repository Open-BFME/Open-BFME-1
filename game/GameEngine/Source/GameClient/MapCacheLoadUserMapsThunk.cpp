// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /game/Libraries/Source/WWVegas/WWLib
// readable body of ?loadUserMaps@MapCache@@AAE_NXZ: game/GameEngine/Source/GameClient/MapUtil.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
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
