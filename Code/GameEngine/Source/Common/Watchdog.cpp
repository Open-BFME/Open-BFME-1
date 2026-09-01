// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

typedef unsigned long UnsignedInt;

extern "C" UnsignedInt __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) long __cdecl time(long *value);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *criticalSection);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *criticalSection);

class WatchdogCriticalSection
{
public:
	void enter(void) { EnterCriticalSection(this); }
	void leave(void) { LeaveCriticalSection(this); }

private:
	char m_storage[0x18];
};

class ScopedWatchdogLock
{
public:
	ScopedWatchdogLock(WatchdogCriticalSection &criticalSection) : m_criticalSection(criticalSection)
	{
		m_criticalSection.enter();
	}
	~ScopedWatchdogLock()
	{
		m_criticalSection.leave();
	}

private:
	WatchdogCriticalSection &m_criticalSection;
};

class ThreadClass
{
public:
	void Execute(void);
	void Stop(void);

private:
	char m_storage[0x50];
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int timeout);
		~LockClass();

private:
		MutexClass &m_mutex;
		bool m_failed;
	};

private:
	void *m_handle;
	unsigned int m_locked;
};

class Watchdog : public ThreadClass
{
public:
	void suppressTimeouts(void);
	void update(void);
	void resumeTimeouts(void);
	void start(void);
	void stop(void);

private:
	UnsignedInt m_parentThreadId;
	long m_lastHeartbeat;
	UnsignedInt m_timeout;
	UnsignedInt m_previousWarning;
	UnsignedInt m_warningInterval;
	UnsignedInt m_warningDelay;
	UnsignedInt m_nextWarning;
	volatile int m_suppressionCount;
	WatchdogCriticalSection m_criticalSection;
	MutexClass m_mutex;
	MutexClass::LockClass *m_ownedLock;
};

void Watchdog::suppressTimeouts(void)
{
	ScopedWatchdogLock suppressionLock(m_criticalSection);
	++m_suppressionCount;
}

void Watchdog::update(void)
{
	long now;
	UnsignedInt currentThread = GetCurrentThreadId();
	if (currentThread == m_parentThreadId)
	{
		time(&now);
		ScopedWatchdogLock lock(m_criticalSection);
		m_lastHeartbeat = now;
	}
}

void Watchdog::resumeTimeouts(void)
{
	long now;
	UnsignedInt currentThread = GetCurrentThreadId();
	if (currentThread == m_parentThreadId)
	{
		time(&now);
		ScopedWatchdogLock heartbeatLock(m_criticalSection);
		m_lastHeartbeat = now;
	}

	ScopedWatchdogLock suppressionLock(m_criticalSection);
	if (m_suppressionCount > 0)
	{
		m_suppressionCount--;
	}
}

void Watchdog::start(void)
{
	MutexClass::LockClass *lock = new MutexClass::LockClass(m_mutex, -1);
	if (lock != m_ownedLock)
	{
		delete m_ownedLock;
		m_ownedLock = lock;
	}
	ThreadClass::Execute();
}

void Watchdog::stop(void)
{
	delete m_ownedLock;
	m_ownedLock = 0;
	ThreadClass::Stop();
}
