// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *first, const void *second, unsigned int count);
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
		const char *data = other.m_data.m_data ? &other.m_data.m_data->data[0] : "";
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

struct Rva0046C540Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva0046C540ExtractKey
{
	const AsciiString &operator()(const Rva0046C540Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva0046C540Value, AsciiString, rts::hash<AsciiString>,
	Rva0046C540ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046C540Value> > Rva0046C540Table;

// Retail 0x00468D80 is the resize body called by the named _M_insert at
// 0x0046C540 through ILT 0x00030E31. The sibling exact resize bodies establish
// the same AsciiString hash and four-byte mapped-value layout.
template void Rva0046C540Table::resize(unsigned int);
