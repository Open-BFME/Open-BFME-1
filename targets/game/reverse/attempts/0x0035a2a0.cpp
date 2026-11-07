// ?d_0035a2a0@@YAXXZ
// partial score=0.8057 date=2026-11-07
// ?d_0035a2a0@@YAXXZ
// partial: 350/350 68 raw diffs shape 0.958/7 (2026-11-07, donor-form ++suffix then text statement)
// ?rvaUniqueName0035a2a0@@YAXPAVRva0035A220Owner@@AAVAsciiString@@@Z (row ?d_0035a2a0@@YAXXZ)
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"

bool rvaLookupReleased0035a220(void *owner, AsciiString *name);

struct Rva00359530Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	bool m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359530StringRecordTable
{
public:
	int findNameIndex(AsciiString *name);

	std::vector<int> m_nameIndexes;
	std::vector<Rva00359530Record> m_records;
	int m_freeHead;
	int m_activeTail;
};

class Rva0035A220Owner
{
public:
	unsigned char m_head[0x2c];
	Rva00359530StringRecordTable m_nameTable;
};

static inline int rvaCompareNames(const AsciiString &self, const AsciiString &other)
{
	int thatLen = other.getLength();
	const char *thatData = other.str();
	int thisLen = self.getLength();
	const char *thisData = self.str();
	int n = thisLen < thatLen ? thisLen : thatLen;
	int c = memcmp(thisData, thatData, n);
	if (c != 0)
		return c;
	return thisLen - thatLen;
}

static inline bool rvaLookupReleasedInline(Rva00359530StringRecordTable *table, AsciiString *name)
{
	unsigned int nameIndex = table->findNameIndex( name );
	unsigned int count = table->m_nameIndexes.size();
	if ( nameIndex < count )
	{
		int recordIndex = table->m_nameIndexes[nameIndex];
		if ( rvaCompareNames(table->m_records[recordIndex].m_name, *name) == 0 && recordIndex != -1 )
			return table->m_records[recordIndex].m_released;
	}
	return true;
}

static __declspec(noinline) void rvaUniqueName0035a2a0(Rva0035A220Owner *owner, AsciiString &name)
{
	if (!rvaLookupReleased0035a220(owner, &name))
	{
		AsciiString candidate;
		int suffix = 0;
		Rva00359530StringRecordTable *table = &owner->m_nameTable;
		do
		{
			++suffix;
			const char *text = name.str();
			candidate.format("%s %d", text, suffix);
		} while (!rvaLookupReleasedInline(table, &candidate));
		name = candidate;
}
}

void rvaUniqueNameStub(Rva0035A220Owner *owner, AsciiString &name)
{
	rvaUniqueName0035a2a0(owner, name);
}
