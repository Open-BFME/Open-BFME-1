// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef struct PEERConnection
{
	unsigned char pad_0000[0x0BA0];
	int sbInitialized;
	unsigned char gameList[0x05CC];
	unsigned char groupList[1];
} PEERConnection;

typedef PEERConnection *PEER;

void SBServerListDisconnect(void *serverList);

void piSBStopListingGroups(PEER peer)
{
	if (!peer->sbInitialized)
		return;

	SBServerListDisconnect(&peer->groupList);
}
