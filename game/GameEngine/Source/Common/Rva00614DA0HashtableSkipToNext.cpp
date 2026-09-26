// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/STLTypedefs.h"
#include <hash_map>

struct Rva00614BC0Value
{
	const AsciiString first;
	int second;
};

struct Rva00614BC0ExtractKey
{
	const AsciiString &operator()(const Rva00614BC0Value &value) const
	{
		return value.first;
	}
};

template struct _STL::_Hashtable_iterator<
	Rva00614BC0Value, AsciiString, rts::hash<AsciiString>,
	Rva00614BC0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00614BC0Value> >;
