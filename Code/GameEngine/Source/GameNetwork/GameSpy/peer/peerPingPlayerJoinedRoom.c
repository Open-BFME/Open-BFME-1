// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK -- piPingPlayerJoinedRoom from peerPing.c. */

typedef void *PEER;

typedef enum RoomType
{
	TitleRoom,
	GroupRoom,
	StagingRoom
} RoomType;

typedef struct piPlayer
{
	unsigned char pad0[0xA0];
	int inPingRoom;
	int inXpingRoom;
	int mustPing;
} piPlayer;

typedef struct piConnection
{
	unsigned char pad0[0xAB0];
	int stayInTitleRoom;
	unsigned char padAB4[0xAC8 - 0xAB4];
	int doPings;
	int lastPingTimeMod;
	int pingRoom[3];
	int xpingRoom[3];
	void *xpings;
	int lastXpingSend;
} piConnection;

void TableFree(void *table);
void pingerShutdown(void);

void piPingCleanup(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if(!connection->doPings)
		return;

	if(connection->stayInTitleRoom)
		return;

	connection->lastPingTimeMod = 0;
	connection->lastXpingSend = 0;

	if(connection->xpings)
		TableFree(connection->xpings);
	connection->xpings = 0;

	pingerShutdown();
	connection->doPings = 0;
}

void piPingPlayerJoinedRoom(PEER peer, piPlayer *player, RoomType roomType)
{
	piConnection *connection = (piConnection *)peer;

	if(!connection->doPings)
		return;

	if(connection->pingRoom[roomType])
		player->inPingRoom = 1;

	if(connection->xpingRoom[roomType])
		player->inXpingRoom = 1;

	if(roomType == StagingRoom)
		player->mustPing = 1;
}
