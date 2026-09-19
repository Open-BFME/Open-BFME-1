// Open-BFME5: retail RVA 0x00615CB0, 125 bytes.
//
// The matched caller at 0x003BF3C0 loads TheLivingWorldManager from
// 0x012F706C and calls the coordinate/category lookup at 0x00615D50.  That
// lookup traverses this same AsciiString table at manager+0x224 and returns
// the same mapped object.  The caller then reads the returned object's +8
// word as a signed ID.  This body traverses that table and returns the object
// whose +8 ID equals its integer argument.  Its public method spelling is not
// recovered and therefore remains address-derived.
//
// The retail begin call reaches 0x00611680 through ILT 0x00036412.  Native
// STLport iterator increment passes the node's AsciiString key at +4 to the
// bucket helper at 0x00611CE0 through ILT 0x0001F843.
//
// First exact probe: 125/125 bytes with two relocations, t=12min.
// campaign=luna36h-20260907 lane=expand08 model=gpt-5.6-sol-ultra.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

struct Rva00615D50Object
{
	char pad[8];
	int id;
};

typedef _STL::hash_map<AsciiString, Rva00615D50Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00615CB0Map;

class BfmeLivingWorldManager
{
public:
	Rva00615D50Object *rva00615cb0(int id);

private:
	unsigned char m_prefix[0x224];
	Rva00615CB0Map m_objects;
};

Rva00615D50Object *BfmeLivingWorldManager::rva00615cb0(int id)
{
	for (Rva00615CB0Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		Rva00615D50Object *object = it->second;
		if (object->id == id)
			return object;
	}
	return 0;
}
