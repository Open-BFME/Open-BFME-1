// ?resize@?$hashtable@URva00461250Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva00461250ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva00461250Value@@@7@@_STL@@QAEXI@Z
// The caller at 0x00461250 is the matching _M_insert specialization.
// Its value has an AsciiString key and a four-byte mapped field, so this
// body is the STLport resize specialization for that table.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
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

struct Rva00461250Value
{
	AsciiString m_key;
	Int m_mapped;
};

struct Rva00461250ExtractKey
{
	const AsciiString &operator()(const Rva00461250Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva00461250Value, AsciiString,
	rts::hash<AsciiString>, Rva00461250ExtractKey,
	_STL::equal_to<AsciiString>, _STL::allocator<Rva00461250Value> >
	Rva00461250Table;

template void Rva00461250Table::resize(unsigned int);

struct Rva006A7AD0Value
{
	AsciiString m_key;
	Int m_mapped;
};

struct Rva006A7AD0ExtractKey
{
	const AsciiString &operator()(const Rva006A7AD0Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva006A7AD0Value, AsciiString,
	rts::hash<AsciiString>, Rva006A7AD0ExtractKey,
	_STL::equal_to<AsciiString>, _STL::allocator<Rva006A7AD0Value> >
	Rva006A7AD0Table;

template void Rva006A7AD0Table::resize(unsigned int);
