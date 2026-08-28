// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of map-cache validation.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_allocated;
	unsigned short m_length;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();
	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
	void toLower();
private:
	AsciiStringData *m_data;
};

struct MapCacheNode
{
	unsigned char m_pad[0x38];
	bool m_isMultiplayer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
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
