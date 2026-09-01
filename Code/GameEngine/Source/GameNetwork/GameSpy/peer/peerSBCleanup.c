// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef struct PEERConnection
{
	unsigned char pad_0000[0x0BA0];
	int sbInitialized;
	unsigned char gameList[0x05CC];
	unsigned char groupList[0x05CC];
	unsigned char gameEngine[0x019C];
	unsigned char autoMatchList[0x05CC];
	unsigned char autoMatchEngine[0x0048];
	int autoMatchBrowsing;
} PEERConnection;

typedef PEERConnection *PEER;

void SBServerListDisconnect(void *serverList);
void SBServerListCleanup(void *serverList);
void SBEngineHaltUpdates(void *queryEngine);
void SBEngineCleanup(void *queryEngine);
void piClearCallbacks(PEER peer, int type);

static __forceinline void piSBStopListingGames(PEER peer)
{
	if (!peer->sbInitialized)
		return;

	SBServerListDisconnect(&peer->gameList);
	SBEngineHaltUpdates(&peer->gameEngine);
	piClearCallbacks(peer, 3);
}

static __forceinline void piSBStopListingGroups(PEER peer)
{
	if (!peer->sbInitialized)
		return;

	SBServerListDisconnect(&peer->groupList);
}

void piSBCleanup(PEER peer)
{
	piSBStopListingGames(peer);
	piSBStopListingGroups(peer);

	if (peer->sbInitialized) {
		SBServerListCleanup(&peer->gameList);
		SBEngineCleanup(&peer->gameEngine);
		SBServerListCleanup(&peer->groupList);
		SBServerListCleanup(&peer->autoMatchList);
		SBEngineCleanup(&peer->autoMatchEngine);
	}

	peer->autoMatchBrowsing = 0;
}
