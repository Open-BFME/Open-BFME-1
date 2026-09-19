// ?lookup@Rva008838F0Owner@@QAEHIPAPAXI@Z
// The tracker owner identity remains address-derived; reciprocal placement and
// the neighboring owner methods establish the original memorypool TU.
// cl: /O2 /DNDEBUG /MD

extern "C" __declspec(dllimport) void __stdcall Rva01358D18Enter(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358D0CReset(void *section);
extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *heap, unsigned long flags, unsigned long bytes);
extern "C" __declspec(dllimport) int __stdcall HeapFree(
	void *heap, unsigned long flags, void *block);
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
	~Rva008838F0Owner();
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

struct Rva00883220Node
{
	Rva00883220Node *m_next;
	char m_pad04[0x10];
	void *m_value14;
};

Rva008838F0Owner::~Rva008838F0Owner()
{
	if (m_lock != 0)
		Rva01358D18Enter(m_lock);

	m_disabled = 1;

	if (m_lock != 0)
	{
		Rva01358E74Leave(m_lock);
		Rva01358D0CReset(m_lock);
		HeapFree(GetProcessHeap(), 0, m_lock);
		m_lock = 0;
	}

	Rva00883220Node **bucket =
		reinterpret_cast<Rva00883220Node **>(m_buckets);
	unsigned int bucketCount = 0x2b7b;
	do
	{
		Rva00883220Node *node = *bucket;
		while (node != 0)
		{
			Rva00883220Node *next = node->m_next;
			if (node->m_value14 != 0)
				HeapFree(GetProcessHeap(), 0, node->m_value14);
			HeapFree(GetProcessHeap(), 0, node);
			node = next;
		}
		*bucket = 0;
		++bucket;
		--bucketCount;
	} while (bucketCount != 0);

	Rva00883220Node *node = reinterpret_cast<Rva00883220Node *>(m_current);
	while (node != 0)
	{
		Rva00883220Node *next = node->m_next;
		if (node->m_value14 != 0)
			HeapFree(GetProcessHeap(), 0, node->m_value14);
		HeapFree(GetProcessHeap(), 0, node);
		node = next;
	}
	m_current = 0;
}
