// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
	void toLower();

private:
	void *m_data;
};

class MapMetaData
{
};

struct MapCacheNode
{
	unsigned char m_treeLinks[0x14];
	MapMetaData second;
};

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
