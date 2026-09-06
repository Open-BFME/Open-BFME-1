// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x0010BC80 (176 B) of Watchdog (see
// Watchdog.cpp for the matched constructor/methods; vtable 0x0108E834 --
// (0x01088E34, installed here and by ??0Watchdog@@QAE@HHH@Z) confirms the
// class.  The
// body: release the owned MutexClass::LockClass through a holder (delete +
// null, matching the model Rva00641C60LockHolder shape), close the thread
// handle at +0x44/+0x48 (the already-matched closeLiveHandle body, which
// operates on those relative offsets regardless of the object's real type),
// then delete the critical section at +0x70.  The holder's own destructor
// then fires automatically (no-op, already released), then the MutexClass
// member at +0x88 (whose real destructor is ICF-folded with
// GameResultsCounter's), then the base ThreadClass destructor -- a trivial
// empty virtual dtor that only restores its own vtable (0x01144844).

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

class WatchdogCriticalSection
{
public:
	char m_storage[ 0x18 ];
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

class BFMENetworkBackend
{
public:
	void closeLiveHandle( void );
};

extern "C" __declspec(dllimport) void __stdcall bfmeInitDXB( void *cs );

class ThreadClass
{
public:
	virtual ~ThreadClass();

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
	WatchdogCriticalSection m_criticalSection;
	MutexClass m_mutex;
	WatchdogLockHolder m_ownedLock;
};

// ??1Watchdog@@UAE@XZ
Watchdog::~Watchdog()
{
	m_ownedLock.release();
	( (BFMENetworkBackend *)this )->closeLiveHandle();
	bfmeInitDXB( &m_criticalSection );
}
