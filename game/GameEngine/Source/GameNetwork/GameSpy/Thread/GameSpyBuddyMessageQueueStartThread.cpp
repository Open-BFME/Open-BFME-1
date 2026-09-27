// cl: /DNDEBUG /MD /EHsc
// BFME GameSpyBuddyMessageQueue::startThread at retail 0x0063C650.

class BFMENetworkLock
{
public:
	void *m_handle;
	unsigned int m_refCount;
};

// Lock-ref acquire helper, pinned at 0x009DB3B0 (BFME network lock-ref ctor).
class BFMEAutoLockRef
{
public:
	BFMEAutoLockRef(BFMENetworkLock *lock, unsigned int timeout);
	~BFMEAutoLockRef();

private:
	BFMENetworkLock *m_lock;
	bool m_failed;
	char m_padding[3];
};

class CriticalSectionClass
{
public:
	class LockClass
	{
	public:
		LockClass(CriticalSectionClass &criticalSection);
		~LockClass();

	private:
		char m_body[4];
	};

private:
	char m_body[8];
};

// Layout witnessed by the matched BuddyThreadClass constructor at 0x0063C4F0:
// the five string ctors at +0x60/+0x6C/+0x78/+0x84/+0x90, the network lock
// pointer at +0x9C, the CriticalSectionClass at +0xA0 and the owned-lock
// pointer at +0xA8, so the object is 0xAC bytes -- the size this body's
// operator new asks for.
class BuddyThreadClass
{
public:
	BuddyThreadClass(BFMENetworkLock *lock);
	virtual ~BuddyThreadClass();
	virtual void Execute();
	virtual void Thread_Function();

	// Public only so this TU can name the witnessed +0xA0 critical section.
	char m_base[0x4c];
	bool m_isNewAccount;
	bool m_isConnecting;
	bool m_isConnected;
	char m_padding0;
	int m_profileID;
	int m_lastErrorCode;
	bool m_isDeleting;
	char m_padding1[3];
	char m_strings[0x3c];
	BFMENetworkLock *m_networkLock;
	CriticalSectionClass m_criticalSection;
	void *m_ownedLock;
};

class GameSpyBuddyMessageQueue
{
public:
	virtual void startThread();

private:
	char m_prefix[0x60];
	BuddyThreadClass *m_thread;
	BFMENetworkLock m_lock;
	BFMEAutoLockRef *m_lockRef;
};

void GameSpyBuddyMessageQueue::startThread()
{
	if (m_thread)
		return;

	BFMEAutoLockRef *lock_ref = new BFMEAutoLockRef(&m_lock, -1);
	if (lock_ref != m_lockRef)
	{
		if (m_lockRef)
			delete m_lockRef;
		m_lockRef = lock_ref;
	}

	BuddyThreadClass *thread = new BuddyThreadClass(&m_lock);
	m_thread = thread;
	thread->Execute();

	// Own nested block: the retail body releases the critical-section lock in
	// the same scope as the local, which is what keeps MSVC's frame at
	// `push ecx` / 0x18 rather than allocating 8 fresh bytes with `sub esp,8`.
	{
		CriticalSectionClass::LockClass lock(m_thread->m_criticalSection);
	}
}
