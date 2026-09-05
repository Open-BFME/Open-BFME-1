// ?bfmeGetOrCreateDefault@Rva008A78D0Owner@@QAEPAXHPAPAX@Z
// partial score=0.4 date=2026-09-05
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME5 conversion from Code/gen_asm/d_008592e0.asm.
//
// Three lazily constructed per-type default singletons, gated on a fixed
// byte compare of a name buffer (offset 8 of *arg2) against three constant
// templates. The first two reuse (or freshly allocate) a Rva008A9B00 object
// -- the exact class and free-list/registry recycling shape already landed
// in Rva008AAFD0Factory.cpp -- and append it through this object's own
// per-slot pointer (this+0x20 / this+0x24) via the still-dump
// Rva008B2EA0Node::append. The third builds a BfmeA1029 default (see
// BfmeConv1029.cpp) through bfmeGo1029A and gives it the same one-time
// registered-flag-and-notify tail as 0x008A7270.
//
// IDENTITY IS NOT RECOVERED: the owning class, the real parameter types and
// the meaning of the three 8/5/9-byte name templates are unknown; only the
// byte shape is proven. Names are address-derived.

extern "C" void *(*WideAllocPtr)(unsigned int bytes);

class BfmeItemDX;
extern void __cdecl bfmePush(BfmeItemDX *item);

extern "C" void *bfmeVft1029A[];

class BfmeA1029
{
public:
	BfmeA1029 *bfmeGo1029A(int a);

	void *m_bfmeVfptr;
	char m_bfmePad[0x1c];
	int m_bfmeVal;
};

class Rva008991B0Flags
{
public:
	int m_bfmeHead;
	unsigned int m_bfmeBits;
};

class Rva008A78D0VBase
{
public:
	virtual void bfmeNotify();
};

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);
#pragma intrinsic(memcmp)

extern const char g_rva0112abcc[8];
extern const char g_rva0111195a0[5];
extern const char g_rva0113666c[9];

extern BfmeA1029 *g_rva01337abc;

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

class Rva008A9B00
{
public:
	__declspec(nothrow) Rva008A9B00();

	void *operator new(unsigned int bytes)
	{
		return WideAllocPtr(bytes);
	}

	__forceinline void clearRegistered()
	{
		m_flags &= ~0x40000000;
	}

	void *m_vptr;
	unsigned m_flags;
	Rva00891B80Block *m_block;
	Rva008A9B00 *m_next;
};

struct BfmeRegistryKind1
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
			obj->clearRegistered();
			return;
		}

		m_entries[index] = obj;
		++*pcount;
	}
};

extern "C" BfmeRegistryKind1 *g_bfmeRegistryVNF;

class Rva008B2EA0Node
{
public:
	void append(void *node);
};

class Rva008A78D0Owner
{
public:
	void *bfmeGetOrCreateDefault(int unused, void **arg2);

	char m_pad0[0x20];
	void *m_slot20;
	void *m_slot24;
};

void *Rva008A78D0Owner::bfmeGetOrCreateDefault(int unused, void **arg2)
{
	if (memcmp((const char *)*arg2 + 8, g_rva0112abcc, 8) == 0)
	{
		extern Rva008A9B00 *g_rva01338478Free;

		Rva008A9B00 *obj = g_rva01338478Free;

		if (obj != 0)
		{
			g_rva01338478Free = obj->m_next;
			g_bfmeRegistryVNF->addOrClear(obj);

			if (obj->m_block != &g_default012D5298)
				((BfmeStrVKK *)&obj->m_block)->bfmeTruncVKK(0);
		}
		else
		{
			obj = new Rva008A9B00();
		}

		void *arg = (char *)m_slot20 + 8;
		((Rva008B2EA0Node *)obj)->append(arg);

		return obj;
	}

	if (memcmp((const char *)*arg2 + 8, g_rva0111195a0, 5) == 0)
	{
		extern Rva008A9B00 *g_rva01338478Free;

		Rva008A9B00 *obj = g_rva01338478Free;

		if (obj != 0)
		{
			g_rva01338478Free = obj->m_next;
			g_bfmeRegistryVNF->addOrClear(obj);

			if (obj->m_block != &g_default012D5298)
				((BfmeStrVKK *)&obj->m_block)->bfmeTruncVKK(0);
		}
		else
		{
			obj = new Rva008A9B00();
		}

		void *arg = (char *)m_slot24 + 8;
		((Rva008B2EA0Node *)obj)->append(arg);

		return obj;
	}

	if (memcmp((const char *)*arg2 + 8, g_rva0113666c, 9) == 0)
	{
		extern void *Rva00897640(unsigned int bytes);

		BfmeA1029 *obj = g_rva01337abc;

		if (obj == 0)
		{
			obj = (BfmeA1029 *)Rva00897640(0x24);

			if (obj != 0)
				obj = obj->bfmeGo1029A(0xca62a0);

			g_rva01337abc = obj;

			Rva008991B0Flags *flags = (Rva008991B0Flags *)obj;
			flags->m_bfmeBits = (flags->m_bfmeBits & 0xffffc07f) | 0x40;

			((Rva008A78D0VBase *)obj)->bfmeNotify();

			obj = g_rva01337abc;
		}

		return obj;
	}

	return 0;
}
