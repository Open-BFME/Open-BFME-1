// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x005592D0: construct a 0x194-byte PeerRequest, set type 0x11
// (PEERREQUEST_STOPQUICKMATCH), queue it.  One unused stack argument (ret 4).

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

// ?_bfme_stopQuickMatchRequest@@YGXH@Z
void __stdcall _bfme_stopQuickMatchRequest( int )
{
	PeerRequest req;
	req.peerRequestType = 0x11;
	TheGameSpyPeerMessageQueue->addRequest( req );
}
