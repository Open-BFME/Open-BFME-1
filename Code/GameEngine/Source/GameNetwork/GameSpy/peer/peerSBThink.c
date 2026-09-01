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
	unsigned char autoMatchEngine[1];
} PEERConnection;

typedef PEERConnection *PEER;

void SBListThink(void *serverList);
void SBQueryEngineThink(void *queryEngine);

void piSBThink(PEER peer)
{
	if (!peer->sbInitialized)
		return;

	SBListThink(&peer->gameList);
	SBListThink(&peer->groupList);
	SBQueryEngineThink(&peer->gameEngine);
	SBListThink(&peer->autoMatchList);
	SBQueryEngineThink(&peer->autoMatchEngine);
}
