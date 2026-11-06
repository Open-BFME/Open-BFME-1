// ?d_0035df10@@YAXXZ
// partial score=1.0 date=2026-11-06
// ?parse@Rva0035DF10ScriptParser@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z (row ?d_0035df10@@YAXXZ)
// partial: the caller 0x0035DF10 is probe-EXACT (227/227, relocations masked) but it cannot
// land until the compiler-private static helper rvaUniqueName0035a2a0 (0x0035A2A0, owner in
// ECX, name on the stack, caller cleans) also matches; that helper is 0.917 shape here.
// Handoff: targets/game/reverse/attempt_support/0x0035a2a0-20261106-unique-name-helper.md
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"

class DataChunkInput
{
public:
	AsciiString readAsciiString();
};

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	unsigned short version;
	int dataSize;
};

class Xfer;
class Script
{
public:
	virtual void xfer( Xfer *xfer );
	bool Rva0035C0C0( DataChunkInput &file, unsigned short version );
};

struct Rva0035DF10ScriptNode
{
	Rva0035DF10ScriptNode *m_next;
	Script m_script;
};

struct Rva0035D800Node
{
	Rva0035D800Node *m_next;
	int m_index;
	int m_extra;
};

class Rva0035D800
{
public:
	Rva0035D800Node *makeNode(int key);
};

bool rvaLookupReleased0035a220(void *owner, AsciiString *name);

struct Rva00359530Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	bool m_released;
	unsigned char m_pad;
	short m_references;
	struct Rva0035DF10ScriptNode *m_nodes;
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
	if ( nameIndex < table->m_nameIndexes.size() )
	{
		int recordIndex = table->m_nameIndexes[nameIndex];
		if ( rvaCompareNames(table->m_records[recordIndex].m_name, *name) == 0 && recordIndex != -1 )
			return table->m_records[recordIndex].m_released;
	}
	return true;
}

static __declspec(noinline) void rvaUniqueName0035a2a0(Rva0035A220Owner *owner, AsciiString *name)
{
	if (rvaLookupReleased0035a220(owner, name))
		return;

	AsciiString candidate;
	int suffix = 0;
	Rva00359530StringRecordTable *table = &owner->m_nameTable;
	do
	{
		++suffix;
		candidate.format(AsciiString("%s %d"), name->str(), suffix);
	} while (!rvaLookupReleasedInline(table, &candidate));
	name->set(candidate);
}

struct Rva0035DF10NodeList
{
	int m_0;
	Rva0035D800Node *m_head;

	Rva0035D800Node *getLast()
	{
		Rva0035D800Node *last = m_head;
		if (last)
			for (Rva0035D800Node *next = last->m_next; next; next = next->m_next)
				last = next;
		return last;
	}

	void insertAfter(Rva0035D800Node *prev, Rva0035D800Node *node)
	{
		if (prev)
		{
			node->m_next = prev->m_next;
			prev->m_next = node;
		}
		else
		{
			node->m_next = m_head;
			m_head = node;
		}
	}
};

class Rva0035DF10ScriptParser
{
public:
	bool parse(DataChunkInput &file, DataChunkInfo *info);

private:
	void *m_vtbl;
	int m_4;
	int m_8;
	Rva0035A220Owner *m_owner;
	Rva0035DF10NodeList *m_list;
};

bool Rva0035DF10ScriptParser::parse(DataChunkInput &file, DataChunkInfo *info)
{
	AsciiString name = file.readAsciiString();
	rvaUniqueName0035a2a0(m_owner, &name);
	Rva0035D800Node *node = ((Rva0035D800 *)m_owner)->makeNode((int)&name);
	Rva00359530StringRecordTable *table = &m_owner->m_nameTable;
	int skip = node->m_extra;
	Rva00359530Record &record = table->m_records[node->m_index];
	int count = record.m_references;
	Rva0035DF10ScriptNode *script = record.m_nodes;
	if (count > skip)
	{
		int n = count - skip;
		do
			script = script->m_next;
		while (--n);
	}
	script->m_script.Rva0035C0C0(file, info->version);

	m_list->insertAfter(m_list->getLast(), node);
	return true;
}
