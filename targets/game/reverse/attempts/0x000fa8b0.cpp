// ?findBuildIndex@Rva000FA8B0@@QAEHPBVRva000FA8B0Query@@H@Z
// partial score=0.2606 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;

extern "C" int memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)
extern const char Rva006A16B0Empty[];

struct Rva000FA8B0StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

struct Rva000FA8B0String
{
	Rva000FA8B0StringData *m_data;

	int compare(const Rva000FA8B0String &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherData = other.m_data ? other.m_data->m_data : Rva006A16B0Empty;
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisData = m_data ? m_data->m_data : Rva006A16B0Empty;
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisData, otherData, length);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}
};

class Rva000FA8B0Query
{
public:
	char m_prefix00[0x20];
	Rva000FA8B0String m_value20;
};

struct Rva000FA8B0Entry
{
	Rva000FA8B0String m_value00;
	char m_prefix04[0x3c - sizeof(Rva000FA8B0String)];
	Int m_key;
	char m_prefix40[0x20];
};

class Rva000FA8B0
{
public:
	int findBuildIndex(const Rva000FA8B0Query *query, Int requestedIndex);

private:
	void *m_vtable;
	Rva000FA8B0Entry *m_begin;
	Rva000FA8B0Entry *m_end;
};

int Rva000FA8B0::findBuildIndex(const Rva000FA8B0Query *query, Int requestedIndex)
{
	Int index = 0;
	Rva000FA8B0Entry *entry = m_begin;
	Rva000FA8B0Entry *end = m_end;
	if (entry != end)
	{
		Rva000FA8B0StringData * volatile savedName =
			query->m_value20.m_data;
		Rva000FA8B0String queryName;
		queryName.m_data = savedName;
		goto compare;
		do
		{
			queryName.m_data = savedName;
		compare:
			if (entry->m_value00.compare(queryName) == 0)
			{
				if (requestedIndex == -1 || requestedIndex == entry->m_key)
					return index;
			}
			++index;
			++entry;
		} while (entry != end);
	}
	return -1;
}
