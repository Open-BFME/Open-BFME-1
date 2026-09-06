// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x00641C60 (237 B) of the BFME game-results
// queue (the SubsystemInterface-derived object GameResultsThread.cpp's
// GameResultsQueue stands for; retail keeps a lock pointer holder at +0x7C a
// network backend pointer at +0x70 a GameResultsCounter at +0x74 the response
// and request deques at +0x40 / +0x18 and two counters at +0x10 / +8).  The
// body releases the lock through the holder (delete then null) and closes
// and deletes the backend (virtual deleting destructor nulling the pointer
// inside the branch); the members then unwind in reverse (the lock holder's inline
// destructor first) then the inline empty GameResultsInterface destructor
// stores its vtable before the out-of-line SubsystemInterface destructor.
// Member types are opaque address-derived shells with out-of-line
// destructors.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class GameResultsInterface : public SubsystemInterface
{
public:
	virtual ~GameResultsInterface() {}
};

class GameResultsCounter
{
public:
	~GameResultsCounter();

private:
	char m_body[ 8 ];
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		~LockClass();

	private:
		char m_body[ 4 ];
	};
};

struct Rva006418E0RequestDeque
{
	~Rva006418E0RequestDeque();
	char m_body[ 0x28 ];
};

struct Rva00641A30ResponseDeque
{
	~Rva00641A30ResponseDeque();
	char m_body[ 0x28 ];
};

class BFMENetworkBackend
{
public:
	virtual ~BFMENetworkBackend();
	void closeLiveHandle( void );
};

struct Rva00641C60LockHolder
{
	~Rva00641C60LockHolder()
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

class Rva00641C60Queue : public GameResultsInterface
{
public:
	virtual ~Rva00641C60Queue();

private:
	char m_unreconstructed04[ 4 ];
	GameResultsCounter m_counter08;
	GameResultsCounter m_counter10;
	Rva006418E0RequestDeque m_requests;
	Rva00641A30ResponseDeque m_responses;
	char m_unreconstructed68[ 8 ];
	BFMENetworkBackend *m_backend;
	GameResultsCounter m_counter74;
	Rva00641C60LockHolder m_lockHolder;
};

// ??1Rva00641C60Queue@@UAE@XZ
Rva00641C60Queue::~Rva00641C60Queue()
{
	m_lockHolder.release();
	if( m_backend )
	{
		m_backend->closeLiveHandle();
		delete m_backend;
		m_backend = 0;
	}
}
