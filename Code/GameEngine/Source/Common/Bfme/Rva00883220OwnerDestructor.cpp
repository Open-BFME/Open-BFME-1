// ??1Rva008838F0Owner@@QAE@XZ
// Owner identity is established by the matched constructor and tracker
// methods.  This TU uses the separately witnessed free-list node layout.
// cl: /O2 /DNDEBUG /MD

extern "C" __declspec(dllimport) void __stdcall Rva01358D18Enter(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358D0CReset(void *section);
extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) int __stdcall HeapFree(
	void *heap, unsigned long flags, void *block);

struct Rva00883220Node
{
	Rva00883220Node *m_next;
	char m_pad04[0x10];
	void *m_value14;
};

class Rva008838F0Owner
{
public:
	~Rva008838F0Owner(void);

private:
	char m_pad00[0x0c];
	Rva00883220Node *m_buckets[0x2b7b];
	Rva00883220Node *m_slots[0x7530];
	unsigned int m_slotIndex;
	Rva00883220Node *m_current;
	unsigned char m_disabled;
	char m_pad282c1[3];
	void *m_previousOwner;
	void *m_lock;
};

Rva008838F0Owner::~Rva008838F0Owner(void)
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

	Rva00883220Node **bucket = m_buckets;
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

	Rva00883220Node *node = m_current;
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
