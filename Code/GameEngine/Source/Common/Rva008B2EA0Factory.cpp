// ?rva008B2EA0Create@@YAPAVRva008B2EA0Node@@XZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct AptStringBlock
{
	unsigned short m_refs;
	unsigned short m_length;
};

extern void *(__cdecl *g_aptAllocate)(unsigned int);

class Rva008A9B00
{
public:
	void *operator new(unsigned int bytes)
	{
		return g_aptAllocate(bytes);
	}

	void operator delete(void *) {}

	Rva008A9B00();

	void *m_vtable;
	unsigned int m_flags;
	AptStringBlock *m_string;
	Rva008A9B00 *m_next;
};

struct AptValueRegistry
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(Rva008A9B00 *object)
	{
		int index = m_count;
		int capacity = m_capacity;
		if (index >= capacity)
		{
			object->m_flags &= ~0x40000000u;
			return;
		}
		m_entries[index] = object;
		++m_count;
	}
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned int length);
};

extern AptStringBlock g_bfmeDefaultString1284;
extern AptValueRegistry *g_bfmeRegistryVNF;
extern Rva008A9B00 *g_aptStringFreeList;

class Rva008B2EA0Node;

Rva008B2EA0Node *rva008B2EA0Create()
{
	Rva008A9B00 *object = g_aptStringFreeList;
	if (object)
	{
		g_aptStringFreeList = object->m_next;
		g_bfmeRegistryVNF->addOrClear(object);
		if (object->m_string != &g_bfmeDefaultString1284)
			((BfmeStrVKK *)&object->m_string)->bfmeTruncVKK(0);
	}
	else
	{
		object = new Rva008A9B00;
	}
	return (Rva008B2EA0Node *)object;
}
