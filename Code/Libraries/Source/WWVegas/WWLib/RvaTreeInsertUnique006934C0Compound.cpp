// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <set>

struct Rva006934C0Key
{
	unsigned int m_id;
	AsciiString m_name;
};

namespace _STL
{
template <> struct less<Rva006934C0Key>
{
	bool operator()( const Rva006934C0Key &left,
		const Rva006934C0Key &right ) const
	{
		if ( left.m_id < right.m_id )
			return true;
		if ( left.m_id > right.m_id )
			return false;
		return left.m_name.compare( right.m_name ) < 0;
	}
};
}

typedef _STL::_Rb_tree<Rva006934C0Key, Rva006934C0Key,
	_STL::_Identity<Rva006934C0Key>, _STL::less<Rva006934C0Key>,
	_STL::allocator<Rva006934C0Key> > Rva006934C0Tree;

template _STL::pair<Rva006934C0Tree::iterator, bool>
Rva006934C0Tree::insert_unique( const Rva006934C0Key & );
