// cl: /DNDEBUG /MD /EHsc /Iinputs/vendor/stlport /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

#define _STLP_NO_EXCEPTIONS 1
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <vector>
#include <windows.h>

extern char g_bfme911Flag;
extern int g_bfme911Val;
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
public:
	static bool Has_Stencil();
};

void bfmeGo911A(void)
{
	if (g_bfme911Flag) {
		if (DX8Wrapper::Has_Stencil())
			g_bfme911Val = 0x100;
		g_bfme911Flag = 0;
	}
}

class RayCollisionTestClass;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/aabtree.h
class AABTreeClass
{
public:
	struct CullNodeStruct;
	char m_bfmePad[0xc];
	CullNodeStruct *Nodes;
private:
	bool Cast_Ray_Recursive(CullNodeStruct *n, RayCollisionTestClass &r);
	friend class BfmeThing911B;
};

class BfmeThing911B
{
public:
	void bfmeGo911B(void *a);
	void bfmeElse911B(void *a);
	char m_bfmePad[0x90];
	AABTreeClass *m_bfmeSub;
};

void BfmeThing911B::bfmeGo911B(void *a)
{
	AABTreeClass *s = m_bfmeSub;
	if (s) {
		s->Cast_Ray_Recursive(s->Nodes, *(RayCollisionTestClass *)a);
		return;
	}
	bfmeElse911B(a);
}

class BfmeObj911C
{
public:
	virtual void bfmeRelease911C();
	int m_bfmeRef;
};

extern BfmeObj911C *g_bfme911Ptr;
extern char g_bfme911Busy;

void bfmeGo911C(void)
{
	BfmeObj911C *p = g_bfme911Ptr;
	if (p) {
		if (--p->m_bfmeRef == 0)
			p->bfmeRelease911C();
		g_bfme911Ptr = 0;
	}
	g_bfme911Busy = 0;
}

class BfmeA911D
{
public:
	virtual void bfmeSlot911D0();
	virtual void bfmeSlot911D1();
	virtual void bfmeStop911D();
};

class BfmeB911D
{
public:
	virtual void bfmeSlot911E0();
	virtual void bfmeFree911D();
};

class BfmeThing911D
{
public:
	void bfmeGo911D();
	char m_bfmePad[0x4c];
	BfmeB911D *m_bfmeB;
	BfmeA911D *m_bfmeA;
};

void BfmeThing911D::bfmeGo911D()
{
	BfmeA911D *a = m_bfmeA;
	if (a)
		a->bfmeStop911D();
	BfmeB911D *b = m_bfmeB;
	if (b)
		b->bfmeFree911D();
	m_bfmeB = 0;
}

class BfmeSub911E
{
public:
	virtual void bfmeSlot911F0();
	virtual void bfmeDrop911E(int f);
	void bfmePrep911E();
	void *m_rva00000004;
	void *m_rva00000008;
};

struct BfmeLockTEA
{
	char m_pad[0x18];
	bool m_armed;
};

class Rva00886F60Class
{
public:
	Rva00886F60Class(BfmeLockTEA *lock) : m_lock(lock)
	{
		if (lock && lock->m_armed)
			EnterCriticalSection(reinterpret_cast<CRITICAL_SECTION *>(lock));
	}
	virtual ~Rva00886F60Class()
	{
		if (m_lock && m_lock->m_armed)
			LeaveCriticalSection(reinterpret_cast<CRITICAL_SECTION *>(m_lock));
	}

private:
	BfmeLockTEA *m_lock;
};

class Rva0090F050Resource
{
public:
	virtual ~Rva0090F050Resource();
	virtual void unusedVirtual();
	virtual void __stdcall releaseResources();
};

struct Gen_t_0090ef40_m4pod
{
	int a[1];
};
namespace _STL
{
template <> struct __type_traits<Gen_t_0090ef40_m4pod> : __type_traits_aux<1> {};
}

class Gen_00C71060Target
{
public:
	void bfmeForward(void);
};

class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
extern char g_012D6DE0;
extern Gen_00C71060Target TheBfmeObject_00C71060;

void BfmeSub911E::bfmePrep911E()
{
	if (m_rva00000008)
	{
		if (Rva0134FAA0)
		{
			Rva00886F60Class guard(reinterpret_cast<BfmeLockTEA *>(&g_012D6DE0));
			std::vector<Gen_t_0090ef40_m4pod> &updates = *reinterpret_cast<std::vector<Gen_t_0090ef40_m4pod> *>(&TheBfmeObject_00C71060);
			updates.push_back(*reinterpret_cast<Gen_t_0090ef40_m4pod *>(&m_rva00000008));
		}
		else
		{
			static_cast<Rva0090F050Resource *>(m_rva00000008)->releaseResources();
		}
		m_rva00000008 = 0;
	}
}

class BfmeThing911E
{
public:
	void bfmeGo911E();
	char m_bfmePad[0x14];
	BfmeSub911E *m_bfmeSub;
};

void BfmeThing911E::bfmeGo911E()
{
	m_bfmeSub->bfmePrep911E();
	BfmeSub911E *s = m_bfmeSub;
	if (s)
		s->bfmeDrop911E(1);
	m_bfmeSub = 0;
}

class BfmeThingVDW
{
public:
	void bfmeBaseVDW(int a, int b);
};

extern char g_bfme911Vft[];

class BfmeThing911F
{
public:
	BfmeThing911F *bfmeGo911F(int a, void *b);
	char *m_bfmeVft;
	char m_bfmePad[0x1c];
	void *m_bfmeArg;
};

BfmeThing911F *BfmeThing911F::bfmeGo911F(int a, void *b)
{
	((BfmeThingVDW *)this)->bfmeBaseVDW(a, 8);
	m_bfmeVft = g_bfme911Vft;
	m_bfmeArg = b;
	return this;
}
