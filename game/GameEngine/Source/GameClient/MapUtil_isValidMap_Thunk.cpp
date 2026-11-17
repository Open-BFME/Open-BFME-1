// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: clean C++ reconstruction of map-cache validation.

#include "ascii_string.h"

// Retail inlines the canonical string's null/length test in this caller.
template <> inline bool StringBase<char>::isEmpty() const
{
	return !m_data || m_data->length == 0;
}

struct MapCacheNode
{
	unsigned char m_pad[0x38];
	bool m_isMultiplayer;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	void updateCache();
	MapCacheNode *m_end;
};

extern MapCache *TheMapCache;

// Retail calls MapCache::find through ILT 0x000263D7 (jumps to the map's
// _Rb_tree find body 0x000773E0); nothing defines a MapCache::find symbol.
extern void j_000263d7();

bool isValidMap(AsciiString mapName, bool isMultiplayer)
{
	if (!TheMapCache || mapName.isEmpty())
		return false;

	TheMapCache->updateCache();
	mapName.StringBase<char>::toLower();
	MapCache *cache = TheMapCache;
	typedef MapCacheNode *(MapCache::*FindFn)(const AsciiString &);
	union { void (*fn)(); FindFn call; } find = { j_000263d7 };
	MapCacheNode *it = (cache->*find.call)(mapName);
	if (it != cache->m_end && isMultiplayer == it->m_isMultiplayer)
		return true;

	return false;
}
