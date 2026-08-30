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
	char reserved3[0x18D4 - 0x39C];
	int autoMatchStatus;
} piConnection;

void piLeaveRoom(PEER peer, int roomType, const char *reason);
void piSetAutoMatchStatus(PEER peer, int status);

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
