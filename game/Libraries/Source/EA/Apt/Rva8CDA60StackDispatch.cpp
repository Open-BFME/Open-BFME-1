// ?rva8CDA60StackDispatch@@YAXPAVRva8CDA60State@@PAURva8CDA60Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable stack operation, retail 0x008CDA60 (109 bytes).

class Rva8CDA60Value
{
public:
	virtual void unused();
	virtual void release();

	unsigned m_flags;
	char m_gap[0x18];
	Rva8CDA60Value *m_indirect;
};

struct Rva8CDA60Context
{
	int m_unused;
	void *m_first;
	void *m_second;
};

class Rva8CDA60State
{
public:
	void append(void *first, void *second, void *data, Rva8CDA60Value *value,
		int zero1, int one, int zero2);

	int m_count;
	int m_unused;
	Rva8CDA60Value **m_stack;
};

void rva8CDA60StackDispatch(Rva8CDA60State *state, Rva8CDA60Context *context)
{
	int count = state->m_count;
	Rva8CDA60Value *value = state->m_stack[count - 1];
	Rva8CDA60Value *dataValue = state->m_stack[count - 2];
	void *data = (char *)(dataValue->m_flags % 64 == 1 ? dataValue : dataValue->m_indirect) + 8;
	state->append(context->m_first, context->m_second, data, value, 0, 1, 0);

	for (int i = 1; i <= 2; ++i)
	{
		Rva8CDA60Value *item = state->m_stack[state->m_count - i];
		unsigned char flags = (unsigned char)(item->m_flags >> 30);
		if (!(flags & 1))
			item->release();
	}
	state->m_count -= 2;
}
