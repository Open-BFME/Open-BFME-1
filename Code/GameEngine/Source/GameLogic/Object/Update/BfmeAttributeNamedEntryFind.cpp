// cl: /DNDEBUG /MD /EHsc

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

class AsciiString
{
public:
	Int getLength() const { return m_data ? m_data->m_len : 0; }
	const char *str() const { return m_data ? (const char *)(m_data + 1) : ""; }
	Int compare(const AsciiString &other) const
	{
		Int otherLength = other.getLength();
		const char *otherData = other.str();
		Int thisLength = getLength();
		const char *thisData = str();
		Int shorter = thisLength < otherLength ? thisLength : otherLength;
		Int result = memcmp(thisData, otherData, shorter);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}
private:
	BfmeAsciiStringData *m_data;
};

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
