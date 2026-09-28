// cl: /DNDEBUG /O2 /Ob1 /MD /EHsc
// The matched version-chain method rvaProcess at 0x003559C0 proves the 20-byte
// record layout. No evidence identifies the owner class, so this source calls it
// Rva00359E40HeldBody.

struct Rva00359E40Version;

extern void j_00042a32();
void __cdecl operator delete(void *block);

class Rva003592A0NodeLink
{
public:
	Rva003592A0NodeLink *m_next;

	~Rva003592A0NodeLink()
	{
		typedef void (Rva003592A0NodeLink::*Destructor)(void);
		union
		{
			void (__cdecl *raw)(void);
			Destructor member;
		} thunk;
		thunk.raw = ::j_00042a32;
		(this->*thunk.member)();
	}
};

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
	void rva003592A0();

	char m_prefix[0x0c];
	Rva00359E40Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

void Rva00359E40Table::rva003592A0()
{
	int index = m_activeTail;
	while (index != -1)
	{
		Rva00359E40Record *record = &m_records[index];
		Rva003592A0NodeLink *head =
			reinterpret_cast<Rva003592A0NodeLink *>(record->m_nodes);
		while (head->m_next != 0)
		{
			Rva003592A0NodeLink *node = head->m_next;
			Rva003592A0NodeLink *next = head->m_next->m_next;
			delete node;
			head->m_next = next;
		}
		record->m_references = 1;
		index = m_records[index].m_previous;
	}
}

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
