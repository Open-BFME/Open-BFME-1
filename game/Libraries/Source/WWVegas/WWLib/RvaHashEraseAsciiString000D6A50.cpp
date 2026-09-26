// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// Open-BFME: STLport hashtable erase(const AsciiString&) at retail 0x000D6A50.
// The caller is BfmeThingEZC::eraseMaps, and the pinned bucket helper uses the
// CommandButton pointer specialization. The 12-byte node holds an AsciiString
// key and one opaque four-byte mapped value.

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

class CommandButton;

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};

template <class T>
struct equal_to
{
	bool operator()(const T &left, const T &right) const
	{
		return left == right;
	}
};
}

typedef _STL::pair<const AsciiString, const CommandButton *> Rva000D6A50Pair;
typedef _STL::hashtable<Rva000D6A50Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva000D6A50Pair>, rts::equal_to<AsciiString>,
	_STL::allocator<Rva000D6A50Pair> > Rva000D6A50Hashtable;

template unsigned int Rva000D6A50Hashtable::erase(const AsciiString &key);
