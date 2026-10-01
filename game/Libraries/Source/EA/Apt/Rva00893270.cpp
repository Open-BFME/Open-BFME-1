// ?Rva00893270@@YAXPBD0@Z
// cl: /DNDEBUG /MD /EHsc

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

class BfmeStrVKI
{
public:
	BfmeStrVKI()
	{
		m_block = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refCount;
	}

	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *block = m_block;
		if (--block->m_refCount == 0)
			g_bfmeStringPool1284->free(block);
	}

	void __declspec(nothrow) bfmeSetVKI(const char *text);

	BfmeStringData3AF0 *m_block;
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
		return Rva008C5D70Alloc(bytes);
	}

	static void operator delete(void *memory);

	void *m_vptr;
	unsigned m_flags;
	BfmeStringData3AF0 *m_block;
	Rva008A9B00 *m_next;
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	Rva008A9B00 **m_items;

	__forceinline void addOrClear(Rva008A9B00 *obj)
	{
		int index = m_count;
		int *pcount = &m_count;
		if (index >= m_capacity)
		{
			obj->m_flags &= ~0x40000000;
			return;
		}

		m_items[index] = obj;
		++*pcount;
	}
};

extern Rva00899560Pool *g_rva8CD130IdleHook;
struct Rva008C3B60Node;
extern Rva008C3B60Node *Rva008C3B60Head;

class Rva008B2EA0Node
{
public:
	void append(void *text);
};

class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int value);

// m_count is the stack depth the Apt interpreter reads; the cast below reinterprets the
// whole object as Rva008CF3C0State, so the member is only here to spell the type MSVC
// mangles the global with (3U...@@A).
struct Rva008AE770Stack { int m_count; };
extern Rva008AE770Stack Rva008AE770TheStack;

class Rva008CF3C0State
{
public:
	void append(void *owner, void *scope, BfmeStrVKI *name,
		Rva008A9B00 *node, int a, int b, int c);
};

#pragma comment(linker, "/alternatename:?append@Rva008CF3C0State@@QAEXPAX0PAVBfmeStrVKI@@PAVRva008A9B00@@HHH@Z=?d_008cc690@@YAXXZ")

void Rva00893270(const char *first, const char *second)
{
	Rva008A9B00 *node = (Rva008A9B00 *)Rva008C3B60Head;
	if (node != 0)
	{
		Rva008C3B60Head = (Rva008C3B60Node *)node->m_next;
		g_rva8CD130IdleHook->addOrClear(node);
		if (node->m_block != &g_bfmeDefaultString1284)
			((BfmeStrVKK *)&node->m_block)->bfmeTruncVKK(0);
	}
	else
	{
		node = new Rva008A9B00();
	}

	((Rva008B2EA0Node *)node)->append((void *)second);
	BfmeStrVKI name(first);
	((Rva008CF3C0State *)&Rva008AE770TheStack)->append(
		Rva008930C0AptLookup(0), 0, &name,
		node, 1, 1, 0);
}
