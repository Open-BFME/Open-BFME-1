// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: STLport _Rb_tree<AsciiString, V>::insert_unique(const value_type
// &) for the three trees whose comparator is case-insensitive -- 275 bytes each
// where the case-sensitive siblings in RvaTreeInsertUniquePlain.cpp are 310.
//
// The thirty-five byte difference is the comparison.  less<AsciiString> inlines
// AsciiString::compare -- two lengths as halfwords, repe cmpsb, the length
// difference as the tiebreak -- at both comparison sites.  This comparator does
// not: what these bodies call at both sites is
// StringBase<char>::compareNoCase, out of line, which is why the shim used here
// is stringbaseascii rather than the case-sensitive file's.
//
// The comparator has no name the bytes reach, so it is spelled for the function
// it calls, exactly as the _M_insert conversions in RvaTreeMInsertStringKey.cpp
// already spell it; the tree types come from those _M_insert bodies unchanged,
// which is why the mapped types are named for the _M_insert's address.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/AsciiString.h"

// The CRT import, not the static one: retail reaches _memicmp through the
// import table, so the comparison ends in `call dword ptr [__imp__memicmp]`
// rather than a direct call.
extern "C" __declspec(dllimport) int __cdecl _memicmp( const void *buf1, const void *buf2, unsigned int count );

// StringBase<char>::compareNoCase, spelled out where the sibling
// RvaTreeInsertUniquePlain.cpp lets the shim spell compare.  It has to be a
// real function rather than a hand-inlined expression, because retail expands
// it at one of the two comparison sites in each of these bodies and calls the
// out-of-line copy at 0x00090570 at the other -- an inline budget spent inside
// the loop and refused afterwards.  Written this way MSVC is given the same
// choice and makes the same one.  The shape is compare's: the length as a
// halfword at +4 of the header, a null pointer standing in for the empty
// string, the length difference as the tiebreak.
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

// The comparator has no name the bytes reach; it is spelled for the function it
// calls, exactly as the _M_insert conversions in RvaTreeMInsertStringKey.cpp
// already spell it.
struct BfmeStringNoCaseLess
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const
	{
		return ( (const StringBase<char> *)&left )->compareNoCase( *(const StringBase<char> *)&right ) < 0;
	}
};

struct Rva00093670Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const AsciiString, Rva00093670Value> Rva00093670Pair;

typedef _STL::_Rb_tree<AsciiString, Rva00093670Pair, _STL::_Select1st<Rva00093670Pair>,
	BfmeStringNoCaseLess, _STL::allocator<Rva00093670Pair> > Rva00093670Tree;

// retail 0x00093760, inserting through the _M_insert at 0x00093670
template _STL::pair<Rva00093670Tree::iterator, bool>
Rva00093670Tree::insert_unique( const Rva00093670Pair & );

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	BfmeStringNoCaseLess, _STL::allocator<AsciiString> > Rva00195D30Tree;

// retail 0x00197270, inserting through the _M_insert at 0x00195D30 -- a set of the key
template _STL::pair<Rva00195D30Tree::iterator, bool>
Rva00195D30Tree::insert_unique( const AsciiString & );

struct Rva003D3F90Value
{
	char m_body[ 8 ];
};

typedef _STL::pair<const AsciiString, Rva003D3F90Value> Rva003D3F90Pair;

typedef _STL::_Rb_tree<AsciiString, Rva003D3F90Pair, _STL::_Select1st<Rva003D3F90Pair>,
	BfmeStringNoCaseLess, _STL::allocator<Rva003D3F90Pair> > Rva003D3F90Tree;

// retail 0x003D4320, inserting through the _M_insert at 0x003D3F90
template _STL::pair<Rva003D3F90Tree::iterator, bool>
Rva003D3F90Tree::insert_unique( const Rva003D3F90Pair & );
