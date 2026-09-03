// cl: /DNDEBUG /MD /EHsc
// readable body of ?findMap@MapCache@@QAEPBVMapMetaData@@VAsciiString@@@Z: Code/GameEngine/Source/GameClient/MapUtil.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
	void toLower();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapMetaData
{
};

struct MapCacheNode
{
	unsigned char m_treeLinks[0x14];
	MapMetaData second;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
	MapCacheNode *bfmeFind(const AsciiString &mapName);

private:
	MapCacheNode *m_head;
};

const MapMetaData *MapCache::findMap(AsciiString mapName)
{
	mapName.toLower();
	MapCacheNode *it = bfmeFind(mapName);
	if (it == m_head)
		return 0;
	return &(it->second);
}
