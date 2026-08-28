// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport hash_map<AsciiString, V>::operator[] -- nine bodies of
// 142 bytes that carried only a machine byte-dump row.
//
// The shape is STLport's own: find the key, and on a miss build a value_type
// from the key and a default-constructed mapped half and hand it to
// _M_insert; either way the result is the address of the mapped half, at +8 of
// the node on the hit path and +4 of the returned value on the miss path.  The
// SEH prologue and the trailing destructor belong to that temporary.
//
// Neither table needs guessing: each body calls a _M_find and a _M_insert that
// are already converted in RvaHashFindAsciiString.cpp and
// RvaHashInsertAsciiString.cpp, and those two name the table.  The mapped type
// is four bytes wide -- retail stores its default-constructed value with a
// dword store -- and it is an ENUMERATION rather than a struct, because a class
// type makes that value a temporary MSVC must keep alive across the key's copy
// constructor.  Each is named for the _M_insert it belongs to.
//
// Those two conversions spell the table through an extract-key functor over an
// opaque value; a hash_map spells it as a pair and _Select1st, and only one
// spelling can be in one file, so each callee gets a pin at the ILT thunk this
// body reaches.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_string.m_data ? str.m_string.m_data->length : 0;
		const char *data = str.m_string.m_data ? &str.m_string.m_data->data[0] : "";
		const int myLen = m_string.m_data ? m_string.m_data->length : 0;
		const char *myData = m_string.m_data ? &m_string.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_string;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(T value) const;
};
}

enum Rva000D6C60Mapped { Rva000D6C60MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva000D6C60Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva000D6C60Mapped> > > Rva000D6C60Map;

// retail 0x000D9870, finding through 0x000D7250 and inserting through 0x000D6C60
template Rva000D6C60Mapped &Rva000D6C60Map::operator[]( const AsciiString & );

enum Rva001360E0Mapped { Rva001360E0MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva001360E0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva001360E0Mapped> > > Rva001360E0Map;

// retail 0x00137750, finding through 0x001366A0 and inserting through 0x001360E0
template Rva001360E0Mapped &Rva001360E0Map::operator[]( const AsciiString & );

enum Rva0038EE10Mapped { Rva0038EE10MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva0038EE10Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva0038EE10Mapped> > > Rva0038EE10Map;

// retail 0x00390750, finding through 0x0038BF10 and inserting through 0x0038EE10
template Rva0038EE10Mapped &Rva0038EE10Map::operator[]( const AsciiString & );

enum Rva004613F0Mapped { Rva004613F0MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva004613F0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva004613F0Mapped> > > Rva004613F0Map;

// retail 0x00461E00, finding through 0x00460CD0 and inserting through 0x004613F0
template Rva004613F0Mapped &Rva004613F0Map::operator[]( const AsciiString & );

enum Rva00469D20Mapped { Rva00469D20MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva00469D20Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00469D20Mapped> > > Rva00469D20Map;

// retail 0x0046B660, finding through 0x0046A470 and inserting through 0x00469D20
template Rva00469D20Mapped &Rva00469D20Map::operator[]( const AsciiString & );

enum Rva00469FC0Mapped { Rva00469FC0MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva00469FC0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00469FC0Mapped> > > Rva00469FC0Map;

// retail 0x0046B750, finding through 0x0046A540 and inserting through 0x00469FC0
template Rva00469FC0Mapped &Rva00469FC0Map::operator[]( const AsciiString & );

enum Rva00614D10Mapped { Rva00614D10MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva00614D10Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00614D10Mapped> > > Rva00614D10Map;

// retail 0x006151B0, finding through 0x00613BB0 and inserting through 0x00614D10
template Rva00614D10Mapped &Rva00614D10Map::operator[]( const AsciiString & );

enum Rva00693020Mapped { Rva00693020MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva00693020Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00693020Mapped> > > Rva00693020Map;

// retail 0x00693880, finding through 0x006931A0 and inserting through 0x00693020
template Rva00693020Mapped &Rva00693020Map::operator[]( const AsciiString & );

enum Rva006A7AD0Mapped { Rva006A7AD0MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva006A7AD0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva006A7AD0Mapped> > > Rva006A7AD0Map;

// retail 0x006AC440, finding through 0x006A7F80 and inserting through 0x006A7AD0
template Rva006A7AD0Mapped &Rva006A7AD0Map::operator[]( const AsciiString & );
