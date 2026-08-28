// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: clean C++ lift of the retail MapCache constructor.

#include <map>
#include <set>

typedef int Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString();
	~AsciiString();
	bool operator<(const AsciiString &other) const;

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
struct MapMetaData
{
	unsigned char m_data[252];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
	MapCache();

private:
	std::map<AsciiString, Bool> m_seen;
	std::set<AsciiString> m_allowedMaps;
};

MapCache::MapCache()
{
}
