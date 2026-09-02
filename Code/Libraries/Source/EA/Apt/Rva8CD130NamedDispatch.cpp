// ?rva8CD130NamedDispatch@@YAXPAVRva8CD130State@@PAURva8CD130Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt two-value named dispatch, retail 0x008CD130 (224 bytes).

struct Rva8CD130StringBlock
{
	unsigned short m_refs;
};

extern Rva8CD130StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		m_block = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refs;
	}
	~Rva8CD130String()
	{
		Rva8CD130StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}

private:
	Rva8CD130StringBlock *m_block;
};

class Rva8CD130Value
{
public:
	virtual void addRef();
	virtual void release();
	void getName(Rva8CD130String *name);
	bool maxRefCountHit() const
	{
		return ((m_flags >> 30) & 1) != 0;
	}

	unsigned m_flags;
};

struct Rva8CD130Context
{
	int m_unused;
	void *m_first;
	void *m_second;
};

class Rva8CD130State
{
public:
	void append(void *first, void *second, Rva8CD130String *name,
		Rva8CD130Value *top, int one1, int one2, int zero);

	int m_count;
	int m_unused;
	Rva8CD130Value **m_stack;
};

class Rva8CD130IdleHook
{
public:
	int m_unused;
	int m_enabled;
	void run();
};

extern Rva8CD130IdleHook *g_rva8CD130IdleHook;

void rva8CD130NamedDispatch(Rva8CD130State *state, Rva8CD130Context *context)
{
	Rva8CD130State *owner = state;
	Rva8CD130String name;
	int count = owner->m_count;
	Rva8CD130Value *top = owner->m_stack[count - 1];
	Rva8CD130Value *under = owner->m_stack[count - 2];
	under->getName(&name);
	owner->append(context->m_first, context->m_second, &name, top, 1, 1, 0);

	for (int i = 1; i <= 2; ++i)
	{
		Rva8CD130Value *value = owner->m_stack[owner->m_count - i];
		if (!value->maxRefCountHit())
			value->release();
	}
	owner->m_count -= 2;
	if (g_rva8CD130IdleHook->m_enabled != 0 && owner->m_count == 0)
		g_rva8CD130IdleHook->run();
}
