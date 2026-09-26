// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

// ScriptEngine::assignTeamReference calls this tree insertion for the map at
// ScriptEngine+0x16064.  The canonical two-AsciiString key is shared with the
// unit-reference tree; the mapped word is the Team reference.
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

class Team;
typedef _STL::pair<const Rva0019BC70Key, Team *> Rva00342170Pair;

typedef _STL::_Rb_tree<Rva0019BC70Key, Rva00342170Pair,
	_STL::_Select1st<Rva00342170Pair>, _STL::less<Rva0019BC70Key>,
	_STL::allocator<Rva00342170Pair> > Rva00342170Tree;

template _STL::pair<Rva00342170Tree::iterator, bool>
Rva00342170Tree::insert_unique( const Rva00342170Pair & );
