// _peerAuthenticateCDKeyA
// partial score=0.97 date=2026-08-30
// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

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
int piNewChangeNickOperation(PEER peer, const char *newNick,
	void *callback, void *param, int opID);
void piAddChangeNickCallback(PEER peer, int success, const char *oldNick,
	const char *newNick, void *callback, void *param, int opID);
int piNewAuthenticateCDKeyOperation(PEER peer, const char *cdkey,
	void *callback, void *param, int opID);
void piAddAuthenticateCDKeyCallback(PEER peer, int result,
	const char *message, void *callback, void *param, int opID);
void msleep(unsigned int milliseconds);
void bfmePiThinkFromEsi(int opID);
int piIsOperationFinished(PEER peer, int opID);
int piIsCallbackFinished(PEER peer, int opID);
void peerShutdown(PEER peer);

void peerChangeNickA(PEER peer, const char *newNick, void *callback,
	void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (!piNewChangeNickOperation(peer, newNick, callback, param, opID))
		success = 0;

	if (!success)
		piAddChangeNickCallback(peer, 0, connection->nick, newNick,
			callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerAuthenticateCDKeyA(PEER peer, const char *cdkey, void *callback,
	void *param, int blocking)
{
	int success = 1;
	register piConnection *connection = (piConnection *)peer;
	int opID = piGetNextID(connection);

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
		while (!piIsOperationFinished(connection, opID) ||
			!piIsCallbackFinished(connection, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(connection);
	}
}
