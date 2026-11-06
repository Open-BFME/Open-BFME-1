// Recovered asset-manager bodies grouped by reciprocal WorldBuilder placement.
// Retail RVA 0x009F0D40, 265 bytes; identity is address-derived.
// The matched Rva009EBB20 forwarder in Q1GlobalGuardedForwarders.cpp proves
// this receiver and one-argument ABI. No original game class name is claimed.
// The copied set is 12 bytes (header/count/comparator); the local wrapper's
// zero and true fields are at +0xC/+0x10. Locks are at receiver +0x60/+0x2C.
// The hash map at +0x44 uses integer keys and pointer payloads; retail updates
// payload +4, not the key. Its const_iterator retains both node and table.
// The copy constructor is 0x009EE8E0; the tree destructor is called through
// ILT 0x00015D7A -> 0x00140950. Existing Gen_t names describe those ABI types.

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <hash_map>

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};

bool operator<(const Gen_t_009ee8e0_k4 &, const Gen_t_009ee8e0_k4 &);
typedef _STL::set<Gen_t_009ee8e0_k4> Q1ReceiverSet;

void j_00015d7a();

// ABI view of the canonical 12-byte STL set. The externally compiled copy
// constructor is 0x009EE8E0. Destruction uses the already-named ILT thunk;
// no new template identity is asserted for its generated destination row.
struct Q1ReceiverTreeStorage
{
	Q1ReceiverTreeStorage(const Q1ReceiverSet &source);
	~Q1ReceiverTreeStorage()
	{
		// MSVC x86 single-inheritance member-pointer ABI: ECX is this and
		// the verified thunk has no stack arguments. No numeric code address.
		typedef void (Q1ReceiverSet::*TreeDestructor)();
		union { void (*raw)(); TreeDestructor member; } destroy;
		destroy.raw = j_00015d7a;
		(get().*destroy.member)();
	}
	Q1ReceiverSet &get() { return *(Q1ReceiverSet *)m_storage; }
	int m_storage[sizeof(Q1ReceiverSet) / sizeof(int)];
};

typedef char Q1ReceiverSetSizeCheck[sizeof(Q1ReceiverSet) == 12 ? 1 : -1];

struct Q1ReceiverLocalSet
{
	Q1ReceiverTreeStorage m_set;
	int m_zero;
	bool m_one;
};

struct Q1ReceiverSetNode : public _STL::_Rb_tree_node_base
{
	int m_key;
};

// The dependency closure (0x009EFD40) views the same 12-byte trees as sets of
// the asset pointers the matched insert_unique (ILT 0x00030413) is pinned on.
struct Rva001408C0Target;
typedef Rva001408C0Target *Q1ReceiverKey;
typedef _STL::set<Q1ReceiverKey> Q1ReceiverPtrSet;

struct Q1ReceiverHashPayload
{
	int m_unused;
	int m_flags;
	Q1ReceiverKey m_key;			// +0x08
	Q1ReceiverKey *m_dependencies;	// +0x0C, null-terminated
};

typedef _STL::hash_map<int, Q1ReceiverHashPayload *> Q1ReceiverHashTable;

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
volatile bool g_q1Flag0134FAA8 = false;

class Q1ReceiverLockGuard
{
public:
	explicit Q1ReceiverLockGuard(int lock) : m_lock(lock)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_lock);
	}
	~Q1ReceiverLockGuard()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_lock);
	}

	int m_lock;
};

class Q1Receiver0134FAAC
{
public:
	void m009EC960(void *value);
	void m009EC970(int which);
	void m009EC9A0(int which);
	void m009ECA30(int value);
	void m009F0D40(int value);
	void m009EFD40(Q1ReceiverLocalSet *set);

private:
	unsigned char m_unmodelled_000[0x24];
	int m_value;
	unsigned char m_unmodelled_028[4];
	unsigned char m_lock_02C[0x18];
	Q1ReceiverHashTable m_table;
	// Retail lock is at +0x60; the STL hash map at +0x44 occupies 20 bytes.
	unsigned char m_unmodelled_058[8];
	unsigned char m_lock_060[0x18];
	unsigned char m_unmodelled_078[0x174];
	bool m_flag0;
	bool m_flag1;
	bool m_flag2;
};

// 0x009EC960: the receiver accepts one argument and returns without work.
void Q1Receiver0134FAAC::m009EC960(void *)
{
}

void Q1Receiver0134FAAC::m009EC970(int which)
{
	switch (which)
	{
		case 0:
			m_flag0 = true;
			break;
		case 1:
			m_flag1 = true;
			break;
		case 2:
			m_flag2 = true;
			break;
	}
}

void Q1Receiver0134FAAC::m009EC9A0(int which)
{
	switch (which)
	{
		case 0:
			g_q1Flag0134FAA8 = false;
			if (g_q1Flag0134FAA8)
			{
				m_flag0 = false;
				break;
			}
			m_flag0 = false;
		spin:
			Sleep(1);
			if (!g_q1Flag0134FAA8)
				goto spin;
			break;
		case 1:
			m_flag1 = false;
			break;
		case 2:
			m_flag2 = false;
			break;
	}
}

void Q1Receiver0134FAAC::m009ECA30(int value)
{
	m_value = value;
	if (value < 1)
		m_value = 1;
}

// Retail 0x009EFD40, 513 bytes (ret 4 at +0x1FE, int3 after; the 504-byte
// generated row stopped short): grows the caller's key set to its dependency
// closure. Each pass copies the frontier (0x009EE8E0), clears the frontier,
// and for every non-null key of the copy looks its payload up in the +0x44
// table and adds every listed dependency not yet in the caller's set to both
// sets. The matched m009F0D40 below and m009F0E50 call it with a local
// wrapper. Shape ported from BFME 2 (Open-BFME-2 dbde7dbe,
// Code/Libraries/Source/assetmanager/assetmanager_impl.cpp, retail 0x006217F0
// there, also 513 bytes).
void Q1Receiver0134FAAC::m009EFD40(Q1ReceiverLocalSet *source)
{
	Q1ReceiverLocalSet frontier = { source->m_set.get(), 0, true };
	Q1ReceiverPtrSet &sourceKeys = (Q1ReceiverPtrSet &)source->m_set.get();
	Q1ReceiverPtrSet &frontierKeys = (Q1ReceiverPtrSet &)frontier.m_set.get();
	while (!frontierKeys.empty())
	{
		Q1ReceiverLocalSet previous = { frontier.m_set.get(), 0, true };
		frontierKeys.clear();
		frontier.m_one = true;
		Q1ReceiverPtrSet &previousKeys = (Q1ReceiverPtrSet &)previous.m_set.get();
		for (Q1ReceiverPtrSet::const_iterator it = previousKeys.begin();
			it != previousKeys.end(); ++it)
		{
			Q1ReceiverSetNode *node = (Q1ReceiverSetNode *)it._M_node;
			if (!node->m_key)
				continue;
			Q1ReceiverHashTable::const_iterator found = m_table.find(node->m_key);
			if (found == m_table.end())
				continue;
			Q1ReceiverHashPayload *asset = found->second;
			if (!asset->m_dependencies)
				continue;
			for (int n = 0; asset->m_dependencies[n]; ++n)
			{
				Q1ReceiverKey dependency = asset->m_dependencies[n];
				if (sourceKeys.find(dependency) == sourceKeys.end())
				{
					frontierKeys.insert(dependency);
					sourceKeys.insert(dependency);
				}
			}
		}
	}
}

void Q1Receiver0134FAAC::m009F0D40(int value)
{
	Q1ReceiverLocalSet set = { *(Q1ReceiverSet *)value, 0, true };
	m009EFD40(&set);

	Q1ReceiverLockGuard lock60((int)m_lock_060);
	Q1ReceiverLockGuard lock2c((int)m_lock_02C);

	Q1ReceiverSet::iterator current = set.m_set.get().begin();
	while (current != set.m_set.get().end())
	{
		Q1ReceiverHashTable *table = &m_table;
		Q1ReceiverSetNode *node =
			(Q1ReceiverSetNode *)current._M_node;
		Q1ReceiverHashTable::const_iterator found = table->find(node->m_key);
		if (found != table->end())
			found->second->m_flags |= 0x04000000;

		++current;
	}
}

class AssetManagerImpl
{
public:
	unsigned char IsEnabled(int which) const;

private:
	unsigned char m_bfmeHead[0x1ec];
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
	unsigned char m_bfmeThird;
};

unsigned char AssetManagerImpl::IsEnabled(int which) const
{
	switch (which)
	{
		case 0:
			return m_bfmeFirst;
		case 1:
			return m_bfmeSecond;
		case 2:
			return m_bfmeThird;
	}
	return 0;
}
