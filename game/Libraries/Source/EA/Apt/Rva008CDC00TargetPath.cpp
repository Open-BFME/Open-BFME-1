// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt opcode 0x45 handler (Flash ActionTargetPath slot 0x00ED5B7C of the table at 0x00ED5A68):
// replaces the top value with the path string of the clip it resolves to, or with g_bfmeFallbackDB.

struct BfmeStringData3AF0
{
	unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0
{
	void *m_unknown00;
	void (__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern const char g_Rva0107301CEmptyString[];

class BfmeStrVKI
{
public:
	BfmeStrVKI()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}
	BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_rva01337A30AllocPair->free(old);
	}
	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		++other.m_data->m_refCount;
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_rva01337A30AllocPair->free(old);
		m_data = other.m_data;
		return *this;
	}
	void bfmeSetVKI(const char *text);
	BfmeStringData3AF0 *m_data;
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	bool isUndefined() const
	{
		return ((unsigned char)~(m_valueBits >> 15) & 1) != 0;
	}
	bool GetMaxRefCountHit() const
	{
		return (m_valueBits >> 30 & 1) != 0;
	}

	unsigned int m_valueBits;
};

class Rva8CCCE0Value;
void rva8CCCE0ResolveValue(void *first, void *second, Rva8CCCE0Value *value,
	Rva8CCCE0Value **result);
void bfmeResetEVF(void *ctx, BfmeStrVKI *text);

class Gen_uws16_00891a80
{
public:
	static void operator delete(void *memory, unsigned bytes);
};
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);
class Rva008A9B00 : public Gen_uws16_00891a80
{
public:
	Rva008A9B00();
	void *operator new(unsigned bytes) { return Rva008C5D70Alloc(bytes); }
	void *m_unknown00;
	unsigned m_flags;
	BfmeStringData3AF0 *m_data;
	Rva008A9B00 *m_next;
};

struct Rva008C3B60Node
{
	void *m_unknown00;
	unsigned m_flags;
	BfmeStringData3AF0 *m_data;
	Rva008C3B60Node *m_next;
};

struct Rva00899560Pool
{
	int m_capacity, m_count;
	Rva008C3B60Node **m_items;
	__forceinline void addPooled(Rva008C3B60Node *object)
	{
		int index = m_count;
		int *count = &m_count;
		if (index >= m_capacity)
			object->m_flags &= ~0x40000000;
		else
		{
			m_items[index] = object;
			++*count;
		}
	}
};
extern Rva00899560Pool *g_rva01337810GcRoots;
extern Rva008C3B60Node *Rva008C3B60Head;
extern AptValue *g_bfmeFallbackDB;

static __forceinline Rva008C3B60Node *createStringValue()
{
	Rva008C3B60Node *node = Rva008C3B60Head;
	if (node)
	{
		Rva008C3B60Head = node->m_next;
		g_rva01337810GcRoots->addPooled(node);
		if (node->m_data != &g_bfmeDefaultString1284)
			((BfmeStrVKK *)&node->m_data)->bfmeTruncVKK(0);
		return node;
	}
	return (Rva008C3B60Node *)new Rva008A9B00;
}

class AptActionInterpreter
{
public:
	struct LocalContextT
	{
		const unsigned char *m_pc;
		void *m_owner;
		void *m_scope;

		AptValue *resolveValue(AptValue *value)
		{
			AptValue *result;
			rva8CCCE0ResolveValue(m_owner, m_scope, (Rva8CCCE0Value *)value,
				(Rva8CCCE0Value **)&result);
			return result;
		}
	};

	static void _FunctionRva008CDC00(
		AptActionInterpreter *interpreter, LocalContextT *context);

	void pop()
	{
		AptValue *old = m_stack[m_stackTop - 1];
		if (!old->GetMaxRefCountHit())
			old->Release();
		m_stackTop--;
	}
	void push(AptValue *value)
	{
		m_stack[m_stackTop] = value;
		m_stackTop++;
		if (!value->GetMaxRefCountHit())
			value->AddRef();
	}

	int m_stackTop;
	int m_stackCapacity;
	AptValue **m_stack;
};

void AptActionInterpreter::_FunctionRva008CDC00(
	AptActionInterpreter *interpreter, LocalContextT *context)
{
	BfmeStrVKI path;
	AptValue *target = context->resolveValue(interpreter->m_stack[interpreter->m_stackTop - 1]);
	if (target)
	{
		int type = target->m_valueBits & 63;
		if (type >= 12 && type <= 19 && !target->isUndefined())
			bfmeResetEVF(target, &path);
		else
			path = BfmeStrVKI(g_Rva0107301CEmptyString);
		Rva008C3B60Node *result = createStringValue();
		*(BfmeStrVKI *)&result->m_data = path;
		interpreter->pop();
		interpreter->push((AptValue *)result);
	}
	else
	{
		interpreter->pop();
		interpreter->push(g_bfmeFallbackDB);
	}
}
