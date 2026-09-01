// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Peer SDK -- piSBStopListingGames from peerSB.c. */

typedef void *PEER;

typedef struct piConnection
{
	unsigned char pad0[0xBA0];
	int sbInitialized;
	unsigned char gameList[0xB98];
	unsigned char gameEngine;
} piConnection;

void SBServerListDisconnect(void *serverList);
void SBEngineHaltUpdates(void *engine);
void piClearCallbacks(PEER peer, int type);

void piSBStopListingGames(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if(!connection->sbInitialized)
		return;

	SBServerListDisconnect(&connection->gameList);
	SBEngineHaltUpdates(&connection->gameEngine);
	piClearCallbacks(peer, 3);
}
