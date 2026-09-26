// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0053AB90, 133 bytes. Construct a 0x194-byte PeerRequest, copy
// the two dwords at 0x012B9660/0x012B9664 into +0xE4/+0xE8, set type 0x19,
// and queue it on TheGameSpyPeerMessageQueue addRequest (+0x18).

class PeerRequest
{
public:
	PeerRequest();
	~PeerRequest();
	int peerRequestType;
	unsigned char m_pad[ 0xE0 ];
	int m_fieldE4;
	int m_fieldE8;
	unsigned char m_tail[ 0x194 - 0xEC ];
};

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
extern int g_bfmePeerReqE4;
extern int g_bfmePeerReqE8;

void postPeerRequest19()
{
	PeerRequest req;
	req.m_fieldE4 = g_bfmePeerReqE4;
	req.m_fieldE8 = g_bfmePeerReqE8;
	req.peerRequestType = 0x19;
	TheGameSpyPeerMessageQueue->addRequest( req );
}
