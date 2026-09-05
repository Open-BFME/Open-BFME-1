// ?bfmeGetOrCreateCandidate@@YGPAXPAXPBUBfmeCandidateDX@@@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x008B4DA0 (674 bytes), a __stdcall(unused, BfmeCandidate*) lookup.
// Four near-identical blocks test the incoming descriptor against four fixed
// candidates (pointer-identity short-circuit, else ?bfmeCompareVSC@@YAHPBD0@Z
// on the name past the tag) and lazily build/cache a singleton for whichever
// candidate matches, in the same {capacity-checked registry, saturating
// bitfield} family already recovered for vtable 0x01135D68 (Rva899F00Base,
// see ThreadClassCtorThunk.cpp and Bfme5SaturatingRelease.cpp's partial).
//
// Candidates 0/1 build a derived object over Rva899F00Base(9,8) by hand --
// alloc the raw size, skip the 8-byte WideHeaderedAlloc-style header, link it
// (0x00897300), then placement-construct only if the pointer is non-null --
// exactly Rva00897640's own body (WideHeaderedAlloc.cpp) inlined rather than
// called, so no operator-new exception machinery applies. Each then sets its
// own vtable and one extra field (a compiled-in constant, not a parameter)
// and -- ONLY on first construction -- clears bits 7-13 of the shared
// packed-bits field, sets bit 6, and bumps the saturating counter via the
// object's own vtable slot 0 (Gen_008991B0::bfmeBump / the partial at
// 0x008991E0).
//
// Candidates 2/3 instead go through the already-landed helpers verbatim:
// Rva00897640(0x24) (WideHeaderedAlloc.cpp) then
// BfmeA1029::bfmeGo1029A(constant) (BfmeConv1029.cpp), which install a FIXED
// shared vtable and store the constant as m_bfmeVal -- no extra vtable write,
// no bump call.
//
// Identity is not recovered for the descriptor type, the four candidate
// globals, the four cached-singleton globals or the two derived classes;
// all are address-derived. The SEH/state-variable frame retail carries is
// not reproduced explicitly -- it is standard /EHsc scaffolding this
// compiler may or may not emit for the same source shape, tracked as a
// known risk to the byte match rather than modelled by hand.

inline void *operator new( unsigned int, void *place ) { return place; }

extern "C" void * (*WideAllocPtr)(unsigned int bytes);
void Gen00897300(void *block);
int __cdecl bfmeCompareVSC(const char *a, const char *b);
void *__cdecl Rva00897640(unsigned int bytes);

// Local ABI-slice replica of the vtable-0x01135D68 base, same family as
// ThreadClassCtorThunk.cpp / Rva8CB6D0CallbackCtor.cpp, but this TU calls
// vtable slot 0 (bfmeBump) so it is declared here as the class's only
// virtual, matching Bfme5SaturatingRelease.cpp's field layout: the packed
// bits dword sits at this+4, right after the vptr.
class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual void bfmeBump();

private:
	unsigned int	m_bfmeBits;			// +0x04
	char			_bfme_base_slice[0x18];	// +0x08..+0x1F
};

class BfmeCandidateSingleton0 : public Rva899F00Base
{
public:
	void *operator new(unsigned int n)
	{
		char *block = (char *)WideAllocPtr(n + 8) + 8;
		Gen00897300(block);
		return block;
	}
	void operator delete(void *p) { }

	BfmeCandidateSingleton0();

private:
	int	m_bfmeTag;	// +0x20
};

BfmeCandidateSingleton0::BfmeCandidateSingleton0() :
	Rva899F00Base(reinterpret_cast<const char *>(9), 8)
{
	m_bfmeTag = 0xcb4370;
}

class BfmeCandidateSingleton1 : public Rva899F00Base
{
public:
	void *operator new(unsigned int n)
	{
		char *block = (char *)WideAllocPtr(n + 8) + 8;
		Gen00897300(block);
		return block;
	}
	void operator delete(void *p) { }

	BfmeCandidateSingleton1();

private:
	int	m_bfmeTag;	// +0x20
};

BfmeCandidateSingleton1::BfmeCandidateSingleton1() :
	Rva899F00Base(reinterpret_cast<const char *>(9), 8)
{
	m_bfmeTag = 0xcb4420;
}

// upstream layout: reference/CnC_Generals_Zero_Hour has no match; see
// BfmeConv1029.cpp, which already lands this class and its ctor.
class BfmeA1029
{
public:
	BfmeA1029 *bfmeGo1029A(int a);

	void	*m_bfmeVfptr;
	char	m_bfmePad[0x1c];
	int		m_bfmeVal;
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

extern Rva899F00Base *g_bfmeSingleton0;	// retail 0x01338388
extern Rva899F00Base *g_bfmeSingleton1;	// retail 0x0133838C
extern BfmeA1029 *g_bfmeSingleton2;		// retail 0x01338390
extern BfmeA1029 *g_bfmeSingleton3;		// retail 0x01338394

static void bfmeSetRegisteredFlag(Rva899F00Base *obj)
{
	unsigned int *bits = (unsigned int *)((char *)obj + 4);
	*bits = (*bits & 0xffffc07f) | 0x40;
}

// ?d_008b4da0@@YAXXZ
void *__stdcall bfmeGetOrCreateCandidate(void *unused, const BfmeCandidateDX *desc)
{
	if (desc->m_tag == g_bfmeCandidate0.m_tag || bfmeCompareVSC(desc->m_name, g_bfmeCandidate0.m_name) == 0)
	{
		if (g_bfmeSingleton0 == 0)
		{
			g_bfmeSingleton0 = new BfmeCandidateSingleton0();
			bfmeSetRegisteredFlag(g_bfmeSingleton0);
			g_bfmeSingleton0->bfmeBump();
		}

		return g_bfmeSingleton0;
	}

	if (desc->m_tag == g_bfmeCandidate1.m_tag || bfmeCompareVSC(desc->m_name, g_bfmeCandidate1.m_name) == 0)
	{
		if (g_bfmeSingleton1 == 0)
		{
			g_bfmeSingleton1 = new BfmeCandidateSingleton1();
			bfmeSetRegisteredFlag(g_bfmeSingleton1);
			g_bfmeSingleton1->bfmeBump();
		}

		return g_bfmeSingleton1;
	}

	if (desc->m_tag == g_bfmeCandidate2.m_tag || bfmeCompareVSC(desc->m_name, g_bfmeCandidate2.m_name) == 0)
	{
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
	}

	if (desc->m_tag == g_bfmeCandidate3.m_tag || bfmeCompareVSC(desc->m_name, g_bfmeCandidate3.m_name) == 0)
	{
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

	return 0;
}
