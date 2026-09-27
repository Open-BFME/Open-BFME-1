// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x00690370 (231 bytes): STLport
// map<UnicodeString, UnicodeString>::operator[](const UnicodeString &).
//
// The name is the ledger's own for this address, and the body confirms it: a
// wide-key tree (key at node+0x10, mapped at +0x14, both one header pointer),
// a single descent through _M_lower_bound, one out-of-line StringBase<G>::
// compare, then the hinted insert_unique with a pair built from a copy of the
// argument and a default-constructed mapped value, and three out-of-line
// releases. The only caller, ?d_00690490, is a LANGameInfo.cpp-shaped body and
// the funclet at 0x00C46F00 is filed in game/GameEngine/Source/GameNetwork/
// LANGameInfo.cpp under this exact parent symbol, whose Zero Hour source
// declares `std::map<UnicodeString, UnicodeString> oldLogins, oldMachines;`.
//
// Its tree is the one RvaTreeInsertUniqueWide.cpp matched: _M_lower_bound
// 0x0068FA20 (ILT 0x00015023) and the hinted insert_unique 0x0068FF60
// (ILT 0x0003DC21).
//
// Two shape levers are load-bearing, and both are EH-shaped rather than
// layout-shaped. The comparison must stay out of line (the comparator calls
// the member, it does not expand it). The copy constructor must be left able to
// throw: retail registers a separate EH state around each of its three
// constructor calls and carries a real scope table, and a throw() on the copy
// constructor deletes one of those state stores, leaving the body 5 bytes short
// at 226 with `push 0` for the scope table.

void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#include <stl/_config.h>
// Retail default-constructs the mapped value in place (the zero store ahead of
// both copy constructors), which is the `_Tp()` form of _STLP_DEFAULT_CONSTRUCTED.
// stl_msvc.h selects the __default_constructed((_Tp*)0) workaround instead.
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

template <typename T>
class StringBase
{
	friend class UnicodeString;
public:
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
private:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &src );
	~StringBase();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};
	Header *m_data;
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &that ) : StringBase<unsigned short>( that ) {}
	~UnicodeString() {}
};

namespace _STL
{
template <> struct less<UnicodeString>
{
	bool operator()( const UnicodeString &left, const UnicodeString &right ) const
	{
		return left.compare( right ) < 0;
	}
};
}

typedef std::map<UnicodeString, UnicodeString, std::less<UnicodeString>,
	std::allocator<std::pair<const UnicodeString, UnicodeString> > > UnicodeStringMap;

// retail 0x00690370
template UnicodeString &UnicodeStringMap::operator[]( const UnicodeString & );
