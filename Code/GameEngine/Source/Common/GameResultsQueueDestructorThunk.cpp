// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/GameResultsThread.h
class GameResultsInterface
{
public:
	virtual ~GameResultsInterface() {}
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

class GameResultsQueue : public GameResultsInterface
{
public:
	virtual ~GameResultsQueue();

private:
	GameResultsMutex m_requestMutex;
	GameResultsMutex m_responseMutex;
	GameResultsRequestQueue m_requests;
	GameResultsResponseQueue m_responses;
	GameResultsThread *m_worker;
	GameResultsCounter m_counters;
	GameResultsThreadAuxHolder m_aux;
};

GameResultsQueue::~GameResultsQueue()
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
