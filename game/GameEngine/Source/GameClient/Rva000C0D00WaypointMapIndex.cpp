// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// WaypointMap callers establish a string-keyed map returning a 12-byte value.
// The retail default-value sequence copies three overlapping stack dwords;
// these are NOT zero stores. An empty constructor preserves that historical
// initialization shape. The payload remains address-derived because the
// current reference Coord3D declaration emits a different template body.

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include "Common/AsciiString.h"
#include <map>

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const
	{
		return left.compare( right ) < 0;
	}
};
}

struct Rva000C0D00Less : _STL::less<AsciiString>
{
};

struct Rva000C0D00Value
{
	Rva000C0D00Value()
	{
	}

	float x;
	float y;
	float z;
};

// Independently decoded helpers: lower_bound at 0x000BF610 returns a node
// and pops one key pointer; hinted insert at 0x000C0110 receives a hidden
// iterator output pointer first, then hint and pair pointers, and pops 12 bytes.

template class _STL::map<AsciiString, Rva000C0D00Value, Rva000C0D00Less,
	_STL::allocator<_STL::pair<const AsciiString, Rva000C0D00Value> > >;
