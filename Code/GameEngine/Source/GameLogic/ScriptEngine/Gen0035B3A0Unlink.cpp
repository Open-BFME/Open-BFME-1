// cl: /DNDEBUG /MD /EHsc
// The matched cleanup caller at 0x0035B3A0 passes &m_slot4 to this method
// through its ILT and names it Gen0035B3A0::unlink.  The two table record
// arrays and the handle fields below are kept address-derived: the retail
// body proves their offsets and strides, but not semantic field names.

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

struct Gen0035B3A0Version
{
	Gen0035B3A0Version *m_previous;
	int m_unused;
	ScriptPoolObject *m_script;
	ScriptGroupPoolObject *m_group;
};

struct Gen0035B3A0Record
{
	int m_previous;
	int m_next;
	char m_name[4];
	unsigned char m_released;
	unsigned char m_pad;
	short m_references;
	Gen0035B3A0Version *m_nodes;
};

struct Gen0035B3A0Table
{
	char m_prefix[0x0c];
	Gen0035B3A0Record *m_records;
	int m_10;
	int m_14;
	int m_freeHead;
	int m_activeTail;
};

class Gen0035B3A0ScriptHandle : public ScriptPoolObject
{
public:
	Gen0035B3A0ScriptHandle * volatile m_next;
	int m_recordIndex;
	volatile int m_version;
};

class Gen0035B3A0GroupHandle : public ScriptGroupPoolObject
{
public:
	Gen0035B3A0GroupHandle * volatile m_next;
	int m_recordIndex;
	volatile int m_version;
};

class Gen0035B3A0
{
public:
	void unlink(void *slot);

private:
	char m_prefix[0x0c];
	Gen0035B3A0Table m_scriptTable;
	Gen0035B3A0Table m_groupTable;
};

void Gen0035B3A0::unlink(void *slot)
{
	void *headBase = slot;
	Gen0035B3A0 *self = this;
	Gen0035B3A0ScriptHandle * volatile *link =
		(Gen0035B3A0ScriptHandle * volatile *)headBase;
	if (*(Gen0035B3A0ScriptHandle * volatile *)headBase != 0)
	{
		do
		{
			Gen0035B3A0ScriptHandle *handle = *link;
			Gen0035B3A0Record *records = self->m_scriptTable.m_records;
			int handleVersion = handle->m_version;
			Gen0035B3A0Record *record =
				&records[handle->m_recordIndex];
			int references = record->m_references;
			Gen0035B3A0Version *version = record->m_nodes;
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
			self->unlink(childHeads);

			if (self->m_scriptTable.m_records[handle->m_recordIndex].m_references !=
				handle->m_version)
				goto destroyScriptHandle;
			if (self->m_scriptTable.m_records[handle->m_recordIndex].m_released != 0)
				goto destroyScriptHandle;
			handle->m_version = 1;
			link = &handle->m_next;
			continue;

		destroyScriptHandle:
			*link = handle->m_next;
			handle->m_next = 0;
			Gen0035B3A0ScriptHandle *nextAfterClear = handle->m_next;
			if (nextAfterClear != 0)
				nextAfterClear->deleteInstance(1);
			operator delete(handle);
		}
		while (*link != 0);
	}

	if (*(Gen0035B3A0GroupHandle * volatile *)((char *)headBase + 4) != 0)
	{
		Gen0035B3A0GroupHandle * volatile *groupLink =
			(Gen0035B3A0GroupHandle * volatile *)((char *)headBase + 4);
		do
		{
			Gen0035B3A0GroupHandle *handle = *groupLink;
			if (self->m_groupTable.m_records[handle->m_recordIndex].m_references !=
				handle->m_version)
				goto destroyGroupHandle;
			if (self->m_groupTable.m_records[handle->m_recordIndex].m_released != 0)
				goto destroyGroupHandle;
			handle->m_version = 1;
			groupLink = &handle->m_next;
			continue;

		destroyGroupHandle:
			*groupLink = handle->m_next;
			handle->m_next = 0;
			Gen0035B3A0GroupHandle *nextAfterClear = handle->m_next;
			if (nextAfterClear != 0)
				nextAfterClear->deleteInstance(1);
			operator delete(handle);
		}
		while (*groupLink != 0);
	}
}
