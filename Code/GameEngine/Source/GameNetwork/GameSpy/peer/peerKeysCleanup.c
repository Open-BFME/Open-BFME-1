// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy PEER SDK -- piKeysCleanup from peerKeys.c. */

typedef void *PEER;
typedef void *HashTable;

typedef struct piConnection
{
	unsigned char pad0[0x18AC];
	HashTable globalWatchKeys[3];
	HashTable roomWatchKeys[3];
	HashTable globalWatchCache;
	HashTable roomWatchCache[3];
} piConnection;

void TableFree(HashTable table);

void piKeysCleanup(PEER peer)
{
	int roomType;
	piConnection *connection = (piConnection *)peer;

	if (connection->globalWatchCache)
		TableFree(connection->globalWatchCache);

	for (roomType = 0; roomType < 3; ++roomType) {
		if (connection->globalWatchKeys[roomType])
			TableFree(connection->globalWatchKeys[roomType]);
		if (connection->roomWatchKeys[roomType])
			TableFree(connection->roomWatchKeys[roomType]);
		if (connection->roomWatchCache[roomType])
			TableFree(connection->roomWatchCache[roomType]);
	}
}
