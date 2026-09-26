// cl: /DNDEBUG /O2 /Ob1 /MD /EHsc
// Address-derived conversion of retail 0x003559C0.  The direct caller at
// 0x00359E40 passes this+4, and the matched table accessors around this family
// prove the two twenty-byte record arrays at this+0x18 and this+0x38.  The
// concrete owner name is not recovered; the method keeps only the raw ABI and
// the observed version-chain operation.

class ScriptPoolObject
{
public:
	void deleteInstance(int destroy);
};

class ScriptGroupPoolObject
{
public:
	void deleteInstance(int destroy);
};

void __cdecl operator delete(void *pointer);

struct Rva00359E40Version
{
	Rva00359E40Version *m_previous;
	int m_unused;
	ScriptPoolObject *m_script;
	ScriptGroupPoolObject *m_group;
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
	char m_prefix[0x0c];
	Rva00359E40Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class Rva00359E40ScriptHandle : public ScriptPoolObject
{
public:
	Rva00359E40ScriptHandle * volatile m_next;
	int m_recordIndex;
	volatile int m_version;
};

class Rva00359E40GroupHandle : public ScriptGroupPoolObject
{
public:
	Rva00359E40GroupHandle * volatile m_next;
	int m_recordIndex;
	volatile int m_version;
};

class Rva00359E40HeldBody
{
public:
	void rvaProcess(void *heads);

private:
	char m_prefix[0x0c];
	Rva00359E40Table m_scriptTable;
	Rva00359E40Table m_groupTable;
};

extern void j_00020b53();

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

void Rva00359E40HeldBody::rvaProcess(void *heads)
{
	void *headBase = heads;
	Rva00359E40HeldBody *self = this;
	Rva00359E40ScriptHandle * volatile *link =
		(Rva00359E40ScriptHandle * volatile *)headBase;
	if (*(Rva00359E40ScriptHandle * volatile *)headBase != 0)
	{
		do
		{
			Rva00359E40ScriptHandle *handle = *link;
			Rva00359E40Record *records = self->m_scriptTable.m_records;
			int handleVersion = handle->m_version;
			Rva00359E40Record *record =
				&records[handle->m_recordIndex];
			int references = record->m_references;
			Rva00359E40Version *version = record->m_nodes;
			if (references > handleVersion)
			{
				int versionsBack = references - handleVersion;
				do
				{
					--versionsBack;
					version = version->m_previous;
				}
				while (versionsBack);
			}

			void *childHeads;
			void *versionTail = (char *)version + 4;
			if (versionTail != 0)
				childHeads = (char *)versionTail + 4;
			else
				childHeads = 0;
			rva00359E40Process(self, childHeads);

			if (self->m_scriptTable.m_records[handle->m_recordIndex].m_references !=
				handle->m_version)
			{
				*link = handle->m_next;
				handle->m_next = 0;
				Rva00359E40ScriptHandle *nextAfterClear = handle->m_next;
				if (nextAfterClear != 0)
						nextAfterClear->deleteInstance(1);
				operator delete(handle);
			}
			else
			{
				handle->m_version = 1;
				link = &handle->m_next;
			}
		}
		while (*link != 0);
	}

	if (*(Rva00359E40GroupHandle * volatile *)((char *)headBase + 4) != 0)
	{
		Rva00359E40GroupHandle * volatile *groupLink =
			(Rva00359E40GroupHandle * volatile *)((char *)headBase + 4);
		do
		{
			Rva00359E40GroupHandle *handle = *groupLink;
			if (self->m_groupTable.m_records[handle->m_recordIndex].m_references !=
				handle->m_version)
			{
				*groupLink = handle->m_next;
				handle->m_next = 0;
				Rva00359E40GroupHandle *nextAfterClear = handle->m_next;
				if (nextAfterClear != 0)
						nextAfterClear->deleteInstance(1);
				operator delete(handle);
			}
			else
			{
				handle->m_version = 1;
				groupLink = &handle->m_next;
			}
		}
		while (*groupLink != 0);
	}
}
