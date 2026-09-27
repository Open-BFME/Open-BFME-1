// ?rva8C77F0PushStringLength@@YAXPAVRva8C77F0State@@@Z
// partial score=0.6 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt handler, retail 0x008C77F0 (346 bytes), address-derived identity: take
// the name of the value on top of the state's stack, replace that value with
// a pooled integer holding the name's length. The integer is built by the
// same pooled constructor as AptInteger::Create (0x008A11E0), inlined here.

struct Rva8C77F0StringBlock
{
	unsigned short m_refs;
	unsigned short m_length;
};

extern Rva8C77F0StringBlock g_bfmeDefaultString1284;
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
		Rva8C77F0StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}

	Rva8C77F0StringBlock *m_block;
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

class Rva8C77F0State
{
public:
	int m_count;
	int m_unused;
	Rva8CD130Value **m_stack;
};

struct Rva008D2A30Node
{
	void *m_vtable;
	unsigned int m_flags;
	union
	{
		Rva008D2A30Node *m_next;
		int m_value;
	};
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	Rva008D2A30Node **m_items;

	__forceinline void addPooled(Rva008D2A30Node *node)
	{
		int &count = m_count;
		if (count >= m_capacity)
		{
			node->m_flags &= 0xbfffffff;
		}
		else
		{
			m_items[count] = node;
			count++;
		}
	}
};

extern Rva008D2A30Node *Rva013387D0Head;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);

static __forceinline Rva008D2A30Node *makeInteger(int value)
{
	Rva008D2A30Node *object = Rva013387D0Head;

	if (object != 0)
	{
		Rva013387D0Head = object->m_next;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_value = value;
		return object;
	}

	object = (Rva008D2A30Node *)Rva008C5D70Alloc(12);

	if (object != 0)
	{
		object->m_vtable = (void *)0x01135D68;
		object->m_flags = (object->m_flags & 0xf0008007) | 0x40008007;
		g_rva8CD130IdleHook->addPooled(object);
		object->m_vtable = (void *)0x01136400;
		object->m_value = value;
		return object;
	}

	return 0;
}

// ?rva8C77F0PushStringLength@@YAXPAVRva8C77F0State@@@Z
void rva8C77F0PushStringLength(Rva8C77F0State *state)
{
	Rva8CD130Value *top = state->m_stack[state->m_count - 1];
	Rva8CD130String name;
	top->getName(&name);

	Rva8CD130Value *result = (Rva8CD130Value *)makeInteger(name.m_block->m_length);

	Rva8CD130Value *old = state->m_stack[state->m_count - 1];
	if (!old->maxRefCountHit())
		old->release();
	state->m_count--;

	state->m_stack[state->m_count] = result;
	state->m_count++;
	if (!result->maxRefCountHit())
		result->addRef();
}
