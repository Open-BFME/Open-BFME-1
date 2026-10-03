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
	MapCacheNode *find(const AsciiString &name);
	MapCacheNode *m_end;
};

extern MapCache *TheMapCache;

bool isValidMap(AsciiString mapName, bool isMultiplayer)
{
	if (!TheMapCache || mapName.isEmpty())
		return false;

	TheMapCache->updateCache();
	mapName.toLower();
	MapCache *cache = TheMapCache;
	MapCacheNode *it = cache->find(mapName);
	if (it != cache->m_end && isMultiplayer == it->m_isMultiplayer)
		return true;

	return false;
}
