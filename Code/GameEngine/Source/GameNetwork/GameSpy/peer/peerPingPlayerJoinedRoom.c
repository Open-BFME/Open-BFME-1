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
	unsigned char pad0[0xAC8];
	int doPings;
	unsigned char padACC[0xAD0 - 0xACC];
	int pingRoom[3];
	int xpingRoom[3];
} piConnection;

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
