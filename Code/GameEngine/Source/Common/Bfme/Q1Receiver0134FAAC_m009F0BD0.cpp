// ?m009F0BD0@Q1Receiver0134FAAC@@QAEXH@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail RVA 0x009F0BD0, 238 bytes; identity is address-derived.
// The matched guarded forwarder Rva009EBAC0 (Q1GlobalGuardedForwarders.cpp)
// reaches this method on the object held in global 0x0134FAAC, whose
// constructor is ??0Gen_dtor_009eb9e0 (Rva009EB960Ctor.cpp):
// lock at +0x60, first pointer-set group at +0x190 (set/count/active).
// Under the lock, every non-null key of the argument set that is missing
// from the +0x190 set is inserted (insert_unique via ILT 0x00030413);
// when anything was inserted the receiver's refresh at 0x009EFF50 runs.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva001408C0Target;
typedef Rva001408C0Target *Q1ReceiverKey;
typedef _STL::set<Q1ReceiverKey> Q1ReceiverKeySet;

struct Q1ReceiverSetGroup
{
	Q1ReceiverKeySet m_tree;
	volatile unsigned int m_count;
	volatile bool m_active;
};

struct CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class CriticalSectionLock009F0BD0
{
public:
	explicit CriticalSectionLock009F0BD0(int state) : m_state(state)
	{
		EnterCriticalSection((CRITICAL_SECTION *)m_state);
	}
	~CriticalSectionLock009F0BD0()
	{
		LeaveCriticalSection((CRITICAL_SECTION *)m_state);
	}

	int m_state;
};

class Q1Receiver0134FAAC
{
public:
	void m009F0BD0(int value);
	void refresh(void);

private:
	unsigned char m_unmodelled_000[0x60];
	unsigned char m_lock_060[0x18];
	unsigned char m_unmodelled_078[0x118];
	Q1ReceiverSetGroup m_set190;
};

void Q1Receiver0134FAAC::m009F0BD0(int value)
{
	CriticalSectionLock009F0BD0 lock((int)m_lock_060);
	bool changed = false;
	const Q1ReceiverKeySet &source = *(const Q1ReceiverKeySet *)value;

	for (Q1ReceiverKeySet::const_iterator it = source.begin();
		it != source.end(); ++it)
	{
		Q1ReceiverKey key = *it;
		if (m_set190.m_tree.count(key) == 0 && key != 0)
		{
			if (!changed)
				changed = true;
			m_set190.m_tree.insert(*it);
		}
	}

	if (!changed)
		return;
	this->refresh();
}
