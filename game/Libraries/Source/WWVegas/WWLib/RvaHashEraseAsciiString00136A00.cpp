// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME: STLport hashtable erase(const AsciiString&) at retail 0x00136A00.
// The ThingFactory table uses a ThingTemplate pointer as its four-byte mapped
// value.  Its retail body walks the bucket, compares the inline string fields,
// destroys matching pairs, and returns the number of removed nodes.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ? &str.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

	StringBase<char> m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

class ThingTemplate;

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

typedef _STL::pair<const AsciiString, ThingTemplate *> Rva00136A00Pair;
typedef _STL::hashtable<Rva00136A00Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva00136A00Pair>, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00136A00Pair> > Rva00136A00HashTable;

template unsigned int Rva00136A00HashTable::erase(const AsciiString &key);
