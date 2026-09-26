// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// The retail body is the plain insert_unique overload in the same
// Rva0019BC70Key tree family as the hinted overload at 0x0019AA50.  Its
// _M_insert call resolves to the independently converted 8-byte-value body at
// 0x00198190, so the mapped type follows that proven callee ABI.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#include "PreRTS.h"
#include "Common/AsciiString.h"

struct Rva0019BC70Key
{
	AsciiString first;
	AsciiString second;
};

namespace _STL
{
template <> struct less<Rva0019BC70Key>
{
	bool operator()( const Rva0019BC70Key &left,
		const Rva0019BC70Key &right ) const
	{
		return left.first.compare( right.first ) < 0
			|| ( !( right.first.compare( left.first ) < 0 )
				&& left.second.compare( right.second ) < 0 );
	}
};
}

struct Rva00198190Value
{
	char m_body[ 8 ];
};

typedef _STL::pair<const Rva0019BC70Key, Rva00198190Value> Rva00198190Pair;

typedef _STL::_Rb_tree<Rva0019BC70Key, Rva00198190Pair,
	_STL::_Select1st<Rva00198190Pair>, _STL::less<Rva0019BC70Key>,
	_STL::allocator<Rva00198190Pair> > Rva00198190Tree;

template _STL::pair<Rva00198190Tree::iterator, bool>
Rva00198190Tree::insert_unique( const Rva00198190Pair & );
