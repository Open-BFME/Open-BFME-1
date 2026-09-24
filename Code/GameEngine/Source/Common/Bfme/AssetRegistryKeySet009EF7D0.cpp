// ?Collect_Keys_009EF7D0@AssetRegistry@@QAE?AURva009F2140AssetSetGroup@@XZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// A member of the registry g_theAssetRegistry (0x0134FAAC) points at. The
// layout is the one the landed constructor ??0Gen_dtor_009eb9e0@@QAE@XZ
// size-checks: the critical section at +0x2C and the hash_map at +0x44 whose
// begin() is the pinned 0x009EE0F0. The retail caller at 0x009EC050 is the
// global wrapper that default-constructs the same 0x14-byte set group when the
// registry is absent, so the return is that group by value.
//
// Under the registry lock the body walks the +0x44 map with the native
// STLport iterator (the bucket skip is inlined) and inserts every key into a
// local set group, then returns a group copy-constructed from that tree with
// the count and flag re-armed the way the default constructor does. The
// address token stays in the method name: nothing names this body beyond
// what it does.
//
// Two ABI views, no new pins: the local tree is the pointer set whose
// insert_unique (0x00030413) and destructor (0x00015D7A -> 0x00140950) are
// already pinned, and the returned tree is spelled as the 4-byte-key tree
// whose copy constructor the ledger already names at 0x009EE8E0 (the same
// body the neighbouring Rva009EF6D0 copy and m009F0D40 call). Both trees are
// the 12-byte header/count/comparator STLport layout.

#define _STLP_USE_STATIC_LIB 1

#include <hash_map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

struct Gen_t_009f14c0_p12cd
{
	int a[3];
	Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd(const Gen_t_009f14c0_p12cd &);
	~Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd &operator=(const Gen_t_009f14c0_p12cd &);
};

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};

typedef _STL::_Rb_tree<Gen_t_009ee8e0_k4, Gen_t_009ee8e0_k4,
	_STL::_Identity<Gen_t_009ee8e0_k4>, _STL::less<Gen_t_009ee8e0_k4>,
	_STL::allocator<Gen_t_009ee8e0_k4> > KeyTreeCopyView009EE8E0;

struct Rva009F2140AssetSetGroup
{
	KeyTreeCopyView009EE8E0 m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];

	explicit Rva009F2140AssetSetGroup(const KeyTreeCopyView009EE8E0 &tree)
		: m_tree(tree)
	{
		clear();
	}

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

struct LocalKeySet009EF7D0
{
	Rva001408C0Set m_tree;
	unsigned int m_count;
	bool m_active;
	unsigned char m_padding[3];

	LocalKeySet009EF7D0() { clear(); }

	void clear()
	{
		m_count = 0;
		m_active = true;
	}
};

typedef std::hash_map<int, Gen_t_009f14c0_p12cd> GenHashMap14C0;

class CriticalSectionLock
{
public:
	explicit CriticalSectionLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~CriticalSectionLock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

class AssetRegistry
{
public:
	Rva009F2140AssetSetGroup Collect_Keys_009EF7D0();

private:
	unsigned char m_unmodelled_000[0x2c];
	CRITICAL_SECTION m_lock2c;
	GenHashMap14C0 m_map44;
};

Rva009F2140AssetSetGroup AssetRegistry::Collect_Keys_009EF7D0()
{
	CriticalSectionLock lock(&m_lock2c);
	LocalKeySet009EF7D0 keys;
	GenHashMap14C0::iterator it;
	for (it = m_map44.begin(); it != m_map44.end(); ++it)
	{
		keys.m_tree.insert(*(const Rva001408C0Key *)&(*it).first);
	}
	return Rva009F2140AssetSetGroup(
		*(const KeyTreeCopyView009EE8E0 *)&keys.m_tree);
}
