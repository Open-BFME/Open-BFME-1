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
	unsigned char pad_0044[0xAB8 - 0x44];
	int numPlayers[3];
	unsigned char pad_0AC4[0xB48 - 0xAC4];
	int maxPlayers;
	unsigned char pad_0B4C[0x1EF0 - 0xB4C];
	piOperation *autoMatchOperation;
	unsigned char pad_1EF4[0x1EFC - 0x1EF4];
	PEERBool autoMatchSBFailed;
	PEERBool autoMatchQRFailed;
} PEERConnection;

typedef PEERConnection *PEER;

int piGetNextID(PEER peer);
void piSetAutoMatchStatus(PEER peer, int status);
int piNewCreateStagingRoomOperation(PEER peer, const char *nick,
	const char *password, int maxPlayers, int socket, unsigned short port,
	void *callback, void *param, int opID);

typedef int PEERJoinResult;
typedef int RoomType;

void piCreateAutoMatchRoomCallback
(
	PEER peer,
	PEERBool success,
	PEERJoinResult result,
	RoomType roomType,
	void *param
)
{
	int status;

	if (success)
	{
		if (peer->numPlayers[2] <= 1)
			status = 2;
		else if (peer->numPlayers[2] >= peer->maxPlayers)
			status = 4;
		else
			status = 3;

		piSetAutoMatchStatus(peer, status);
	}
	else
	{
		peer->autoMatchQRFailed = 1;
		piSetAutoMatchStatus(peer,
			peer->autoMatchSBFailed ? 0 : 1);
	}

	(void)result;
	(void)roomType;
	(void)param;
}

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
