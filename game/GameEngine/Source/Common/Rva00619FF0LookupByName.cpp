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

extern const char Rva006A16B0Empty[];

class AsciiString
{
public:
	BfmeAsciiStringData *m_data;

	int compare(const char *text) const
	{
		int rightLength = text ? (int)strlen(text) : 0;
		int leftLength = m_data ? m_data->m_length : 0;
		const char *leftText = m_data ? m_data->m_text : Rva006A16B0Empty;
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

extern LookupListRec g_01116F40[];

// ?Rva00619FF0LookupByName@@YAHABVAsciiString@@@Z
int __cdecl Rva00619FF0LookupByName(const AsciiString &name)
{
	const char *recordName = g_01116F40[0].name;
	LookupListRec *record = g_01116F40;
	for (; recordName; ++record)
	{
		if (name.compare(recordName) == 0)
			return record->value;
		recordName = record[1].name;
	}
	return 0;
}
