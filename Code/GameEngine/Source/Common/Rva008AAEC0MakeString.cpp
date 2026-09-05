// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva8AAEC0MakeString@@YAPAVRva008A9B00@@PAVBfmeE1233@@@Z
// Apt string-value factory at 0x008AAEC0: getName, utf8 map, recycle or new.

struct AptStringBlock
{
	unsigned short m_refs;
	unsigned short m_length;
};

struct AptStringPool
{
	void *m_unused;
	void (__cdecl *m_free)(void *);
};

class Rva008A9B00;

struct AptValueRegistry;

extern AptStringBlock g_bfmeDefaultString1284;
extern AptStringPool *g_pool01337A30;
extern AptValueRegistry *g_bfmeRegistryVNF;
extern void *(__cdecl *g_aptAllocate)(unsigned int);

class BfmeUtf8String008A00C0
{
public:
	BfmeUtf8String008A00C0()
	{
		++g_bfmeDefaultString1284.m_refs;
		m_data = &g_bfmeDefaultString1284;
	}

	~BfmeUtf8String008A00C0()
	{
		AptStringBlock *block = m_data;
		if (--block->m_refs == 0)
			g_pool01337A30->m_free(block);
	}

	BfmeUtf8String008A00C0 &map();

	AptStringBlock *m_data;
};

struct BfmeStr1233
{
	AptStringBlock *m_data;
};

class BfmeE1233
{
public:
	void bfmeName1233(BfmeStr1233 *out);
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
	AptStringBlock *m_bfme00;
};

class Rva008A9B00
{
public:
	__declspec(nothrow) Rva008A9B00();

	void *m_vtable;
	unsigned int m_flags;
	AptStringBlock *m_string;
	Rva008A9B00 *m_next;
};

inline void *operator new(unsigned int, void *p)
{
	return p;
}

extern Rva008A9B00 *g_aptStringFreeList;


struct AptValueRegistry
{
 int m_capacity;
 int m_count;
 void **m_entries;
 __forceinline void addOrClear(Rva008A9B00 *obj)
{
	int index = m_count;
	int cap = m_capacity;
	if (index >= cap)
	{
		obj->m_flags &= ~0x40000000u;
		return;
	}
	m_entries[index] = obj;
	++m_count;
}

};
Rva008A9B00 *rva8AAEC0MakeString(BfmeE1233 *source)
{
	BfmeUtf8String008A00C0 name;
	source->bfmeName1233((BfmeStr1233 *)&name);
	name.map();

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
		void *raw = g_aptAllocate(0x10);
		Rva008A9B00 *fresh;
		if (raw)
			fresh = new (raw) Rva008A9B00;
		else
			fresh = 0;
		object = fresh;
	}

	++name.m_data->m_refs;
	AptStringBlock *old = object->m_string;
	if (--old->m_refs == 0)
		g_pool01337A30->m_free(old);
	object->m_string = name.m_data;
	return object;
}
