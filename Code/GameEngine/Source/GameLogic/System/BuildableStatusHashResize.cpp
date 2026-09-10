// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Focused ordinary-C++ reconstruction of the BuildableStatus map resize at
// retail RVA 0x00389C00. The public map is declared in GameLogic.h; expanding
// it to the underlying STLport hashtable isolates this one emitted member.

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
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	const char *str() const
	{
		return m_string.m_data ? &m_string.m_data->data[0] : "";
	}

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

template <class T>
struct equal_to;

template <>
struct equal_to<AsciiString>
{
	Bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left == right;
	}
};
}

enum BuildableStatus
{
	BSTATUS_YES = 0,
	BSTATUS_IGNORE_PREREQUISITES,
	BSTATUS_NO,
	BSTATUS_ONLY_BY_AI,
	BSTATUS_NUM_TYPES
};

typedef _STL::pair<const AsciiString, BuildableStatus> BuildableStatusPair;
typedef _STL::hashtable<BuildableStatusPair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<BuildableStatusPair>, rts::equal_to<AsciiString>,
	_STL::allocator<BuildableStatusPair> > BuildableStatusMap;

template void BuildableStatusMap::resize(unsigned int);
