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

class Watchdog
{
public:
	void update(void);
	void stop(void);

private:
	char m_threadBase[0x50];
	UnsignedInt m_parentThreadId;
	long m_lastHeartbeat;
	UnsignedInt m_timeout;
	UnsignedInt m_previousWarning;
	UnsignedInt m_warningInterval;
	UnsignedInt m_warningDelay;
	UnsignedInt m_nextWarning;
	int m_suppressionCount;
	WatchdogCriticalSection m_criticalSection;
	char m_event[8];
	void *m_ownedState;
};

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
