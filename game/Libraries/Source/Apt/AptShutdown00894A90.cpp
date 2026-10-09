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
extern void rva00897360(bool);
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

class Gen_uw_00893e70;
extern Gen_uw_00893e70 *g_rva013377F0;
class BfmeTracker4310;
extern BfmeTracker4310 *g_bfmeTracker4310;
struct Registry008C3F10;
extern Registry008C3F10 *g_registry01337814;
class BfmeStrVKI { public: BfmeStringData3AF0 *m_data; };
extern BfmeStrVKI g_String012D5140;
extern int g_bfme1017H;
extern int g_stack01338748;
typedef void (__cdecl *IntCall)(int);

class Rva00894A60SizedDeleting { public: virtual ~Rva00894A60SizedDeleting(); };
class Rva00894350SizedDeleting { public: virtual ~Rva00894350SizedDeleting(); };
#define POOL_DELETE static void operator delete(void *p, unsigned n) { TheBfmeFree(p, n); }
class Rva00894A10Delete { public: ~Rva00894A10Delete() { ((Rva00894A60SizedDeleting *)this)->Rva00894A60SizedDeleting::~Rva00894A60SizedDeleting(); } POOL_DELETE char pad[0x18]; };
class Rva00896060Delete { public: ~Rva00896060Delete() { ((Rva00896060Owner *)this)->~Rva00896060Owner(); } POOL_DELETE char pad[4]; };
class Rva00894110Delete { public: ~Rva00894110Delete() { ((Rva00894350SizedDeleting *)this)->Rva00894350SizedDeleting::~Rva00894350SizedDeleting(); } POOL_DELETE char pad[0x1c]; };
class Rva008A2CF0Delete { public: ~Rva008A2CF0Delete() { ((Rva008A2CF0Owner *)this)->~Rva008A2CF0Owner(); } POOL_DELETE char pad[0x12b4]; };
class Rva008A30A0Delete { public: ~Rva008A30A0Delete() { ((Rva008A30A0Object *)this)->clear(); } POOL_DELETE char pad[0xc]; };


// ?dup_00894A90@@YAXH@Z
// Open BFME 2: Code/Libraries/Source/Apt/AptShutdownRva006CFAB0.cpp.
void dup_00894A90(int mode)
{
	bfmeGoDWG();
	((Rva008A1460Owner *)Rva008A5380Holder)->cleanup();
	((IntCall)d_00893820)(1);

	void *zero = 0;
	delete (Rva00894A10Delete *)g_bfmeTracker4310;
	delete (Rva00896060Delete *)g_rva00893030Manager;
	delete (Rva00894110Delete *)g_rva013377F0;

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
	rva00897360(true);
	Rva00898D60Invoke();

	typedef void (Rva008A30C0Call::*IdleCall)(void);
	union { void (*freeFunction)(void); IdleCall memberFunction; } idleTarget;
	idleTarget.freeFunction = d_008a30c0;
	IdleCall idleCall = idleTarget.memberFunction;
	(((Rva008A30C0Call *)g_rva8CD130IdleHook)->*idleCall)();

	delete (Rva008A2CF0Delete *)Rva008A5380Holder;
	Rva008A5380Holder = 0;
	delete (Rva008A30A0Delete *)g_registry01337814;

	BfmeStringData3AF0 *data = g_String012D5140.m_data;
	g_registry01337814 = 0;
	--data->m_refCount;
	if (data->m_refCount == 0) {
		g_bfmeStringPool1284->free(data);
	}
	++g_bfmeDefaultString1284.m_refCount;
	g_String012D5140.m_data = &g_bfmeDefaultString1284;
	bfmeClearHash3AF0();

	(((Rva008A30C0Call *)g_rva8CD130IdleHook)->*idleCall)();
	delete (Rva008A30A0Delete *)g_rva8CD130IdleHook;

	g_rva8CD130IdleHook = 0;
	g_bfmeStringPool1284 = 0;
	((Rva008C6220ScoreBuffers *)&g_stack01338748)->clear();
	g_bfme1017H = 0;
}

