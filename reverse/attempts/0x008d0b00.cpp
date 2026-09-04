// ?rva8D0B00RouteAction@@YAXPAVRva8D0B00State@@PAURva8D0B00Context@@@Z
// partial score=0.76 date=2026-09-02
// ?rva8D0B00RouteAction@@YAXPAVRva8D0B00State@@PAURva8D0B00Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt route action, retail 0x008D0B00 (352 bytes).

struct Rva8D0B00StringBlock
{
	unsigned short m_refs;
};

extern Rva8D0B00StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class Rva8D0B00String
{
public:
	Rva8D0B00String()
	{
		m_block = &g_bfmeDefaultString1284;
		++g_bfmeDefaultString1284.m_refs;
	}
	~Rva8D0B00String()
	{
		Rva8D0B00StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}

private:
	Rva8D0B00StringBlock *m_block;
};

class Rva8D0B00Value
{
public:
	virtual void addRef();
	virtual void release();
	int toInteger() const;
	Rva8D0B00Value *at(int index) const;

	bool maxRefCountHit() const
	{
		return ((m_flags >> 30) & 1) != 0;
	}

	unsigned m_flags;
	char m_gap[0x18];
	Rva8D0B00Value *m_indirect;
};

struct Rva8D0B00Context
{
	int m_unused;
	int m_first;
	void *m_second;
};

class Rva8D0B00State
{
public:
	Rva8D0B00Value *makeValue(int number, void *contextValue, Rva8D0B00String *key,
		int one1, int one2, int zero);
	void finish(int primary, Rva8D0B00Value *value, void *lookup);

	int m_count;
	int m_unused;
	Rva8D0B00Value **m_stack;
};

void rva8C6320PrepareRoute(int first, void *second, void *data,
	void **lookup, Rva8D0B00String *key);

void rva8D0B00RouteAction(Rva8D0B00State *state, Rva8D0B00Context *context)
{
	Rva8D0B00State *owner = state;
	Rva8D0B00Value *top;
	top = owner->m_stack[owner->m_count - 1];
	Rva8D0B00Value *under = owner->m_stack[owner->m_count - 2];
	int number = under->toInteger();
	Rva8D0B00String key;
	void *lookup = 0;

	unsigned flags = top->m_flags;
	int type = flags & 0x3f;
	if (type == 22)
	{
		flags >>= 15;
		*(unsigned char *)&flags = (unsigned char)~*(unsigned char *)&flags;
		if (!(*(unsigned char *)&flags & 1))
			top = top->at(0);
	}

	flags = top->m_flags;
	type = flags & 0x3f;
	if (type == 1 || type == 42)
	{
		flags >>= 15;
		*(unsigned char *)&flags = (unsigned char)~*(unsigned char *)&flags;
		if (!(*(unsigned char *)&flags & 1))
		{
			Rva8D0B00Value *stringValue = type == 1 ? top : top->m_indirect;
			rva8C6320PrepareRoute(context->m_first, context->m_second,
				(char *)stringValue + 8, &lookup, &key);
			top = owner->makeValue(number, context->m_second, &key, 1, 1, 0);
		}
	}

	top->addRef();
	for (int i = 1; i <= 2; ++i)
	{
		Rva8D0B00Value *value = owner->m_stack[owner->m_count - i];
		if (!value->maxRefCountHit())
			value->release();
	}
	owner->m_count -= 2;
	owner->finish(number != 0 ? number : context->m_first, top, lookup);
	top->release();
}
