// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

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

inline bool operator==(const AsciiString &a, const AsciiString &b)
{
	return a.compare(b) == 0;
}

class Rva003B9100
{
public:
	bool contains(const AsciiString &name) const;

private:
	char m_pad[0x0C];
	_STL::vector<AsciiString> m_vec;
};

bool Rva003B9100::contains(const AsciiString &name) const
{
	for (unsigned int i = 0; i < m_vec.size(); ++i)
		if (m_vec[i] == name)
			return true;
	return false;
}
