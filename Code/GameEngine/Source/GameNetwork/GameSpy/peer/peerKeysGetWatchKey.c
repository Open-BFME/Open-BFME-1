// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy PEER SDK -- watch-key lookup functions from peerKeys.c. */

typedef void *PEER;
typedef void *HashTable;
typedef int RoomType;

typedef struct piConnection
{
	unsigned char pad0[0x384];
	int enteringRoom[3];
	int inRoom[3];
	unsigned char pad1[0x1510];
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
void TableMapSafe(HashTable table, void (*mapFunction)(void *, void *),
	void *clientData);
void TableClear(HashTable table);
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

void piCleanseGlobalCacheMap(void *elem, void *clientData)
{
	piPlayer *player;
	int roomType;
	piCacheKey *cacheKey = (piCacheKey *)elem;
	PEER peer = (PEER)clientData;
	piConnection *connection = (piConnection *)peer;
	piWatchKey watchKeyTemp;

	watchKeyTemp.key = cacheKey->key;
	player = piGetPlayer(peer, cacheKey->nick);
	if (player) {
		for (roomType = 0; roomType < 3; roomType++) {
			if (player->inRoom[roomType]) {
				if (TableLookup(connection->globalWatchKeys[roomType], &watchKeyTemp))
					return;
			}
		}
	}
	TableRemove(connection->globalWatchCache, cacheKey);
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

void piKeyCacheCleanse(PEER peer)
{
	int roomType;
	piCleanseRoomCacheMapData data;
	piConnection *connection = (piConnection *)peer;

	TableMapSafe(connection->globalWatchCache, piCleanseGlobalCacheMap, peer);
	data.peer = peer;
	for (roomType = 0; roomType < 3; roomType++) {
		if (connection->inRoom[roomType] || connection->enteringRoom[roomType]) {
			data.roomType = roomType;
			TableMapSafe(connection->roomWatchCache[roomType], piCleanseRoomCacheMap,
				&data);
		} else {
			TableClear(connection->roomWatchCache[roomType]);
		}
	}
}
