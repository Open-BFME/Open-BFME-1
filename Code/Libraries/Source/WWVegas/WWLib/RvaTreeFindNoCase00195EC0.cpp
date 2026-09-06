// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Open-BFME7: STLport _Rb_tree<AsciiString, AsciiString, _Identity, NoCaseLess>::
// _M_find<AsciiString> at 0x00195EC0 -- the find() of the same case-insensitive
// set<AsciiString> whose insert_unique landed at 0x00195D30 in
// RvaTreeInsertUniqueNoCase.cpp.  The descent inlines compareNoCase around the
// _memicmp import (VA 0x01359310) exactly like the insert body; the equality
// tail calls compareNoCase out of line through the ILT at 0x00027471.
#include "PreRTS.h"
#include "Common/AsciiString.h"
extern "C" __declspec(dllimport) int __cdecl _memicmp( const void *buf1, const void *buf2, unsigned int count );
template <>
inline int StringBase<char>::compareNoCase( const StringBase<char> &str ) const
{
	int thatLen = str.m_data ? str.m_data->length : 0;
	const char *thatData = str.m_data ? &str.m_data->data[ 0 ] : (const char *)"";
	int thisLen = m_data ? m_data->length : 0;
	const char *thisData = m_data ? &m_data->data[ 0 ] : (const char *)"";
	int n = thisLen < thatLen ? thisLen : thatLen;
	int c = _memicmp( thisData, thatData, n );
	if ( c != 0 )
		return c;
	return thisLen - thatLen;
}
struct BfmeStringNoCaseLess
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const
	{
		return ( (const StringBase<char> *)&left )->compareNoCase( *(const StringBase<char> *)&right ) < 0;
	}
};
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	BfmeStringNoCaseLess, _STL::allocator<AsciiString> > Rva00195D30Tree;
// find() is public; the _M_find it calls is not, so reaching it through the
// public method is what emits it.
const AsciiString *BfmeTreeFindAnchor00195D30( const Rva00195D30Tree &tree, const AsciiString &key )
{
	Rva00195D30Tree::const_iterator it = tree.find( key );
	if ( it == tree.end() )
		return 0;
	return &( *it );
}
// ---- 0x000932F0: the same _M_find for the case-insensitive map whose
// insert_unique landed at 0x00093760 (pair<const AsciiString, 4-byte value>);
// replaces the byte lift in AsciiStringMapMetaDataFindThunk.cpp.
struct Rva00093670Value
{
	char m_body[ 4 ];
};
typedef _STL::pair<const AsciiString, Rva00093670Value> Rva00093670Pair;
typedef _STL::_Rb_tree<AsciiString, Rva00093670Pair, _STL::_Select1st<Rva00093670Pair>,
	BfmeStringNoCaseLess, _STL::allocator<Rva00093670Pair> > Rva00093670Tree;
const Rva00093670Pair *BfmeTreeFindAnchor00093670( const Rva00093670Tree &tree, const AsciiString &key )
{
	Rva00093670Tree::const_iterator it = tree.find( key );
	if ( it == tree.end() )
		return 0;
	return &( *it );
}
