// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerAutoMatch.c */

typedef int PEERBool;

typedef struct piOperation
{
	unsigned char pad_0000[0x2C];
	int socket;
	unsigned short port;
} piOperation;

typedef struct PEERConnection
{
	unsigned char pad_0000[4];
	char nick[64];
	unsigned char pad_0044[0xB48 - 0x44];
	int maxPlayers;
	unsigned char pad_0B4C[0x1EF0 - 0xB4C];
	piOperation *autoMatchOperation;
	unsigned char pad_1EF4[0x1F00 - 0x1EF4];
	PEERBool autoMatchQRFailed;
} PEERConnection;

typedef PEERConnection *PEER;

int piGetNextID(PEER peer);
void piCreateAutoMatchRoomCallback(void);
int piNewCreateStagingRoomOperation(PEER peer, const char *nick,
	const char *password, int maxPlayers, int socket, unsigned short port,
	void *callback, void *param, int opID);

PEERBool piCreateAutoMatchRoom(PEER peer)
{
	piOperation *operation = peer->autoMatchOperation;

	if (!piNewCreateStagingRoomOperation(peer, peer->nick, "",
		peer->maxPlayers, operation->socket, operation->port,
		(void *)piCreateAutoMatchRoomCallback, 0, piGetNextID(peer)))
	{
		peer->autoMatchQRFailed = 1;
		return 0;
	}

	return 1;
}
