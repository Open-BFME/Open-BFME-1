// ?rva8C77F0PushStringLength@@YAXPAVRva8C77F0State@@@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
	void *m_unknown00;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class Rva8CD130String
{
public:
	__forceinline Rva8CD130String()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}
	__forceinline ~Rva8CD130String()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
	}
	BfmeStringData3AF0 *m_data;
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

class AptValue
{
public:
	virtual ~AptValue();
	unsigned int m_flags;
	__forceinline AptValue(int type);
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	AptValue **m_items;

	__forceinline void addPooled(AptValue *node)
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

extern AptValue *Rva013387D0Head;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(*Rva008C5D70Alloc)(unsigned int bytes);

__forceinline AptValue::AptValue(int type)
{
	unsigned int flags = (((m_flags & ~0x3f) | type) & 0xf000803f) | 0x8000;
	m_flags = flags;
	if (type != 0x1c && type != 0xa)
	{
		m_flags = flags | 0x40000000;
		g_rva8CD130IdleHook->addPooled(this);
	}
	else
	{
		m_flags = flags & 0xbfffffff;
	}
}

class AptInteger : public AptValue
{
public:
	static void *operator new(unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}

	__forceinline AptInteger(int value)
		: AptValue(7), m_value(value)
	{
	}

	union
	{
		AptInteger *m_next;
		volatile int m_value;
	};

	static __forceinline AptInteger *Create(int value)
	{
		AptInteger *object = (AptInteger *)Rva013387D0Head;

		if (object != 0)
		{
			Rva013387D0Head = (AptInteger *)object->m_next;
			g_rva8CD130IdleHook->addPooled(object);
			object->m_value = value;
			return object;
		}

		return new AptInteger(value);
	}
};

// ?rva8C77F0PushStringLength@@YAXPAVRva8C77F0State@@@Z
void rva8C77F0PushStringLength(Rva8C77F0State *state)
{
	Rva8CD130Value *top = state->m_stack[state->m_count - 1];
	Rva8CD130String name;
	top->getName(&name);

	Rva8CD130Value *result = (Rva8CD130Value *)AptInteger::Create(name.m_data->m_length);

	Rva8CD130Value *old = state->m_stack[state->m_count - 1];
	if (!old->maxRefCountHit())
		old->release();
	state->m_count--;

	state->m_stack[state->m_count] = result;
	state->m_count++;
	if (!result->maxRefCountHit())
		result->addRef();
}
