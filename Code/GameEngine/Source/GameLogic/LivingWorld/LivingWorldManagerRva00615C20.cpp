// Open-BFME5: retail RVA 0x00615C20, 110 bytes.
//
// The sole retail caller at 0x00609243 has already loaded g_bfmeGameCW from
// 0x012F706C into ECX and branches to this method when its input flag is zero,
// proving BfmeLivingWorldManager ownership.  This body traverses the same
// this+0x194 table and the same mapped object type as retail 0x006157C0.
//
// begin() returns the native two-word STLport iterator.  Each node holds an
// AsciiString key at +4 and a mapped object pointer at +8.  Iterator increment
// passes the +4 key to the AsciiString bucket helper at 0x00611CA0.  The mapped
// object call reaches 0x0061C3C0 through ILT 0x0001B2AC.  Its public method
// spelling is not recovered and therefore remains address-derived.
//
// Evidence checkpoint: t=3min model=gpt-5.6-sol-ultra
// campaign=luna36h-20260907 lane=expand08.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

class Rva0061C1D0Object
{
public:
	void rva0061c3c0();
};

typedef _STL::hash_map<AsciiString, Rva0061C1D0Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva00615C20Map;

class BfmeLivingWorldManager
{
public:
	void rva00615c20();

private:
	unsigned char m_prefix[0x194];
	Rva00615C20Map m_objects;
};

void BfmeLivingWorldManager::rva00615c20()
{
	for (Rva00615C20Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		it->second->rva0061c3c0();
	}
}
