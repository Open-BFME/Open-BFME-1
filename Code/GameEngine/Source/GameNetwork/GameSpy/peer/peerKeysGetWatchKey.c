// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy PEER SDK -- watch-key lookup functions from peerKeys.c. */

typedef void *PEER;
typedef void *HashTable;
typedef int RoomType;

typedef struct piConnection
{
	unsigned char pad0[0x18AC];
	HashTable globalWatchKeys[3];
	HashTable roomWatchKeys[3];
	HashTable globalWatchCache;
	HashTable roomWatchCache[3];
} piConnection;

typedef struct piPlayer
{
	char nick[0x40];
	int inRoom[3];
} piPlayer;

typedef struct piWatchKey
{
	char *key;
} piWatchKey;

typedef struct piCleanseRoomCacheMapData
{
	PEER peer;
	RoomType roomType;
} piCleanseRoomCacheMapData;

typedef struct piCacheKey
{
	char *nick;
	char *key;
	char *value;
} piCacheKey;

void *TableLookup(HashTable table, const void *element);
void TableRemove(HashTable table, const void *element);
piPlayer *piGetPlayer(PEER peer, const char *nick);

static const char *piGetWatchKeyA(const char *nick, const char *key,
	HashTable watchCache)
{
	piCacheKey keyTemp;
	piCacheKey *cacheKey;

	keyTemp.nick = (char *)nick;
	keyTemp.key = (char *)key;
	cacheKey = (piCacheKey *)TableLookup(watchCache, &keyTemp);
	if (!cacheKey)
		return 0;
	if (cacheKey->value)
		return cacheKey->value;
	return "";
}

const char *piGetGlobalWatchKeyA(PEER peer, const char *nick, const char *key)
{
	piConnection *connection = (piConnection *)peer;
	return piGetWatchKeyA(nick, key, connection->globalWatchCache);
}

const char *piGetRoomWatchKeyA(PEER peer, RoomType roomType, const char *nick,
	const char *key)
{
	piConnection *connection = (piConnection *)peer;
	return piGetWatchKeyA(nick, key, connection->roomWatchCache[roomType]);
}

void piCleanseRoomCacheMap(void *elem, void *clientData)
{
	piPlayer *player;
	piCacheKey *cacheKey = (piCacheKey *)elem;
	piCleanseRoomCacheMapData *data = (piCleanseRoomCacheMapData *)clientData;
	piConnection *connection = (piConnection *)data->peer;
	piWatchKey watchKeyTemp;

	watchKeyTemp.key = cacheKey->key;
	player = piGetPlayer(data->peer, cacheKey->nick);
	if (player && player->inRoom[data->roomType]) {
		if (TableLookup(connection->roomWatchKeys[data->roomType], &watchKeyTemp))
			return;
	}
	TableRemove(connection->globalWatchCache, cacheKey);
}
