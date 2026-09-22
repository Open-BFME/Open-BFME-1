// ?bfmeGetOrCreateDefault@Rva008A78D0Owner@@QAEPAXHPAPAX@Z
// partial score=0.75 date=2026-09-22
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
//
// THIS REVISION (0.4 -> 0.75): the 0.4 candidate was missing retail's ENTIRE
// SEH/_except_handler3 frame (tools/eh_info.py 0x008A78D0 shows 3 unwind
// states, sizes 0x10/0x10/0x24 -- exactly sizeof(Rva008A9B00) for the two
// `new Rva008A9B00()` call sites and sizeof(BfmeA1029) for the third). The
// fix: the ctor declaration `__declspec(nothrow) Rva008A9B00();` was
// SUPPRESSING the compiler's automatic delete-on-throw wrap around the two
// `new Rva008A9B00()` expressions in THIS TU. Removing `__declspec(nothrow)`
// (declaration is TU-scoped -- Rva008AAFD0Factory.cpp, which independently
// lands byte-exact WITHOUT this wrap around the same ctor address, keeps its
// own nothrow declaration untouched) makes MSVC emit exactly the observed
// alloc -> [state=N] -> ctor-call -> [state=-1] shape and dropped the diff
// from 291B to 92B (object now 519B vs retail's 547B). Also repointed the
// free-list-head/registry globals from unpinned invented names
// (g_rva01338478Free, g_bfmeRegistryVNF) to the REAL pinned symbols already
// used by Rva008A9AB0ChainInsertRelease.cpp (extern Rva008A9B00
// *Rva008C3B60Head;) and matching a new Rva00899560Pool struct for
// g_rva8CD130IdleHook (0x01337810, mangled ?g_rva8CD130IdleHook@@3PAURva0
// 0899560Pool@@A) -- this didn't change the byte diff but is the honest fix
// (the old names were unpinned externs that happened to still compile).
//
// RESIDUAL (92B, two distinct issues, both isolated -- tried and ruled out
// separately, see reverse/re_attempts.log for this RVA):
//  1. The FIRST memcmp (n=8, offset+0x23..+0x33) compiles to `repe cmpsd`
//     (dword-granularity) here vs retail's `repe cmpsb` (byte-granularity).
//     The OTHER two memcmp calls in the same function (n=5, n=9 -- neither
//     a multiple of 4) already match retail's cmpsb byte-for-byte with NO
//     changes needed, so this is specific to n=8 being divisible by 4.
//     Tried and ruled out: /O1, /O2 without /Ob1, /Ox, unsigned char vs
//     char operand types, dropping `#pragma intrinsic(memcmp)`, and routing
//     all three calls through one shared __forceinline `bfmeNameMatches()`
//     helper (still resolves n as a compile-time constant per call site,
//     no change). NEXT LEVER TO TRY: whatever makes retail treat n=8 as
//     "not provably a multiple of 4" to the intrinsic -- maybe the real
//     source computes the length via a variable/field rather than a bare
//     literal `8`, or reads it as `sizeof` of a type the compiler can't
//     see through the same way our plain array can.
//  2. Branch 3 (BfmeA1029 default, offset ~+0x1a4 onward): retail's EH
//     state 2 stays ACTIVE (not reset to -1) through the bfmeGo1029A call
//     AND the subsequent flag-bit manipulation on obj->m_bfmeBits, only
//     clearing right before the final bfmeNotify() virtual call -- unlike
//     branches 1/2 where the state clears immediately after the ctor call
//     returns. Tried wrapping that whole span in an explicit
//     `try { ... } catch (...) { throw; }`: this produces a COMPLETELY
//     different (ebp-based, full catch-handler) frame shape, not retail's
//     simple cleanup-only funclet, so it's the wrong mechanism -- reverted.
//     Whatever extends the protection window here without a real
//     catch-block is still unknown; the cleanup handler itself (per
//     eh_info.py) is a plain `operator delete(obj, 0x24)`, so it must still
//     be some form of implicit new-expression-style protection, just with
//     a wider "still under construction" window than branches 1/2.

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

extern const char g_rva0112abcc[8];
extern const char g_rva0111195a0[5];
extern const char g_rva0113666c[9];

extern BfmeA1029 *g_rva01337abc;

extern void *Rva00897640(unsigned int bytes);

class Rva008A78D0Owned1029
{
public:
	static void *operator new(unsigned int bytes)
	{
		return Rva00897640(bytes);
	}

	__forceinline Rva008A78D0Owned1029(int value)
	{
		BfmeA1029 *obj = ((BfmeA1029 *)this)->bfmeGo1029A(value);
		g_rva01337abc = obj;

		Rva008991B0Flags *flags = (Rva008991B0Flags *)obj;
		flags->m_bfmeBits = (flags->m_bfmeBits & 0xffffc07f) | 0x40;
	}

	char m_storage[0x24];
};

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
	Rva008A9B00();

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
			obj->clearRegistered();
			return;
		}

		m_entries[index] = obj;
		++*pcount;
	}
};

extern Rva00899560Pool *g_rva8CD130IdleHook;
extern Rva008A9B00 *Rva008C3B60Head;

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
		Rva008A9B00 *obj = Rva008C3B60Head;

		if (obj != 0)
		{
			Rva008C3B60Head = obj->m_next;
			g_rva8CD130IdleHook->addOrClear(obj);

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
		Rva008A9B00 *obj = Rva008C3B60Head;

		if (obj != 0)
		{
			Rva008C3B60Head = obj->m_next;
			g_rva8CD130IdleHook->addOrClear(obj);

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
		BfmeA1029 *obj = g_rva01337abc;

		if (obj == 0)
		{
			new Rva008A78D0Owned1029(0xca62a0);
			((Rva008A78D0VBase *)g_rva01337abc)->bfmeNotify();
			obj = g_rva01337abc;
		}

		return obj;
	}

	return 0;
}
