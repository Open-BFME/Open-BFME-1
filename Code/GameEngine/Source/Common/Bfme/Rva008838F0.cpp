// ?lookup@Rva008838F0Owner@@QAEHIPAPAXI@Z
// Address-derived identity from the complete retail hash-bucket and copy
// shape; no semantic owner name is claimed.
// cl: /O2 /DNDEBUG /MD

extern "C" __declspec(dllimport) void __stdcall Rva01358D18Enter(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave(void *lock);
extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *heap, unsigned long flags, unsigned long bytes);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *section);
extern "C" unsigned char g_rva01336CE8[];

class Rva008838F0Node
{
public:
	Rva008838F0Node *m_next;
	unsigned int m_type;
	unsigned int m_key;
	unsigned int m_pad0c[3];
	unsigned int m_count;
	void *m_values[1];
	unsigned char m_pad20[0x9c - 0x20];
	int m_freeCheckpoint;
};

class Rva008838F0Owner
{
public:
	Rva008838F0Owner(void *owner, void **table);
	int lookup(unsigned int key, void **dest, unsigned int limit);
	bool isValidBlock(int type, void *block);

private:
	void *m_owner;
	void **m_table;
	unsigned int m_tableIndex;
	Rva008838F0Node *m_buckets[0x2b7b];
	Rva008838F0Node *m_slots[0x7530];
	unsigned int m_slotIndex;
	Rva008838F0Node *m_current;
	unsigned char m_disabled;
	char m_pad282c1[3];
	void *m_previousOwner;
	void *m_lock;
};

Rva008838F0Owner::Rva008838F0Owner(void *owner, void **table)
{
	m_owner = owner;
	m_previousOwner = *(void **)0x01336CE0;
	*(void **)0x01336CE0 = this;
	if (table == 0)
		table = (void **)g_rva01336CE8;
	m_table = table;
	m_tableIndex = 0;
	while (m_table[m_tableIndex] != 0)
		++m_tableIndex;
	m_lock = HeapAlloc(GetProcessHeap(), 4, 0x18);
	InitializeCriticalSection(m_lock);
}

int Rva008838F0Owner::lookup(unsigned int key, void **dest, unsigned int limit)
{
	if (dest != 0 && limit != 0 && m_disabled == 0)
	{
		if (m_lock != 0)
			Rva01358D18Enter(m_lock);

		Rva008838F0Node **link = &m_buckets[key % 0x2b7b];
		while (*link != 0 && (*link)->m_key != key)
			link = &(*link)->m_next;
		Rva008838F0Node *node = *link;
		if (node == 0)
			return 0;

		unsigned int i = 0;
		while (i < limit && i < node->m_count)
		{
			dest[i] = node->m_values[i];
			++i;
		}

		if (m_lock != 0)
			Rva01358E74Leave(m_lock);
		return i;
	}

	return 0;
}

bool Rva008838F0Owner::isValidBlock(int type, void *block)
{
	if (m_disabled)
		return false;

	if (m_lock != 0)
		Rva01358D18Enter(m_lock);

	Rva008838F0Node **link = &m_buckets[(unsigned int)block % 0x2b7b];
	while (*link != 0 && (*link)->m_key != (unsigned int)block)
		link = &(*link)->m_next;

	Rva008838F0Node *node = *link;
	if (node == 0)
	{
		if (m_lock != 0)
			Rva01358E74Leave(m_lock);
		return false;
	}
	if (node->m_freeCheckpoint >= 0)
	{
		if (m_lock != 0)
			Rva01358E74Leave(m_lock);
		return false;
	}
	if (type >= 0 && node->m_type != (unsigned int)type)
	{
		if (m_lock != 0)
			Rva01358E74Leave(m_lock);
		return false;
	}

	if (m_lock != 0)
		Rva01358E74Leave(m_lock);
	return true;
}
