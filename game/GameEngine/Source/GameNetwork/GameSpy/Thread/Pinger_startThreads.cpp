// cl: /DNDEBUG /MD /EHsc
// Open-BFME conversion of Pinger::startThreads at retail 0x0065EFD0.

typedef int Int;
typedef bool Bool;

class AsciiString;
class PingRequest;
class PingResponse;

class PingerInterface
{
public:
	virtual ~PingerInterface() {}
	virtual void startThreads() = 0;
	virtual void endThreads() = 0;
	virtual Bool areThreadsRunning() = 0;
	virtual void addRequest(const PingRequest &) = 0;
	virtual Bool getRequest(PingRequest &) = 0;
	virtual void addResponse(const PingResponse &) = 0;
	virtual Bool getResponse(PingResponse &) = 0;
	virtual Bool arePingsInProgress() = 0;
	virtual Int getPing(AsciiString) = 0;
	virtual void clearPingMap() = 0;
	virtual AsciiString getPingString(Int) = 0;
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &, int);
		~LockClass();

		unsigned char m_bfmeBody[8];
	};

	unsigned char m_bfmeBody[8];
};

extern "C" void *bfmeVft1028A[];

class ThreadClass
{
public:
	ThreadClass(const char *name);

	void *volatile m_bfmeVft;
	unsigned char m_bfmeBody[0x4c];
};

class PingThreadClass : public ThreadClass
{
public:
	__forceinline PingThreadClass(MutexClass *mutex) : ThreadClass(0)
	{
		m_bfmeVft = bfmeVft1028A;
		m_mutex = mutex;
	}

	MutexClass *m_mutex;
};

typedef void (__fastcall *PingThreadExecute)(PingThreadClass *self);

class Pinger : public PingerInterface
{
public:
	virtual ~Pinger();
	virtual void startThreads();
	virtual void endThreads();

private:
	unsigned char m_bfmeHead[0x7c];
	PingThreadClass *m_workerThreads[10];
	MutexClass m_workerMutex;
	MutexClass::LockClass *m_workerLock;
};

void Pinger::startThreads()
{
	endThreads();

	MutexClass::LockClass *lock = new MutexClass::LockClass(m_workerMutex, -1);
	if (lock != m_workerLock)
	{
		delete m_workerLock;
		m_workerLock = lock;
	}

	for (Int index = 0; index < 10; ++index)
	{
		m_workerThreads[index] = new PingThreadClass(&m_workerMutex);
		((PingThreadExecute *)m_workerThreads[index]->m_bfmeVft)[1](m_workerThreads[index]);
	}
}
