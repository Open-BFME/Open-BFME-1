// ?d_00893270@@YAXXZ
// partial score=0.94 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc

extern void *(*WideAllocPtr)(unsigned int bytes);
void Gen00897300(void *block);

struct Rva00893270Block
{
	unsigned short m_ref;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

extern Rva00893270Block g_default012D5298;

struct Rva00893270Pool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva00893270Pool *g_pool01337A30;
extern void *(__cdecl *Rva01337828Allocate)(unsigned int);

class BfmeStrVKI
{
public:
	BfmeStrVKI()
	{
		m_block = &g_default012D5298;
		++g_default012D5298.m_ref;
	}

	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	~BfmeStrVKI()
	{
		Rva00893270Block *block = m_block;
		if (--block->m_ref == 0)
			g_pool01337A30->free(block);
	}

	void __declspec(nothrow) bfmeSetVKI(const char *text);

	Rva00893270Block *m_block;
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
};

class Rva008A9B00
{
public:
	Rva008A9B00();

	void *operator new(unsigned int bytes)
	{
		return Rva01337828Allocate(bytes);
	}

	static void operator delete(void *memory);

	void *m_vptr;
	unsigned m_flags;
	Rva00893270Block *m_block;
	Rva008A9B00 *m_next;
};

struct BfmeRegistryKind1
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(Rva008A9B00 *obj)
	{
		int index = m_count;
		int *pcount = &m_count;
		if (index >= m_capacity)
		{
			obj->m_flags &= ~0x40000000;
			return;
		}

		m_entries[index] = obj;
		++*pcount;
	}
};

extern "C" BfmeRegistryKind1 *g_bfmeRegistryVNF;
extern Rva008A9B00 *Rva01338478FreeHead;

class Rva008B2EA0Node
{
public:
	void append(void *text);
};

class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int value);

class Rva00893270State
{
public:
	void append(void *owner, void *scope, BfmeStrVKI *name,
		Rva008A9B00 *node, int a, int b, int c);
};

void rva00893270ParseAppend(const char *text, const char *scope)
{
	Rva008A9B00 *node = Rva01338478FreeHead;
	if (node != 0)
	{
		Rva01338478FreeHead = node->m_next;
		g_bfmeRegistryVNF->addOrClear(node);
		if (node->m_block != &g_default012D5298)
			((BfmeStrVKK *)&node->m_block)->bfmeTruncVKK(0);
	}
	else
	{
		node = new Rva008A9B00();
	}

	((Rva008B2EA0Node *)node)->append((void *)text);
	BfmeStrVKI name(scope);
	Rva00893270State *state = (Rva00893270State *)Rva008930C0AptLookup(0);
	state->append(0, 0, &name, node, 1, 1, 0);
}
