// BFME's PeerResponse is 0x330 bytes.  The Zero Hour reference header has the
// same fields and callback behavior, but its reduced string layout is smaller.
typedef void *PEER;

enum qr2_error_t
{
	QR2_ERROR_DUMMY
};

class PeerResponse
{
public:
	enum ResponseType
	{
		PEERRESPONSE_FAILEDTOHOST = 19
	};

	PeerResponse();
	~PeerResponse();

	int peerResponseType;
	char m_bfmeBody[0x32c];
};

class PeerRequest;

class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual int isThreadRunning() = 0;
	virtual int isConnected() = 0;
	virtual int isConnecting() = 0;
	virtual void addRequest(const PeerRequest &request) = 0;
	virtual int getRequest(PeerRequest &request) = 0;
	virtual void addResponse(const PeerResponse &response) = 0;
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

void QRAddErrorCallback(
	PEER peer,
	qr2_error_t error,
	char *errorString,
	void *param)
{
	PeerResponse response;
	response.peerResponseType = PeerResponse::PEERRESPONSE_FAILEDTOHOST;
	TheGameSpyPeerMessageQueue->addResponse(response);
}
