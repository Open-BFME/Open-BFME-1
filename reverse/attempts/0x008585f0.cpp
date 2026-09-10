// _peerAuthenticateCDKey
// partial score=0.98 date=2026-09-10
// BFME GameSpy peerMainBlockingOperations.c full-TU candidate shape.

typedef void *PEER;

typedef struct piConnection
{
	char reserved0[4];
	char nick[64];
	char reserved1[0x1824 - 0x44];
	int callbackDepth;
	char reserved2[0x1F08 - 0x1828];
	int shutdown;
} piConnection;

int piGetNextID(PEER peer);
int piNewAuthenticateCDKeyOperation(PEER peer, const char *cdkey,
	void *callback, void *param, int opID);
void piAddAuthenticateCDKeyCallback(PEER peer, int result,
	const char *message, void *callback, void *param, int opID);
void msleep(unsigned int milliseconds);
void bfmePiThinkFromEsi(int opID);
int PeerOperationsComplete(PEER peer, int opID);
int piIsCallbackFinished(PEER peer, int opID);
void peerShutdown(PEER peer);

void peerAuthenticateCDKey(register PEER peer, const char *cdkey, void *callback,
	void *param, int blocking)
{
	int success = 1;
	register int opID = piGetNextID(peer);
	piConnection *connection = (piConnection *)peer;

	if (!piNewAuthenticateCDKeyOperation(connection, cdkey, callback, param, opID))
		success = 0;

	if (!success)
		piAddAuthenticateCDKeyCallback(connection, 0,
			"Error starting CD Key check", callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!PeerOperationsComplete(connection, opID) ||
			!piIsCallbackFinished(connection, opID));

		if (((piConnection *)connection)->shutdown &&
			((piConnection *)connection)->callbackDepth == 0)
			peerShutdown(connection);
	}
}
