// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

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

struct Rva0019BC70Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const Rva0019BC70Key, Rva0019BC70Value> Rva0019BC70Pair;

typedef _STL::_Rb_tree<Rva0019BC70Key, Rva0019BC70Pair,
	_STL::_Select1st<Rva0019BC70Pair>, _STL::less<Rva0019BC70Key>,
	_STL::allocator<Rva0019BC70Pair> > Rva0019BC70Tree;

extern template _STL::pair<Rva0019BC70Tree::iterator, bool>
Rva0019BC70Tree::insert_unique( const Rva0019BC70Pair & );

template Rva0019BC70Tree::iterator
Rva0019BC70Tree::insert_unique( Rva0019BC70Tree::iterator,
	const Rva0019BC70Pair & );
