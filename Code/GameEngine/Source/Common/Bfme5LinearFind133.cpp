// cl: /DNDEBUG /MD /EHs-c-
// 0x00141520 133 bytes linear find - AsciiString vector search

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;
#define NULL 0

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// +4
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Int compare(const AsciiString &that) const
	{
		Int thatLen = that.m_data ? that.m_data->m_len : 0;
		const char *thatData = that.m_data ? (const char *)(that.m_data + 1) : "";
		Int thisLen = m_data ? m_data->m_len : 0;
		const char *thisData = m_data ? (const char *)(m_data + 1) : "";
		Int n = thisLen < thatLen ? thisLen : thatLen;
		Int c = memcmp(thisData, thatData, n);
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}
	BfmeStringData *m_data;
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return a.compare(b) == 0; }

struct Entry
{
	int field0;						// +0
	AsciiString key;					// +4
	int field1;						// +8
	int field2;						// +12
	int field3;						// +16
}; // size 0x14

class Container
{
	Entry *m_begin;					// +0
	Entry *m_end;					// +4
public:
	Entry *find(const AsciiString &name) const;
};

// ?find@Container@@QBEPAUEntry@@ABVAsciiString@@@Z
Entry *Container::find(const AsciiString &name) const
{
	Entry *it;
	for (it = m_begin; it != m_end; ++it)
		if (it->key == name)
			return it;
	return NULL;
}
