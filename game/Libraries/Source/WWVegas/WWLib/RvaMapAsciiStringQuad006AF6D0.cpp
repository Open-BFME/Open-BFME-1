// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Retail 0x006AF6D0: AsciiString-keyed map subscript. The mapped float is
// witnessed by caller 0x006B0850: +0x153 transfers through Xfer slot 0x6C,
// then +0x15D calls this body via ILT 0xD9D1 and +0x166 stores that value.
// The same Xfer slot is used for the independently matched floating-point
// record in Rva006ABC60Xfer.cpp. Hinted insertion 0x006AB6D0 delegates to
// 0x005C7490, which allocates 0x18 bytes: 16-byte links plus string/float.
// Its iterator result uses a hidden output pointer (three stack arguments,
// ret 0x0C), not a direct scalar return. Comparator owner stays opaque.

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include "PreRTS.h"
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

struct Rva006AF6D0Less : _STL::less<AsciiString>
{
};

typedef float Rva006AF6D0Mapped;

template class _STL::map<AsciiString, Rva006AF6D0Mapped, Rva006AF6D0Less,
    _STL::allocator<_STL::pair<const AsciiString, Rva006AF6D0Mapped> > >;
