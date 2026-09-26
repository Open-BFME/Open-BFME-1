// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef void *PEER;
typedef void *SBServer;

void piAddListingGamesCallback(
	PEER peer,
	int success,
	SBServer server,
	int message);

void piSBGamesEngineCallback(
	void *engine,
	int reason,
	SBServer server,
	void *instance)
{
	(void)engine;

	if (reason == 0)
		piAddListingGamesCallback(instance, 1, server, 1);
}
