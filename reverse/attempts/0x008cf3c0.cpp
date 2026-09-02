// ?parseAndAppend@Rva8CF3C0State@@QAEXPAX0PAVRva8CF3C0String@@@Z
// partial score=0.9 date=2026-09-02
// ?parseAndAppend@Rva8CF3C0State@@QAEXPAX0PAVRva8CF3C0String@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva8CF3C0StringBlock { unsigned short m_refs; char m_gap02[6]; };
inline void *operator new(unsigned, void *where) { return where; }
extern Rva8CF3C0StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);
extern void *(__cdecl *g_rva8CF3C0Allocate)(unsigned);

class Rva8CF3C0String
{
public:
	Rva8CF3C0String()
	{
		m_block = &g_bfmeDefaultString1284;
		++m_block->m_refs;
	}
	~Rva8CF3C0String()
	{
		Rva8CF3C0StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}
	Rva8CF3C0String &operator=(const Rva8CF3C0String &other)
	{
		Rva8CF3C0StringBlock *next = other.m_block;
		++next->m_refs;
		Rva8CF3C0StringBlock *old = m_block;
		--old->m_refs;
		if (old->m_refs == 0)
			Rva01337A30ReleaseTable[1](old);
		m_block = next;
		return *this;
	}
	void clear(int);
	Rva8CF3C0StringBlock *m_block;
};

class Rva8CF3C0Value
{
public:
	virtual void addRef();
	unsigned m_flags;
};

class Rva8CF3C0Node : public Rva8CF3C0Value
{
public:
	Rva8CF3C0Node();
	Rva8CF3C0String m_string;
	Rva8CF3C0Node *m_next;
};

struct Rva8CF3C0Pool
{
	int m_capacity;
	int m_count;
	Rva8CF3C0Node **m_items;
};

extern Rva8CF3C0Node *g_rva8CF3C0FreeNodes;
extern Rva8CF3C0Pool *g_rva8CF3C0Pool;
extern char *(__cdecl *g_rva8CF3C0EmptyBuffer)();
extern char *(__cdecl *g_rva8CF3C0Duplicate)(const char *);
extern void (__cdecl *g_rva8CF3C0Free)(void *);

class Rva8CF3C0State
{
public:
	char *parse(char *cursor, Rva8CF3C0String *name, Rva8CF3C0String *value);
	void append(void *, void *, Rva8CF3C0String *, Rva8CF3C0Value *, int, int, int);
	void parseAndAppend(void *, void *, Rva8CF3C0String *);
};

static Rva8CF3C0Node *rva8CF3C0AcquireNode()
{
	Rva8CF3C0Node *node = g_rva8CF3C0FreeNodes;
	if (node != 0)
	{
		g_rva8CF3C0FreeNodes = node->m_next;
		Rva8CF3C0Pool *pool = g_rva8CF3C0Pool;
		if (pool->m_count >= pool->m_capacity)
			node->m_flags &= ~0x40000000u;
		else
			pool->m_items[pool->m_count++] = node;
		if (node->m_string.m_block != &g_bfmeDefaultString1284)
			node->m_string.clear(0);
		return node;
	}

	void *memory = g_rva8CF3C0Allocate(0x10);
	return memory != 0 ? new(memory) Rva8CF3C0Node : 0;
}

void Rva8CF3C0State::parseAndAppend(void *owner, void *scope,
	Rva8CF3C0String *input)
{
	char *buffer;
	if (input == 0)
		buffer = g_rva8CF3C0EmptyBuffer();
	else
		buffer = g_rva8CF3C0Duplicate((const char *)input->m_block + 8);

	char *cursor = buffer;
	Rva8CF3C0String value;
	Rva8CF3C0String name;
	while ((cursor = parse(cursor, &name, &value)) != 0)
	{
		if (name.m_block != &g_bfmeDefaultString1284)
		{
			Rva8CF3C0Node *node = rva8CF3C0AcquireNode();
			node->m_string = value;
			append(owner, scope, &name, node, 1, 1, 0);
		}
	}
	g_rva8CF3C0Free(buffer);
}
