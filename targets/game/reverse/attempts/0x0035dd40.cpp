// ?d_0035dd40@@YAXXZ
// partial score=1.0 date=2026-11-06
// ?parse@Rva0035DD40GroupParser@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z (row ?d_0035dd40@@YAXXZ)
// partial: the caller 0x0035DD40 is probe-EXACT (363/363, relocations masked) beside the
// compiler-private static helper rvaUniqueName0035a060 (0x0035A060), which does not match yet
// (0.917 shape); neither can land until it does. Lever here: the two readByte results go
// through named bool locals. Handoff:
// targets/game/reverse/attempt_support/0x0035a2a0-20261106-unique-name-helper.md
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"

class UserParser;
struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	unsigned short version;
	int dataSize;
};

class DataChunkInput
{
public:
	AsciiString readAsciiString();
	char readByte();
	bool parse(void *userData);
};

class Q1Forwardee0000871A
{
public:
	void handle(int parser);
};

extern "C" int _bfmeVftVE[];

class BfmeParserRegistrationVE
{
public:
	~BfmeParserRegistrationVE()
	{
		m_vftable = _bfmeVftVE;
		((Q1Forwardee0000871A *)m_table)->handle((int)m_parser);
	}
protected:
	void *m_vftable;
	DataChunkInput *m_table;
	UserParser *m_parser;
};

class Rva00352AB0ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva00352AB0ParserRegistration(void *dataContext, void *localList,
		DataChunkInput *table, AsciiString *labelOverride);
private:
	void *m_0c;
	void *m_10;
};

class Rva00350F50ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva00350F50ParserRegistration(void *dataContext, void *localList,
		DataChunkInput *table, AsciiString *labelOverride);
private:
	void *m_0c;
	void *m_10;
};

struct Rva0035DD40GroupNode
{
	Rva0035DD40GroupNode *m_next;
	int m_4;
	int m_list8;
	int m_c;
	bool m_10;
	bool m_11;
};

struct Gen0035D740Node
{
	Gen0035D740Node *m_next;
	int m_index;
	int m_extra;
};

class Gen0035D740
{
public:
	Gen0035D740Node *makeNode(int key);
};

bool rvaLookupReleased00359fe0(void *owner, AsciiString *name);

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	bool m_released;
	unsigned char m_pad;
	short m_references;
	struct Rva0035DD40GroupNode *m_nodes;
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
	if ( nameIndex < table->m_nameIndexes.size() )
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
		++suffix;
		candidate.format(AsciiString("%s %d"), name->str(), suffix);
	} while (!rvaLookupReleasedInline(table, &candidate));
	name->set(candidate);
}

struct Rva0035DD40NodeList
{
	Gen0035D740Node *m_head;

	Gen0035D740Node *getLast()
	{
		Gen0035D740Node *last = m_head;
		if (last)
			for (Gen0035D740Node *next = last->m_next; next; next = next->m_next)
				last = next;
		return last;
	}

	void insertAfter(Gen0035D740Node *prev, Gen0035D740Node *node)
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

class Rva0035DD40GroupParser
{
public:
	bool parse(DataChunkInput &file, DataChunkInfo *info);

private:
	void *m_vtbl;
	int m_4;
	int m_8;
	Rva00359FE0Owner *m_owner;
	Rva0035DD40NodeList *m_list;
};

bool Rva0035DD40GroupParser::parse(DataChunkInput &file, DataChunkInfo *info)
{
	AsciiString name = file.readAsciiString();
	rvaUniqueName0035a060(m_owner, &name);
	Gen0035D740Node *node = ((Gen0035D740 *)m_owner)->makeNode((int)&name);
	Rva00359330StringRecordTable *table = &m_owner->m_nameTable;
	int skip = node->m_extra;
	Rva00359330Record &record = table->m_records[node->m_index];
	int count = record.m_references;
	Rva0035DD40GroupNode *group = record.m_nodes;
	if (count > skip)
	{
		int n = count - skip;
		do
			group = group->m_next;
		while (--n);
	}
	bool active = file.readByte() != 0;
	group->m_10 = active;
	if (info->version >= 2)
	{
		bool flag = file.readByte() != 0;
		group->m_11 = flag;
	}

	m_list->insertAfter(m_list->getLast(), node);

	Rva00352AB0ParserRegistration groupParser(m_owner, &group->m_list8, &file, (AsciiString *)info);
	Rva00350F50ParserRegistration scriptParser(m_owner, &group->m_list8, &file, (AsciiString *)info);
	return file.parse(0);
}
