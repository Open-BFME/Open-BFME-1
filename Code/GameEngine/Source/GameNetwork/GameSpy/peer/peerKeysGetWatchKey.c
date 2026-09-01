// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy PEER SDK -- watch-key functions from peerKeys.c. */

#include <string.h>

typedef void *PEER;
typedef void *HashTable;
typedef void *CHAT;
typedef int RoomType;
typedef int PEERBool;
typedef int CHATBool;

typedef struct piConnection
{
	CHAT chat;
	unsigned char pad04[0x7C];
	char rooms[3][0x101];
	unsigned char pad383;
	int enteringRoom[3];
	int inRoom[3];
	unsigned char pad39c[0x728];
	int alwaysRequestPlayerInfo;
	unsigned char padac8[8];
	int pingRoom[3];
	unsigned char padadc[0xDD0];
	HashTable globalWatchKeys[3];
	HashTable roomWatchKeys[3];
	HashTable globalWatchCache;
	HashTable roomWatchCache[3];
} piConnection;

typedef struct piPlayer
{
	char nick[0x40];
	int inRoom[3];
	int local;
	unsigned int IP;
	int profileID;
	int gotIPAndProfileID;
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

typedef struct piRemoveExistingKeysData
{
	int num;
	const char **keys;
	HashTable watchKeys;
} piRemoveExistingKeysData;

typedef struct piPlayerChangedNickMapData
{
	const char *oldNick;
	const char *newNick;
} piPlayerChangedNickMapData;

typedef struct piSetupKeysMapData
{
	int next;
	char **keys;
} piSetupKeysMapData;

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
void TableMap(HashTable table, void (*mapFunction)(void *, void *), void *clientData);
void TableClear(HashTable table);
piPlayer *piGetPlayer(PEER peer, const char *nick);
__declspec(dllimport) int __cdecl strcasecmp(const char *left, const char *right);
__declspec(dllimport) void __cdecl free(void *memory);
char *goastrdup(const char *source);
void TableEnter(HashTable table, const void *element);
int TableCount(HashTable table);
void piAddPlayerInfoCallback(PEER peer, RoomType roomType, const char *nick,
	unsigned int IP, int profileID);
PEERBool piDemangleUser(const char *user, unsigned int *IP, int *profileID);
void piSetPlayerIPAndProfileID(PEER peer, const char *nick, unsigned int IP,
	int profileID);
void piSetPlayerRoomFlags(PEER peer, const char *nick, RoomType roomType,
	const char *flags);
void piAddGlobalKeyChangedCallback(PEER peer, const char *nick, const char *key,
	const char *value);
void piAddRoomKeyChangedCallback(PEER peer, RoomType roomType, const char *nick,
	const char *key, const char *value);
PEERBool piRoomToType(PEER peer, const char *room, RoomType *roomType);
__declspec(dllimport) void *__cdecl malloc(unsigned int size);
void chatGetGlobalKeysA(CHAT chat, const char *user, int num,
	const char **keys, void (*callback)(CHAT, CHATBool, const char *, int,
		const char **, const char **, void *), void *param, CHATBool blocking);
void chatGetChannelKeysA(CHAT chat, const char *channel, const char *user,
	int num, const char **keys, void (*callback)(CHAT, CHATBool, const char *,
		const char *, int, const char **, const char **, void *), void *param,
	CHATBool blocking);

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

void piRemoveExistingKeysMap(void *elem, void *clientData)
{
	int i;
	piWatchKey *key = (piWatchKey *)elem;
	piRemoveExistingKeysData *data = (piRemoveExistingKeysData *)clientData;

	for (i = 0; i < data->num; i++) {
		if (strcasecmp(key->key, data->keys[i]) == 0)
			return;
	}
	TableRemove(data->watchKeys, key);
}

void piPlayerChangedNickMap(void *elem, void *clientData)
{
	piCacheKey *key = (piCacheKey *)elem;
	piPlayerChangedNickMapData *data = (piPlayerChangedNickMapData *)clientData;

	if (strcasecmp(key->nick, data->oldNick) == 0) {
		free(key->nick);
		key->nick = goastrdup(data->newNick);
	}
}

void piKeyCachePlayerChangedNick(PEER peer, const char *oldNick,
	const char *newNick)
{
	piPlayerChangedNickMapData data;
	piConnection *connection = (piConnection *)peer;

	data.oldNick = oldNick;
	data.newNick = newNick;
	TableMap(connection->globalWatchCache, piPlayerChangedNickMap, &data);
	TableMap(connection->roomWatchCache[0], piPlayerChangedNickMap, &data);
	TableMap(connection->roomWatchCache[1], piPlayerChangedNickMap, &data);
	TableMap(connection->roomWatchCache[2], piPlayerChangedNickMap, &data);
}

static PEERBool piKeyChanged(PEER peer, const char *nick, const char *key,
	const char *value, HashTable watchKeys, HashTable watchCache, PEERBool inRoom,
	RoomType roomType)
{
	piWatchKey watchKeyTemp;
	piCacheKey cacheKey;

	if (!nick || !nick[0])
		return 1;
	if (!value)
		value = "";

	if (strcasecmp(key, "username") == 0) {
		piPlayer *player;

		if (strcmp(nick, "(END)") == 0) {
			piAddPlayerInfoCallback(peer, roomType, 0, 0, 0);
			return 0;
		}

		player = piGetPlayer(peer, nick);
		if (player && !player->gotIPAndProfileID) {
			int profileID;
			unsigned int IP;

			if (piDemangleUser(value, &IP, &profileID))
				piSetPlayerIPAndProfileID(peer, nick, IP, profileID);
		}

		if (inRoom) {
			if (player && player->gotIPAndProfileID)
				piAddPlayerInfoCallback(peer, roomType, nick, player->IP,
					player->profileID);
			else
				piAddPlayerInfoCallback(peer, roomType, nick, 0, 0);
		}
	}

	if (inRoom && strcasecmp(key, "b_flags") == 0)
		piSetPlayerRoomFlags(peer, nick, roomType, value);

	watchKeyTemp.key = (char *)key;
	if (!TableLookup(watchKeys, &watchKeyTemp)) {
		if (inRoom && strncmp(key, "b_", 2) == 0)
			return 1;
		return 0;
	}

	memset(&cacheKey, 0, sizeof(cacheKey));
	cacheKey.nick = goastrdup(nick);
	cacheKey.key = goastrdup(key);
	cacheKey.value = goastrdup(value);
	TableEnter(watchCache, &cacheKey);
	return 1;
}

void piGlobalKeyChanged(PEER peer, const char *nick, const char *key,
	const char *value)
{
	piConnection *connection = (piConnection *)peer;

	if (piKeyChanged(peer, nick, key, value, connection->globalWatchKeys[0],
			connection->globalWatchCache, 0, 0)
		|| piKeyChanged(peer, nick, key, value, connection->globalWatchKeys[1],
			connection->globalWatchCache, 0, 0)
		|| piKeyChanged(peer, nick, key, value, connection->globalWatchKeys[2],
			connection->globalWatchCache, 0, 0))
		piAddGlobalKeyChangedCallback(peer, nick, key, value);
}

void piRoomKeyChanged(PEER peer, RoomType roomType, const char *nick,
	const char *key, const char *value)
{
	piConnection *connection = (piConnection *)peer;

	if (piKeyChanged(peer, nick, key, value, connection->roomWatchKeys[roomType],
		connection->roomWatchCache[roomType], 1, roomType))
		piAddRoomKeyChangedCallback(peer, roomType, nick, key, value);
}

void piSetupKeysMap(void *elem, void *clientData)
{
	piWatchKey *key = (piWatchKey *)elem;
	piSetupKeysMapData *data = (piSetupKeysMapData *)clientData;

	data->keys[data->next++] = key->key;
}

void piKeysGetGlobalKeysCallbackA(CHAT chat, CHATBool success, const char *user,
	int num, const char **keys, const char **values, void *param)
{
	PEER peer = (PEER)param;
	int i;

	if (success && user) {
		for (i = 0; i < num; i++)
			piGlobalKeyChanged(peer, user, keys[i], values[i]);
	}
	(void)chat;
}

void piGetRoomKeysCallbackA(CHAT chat, CHATBool success, const char *channel,
	const char *user, int num, const char **keys, const char **values, void *param)
{
	PEER peer = (PEER)param;

	if (!user && success) {
		int i;
		RoomType roomType;
		static const char *endName = "(END)";

		if (!piRoomToType(peer, channel, &roomType))
			return;
		for (i = 0; i < num; i++)
			piRoomKeyChanged(peer, roomType, endName, keys[i], 0);
		return;
	}

	if (success) {
		int i;
		RoomType roomType;

		if (!piRoomToType(peer, channel, &roomType))
			return;
		for (i = 0; i < num; i++)
			piRoomKeyChanged(peer, roomType, user, keys[i], values[i]);
	}
	(void)chat;
}

static void piKeyCacheRefresh(PEER peer, RoomType roomType, const char *nick)
{
	int num;
	piSetupKeysMapData data;
	PEERBool getIP;
	PEERBool getFlags;
	piWatchKey watchKey;
	piConnection *connection = (piConnection *)peer;

	if (!connection->inRoom[roomType] && !connection->enteringRoom[roomType])
		return;

	if (!nick)
		getIP = connection->pingRoom[roomType]
			|| connection->alwaysRequestPlayerInfo;
	else
		getIP = 0;

	if (getIP) {
		watchKey.key = "username";
		getIP = !TableLookup(connection->roomWatchKeys[roomType], &watchKey);
	}

	getFlags = nick == 0;
	if (getFlags) {
		watchKey.key = "b_flags";
		getFlags = !(TableLookup(connection->globalWatchKeys[roomType], &watchKey)
			|| TableLookup(connection->roomWatchKeys[roomType], &watchKey));
	}

	data.next = 0;
	num = TableCount(connection->globalWatchKeys[roomType]);
	if (num) {
		data.keys = (char **)malloc(sizeof(char *) * num);
		if (!data.keys)
			return;
		TableMap(connection->globalWatchKeys[roomType], piSetupKeysMap, &data);
		chatGetGlobalKeysA(connection->chat,
			nick ? nick : connection->rooms[roomType], num,
			(const char **)data.keys, piKeysGetGlobalKeysCallbackA, peer, 0);
		free(data.keys);
	}

	if (!nick) {
		data.next = 0;
		num = TableCount(connection->roomWatchKeys[roomType]);
		if (getIP)
			num++;
		if (getFlags)
			num++;
		if (num) {
			data.keys = (char **)malloc(sizeof(char *) * num);
			if (!data.keys)
				return;
			TableMap(connection->roomWatchKeys[roomType], piSetupKeysMap, &data);
			if (getIP)
				data.keys[data.next++] = "username";
			if (getFlags)
				data.keys[data.next++] = "b_flags";
			chatGetChannelKeysA(connection->chat, connection->rooms[roomType],
				nick ? nick : "*", num, (const char **)data.keys,
				piGetRoomKeysCallbackA, peer, 0);
			free(data.keys);
		}
	}
}

void piKeyCacheRefreshPlayer(PEER peer, RoomType roomType, const char *nick)
{
	piKeyCacheRefresh(peer, roomType, nick);
}

void piKeyCacheRefreshRoom(PEER peer, RoomType roomType)
{
	piKeyCacheRefresh(peer, roomType, 0);
}

void piSetRoomWatchKeys(PEER peer, RoomType roomType, int num,
	const char **keys, PEERBool addKeys)
{
	piWatchKey watchKey;
	int i;
	piConnection *connection = (piConnection *)peer;

	if (num == 0) {
		if (addKeys)
			return;
		TableClear(connection->roomWatchKeys[roomType]);
		TableClear(connection->roomWatchCache[roomType]);
		return;
	}

	if (!addKeys) {
		piRemoveExistingKeysData data;

		data.num = num;
		data.keys = keys;
		data.watchKeys = connection->roomWatchKeys[roomType];
		TableMapSafe(connection->roomWatchKeys[roomType], piRemoveExistingKeysMap,
			&data);
	}

	for (i = 0; i < num; i++) {
		watchKey.key = goastrdup(keys[i]);
		TableEnter(connection->roomWatchKeys[roomType], &watchKey);
	}

	if (connection->enteringRoom[roomType] || connection->inRoom[roomType])
		chatGetChannelKeysA(connection->chat, connection->rooms[roomType], "*", num,
			keys, piGetRoomKeysCallbackA, peer, 0);
}
