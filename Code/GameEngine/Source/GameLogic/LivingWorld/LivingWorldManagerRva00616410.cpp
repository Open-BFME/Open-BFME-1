// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

struct Rva00615D50Object
{
public:
	virtual void destroy(int deleteThis) = 0;
};

class Rva00618980Object
{
public:
	void rva00618980(int value);
};

typedef _STL::hash_map<AsciiString, Rva00615D50Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00616410Map;

class BfmeLivingWorldManager
{
public:
	void rva00616410();

private:
	unsigned char m_prefix[0x1a8];
	Rva00618980Object *m_field1a8;
	unsigned char m_middle[0x224 - 0x1ac];
	Rva00616410Map m_objects;
};

void BfmeLivingWorldManager::rva00616410()
{
	if (m_field1a8 != 0)
	{
		m_field1a8->rva00618980(0);
		m_field1a8 = 0;
	}

	for (Rva00616410Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		Rva00615D50Object *object = it->second;
		if (object != 0)
			object->destroy(1);
	}
	m_objects.clear();
}
