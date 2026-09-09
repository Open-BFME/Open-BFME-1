// ?bfmeRegisterHouseColor@@YAXPBD0@Z
// partial score=0.6 date=2026-09-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x00900D70. The HouseColor parser and BfmeThingFGD call this helper
// after resolving a prototype. The prototype's object id becomes the key in
// the unsigned map, and the second string becomes its value.

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
		if ( m_object != 0 )
			m_object->Release_Ref();
	}

	TextureClass *m_object;
};

Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype( const char *name );

class BfmeOwnedMember
{
public:
	BfmeOwnedMember() : m_object( 0 ) {}
	~BfmeOwnedMember()
	{
		if ( m_object != 0 )
			m_object->Release_Ref();
	}

	TextureClass *m_object;
};

class Gen0090DB70
{
public:
	Gen0090DB70( void *source );
	BfmeOwnedMember m_owned;
};

extern HouseColorMap g_bfmeList1016;

// ?bfmeRegisterHouseColor@@YAXPBD0@Z
void __cdecl bfmeRegisterHouseColor( const char *name, const char *value )
{
	if ( name == 0 || value == 0 )
		return;

	unsigned int key;
	Gen0090DB70 owner = Gen0090DB70(
		&(Rva009EBCE0AssetReference &)Rva009EBCE0_GetPrototype( name ) );
	key = owner.m_owned.m_object != 0
		? *(unsigned int *)((char *)owner.m_owned.m_object + 8)
		: (unsigned int)-1;
	g_bfmeList1016[key] = value;
}
