// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport

// Open-BFME: key erase for the address-derived 0x0046C2A0 AsciiString table.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}
	~AsciiString();

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

class Rva0046C2A0Counted
{
public:
	virtual void release(unsigned int deleting);
	int m_references;
};

struct Rva0046C2A0Mapped
{
	Rva0046C2A0Mapped() : m_counted(0), m_value(0) {}
	Rva0046C2A0Mapped(const Rva0046C2A0Mapped &other) :
		m_counted(other.m_counted), m_value(other.m_value)
	{
		if (m_counted)
			++m_counted->m_references;
	}
	~Rva0046C2A0Mapped()
	{
		if (m_counted && --m_counted->m_references <= 0)
			m_counted->release(1);
	}

	Rva0046C2A0Counted *m_counted;
	void *m_value;
};

namespace rts
{
	template <class T> struct hash;
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};
}

typedef _STL::pair<const AsciiString, Rva0046C2A0Mapped> Rva0046C2A0Pair;
typedef _STL::hashtable<Rva0046C2A0Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva0046C2A0Pair>, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046C2A0Pair> > Rva0046C2A0HashTable;

template unsigned int Rva0046C2A0HashTable::erase(const AsciiString &key);
