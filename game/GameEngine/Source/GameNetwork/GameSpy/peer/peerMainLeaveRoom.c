// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

typedef void *PEER;

typedef struct piConnection
{
	char reserved0[0x48];
	int connected;
	char reserved1[0x60 - 0x4C];
	char title[1];
	char reserved2[0x384 - 0x61];
	int enteringRoom[3];
	int inRoom[3];
	char reserved3[0x1824 - 0x39C];
	int callbackDepth;
	char reserved4[0x18D4 - 0x1828];
	int autoMatchStatus;
	char reserved5[0x1F08 - 0x18D8];
	int shutdown;
} piConnection;

void piLeaveRoom(PEER peer, int roomType, const char *reason);
void piSetAutoMatchStatus(PEER peer, int status);
int piGetNextID(PEER peer);
int piNewListGroupRoomsOperation(PEER peer, const char *fields,
	void *callback, void *param, int opID);
void piAddListGroupRoomsCallback(PEER peer, int success, int groupID,
	const char *name, int maxWaiting, int numWaiting, int numGames,
	int numPlaying, int numRooms, void *callback, void *param, int opID);
void msleep(unsigned int milliseconds);
void bfmePiThinkFromEsi(int opID);
int piIsOperationFinished(PEER peer, int opID);
int piIsCallbackFinished(PEER peer, int opID);
void peerShutdown(PEER peer);

static int piCheckBlockingID(PEER peer, int opID)
{
	return piIsOperationFinished(peer, opID) &&
		piIsCallbackFinished(peer, opID);
}

void peerLeaveRoomA(PEER peer, int roomType, const char *reason)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->title[0])
		return;
	if (!connection->connected)
		return;
	if (!connection->enteringRoom[roomType] && !connection->inRoom[roomType])
		return;

	piLeaveRoom(peer, roomType, reason);
	if (roomType == 2 && connection->autoMatchStatus != 0 &&
		connection->autoMatchStatus != 5)
		piSetAutoMatchStatus(peer, 1);
}

void peerListGroupRoomsA(PEER peer, const char *fields, void *callback,
	void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (!connection->title[0])
		success = 0;
	if (!fields)
		fields = "";
	if (success &&
		!piNewListGroupRoomsOperation(peer, fields, callback, param, opID))
		success = 0;

	if (!success)
		piAddListGroupRoomsCallback(peer, 0, 0, 0, 0, 0, 0, 0, 0,
			callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piCheckBlockingID(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}
