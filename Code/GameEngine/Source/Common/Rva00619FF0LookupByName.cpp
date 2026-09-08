// cl: /DNDEBUG /MD /EHsc

// The LivingWorldRegion field table names RegionBonus and routes its parser
// through ILT 0x0003AD23 to this lookup. The table at 0x01116F40 maps the
// retail names None, Resource, Army, and Legendary to their integer values.

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_length;
	unsigned short m_pad;
	char m_text[1];
};

class AsciiString
{
public:
	BfmeAsciiStringData *m_data;

	int compare(const char *text) const
	{
		int rightLength = text ? (int)strlen(text) : 0;
		int leftLength = m_data ? m_data->m_length : 0;
		const char *leftText = m_data ? m_data->m_text : (const char *)0x0107388B;
		int length = leftLength < rightLength ? leftLength : rightLength;
		int difference = memcmp(leftText, text, length);
		if (difference != 0)
			return difference;
		return leftLength - rightLength;
	}
};

struct LookupListRec
{
	const char *name;
	int value;
};

// ?Rva00619FF0LookupByName@@YAHABVAsciiString@@@Z
int __cdecl Rva00619FF0LookupByName(const AsciiString &name)
{
	const char *recordName = *(const char **)0x01116F40;
	LookupListRec *record = (LookupListRec *)0x01116F40;
	for (; recordName; ++record)
	{
		if (name.compare(recordName) == 0)
			return record->value;
		recordName = record[1].name;
	}
	return 0;
}
