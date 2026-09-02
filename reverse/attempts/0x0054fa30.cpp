// ??A?$map@V?$StringBase@G@@URva0054EF10Value@@U?$less@V?$StringBase@G@@@_STL@@V?$allocator@U?$pair@$$CBV?$StringBase@G@@URva0054EF10Value@@@_STL@@@4@@_STL@@QAEAAURva0054EF10Value@@ABV?$StringBase@G@@@Z
// partial score=0.87 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport map<StringBase<unsigned short>, V>::operator[] -- the
// wide-string sibling of RvaMapIndexAsciiString.cpp.  169 bytes at 0x0054FA30.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

template <typename T>
class StringBase
{
public:
	StringBase();
	StringBase( const StringBase<T> &src );
	~StringBase();

	int compare( const StringBase<T> &str ) const;

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
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

struct Rva0054EF10Value
{
	char m_body[ 4 ];
};

typedef _STL::map<BfmeWideString, Rva0054EF10Value, _STL::less<BfmeWideString>,
	_STL::allocator<_STL::pair<const BfmeWideString, Rva0054EF10Value> > > Rva0054EF10Map;

// retail 0x0054FA30, over the tree whose _M_lower_bound is at 0x0054EE40
template Rva0054EF10Value &Rva0054EF10Map::operator[]( const BfmeWideString & );
