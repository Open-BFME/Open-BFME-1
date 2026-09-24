// ?m009F0E50@Q1Receiver0134FAAC@@QAEXH@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail RVA 0x009F0E50, 327 bytes; identity is address-derived.
// Reached through the guarded forwarder at 0x009EBB00 (load global
// 0x0134FAAC, test, push the one stack argument, call) and called directly by
// the registry destructor at 0x009F23C0 with the +0x1B8 set group, so this is
// a one-argument method of the Q1Receiver0134FAAC object built by
// ??0Gen_dtor_009eb9e0 (W3DRenderObjectSnapshotCtor.cpp).
// Sibling of m009F0D40 (assetmanager_impl.cpp): copy the argument set with
// 0x009EE8E0, hand the local group to 0x009EFD40, then under the +0x60 and
// +0x2C locks walk the +0x44 hash map (begin at 0x009EE0F0) and store, per
// payload, whether its key is in the copied set. The copy is destroyed through
// ILT 0x00015D7A -> 0x00140950, the pointer-set destructor.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <hash_map>

struct Rva001408C0Target;
typedef Rva001408C0Target *Q1ReceiverKey;
typedef _STL::set<Q1ReceiverKey> Q1ReceiverKeySet;

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

struct Q1ReceiverTreeStorage
{
	Q1ReceiverTreeStorage(const Q1ReceiverSet &source);
	~Q1ReceiverTreeStorage()
	{
		get().~Q1ReceiverKeySet();
	}
	Q1ReceiverKeySet &get() { return *(Q1ReceiverKeySet *)m_storage; }
	int m_storage[sizeof(Q1ReceiverKeySet) / sizeof(int)];
};

struct Q1ReceiverLocalSet
{
	Q1ReceiverTreeStorage m_set;
	int m_zero;
	bool m_one;
};

// Hash payload: bit 26 of the dword at +4 records whether the key at +8 is
// in the argument set (0x009F0D40 sets the same bit with an OR).
struct Q1ReceiverHashPayload
{
	int m_unmodelled_000;
	unsigned int m_bits00 : 26;
	unsigned int m_inSet : 1;
	unsigned int m_bits27 : 5;
	Q1ReceiverKey m_key;
};

struct Gen_t_009f14c0_p12cd
{
	Q1ReceiverHashPayload *m_payload;
	int m_unmodelled[2];
};

typedef _STL::hash_map<int, Gen_t_009f14c0_p12cd> Q1ReceiverHashTable;

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

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
	void m009F0E50(int value);
	void m009EFD40(Q1ReceiverLocalSet *set);

private:
	unsigned char m_unmodelled_000[0x2C];
	unsigned char m_lock_02C[0x18];
	Q1ReceiverHashTable m_table;
	unsigned char m_unmodelled_058[8];
	unsigned char m_lock_060[0x18];
};

void Q1Receiver0134FAAC::m009F0E50(int value)
{
	Q1ReceiverLocalSet set = { *(Q1ReceiverSet *)value, 0, true };
	m009EFD40(&set);

	Q1ReceiverLockGuard lock60((int)m_lock_060);
	Q1ReceiverLockGuard lock2c((int)m_lock_02C);

	for (Q1ReceiverHashTable::iterator it = m_table.begin();
		it != m_table.end(); ++it)
	{
		Q1ReceiverHashPayload *payload = it->second.m_payload;
		Q1ReceiverKey key = payload->m_key;
		payload->m_inSet = set.m_set.get().count(key);
	}
}
