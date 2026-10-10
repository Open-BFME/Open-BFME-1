// ?rva8CD520ConfigureState@@YAXPAVRva8CD520State@@PAURva8CD520Context@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Apt handler 0x008CD520: resolve a string target, store it with offset and bounds, pop 3 or 7 values.

struct Rva8CD520StringBlock { unsigned short m_refs; };
// Retail 0x008CD56C/577 use the empty block at VA 0x012D5298;
// 0x008CD5E6 loads the allocation pair at VA 0x01337A30, then calls
// its second slot with one pointer and caller cleanup. Both have owners.
class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

class Rva8CD520String
{
public:
	Rva8CD520String()
	{
		m_block = reinterpret_cast<Rva8CD520StringBlock *>(&g_rva012D5298Empty);
		++m_block->m_refs;
	}
	~Rva8CD520String()
	{
		Rva8CD520StringBlock *block = m_block;
		--block->m_refs;
		if (block->m_refs == 0)
			reinterpret_cast<void (__cdecl **)(void *)>(g_rva01337A30AllocPair)[1](block);
	}
	Rva8CD520StringBlock *m_block;
};

class AptValue
{
public:
	float toNumber();
};

class Rva8CD520Value
{
public:
	virtual void addRef();
	virtual void release();
	bool isUndefined() const
	{
		return ((unsigned char)~(m_flags >> 15) & 1) != 0;
	}
	bool isString() const
	{
		return ((m_flags & 63) == 1 || (m_flags & 63) == 42) && !isUndefined();
	}
	__forceinline bool isType(int t) const { return (m_flags & 63) == t && !isUndefined(); }
	Rva8CD520String &string()
	{
		int type = m_flags & 63;
		return *(Rva8CD520String *)((char *)(type == 1 ? this : m_inner) + 8);
	}
	float toFloat() { return ((AptValue *)this)->toNumber(); }
	unsigned m_flags;
	char m_gap08[0x18];
	union { Rva8CD520Value *m_inner; float m_x; };
	float m_y;
};

class BfmeStrVKI;
class Rva00899770;
// Body at 0x008cc940: ?d_008cc940@@YAXXZ. The retail callee is linked as a
// cdecl void() body, so the thiscall state method is recovered through a
// member-pointer call (the pattern aptExportString.cpp uses).
struct Rva008AE770Stack
{
};

extern void d_008cc940();

class BfmeA1232
{
public:
	void bfmePop1232(int);
};

class Rva8CD520State
{
public:
	Rva8CD520Value *top(int i) { return m_stack[m_count - 1 - i]; }
	void popValues(int count) { ((BfmeA1232 *)this)->bfmePop1232(count); }
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

// Retail loads from 0x008CD5FC onward read the canonical VA 0x013377D8
// pointer defined by BfmePicker1284.cpp. Retain only this TU's packet view.
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;
extern void d_008c6320();
typedef void (__cdecl *Rva8CD520ResolveName)(void *, void *, Rva8CD520String *, void **,
	Rva8CD520String *);

void rva8CD520ConfigureState(Rva8CD520State *state, Rva8CD520Context *context)
{
	Rva8CD520Value *value = state->top(0);
	if (value->isString())
	{
		void *output = 0;
		Rva8CD520String name;
		((Rva8CD520ResolveName)d_008c6320)(context->m_owner, context->m_scope,
			&value->string(), &output, &name);
		typedef Rva00899770 *(Rva008AE770Stack::*Fn)(void *, int, BfmeStrVKI *, int, int, int);
		union { void (*fn)(); Fn call; } u = { d_008cc940 };
		value = (Rva8CD520Value *)(((Rva008AE770Stack *)state)->*u.call)(output,
			(int)context->m_scope, (BfmeStrVKI *)&name, 1, 1, 0);
	}

	int popCount = 3;
	value->addRef();
	reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_value = value;
	reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_x = 0.0f;
	reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_y = 0.0f;
	reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_a = -9999.0f;
	reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_b = -9999.0f;
	reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_c = -9999.0f;
	reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_d = -9999.0f;

	if (!state->top(1)->isType(7))
	{
		reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_x = (float)reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_width - value->m_x;
		reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_y = (float)reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_height - value->m_y;
	}

	if (state->top(2)->isType(7))
	{
		popCount = 7;
		reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_d = state->top(3)->toFloat();
		reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_c = state->top(4)->toFloat();
		reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_b = state->top(5)->toFloat();
		reinterpret_cast<Rva8CD520Packet *>(g_bfmeHolderBU)->m_a = state->top(6)->toFloat();
	}
	state->popValues(popCount);
}
