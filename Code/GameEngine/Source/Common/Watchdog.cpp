// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

typedef unsigned long UnsignedInt;

extern "C" UnsignedInt __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) long __cdecl time(long *value);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *criticalSection);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *criticalSection);
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/thread.h
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	void Execute(void);
	void Stop(void);
	virtual void Thread_Function(void) = 0;

private:
	char m_name[0x40];
	volatile unsigned int m_running;
	volatile unsigned long m_handle;
	int m_priority;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class MutexClass
{
public:
	MutexClass(const char *name);

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
	Watchdog(int timeout, int warningInterval, int warningDelay);
	virtual ~Watchdog();
	void suppressTimeouts(void);
	void update(void);
	void resumeTimeouts(void);
	void start(void);
	virtual void Thread_Function(void);
	void stop(void);

private:
	UnsignedInt m_parentThreadId;
	long m_lastHeartbeat;
	int m_timeout;
	UnsignedInt m_previousWarning;
	UnsignedInt m_warningInterval;
	UnsignedInt m_warningDelay;
	UnsignedInt m_nextWarning;
	int m_suppressionCount;
	WatchdogCriticalSection m_criticalSection;
	MutexClass m_mutex;
	MutexClass::LockClass *m_ownedLock;
};

Watchdog *createWatchdog(int timeout, int warningInterval, int warningDelay)
{
	return new Watchdog(timeout, warningInterval, warningDelay);
}

Watchdog::Watchdog(int timeout, int warningInterval, int warningDelay) :
	ThreadClass(0),
	m_parentThreadId(GetCurrentThreadId()),
	m_timeout(timeout),
	m_previousWarning(0),
	m_warningInterval(warningInterval),
	m_warningDelay(warningDelay),
	m_nextWarning(0),
	m_suppressionCount(0),
	m_mutex((*(volatile long *)&m_lastHeartbeat = 0, (const char *)0))
{
	*(MutexClass::LockClass *volatile *)&m_ownedLock = 0;
	if (*(volatile int *)&m_timeout <= 0)
	{
		m_timeout = 1;
	}
	InitializeCriticalSection(&m_criticalSection);
}

void Watchdog::suppressTimeouts(void)
{
	ScopedWatchdogLock suppressionLock(m_criticalSection);
	++*(volatile int *)&m_suppressionCount;
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
	volatile int &suppressionCount = *(volatile int *)&m_suppressionCount;
	if (suppressionCount > 0)
	{
		suppressionCount--;
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
