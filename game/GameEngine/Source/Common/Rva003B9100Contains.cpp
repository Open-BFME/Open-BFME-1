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

// Retail 0x003B9200 (79 bytes, ret 4), reached only through ILT 0x00033889
// from Rva003BAA70Owner::append.  The receiver is the same 36-byte record as
// Rva003B9100 (the caller passes two elements of one vector), so it carries the
// same STLport vector<AsciiString> at +0x0C; the body asks the other record
// whether it contains each of this record's strings.  The address-derived class
// view keeps the caller's pinned mangled name; identity is not recovered.
class Rva003B9200Owner
{
public:
	bool rva003B9200(const Rva003B9100 *other) const;

private:
	char m_pad[0x0C];
	_STL::vector<AsciiString> m_vec;
};

bool Rva003B9200Owner::rva003B9200(const Rva003B9100 *other) const
{
	for (unsigned int i = 0; i < m_vec.size(); ++i)
		if (other->contains(m_vec[i]))
			return true;
	return false;
}
