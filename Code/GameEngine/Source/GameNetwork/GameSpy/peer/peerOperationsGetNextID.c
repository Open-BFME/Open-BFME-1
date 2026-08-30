// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerOperations.c, 2007 release, piGetNextID.

typedef void *PEER;

typedef struct piConnection
{
	char reserved[0x1794];
	int nextID;
} piConnection;

int piGetNextID(PEER peer)
{
	piConnection *connection = (piConnection *)peer;
	int ID = connection->nextID;

	connection->nextID++;
	if (connection->nextID < 0)
		connection->nextID = 0;

	return ID;
}
