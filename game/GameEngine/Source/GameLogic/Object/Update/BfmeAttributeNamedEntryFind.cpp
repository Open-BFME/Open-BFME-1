// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

#include "ascii_string.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

struct BfmeAttributeNamedEntry
{
	unsigned char m_pad[0x0C];
	AsciiString m_name;
};

struct BfmeAttributeNamedEntryRange
{
	BfmeAttributeNamedEntry **m_begin;
	BfmeAttributeNamedEntry **m_end;
};

class BfmeAttributeNamedEntryFinder
{
public:
	BfmeAttributeNamedEntry *find(const BfmeAttributeNamedEntryRange *range,
		const AsciiString *name) const;
};

BfmeAttributeNamedEntry *BfmeAttributeNamedEntryFinder::find(
		const BfmeAttributeNamedEntryRange *range, const AsciiString *name) const
{
	for (BfmeAttributeNamedEntry **it = range->m_begin; it != range->m_end; ++it) {
		if ((*it)->m_name.StringBase<char>::compare(*name) == 0)
			return *it;
	}
	return 0;
}
