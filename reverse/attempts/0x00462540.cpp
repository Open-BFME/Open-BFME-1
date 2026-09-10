// ?d_00462540@@YAXXZ
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /MD /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// Retail 0x00462540 is the STLport for_each operation reached by
// _bfme_closeAptScreen.  The call supplies begin/end iterators for the
// hashtable embedded at 0x012F19A4 and a one-string close functor.  The
// mapped record's second AsciiString is at value+0x2c; matching it releases
// that string while the iterator advances through the table.

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <hash_map>

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2,
	unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	public:
	BfmeAsciiStringData *m_data;
};

struct BfmeAptScreenCloseFunctor;
class BFMERetailAsciiString;
bool operator==(const BFMERetailAsciiString &left,
	const BFMERetailAsciiString &right);

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const BFMERetailAsciiString &other)
		: m_string(other.m_string) {}
	~BFMERetailAsciiString() {}

	const char *str() const
	{
		return m_string.m_data ? &m_string.m_data->data[0] : "";
	}

private:
	friend bool operator==(const BFMERetailAsciiString &left,
		const BFMERetailAsciiString &right);
	friend struct BfmeAptScreenCloseFunctor;
	void releaseBuffer();
	StringBase<char> m_string;
};

inline bool operator==(const BFMERetailAsciiString &left,
	const BFMERetailAsciiString &right)
{
	const BfmeAsciiStringData *rightData = right.m_string.m_data;
	const int len = rightData ? rightData->length : 0;
	const char *data = rightData ? &rightData->data[0] : "";
	const BfmeAsciiStringData *leftData = left.m_string.m_data;
	const int myLen = leftData ? leftData->length : 0;
	const char *myData = leftData ? &leftData->data[0] : "";
	const int result = memcmp(myData, data, myLen < len ? myLen : len);
	return result == 0 && myLen == len;
}

struct BfmeAptScreenMapped
{
	unsigned char m_padding[0x28];
	BFMERetailAsciiString m_name;
};

typedef _STL::pair<const BFMERetailAsciiString, BfmeAptScreenMapped>
	BfmeAptScreenRecord;

struct BfmeAptScreenCloseFunctor
{
	BFMERetailAsciiString m_name;

	void operator()(BfmeAptScreenRecord &record) const
	{
		if (record.second.m_name == m_name)
			record.second.m_name.releaseBuffer();
	}
};

namespace rts
{
	template <class T> struct hash
	{
		unsigned int operator()(T value) const
		{
			const char *text = value.str();
			int result = 0;
			while (*text != 0)
			{
				result = result * 5 + *text;
				++text;
			}
			return result;
		}
	};
}

struct BfmeAptScreenExtractKey
{
	const BFMERetailAsciiString &operator()(const BfmeAptScreenRecord &record) const
	{
		return record.first;
	}
};

typedef _STL::hashtable<BfmeAptScreenRecord, BFMERetailAsciiString,
	rts::hash<BFMERetailAsciiString>, BfmeAptScreenExtractKey,
	_STL::equal_to<BFMERetailAsciiString>, _STL::allocator<BfmeAptScreenRecord> >
	BfmeAptScreenTable;

template BfmeAptScreenCloseFunctor _STL::for_each<BfmeAptScreenTable::iterator,
	BfmeAptScreenCloseFunctor>(BfmeAptScreenTable::iterator,
	BfmeAptScreenTable::iterator, BfmeAptScreenCloseFunctor);
