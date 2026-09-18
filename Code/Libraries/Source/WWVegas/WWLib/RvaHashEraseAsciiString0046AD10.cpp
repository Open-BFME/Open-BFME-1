// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

// STLport hashtable erase(const AsciiString&) at retail 0x0046AD10.
// The bucket helper and pair destructor identify the Rva0046AF20 table.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

typedef int Int;
typedef bool Bool;

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

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

struct Rva0046AF20Value
{
	AsciiString m_key;
	int m_mapped;
};

#pragma comment(linker, "/alternatename:??1Rva0046AF20Value@@QAE@XZ=?j_000335fa@@YAXXZ")

struct Rva0046AF20ExtractKey
{
	const AsciiString &operator()(const Rva0046AF20Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva0046AF20Value, AsciiString, rts::hash<AsciiString>,
	Rva0046AF20ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046AF20Value> > Rva0046AF20HashTable;

template unsigned int Rva0046AF20HashTable::erase(const AsciiString &key);
