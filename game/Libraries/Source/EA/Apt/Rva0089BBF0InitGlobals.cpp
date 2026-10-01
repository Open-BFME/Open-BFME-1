// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0089BBF0 (1684 bytes): an Apt start-up routine that builds a set
// of value singletons into globals, resets two float blocks, clears a
// four-word block and ends by running the idle hook.  Its sole caller is the
// gen dump at 0x00894800.  The owner and the real name are not recovered, so
// the function keeps its address token.
//
// WHAT THE BYTES PROVE.
//  * Three allocation policies.  Kind3, KindB, Rva008D2B10 and Rva008A9B00 are
//    allocated straight through the allocator pointer at 0x01337828; the
//    registry values (0x18/0x20/0x24 bytes) go through the eight-byte-headered
//    allocator inline (alloc(size + 8) + 8, then the list push at 0x00897300),
//    which is the body of the fifteen WideHeaderedAlloc copies.
//  * The retail unwind map (FuncInfo 0x01246DD0, 15 states) names every
//    new-expression cleanup: state 0 sized-frees 0x3C0 bytes through
//    0x008979B0; states 1-6 go to the class operators delete at 0x00897790,
//    0x008977F0, 0x00897850, 0x008978B0, 0x00897910 and 0x00897970; state 7
//    frees 16 bytes through 0x00891A80 (the pinned Rva008A9B00 delete); states
//    8-14 all free 0x24 bytes through 0x00897670.  Kind3 and KindB get NO
//    state, so from this TU their constructors cannot throw.
//  * The 0x24-byte values are the standalone constructor at 0x00899FC0
//    (BfmeA1029: base(9, 8), callback at +0x20, vftable 0x01136128) inlined;
//    the 0x20-byte one is the constructor at 0x0089A460 (BfmeThingVDW) inlined.
//  * The pooled-string path is the same free-list reuse the matched
//    Rva008A78D0 body inlines (head 0x01338478, pool 0x01337810, shared empty
//    string 0x012D5298).
//
// Flag words are named by bit position only: bits 6-13 and bits 16-27 of the
// word at +4.

extern void *(*Rva008C5D70Alloc)(unsigned int bytes);
void Gen00897300(void *block);

extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

// ---- allocation policies ------------------------------------------------

struct Rva0089BBF0PlainNew
{
	static void *operator new(unsigned int bytes)
	{
		return Rva008C5D70Alloc(bytes);
	}
};

class Rva00897790HeaderedDelete { public: static void operator delete(void *storage, unsigned int size); };
class Rva008977F0HeaderedDelete { public: static void operator delete(void *storage, unsigned int size); };
class Rva00897850HeaderedDelete { public: static void operator delete(void *storage, unsigned int size); };
class Rva008978B0HeaderedDelete { public: static void operator delete(void *storage, unsigned int size); };
class Rva00897910HeaderedDelete { public: static void operator delete(void *storage, unsigned int size); };
class Rva00897970HeaderedDelete { public: static void operator delete(void *storage, unsigned int size); };
class Rva00897670HeaderedDelete { public: static void operator delete(void *storage, unsigned int size); };

template <class Delete>
struct Rva0089BBF0HeaderedNew : public Delete
{
	static void *operator new(unsigned int bytes)
	{
		char *raw = (char *)Rva008C5D70Alloc(bytes + 8);
		char *block = raw + 8;
		Gen00897300(block);
		return block;
	}
};

// ---- value classes ------------------------------------------------------

class BfmeDerivedKind3 : public Rva0089BBF0PlainNew
{
public:
	BfmeDerivedKind3() throw();

	void *m_vfptr;
	unsigned int m_flags;
};

class BfmeDerivedKindB : public Rva0089BBF0PlainNew
{
public:
	BfmeDerivedKindB() throw();

	void *m_vfptr;
	unsigned int m_flags;
};

class Rva008D2B10 : public Rva0089BBF0PlainNew
{
public:
	Rva008D2B10();
	static void operator delete(void *storage, unsigned int size);

	char m_body[0x3c0];
};

class Rva89A2C0Derived : public Rva0089BBF0HeaderedNew<Rva00897790HeaderedDelete>
{
public:
	Rva89A2C0Derived();

	void *m_vfptr;
	unsigned int m_flags;
	char m_state[0x10];
};

class Rva89A540Derived : public Rva0089BBF0HeaderedNew<Rva00897850HeaderedDelete>
{
public:
	Rva89A540Derived();

	void *m_vfptr;
	unsigned int m_flags;
	char m_state[0x10];
};

class Rva89A6E0Derived : public Rva0089BBF0HeaderedNew<Rva008978B0HeaderedDelete>
{
public:
	Rva89A6E0Derived();

	void *m_vfptr;
	unsigned int m_flags;
	char m_state[0x10];
};

class Rva89A880Derived : public Rva0089BBF0HeaderedNew<Rva00897910HeaderedDelete>
{
public:
	Rva89A880Derived();

	void *m_vfptr;
	unsigned int m_flags;
	char m_state[0x10];
};

class Rva89AA20Derived : public Rva0089BBF0HeaderedNew<Rva00897970HeaderedDelete>
{
public:
	Rva89AA20Derived();

	void *m_vfptr;
	unsigned int m_flags;
	char m_state[0x10];
};

struct Rva0089BBF0Bits
{
	unsigned int m_bits0to5 : 6;
	unsigned int m_bits6to13 : 8;
	unsigned int m_bits14to15 : 2;
	unsigned int m_bits16to27 : 12;
	unsigned int m_bits28to31 : 4;

	__forceinline void clearBits6to13()
	{
		m_bits6to13 = 0;
	}

	__forceinline void setBit6()
	{
		*(unsigned int *)this |= 0x40;
	}
};

class Rva00899F00Base
{
public:
	Rva00899F00Base(unsigned int argument0, int argument1);

	void *m_vfptr;
	union
	{
		unsigned int m_flags;
		Rva0089BBF0Bits m_bits;
	};
	char m_body[0x18];
};

extern char g_bfmeVftVDW[];
extern "C" void *bfmeVft1029A[];

class BfmeThingVDW :
	public Rva0089BBF0HeaderedNew<Rva008977F0HeaderedDelete>,
	public Rva00899F00Base
{
public:
	BfmeThingVDW() : Rva00899F00Base(0x18, 8)
	{
		m_vfptr = g_bfmeVftVDW;
		m_flags = (m_flags & 0xffffc07f) | 0x0fff0040;
	}
};

class BfmeA1029 :
	public Rva0089BBF0HeaderedNew<Rva00897670HeaderedDelete>,
	public Rva00899F00Base
{
public:
	BfmeA1029(int callback) : Rva00899F00Base(9, 8)
	{
		m_vfptr = bfmeVft1029A;
		m_callback = callback;
	}

	int m_callback;
};

// ---- pooled string value ------------------------------------------------

struct Rva00891B80Block
{
	unsigned short m_ref;
};

extern Rva00891B80Block g_default012D5298;

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
};

class Rva008A9B00 : public Rva0089BBF0PlainNew
{
public:
	Rva008A9B00();
	static void operator delete(void *storage, unsigned int size);

	void *m_vptr;
	unsigned m_flags;
	Rva00891B80Block *m_block;
	Rva008A9B00 *m_next;
};

class Rva0089BBF0Notify
{
public:
	virtual void notify();
};

struct Rva00899560Pool
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void addOrClear(Rva008A9B00 *obj)
	{
		int index = m_count;
		int *pcount = &m_count;
		int cap = m_capacity;
		if (index >= cap)
		{
			obj->m_flags &= ~0x40000000;
			return;
		}

		m_entries[index] = obj;
		++*pcount;
	}
};

class Rva8CD130IdleHook
{
public:
	void run();
};

extern Rva00899560Pool *g_rva8CD130IdleHook;
extern Rva008A9B00 *Rva008C3B60Head;

extern void __cdecl d_0089abc0();

// value callbacks installed at BfmeA1029+0x20
extern void __cdecl d_008c64c0();
extern void __cdecl d_008c66a0();
class AptBoolean;
extern AptBoolean *__cdecl rva008C6800(void *, int);
class AptValue;
extern AptValue *__cdecl rva008C4F90(void *, int);
extern void __cdecl d_008c6ad0();
Rva008A9B00 *rva008C6840StringTransform();
Rva008A9B00 *rva008C6990StringTransform(void *unknown, int count);

// ---- globals written by the body ----------------------------------------

struct Rva0089BBF0ColorTransform
{
	float m_mul[4];
	float m_add[4];
};

struct Rva0089BBF0Matrix
{
	float m_a;
	float m_b;
	float m_c;
	float m_d;
	float m_tx;
	float m_ty;
};

// The globals below carry retail's own names.  Each address is already
// named in dir32_addresses.csv, so the declared type here is the one the
// name mangles with; the value stored is the object this body builds, cast
// to that pointer.  No member of any of these types is touched here.

// Defining name at 0x00F379BC: a global int (BfmeConv568.cpp reads it as
// one), holding the kind-3 registry value as an address.
extern int bfmeTheCBC;
// Defining name at 0x00F37A04: a global int holding the 0x3C0-byte value.
extern int g_bfmeB1038;
// Defining name at 0x00F37A20: pointer to Rva00898D60Target, the class the
// matched 0x00898D60 body chains through (Rva00898D60GlobalTail.cpp).
class Rva00898D60Target;
extern Rva00898D60Target *g_Rva01337A20;
extern Rva89A2C0Derived *g_Va013379B4;
extern BfmeThingVDW *g_Va013379FC;
extern Rva89A540Derived *g_Va013379AC;
// Defining name at 0x00F387D8: pointer to Rva00899C20Registry, the
// find-1024 registry the matched 0x00899C20 body searches.
struct Rva00899C20Registry;
extern Rva00899C20Registry *g_Va013387D8;
// Defining name at 0x00F3846C: pointer to BfmeMap1024, the map the matched
// BfmeConv1024 body probes (BfmeConv1024.cpp).
struct BfmeMap1024;
extern BfmeMap1024 *g_bfmeMap1024;
extern Rva89AA20Derived *g_Va01337A00;
extern Rva008A9B00 *g_Va013379F0;
// Defining name at 0x00F37A28: the lazily built Apt global table, spelled
// void* by the matched 0x00899800 body (Rva00899800TableSet.cpp).
extern void *g_Rva01337A28Index;
extern Rva0089BBF0ColorTransform g_Va013379CC;
// Defining name at 0x00F37A08: the C-linkage 2x3 matrix block.
extern "C" Rva0089BBF0Matrix g_bfmeD1206;
extern BfmeA1029 *g_Va013379EC;
extern BfmeA1029 *g_Va013379C4;
extern BfmeA1029 *g_Va013379C8;
extern BfmeA1029 *g_Va013379F8;
extern BfmeA1029 *g_Va013379B8;
extern BfmeA1029 *g_Va013379B0;
extern BfmeA1029 *g_Va01337A2C;
extern void *g_Va013387B0[4];

// ---- helpers ------------------------------------------------------------

// Two separate inline calls on the flag word's sub-object: retail keeps both
// stores (bits 6-13 cleared, then bit 6 set) through the materialised
// sub-object pointer.
static __forceinline void rva0089BBF0ResetBits6to13(BfmeA1029 *value)
{
	value->m_bits.clearBits6to13();
	value->m_bits.setBit6();
}

static __forceinline Rva008A9B00 *rva0089BBF0CreateString()
{
	Rva008A9B00 *string = Rva008C3B60Head;
	if (string != 0)
	{
		Rva008C3B60Head = string->m_next;
		g_rva8CD130IdleHook->addOrClear(string);
		if (string->m_block != &g_default012D5298)
			((BfmeStrVKK *)&string->m_block)->bfmeTruncVKK(0);
		return string;
	}

	return new Rva008A9B00();
}

// ---- the body -----------------------------------------------------------

void Rva0089BBF0InitGlobals()
{
	BfmeDerivedKind3 *kind3 = new BfmeDerivedKind3();
	bfmeTheCBC = (int)kind3;
	Rva008D2B10 *d2b10 = new Rva008D2B10();
	g_bfmeB1038 = (int)d2b10;
	BfmeDerivedKindB *kindB = new BfmeDerivedKindB();
	g_Rva01337A20 = (Rva00898D60Target *)kindB;
	Rva89A2C0Derived *a2c0 = new Rva89A2C0Derived();
	g_Va013379B4 = a2c0;
	BfmeThingVDW *vdw = new BfmeThingVDW();
	g_Va013379FC = vdw;
	Rva89A540Derived *a540 = new Rva89A540Derived();
	g_Va013379AC = a540;
	Rva89A6E0Derived *a6e0 = new Rva89A6E0Derived();
	g_Va013387D8 = (Rva00899C20Registry *)a6e0;
	Rva89A880Derived *a880 = new Rva89A880Derived();
	g_bfmeMap1024 = (BfmeMap1024 *)a880;
	Rva89AA20Derived *aa20 = new Rva89AA20Derived();
	g_Va01337A00 = aa20;

	Rva008A9B00 *string = rva0089BBF0CreateString();
	g_Va013379F0 = string;
	string->m_flags = (string->m_flags & 0xffffc03f) | 0x40;
	((Rva0089BBF0Notify *)g_Va013379F0)->notify();

	g_Rva01337A28Index = (void *)0;
	d_0089abc0();

	g_Va013379CC.m_mul[0] = 1.0f;
	g_Va013379CC.m_mul[1] = 1.0f;
	g_Va013379CC.m_mul[2] = 1.0f;
	g_Va013379CC.m_mul[3] = 1.0f;
	g_Va013379CC.m_add[0] = 0.0f;
	g_Va013379CC.m_add[1] = 0.0f;
	g_Va013379CC.m_add[2] = 0.0f;
	g_Va013379CC.m_add[3] = 0.0f;
	g_bfmeD1206.m_a = 1.0f;
	g_bfmeD1206.m_b = 0.0f;
	g_bfmeD1206.m_c = 0.0f;
	g_bfmeD1206.m_d = 1.0f;
	g_bfmeD1206.m_tx = 0.0f;
	g_bfmeD1206.m_ty = 0.0f;

	BfmeA1029 *value = new BfmeA1029(reinterpret_cast<int>(&d_008c64c0));
	g_Va013379EC = value;
	value->m_bits.m_bits16to27 = 100;
	rva0089BBF0ResetBits6to13(g_Va013379EC);

	value = new BfmeA1029(reinterpret_cast<int>(&d_008c66a0));
	g_Va013379C4 = value;
	value->m_bits.m_bits16to27 = 100;
	rva0089BBF0ResetBits6to13(g_Va013379C4);

	value = new BfmeA1029(reinterpret_cast<int>(&rva008C6800));
	g_Va013379C8 = value;
	value->m_bits.m_bits16to27 = 100;
	rva0089BBF0ResetBits6to13(g_Va013379C8);

	value = new BfmeA1029(reinterpret_cast<int>(&rva008C6840StringTransform));
	g_Va013379F8 = value;
	value->m_bits.m_bits16to27 = 100;
	rva0089BBF0ResetBits6to13(g_Va013379F8);

	value = new BfmeA1029(reinterpret_cast<int>(&rva008C6990StringTransform));
	g_Va013379B8 = value;
	value->m_bits.m_bits16to27 = 100;
	rva0089BBF0ResetBits6to13(g_Va013379B8);

	value = new BfmeA1029(reinterpret_cast<int>(&d_008c6ad0));
	g_Va013379B0 = value;
	value->m_bits.m_bits16to27 = 100;
	rva0089BBF0ResetBits6to13(g_Va013379B0);

	value = new BfmeA1029(reinterpret_cast<int>(&rva008C4F90));
	g_Va01337A2C = value;
	value->m_bits.m_bits16to27 = 100;
	rva0089BBF0ResetBits6to13(g_Va01337A2C);

	memset(&g_Va013387B0, 0, sizeof(g_Va013387B0));
	((Rva8CD130IdleHook *)g_rva8CD130IdleHook)->run();
}
