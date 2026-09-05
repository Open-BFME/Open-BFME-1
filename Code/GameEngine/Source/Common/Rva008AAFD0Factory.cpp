// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00891B80Block
{
	unsigned short m_ref;
};

extern Rva00891B80Block g_default012D5298;

struct Rva00891B80Pool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva00891B80Pool *g_pool01337A30;
extern void *(*WideAllocPtr)(unsigned int bytes);

class BfmeUtf8String008A01F0
{
public:
	BfmeUtf8String008A01F0()
	{
		m_block = &g_default012D5298;
		++g_default012D5298.m_ref;
	}

	~BfmeUtf8String008A01F0()
	{
		Rva00891B80Block *block = m_block;
		if (--block->m_ref == 0)
			g_pool01337A30->free(block);
	}

	BfmeUtf8String008A01F0 &map();

	Rva00891B80Block *m_block;
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
};

struct BfmeStr1233
{
	Rva00891B80Block *m_block;
};

class BfmeE1233
{
public:
	void bfmeName1233(BfmeStr1233 *a);
};

class Rva008A9B00
{
public:
	__declspec(nothrow) Rva008A9B00();

	void *operator new(unsigned int bytes)
	{
		return WideAllocPtr(bytes);
	}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

	void *m_vptr;
	unsigned m_flags;
	Rva00891B80Block *m_block;
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
		int cap = m_capacity;
		if (index >= cap)
		{
			obj->clearRegistered();
			return;
		}

		m_entries[index] = obj;
		++*pcount;
	}
};

extern "C" BfmeRegistryKind1 *g_bfmeRegistryVNF;

extern Rva008A9B00 *g_rva008AAFD0Free;

Rva008A9B00 *rva008AAFD0Make(BfmeE1233 *src)
{
	BfmeUtf8String008A01F0 local;
	src->bfmeName1233((BfmeStr1233 *)&local);
	local.map();

	Rva008A9B00 *obj = g_rva008AAFD0Free;
	if (obj)
	{
		g_rva008AAFD0Free = obj->m_next;
		g_bfmeRegistryVNF->addOrClear(obj);
		if (obj->m_block != &g_default012D5298)
			((BfmeStrVKK *)&obj->m_block)->bfmeTruncVKK(0);
	}
	else
	{
		Rva008A9B00 *fresh = new Rva008A9B00();
		obj = fresh;
	}

	++local.m_block->m_ref;
	Rva00891B80Block *outgoing = obj->m_block;
	if (--outgoing->m_ref == 0)
		g_pool01337A30->free(outgoing);
	obj->m_block = local.m_block;
	return obj;
}
