// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00559360: thiscall.  Queue a 0x194-byte PeerRequest of type 0x12
// (PEERREQUEST_PUSHSTATS) and clear this+0x3c.  One unused stack argument.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();
	int peerRequestType;
	char m_bfmeBody[ 0x190 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual int isThreadRunning() = 0;
	virtual int isConnected() = 0;
	virtual int isConnecting() = 0;
	virtual void addRequest( const PeerRequest &request ) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

class BfmePushStatsHost
{
public:
	void pushStats( int unused );

private:
	unsigned char m_unmodelled[ 0x3c ];
	int m_flag;
};

// ?pushStats@BfmePushStatsHost@@QAEXH@Z
void BfmePushStatsHost::pushStats( int )
{
	PeerRequest req;
	req.peerRequestType = 0x12;
	TheGameSpyPeerMessageQueue->addRequest( req );
	m_flag = 0;
}
