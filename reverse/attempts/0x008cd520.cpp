// ?rva8CD520ConfigureState@@YAXPAVRva8CD520State@@PAURva8CD520Context@@@Z
// partial score=0.88 date=2026-09-02
// ?rva8CD520ConfigureState@@YAXPAVRva8CD520State@@PAURva8CD520Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva8CD520StringBlock { unsigned short m_refs; };
extern Rva8CD520StringBlock g_bfmeDefaultString1284;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class Rva8CD520String
{
public:
	Rva8CD520String()
	{
		m_block = &g_bfmeDefaultString1284;
		++m_block->m_refs;
	}
	~Rva8CD520String()
	{
		Rva8CD520StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			Rva01337A30ReleaseTable[1](block);
	}
	Rva8CD520StringBlock *m_block;
};

class Rva8CD520Value
{
public:
	virtual void addRef();
	virtual void release();
	float toFloat();
	unsigned m_flags;
	char m_gap08[0x18];
	union { Rva8CD520Value *m_inner; float m_x; };
	float m_y;
};

class Rva8CD520State
{
public:
	Rva8CD520Value *resolve(void *, void *, Rva8CD520String *, int, int, int);
	void popValues(int count);
	int m_count;
	int m_unused;
	Rva8CD520Value **m_stack;
};

struct Rva8CD520Context { void *m_zero; void *m_owner; void *m_scope; };

struct Rva8CD520Packet
{
	char m_gap0000[0x1240];
	Rva8CD520Value *m_value;
	float m_a;
	float m_b;
	float m_c;
	float m_d;
	float m_x;
	float m_y;
	char m_gap125c[0x18];
	int m_width;
	int m_height;
};

extern Rva8CD520Packet *g_rva8CD520Packet;
extern void rva8C6320Resolve(void *, void *, void *, int *, Rva8CD520String *);

static int rva8CD520Type(Rva8CD520Value *value) { return value->m_flags & 0x3f; }
void rva8CD520ConfigureState(Rva8CD520State *state, Rva8CD520Context *context)
{
	Rva8CD520Value *value = state->m_stack[state->m_count - 1];
	int type = rva8CD520Type(value);
	if ((type == 1 || type == 0x2a) &&
		!((unsigned char)(~(value->m_flags >> 15)) & 1))
	{
		Rva8CD520String name;
		if (rva8CD520Type(value) != 1)
			value = value->m_inner;
		int output = 0;
		rva8C6320Resolve(context->m_owner, context->m_scope,
			(char *)value + 8, &output, &name);
		value = state->resolve(context->m_owner, context->m_scope, &name, 1, 1, 0);
	}

	value->addRef();
	g_rva8CD520Packet->m_value = value;
	g_rva8CD520Packet->m_x = 0.0f;
	g_rva8CD520Packet->m_y = 0.0f;
	g_rva8CD520Packet->m_a = -9999.0f;
	g_rva8CD520Packet->m_b = -9999.0f;
	g_rva8CD520Packet->m_c = -9999.0f;
	g_rva8CD520Packet->m_d = -9999.0f;

	Rva8CD520Value *position = state->m_stack[state->m_count - 2];
	if (rva8CD520Type(position) != 7 ||
		((unsigned char)(~(position->m_flags >> 15)) & 1))
	{
		g_rva8CD520Packet->m_x = (float)g_rva8CD520Packet->m_width - value->m_x;
		g_rva8CD520Packet->m_y = (float)g_rva8CD520Packet->m_height - value->m_y;
	}

	int popCount = 3;
	Rva8CD520Value *quad = state->m_stack[state->m_count - 3];
	if (rva8CD520Type(quad) == 7 &&
		!((unsigned char)(~(quad->m_flags >> 15)) & 1))
	{
		popCount = 7;
		g_rva8CD520Packet->m_d = state->m_stack[state->m_count - 4]->toFloat();
		g_rva8CD520Packet->m_c = state->m_stack[state->m_count - 5]->toFloat();
		g_rva8CD520Packet->m_b = state->m_stack[state->m_count - 6]->toFloat();
		g_rva8CD520Packet->m_a = state->m_stack[state->m_count - 7]->toFloat();
	}
	state->popValues(popCount);
}
