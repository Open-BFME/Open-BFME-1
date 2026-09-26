// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?writeCacheINI@MapCache@@AAEX_N@Z: game/GameEngine/Source/GameClient/MapUtil.cpp

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
    void writeCacheINI(bool);
};

class MapCacheWriteCacheINIShim
{
public:
    void write(bool user);
};

void MapCache::writeCacheINI(bool user)
{
    ((MapCacheWriteCacheINIShim *)this)->write(user);
}
