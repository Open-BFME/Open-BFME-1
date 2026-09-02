// ?rva8D0D80BuildObject@@YAXPAVRva8D0D80State@@PAURva8D0D80Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva8D0D80StringBlock { unsigned short m_refs; };
extern Rva8D0D80StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class Rva8D0D80String
{
public:
	Rva8D0D80String()
	{
		m_block = &g_bfmeDefaultString1284;
		++m_block->m_refs;
	}
	~Rva8D0D80String()
	{
		Rva8D0D80StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}
private:
	Rva8D0D80StringBlock *m_block;
};

class Rva8D0D80Value
{
public:
	virtual void addRef();
	virtual void release();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	void getName(Rva8D0D80String *name);
	int toInteger();
	unsigned m_flags;
};

class Rva8D0D80Table
{
public:
	void add(Rva8D0D80String *name, Rva8D0D80Value *value);
};

class Rva8D0D80Result : public Rva8D0D80Value
{
public:
	Rva8D0D80Table m_table;
};

class Rva8D0D80State
{
public:
	Rva8D0D80Result *create(void *, void *, void *, int, int);
	void popValues(int count);
	int m_count;
	int m_unused;
	Rva8D0D80Value **m_stack;
};

struct Rva8D0D80Context { void *m_zero; void *m_owner; void *m_scope; };
extern char g_rva8D0D80CreateTag;
extern Rva8D0D80Value *g_bfmeFallbackDB;

void rva8D0D80BuildObject(Rva8D0D80State *state, Rva8D0D80Context *context)
{
	int count = state->m_stack[state->m_count - 1]->toInteger();
	Rva8D0D80Value *countValue = state->m_stack[state->m_count - 1];
	if (!((unsigned char)(countValue->m_flags >> 30) & 1))
		countValue->release();
	--state->m_count;

	Rva8D0D80Context *callContext = context;
	Rva8D0D80Result *result = state->create(callContext->m_owner, callContext->m_scope,
		&g_rva8D0D80CreateTag, 0, 1);
	if (result != 0)
	{
		for (int remaining = count; remaining > 0; --remaining)
		{
			Rva8D0D80Value *value = state->m_stack[state->m_count - 1];
			Rva8D0D80Value *nameValue = state->m_stack[state->m_count - 2];
			Rva8D0D80String name;
			nameValue->getName(&name);
			result->m_table.add(&name, value);

			for (int index = 1; index <= 2; ++index)
			{
				Rva8D0D80Value *old = state->m_stack[state->m_count - index];
				if (!((unsigned char)(old->m_flags >> 30) & 1))
					old->release();
			}
			state->m_count -= 2;
		}

		state->m_stack[state->m_count++] = result;
		if (!((unsigned char)(result->m_flags >> 30) & 1))
			result->addRef();
		result->release();
	}
	else
	{
		state->popValues(count + count);
		Rva8D0D80Value *fallback = g_bfmeFallbackDB;
		state->m_stack[state->m_count++] = fallback;
		if (!((unsigned char)(fallback->m_flags >> 30) & 1))
			fallback->addRef();
	}
}
