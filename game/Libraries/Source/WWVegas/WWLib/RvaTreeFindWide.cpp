// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<StringBase<unsigned short>, V>::_M_find for the
// wide-string-keyed tree whose insert_unique bodies live in
// RvaTreeInsertUniqueWide.cpp (retail 0x0068FBE0 / 0x0068FF60, both through
// the _M_insert at 0x0068FAF0).
//
// Tree identity: 0x00690490 calls this body (via ILT 0x00031DD6) and the map
// operator[] at 0x00690370 (via ILT 0x000409D5) on the same two stack maps
// ([esp+0x3c] and [esp+0x30] after one argument push), and that operator[]
// inserts through the hinted insert_unique at 0x0068FF60.  The body itself
// never reads the mapped value, so the address-derived value spelling is kept.
//
// Like the plain insert_unique next door, retail expands the comparison in the
// descent loop and leaves the final candidate check out of line (a call to
// StringBase<unsigned short>::compare through ILT 0x000226EC).  The empty
// literal is g_bfmeEmptyUnicode (0x0107388C).  StringBase is spelled here for
// the same reason as in the insert_unique file.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

template <typename T>
class StringBase
{
public:
	StringBase();
	StringBase( const StringBase<T> &src );
	~StringBase();

	int compare( const StringBase<T> &str ) const
	{
		int thatLen = str.m_data ? str.m_data->length : 0;
		const T *thatData = str.m_data ? &str.m_data->data[ 0 ] : (const T *)L"";
		int thisLen = m_data ? m_data->length : 0;
		const T *thisData = m_data ? &m_data->data[ 0 ] : (const T *)L"";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = 0;
		while ( n > 0 )
		{
			if ( *thisData != *thatData )
			{
				c = *thisData - *thatData;
				break;
			}
			++thisData;
			++thatData;
			--n;
		}
		if ( c != 0 )
			return c;
		return thisLen - thatLen;
	}

	struct Header
	{
		int ref_count;					// +0x00
		unsigned short length;			// +0x04
		unsigned short capacity;		// +0x06
		T data[ 1 ];					// +0x08
	};

	Header *m_data;						// +0x00
};

typedef StringBase<unsigned short> BfmeWideString;

namespace _STL
{
template <> struct less<BfmeWideString>
{
	bool operator()( const BfmeWideString &left, const BfmeWideString &right ) const
	{
		return left.compare( right ) < 0;
	}
};
}

struct Rva0068FAF0Value
{
	char m_body[ 4 ];
};

typedef _STL::pair<const BfmeWideString, Rva0068FAF0Value> Rva0068FAF0Pair;

typedef _STL::_Rb_tree<BfmeWideString, Rva0068FAF0Pair, _STL::_Select1st<Rva0068FAF0Pair>,
	_STL::less<BfmeWideString>, _STL::allocator<Rva0068FAF0Pair> > Rva0068FAF0Tree;

static __forceinline int bfmeWideCompareInline( const BfmeWideString &left,
	const BfmeWideString &right )
{
	int rightLength = right.m_data ? right.m_data->length : 0;
	const unsigned short *rightText = right.m_data ? right.m_data->data :
		(const unsigned short *)L"";
	int leftLength = left.m_data ? left.m_data->length : 0;
	const unsigned short *leftText = left.m_data ? left.m_data->data :
		(const unsigned short *)L"";
	int count = leftLength < rightLength ? leftLength : rightLength;
	int result = 0;
	while ( count > 0 )
	{
		if ( *leftText != *rightText )
		{
			result = (int)*leftText - (int)*rightText;
			break;
		}
		++leftText;
		++rightText;
		--count;
	}
	if ( result != 0 )
		return result;
	return leftLength - rightLength;
}

template <>
template <>
_STL::_Rb_tree_node<Rva0068FAF0Pair> *
Rva0068FAF0Tree::_M_find<BfmeWideString>( const BfmeWideString &key ) const
{
	_Link_type result = this->_M_header._M_data;
	_Link_type node = _M_root();
	while ( node != 0 )
	{
		if ( bfmeWideCompareInline( _S_key( node ), key ) >= 0 )
		{
			result = node;
			node = _S_left( node );
		}
		else
			node = _S_right( node );
	}
	if ( result == this->_M_header._M_data || key.compare( _S_key( result ) ) < 0 )
		result = this->_M_header._M_data;
	return result;
}
