// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/ini /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// Retail BfmeThingBPA::bfmeGoBFA receives its map receiver in ECX and forwards
// the second argument through ILT 0x00036CFA to the matched STLport map
// operator[] body at 0x00093E60.  Keep the mapped type and comparator spelling
// identical to that existing instantiation so this method has the real member
// ABI rather than the old free-stdcall facade.
#define _STLP_NO_EXCEPTIONS 1
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#include "Common/AsciiString.h"
#include <map>
#include <set>
#include <vector>
#include <algorithm>

class Rva00093E60Item;

typedef _STL::map<AsciiString, Rva00093E60Item *, _STL::less<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, Rva00093E60Item *> > > Rva00093E60Map;

class BfmeThingBPA : public Rva00093E60Map
{
public:
	void bfmeGoBFA(void *one, void *two, void *three);
};

void BfmeThingBPA::bfmeGoBFA(void *one, void *two, void *three)
{
	Rva00093E60Item *&got = (*this)[*static_cast<const AsciiString *>(two)];
	got = static_cast<Rva00093E60Item *>(three);
}
