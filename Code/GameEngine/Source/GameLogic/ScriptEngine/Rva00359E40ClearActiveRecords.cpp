// cl: /DNDEBUG /O2 /Ob1 /MD /EHsc
// The matched version-chain method rvaProcess at 0x003559C0 proves the 20-byte
// record layout. No evidence identifies the owner class, so this source calls it
// Rva00359E40HeldBody.

struct Rva00359E40Version;

struct Rva00359E40Record
{
	int m_previous;
	int m_next;
	char m_name[4];
	unsigned char m_released;
	unsigned char m_pad;
	short m_references;
	Rva00359E40Version *m_nodes;
};

class Rva00359E40Table
{
public:
	char m_prefix[0x0c];
	Rva00359E40Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class Rva00359E40HeldBody
{
public:
	void rvaProcess(void *heads);
	void rvaClearActiveRecords();

private:
	char m_prefix[0x0c];
	Rva00359E40Table m_scriptTable;
	Rva00359E40Table m_groupTable;
};

extern void j_00020b53();
extern void j_00029429();
extern void j_0003bed0();

static __forceinline void rva00359E40Process(
	Rva00359E40HeldBody *owner, void *heads)
{
	typedef void (Rva00359E40HeldBody::*Process)(void *);
	union
	{
		void (*raw)(void);
		Process member;
	} thunk;
	thunk.raw = j_00020b53;
	(owner->*thunk.member)(heads);
}

static __forceinline void rva00359E40ScriptTableInit(Rva00359E40Table *table)
{
	typedef void (Rva00359E40Table::*Init)(void);
	union
	{
		void (*raw)(void);
		Init member;
	} thunk;
	thunk.raw = j_00029429;
	(table->*thunk.member)();
}

static __forceinline void rva00359E40GroupTableInit(Rva00359E40Table *table)
{
	typedef void (Rva00359E40Table::*Init)(void);
	union
	{
		void (*raw)(void);
		Init member;
	} thunk;
	thunk.raw = j_0003bed0;
	(table->*thunk.member)();
}

void Rva00359E40HeldBody::rvaClearActiveRecords()
{
	Rva00359E40HeldBody *self = this;
	void *heads = self ? (char *)self + 4 : 0;
	rva00359E40Process(self, heads);

	Rva00359E40Table *scriptTable = &self->m_scriptTable;
	rva00359E40ScriptTableInit(scriptTable);
	int idx = scriptTable->m_activeTail;
	if (idx != -1)
	{
		do
		{
			{
				Rva00359E40Record *records = scriptTable->m_records;
				records[idx].m_released = 0;
			}
			idx = scriptTable->m_records[idx].m_previous;
		}
		while (idx != -1);
	}

	Rva00359E40Table *groupTable = &self->m_groupTable;
	rva00359E40GroupTableInit(groupTable);
	int groupIdx = groupTable->m_activeTail;
	if (groupIdx != -1)
	{
		do
		{
			{
				Rva00359E40Record *records = groupTable->m_records;
				records[groupIdx].m_released = 0;
			}
			groupIdx = groupTable->m_records[groupIdx].m_previous;
		}
		while (groupIdx != -1);
	}
}
