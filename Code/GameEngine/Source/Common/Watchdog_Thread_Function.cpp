// ?Thread_Function@Watchdog@@UAEXXZ
// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) long __cdecl time(long *value);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int timeout);
		~LockClass();
		bool Failed() const { return m_failed; }

	private:
		MutexClass &m_mutex;
		bool m_failed;
	};

private:
	void *m_handle;
	unsigned int m_locked;
};

class WatchdogCriticalSection
{
public:
	void enter()
	{
		EnterCriticalSection(this);
	}

	void leave()
	{
		LeaveCriticalSection(this);
	}

private:
	char m_storage[0x18];
};

class ScopedWatchdogLock
{
public:
	ScopedWatchdogLock(WatchdogCriticalSection &section) : m_section(section)
	{
		m_section.enter();
	}

	~ScopedWatchdogLock()
	{
		m_section.leave();
	}

private:
	WatchdogCriticalSection &m_section;
};

class Watchdog
{
public:
	virtual ~Watchdog();
	virtual void start();
	virtual void Thread_Function();
	virtual void reportWatchdog();

private:
	char m_threadClass[0x4c];
	UnsignedInt m_parentThreadId;
	long m_lastHeartbeat;
	int m_timeout;
	long m_previousWarning;
	long m_warningInterval;
	long m_warningDelay;
	long m_nextWarning;
	int m_suppressionCount;
	WatchdogCriticalSection m_criticalSection;
	MutexClass m_mutex;
};

// ?Thread_Function@Watchdog@@UAEXXZ
void Watchdog::Thread_Function()
{
	for (;;)
	{
		MutexClass::LockClass lock(m_mutex, 1000);
		if (!lock.Failed())
			break;

		long lastHeartbeat;
		int suppressionCount;
		{
			ScopedWatchdogLock criticalSectionLock(m_criticalSection);
			lastHeartbeat = m_lastHeartbeat;
			suppressionCount = m_suppressionCount;
		}

		long now;
		time(&now);
		if (suppressionCount < 0 && now >= m_nextWarning)
		{
			long warningTime;
			if (now - m_previousWarning > m_warningInterval)
			{
				const long warningDelay = m_warningDelay;
				warningTime = m_nextWarning = now + warningDelay;
			}
			else
			{
				if (lastHeartbeat != 0 && lastHeartbeat < now)
				{
					long heartbeatDelta = now - lastHeartbeat;
					if (heartbeatDelta > m_timeout)
					{
						reportWatchdog();
					}
				}
				warningTime = now;
			}
			m_previousWarning = warningTime;
		}
	}
}
