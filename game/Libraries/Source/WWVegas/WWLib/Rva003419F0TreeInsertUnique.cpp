// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// The retail body is the plain insert_unique overload at 0x003419F0.  The
// adjacent landed bodies establish the two-AsciiString ordering, while its
// own _M_insert target allocates a 0x20-byte node, proving an eight-byte
// mapped value for this instantiation.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#include "PreRTS.h"
#include "Common/AsciiString.h"

struct Rva003419F0Key
{
	AsciiString first;
	AsciiString second;
};

namespace _STL
{
template <> struct less<Rva003419F0Key>
{
	bool operator()( const Rva003419F0Key &left,
		const Rva003419F0Key &right ) const
	{
		return left.first.compare( right.first ) < 0
			|| ( !( right.first.compare( left.first ) < 0 )
				&& left.second.compare( right.second ) < 0 );
	}
};
}

struct Rva003419F0Value
{
	char m_body[ 8 ];
};

typedef _STL::pair<const Rva003419F0Key, Rva003419F0Value>
	Rva003419F0Pair;

typedef _STL::_Rb_tree<Rva003419F0Key, Rva003419F0Pair,
	_STL::_Select1st<Rva003419F0Pair>, _STL::less<Rva003419F0Key>,
	_STL::allocator<Rva003419F0Pair> > Rva003419F0Tree;

template _STL::pair<Rva003419F0Tree::iterator, bool>
Rva003419F0Tree::insert_unique( const Rva003419F0Pair & );
