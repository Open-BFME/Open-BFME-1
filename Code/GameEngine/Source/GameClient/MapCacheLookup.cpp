// cl: /DNDEBUG /MD /EHsc
// readable body of ?getMapDir@MapCache@@QBE?AVAsciiString@@XZ: Code/GameEngine/Source/GameClient/MapUtil.cpp
// readable body of ?getMapExtension@MapCache@@QBE?AVAsciiString@@XZ: Code/GameEngine/Source/GameClient/MapUtil.cpp
// readable body of ?findMap@MapCache@@QAEPBVMapMetaData@@VAsciiString@@@Z: Code/GameEngine/Source/GameClient/MapUtil.cpp
//
// Where the maps are and how one is found: the two constants the rest of the
// map cache builds every path out of, at 0x0044FF90 and 0x0044FFC0, and the
// lookup at 0x00454500 that turns a map name into its metadata.
//
// The three bodies had a file and an AsciiString declaration each. This is the
// spelling that byte-matches all three -- one data pointer, both constructors
// and the destructor out of line -- and it is deliberately NOT the inline
// StringBase forwarder that MapCacheGetUserMapDir and MapCacheLoadStandardMaps
// use: these bodies call ??0AsciiString@@QAE@PBD@Z directly, the forwarders
// would call ??0?$StringBase@D@@AAE@PBD@Z instead, and the two are different
// addresses. Merging those two in as well would have to unpick that first.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
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

// One node of the cache's name-keyed tree: the 0x14 bytes of links every
// STLport tree node carries, then the value.
struct MapCacheNode
{
	unsigned char m_treeLinks[0x14];
	MapMetaData second;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	AsciiString getMapDir() const;
	AsciiString getMapExtension() const;
	const MapMetaData *findMap(AsciiString mapName);
	MapCacheNode *bfmeFind(const AsciiString &mapName);

private:
	MapCacheNode *m_head;
};

// ?getMapDir@MapCache@@QBE?AVAsciiString@@XZ
// Retail 0x0044FF90, 33 bytes.
AsciiString MapCache::getMapDir() const
{
	return AsciiString("Maps");
}

// ?getMapExtension@MapCache@@QBE?AVAsciiString@@XZ
// Retail 0x0044FFC0, 33 bytes.
AsciiString MapCache::getMapExtension() const
{
	return AsciiString("map");
}

// ?findMap@MapCache@@QAEPBVMapMetaData@@VAsciiString@@@Z
// Retail 0x00454500, 122 bytes. The name arrives by value because it is
// lower-cased on the way in -- the cache is keyed case-insensitively. A search
// that lands on the tree head found nothing.
const MapMetaData *MapCache::findMap(AsciiString mapName)
{
	mapName.toLower();
	MapCacheNode *it = bfmeFind(mapName);
	if (it == m_head)
		return 0;
	return &(it->second);
}
