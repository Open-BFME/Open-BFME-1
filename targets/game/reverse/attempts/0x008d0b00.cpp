// ?rva8D0B00RouteAction@@YAXPAVRva8D0B00State@@PAURva8D0B00Context@@@Z
// partial score=0.636363636364 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Route a selected value through hub 0x008CF740; retail 0x008D0B00, 352 bytes.
// Opaque identity. Evidence: docs/analysis/0x008cf740.md sections 2, 3, 5;
// complete caller instructions at +0x2C/+0x67/+0xAC/+0xC9/+0x120.
// Direct external declarations below are ABI models; unlanded aliases still
// need address bindings before a relocation/link acceptance gate.
// In particular, the hub's first argument is the parsed receiver (or context+4),
// and its third argument is the independent toInteger result. Do not merge them.
// The bank inherited a wrong selection of the integer as receiver. This version
// separates the two values and the parse output from its retained copy.
// Capture after makeValue is safe for this retail graph: 0x008C6320 forwards the
// output-slot address only to 0x008C4DA0; all five output-address loads in that
// helper are followed by stores through it and none passes/stores its address.
// Raw witnesses: 8C4DA0 +57/+68/+F5/+1A0/+1DF and 8C6320 +75/+7F/+99/+AD.
// Remaining nonmatch: key/lookup stack homes are exchanged; selected-receiver
// reload is after create instead of before; loop/pool-call scheduling differs.
// Best measured 353B vs 352B; 126 masked differing bytes; score 0.636363636.
// 0x012D5298 is the refcounted empty string block, not an installed vtable.

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
	int toInteger() const; // thiscall 0x00898300, EAX signed count, no stack args
	Rva8D0B00Value *at(int index) const; // thiscall 0x008B8E50, ret 4, EAX value

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
	Rva8D0B00Value *m_first;
	void *m_second;
};

class Rva8D0B00State
{
public:
	// 0x008CC940: thiscall, six dword arguments, ret 0x18, EAX value.
	Rva8D0B00Value *makeValue(Rva8D0B00Value *number, void *contextValue, Rva8D0B00String *key,
		int one1, int one2, int zero);
	// 0x008CF740: thiscall, (receiver, callable, count), ret 0x0C.
	void finish(Rva8D0B00Value *primary, Rva8D0B00Value *value, int number);

	int m_count;
	int m_unused;
	Rva8D0B00Value **m_stack;
};

// 0x008C6320: cdecl, five dword arguments, AL result ignored.
void rva8C6320PrepareRoute(Rva8D0B00Value *first, void *second, void *data,
	Rva8D0B00Value **lookup, Rva8D0B00String *key);

void rva8D0B00RouteAction(Rva8D0B00State *state,
	Rva8D0B00Context *context)
{
	Rva8D0B00State *owner = state;
	int count = owner->m_count;
	Rva8D0B00Value *top = owner->m_stack[count - 1];
	Rva8D0B00Value *under = owner->m_stack[count - 2];
	int number = under->toInteger();
	Rva8D0B00String key;
	Rva8D0B00Value *selected = 0;
	{
		Rva8D0B00Value *lookup = 0;

		unsigned flags = top->m_flags;
		int type = flags & 0x3f;
		if (type == 22)
		{
			flags >>= 15;
			if (!((unsigned char)~flags & 1))
				top = top->at(0);
		}

		flags = top->m_flags;
		type = flags & 0x3f;
		if (type == 1 || type == 42)
		{
			flags >>= 15;
			if (!((unsigned char)~flags & 1))
			{
				Rva8D0B00Value *stringValue = type == 1 ? top : top->m_indirect;
				Rva8D0B00Context *routeContext = context;
				rva8C6320PrepareRoute(routeContext->m_first,
					routeContext->m_second,
					(char *)stringValue + 8, &lookup, &key);
				top = owner->makeValue(lookup, routeContext->m_second,
					&key, 1, 1, 0);
				selected = lookup;
			}
		}

	}
	top->addRef();
	for (int i = 1; i <= 2; ++i)
	{
		int index = owner->m_count - i;
		Rva8D0B00Value **entries = owner->m_stack;
		Rva8D0B00Value *value = entries[index];
		unsigned char flags = (unsigned char)(value->m_flags >> 30);
		if (!(flags & 1)) value->release();
	}
	owner->m_count -= 2;
	owner->finish(selected != 0 ? selected : context->m_first,
		top, number);
	top->release();
}
