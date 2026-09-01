// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// Upstream: GameSpy Peer SDK peerPlayers.c, 2004 release.

#include <ctype.h>
#include <string.h>

typedef int PEERBool;
typedef int RoomType;
typedef void *HashTable;

enum
{
	StagingRoom = 2,
	CHAT_VOICE = 0x01,
	CHAT_OP = 0x02,
	PEER_FLAG_STAGING = 0x01,
	PEER_FLAG_READY = 0x02,
	PEER_FLAG_PLAYING = 0x04,
	PEER_FLAG_AWAY = 0x08,
	PEER_FLAG_HOST = 0x10,
	PEER_FLAG_OP = 0x20,
	PEER_FLAG_VOICE = 0x40
};

typedef struct piPlayer
{
	char nick[0x40];
	PEERBool inRoom[3];
	PEERBool local;
	unsigned int IP;
	int profileID;
	PEERBool gotIPAndProfileID;
	int flags[3];
	char unreconstructed_68[0xB0 - 0x68];
} piPlayer;

typedef struct piConnection
{
	char unreconstructed_0000[4];
	char nick[0x40];
	char unreconstructed_0044[0x384 - 0x44];
	PEERBool enteringRoom[3];
	PEERBool inRoom[3];
	char unreconstructed_039C[0xAB0 - 0x39C];
	PEERBool stayInTitleRoom;
	HashTable players;
	int numPlayers[3];
} piConnection;

typedef piConnection *PEER;

piPlayer *piGetPlayer(PEER peer, const char *nick);
void piAddReadyChangedCallback(PEER peer, const char *nick, PEERBool ready);
void piAddPlayerFlagsChangedCallback(PEER peer, RoomType roomType,
	const char *nick, int oldFlags, int newFlags);
void *TableMap2(HashTable table, int (*mapFn)(void *, void *), void *clientData);
void TableMap(HashTable table, void (*mapFn)(void *, void *), void *clientData);
void TableMapSafe(HashTable table, void (*mapFn)(void *, void *),
	void *clientData);
void *TableLookup(HashTable table, const void *elem);
void TableEnter(HashTable table, void *elem);
void TableRemove(HashTable table, void *elem);
HashTable TableNew(int elemSize, int numBuckets,
	int (*hashFn)(const void *, int),
	int (*compareFn)(const void *, const void *),
	void (*freeFn)(void *));
void TableFree(HashTable table);
__declspec(dllimport) int __cdecl strcasecmp(const char *left, const char *right);
__declspec(dllimport) char *__cdecl strzcpy(char *dest, const char *source, int len);
PEERBool piPingInitPlayer(PEER peer, piPlayer *player);
void piPingPlayerJoinedRoom(PEER peer, piPlayer *player, RoomType roomType);
void piPingPlayerLeftRoom(PEER peer, piPlayer *player);
void piKeyCacheCleanse(PEER peer);
void piKeyCachePlayerChangedNick(PEER peer, const char *oldNick,
	const char *newNick);

static void piSetNewPlayerFlags(PEER peer, const char *nick,
	RoomType roomType, int flags)
{
	piPlayer *player;
	int oldFlags;

	if (!nick)
		return;

	player = piGetPlayer(peer, nick);
	if (!player || !player->inRoom[roomType])
		return;

	oldFlags = player->flags[roomType];
	if (flags == oldFlags)
		return;

	player->flags[roomType] = flags;
	if ((roomType == StagingRoom)
		&& ((oldFlags & PEER_FLAG_READY) != (flags & PEER_FLAG_READY)))
	{
		piAddReadyChangedCallback(peer, player->nick,
			(PEERBool)((player->flags[roomType] & PEER_FLAG_READY) != 0));
	}

	piAddPlayerFlagsChangedCallback(peer, roomType, nick, oldFlags, flags);
}

piPlayer *piGetPlayer(PEER peer, const char *nick)
{
	piPlayer playerMatch;
	piPlayer *player;

	if (!peer->players)
		return 0;

	strzcpy(playerMatch.nick, nick, 0x40);
	playerMatch.nick[0x3F] = '\0';
	player = (piPlayer *)TableLookup(peer->players, &playerMatch);
	return player;
}

static int piPlayersTableHashFn(const void *elem, int numBuckets)
{
	const piPlayer *player = (const piPlayer *)elem;
	const char *str = player->nick;
	unsigned int hash = 0;
	int c;

	while ((c = *str++) != '\0')
		hash += (unsigned int)tolower(c);
	return (int)(hash % (unsigned int)numBuckets);
}

static int piPlayersTableCompareFn(const void *elem1, const void *elem2)
{
	const piPlayer *player1 = (const piPlayer *)elem1;
	const piPlayer *player2 = (const piPlayer *)elem2;

	return strcasecmp(player1->nick, player2->nick);
}

static void piPlayersTableElementFreeFn(void *elem)
{
	(void)elem;
}

PEERBool piPlayersInit(PEER peer)
{
	int i;

	if (peer->stayInTitleRoom)
		return 1;

	peer->players = TableNew(sizeof(piPlayer), 32,
		piPlayersTableHashFn, piPlayersTableCompareFn,
		piPlayersTableElementFreeFn);
	if (!peer->players)
		return 0;

	for (i = 0; i < 3; i++)
		peer->numPlayers[i] = 0;
	return 1;
}

void piPlayersCleanup(PEER peer)
{
	int i;

	if (peer->stayInTitleRoom)
		return;
	if (peer->players)
		TableFree(peer->players);
	peer->players = 0;
	for (i = 0; i < 3; i++)
		peer->numPlayers[i] = 0;
}

static piPlayer *piAddPlayer(PEER peer, const char *nick,
	PEERBool initialize)
{
	piPlayer playerMatch;
	piPlayer *player = &playerMatch;

	memset(player, 0, sizeof(piPlayer));
	strzcpy(player->nick, nick, 0x40);
	player->nick[0x3F] = '\0';
	if (initialize)
	{
		int roomType;

		player->local = (PEERBool)(strcasecmp(nick, peer->nick) == 0);
		for (roomType = 0; roomType < 3; roomType++)
		{
			player->inRoom[roomType] = 0;
			player->flags[roomType] = 0;
		}
		player->IP = 0;
		player->profileID = 0;
		player->gotIPAndProfileID = 0;
		if (!piPingInitPlayer(peer, player))
			return 0;
	}

	TableEnter(peer->players, player);
	return piGetPlayer(peer, nick);
}

static void piRemovePlayer(PEER peer, piPlayer *player)
{
	TableRemove(peer->players, player);
}

piPlayer *piPlayerJoinedRoom(PEER peer, const char *nick,
	RoomType roomType, int mode)
{
	piPlayer *player;

	if (!peer->enteringRoom[roomType] && !peer->inRoom[roomType])
		return 0;

	player = piGetPlayer(peer, nick);
	if (!player)
		player = piAddPlayer(peer, nick, 1);

	player->inRoom[roomType] = 1;
	peer->numPlayers[roomType]++;
	player->flags[roomType] = 0;
	if (mode & CHAT_OP)
		player->flags[roomType] |= PEER_FLAG_OP;
	if (mode & CHAT_VOICE)
		player->flags[roomType] |= PEER_FLAG_VOICE;

	piPingPlayerJoinedRoom(peer, player, roomType);
	return player;
}

void piPlayerLeftRoom(PEER peer, const char *nick, RoomType roomType)
{
	piPlayer *player = piGetPlayer(peer, nick);

	if (!player)
		return;

	player->inRoom[roomType] = 0;
	peer->numPlayers[roomType]--;
	player->flags[roomType] = 0;
	piPingPlayerLeftRoom(peer, player);

	if (!player->inRoom[0] && !player->inRoom[1] && !player->inRoom[2])
		piRemovePlayer(peer, player);

	piKeyCacheCleanse(peer);
}

void piPlayerChangedNick(PEER peer, const char *oldNick,
	const char *newNick)
{
	char playerInfoBuffer[0x70];
	piPlayer *player = piGetPlayer(peer, oldNick);

	if (!player)
		return;

	memcpy(playerInfoBuffer, &player->inRoom[0], sizeof(playerInfoBuffer));
	piRemovePlayer(peer, player);
	player = piAddPlayer(peer, newNick, 0);
	if (!player)
		return;

	memcpy(&player->inRoom[0], playerInfoBuffer, sizeof(playerInfoBuffer));
	piKeyCachePlayerChangedNick(peer, oldNick, newNick);
}

typedef struct piLeftRoomData
{
	PEER peer;
	RoomType roomType;
} piLeftRoomData;

static void piLeftRoomMapFn(void *elem, void *clientData)
{
	piPlayer *player = (piPlayer *)elem;
	piLeftRoomData *data = (piLeftRoomData *)clientData;

	if (player->inRoom[data->roomType])
		piPlayerLeftRoom(data->peer, player->nick, data->roomType);
}

void piClearRoomPlayers(PEER peer, RoomType roomType)
{
	piLeftRoomData data;

	data.peer = peer;
	data.roomType = roomType;
	TableMapSafe(peer->players, piLeftRoomMapFn, &data);
}

void piSetPlayerIPAndProfileID(PEER peer, const char *nick,
	unsigned int IP, int profileID)
{
	piPlayer *player;

	if (!nick)
		return;

	player = piGetPlayer(peer, nick);
	if (player)
	{
		player->IP = IP;
		player->profileID = profileID;
		if (!player->gotIPAndProfileID)
		{
			player->gotIPAndProfileID = 1;
			if (player->inRoom[0])
				piPingPlayerJoinedRoom(peer, player, 0);
			if (player->inRoom[1])
				piPingPlayerJoinedRoom(peer, player, 1);
			if (player->inRoom[2])
				piPingPlayerJoinedRoom(peer, player, 2);
		}
	}
}

typedef void (*piEnumRoomPlayersCallback)(PEER peer, RoomType roomType,
	piPlayer *player, int index, void *param);

typedef struct piEnumRoomPlayersData
{
	PEER peer;
	RoomType roomType;
	int count;
	piEnumRoomPlayersCallback callback;
	void *param;
} piEnumRoomPlayersData;

static void piEnumRoomPlayersMap(void *elem, void *clientData)
{
	piPlayer *player = (piPlayer *)elem;
	piEnumRoomPlayersData *data = (piEnumRoomPlayersData *)clientData;

	if (player->inRoom[data->roomType])
	{
		data->callback(data->peer, data->roomType, player,
			data->count, data->param);
		data->count++;
	}
}

void piEnumRoomPlayers(PEER peer, RoomType roomType,
	piEnumRoomPlayersCallback callback, void *param)
{
	piEnumRoomPlayersData data;

	data.peer = peer;
	data.roomType = roomType;
	data.count = 0;
	data.callback = callback;
	data.param = param;
	TableMap(peer->players, piEnumRoomPlayersMap, &data);
	callback(peer, roomType, 0, -1, param);
}

int piParseFlags(const char *flags)
{
	int nFlags = 0;

	if (strchr(flags, 's'))
		nFlags |= PEER_FLAG_STAGING;
	if (strchr(flags, 'r'))
		nFlags |= PEER_FLAG_READY;
	if (strchr(flags, 'g'))
		nFlags |= PEER_FLAG_PLAYING;
	if (strchr(flags, 'a'))
		nFlags |= PEER_FLAG_AWAY;
	if (strchr(flags, 'h'))
		nFlags |= PEER_FLAG_HOST;

	return nFlags;
}

void piSetPlayerRoomFlags(PEER peer, const char *nick,
	RoomType roomType, const char *flags)
{
	piPlayer *player;
	int nFlags;

	if (!nick)
		return;

	player = piGetPlayer(peer, nick);
	if (!player || !player->inRoom[roomType])
		return;

	nFlags = player->flags[roomType] & (PEER_FLAG_OP | PEER_FLAG_VOICE);
	nFlags |= piParseFlags(flags);
	piSetNewPlayerFlags(peer, nick, roomType, nFlags);
}

void piSetPlayerModeFlags(PEER peer, const char *nick,
	RoomType roomType, int mode)
{
	piPlayer *player;
	int nFlags;

	if (!nick)
		return;

	player = piGetPlayer(peer, nick);
	if (!player || !player->inRoom[roomType])
		return;

	nFlags = player->flags[roomType] & ~(PEER_FLAG_OP | PEER_FLAG_VOICE);
	if (mode & CHAT_OP)
		nFlags |= PEER_FLAG_OP;
	if (mode & CHAT_VOICE)
		nFlags |= PEER_FLAG_VOICE;

	piSetNewPlayerFlags(peer, nick, roomType, nFlags);
}

typedef struct piFindPlayerByIndexData
{
	int index;
	int count;
	RoomType roomType;
} piFindPlayerByIndexData;

static int piFindPlayerByIndexMap(void *elem, void *clientData)
{
	piPlayer *player = (piPlayer *)elem;
	piFindPlayerByIndexData *data = (piFindPlayerByIndexData *)clientData;

	if (player->inRoom[data->roomType])
	{
		if (data->index == data->count)
			return 0;
		data->count++;
	}

	return 1;
}

piPlayer *piFindPlayerByIndex(PEER peer, RoomType roomType, int index)
{
	piFindPlayerByIndexData data;

	data.index = index;
	data.count = 0;
	data.roomType = roomType;
	return (piPlayer *)TableMap2(peer->players, piFindPlayerByIndexMap, &data);
}

typedef struct piCountRoomOpsMapData
{
	int count;
	RoomType roomType;
	const char *exclude;
} piCountRoomOpsMapData;

static void piCountRoomOpsMap(void *elem, void *clientData)
{
	piPlayer *player = (piPlayer *)elem;
	piCountRoomOpsMapData *data = (piCountRoomOpsMapData *)clientData;

	if (data->exclude && strcasecmp(data->exclude, player->nick) == 0)
		return;
	if (player->flags[data->roomType] & PEER_FLAG_OP)
		data->count++;
}

int piCountRoomOps(PEER peer, RoomType roomType, const char *exclude)
{
	piCountRoomOpsMapData data;

	data.count = 0;
	data.roomType = roomType;
	data.exclude = exclude;
	TableMap(peer->players, piCountRoomOpsMap, &data);
	return data.count;
}
