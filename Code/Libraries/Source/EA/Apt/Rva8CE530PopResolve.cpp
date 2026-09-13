// ?rva8CE530PopResolve@@YAXPAVRva8CE530State@@PAURva8CE530Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt pop-and-resolve, retail 0x008CE530 (129 bytes).

class Rva8CCCE0Value
{
public:
	virtual void unused();
	virtual void release();

	unsigned m_flags;
};

void rva8CCCE0ResolveValue(void *first, void *second, Rva8CCCE0Value *value,
	Rva8CCCE0Value **result);

class Rva8CE530State
{
public:
	int m_count;
	int m_unused;
	Rva8CCCE0Value **m_stack;
};

struct Rva8CE530Context
{
	unsigned int m_field0;
	void *m_first;
	Rva8CCCE0Value *m_field8;
	unsigned int m_fieldC;
};

void rva8CE530PopResolve(Rva8CE530State *state, Rva8CE530Context *context)
{
	unsigned char *slot = (unsigned char *)(((unsigned int)context->m_field0 + 3) & ~3u);
	context->m_field0 = (unsigned int)(slot + 4);

	Rva8CCCE0Value *value = state->m_stack[state->m_count - 1];
	unsigned flags = value->m_flags;

	if (((unsigned char)~(unsigned char)(flags >> 15) & 1) != 0)
	{
		context->m_field8 = 0;
		context->m_field0 = *(unsigned int *)slot;
	}
	else
	{
		void *first = context->m_first;
		Rva8CCCE0Value *resolved;
		rva8CCCE0ResolveValue(first, 0, value, &resolved);
		context->m_fieldC = *(unsigned int *)slot;
		context->m_field8 = resolved;
		resolved->unused();
	}

	value = state->m_stack[state->m_count - 1];

	if (((unsigned char)(value->m_flags >> 30) & 1) == 0)
		value->release();

	state->m_count--;
}
