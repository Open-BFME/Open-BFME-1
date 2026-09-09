// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// BFME HouseColor registration helper, retail 0x00900D70. The parser and the
// BfmeThingFGD caller both pass two C strings. The resolved prototype object id
// becomes the map key and the second string becomes its value.

#include <stl/_config.h>
#include <map>
#include <string>

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	HouseColorString;
typedef _STL::map<unsigned int, HouseColorString> HouseColorMap;

class TextureClass
{
public:
	void Release_Ref();
};

class Rva009EBCE0AssetReference
{
public:
	~Rva009EBCE0AssetReference()
	{
		if (m_object != 0)
			m_object->Release_Ref();
	}

	TextureClass *m_object;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

class BfmeOwnedMember
{
public:
	BfmeOwnedMember() : m_object(0) {}
	~BfmeOwnedMember()
	{
		if (m_object != 0)
			m_object->Release_Ref();
	}

	TextureClass *m_object;
};

class Gen0090DB70
{
public:
	Gen0090DB70(void *source);
	BfmeOwnedMember m_owned;
};

extern HouseColorMap g_bfmeList1016;

// ?bfmeRegisterHouseColor@@YAXPBD0@Z
void __cdecl bfmeRegisterHouseColor(const char *name, const char *value)
{
	if (name == 0 || value == 0)
		return;

	// Keeping the key address-significant reproduces retail's stack-slot order:
	// temporary asset, key, then the counted owner.
	volatile unsigned int key;
	Gen0090DB70 owner = Gen0090DB70(
		&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype(name));
	key = owner.m_owned.m_object != 0
		? *(unsigned int *)((char *)owner.m_owned.m_object + 8)
		: (unsigned int)-1;
	g_bfmeList1016[const_cast<const unsigned int &>(key)] = value;
}
