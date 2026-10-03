// cl: /DNDEBUG /MD /EHsc
// ILT RVA 0x00028FF1 routes directly to MapCache::loadUserMaps at 0x004577C0.
// The implementation lives in MapCacheLoadUserMaps.cpp; this keeps the
// incremental-link entry distinct from the full method's identity.
class MapCacheLoadUserMapsThunk;
class MapCache
{
    friend class MapCacheLoadUserMapsThunk;
    bool loadUserMaps();
};

class MapCacheLoadUserMapsThunk
{
public:
    bool loadUserMaps();
};

bool MapCacheLoadUserMapsThunk::loadUserMaps()
{
    return ((MapCache *)this)->loadUserMaps();
}
