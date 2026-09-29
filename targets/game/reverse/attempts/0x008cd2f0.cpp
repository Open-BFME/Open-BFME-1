// ?rva8CD2F0GetProperty@@YAXPAVRva8CD2F0State@@PAURva8CD2F0Context@@@Z
// partial score=0.9685 date=2026-09-30
// ?rva8CD2F0GetProperty@@YAXPAVRva8CD2F0State@@PAURva8CD2F0Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// EA Apt ActionScript GetProperty (opcode 0x22), retail 0x008CD2F0: slot 0x22
// of the opcode table based at 0x00ED5A68 (see
// AptActionInterpreterStoreRegister.cpp), at 0x00ED5AF0.  The mirror of the
// landed SetProperty handler (Rva8CD3F0RouteDispatch.cpp, 0x008CD3F0): the
// target below the property index is resolved (rva8CCCE0ResolveValue), the
// index is mapped through the same route tables to a property key, and the
// property value is fetched with the interpreter's createString (0x008CC940,
// as EnsureName008CDAD0.cpp calls it).  Both operands are popped and the
// value -- or the fallback value when the target does not resolve -- is
// pushed.

class BfmeStrVKI;
class Rva00899770;

class Rva8CCCE0Value
{
public:
	virtual void addRef();
	virtual void release();
	int toInteger() const;

	unsigned m_flags;
};

struct Rva8CD2F0Context
{
	int m_unused;
	void *m_first;
	void *m_second;
};

class Rva008AE770Stack
{
public:
	Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int);
};

class Rva8CD2F0State
{
public:
	int m_count;
	int m_unused;
	Rva8CCCE0Value **m_stack;
};

extern int g_rva8CD3F0RouteIndices[];
extern int g_bfmeRouteKeys1282[];
extern Rva8CCCE0Value *g_bfmeFallbackDB;

void rva8CCCE0ResolveValue(void *first, void *second, Rva8CCCE0Value *value,
	Rva8CCCE0Value **result);

void rva8CD2F0GetProperty(Rva8CD2F0State *state, Rva8CD2F0Context *context)
{
	Rva8CCCE0Value *top = state->m_stack[state->m_count - 1];
	Rva8CCCE0Value *under = state->m_stack[state->m_count - 2];
	Rva8CCCE0Value *resolved;
	rva8CCCE0ResolveValue(context->m_first, context->m_second, under, &resolved);
	Rva8CCCE0Value *target = resolved;
	if (target != 0)
	{
		int keyIndex = g_rva8CD3F0RouteIndices[top->toInteger()];
		Rva8CCCE0Value *value = (Rva8CCCE0Value *)((Rva008AE770Stack *)state)->createString(
			target, (int)context->m_second, (BfmeStrVKI *)&g_bfmeRouteKeys1282[keyIndex], 1, 1, 0);
		for (int i = 1; i <= 2; ++i)
		{
			Rva8CCCE0Value *old = state->m_stack[state->m_count - i];
			if (!((unsigned char)(old->m_flags >> 30) & 1))
				old->release();
		}
		state->m_count -= 2;
		state->m_stack[state->m_count++] = value;
		if (!((unsigned char)(value->m_flags >> 30) & 1))
			value->addRef();
	}
	else
	{
		for (int i = 1; i <= 2; ++i)
		{
			Rva8CCCE0Value *old = state->m_stack[state->m_count - i];
			if (!((unsigned char)(old->m_flags >> 30) & 1))
				old->release();
		}
		state->m_count -= 2;
		Rva8CCCE0Value *fallback = g_bfmeFallbackDB;
		state->m_stack[state->m_count++] = fallback;
		if (!((unsigned char)(fallback->m_flags >> 30) & 1))
			fallback->addRef();
	}
}
