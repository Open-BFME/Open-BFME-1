// ?rva8CD3F0RouteDispatch@@YAXPAVRva8CD3F0State@@PAURva8CD3F0Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable Apt three-value route dispatch, retail 0x008CD3F0 (155 bytes).

class Rva8CD3F0Value
{
public:
	virtual void addRef();
	virtual void release();
	int toInteger() const;

	unsigned m_flags;
};

struct Rva8CD3F0Context
{
	int m_unused;
	void *m_first;
	void *m_second;
};

class Rva8CD3F0State
{
public:
	void append(Rva8CD3F0Value *resolved, void *contextValue, int *routeKey,
		Rva8CD3F0Value *top, int one1, int one2, int zero);

	int m_count;
	int m_unused;
	Rva8CD3F0Value **m_stack;
};

extern int g_rva8CD3F0RouteIndices[];
extern int g_bfmeRouteKeys1282[];

void rva8CD3F0ResolveValue(void *first, void *second, Rva8CD3F0Value *value,
	Rva8CD3F0Value **result);

void rva8CD3F0RouteDispatch(Rva8CD3F0State *state, Rva8CD3F0Context *context)
{
	Rva8CD3F0State *owner = state;
	int count = owner->m_count;
	Rva8CD3F0Value *top = owner->m_stack[count - 1];
	Rva8CD3F0Value *under = owner->m_stack[count - 2];
	Rva8CD3F0Value *candidate = owner->m_stack[count - 3];
	Rva8CD3F0Value *resolved;
	rva8CD3F0ResolveValue(context->m_first, context->m_second, candidate, &resolved);
	int routeIndex = under->toInteger();
	if (resolved != 0)
	{
		int keyIndex = g_rva8CD3F0RouteIndices[routeIndex];
		owner->append(resolved, context->m_second, &g_bfmeRouteKeys1282[keyIndex],
			top, 1, 1, 0);
	}

	for (int i = 1; i <= 3; ++i)
	{
		Rva8CD3F0Value *value = owner->m_stack[owner->m_count - i];
		unsigned char flags = (unsigned char)(value->m_flags >> 30);
		if (!(flags & 1))
			value->release();
	}
	owner->m_count -= 3;
}
