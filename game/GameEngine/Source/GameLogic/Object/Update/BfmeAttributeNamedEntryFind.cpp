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
		if ((*it)->m_name.compare(*name) == 0)
			return *it;
	}
	return 0;
}
