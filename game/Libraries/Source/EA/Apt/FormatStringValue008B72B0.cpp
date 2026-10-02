// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00891B80Block
{
	unsigned short m_ref;
};

// The shared empty EA string block at 0x012D5298 is defined once, with its
// proven type, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp.  It is
// named here through a file-local view cast at each use so the DIR32 target is
// the one retail address.
class EAStringC
{
public:
	class StringDataC;
};

extern EAStringC::StringDataC g_rva012D5298Empty;

static inline Rva00891B80Block *rva012D5298Block()
{
	return (Rva00891B80Block *)&g_rva012D5298Empty;
}

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
		m_block = rva012D5298Block();
		++rva012D5298Block()->m_ref;
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
	Rva008A9B00();
    static void operator delete(void *, unsigned);

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

class Rva8CD130String;
class Rva008B6880 { public: void invoke(Rva8CD130String *); };
class Rva008B2EA0Node { public: void append(void *); };
Rva008A9B00 *formatStringValue008B72B0(Rva008B6880 *src)
{
    Rva008A9B00 *obj = g_rva008AAFD0Free;
    if (obj) {
        g_rva008AAFD0Free = obj->m_next;
        g_bfmeRegistryVNF->addOrClear(obj);
        if (obj->m_block != rva012D5298Block())
            ((BfmeStrVKK *)&obj->m_block)->bfmeTruncVKK(0);
    } else {
        Rva008A9B00 *fresh = new Rva008A9B00();
        obj = fresh;
    }
    BfmeUtf8String008A01F0 local;
    src->invoke((Rva8CD130String *)&local);
    ((Rva008B2EA0Node *)obj)->append((char *)local.m_block + 8);
    return obj;
}
