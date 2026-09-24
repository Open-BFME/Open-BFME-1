// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Retail 0x00239600, complete 185-byte boundary. The caller and vtable scans
// do not identify its owner, so keep the type and method names address-derived.

#define _STLP_NO_EXCEPTIONS 1
#include "Lib/BaseType.h"
#include <map>
#include <list>

struct Rva00239600Payload
{
	unsigned char m_unreconstructed_000[0x74];
	int m_key;
};

typedef _STL::map<int, Rva00239600Payload *> Rva00239600Map;
typedef _STL::list<Rva00239600Payload *> Rva00239600List;

class Rva00239600
{
public:
	bool body();
	unsigned char m_unreconstructed_000[0x30];
	Rva00239600Map m_tree;
};

extern Real g_bfmeScaleBC;

bool Rva00239600::body()
{
	void *owner = *(void **)((char *)this - 0xdc);
	Coord3D *ownerPositionRaw = (Coord3D *)((char *)owner + 0x38);
	Coord3D ownerPosition;
	ownerPosition.x = ownerPositionRaw->x;
	ownerPosition.y = ownerPositionRaw->y;
	Rva00239600List *items = (Rva00239600List *)((char *)this - 0xac);
	Rva00239600List::iterator entry = items->begin();
	Rva00239600List::iterator head = items->end();
	int key;

	while (entry != head)
	{
		Rva00239600Payload *payload = *entry;
		key = payload->m_key;
		if (m_tree.find(key) == m_tree.end())
		{
			Coord2D *position = (Coord2D *)((char *)payload + 0x38);
			Real dx = ownerPosition.x - position->x;
			Real dy = ownerPosition.y - position->y;
			if (dx * dx + dy * dy > g_bfmeScaleBC)
				return false;
		}
		++entry;
	}
	return true;
}
