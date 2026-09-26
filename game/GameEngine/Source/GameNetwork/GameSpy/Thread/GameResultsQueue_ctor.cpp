// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The 0x01119380 vtable, the 0x00641C60 destructor, the 0x006426E0 factory,
// and the 0x00642060 and 0x006420A0 queue constructors identify this object as
// the BFME game-results queue. The class keeps this constructor beside the
// matching destructor because GameResultsThread.cpp models a different queue
// layout from the one at 0x00642300.

#include <queue>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface() {}

private:
	int m_name;
};

class MutexClass
{
	void *handle;
	unsigned locked;

public:
	MutexClass(const char *name = 0);
	~MutexClass();
};

struct Rva00642060Element
{
	char m_body[32];
};

struct Rva006420A0Element
{
	char m_body[16];
};

class GameResultsQueue
{
public:
	virtual void startThreads();
};

class GameResultsLock
{
public:
	virtual ~GameResultsLock() {}
};

class GameResultsTail
{
public:
	GameResultsTail() : m_lock(0) {}
	~GameResultsTail()
	{
		if (m_lock)
			delete m_lock;
	}

	GameResultsLock *m_lock;
};

class Rva00641C60Queue : public SubsystemInterface
{
public:
	Rva00641C60Queue();
	virtual ~Rva00641C60Queue() {}

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	_STL::queue<Rva00642060Element> m_requests;
	_STL::queue<Rva006420A0Element> m_responses;
	int m_requestCount;
	int m_responseCount;
	void *m_workerThread;
	MutexClass m_bfmeHoleThirdMutex;
	GameResultsTail m_bfmeHoleTailWord;
};

// ??0Rva00641C60Queue@@QAE@XZ
Rva00641C60Queue::Rva00641C60Queue()
	: m_requestMutex(0), m_responseMutex(0), m_requestCount(0), m_responseCount(0), m_bfmeHoleThirdMutex(0)
{
	m_workerThread = 0;
	reinterpret_cast<GameResultsQueue *>(this)->GameResultsQueue::startThreads();
}
