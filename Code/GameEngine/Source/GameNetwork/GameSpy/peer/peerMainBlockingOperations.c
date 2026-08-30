// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

typedef void *PEER;

typedef struct piConnection
{
	char reserved0[4];
	char nick[64];
	int connecting;
	int connected;
	char reserved1[0x1824 - 0x4C];
	int callbackDepth;
	char reserved2[0x1F08 - 0x1828];
	int shutdown;
} piConnection;

int piGetNextID(PEER peer);
int piNewChangeNickOperation(PEER peer, const char *newNick,
	void *callback, void *param, int opID);
void piAddChangeNickCallback(PEER peer, int success, const char *oldNick,
	const char *newNick, void *callback, void *param, int opID);
int piNewGetGlobalKeysOperation(PEER peer, const char *target, int num,
	const char **keys, void *callback, void *param, int opID);
void piAddGetGlobalKeysCallback(PEER peer, int success, const char *nick,
	int num, const char **keys, const char **values, void *callback,
	void *param, int opID);
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

void peerGetPlayerGlobalKeysA(PEER peer, const char *nick, int num,
	const char **keys, void *callback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (!connection->connected)
		return;
	if (!nick || !nick[0])
		nick = connection->nick;

	if (!piNewGetGlobalKeysOperation(peer, nick, num, keys, callback, param,
			opID))
		success = 0;
	if (!success)
		piAddGetGlobalKeysCallback(peer, 0, nick, 0, 0, 0, callback, param,
			opID);

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
