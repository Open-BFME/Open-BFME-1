// ??0W3DRenderObjectSnapshot@@QAE@XZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_STATIC_LIB 1

#include <deque>
#include <hash_map>
#include <new>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <string.h>
#include <windows.h>

extern "C" __declspec(dllimport) unsigned long __cdecl _beginthread(void (__cdecl *start_address)(void *), unsigned stack_size, void *arglist);

#pragma intrinsic(memset)

class BfmeBase1134
{
public:
	BfmeBase1134();
	virtual ~BfmeBase1134();

private:
	int m_value;
};

struct Gen_t_009f1470_p12cd
{
	int a[3];
	Gen_t_009f1470_p12cd();
	Gen_t_009f1470_p12cd(const Gen_t_009f1470_p12cd &);
	~Gen_t_009f1470_p12cd();
	Gen_t_009f1470_p12cd &operator=(const Gen_t_009f1470_p12cd &);
};

struct Gen_t_009f14c0_p12cd
{
	int a[3];
	Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd(const Gen_t_009f14c0_p12cd &);
	~Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd &operator=(const Gen_t_009f14c0_p12cd &);
};

struct Gen_t_009edfe0_p12cd
{
	int a[3];
	Gen_t_009edfe0_p12cd();
	Gen_t_009edfe0_p12cd(const Gen_t_009edfe0_p12cd &);
	~Gen_t_009edfe0_p12cd();
	Gen_t_009edfe0_p12cd &operator=(const Gen_t_009edfe0_p12cd &);
};

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;

struct Rva009F2140AssetSetGroup
{
	Rva001408C0Set m_tree;
	volatile unsigned int m_count;
	volatile bool m_active;
	unsigned char m_padding[3];

	Rva009F2140AssetSetGroup() { clear(); }

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

class Rva009EEA70CleanupDeleting
{
public:
	Rva009EEA70CleanupDeleting() : m_last(1)
	{
		for (unsigned int i = 0; i < 0xafcf; ++i)
			m_data[i] = 0;
	}

	virtual ~Rva009EEA70CleanupDeleting();

	unsigned int m_data[0xafcf];
	unsigned int m_last;
};

class AssetRegistry;
extern AssetRegistry *g_theAssetRegistry;
extern void __cdecl Rva00DEFBE0ThreadProc(void *);

typedef std::hash_map<int, Gen_t_009f1470_p12cd> GenHashMap1470;
typedef std::hash_map<int, Gen_t_009f14c0_p12cd> GenHashMap14C0;
typedef std::deque<Gen_t_009edfe0_p12cd> GenDeque;

class Gen_dtor_009eb9e0
{
public:
	Gen_dtor_009eb9e0();
	~Gen_dtor_009eb9e0();

private:
	uintptr_t m_thread;
	void *m_unknown04;
	bool m_active;
	unsigned char m_pad09[3];
	GenHashMap1470 m_map0c;
	unsigned int m_field20;
	unsigned int m_field24;
	unsigned int m_field28;
	CRITICAL_SECTION m_lock2c;
	GenHashMap14C0 m_map44;
	GenHashMap14C0::iterator m_iterator58;
	CRITICAL_SECTION m_lock60;
	GenDeque m_deques78[7];
	Rva009F2140AssetSetGroup m_set190;
	Rva009F2140AssetSetGroup m_set1a4;
	Rva009F2140AssetSetGroup m_set1b8;
	Rva009F2140AssetSetGroup m_set1cc;
	unsigned int m_field1e0;
	unsigned int m_field1e4;
	unsigned char m_pad1e8[4];
	bool m_flag1ec;
	bool m_flag1ed;
	bool m_flag1ee;
	unsigned char m_pad1ef;
	Rva009EEA70CleanupDeleting *m_hashContext;
};

typedef char GenDtorSizeCheck[sizeof(Gen_dtor_009eb9e0) == 0x1f4 ? 1 : -1];
typedef char RegistryWorkerSizeCheck[sizeof(Rva009EEA70CleanupDeleting) == 0x2bf44 ? 1 : -1];

class W3DRenderObjectSnapshot : public BfmeBase1134
{
public:
	W3DRenderObjectSnapshot();
	virtual ~W3DRenderObjectSnapshot();

private:
	Gen_dtor_009eb9e0 *m_renderObject;
};

W3DRenderObjectSnapshot::W3DRenderObjectSnapshot()
{
	m_renderObject = new Gen_dtor_009eb9e0;
}

Gen_dtor_009eb9e0::Gen_dtor_009eb9e0()
	: m_active(false),
	  m_map0c(100),
	  m_field20(0),
	  m_field24(0x10000000),
	  m_field28(0),
	  m_map44(100)
{
	m_field1e0 = 0;
	m_field1e4 = 0;
	m_flag1ec = true;
	m_flag1ed = true;
	m_flag1ee = false;

	m_iterator58 = m_map44.begin();

	void *workerMemory = ::operator new(0x2bf44);
	Rva009EEA70CleanupDeleting *worker;
	if (workerMemory != 0)
	{
		worker = new (workerMemory) Rva009EEA70CleanupDeleting;
	}
	else
	{
		worker = 0;
	}
	m_hashContext = worker;

	InitializeCriticalSection(&m_lock2c);
	InitializeCriticalSection(&m_lock60);
	g_theAssetRegistry = (AssetRegistry *)this;
	m_thread = _beginthread(Rva00DEFBE0ThreadProc, 0, this);
	Sleep(1);
}
