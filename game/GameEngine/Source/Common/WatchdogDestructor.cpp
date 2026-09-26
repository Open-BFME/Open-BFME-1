// cl: /DNDEBUG /MD /EHsc
#include <windows.h>

// Preserve holder, mutex and ThreadClass destruction in retail order.

class MutexClass
{
public:
	~MutexClass();

	class LockClass
	{
	public:
		~LockClass();

	private:
		char m_body[ 4 ];
	};

private:
	void *m_handle;
	unsigned int m_locked;
};

class WatchdogLockHolder
{
public:
	~WatchdogLockHolder()
	{
		if( m_lock )
			delete m_lock;
	}

	void release( void )
	{
		if( m_lock )
			delete m_lock;
		m_lock = 0;
	}

	MutexClass::LockClass *m_lock;
};

class ThreadClass
{
public:
	virtual ~ThreadClass();
	void Stop(void);

private:
	char m_name[ 0x40 ];
	volatile unsigned int m_running;
	volatile unsigned long m_handle;
	int m_priority;
};

class Watchdog : public ThreadClass
{
public:
	virtual ~Watchdog();

private:
	unsigned int m_parentThreadId;
	long m_lastHeartbeat;
	int m_timeout;
	unsigned int m_previousWarning;
	unsigned int m_warningInterval;
	unsigned int m_warningDelay;
	unsigned int m_nextWarning;
	int m_suppressionCount;
	CRITICAL_SECTION m_criticalSection;
	MutexClass m_mutex;
	WatchdogLockHolder m_ownedLock;
};

// ??1Watchdog@@UAE@XZ
Watchdog::~Watchdog()
{
	m_ownedLock.release();
	ThreadClass::Stop();
	DeleteCriticalSection( &m_criticalSection );
}
