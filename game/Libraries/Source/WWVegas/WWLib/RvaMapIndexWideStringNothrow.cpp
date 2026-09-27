// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Retail 0x0054FA30 (169 bytes): STLport map<UnicodeString, enum>::operator[] from a
// TU whose array/scalar delete is declared nothrow (docs/shape_levers.md). It was
// filed as the AsciiString map, but every string call it makes is wide:
// StringBase<G>::compare (ILT 0x000226EC -> 0x0005FFA0), the wide copy
// constructor (0x00888400) and the wide release (0x008881D0). Its tree is the one
// RvaTreeInsertUniqueWide.cpp matched: _M_lower_bound 0x0054EE40 (ILT 0x0003FABC)
// and the hinted insert_unique 0x0054F3F0 (ILT 0x00033D5C).
//
// Two details are load-bearing for the shape. The key derives from StringBase, as
// BFME's UnicodeString does, and the mapped type is a scalar; a bare StringBase key
// or a struct value does not reproduce retail. compare's body is visible but stays
// out of line, as in retail: the compiler has to see that it cannot throw, or the
// EH state is scheduled differently.
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
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
	StringBase( const StringBase<T> &src ) throw();
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

enum Rva0054FA30Mapped { Rva0054FA30MappedZero = 0 };

typedef _STL::map<UnicodeString, Rva0054FA30Mapped, _STL::less<UnicodeString>,
	_STL::allocator<_STL::pair<const UnicodeString, Rva0054FA30Mapped> > > Rva0054FA30Map;

// retail 0x0054FA30
template Rva0054FA30Mapped &Rva0054FA30Map::operator[]( const UnicodeString & );
