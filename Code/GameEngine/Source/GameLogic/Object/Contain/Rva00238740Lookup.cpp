// Retail 0x00238740 searches the array of entry pointers described by the
// begin/end fields at the table view's +0x230/+0x234. Each entry starts with
// an AsciiString key; its owner and semantic method name remain unproven, so
// keep the class address-derived. The by-value AsciiString parameter releases
// through the established StringBase<char> cleanup on normal and EH exits.
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct RetailStringData
{
	int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
	Int compare(const AsciiString &other) const
	{
		Int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherText = other.m_data ? other.m_data->m_text : "";
		Int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : "";
		Int count = thisLength < otherLength ? thisLength : otherLength;
		Int result = memcmp(thisText, otherText, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	~AsciiString();
	RetailStringData *m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

struct Rva00238740Entry
{
	AsciiString m_key;
	void *m_value;
};

struct Rva00238740Table
{
	unsigned char m_unmodeled_000[0x230];
	Rva00238740Entry **m_begin;
	Rva00238740Entry **m_end;
};

class Rva00238740Lookup
{
public:
	void *m_vtable;
	Rva00238740Table *m_table;

	Rva00238740Entry *find(AsciiString name);
};

Rva00238740Entry *Rva00238740Lookup::find(AsciiString name)
{
	for (Rva00238740Entry **it = m_table->m_begin;
		it != m_table->m_end; ++it)
	{
		Rva00238740Entry *entry = *it;
		if (entry->m_key == name)
			return entry;
	}
	return 0;
}
