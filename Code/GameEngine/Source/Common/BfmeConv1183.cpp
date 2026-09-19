// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// Open-BFME5 conversions.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" int __cdecl memcmp(const void *first, const void *second,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

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
}

struct Rva00469D20Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00469D20ExtractKey
{
	const AsciiString &operator()(const Rva00469D20Value &entry) const
	{
		return entry.m_key;
	}
};

typedef _STL::hashtable<Rva00469D20Value, AsciiString, rts::hash<AsciiString>,
	Rva00469D20ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00469D20Value> > BfmeList1183HashTable;

class BfmeStr1183
{
public:
	void bfmeFree1183(void);
	int m_bfme00;
};

struct BfmeSlot1183
{
	BfmeStr1183 m_bfme00;
	BfmeStr1183 m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	unsigned char m_bfme10;
	char m_bfmePad[3];
};

class BfmeList1183
{
public:
	void bfmeRemove1183(BfmeSlot1183 *s)
	{
		reinterpret_cast<BfmeList1183HashTable *>(this)->erase(
			*reinterpret_cast<const AsciiString *>(s));
	}
};

class BfmeW1183
{
public:
	bool bfmeClose1183(unsigned int i);
	void bfmeHide1183(unsigned int i);
	char m_bfmePad0[0x58];
	BfmeList1183 m_bfme58;
	char m_bfmePad1[0x4c];
	BfmeSlot1183 m_bfmeA8[12];
};

bool BfmeW1183::bfmeClose1183(unsigned int i)
{
	BfmeSlot1183 *s;

	if (i >= 0xc)
		return false;

	s = &m_bfmeA8[i];

	if (s->m_bfme0c == -1)
		return false;

	if (s->m_bfme10 & 2)
		bfmeHide1183(i);

	m_bfme58.bfmeRemove1183(s);
	s->m_bfme00.bfmeFree1183();
	s->m_bfme04.bfmeFree1183();
	s->m_bfme10 &= 0xf4;
	s->m_bfme08 = 0;
	s->m_bfme0c = -1;

	return true;
}
