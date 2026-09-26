// ?resize@?$hashtable@URva00614BC0Value@@VAsciiString@@U?$hash@VAsciiString@@@rts@@URva00614BC0ExtractKey@@U?$equal_to@VAsciiString@@@_STL@@V?$allocator@URva00614BC0Value@@@7@@_STL@@QAEXI@Z
// The _M_insert specialization at 0x00614BC0 calls this resize body through
// its ILT.  Its value has an AsciiString key and a four-byte mapped field.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

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

	const char *str() const
	{
		return m_data.m_data ? &m_data.m_data->data[0] : "";
	}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ? &str.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
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

template <>
struct hash<AsciiString>
{
	unsigned int operator()(AsciiString value) const
	{
		return static_cast<unsigned int>(_STL::__stl_hash_string(value.str()));
	}
};
}

struct Rva00614BC0Value
{
	AsciiString m_key;
	Int m_mapped;
};

struct Rva00614BC0ExtractKey
{
	const AsciiString &operator()(const Rva00614BC0Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva00614BC0Value, AsciiString, rts::hash<AsciiString>,
	Rva00614BC0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00614BC0Value> > Rva00614BC0Table;

template void Rva00614BC0Table::resize(unsigned int);
