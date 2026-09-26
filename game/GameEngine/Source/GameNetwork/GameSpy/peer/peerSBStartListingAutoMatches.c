// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef struct PEERConnection
{
	unsigned char pad_0000[0x0BA0];
	int sbInitialized;
	unsigned char pad_0BA4[0x0D34];
	unsigned char autoMatchList[0x05CC];
	unsigned char autoMatchEngine[0x0048];
	int autoMatchBrowsing;
	unsigned char pad_1EF0[8];
	const char *autoMatchFilter;
	int autoMatchSBFailed;
} PEERConnection;

typedef PEERConnection *PEER;
typedef int PEERBool;

void SBServerListDisconnect(void *serverList);
void SBEngineHaltUpdates(void *queryEngine);
void SBServerListClear(void *serverList);
int SBServerListConnectAndQuery(
	void *serverList, const char *fields, const char *filter,
	int queryType, int disconnectOnComplete);

static __forceinline void piSBStopListingAutoMatches(PEER peer)
{
	if (!peer->sbInitialized)
		return;

	peer->autoMatchBrowsing = 0;
	SBServerListDisconnect(&peer->autoMatchList);
	SBEngineHaltUpdates(&peer->autoMatchEngine);
}

PEERBool piSBStartListingAutoMatches(PEER peer)
{
	if (!peer->sbInitialized) {
		peer->autoMatchSBFailed = 1;
		return 0;
	}

	piSBStopListingAutoMatches(peer);
	SBServerListClear(&peer->autoMatchList);

	if (SBServerListConnectAndQuery(
			&peer->autoMatchList, 0, peer->autoMatchFilter, 4, 0) != 0) {
		piSBStopListingAutoMatches(peer);
		peer->autoMatchSBFailed = 1;
		return 0;
	}

	peer->autoMatchSBFailed = 0;
	peer->autoMatchBrowsing = 1;
	return 1;
}
