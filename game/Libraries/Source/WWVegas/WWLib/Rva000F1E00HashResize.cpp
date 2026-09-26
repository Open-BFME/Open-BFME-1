// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// The caller at 0x000F6C10 proves the Rva000F6C10 hashtable resize identity.
// The body has the same field and helper-call shape as the existing GameSpy
// resize specialization, but this source keeps the caller's struct name.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *first, const void *second,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	const char *str() const
	{
		return m_data.m_data ? &m_data.m_data->data[0] : "";
	}

	int compare(const AsciiString &other) const
	{
		const int length = other.m_data.m_data ? other.m_data.m_data->length : 0;
		const char *data = other.m_data.m_data
			? &other.m_data.m_data->data[0] : "";
		const int myLength = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLength < length ? myLength : length);
		if (result != 0)
			return result;
		return myLength - length;
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

template <>
struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const
	{
		return static_cast<unsigned int>(_STL::__stl_hash_string(value.str()));
	}
};
}

#include "unicode_string.h"

struct Rva000F6C10Value
{
	Rva000F6C10Value(const Rva000F6C10Value &other);
	~Rva000F6C10Value();

	AsciiString m_name;
	UnicodeString m_translatedName;
	int m_groupID;
	int m_numWaiting;
	int m_maxWaiting;
	int m_numGames;
	int m_numPlaying;
};

#pragma comment(linker, "/alternatename:??0Rva000F6C10Value@@QAE@ABU0@@Z=??0GameSpyGroupRoom@@QAE@ABV0@@Z")

struct Rva000F6C10ExtractKey
{
	const AsciiString &operator()(const Rva000F6C10Value &entry) const
	{
		return entry.m_name;
	}
};

typedef _STL::hashtable<Rva000F6C10Value, AsciiString,
	rts::hash<AsciiString>, Rva000F6C10ExtractKey,
	_STL::equal_to<AsciiString>, _STL::allocator<Rva000F6C10Value> >
	Rva000F6C10Table;

template void Rva000F6C10Table::resize(unsigned int);
