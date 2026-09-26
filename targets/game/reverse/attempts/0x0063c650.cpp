// ?startThread@GameSpyBuddyMessageQueue@@UAEXXZ
// partial score=0.28 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// BFME GameSpyBuddyMessageQueue::startThread at retail 0x0063C650.

class BFMENetworkLock
{
public:
	void *m_handle;
	unsigned int m_refCount;
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int time);
		~LockClass();

	private:
		MutexClass &m_mutex;
		bool m_failed;
		char m_padding[3];
	};

private:
	char m_body[8];
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

class BuddyThreadClass
{
public:
	BuddyThreadClass(BFMENetworkLock *lock);
	virtual ~BuddyThreadClass();
	virtual void Execute();
	virtual void Thread_Function();

private:
	char m_prefix[0x9c];

public:
	CriticalSectionClass m_criticalSection;

private:
	char m_suffix[4];
};

class GameSpyBuddyMessageQueue
{
public:
	virtual void startThread();

private:
	char m_prefix[0x60];
	BuddyThreadClass *m_thread;
	BFMENetworkLock m_lock;
	MutexClass::LockClass *m_lockRef;
};

void GameSpyBuddyMessageQueue::startThread()
{
	if (m_thread)
		return;

	MutexClass::LockClass *lock_ref =
		new MutexClass::LockClass(reinterpret_cast<MutexClass &>(m_lock), -1);
	if (lock_ref != m_lockRef)
	{
		if (m_lockRef)
			delete m_lockRef;
		m_lockRef = lock_ref;
	}

	m_thread = new BuddyThreadClass(&m_lock);
	m_thread->Execute();
	CriticalSectionClass::LockClass lock(m_thread->m_criticalSection);
}
