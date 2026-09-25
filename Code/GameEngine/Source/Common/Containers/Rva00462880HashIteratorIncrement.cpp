// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/STLTypedefs.h"
#include <hash_map>

struct AudioEventInfo;
struct Rva00461360Value
{
	const AsciiString first;
	AudioEventInfo *second;
};
struct Rva00461360ExtractKey
{
	const AsciiString &operator()(const Rva00461360Value &value) const
	{
		return value.first;
	}
};

typedef _STL::_Ht_iterator<
	Rva00461360Value, _STL::_Nonconst_traits<Rva00461360Value>, AsciiString,
	rts::hash<AsciiString>, Rva00461360ExtractKey,
	_STL::equal_to<AsciiString>, _STL::allocator<Rva00461360Value> >
	Rva00461360HashIterator;

template Rva00461360HashIterator Rva00461360HashIterator::operator++(int);
