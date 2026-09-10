// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// Open-BFME: key erase for the AptScreenRef hash table, retail 0x00461040.
// The caller is _bfme_closeAptScreen (0x004629A0, through ILT 0x0000F547),
// and the table's matching operator[] is the already-matched 0x00461A00
// Rva00461A00HashIndex instantiation.  The retail body ends at ret 4 at
// 0x00461179; the three bytes of trailing padding are outside this body.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}
	~AsciiString();

	int compare(const AsciiString &str) const
	{
		const int len = str.m_string.m_data ? str.m_string.m_data->length : 0;
		const char *data = str.m_string.m_data ?
			&str.m_string.m_data->data[0] : "";
		const int myLen = m_string.m_data ? m_string.m_data->length : 0;
		const char *myData = m_string.m_data ? &m_string.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

	StringBase<char> m_string;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

class Rva00461A00Counted
{
public:
	virtual void release(unsigned int deleting);
	int m_references;
};

struct Rva00461A00Mapped
{
	Rva00461A00Mapped() : m_counted(0) {}
	Rva00461A00Mapped(const Rva00461A00Mapped &other) : m_counted(other.m_counted)
	{
		if (m_counted)
			++m_counted->m_references;
	}
	~Rva00461A00Mapped()
	{
		if (m_counted && --m_counted->m_references <= 0)
			m_counted->release(1);
	}

	Rva00461A00Counted *m_counted;
};

namespace rts
{
	template <class T> struct hash;
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};
}

typedef _STL::pair<const AsciiString, Rva00461A00Mapped> Rva00461A00Pair;
typedef _STL::hashtable<Rva00461A00Pair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<Rva00461A00Pair>, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00461A00Pair> > Rva00461A00HashTable;

template unsigned int Rva00461A00HashTable::erase(const AsciiString &key);
