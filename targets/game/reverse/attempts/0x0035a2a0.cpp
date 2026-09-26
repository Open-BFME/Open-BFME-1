// ?d_0035a2a0@@YAXXZ
// partial score=0.84 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class UnicodeString
{
public:
	void set(const UnicodeString &source);
};

bool rvaLookupReleased0035a220(void *owner, AsciiString *name);

static __forceinline const char *rvaAsciiText(const AsciiString *name)
{
	const char *data = *(const char * const *)name;
	return data ? data + 8 : "";
}

struct Rva0035A2A0Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359530StringRecordTable
{
public:
	int findNameIndex(AsciiString *name);

	int *m_nameIndexesBegin;
	int *m_nameIndexesEnd;
	int *m_nameIndexesCapacity;
	Rva0035A2A0Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class Rva0035A2A0Owner
{
public:
	void makeUniqueScriptName(AsciiString *name, UnicodeString *result);

private:
	unsigned char m_head[0x2c];
	Rva00359530StringRecordTable m_nameTable;
};

void Rva0035A2A0Owner::makeUniqueScriptName(
	AsciiString *name, UnicodeString *result)
{
	if (rvaLookupReleased0035a220(this, name))
		return;

	AsciiString candidate;
	int suffix = 0;
	Rva00359530StringRecordTable &table = m_nameTable;
	for (;;)
	{
		++suffix;
		candidate.format(AsciiString("%s %d"), rvaAsciiText(name), suffix);

		int nameIndex = table.findNameIndex(&candidate);
		if (nameIndex >= table.m_nameIndexesEnd - table.m_nameIndexesBegin)
			break;

		int recordIndex = table.m_nameIndexesBegin[nameIndex];
		if (table.m_records[recordIndex].m_name.compare(candidate) != 0 ||
			recordIndex == -1 ||
			table.m_records[recordIndex].m_released)
			break;
	}

	((UnicodeString *)result)->set(*(UnicodeString *)&candidate);
}
