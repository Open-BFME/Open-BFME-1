// Open-BFME5: retail RVA 0x00615A70, 126 bytes.
//
// Same LivingWorldManager receiver and native STLport AsciiString/BfmeThingNA
// pointer map at +0x194 proven by the adjacent exact methods 0x006159C0,
// 0x00615900 and 0x00615B10. This body iterates the map and passes the
// Coord2D argument to the matched guarded BfmeThingNA update at 0x0061C2F0;
// no flags or InGameUI dispatch follow, unlike its 0x00615900 sibling.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

class BfmeThingNA
{
public:
	void bfmeUpdateBFromPointGuardedNA(const Coord2D &point);
};

typedef _STL::hash_map<AsciiString, BfmeThingNA *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00615A70Map;

class BfmeLivingWorldManager
{
public:
	void rva00615a70(const Coord2D &point);

private:
	unsigned char m_prefix[0x194];
	Rva00615A70Map m_objects;
};

void BfmeLivingWorldManager::rva00615a70(const Coord2D &point)
{
	for (Rva00615A70Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		it->second->bfmeUpdateBFromPointGuardedNA(point);
	}
}
