// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

typedef void *PEER;

typedef struct piConnection
{
	void *chat;
	char nick[64];
	int connecting;
	int connected;
	void *nickErrorCallback;
	char reserved0[0x5C - 0x50];
	int profileID;
	char title[32];
	char room[3][257];
	int enteringRoom[3];
	int inRoom[3];
	char reserved1[0xAB0 - 0x39C];
	int stayInTitleRoom;
	char reservedStay[0x1824 - 0xAB4];
	int callbackDepth;
	char reserved2[0x1F04 - 0x1828];
	int disconnect;
	int shutdown;
} piConnection;

int piGetNextID(PEER peer);
int piNewChangeNickOperation(PEER peer, const char *newNick,
	void *callback, void *param, int opID);
void piAddChangeNickCallback(PEER peer, int success, const char *oldNick,
	const char *newNick, void *callback, void *param, int opID);
int piNewGetGlobalKeysOperation(PEER peer, const char *target, int num,
	const char **keys, void *callback, void *param, int opID);
int piNewGetRoomKeysOperation(PEER peer, int roomType, const char *nick,
	int num, const char **keys, void *callback, void *param, int opID);
int piNewConnectOperation(PEER peer, int type, const char *nick,
	int namespaceID, const char *email, const char *profilenick,
	const char *uniquenick, const char *password, const char *authtoken,
	const char *partnerchallenge, void *callback, void *param, int opID);
void piAddGetGlobalKeysCallback(PEER peer, int success, const char *nick,
	int num, const char **keys, const char **values, void *callback,
	void *param, int opID);
void piAddGetRoomKeysCallback(PEER peer, int success, int roomType,
	const char *nick, int num, const char **keys, const char **values,
	void *callback, void *param, int opID);
void chatSetGlobalKeysA(void *chat, int num, const char **keys,
	const char **values);
void piAddConnectCallback(PEER peer, int success, int failureReason,
	void *callback, void *param, int opID);
void bfmePiDisconnectCleanupFromEsi(void);
void msleep(unsigned int milliseconds);
void bfmePiThinkFromEsi(int opID);
int piIsOperationFinished(PEER peer, int opID);
int PeerOperationsComplete(PEER peer, int opID);
int piIsCallbackFinished(PEER peer, int opID);
void peerShutdown(PEER peer);
__declspec(dllimport) char *__cdecl strncpy(char *destination,
	const char *source, unsigned int count);

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

void peerConnectA(PEER peer, const char *nick, int profileID,
	void *nickErrorCallback, void *connectCallback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (connection->connected || connection->connecting)
		success = 0;
	if (success && !connection->title[0])
		success = 0;

	if (success)
	{
		connection->chat = 0;
		strncpy(connection->nick, nick, 64);
		connection->nick[63] = '\0';
		connection->connected = 0;
		connection->connecting = 1;
		connection->nickErrorCallback = nickErrorCallback;
		connection->profileID = profileID;
		connection->disconnect = 0;

		if (!piNewConnectOperation(peer, 0, nick, 0, 0, 0, 0, 0, 0, 0,
				connectCallback, param, opID))
		{
			success = 0;
			bfmePiDisconnectCleanupFromEsi();
		}
	}

	if (!success)
		piAddConnectCallback(peer, 0, 0, connectCallback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!PeerOperationsComplete(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerDisconnect(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (connection->callbackDepth > 0)
	{
		connection->disconnect = 1;
	}
	else
	{
		connection->stayInTitleRoom = 0;
		bfmePiDisconnectCleanupFromEsi();
		bfmePiThinkFromEsi(-1);
	}

	if (connection->shutdown && connection->callbackDepth == 0)
		peerShutdown(peer);
}

void peerConnectLoginA(PEER peer, int namespaceID, const char *email,
	const char *profilenick, const char *uniquenick, const char *password,
	void *nickErrorCallback, void *connectCallback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (connection->connected || connection->connecting)
		success = 0;
	if (success && !connection->title[0])
		success = 0;

	if (success)
	{
		connection->chat = 0;
		connection->nick[0] = '\0';
		connection->connected = 0;
		connection->connecting = 1;
		connection->nickErrorCallback = nickErrorCallback;
		connection->profileID = 0;
		connection->disconnect = 0;

		if (!piNewConnectOperation(peer,
				(uniquenick && uniquenick[0]) ? 1 : 2, 0, namespaceID,
				email, profilenick, uniquenick, password, 0, 0,
				connectCallback, param, opID))
		{
			success = 0;
			bfmePiDisconnectCleanupFromEsi();
		}
	}

	if (!success)
		piAddConnectCallback(peer, 0, 0, connectCallback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!PeerOperationsComplete(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerGetRoomKeysA(PEER peer, int roomType, const char *nick, int num,
	const char **keys, void *callback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (!connection->connected)
		return;
	if (!connection->enteringRoom[roomType] && !connection->inRoom[roomType])
		return;

	if (!piNewGetRoomKeysOperation(peer, roomType, nick, num, keys, callback,
			param, opID))
		success = 0;
	if (!success)
		piAddGetRoomKeysCallback(peer, 0, roomType, nick, 0, 0, 0,
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

void peerSetGlobalKeysA(PEER peer, int num, const char **keys,
	const char **values)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->connected)
		return;
	chatSetGlobalKeysA(connection->chat, num, keys, values);
}
