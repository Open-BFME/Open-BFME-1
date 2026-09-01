// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy PEER SDK -- watch-key lookup functions from peerKeys.c. */

typedef void *PEER;
typedef void *HashTable;

typedef struct piConnection
{
	unsigned char pad0[0x18C4];
	HashTable globalWatchCache;
} piConnection;

typedef struct piCacheKey
{
	char *nick;
	char *key;
	char *value;
} piCacheKey;

void *TableLookup(HashTable table, const void *element);

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
