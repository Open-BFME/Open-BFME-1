// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK -- piPingPlayerJoinedRoom from peerPing.c. */

#include <ctype.h>
#include <stdio.h>
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
	char nick[0x40];
	int inRoom[3];
	int local;
	unsigned int IP;
	int profileID;
	int gotIPAndProfileID;
	int flags[3];
	unsigned int lastPingSend;
	unsigned int lastPingRecv;
	unsigned int lastXping;
	int waitingForPing;
	int pingsReturned;
	int pingsLostConsecutive;
	int pingAverage;
	int pingHistory[4];
	int pingHistoryNum;
	int numPings;
	int xpingSent;
	int inPingRoom;
	int inXpingRoom;
	int mustPing;
	int pingOnce;
} piPlayer;

typedef struct piConnection
{
	unsigned char pad0[0x80];
	char rooms[3][0x101];
	void *enteringRoom[3];
	void *inRoom[3];
	unsigned char pad39C[0xAB0 - 0x39C];
	int stayInTitleRoom;
	void *players;
	int numPlayers[3];
	int padAC4;
	int doPings;
	int lastPingTimeMod;
	int pingRoom[3];
	int xpingRoom[3];
	void *xpings;
	int lastXpingSend;
	unsigned char padAF0[0xB44 - 0xAF0];
	int playing;
	unsigned char padB48[0x1828 - 0xB48];
	int away;
} piConnection;

void TableFree(void *table);
void TableRemove(void *table, const void *elem);
int TableCount(void *table);
void TableMap(void *table, void (*mapFn)(void *, void *), void *clientData);
void TableMapSafe(void *table, void (*mapFn)(void *, void *), void *clientData);
void pingerShutdown(void);
void pingerThink(void);
void pingerPing(unsigned int IP, unsigned short port,
	void *pinged, void *pingedParam, int blocking, int timeout);
void piPingPlayerLeftRoomTableMapFn(void *elem, void *clientData);
int piIsPlayerVIP(piPlayer *player, RoomType roomType);
void piMangleIP(char *buffer, unsigned int IP);
void piSendChannelUTM(PEER peer, const char *room, const char *command,
	const char *parameters, int authenticate);

typedef struct piPingerReplyData
{
	PEER peer;
	unsigned int IP;
	int ping;
} piPingerReplyData;

typedef struct piXping
{
	char nicks[2][64];
	int ping;
} piXping;

void *TableNew(int elemSize, int numBuckets,
	int (*hashFn)(const void *, int),
	int (*compareFn)(const void *, const void *),
	void (*freeFn)(void *));
void *TableLookup(void *table, const void *elem);
void TableEnter(void *table, const void *elem);
int piXpingTableHashFn(const void *param, int numBuckets)
{
	piXping *xping = (piXping *)param;
	int i;
	int c;
	const char *str;
	unsigned int hash = 0;
	const char *nicks[2];

	nicks[0] = xping->nicks[0];
	nicks[1] = xping->nicks[1];

	if(strcmp(nicks[1], nicks[0]) < 0)
	{
		const char *temp = nicks[0];
		nicks[0] = nicks[1];
		nicks[1] = temp;
	}

	for(i = 0; i < 2; i++)
	{
		str = nicks[i];
		while((c = *str++) != '\0')
			hash += (unsigned int)tolower(c);
		hash %= (unsigned int)numBuckets;
	}

	return (int)hash;
}
__declspec(dllimport) int __cdecl strcasecmp(const char *left, const char *right);

int piXpingTableCompareFn(const void *param1, const void *param2)
{
	piXping *xping1 = (piXping *)param1;
	piXping *xping2 = (piXping *)param2;
	int i;
	int rcode;
	const char *nicks[2][2];

	nicks[0][0] = xping1->nicks[0];
	nicks[0][1] = xping1->nicks[1];
	nicks[1][0] = xping2->nicks[0];
	nicks[1][1] = xping2->nicks[1];

	for(i = 0; i < 2; i++)
	{
		if(strcmp(nicks[i][1], nicks[i][0]) < 0)
		{
			const char *temp = nicks[i][0];
			nicks[i][0] = nicks[i][1];
			nicks[i][1] = temp;
		}
	}

	for(i = 0; i < 2; i++)
	{
		rcode = strcasecmp(nicks[0][i], nicks[1][i]);
		if(rcode != 0)
			return rcode;
	}

	return 0;
}
void piXpingTableElementFreeFn(void *param)
{
	piXping *xping = (piXping *)param;
	(void)xping;
}
int pingerInit(const char *localAddress, unsigned short localPort,
	void *pinged, void *pingedParam, void *setData, void *setDataParam);
unsigned int current_time(void);
__declspec(dllimport) void srand(unsigned int seed);
piPlayer *piGetPlayer(PEER peer, const char *nick);
piPlayer *piFindPlayerByIP(PEER peer, unsigned int IP);
void piAddPingCallback(PEER peer, const char *nick, int ping);

static void piProcessPing(PEER peer, piPlayer *player, int ping)
{
	int i;
	int total;
	int moveCount;

	player->pingsReturned++;
	player->pingsLostConsecutive = 0;
	player->numPings++;
	player->lastPingRecv = current_time();

	if(player->pingHistoryNum > 0)
	{
		moveCount = (player->pingHistoryNum < 3) ?
			player->pingHistoryNum : 3;
		memmove(player->pingHistory + 1, player->pingHistory,
			(unsigned int)(moveCount * sizeof(int)));
	}
	player->pingHistory[0] = ping;
	if(player->pingHistoryNum < 4)
		player->pingHistoryNum++;

	total = 0;
	for(i = 0; i < player->pingHistoryNum; i++)
		total += player->pingHistory[i];
	player->pingAverage = total / player->pingHistoryNum;

	piAddPingCallback(peer, (const char *)player, ping);
	player->xpingSent = 0;
	if(player->pingOnce)
		player->pingOnce = 0;
}

void piPinged(unsigned int IP, unsigned short port, int ping,
	const char *data, int len, PEER peer)
{
	piPlayer *player;

	player = piFindPlayerByIP(peer, IP);
	if(!player)
		return;

	piProcessPing(peer, player, ping);
}

static void piPingerReplyMapFn(void *elem, void *clientData)
{
	piPlayer *player = (piPlayer *)elem;
	piPingerReplyData *data = (piPingerReplyData *)clientData;

	if(!player->waitingForPing)
		return;

	if(!player->gotIPAndProfileID || player->IP != data->IP)
		return;

	player->waitingForPing = 0;
	if(data->ping == -1)
	{
		player->pingsLostConsecutive++;
		if(player->pingOnce && player->pingsLostConsecutive >= 3)
		{
			player->pingsLostConsecutive = 0;
			player->pingOnce = 0;
		}
	}
	else
	{
		piProcessPing(data->peer, player, data->ping);
	}
}

static piXping *piFindXping(PEER peer, const char *nick1, const char *nick2)
{
	piXping xpingMatch;
	piConnection *connection = (piConnection *)peer;

	strncpy(xpingMatch.nicks[0], nick1, 64);
	xpingMatch.nicks[0][63] = '\0';
	_strlwr(xpingMatch.nicks[0]);
	strncpy(xpingMatch.nicks[1], nick2, 64);
	xpingMatch.nicks[1][63] = '\0';
	_strlwr(xpingMatch.nicks[0]);

	return (piXping *)TableLookup(connection->xpings, &xpingMatch);
}

static piXping *piAddXping(PEER peer, const char *nick1, const char *nick2)
{
	piXping xpingMatch;
	piConnection *connection = (piConnection *)peer;

	strncpy(xpingMatch.nicks[0], nick1, 64);
	xpingMatch.nicks[0][63] = '\0';
	_strlwr(xpingMatch.nicks[0]);
	strncpy(xpingMatch.nicks[1], nick2, 64);
	xpingMatch.nicks[1][63] = '\0';
	_strlwr(xpingMatch.nicks[1]);

	TableEnter(connection->xpings, &xpingMatch);
	return (piXping *)TableLookup(connection->xpings, &xpingMatch);
}

void piUpdateXping(PEER peer, const char *nick1, const char *nick2, int ping)
{
	piPlayer *player1;
	piPlayer *player2;
	piXping *xping;
	piConnection *connection = (piConnection *)peer;

	if(!connection->doPings)
		return;

	player1 = piGetPlayer(peer, nick1);
	if(!player1 || !player1->inXpingRoom)
		return;

	player2 = piGetPlayer(peer, nick2);
	if(!player2 || !player2->inXpingRoom)
		return;

	xping = piAddXping(peer, nick1, nick2);
	if(!xping)
		return;

	xping->ping = ping;
}

int piGetXping(PEER peer, const char *nick1, const char *nick2, int *ping)
{
	piXping *xping;
	piConnection *connection = (piConnection *)peer;

	if(!connection->doPings)
		return 0;

	xping = piFindXping(peer, nick1, nick2);
	if(!xping)
		return 0;

	*ping = xping->ping;
	return 1;
}

typedef struct piPickXpingPlayerData
{
	PEER peer;
	piPlayer *player;
} piPickXpingPlayerData;

void piPickXpingPlayerMap(void *elem, void *clientData)
{
	piPlayer *player = (piPlayer *)elem;
	piPickXpingPlayerData *data = (piPickXpingPlayerData *)clientData;
	unsigned int now;

	if(!player->inXpingRoom)
		return;

	if(player->local)
		return;

	if(!player->numPings)
		return;

	if(player->xpingSent)
		return;

	now = current_time();
	if((now - player->lastXping) < 5000)
		return;

	if(!data->player)
		data->player = player;
	else if((now - player->lastXping) >
		(now - data->player->lastXping))
		data->player = player;
}

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

static void piPingPlayer(PEER peer, piPlayer *player)
{
	if(player->waitingForPing)
		return;

	pingerPing(player->IP, 0x3353, piPingerReply, peer, 0, 5000);
	player->waitingForPing = 1;
	player->lastPingSend = current_time();
	player->mustPing = 0;
}

typedef struct piPickPingPlayersData
{
	PEER peer;
	piPlayer **players;
	int max;
	int num;
} piPickPingPlayersData;

static void piPickPingPlayersMap(void *elem, void *clientData)
{
	piPlayer *player = (piPlayer *)elem;
	piPickPingPlayersData *data = (piPickPingPlayersData *)clientData;
	piPlayer *other;
	unsigned int now;
	unsigned int delay;
	int i;
	int j;

	if(!player->inPingRoom && !player->pingOnce)
		return;
	if(!player->gotIPAndProfileID)
		return;
	if(player->waitingForPing)
		return;
	if(player->local)
		return;
	if((player->inRoom[0] && (player->flags[0] & 12)) ||
		(player->inRoom[1] && (player->flags[1] & 12)) ||
		(player->inRoom[2] && (player->flags[2] & 12)))
		return;

	if(!player->mustPing)
	{
		now = current_time();
		if(player->pingsLostConsecutive >= 4 &&
			(now - player->lastPingSend) < 120000)
			return;
		if(player->inRoom[2])
			delay = 2000;
		else if(player->pingsReturned < 3)
			delay = 5000;
		else
			delay = 30000;
		if((now - player->lastPingSend) < delay)
			return;
		if((now - player->lastPingRecv) < (delay + 1500))
			return;
	}

	for(i = data->max - 1; i >= 0; i--)
	{
		if(!data->players[i])
			continue;
		other = data->players[i];
		if((!other->numPings && player->numPings) ||
			(other->inRoom[2] && !player->inRoom[2]) ||
			(piIsPlayerVIP(other, StagingRoom) &&
			 !piIsPlayerVIP(player, StagingRoom)) ||
			(strcasecmp(other->nick, player->nick) < 0))
			break;
	}

	i++;
	if(i == data->max)
		return;
	for(j = data->max - 1; j > i; j--)
		data->players[j] = data->players[j - 1];
	data->players[i] = player;
	if(data->num < data->max)
		data->num++;
}

static piPlayer **piPickPingPlayers(PEER peer, int *numPings)
{
	static piPlayer *players[12];
	piPickPingPlayersData data;
	piConnection *connection = (piConnection *)peer;

	if(!connection->players || !*numPings || !TableCount(connection->players))
	{
		*numPings = 0;
		return 0;
	}

	data.peer = peer;
	data.players = players;
	data.max = (12 < *numPings) ? 12 : *numPings;
	data.num = 0;
	memset(players, 0, sizeof(piPlayer *) * data.max);
	TableMap(connection->players, piPickPingPlayersMap, &data);
	*numPings = data.num;
	if(!data.players[0])
		return 0;
	return data.players;
}

static void piXpingPlayer(PEER peer, piPlayer *player)
{
	int roomType;
	char message[160];
	char encodedIP[11];
	piConnection *connection = (piConnection *)peer;

	if(!player->inXpingRoom)
		return;
	piMangleIP(encodedIP, player->IP);
	sprintf(message, "%s %d", encodedIP, player->pingAverage);
	for(roomType = 0; roomType < 3; roomType++)
	{
		if(player->inRoom[roomType] && connection->xpingRoom[roomType])
		{
			if(connection->numPlayers[roomType] <= 32)
			{
				if(connection->inRoom[roomType] || connection->enteringRoom[roomType])
					piSendChannelUTM(peer, connection->rooms[roomType], "PNG",
						message, 0);
			}
		}
	}
	player->xpingSent = 1;
	player->lastXping = current_time();
	connection->lastXpingSend = player->lastXping;
}

static piPlayer *piPickXpingPlayer(PEER peer)
{
	piPickXpingPlayerData data;
	piConnection *connection = (piConnection *)peer;

	if(!connection->players || !TableCount(connection->players))
		return 0;
	data.peer = peer;
	data.player = 0;
	TableMap(connection->players, piPickXpingPlayerMap, &data);
	return data.player;
}

void piPingThink(PEER peer)
{
	unsigned int now;
	int pingTimeMod;
	int numPings;
	piPlayer *player;
	piPlayer **players;
	int i;
	piConnection *connection = (piConnection *)peer;

	if(!connection->doPings)
		return;
	if(connection->playing)
		return;
	if(connection->away)
		return;
	now = current_time();
	pingTimeMod = (int)(now / 40);
	if(connection->lastPingTimeMod)
		numPings = pingTimeMod - connection->lastPingTimeMod;
	else
		numPings = 1;
	if(numPings)
		connection->lastPingTimeMod = pingTimeMod;
	players = piPickPingPlayers(peer, &numPings);
	if(players)
	{
		for(i = 0; i < numPings && players[i]; i++)
			piPingPlayer(peer, players[i]);
	}
	if((now - connection->lastXpingSend) > 2000)
	{
		player = piPickXpingPlayer(peer);
		if(player)
			piXpingPlayer(peer, player);
	}
	pingerThink();
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

int piPingInitPlayer(PEER peer, piPlayer *player)
{
	int i;
	piConnection *connection = (piConnection *)peer;

	if(!connection->doPings)
		return 1;

	player->lastPingSend = 0;
	player->lastPingRecv = 0;
	player->lastXping = 0;
	player->waitingForPing = 0;
	player->pingsReturned = 0;
	player->pingsLostConsecutive = 0;
	player->pingAverage = 0;
	for(i = 0; i < 4; i++)
		player->pingHistory[i] = 0;
	player->pingHistoryNum = 0;
	player->numPings = 0;
	player->xpingSent = 0;
	player->inPingRoom = 0;
	player->inXpingRoom = 0;
	player->mustPing = 0;
	player->pingOnce = 0;

	return 1;
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

typedef struct piPingPlayerLeftRoomData
{
	PEER peer;
	const char *nick;
} piPingPlayerLeftRoomData;

void piPingPlayerLeftRoomTableMapFn(void *elem, void *clientData)
{
	piXping *xping = (piXping *)elem;
	piPingPlayerLeftRoomData *data = (piPingPlayerLeftRoomData *)clientData;

	if(strcmp(xping->nicks[0], data->nick) == 0 ||
		strcmp(xping->nicks[1], data->nick) == 0)
	{
		TableRemove(((piConnection *)data->peer)->xpings, xping);
	}
}

void piPingPlayerLeftRoom(PEER peer, piPlayer *player)
{
	piConnection *connection = (piConnection *)peer;

	if(!connection->doPings)
		return;

	if(player->inPingRoom)
	{
		int i;
		int inPingRoom = 0;

		for(i = 0; i < 3; i++)
		{
			if(player->inRoom[i] && connection->pingRoom[i])
				inPingRoom = 1;
		}
		player->inPingRoom = inPingRoom;
	}

	if(player->inXpingRoom)
	{
		int i;
		int inXpingRoom = 0;

		for(i = 0; i < 3; i++)
		{
			if(player->inRoom[i] && connection->xpingRoom[i])
				inXpingRoom = 1;
		}
		player->inXpingRoom = inXpingRoom;

		if(!player->inXpingRoom)
		{
			piPingPlayerLeftRoomData data;
			data.peer = peer;
			data.nick = (const char *)player;
			TableMapSafe(connection->xpings,
				piPingPlayerLeftRoomTableMapFn, &data);
		}
	}
}
