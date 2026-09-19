// Open-BFME5: retail RVA 0x006159C0, 129 bytes.
//
// Its sole matched caller at 0x006094C0 loads TheLivingWorldManager from
// 0x012F706C into ECX, null-checks it, and tail-jumps through ILT 0x0003BE58
// to this body.  Retail stores one byte at manager+0x288, calls the matched
// HideControlBar(bool) through ILT 0x00002847, then traverses the native
// AsciiString/object-pointer hash map at manager+0x194.  The same map layout
// is independently established by 0x006157C0 and 0x00615C20.
//
// Each mapped object is called through ILT 0x0000EA6B to body 0x0061C2A0.
// Its public type and method spelling are not recovered, so both remain
// address-derived and use the same neutral mapped type as the adjacent map
// traversals.  Iterator increment passes the node AsciiString at +4 to the
// bucket helper at 0x00611CA0.
//
// First exact probe: 129/129 bytes with four relocations, t=4min.
// campaign=luna36h-20260907 lane=expand08 model=gpt-5.6-sol-ultra.
//
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include "Common/STLTypedefs.h"
#include <hash_map>

void HideControlBar(bool immediate);

class Rva0061C1D0Object
{
public:
	void rva0061c2a0();
};

typedef _STL::hash_map<AsciiString, Rva0061C1D0Object *,
	rts::hash<AsciiString>, _STL::equal_to<AsciiString> > Rva006159C0Map;

class BfmeLivingWorldManager
{
public:
	void rva006159c0();

private:
	unsigned char m_prefix[0x194];
	Rva006159C0Map m_objects;
	unsigned char m_middle[0x288 - 0x194 - sizeof(Rva006159C0Map)];
	bool m_flag288;
};

void BfmeLivingWorldManager::rva006159c0()
{
	m_flag288 = true;
	HideControlBar(true);
	for (Rva006159C0Map::iterator it = m_objects.begin();
		it != m_objects.end(); ++it)
	{
		it->second->rva0061c2a0();
	}
}
