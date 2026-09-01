// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK -- piPingPlayerJoinedRoom from peerPing.c. */

#include <string.h>

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
	void *players;
	unsigned char padAB8[0xAC8 - 0xAB8];
	int doPings;
	int lastPingTimeMod;
	int pingRoom[3];
	int xpingRoom[3];
	void *xpings;
	int lastXpingSend;
} piConnection;

void TableFree(void *table);
void TableMap(void *table, void (*mapFn)(void *, void *), void *clientData);
void pingerShutdown(void);
void piPingerReplyMapFn(void *elem, void *clientData);

typedef struct piPingerReplyData
{
	PEER peer;
	unsigned int IP;
	int ping;
} piPingerReplyData;

typedef struct piXping
{
	unsigned char data[0x84];
} piXping;

void *TableNew(int elemSize, int numBuckets,
	int (*hashFn)(const void *, int),
	int (*compareFn)(const void *, const void *),
	void (*freeFn)(void *));
int piXpingTableHashFn(const void *param, int numBuckets);
int piXpingTableCompareFn(const void *param1, const void *param2);
void piXpingTableElementFreeFn(void *param);
void piPinged(unsigned int IP, unsigned short port, int ping,
	const char *data, int len, PEER peer);
int pingerInit(const char *localAddress, unsigned short localPort,
	void *pinged, void *pingedParam, void *setData, void *setDataParam);
unsigned int current_time(void);
__declspec(dllimport) void srand(unsigned int seed);

int piPingInit(PEER peer)
{
	static int noPings[3];
	piConnection *connection = (piConnection *)peer;

	if(memcmp(connection->pingRoom, noPings, sizeof(noPings)) == 0)
		return 1;

	connection->xpings = TableNew(sizeof(piXping), 32,
		piXpingTableHashFn, piXpingTableCompareFn,
		piXpingTableElementFreeFn);
	if(!connection->xpings)
		return 0;

	if(!pingerInit(0, 0x3353, piPinged, peer, 0, 0))
		return 0;

	connection->lastPingTimeMod = 0;
	connection->lastXpingSend = 0;
	srand(current_time());
	connection->doPings = 1;

	return 1;
}

void piPingerReply(unsigned int IP, unsigned short port, int ping,
	const char *pingData, int pingDataLen, PEER peer)
{
	piPingerReplyData data;
	piConnection *connection = (piConnection *)peer;

	data.peer = peer;
	data.IP = IP;
	data.ping = ping;
	TableMap(connection->players, piPingerReplyMapFn, &data);
}

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
