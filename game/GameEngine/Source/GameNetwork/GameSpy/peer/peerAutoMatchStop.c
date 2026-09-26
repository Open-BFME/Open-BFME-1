// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerAutoMatch.c */

typedef int PEERBool;

typedef struct piOperation
{
	unsigned char pad_0000[0x10];
	void *callback;
} piOperation;

typedef struct PEERConnection
{
	unsigned char pad_0000[0x390];
	PEERBool inRoom[3];
	unsigned char pad_039C[0x1EF0 - 0x39C];
	piOperation *autoMatchOperation;
} PEERConnection;

typedef PEERConnection *PEER;

PEERBool peerIsAutoMatching(PEER peer);
void piSetAutoMatchStatus(PEER peer, int status);

void piStopAutoMatch(PEER peer)
{
	PEERBool inRoom;

	if (peerIsAutoMatching(peer))
	{
		if (peer->autoMatchOperation)
			peer->autoMatchOperation->callback = 0;

		inRoom = peer->inRoom[2];
		peer->inRoom[2] = 0;
		piSetAutoMatchStatus(peer, 0);
		peer->inRoom[2] = inRoom;
	}
}
