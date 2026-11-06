// ?d_0035a060@@YAXXZ
// partial score=0.8 date=2026-11-06
// ?rvaUniqueName0035a060@@YAXPAVRva00359FE0Owner@@PAVAsciiString@@@Z (row ?d_0035a060@@YAXXZ)
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"

bool rvaLookupReleased00359fe0(void *owner, AsciiString *name);

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	bool m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class Rva00359330StringRecordTable
{
public:
	int findNameIndex(AsciiString *name);

	std::vector<int> m_nameIndexes;
	std::vector<Rva00359330Record> m_records;
	int m_freeHead;
	int m_activeTail;
};

class Rva00359FE0Owner
{
public:
	unsigned char m_head[0xc];
	Rva00359330StringRecordTable m_nameTable;
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

static inline bool rvaLookupReleasedInline(Rva00359330StringRecordTable *table, AsciiString *name)
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

static __declspec(noinline) void rvaUniqueName0035a060(Rva00359FE0Owner *owner, AsciiString *name)
{
	if (rvaLookupReleased00359fe0(owner, name))
		return;

	AsciiString candidate;
	int suffix = 0;
	Rva00359330StringRecordTable *table = &owner->m_nameTable;
	do
	{
		const char *text = name->str();
		++suffix;
		candidate.format(AsciiString("%s %d"), text, suffix);
	} while (!rvaLookupReleasedInline(table, &candidate));
	name->set(candidate);
}

void rvaUniqueNameStub(Rva00359FE0Owner *owner, AsciiString *name)
{
	rvaUniqueName0035a060(owner, name);
}
