// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release, peerConnectPreAuthA.

typedef int PEERBool;
typedef void *PEER;

typedef struct piConnection
{
	void *chat;
	char nick[64];
	PEERBool connecting;
	PEERBool connected;
	void *nickErrorCallback;
	unsigned int lastChatPing;
	unsigned int publicIP;
	unsigned int privateIP;
	int profileID;
	char title[64];
	char reserved[0x1824 - 0xA0];
	int numCallbacksInCall;
	char reserved2[0x1F04 - 0x1828];
	PEERBool disconnect;
	PEERBool shutdown;
} piConnection;

int piGetNextID(PEER peer);
int piNewConnectOperation(PEER peer, int type, const char *nick, int namespaceID,
	const char *email, const char *profilenick, const char *uniquenick,
	const char *password, const char *authtoken, const char *partnerchallenge,
	void *callback, void *param, int ID);
void bfmePiDisconnectCleanupFromEsi(void);
void piAddConnectCallback(PEER peer, PEERBool success, int failureReason,
	void *callback, void *param, int ID);
void msleep(unsigned int milliseconds);
void bfmePiThinkFromEsi(int ID);
int PeerOperationsComplete(PEER peer, int ID);
int piIsCallbackFinished(PEER peer, int ID);
void peerShutdown(PEER peer);

void peerConnectPreAuthA(PEER peer, const char *authtoken,
	const char *partnerchallenge, void *nickErrorCallback,
	void *connectCallback, void *param, PEERBool blocking)
{
	PEERBool success = 1;
	int opID = piGetNextID(peer);
	piConnection *connection = (piConnection *)peer;

	if (connection->connected || connection->connecting)
		success = 0;
	if (success && !connection->title[0])
		success = 0;

	if (success) {
		connection->chat = 0;
		connection->nick[0] = '\0';
		connection->connected = 0;
		connection->connecting = 1;
		connection->nickErrorCallback = nickErrorCallback;
		connection->profileID = 0;
		connection->disconnect = 0;

		if (!piNewConnectOperation(peer, 3, 0, 0, 0, 0, 0, 0,
				authtoken, partnerchallenge, connectCallback, param, opID)) {
			success = 0;
			bfmePiDisconnectCleanupFromEsi();
		}
	}

	if (!success)
		piAddConnectCallback(peer, 0, 0, connectCallback, param, opID);

	if (blocking) {
		do {
			msleep(1);
			bfmePiThinkFromEsi(opID);
		} while (!PeerOperationsComplete(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->numCallbacksInCall == 0)
			peerShutdown(peer);
	}
}
