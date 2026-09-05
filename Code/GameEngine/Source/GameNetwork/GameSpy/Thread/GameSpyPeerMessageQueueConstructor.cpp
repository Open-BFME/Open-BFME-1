// cl: /DNDEBUG /MD /EHsc
// stlport
// BFME GameSpyPeerMessageQueue constructor at retail 0x0064D650.

#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../../../Libraries/Source/WWVegas/WWLib/mutex.h"

#include <queue>

typedef bool Bool;
typedef int Int;

enum SerialAuthResult
{
	SERIAL_NONEXISTENT,
	SERIAL_AUTHFAILED,
	SERIAL_BANNED,
	SERIAL_OK
};

class PeerRequest
{
	public:
	char m_body[4];
};

class PeerResponse
{
	public:
	char m_body[4];
};

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread( void ) = 0;
	virtual void endThread( void ) = 0;
	virtual Bool isThreadRunning( void ) = 0;
	virtual Bool isConnected( void ) = 0;
	virtual Bool isConnecting( void ) = 0;
	virtual void addRequest( const PeerRequest& req ) = 0;
	virtual Bool getRequest( PeerRequest& req ) = 0;
	virtual void addResponse( const PeerResponse& resp ) = 0;
	virtual Bool getResponse( PeerResponse& resp ) = 0;
	virtual SerialAuthResult getSerialAuthResult( void ) = 0;
};

class PeerThreadClass;

typedef std::queue<PeerRequest> RequestQueue;
typedef std::queue<PeerResponse> ResponseQueue;

class GameSpyPeerMessageQueue : public GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueue();
	GameSpyPeerMessageQueue();
	virtual void startThread( void );
	virtual void endThread( void );
	virtual Bool isThreadRunning( void );
	virtual Bool isConnected( void );
	virtual Bool isConnecting( void );

	virtual void addRequest( const PeerRequest& req );
	virtual Bool getRequest( PeerRequest& req );

	virtual void addResponse( const PeerResponse& resp );
	virtual Bool getResponse( PeerResponse& resp );

	virtual SerialAuthResult getSerialAuthResult( void ) { return m_serialAuth; }
	void setSerialAuthResult( SerialAuthResult result ) { m_serialAuth = result; }

	PeerThreadClass* getThread( void );

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	RequestQueue m_requests;
	ResponseQueue m_responses;
	PeerThreadClass *m_thread;

	SerialAuthResult m_serialAuth;
	MutexClass _bfme_hole_thirdMutex;
	Int _bfme_hole_tailWord;
};

GameSpyPeerMessageQueue::GameSpyPeerMessageQueue()
{
	_bfme_hole_tailWord = 0;
	m_thread = NULL;
	m_serialAuth = SERIAL_OK;
}
