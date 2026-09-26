// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

struct Rva00615D50Object
{
	void rva00618a90();
};

// The retail call at +0x28 encodes the ILT at 0x00010186, which jumps to the
// 398-byte body at 0x00618A90.  targets/game/reverse/symbols.csv pins that route.

typedef _STL::hash_map<AsciiString, Rva00615D50Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00616110Map;

class BfmeLivingWorldManager
{
public:
	void rva00616110();

private:
	unsigned char m_prefix[0x224];
	Rva00616110Map m_objects;
};

void BfmeLivingWorldManager::rva00616110()
{
	for (Rva00616110Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		Rva00615D50Object *object = it->second;
		if (object != 0)
			object->rva00618a90();
	}
}
