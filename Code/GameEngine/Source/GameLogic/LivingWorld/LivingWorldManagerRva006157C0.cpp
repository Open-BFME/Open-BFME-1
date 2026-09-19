// Open-BFME5: retail RVA 0x006157C0, 110 bytes.
//
// The sole retail call at 0x0060A09C first loads g_bfmeGameCW from
// 0x012F706C into ECX, proving BfmeLivingWorldManager ownership.  The manager
// constructor/destructor at 0x006171D0/0x00617FB0 and the adjacent methods use
// the same STLport hashtable at this+0x194.
//
// begin() returns the native two-word STLport iterator.  Each node holds an
// AsciiString key at +4 and a mapped object pointer at +8.  The iterator's
// retail increment passes the +4 key to the AsciiString bucket helper at
// 0x00611CA0; this distinguishes the key from an integer despite the otherwise
// compatible node layout.  The mapped object's public type and method spelling
// are not recovered, so both remain address-derived.
//
// Evidence checkpoint: t=8min model=gpt-5.6-sol-ultra
// campaign=luna36h-20260907 lane=expand08.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

class Rva0061C1D0Object
{
public:
	void rva0061c1d0();
};

typedef _STL::hash_map<AsciiString, Rva0061C1D0Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva006157C0Map;

class BfmeLivingWorldManager
{
public:
	void rva006157c0();

private:
	unsigned char m_prefix[0x194];
	Rva006157C0Map m_objects;
};

void BfmeLivingWorldManager::rva006157c0()
{
	for (Rva006157C0Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		it->second->rva0061c1d0();
	}
}
