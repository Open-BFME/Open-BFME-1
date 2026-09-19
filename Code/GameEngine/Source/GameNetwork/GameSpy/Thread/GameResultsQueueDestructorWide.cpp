// cl: /DNDEBUG /MD /EHsc
// Near-twin of GameResultsQueue::~GameResultsQueue (0x0063D0F0, 225B,
// Code/GameEngine/Source/Common/GameResultsQueueDestructorThunk.cpp) at
// 0x0064C710 (225B). Byte-identical except: the request/response queue
// members' destructors resolve to a different pair of retail ILT thunks
// (0x00014DD0 / 0x00049684), and m_worker carries four extra bytes of
// unmodelled trailing storage before m_counters/m_aux, which shifts those
// two members' offsets from 0x68/0x70 to 0x6c/0x74. Fresh tags per
// NEAR-TWIN policy; identity of the owning class is NOT recovered.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/GameResultsThread.h
class GameResultsInterfaceWide
{
public:
	virtual ~GameResultsInterfaceWide() {}
};

class GameResultsMutexWide { public: ~GameResultsMutexWide(); private: void *m_data[2]; };
class GameResultsCounterWide { public: ~GameResultsCounterWide(); private: void *m_data[2]; };

// Out-of-line dtors pinned directly to the retail ILT thunk stubs
// (0x00014DD0 / 0x00049684), matching how the twin pins its own
// GameResultsRequestQueue/GameResultsResponseQueue destructors to their ILTs
// rather than to the underlying deque bodies.
class GameResultsRequestQueueWide { public: ~GameResultsRequestQueueWide(); private: unsigned char m_data[0x28]; };
class GameResultsResponseQueueWide { public: ~GameResultsResponseQueueWide(); private: unsigned char m_data[0x28]; };

class GameResultsThreadAuxWide
{
public:
	~GameResultsThreadAuxWide();
};

class GameResultsThreadAuxHolderWide
{
public:
	~GameResultsThreadAuxHolderWide() { delete m_ptr; }
	GameResultsThreadAuxWide *get() const { return m_ptr; }
	void clear() { m_ptr = 0; }

private:
	GameResultsThreadAuxWide *m_ptr;
};

class GameResultsThreadWide
{
public:
	virtual ~GameResultsThreadWide();
	void shutdown();
};

class GameResultsQueueWide : public GameResultsInterfaceWide
{
public:
	virtual ~GameResultsQueueWide();

private:
	GameResultsMutexWide m_requestMutex;
	GameResultsMutexWide m_responseMutex;
	GameResultsResponseQueueWide m_requests;
	GameResultsRequestQueueWide m_responses;
	GameResultsThreadWide *m_worker;
	unsigned int m_unmodelled;
	GameResultsCounterWide m_counters;
	GameResultsThreadAuxHolderWide m_aux;
};

GameResultsQueueWide::~GameResultsQueueWide()
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
