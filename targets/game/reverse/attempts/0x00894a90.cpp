// ?d_00894a90@@YAXXZ
// partial score=0.9098 date=2026-10-01
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHsc

struct Gen_t_00894a10_k4 { int a[1]; };
struct Gen_t_00894a10_p12cd { int a[3]; };
namespace _STL {
template<class A, class B> struct pair;
template<> struct pair<const Gen_t_00894a10_k4, Gen_t_00894a10_p12cd> { ~pair(); };
}
typedef _STL::pair<const Gen_t_00894a10_k4, Gen_t_00894a10_p12cd> Rva00894A10Pair;

class Rva008A1460Owner { public: void cleanup(); };
class Rva00896060Owner { public: ~Rva00896060Owner(); };
class Rva008A2CF0Owner { public: ~Rva008A2CF0Owner(); };
class Rva008A30A0Object { public: void clear(); };
class Rva008C6220ScoreBuffers { public: void clear(); };
class Rva00893030Manager;
struct Rva00899560Pool;
class Rva00894110Call { public: void dispatch(); };
class Rva008A30C0Call { public: void dispatch(); };

struct BfmeStringData3AF0 { unsigned short m_refCount; char padding[22]; };
struct BfmeStringPool3AF0 {
	void *m_unused;
	void (__cdecl *free)(BfmeStringData3AF0 *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern char *Rva008A5380Holder;
extern Rva00893030Manager *g_rva00893030Manager;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void (*TheBfmeFree)(void *, unsigned int);

extern void bfmeGoDWG();
extern void d_00893820();
extern void j_00894110();
extern void d_00897360();
extern void d_00899af0();
extern void d_008acac0();
extern void d_008a30c0();
extern void rva008B8B80ReleaseAll();
extern void rva008B61D0ReleaseGlobals();
extern void rva008A4630ReleaseGlobals();
extern void rva008A47B0ReleaseGlobals();
extern void bfmeGo1062B();
extern void rva008A48D0ReleaseGlobals();
extern void bfmeGo1083A();
extern void bfmeGo1082C();
extern void bfmeGo1082B();
extern void rva008B2BD0ReleaseGlobals();
extern void rva008A98B0ReleaseAll();
extern void Rva008A4AA0Invoke();
extern void Rva00898D60Invoke();
extern void bfmeClearHash3AF0();

typedef void (__cdecl *IntCall)(int);

void dup_00894A90(int mode)
{
	bfmeGoDWG();
	((Rva008A1460Owner *)Rva008A5380Holder)->cleanup();
	((IntCall)d_00893820)(1);

	void *zero;
	zero = 0;
	Rva00894A10Pair *pair = (Rva00894A10Pair *)*(void **)0x013377F8;
	if (pair != zero) {
		pair->~Rva00894A10Pair();
		TheBfmeFree(pair, 0x18);
	}

	Rva00896060Owner *manager = (Rva00896060Owner *)g_rva00893030Manager;
	if (manager != zero) {
		manager->~Rva00896060Owner();
		TheBfmeFree(manager, 4);
	}

	void *tree = *(void **)0x013377F0;
	if (tree != zero) {
		typedef void (Rva00894110Call::*Call)(void);
		union { void (*freeFunction)(void); Call memberFunction; } callTarget;
		callTarget.freeFunction = j_00894110;
		Call call = callTarget.memberFunction;
		(((Rva00894110Call *)tree)->*call)();
		TheBfmeFree(tree, 0x1c);
	}

	((IntCall)d_00899af0)(mode);
	rva008B8B80ReleaseAll();
	rva008B61D0ReleaseGlobals();
	rva008A4630ReleaseGlobals();
	rva008A47B0ReleaseGlobals();
	bfmeGo1062B();
	rva008A48D0ReleaseGlobals();
	bfmeGo1083A();
	bfmeGo1082C();
	bfmeGo1082B();
	rva008B2BD0ReleaseGlobals();
	d_008acac0();
	rva008A98B0ReleaseAll();
	Rva008A4AA0Invoke();
	((IntCall)d_00897360)(1);
	Rva00898D60Invoke();

	typedef void (Rva008A30C0Call::*IdleCall)(void);
	union { void (*freeFunction)(void); IdleCall memberFunction; } idleTarget;
	idleTarget.freeFunction = d_008a30c0;
	IdleCall idleCall = idleTarget.memberFunction;
	(((Rva008A30C0Call *)g_rva8CD130IdleHook)->*idleCall)();

	Rva008A2CF0Owner *holder = (Rva008A2CF0Owner *)Rva008A5380Holder;
	if (holder != zero) {
		holder->~Rva008A2CF0Owner();
		TheBfmeFree(holder, 0x12b4);
	}
	Rva008A5380Holder = 0;

	Rva008A30A0Object *idle = (Rva008A30A0Object *)g_rva8CD130IdleHook;
	if (idle != zero) {
		idle->clear();
		TheBfmeFree(idle, 0xc);
	}

	BfmeStringData3AF0 *data = *(BfmeStringData3AF0 **)0x012D5140;
	*(void **)0x01337814 = zero;
	--data->m_refCount;
	if (data->m_refCount == 0) {
		g_bfmeStringPool1284->free(data);
		++g_bfmeDefaultString1284.m_refCount;
		*(BfmeStringData3AF0 **)0x012D5140 = &g_bfmeDefaultString1284;
		bfmeClearHash3AF0();
	}

	(((Rva008A30C0Call *)g_rva8CD130IdleHook)->*idleCall)();
	Rva008A30A0Object *idleAgain = (Rva008A30A0Object *)g_rva8CD130IdleHook;
	if (idleAgain != zero) {
		idleAgain->clear();
		TheBfmeFree(idleAgain, 0xc);
	}

	g_rva8CD130IdleHook = 0;
	g_bfmeStringPool1284 = 0;
	((Rva008C6220ScoreBuffers *)0x01338748)->clear();
	*(int *)0x01337800 = 0;
}
