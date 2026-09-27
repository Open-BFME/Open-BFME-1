// cl: /DNDEBUG /MD /EHsc
// GameSpyBuddyMessageQueue's destructor (0x0063D0F0) and the two deleting
// destructors: its own (0x0063E170, slot 0 of its table 0x01118E70) and its
// interface's (0x0063A700, slot 0 of the base table 0x01118E04).

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/BuddyThread.h
class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface() {}
};

class GameResultsMutex { public: ~GameResultsMutex(); private: void *m_data[2]; };
class GameResultsRequestQueue { public: ~GameResultsRequestQueue(); private: unsigned char m_data[0x28]; };
class GameResultsResponseQueue { public: ~GameResultsResponseQueue(); private: unsigned char m_data[0x28]; };
class GameResultsCounter { public: ~GameResultsCounter(); private: void *m_data[2]; };

class GameResultsThreadAux
{
public:
	~GameResultsThreadAux();
};

class GameResultsThreadAuxHolder
{
public:
	~GameResultsThreadAuxHolder() { delete m_ptr; }
	GameResultsThreadAux *get() const { return m_ptr; }
	void clear() { m_ptr = 0; }

private:
	GameResultsThreadAux *m_ptr;
};

class GameResultsThread
{
public:
	virtual ~GameResultsThread();
	void shutdown();
};

class GameSpyBuddyMessageQueue : public GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueue();

private:
	GameResultsMutex m_requestMutex;
	GameResultsMutex m_responseMutex;
	GameResultsRequestQueue m_requests;
	GameResultsResponseQueue m_responses;
	GameResultsThread *m_worker;
	GameResultsCounter m_counters;
	GameResultsThreadAuxHolder m_aux;
};

GameSpyBuddyMessageQueue::~GameSpyBuddyMessageQueue()
{
	if (m_worker)
	{
		delete m_aux.get();
		m_aux.clear();
		// Preserve the thread-owner clear before reloading the worker.
		_ReadWriteBarrier();
		m_worker->shutdown();
		delete m_worker;
	}
	m_worker = 0;
}
