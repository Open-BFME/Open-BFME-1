// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: clean C++ lift of the retail MapCache constructor.

#include <map>
#include <set>

typedef int Bool;

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
struct MapMetaData
{
	unsigned char m_data[252];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
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
