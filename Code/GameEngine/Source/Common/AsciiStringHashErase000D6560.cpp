// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// Retail 0x000D6560 is the key-erase member for the AsciiString hash table
// used by BfmeMapEZC::drop1.  The ILT at 0x00009AA2 and the pair destructor,
// bucket helper, and AsciiString compare calls identify this specialization.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2,
	unsigned int count);
#pragma intrinsic(memcmp)

class Rva000D64A0Mapped;

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ?
			&str.m_data.m_data->data[0] : "";
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

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

typedef _STL::pair<const AsciiString, Rva000D64A0Mapped *> Rva000D6560Pair;
typedef _STL::hashtable<Rva000D6560Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva000D6560Pair>, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000D6560Pair> > Rva000D6560Hashtable;

template unsigned int Rva000D6560Hashtable::erase(const AsciiString &key);
