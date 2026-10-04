// cl: /DNDEBUG /MD /EHsc

struct Rva008CF3C0Block
{
	unsigned short m_ref;
};

extern Rva008CF3C0Block g_default012D5298;

struct Rva008CF3C0Pool
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern Rva008CF3C0Pool *g_pool01337A30;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
extern char *(__cdecl *g_rva01337860Empty)(void);
extern char *(__cdecl *g_rva0133785CDuplicate)(const char *);
extern void (__cdecl *g_bfmeFreeDWF)(void *);

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
};

class Rva008CF3C0String
{
public:
	Rva008CF3C0String()
	{
		m_block = &g_default012D5298;
		++g_default012D5298.m_ref;
	}

	~Rva008CF3C0String()
	{
		Rva008CF3C0Block *block = m_block;
		if (--block->m_ref == 0)
			g_pool01337A30->free(block);
	}

	Rva008CF3C0Block *m_block;
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
	Rva008CF3C0Block *m_block;
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
extern Rva008A9B00 *g_rva008C3B60Free;

class Rva008CF3C0State
{
public:
	void parseAndAppend(void *owner, void *scope, Rva008CF3C0String *input);
};

// The retail body at 0x008C55B0 is the pair scanner thiscall on ecx; it is
// linked under its own free-function identity ?d_008c55b0@@YAXXZ.
extern void d_008c55b0();
// The retail body at 0x008CC690 is the node append thiscall on ecx, linked
// as ?d_008cc690@@YAXXZ.
extern void d_008cc690();

void Rva008CF3C0State::parseAndAppend(void *owner, void *scope,
	Rva008CF3C0String *input)
{
	typedef char *(Rva008CF3C0State::*ParseFn)(char *, Rva008CF3C0String *,
		Rva008CF3C0String *);
	typedef void (Rva008CF3C0State::*AppendFn)(void *, void *,
		Rva008CF3C0String *, Rva008A9B00 *, int, int, int);
	union { void (*fn)(); ParseFn call; } parseThunk = { d_008c55b0 };
	union { void (*fn)(); AppendFn call; } appendThunk = { d_008cc690 };

	char *buffer;
	if (input == 0)
		buffer = g_rva01337860Empty();
	else
		buffer = g_rva0133785CDuplicate((const char *)input->m_block + 8);

	Rva008CF3C0String name;
	Rva008CF3C0String value;
	char *cursor = buffer;
	while ((cursor = (this->*parseThunk.call)(cursor, &name, &value)) != 0)
	{
		if (name.m_block != &g_default012D5298)
		{
			Rva008A9B00 *node = g_rva008C3B60Free;
			if (node != 0)
			{
				g_rva008C3B60Free = node->m_next;
				g_bfmeRegistryVNF->addOrClear(node);
				if (node->m_block != &g_default012D5298)
					((BfmeStrVKK *)&node->m_block)->bfmeTruncVKK(0);
			}
			else
			{
				node = new Rva008A9B00();
			}

			++value.m_block->m_ref;
			Rva008CF3C0Block *outgoing = node->m_block;
			if (--outgoing->m_ref == 0)
				g_pool01337A30->free(outgoing);
			node->m_block = value.m_block;
			(this->*appendThunk.call)(owner, scope, &name, node, 1, 1, 0);
		}
	}
	g_bfmeFreeDWF(buffer);
}
