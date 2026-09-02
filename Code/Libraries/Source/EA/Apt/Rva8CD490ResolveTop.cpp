// ?rva8CD490ResolveTop@@YAXPAVRva8CD490State@@PAURva8CD490Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt top-of-stack resolver, retail 0x008CD490 (133 bytes).

class Rva8CD490Target;
struct Rva8CD490Holder
{
	char m_gap[0x50];
	Rva8CD490Target *m_target_storage;
};

class Rva8CCCE0Value
{
public:
	virtual void unused();
	virtual void release();

	unsigned m_flags;
	char m_gap[0x44];
	Rva8CD490Holder *m_holder;
};

class Rva8CD490Target
{
public:
	void consume(Rva8CCCE0Value *value);
};

struct Rva8CD490Context
{
	int m_unused;
	void *m_first;
	void *m_second;
};

class Rva8CD490State
{
public:
	int m_count;
	int m_unused;
	Rva8CCCE0Value **m_stack;
};

void rva8CCCE0ResolveValue(void *first, void *second, Rva8CCCE0Value *value,
	Rva8CCCE0Value **result);

void rva8CD490ResolveTop(Rva8CD490State *state, Rva8CD490Context *context)
{
	Rva8CD490State *owner = state;
	Rva8CCCE0Value *value = owner->m_stack[owner->m_count - 1];
	unsigned char shifted = (unsigned char)(value->m_flags >> 15);
	shifted = (unsigned char)~shifted;
	if (!(shifted & 1))
	{
		Rva8CCCE0Value *resolved;
		rva8CCCE0ResolveValue(context->m_first, context->m_second, value, &resolved);
		if (resolved != 0)
		{
			unsigned flags = resolved->m_flags;
			int type = flags & 0x3f;
			unsigned char indirect = (unsigned char)(flags >> 15);
			indirect = (unsigned char)~indirect;
			if (type >= 12 && type <= 19 && !(indirect & 1))
				((Rva8CD490Target *)((char *)resolved->m_holder->m_target_storage + 0x24))->consume(resolved);
		}
	}
	value = owner->m_stack[owner->m_count - 1];
	unsigned char releaseFlags = (unsigned char)(value->m_flags >> 30);
	if (!(releaseFlags & 1))
		value->release();
	--owner->m_count;
}
