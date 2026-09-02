// ?m009F0BD0@Q1Receiver0134FAAC@@QAEXH@Z
// partial score=0.76 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: Q1Receiver0134FAAC::m009F0BD0, retail 0x009F0BD0, 238 bytes.
//
// The body merges the pointer set supplied through the guarded forwarder into
// the receiver's set while holding the receiver-owned lock.  The receiver
// helper at 0x009EFF50 is called only when at least one key was inserted.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

struct Rva001408C0Target;
typedef Rva001408C0Target *Q1ReceiverKey;
typedef _STL::set<Q1ReceiverKey, _STL::less<Q1ReceiverKey>,
	_STL::allocator<Q1ReceiverKey> > Q1ReceiverSet;

struct Q1ReceiverLockAndState
{
	unsigned char m_lock[0x1C];
	unsigned char m_unmodelled[0x114];

	void refresh(void);
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	void *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	void *lock);

class Q1Receiver0134FAAC
{
public:
	void m009F0BD0(int value);

	unsigned char m_unmodelled_000[0x60];
	Q1ReceiverLockAndState m_state;
	Q1ReceiverSet m_keys;
};

class Q1ReceiverLockGuard
{
	public:
	explicit Q1ReceiverLockGuard(Q1ReceiverLockAndState *state) :
		m_state(state)
	{
		EnterCriticalSection(m_state);
	}
	~Q1ReceiverLockGuard()
	{
		LeaveCriticalSection(m_state);
	}

	Q1ReceiverLockAndState *m_state;
};

void Q1Receiver0134FAAC::m009F0BD0(int value)
{
	Q1ReceiverLockAndState *state = &m_state;
	Q1ReceiverLockGuard lock(state);
	bool changed = false;
	const Q1ReceiverSet *source = (const Q1ReceiverSet *)value;
	for (Q1ReceiverSet::const_iterator it = source->begin();
		it != source->end(); ++it)
	{
		Q1ReceiverKey key = *it;
		if (m_keys.find(key) == m_keys.end())
		{
			m_keys.insert(key);
			changed = true;
		}
	}

	if (changed)
		state->refresh();
}
