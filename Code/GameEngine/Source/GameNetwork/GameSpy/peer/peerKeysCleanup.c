// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy PEER SDK -- piKeysCleanup from peerKeys.c. */

typedef void *PEER;
typedef void *HashTable;

typedef struct piConnection
{
	unsigned char pad0[0x18AC];
	HashTable roomWatchKeys[3];
	HashTable roomKeys[3];
	HashTable globalKeys;
	HashTable playerKeys[3];
} piConnection;

void TableFree(HashTable table);

void piKeysCleanup(PEER peer)
{
	int roomType;
	piConnection *connection = (piConnection *)peer;

	if (connection->globalKeys)
		TableFree(connection->globalKeys);

	for (roomType = 0; roomType < 3; ++roomType) {
		if (connection->roomWatchKeys[roomType])
			TableFree(connection->roomWatchKeys[roomType]);
		if (connection->roomKeys[roomType])
			TableFree(connection->roomKeys[roomType]);
		if (connection->playerKeys[roomType])
			TableFree(connection->playerKeys[roomType]);
	}
}
