// ?Rva008B4DA0@@YGPAXPAXPBUBfmeCandidateDX@@@Z
// partial score=0.6 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x008B4DA0 (674 bytes), a __stdcall(unused, BfmeCandidateDX*) lookup
// over four fixed candidate descriptors (pointer-identity short-circuit, else
// ?bfmeCompareVSC@@YAHPBD0@Z on the name past the tag), lazily building and
// caching a singleton per candidate.
//
// All four singletons share the exact class BfmeConv1029.cpp already lands
// as BfmeA1029 (vtable 0x01136128, layout vfptr/pad[0x1c]/m_bfmeVal@+0x20).
// Candidates 2/3 reach it the shared way, through Rva00897640(0x24) then
// BfmeA1029::bfmeGo1029A(constant). Candidates 0/1 build the SAME shape
// through their own class-scope operator new (a WideAlloc-family allocator
// sized for this object plus its 8-byte link header) instead of the free
// Rva00897640 helper, so the base-init call (BfmeA1029::bfmeBase1029, the
// same body as ??0Rva00899F00Base@@QAE@IH@Z) and the vtable/tag stores are
// inlined here rather than reached through BfmeA1029::bfmeGo1029A -- and,
// unlike bfmeGo1029A's callers, they also register the new singleton (clear
// bits 7-13, set bit 6 of the packed-bits field at +4) and bump the shared
// saturating counter through the object's own vtable slot 0, but ONLY the
// first time each singleton is built.
//
// Identity is not recovered for the descriptor type, the four candidate
// globals or the two singleton-building classes; all are address-derived.

extern "C" void * (*WideAllocPtr)(unsigned int bytes);
void Gen00897300(void *block);
int __cdecl bfmeCompareVSC(const char *a, const char *b);
void *__cdecl Rva00897640(unsigned int bytes);
extern "C" void *bfmeVft1029A[];

// upstream layout: Code/GameEngine/Source/Common/BfmeConv1029.cpp
class BfmeA1029
{
public:
	BfmeA1029 *bfmeGo1029A(int a);
	void bfmeBase1029(int n, int m);

	void	*m_bfmeVfptr;
	char	m_bfmePad[0x1c];
	int		m_bfmeVal;
};

// The real body reached through vtable 0x01136128 slot 0 is
// Gen_008991B0::bfmeBump (Bfme5FiftyFour.cpp); this view exists only to get
// the virtual-thiscall call shape right, not to supply a body.
class BfmeA1029BumpView
{
public:
	virtual void bfmeBump();
};

struct BfmeCandidateDX
{
	const void	*m_tag;		// +0x00
	const void	*m_reserved;	// +0x04
	const char	m_name[1];	// +0x08
};

extern BfmeCandidateDX g_bfmeCandidate0;	// retail 0x013386A0
extern BfmeCandidateDX g_bfmeCandidate1;	// retail 0x01338594
extern BfmeCandidateDX g_bfmeCandidate2;	// retail 0x013385A4
extern BfmeCandidateDX g_bfmeCandidate3;	// retail 0x013386AC

extern BfmeA1029 *g_bfmeSingleton0;	// retail 0x01338388
extern BfmeA1029 *g_bfmeSingleton1;	// retail 0x0133838C
extern BfmeA1029 *g_bfmeSingleton2;	// retail 0x01338390
extern BfmeA1029 *g_bfmeSingleton3;	// retail 0x01338394

static void bfmeSetRegisteredFlag(BfmeA1029 *obj)
{
	unsigned int *bits = (unsigned int *)((char *)obj + 4);
	*bits = (*bits & 0xffffc07f) | 0x40;
}

// Keeps the four near-identical candidate blocks below from being folded
// into one shared body: retail lays each one out separately in full.
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

class BfmeCandidateSingleton0 : public BfmeA1029
{
public:
	void *operator new(unsigned int n) throw()
	{
		char *block = (char *)WideAllocPtr(n + 8) + 8;
		Gen00897300(block);
		return block;
	}
	void operator delete(void *) { }

	BfmeCandidateSingleton0();
};

__forceinline BfmeCandidateSingleton0::BfmeCandidateSingleton0()
{
	bfmeBase1029(9, 8);
	m_bfmeVfptr = bfmeVft1029A;
	m_bfmeVal = 0xcb4370;
}

class BfmeCandidateSingleton1 : public BfmeA1029
{
public:
	void *operator new(unsigned int n) throw()
	{
		char *block = (char *)WideAllocPtr(n + 8) + 8;
		Gen00897300(block);
		return block;
	}
	void operator delete(void *) { }

	BfmeCandidateSingleton1();
};

__forceinline BfmeCandidateSingleton1::BfmeCandidateSingleton1()
{
	bfmeBase1029(9, 8);
	m_bfmeVfptr = bfmeVft1029A;
	m_bfmeVal = 0xcb4420;
}

// ?Rva008B4DA0@@YGPAXPAXPBUBfmeCandidateDX@@@Z
//
// Written as explicit fallthrough-or-goto rather than four "if (a || b)
// { body }" blocks: with the OR form the compiler pulls each body out of
// line to a shared tail, which retail does not do -- every candidate here
// keeps its own inline body immediately after its own check.
void *__stdcall Rva008B4DA0(void *unused, const BfmeCandidateDX *desc)
{
	if (desc->m_tag != g_bfmeCandidate0.m_tag)
	{
		if (bfmeCompareVSC(desc->m_name, g_bfmeCandidate0.m_name) != 0)
			goto try_candidate1;
	}

	if (g_bfmeSingleton0 == 0)
	{
		g_bfmeSingleton0 = new BfmeCandidateSingleton0();
		if (g_bfmeSingleton0)
		{
			bfmeSetRegisteredFlag(g_bfmeSingleton0);
			((BfmeA1029BumpView *)g_bfmeSingleton0)->bfmeBump();
		}
	}
	return g_bfmeSingleton0;

try_candidate1:
	_WriteBarrier();
	if (desc->m_tag != g_bfmeCandidate1.m_tag)
	{
		if (bfmeCompareVSC(desc->m_name, g_bfmeCandidate1.m_name) != 0)
			goto try_candidate2;
	}

	if (g_bfmeSingleton1 == 0)
	{
		g_bfmeSingleton1 = new BfmeCandidateSingleton1();
		if (g_bfmeSingleton1)
		{
			bfmeSetRegisteredFlag(g_bfmeSingleton1);
			((BfmeA1029BumpView *)g_bfmeSingleton1)->bfmeBump();
		}
	}
	return g_bfmeSingleton1;

try_candidate2:
	_WriteBarrier();
	if (desc->m_tag != g_bfmeCandidate2.m_tag)
	{
		if (bfmeCompareVSC(desc->m_name, g_bfmeCandidate2.m_name) != 0)
			goto try_candidate3;
	}

	if (g_bfmeSingleton2 == 0)
	{
		BfmeA1029 *obj = (BfmeA1029 *)Rva00897640(0x24);

		if (obj != 0)
			obj = obj->bfmeGo1029A(0xcb4700);
		else
			obj = 0;

		g_bfmeSingleton2 = obj;
	}
	return g_bfmeSingleton2;

try_candidate3:
	_WriteBarrier();
	if (desc->m_tag != g_bfmeCandidate3.m_tag)
	{
		if (bfmeCompareVSC(desc->m_name, g_bfmeCandidate3.m_name) != 0)
			return 0;
	}

	if (g_bfmeSingleton3 == 0)
	{
		BfmeA1029 *obj = (BfmeA1029 *)Rva00897640(0x24);

		if (obj != 0)
			obj = obj->bfmeGo1029A(0xcb4480);
		else
			obj = 0;

		g_bfmeSingleton3 = obj;
	}
	return g_bfmeSingleton3;
}
