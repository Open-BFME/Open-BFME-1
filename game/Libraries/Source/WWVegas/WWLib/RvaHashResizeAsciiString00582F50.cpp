// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

typedef int Int;

extern "C" int __cdecl memcmp(const void *left, const void *right,
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
		const int otherLength = other.m_data.m_data
			? other.m_data.m_data->length : 0;
		const char *otherText = other.m_data.m_data
			? &other.m_data.m_data->data[0] : "";
		const int length = m_data.m_data ? m_data.m_data->length : 0;
		const char *text = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(text, otherText,
			length < otherLength ? length : otherLength);
		if (result != 0)
			return result;
		return length - otherLength;
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

struct Rva00583B30Value
{
	AsciiString m_key;
	char m_mapped[16];
};

struct Rva00583B30ExtractKey
{
	const AsciiString &operator()(const Rva00583B30Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva00583B30Value, AsciiString,
	rts::hash<AsciiString>, Rva00583B30ExtractKey,
	_STL::equal_to<AsciiString>, _STL::allocator<Rva00583B30Value> >
	Rva00583B30Table;

template void Rva00583B30Table::resize(unsigned int);
